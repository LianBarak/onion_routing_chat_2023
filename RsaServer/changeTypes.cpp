#pragma once
#include <iostream>
#include <string>

std::string unsignedCharToString(unsigned char* data)
{
	int len = 0;

	std::string myString = "";
	for (int x = 0; x < len - 1; x++)
	{
		myString = myString + std::to_string(char(data[x]));
	}
	return myString;

}

unsigned char* stringToUnsignedChar(std::string data)
{
	int len = 0;
	unsigned char myUnsignedChar[sizeof(data)];
	std::copy(data.begin(), data.end(), myUnsignedChar);
	return myUnsignedChar;
}

