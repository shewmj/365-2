#include <iostream> 
#include <iomanip>
#include <fstream>
#include <map>
#include <cstring>
#include <bitset>
#include <string>
#include <cmath>
#include <limits>

#include <math.h>
#include <vector>
using namespace std; 



	




int main(int argc, char** argv) 
{ 


	//read file1
	ifstream inFile; 
	size_t size = 0;
	inFile.open(argv[1], ios::in|ios::binary);
	char* oData = 0;
	if(inFile.is_open()) {



		inFile.seekg(0, ios::end);
		size = inFile.tellg();
		inFile.seekg(0, ios::beg);

		oData = new char[size+1];
		inFile.read(oData, size);
		oData[size] = '\0';
	}

	//read file2
	ifstream inFile2; 
	size_t size2 = 0;
	inFile2.open(argv[2], ios::in|ios::binary);
	char* oData2 = 0;
	if(inFile2.is_open()) {

		inFile2.seekg(0, ios::end);
		size2 = inFile2.tellg();
		inFile2.seekg(0, ios::beg);

		oData2 = new char[size2+1];
		inFile2.read(oData2, size2);
		oData2[size2] = '\0';
	}

	
	//reverse bytes and take difference between 32 bit float values
	float MSE = 0;
	float flo1;
	float flo2;
	short int short1;
	short int short2;
	float diff;
	int j = 0;
	for (int i = 0; i < size; i++) {  
        char a = *(oData + i);
        i++;
        char b = *(oData + i);
        i++;
		char c = *(oData + i);
		i++;
		char d = *(oData + i);

		char reversed [] = {d, c, b, a};
		memcpy(&flo1, &reversed, sizeof(flo1));
		flo1 = flo1 * pow(10, 12);
		short1 = (short int)flo1;
		

		a = *(oData2 + j);
        j++;
        b = *(oData2 + j);
        j++;
		c = *(oData2 + j);
		j++;
		d = *(oData2 + j);
		j++;

		char reversed2 []= {d, c, b, a};
		memcpy(&flo2, &reversed2, sizeof(flo2));
		flo2 = flo2 * pow(10, 12);
		short2 = (short int)flo2;
		


		diff = pow(short1 - short2, 2);
		
		MSE += diff;
		
		//cout << temp1 << "       " << temp2 << "    " << tt << endl;
		
    }     


    
    MSE = MSE / (size / 4);

    float MAX = 32767 * 2;


    

    float psnr = (20 * log10(MAX)) - (10 * log10(MSE)); 
    cout << "psnr: " << psnr << endl;


	 

}