//The Cherno on Youtube
#include <iostream>
#define LOG(x) stf::cout << x << std::endl
void Log(const char* message); //declaration of Log function
void Increment(int* value);

int main() {

	//function
	std::cout << "Hello World!" << std::endl;
	Log("Hello World!!");
	
	//loop
	for (int i = 0; i < 5; i++) {
		std::cout << i << std::endl;
	}

	//pointer
	int var = 8;
	void* ptr = &var;
	std::cout << "memory address of 8 is: " ;
	std::cout << ptr << std::endl;

	//setting 8 bytes of memory
	char* buffer = new char[8];
	memset(buffer, 0, 8);// 8 bytel�k 0 de�erleri tutar.
	char** ptr2 = &buffer; //buffer pointer�n�n adresini tutar.
	
	delete[] buffer; //bellekte ay�r�lan yer silinir.

	//references in CPP
	int a = 5;
	int b = 8;

	int* ref = &a;
	*ref = 2;
	ref = &b;
	*ref = 1;
	//Increment(&a); yerine yukar�daki kod yaz�labilir
	std::cout << a << std::endl;
	std::cout << b << std::endl;


	std::cin.get();
}

void Increment(int* value) {

	(*value)++;
}