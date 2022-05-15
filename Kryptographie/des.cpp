#include<iostream>

#include "des.h"

using namespace std;

// Array to hold 16 keys
std::string g_roundKeys[16];
std::string g_roundExpansion[16];
std::string g_roundExpXorKey[16];
std::string g_roundSbox[16];
std::string g_roundPbox[16];

// String to hold the plain text
std::string g_initialInput;
std::string g_initialKey;
std::string g_initialInputPermuted;
std::string g_initialKeyPermuted;

std::string convertDecimalToBinary(int decimal)
{
	string binary;
	while (decimal != 0) {
		binary = (decimal % 2 == 0 ? "0" : "1") + binary;
		decimal = decimal / 2;
	}
	while (binary.length() < 4) {
		binary = "0" + binary;
	}
	return binary;
}

int convertBinaryToDecimal(std::string binary)
{
	int decimal = 0;
	int counter = 0;
	int size = binary.length();
	for (int i = size - 1; i >= 0; i--)
	{
		if (binary[i] == '1') {
			decimal += pow(2, counter);
		}
		counter++;
	}
	return decimal;
}

std::string shift_leftPermutationKey_once(std::string key_chunk)
{
	string shifted = "";
	for (int i = 1; i < 28; i++) {
		shifted += key_chunk[i];
	}
	shifted += key_chunk[0];
	return shifted;
}

std::string shift_leftPermutationKey_twice(std::string key_chunk)
{
	string shifted = "";
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j < 28; j++) {
			shifted += key_chunk[j];
		}
		shifted += key_chunk[0];
		key_chunk = shifted;
		shifted = "";
	}
	return key_chunk;
}

string Xor(string a, string b)
{
	string result = "";
	int size = b.size();
	for (int i = 0; i < size; i++) {
		if (a[i] != b[i]) {
			result += "1";
		}
		else {
			result += "0";
		}
	}
	return result;
}

void generate_keys(std::string _key)
{

	// The key Permutation table
	int keyPermutation[56] = {
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4
	};

	// The key Compression table
	int keyCompression[48] = {
	14,17,11,24,1,5,
	3,28,15,6,21,10,
	23,19,12,4,26,8,
	16,7,27,20,13,2,
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32
	};

	// ===========================================
	// ================ Aufgabe 3 ================
	// ===========================================

	// 1. Compressing the key using the key Permutation table
	for (int i = 0; i < 56; i++) {
		g_initialKeyPermuted += _key[keyPermutation[i] - 1];
	}

	// 2. Dividing the key into two equal halves
	string leftPermutationKey = g_initialKeyPermuted.substr(0, 28);
	string rightPermutationKey = g_initialKeyPermuted.substr(28, 28);

	for (int i = 0; i < 16; i++) {
		// 3.1. For rounds 1, 2, 9, 16 the key_chunks
		// are shifted by one.
		if (i == 0 || i == 1 || i == 8 || i == 15) {
			leftPermutationKey = shift_leftPermutationKey_once(leftPermutationKey);
			rightPermutationKey = shift_leftPermutationKey_once(rightPermutationKey);
		}
		// 3.2. For other rounds, the key_chunks
		// are shifted by two
		else {
			leftPermutationKey = shift_leftPermutationKey_twice(leftPermutationKey);
			rightPermutationKey = shift_leftPermutationKey_twice(rightPermutationKey);
		}
		// Combining the two chunks
		string combinedKey = leftPermutationKey + rightPermutationKey;
		string roundKey = "";
		// Finally, using the key Compression table to transpose the key bits
		for (int i = 0; i < 48; i++) {
			roundKey += combinedKey[keyCompression[i] - 1];
		}
		g_roundKeys[i] = roundKey;
	}

	// ===========================================
	// ================ Ende Aufgabe 3 ===========
	// ===========================================

}

