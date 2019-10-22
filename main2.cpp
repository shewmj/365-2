#include <iostream> 
#include <iomanip>
#include <fstream>
#include <map>
#include <cstring>
#include <bitset>


#include <math.h>
#include <vector>
using namespace std; 



bitset<32> ToBits32(unsigned long byte)
{
    return bitset<32>(byte);
}



bitset<8> ToBits8(unsigned char byte)
{
    return bitset<8>(byte);
}


void Decode(char* inString, size_t length, string fileName) {

	std::map<string,int> binarySteps;
  	binarySteps["1111"] = -8;
  	binarySteps["1110"] = -7;
  	binarySteps["1101"] = -6;
  	binarySteps["1100"] = -5;
  	binarySteps["1011"] = -4;
  	binarySteps["1010"] = -3;
  	binarySteps["1001"] = -2;
  	binarySteps["0000"] = -1;
  	binarySteps["0001"] = 1;
  	binarySteps["0010"] = 2;
  	binarySteps["0011"] = 3;
  	binarySteps["0100"] = 4;
  	binarySteps["0101"] = 5;
  	binarySteps["0110"] = 6;
  	binarySteps["0111"] = 7;

  	std::map<string,int> binaryRange;
  	binaryRange["0000"] = 0;
  	binaryRange["0001"] = 1;
  	binaryRange["0010"] = 2;
  	binaryRange["0011"] = 3;
  	binaryRange["0100"] = 4;
  	binaryRange["0101"] = 5;
  	binaryRange["0110"] = 6;
  	binaryRange["0111"] = 7;
  	binaryRange["1000"] = 8;
  	binaryRange["1001"] = 9;
  	binaryRange["1010"] = 10;
  	binaryRange["1011"] = 11;
  	binaryRange["1100"] = 12;



  	ofstream myfile;
	myfile.open (fileName);



	//decode each 9byte block into 32 bits floats
  	std::map<string,int>::iterator it;
  	vector<float> values = {};
	for (int i = 0; i < length; i++) {  
        bitset<8> header = ToBits8(*(inString+i));
        string scaleString =  header.to_string().substr(0, 4);
        string coefficientString = header.to_string().substr(4, 2);
        int coefficient;
        if(coefficientString == "00"){
        	coefficient = 0;
        } else {
        	coefficient = 2;
        }
        
        it = binaryRange.find(scaleString);
        int scale = it->second;

        float prev = 0;
        float prev2 = 0;
        for(int j = 0; j < 8; j++) {
        	i++;
        	if(i >= length)
        		break;



        	bitset<8> byte = ToBits8(*(inString+i));
        	string bsetString = byte.to_string();


        	string sampleString = bsetString.substr(0, 4);
        	it = binarySteps.find(sampleString);
        	float sample = it->second * pow(2, scale);
        	if(coefficient == 2) {
        		float temp = sample;
        		sample += ((61/32) * prev) - ((15/16) * prev2);
        		prev2 = prev;
        		prev = temp;
        	}




        	sample /= pow(10, 12);
        	values.push_back(sample);



        	sampleString = bsetString.substr(4, 4);
        	it = binarySteps.find(sampleString);
        	sample = it->second * pow(2, scale);
        	if(coefficient == 2) {
        		float temp = sample;
        		sample += ((61/32) * prev) - ((15/16) * prev2);
        		prev2 = prev;
        		prev = temp;
        	}



        	sample /= pow(10, 12);
        	values.push_back(sample);



        	
        	
        }
       
    }

    //reverse byte order for 32 bit float big endian file output
    float t;
    for (int i = 0 ; i < values.size(); i++) {
		t = values[i];
		
		char data[4];
		memcpy(data, &t, sizeof(t));
		char a = data[0];
		char b = data[1];
		char c = data[2];
		char d = data[3];

		myfile << d;
		myfile << c;
		myfile << b;
		myfile << a;

    }

    myfile.close();


}



int main(int argc, char** argv) 
{ 


	ifstream inFile; 
	size_t size = 0;
	inFile.open(argv[1], ios::in|ios::binary);
	char* oData = 0;

	if(inFile.is_open()) {
		inFile.seekg(0, ios::end);
		size = inFile.tellg();
		inFile.seekg(0, ios::beg);

		oData = new char[size];
		inFile.read(oData, size);
		
	}

	Decode(oData, size, argv[2]);

	
	return 0;







}