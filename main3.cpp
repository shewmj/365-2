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





bitset<8> ToBits8(unsigned char byte)
{
    return bitset<8>(byte);
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
*/
	

    ifstream inFile; 
	size_t size = 0;
	inFile.open(argv[1], ios::in|ios::binary);
	char* oData = 0;
	if(inFile.is_open()) {

	
		cout << "hi" << endl;
		inFile.seekg(0, ios::end);
		size = inFile.tellg();
		inFile.seekg(0, ios::beg);

		oData = new char[size+1];
		inFile.read(oData, size);
		oData[size] = '\0';
	}



	float temp;
	int count = 1;
	for (int i = 0; i < size; i++) {  
        char a = *(oData + i);
        i++;
        char b = *(oData + i);
        i++;
		char c = *(oData + i);
		i++;
		char d = *(oData + i);

		char normal [] = {d, c, b, a};
		memcpy(&temp, &normal, sizeof(temp));

		//temp = temp * pow(10, 11);
		//short int si = (short int)temp;
		//values.push_back(si);
		
		cout << count++ << "    " << temp << endl;
		bitset<8> bs;
		bs = ToBits8(d);
		cout << bs.to_string() << " ";
		bs = ToBits8(c);
		cout << bs.to_string() << " ";
		bs = ToBits8(b);
		cout << bs.to_string() << " ";
		bs = ToBits8(a);
		cout << bs.to_string() << endl;
		
    }     

/*	

	for (int i = 0; i < size; i++) {  
		if(i%4== 0) {
			cout << endl;
		}
        char a = *(oData + i);
        bitset<8> temp = ToBits8(a);

		
		cout << temp.to_string() << " ";

		
    }     
*/
/*
	for (int i = 0; i < size; i++) {  
		
        char a = *(oData + i);
        bitset<8> temp = ToBits8(a);

		
		cout << temp.to_string() << endl;

		
    }     

*/


}