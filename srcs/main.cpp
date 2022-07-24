#include <string>
#include <iostream>

int main(int argc, char **argv)
{
	std::string str = "lol?puk";

	int symbolPosition = str.find('?');
	int offset = 0;
	std::string substr = str.substr(offset, symbolPosition - offset);
	offset = symbolPosition +1;
	std::cout << substr << std::endl;

	symbolPosition = str.find('\0');
	substr = str.substr(offset, symbolPosition - offset);
	std::cout << substr << std::endl;
}
