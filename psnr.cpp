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

	/*
	for (int i = 0; i < size; i++) {  

		char a = *(oData + i);
		bitset<8> temp = ToBits8(a);


	cout << temp.to_string() << endl;


	}     
	*/
	float MSE = 0;
	float temp1;
	float temp2;
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
		memcpy(&temp1, &reversed, sizeof(temp1));

		a = *(oData2 + j);
        j++;
        b = *(oData2 + j);
        j++;
		c = *(oData2 + j);
		j++;
		d = *(oData2 + j);
		j++;

		char reversed2 []= {d, c, b, a};
		memcpy(&temp2, &reversed2, sizeof(temp2));


		float tt = pow(temp1 - temp2, 2);

		MSE += tt;
		
		//cout << temp1 << "       " << temp2 << "    " << tt << endl;
		
    }     



    MSE = MSE / (size / 4);

    double MAX = std::numeric_limits<float>::max() * 2;

    cout << MAX << endl;

    float psnr = (20 * log10(MAX)) - (10 * log10(MSE)); 
    cout << "psnr: " << psnr << "    " << (20 * log10(MAX)) << "    " << (10 * log10(MSE)) << endl;


    cout << MAX << endl;
    cout << MSE << endl;
    
	 

}