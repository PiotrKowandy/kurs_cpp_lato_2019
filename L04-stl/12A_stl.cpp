#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <algorithm>

void fillMap(std::map<char, int>& myMap, std::string& myString)
{
	myMap.clear();
	std::for_each(myString.begin(), myString.end(), [&](char el)
					{
						myMap.insert(myMap.begin(),std::pair<char,int>(el, int(el)));
					}
			 		);
}


std::string encrypt(std::map<char, int>& myMap, int key, std::string& secretString)
{	
	fillMap(myMap, secretString);
	std::string secret = "";

	std::for_each(myMap.begin(), myMap.end(), [&](auto& el)
					{
						secret += char( el.second + key );
					} 
					);

	secretString = secret;
	return secret;
}


std::string decrypt(std::map<char, int>& myMap, int key, std::string& secretString)
{
	key *= -1;
	return encrypt(myMap, key, secretString);
}


int main ()
{
	srand(time(NULL));
	int key = (rand()%10)+1;

	std::string secretString="";
	std::ifstream myFile ("toEncrypt.txt");
	if (myFile.is_open())
	{
		getline(myFile, secretString);
		myFile.close();
	}
	else
	{
		std::cout<< "I'm unable open this file." <<std::endl;
	}

	std::map<char, int> myMap;

	std::cout<< "Orignal sentence: " << secretString << std::endl;
	std::cout<< "Sentense after encryption: " << encrypt(myMap, key, secretString) << std::endl;

	std::ofstream myFileDe ("decrypt.txt");
	if (myFileDe.is_open())
	{
		myFileDe << secretString << std::endl;
	}
	else
	{
		std::cout<< "There is a problem with file, i can't write into." << std::endl;
	}

	std::cout<< "Sentense after decryption: " << decrypt(myMap, key, secretString) << std::endl;
	
	return 0;
}
