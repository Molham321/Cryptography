
#include<iostream>
#include "vigenereAndanalysis.h"

using namespace std;

void Vigenere(std::string key)
{
	string plainText;

	cout << "Type your first plain Text: ";
	cin >> plainText;

	string ciphertext = plainText;

	for (int i = 0; i < plainText.length(); i++)
	{
		ciphertext[i] = (((int)plainText[i] + (int)key[i % key.length()]) % 26) + 65;
	}

	cout << "ciphertext: " << ciphertext << endl;
	cout << "plainText: " << plainText << endl;
	cout << "Key: " << key << endl;

}

void Analysis(std::string chiffre)
{
	int alphabet[26] = { 0 };
	int offset = 65;

	for (int i = 0; i < chiffre.length(); i++)
	{
		if ((chiffre[i] - offset < 26) && (chiffre[i] - offset >= 0))
		{
			alphabet[chiffre[i] - offset] ++;
		}
	}

	for (int i = 0; i < 26; i++)
	{
		cout << (char)(i + offset) << " = " << alphabet[i] << endl;
	}


	float coincidenceIndex;
	int numberOfLetters = chiffre.length();

	float sum = 0;
	float sum2 = 0;


	for (int i = 0; i < 26; i++)
	{
		sum += alphabet[i] * (alphabet[i] - 1);
		sum2 += alphabet[i];
	}

	coincidenceIndex = sum / (sum2 * (sum2 - 1));

	cout << coincidenceIndex << endl;
}
