#pragma once

#include<string>

// Function to convert a number in decimal to binary
std::string convertDecimalToBinary(int decimal);

// Function to convert a number in binary to decimal
int convertBinaryToDecimal(std::string binary);

// Function to do a circular leftPermutationKey shift by 1
std::string shift_leftPermutationKey_once(std::string key_chunk);

// Function to do a circular leftPermutationKey shift by 2
std::string shift_leftPermutationKey_twice(std::string key_chunk);

// Function to compute xor between two strings
std::string Xor(std::string a, std::string b);

// Function to generate the 16 keys.
void generate_keys(std::string _key);

// Implementing the algorithm
std::string DES();

//output
void output();