#include <iostream> 
#include <iomanip>
#include <fstream>
#include <map>
#include <cstring>
#include <bitset>
#include <string>


#include <math.h>
#include <vector>
using namespace std; 



void Encode(char* inString, size_t length, string fileName) 
{

	std::map<int,string> binarySteps;
  	binarySteps[-8] = "1111";
  	binarySteps[-7] = "1110";
  	binarySteps[-6] = "1101";
  	binarySteps[-5] = "1100";
  	binarySteps[-4] = "1011";
  	binarySteps[-3] = "1010";
  	binarySteps[-2] = "1001";
  	binarySteps[-1] = "0000";
  	binarySteps[1] = "0001";
  	binarySteps[2] = "0010";
  	binarySteps[3] = "0011";
  	binarySteps[4] = "0100";
  	binarySteps[5] = "0101";
  	binarySteps[6] = "0110";
  	binarySteps[7] = "0111";

  	std::map<int,string> binaryRange;
  	binaryRange[0] = "0000";
  	binaryRange[1] = "0001";
  	binaryRange[2] = "0010";
  	binaryRange[3] = "0011";
  	binaryRange[4] = "0100";
  	binaryRange[5] = "0101";
  	binaryRange[6] = "0110";
  	binaryRange[7] = "0111";
  	binaryRange[8] = "1000";
  	binaryRange[9] = "1001";
  	binaryRange[10] = "1010";
  	binaryRange[11] = "1011";
  	binaryRange[12] = "1100";
  


  	ofstream myfile;
	myfile.open (fileName);


	float temp;
	vector<short int> values = {};
	for (int i = 0; i < length; i++) {  
        char a = *(inString + i);
        i++;
        char b = *(inString + i);
        i++;
		char c = *(inString + i);
		i++;
		char d = *(inString + i);

		char reversed [] = {d, c, b, a};
		memcpy(&temp, &reversed, sizeof(temp));

		temp = temp * pow(10, 12);
		short int si = (short int)temp;
		values.push_back(si);
		//cout << temp << endl;
		
    }     
    cout << length << "-----" << values.size() << endl;

    vector<short int> scales = {};
    for(int i = 0; i < values.size(); i++) {
    	short int high = 0;
    	short int low = 0;
    	for(int j = 0; j < 16; j++) {
    		if(i >= values.size()){
    			break;
    		}
    		if(values[i] < low){
    			low = values[i];
    		}
    		if(values[i] > high){
    			high = values[i];
    		}
    		i++;
    	}
    	i--;

    	//cout << "===" << i << "===" << high << "===" << low << endl;
    	short int lowScale;
    	if(low / 1.0 >= -8.0){
    		lowScale = 0;
    	}else if(low / 2.0 >= -8.0){
    		lowScale = 1;
    	}else if(low / 4.0 >= -8.0){
    		lowScale = 2;
    	}else if(low / 8.0 >= -8.0){
    		lowScale = 3;
    	}else if(low / 16.0 >= -8.0){
    		lowScale = 4;
    	}else if(low / 32.0 >= -8.0){
    		lowScale = 5;
    	}else if(low / 64.0 >= -8.0){
    		lowScale = 6;
    	}else if(low / 128.0 >= -8.0){
    		lowScale = 7;
    	}else if(low / 256.0 >= -8.0){
    		lowScale = 8;
    	}else if(low / 512.0 >= -8.0){
    		lowScale = 9;
    	}else if(low / 1024.0 >= -8.0){
    		lowScale = 10;
    	}else if(low / 2048.0 >= -8.0){
    		lowScale = 11;
    	}else if(low / 4096.0 >= -8.0){
    		lowScale = 12;
    	}

    	short int highScale;
    	if(high / 1.0 <= 7.0){
    		highScale = 0;
    	}else if(high / 2.0 <= 7.0){
    		highScale = 1;
    	}else if(high / 4.0 <= 7.0){
    		highScale = 2;
    	}else if(high / 8.0 <= 7.0){
    		highScale = 3;
    	}else if(high / 16.0 <= 7.0){
    		highScale = 4;
    	}else if(high / 32.0 <= 7.0){
    		highScale = 5;
    	}else if(high / 64.0 <= 7.0){
    		highScale = 6;
    	}else if(high / 128.0 <= 7.0){
    		highScale = 7;
    	}else if(high / 256.0 <= 7.0){
    		highScale = 8;
    	}else if(high / 512.0 <= 7.0){
    		highScale = 9;
    	}else if(high / 1024.0 <= 7.0){
    		highScale = 10;
    	}else if(high / 2048.0 <= 7.0){
    		highScale = 11;
    	}else if(high / 4096.0 <= 7.0){
    		highScale = 12;
    	}

    	if(highScale > lowScale){
    		scales.push_back(highScale);
    	}else{ 
    		scales.push_back(lowScale);
    	}
    }

    
    for(int i = 0; i < 20; i++) {
    	cout << "&&&& " << scales[i] << endl;
    }
    cout << "-----[[[[[---" << scales.size() << endl;

	int sampleRoundCount = 0;
	float stepSize;
	int sampleCount;
	vector<short int> encodedValues = {};
    for(int i = 0; i < values.size(); i++) {
    	sampleCount = 0;
    	stepSize = pow(2, scales[sampleRoundCount]);
    	while (sampleCount < 16) {
    		if(i >= values.size())
    			break;
    		short int temp;
    		if(values[i] > 0) {
    			temp = (short int)(((float)values[i] / (float)stepSize) + 0.5);
    			if(temp == 0)
    				temp = 1;
    		} else {
    			temp = (short int)(((float)values[i] / (float)stepSize) - 0.5);
    			if(temp == 0)
    				temp = -1;
    		}
    		
    		encodedValues.push_back(temp);
    		i++;
    		sampleCount++;
    	}
    	i--;
    	sampleRoundCount++; 
    }


    for(int i = 0; i < 90; i++) {
    	cout << i << "^^^" <<  encodedValues[i] << endl;
    }

    cout << "----[[[-" << encodedValues.size() << endl;
    cout << encodedValues[3400000] << endl;


    //string encodedString  = "";
    //char* encodedString = new char[encodedValues.size() + (encodedValues.size()/16) + 100];
    int encodedIter = 0;
    
    unsigned long ulong;
	unsigned char uchar;
    int headerCount = 0;
    std::map<int,string>::iterator it;
    for(int i = 0; i < encodedValues.size(); i++) {
    	string headerString = "";
    	it = binaryRange.find(scales[headerCount]);
    	headerString = it->second;
    	headerString += "0000";
    	std::bitset<8> bit_set(headerString, 0, headerString.size(), '0', '1'); 
		ulong = bit_set.to_ulong(); 
		uchar = static_cast<unsigned char>(ulong);
		myfile << uchar;
		//encodedString[encodedIter++] = uchar;

		string byte = "";
		for(int j = 0; j < 8; j++) {
			if(i %100000 == 0)
				cout << i << endl;
			
			if(i >= encodedValues.size()){
				break;
			}
			it = binarySteps.find(encodedValues[i]);
			if (it != binarySteps.end()){
				byte = it->second;
    		} else {
    			byte = "0000";
    		}
    		
    		i++;
    		
			if(i >= encodedValues.size()){
				byte += "0000";
				
			} else {
				it = binarySteps.find(encodedValues[i]);
				if (it != binarySteps.end()){
					byte += it->second;
	    		} else {
	    			byte += "0000";
	    		}
			}
			
			std::bitset<8> bit_set(byte, 0, byte.size(), '0', '1'); 
			ulong = bit_set.to_ulong(); 
			uchar = static_cast<unsigned char>(ulong);
			
			myfile << uchar;
			i++;
		} 
		i--;
		
    	headerCount++;
    }

   	//cout << "sadads    " << encodedString.size();
    //return encodedString;
    myfile.close();
   


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

	


	string inString((std::istreambuf_iterator<char>(inFile)),
                 std::istreambuf_iterator<char>());
	inFile.close();
*///myfile.open (argv[2]);
	



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


	

	Encode(oData, size, argv[2]);

	//myfile << encoded;
	//myfile.close();

	return 0;

}