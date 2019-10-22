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





  	std::map<string,int>::iterator it;
  	vector<float> values = {};


	for (int i = 0; i < length; i++) {  
        bitset<8> header = ToBits8(*(inString+i));
        //cout << "+)))))))))" << header << endl;
        string scaleString =  header.to_string().substr(0, 4);
        it = binaryRange.find(scaleString);
        int scale = it->second;


    	
        for(int j = 0; j < 8; j++) {
        	i++;
        	if(i >= length)
        		break;
        	bitset<8> byte = ToBits8(*(inString+i));
        	string bsetString = byte.to_string();
        	//cout << "++++++++++" << bsetString << endl;

        	string sampleString = bsetString.substr(0, 4);
        	it = binarySteps.find(sampleString);
        	float sample = it->second * pow(2, scale);
        	sample /= pow(10, 12);

        	values.push_back(sample);
        	//cout << sample << endl;

        	sampleString = bsetString.substr(4, 4);
        	it = binarySteps.find(sampleString);
        	sample = it->second * pow(2, scale);
        	sample /= pow(10, 12);
        	values.push_back(sample);
        	//cout << sample << endl;
        }
       
    }

    cout << "*** " << values.size();
    //string decodedString = "";

    //float temp;
    for (int i = 0 ; i < values.size(); i++) {

    	
		float t = values[i];
		
		

		char data[4];
		memcpy(data, &t, sizeof(t));
		char a = data[0];
		char b = data[1];
		char c = data[2];
		char d = data[3];




		

		//float temp
		
		//string ttt;
	

        //char dd []= {a, b, c, d}; 
		
		//memcpy(&temp, &dd, sizeof(temp));
		//values[i] = temp;
	/*	
		cout << t << endl;
		bitset<8> my_bset;
		my_bset=ToBits8(data[0]);
        ttt = my_bset.to_string();
        cout << ttt << " ";
        my_bset=ToBits8(data[1]);
        ttt = my_bset.to_string();
        cout << ttt << " ";
        my_bset=ToBits8(data[2]);
        ttt = my_bset.to_string();
        cout << ttt << " ";
        my_bset=ToBits8(data[3]);
        ttt = my_bset.to_string();
        cout << ttt << endl;
	
		data[0] = d;
		data[1] = c;
		data[2] = b;
		data[3] = a;

		my_bset=ToBits8(data[0]);
        ttt = my_bset.to_string();
        cout << ttt << " ";
        my_bset=ToBits8(data[1]);
        ttt = my_bset.to_string();
        cout << ttt << " ";
        my_bset=ToBits8(data[2]);
        ttt = my_bset.to_string();
        cout << ttt << " ";
        my_bset=ToBits8(data[3]);
        ttt = my_bset.to_string();
        cout << ttt << endl;
	
		my_bset=ToBits8(data[3]);
        ttt = my_bset.to_string();
        cout << ttt << endl;
        my_bset=ToBits8(data[2]);
        ttt = my_bset.to_string();
        cout << ttt << endl;
        my_bset=ToBits8(data[1]);
        ttt = my_bset.to_string();
        cout << ttt << endl;
        my_bset=ToBits8(data[0]);
        ttt = my_bset.to_string();
        cout << ttt << endl;

		
		
        float temp;
		memcpy(&temp, &data, sizeof(temp));
		cout << temp << endl;
*/
		//cout << values[i] << endl;// << "((((((((" << temp << endl;


		myfile << d;
		myfile << c;
		myfile << b;
		myfile << a;

    }

    myfile.close();



    


    //return decodedString;
    //return "sds";

}



int main(int argc, char** argv) 
{ 

/*
	ifstream inFile;
	inFile.open(argv[1]);
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	ofstream myfile;
	myfile.open (argv[2]);


	string inString((std::istreambuf_iterator<char>(inFile)),
                 std::istreambuf_iterator<char>());
	inFile.close();

*/

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

	//myfile << decoded;
	//myfile.close();

	return 0;







}