std::string DES()
{
	// The initial permutation table 
	int initialPermutationTable[64] = {
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
	};

	// The expansion table
	int expansionMatrix[48] = {	// expansionMatrix error
	32,1,2,3,4,5,4,5,
	6,7,8,9,8,9,10,11,
	12,13,12,13,14,15,16,17,
	16,17,18,19,20,21,20,21,
	22,23,24,25,24,25,26,27,
	28,29,28,29,30,31,32,1
	};

	// The substitution boxes. The should contain values
	// from 0 to 15 in any order.
	int substitionBoxes[8][4][16] =
	{ {
		14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
		0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
		4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
		15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
	},
	{
		15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
		3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
		0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
		13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
	},
	{
		10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
		13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
		13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
		1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
	},
	{
		7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
		13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
		10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
		3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
	},
	{
		2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
		14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
		4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
		11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
	},
	{
		12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
		10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
		9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
		4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
	},
	{
		4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
		13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
		1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
		6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
	},
	{
		13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
		1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
		7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
		2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
	} };

	// The permutation table
	int pBoxPermutation[32] = {
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25
	};

	// The inverse permutation table
	int finalPermutation[64] = {
	40,8,48,16,56,24,64,32,
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41,9,49,17,57,25
	};

	// =============================================
	// ================= Aufgabe 1 =================
	// =============================================

	//1. Applying the initial permutation
	for (int i = 0; i < 64; i++)
	{
		g_initialInputPermuted += g_initialInput[initialPermutationTable[i] - 1];
	}

	// 2. Dividing the result into two equal halves 
	string leftPermutationInput = g_initialInputPermuted.substr(0, 32);
	string rightPermutationInput = g_initialInputPermuted.substr(32, 32);

	// =============================================
	// ================= Ende Aufgabe 1 ============
	// =============================================

	// =============================================
	// ================= Aufgabe 2 =================
	// =============================================

	// The plain text is encryg_initialInputed 16 times  
	for (int i = 0; i < 16; i++)
	{
		string rightPermutationKey_expanded = "";
		// 3.1. The rightPermutationKey half of the plain text is expanded
		for (int i = 0; i < 48; i++)
		{
			rightPermutationKey_expanded += rightPermutationInput[expansionMatrix[i] - 1];
		};

		g_roundExpansion[i] = rightPermutationKey_expanded;

		// =============================================
		// ================= End Aufgabe 2 =============
		// =============================================

		// =============================================
		// ================= Aufgabe 4 =============
		// =============================================

		// 3.3. The result is xored with a key
		string xored = Xor(g_roundKeys[i], rightPermutationKey_expanded);
		string res = "";

		g_roundExpXorKey[i] = xored;

		// 3.4. The result is divided into 8 equal parts and passed 
		// through 8 substitution boxes. After passing through a 
		// substituion box, each box is reduces from 6 to 4 bits.
		for (int i = 0; i < 8; i++) {
			// Finding row and column indices to lookup the
			// substituition box
			string row1 = xored.substr(i * 6, 1) + xored.substr(i * 6 + 5, 1);
			int row = convertBinaryToDecimal(row1);
			string col1 = xored.substr(i * 6 + 1, 1) + xored.substr(i * 6 + 2, 1) + xored.substr(i * 6 + 3, 1) + xored.substr(i * 6 + 4, 1);;
			int col = convertBinaryToDecimal(col1);
			int val = substitionBoxes[i][row][col];
			res += convertDecimalToBinary(val);
		}

		g_roundSbox[i] = res;
		// 3.5. Another permutation is applied
		string pBox = "";
		for (int i = 0; i < 32; i++)
		{
			pBox += res[pBoxPermutation[i] - 1];
		}

		g_roundPbox[i] = pBox;

		// 3.6. The result is xored with the leftPermutationKey half
		xored = Xor(pBox, leftPermutationInput);

		// 3.7. The leftPermutationKey and the rightPermutationKey parts of the plain text are swapped 
		leftPermutationInput = xored;
		if (i < 15) {
			string temp = rightPermutationInput;
			rightPermutationInput = xored;
			leftPermutationInput = temp;
		}
	}

	// 4. The halves of the plain text are applied
	string combined_text = leftPermutationInput + rightPermutationInput;
	string ciphertext = "";

	// The inverse of the initial permuttaion is applied
	for (int i = 0; i < 64; i++) {
		ciphertext += combined_text[finalPermutation[i] - 1];
	}
	//And we finally get the cipher text
	return ciphertext;

	// =============================================
	// ================= End Aufgabe 4 =============
	// =============================================
}

void output()
{
	// A 64 bit key
	g_initialKey = "0001001100110100010101110111100110011011101111001101111111110001";
	// A block of plain text of 64 bits
	g_initialInput = "0000000100100011010001010110011110001001101010111100110111101111";
	// Calling the function to generate 16 keys
	generate_keys(g_initialKey);

	// Applying the algo
	string ciphertext = DES();

	cout << "initial input: " << g_initialInput << endl;
	cout << "initial key: " << g_initialKey << endl;
	cout << endl;
	cout << "initial input permuted: " << g_initialInputPermuted << endl;
	cout << "initial key permuted: " << g_initialKeyPermuted << endl;
	cout << endl;

	for (int i = 0; i < 16; i++)
	{
		cout << "Round " << i + 1 << endl;
		cout << "Key:         48: " << g_roundKeys[i] << endl;
		cout << "expansion:   48: " << g_roundExpansion[i] << endl;
		cout << "exp xor key: 48: " << g_roundExpXorKey[i] << endl;
		cout << "sBox:        32: " << g_roundSbox[i] << endl;
		cout << "pBox:        32: " << g_roundPbox[i] << endl;
		cout << endl;
	}
	cout << "------------------------------------" << endl;
	cout << "Ergebnis: 64: " << ciphertext << endl;
}
