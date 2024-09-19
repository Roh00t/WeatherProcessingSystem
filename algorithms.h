/*
UOW Student Name: Rohit Panda
UOW Student ID: 8943060
MAJ40164 - Digital Systems Security
CSCI251 - Advanced Programming
*/

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
using namespace std;


vector <string> ReadDataFromFile(string name); // Reading of txt file
vector <string> ProcessString(string input, string delimiter); // Extracting data from text files

string ProcessCoordinate(string str); // processing and plotting x and y coordinates
string RemoveSpace(string str); // Remove spaces between the numbers
string SurroundingCheck(string ** map, int x, int y, int tableWidth, int tableHeight); // For the city map, check city's surroundings
string ConvertToLMHSymbols(int val); // converting cloud and pressure index into symbols
string ConvertToPressure(string val); // Extracting data from pressure text file
string ConvertToIndex(string val);// Extracting data from cloud and pressure text file and converting them to indexes
int ConvertStringToInteger(string s); // Converting a string to integer using sstream


void GenerateStringMap(string ** arr, int width, int height); 
void GenerateIntegerMap(int** arr, int width, int height);
void RenderMap(string** arr, int width, int height);

void UserPressEnter(); //Freezes screen and waiting for user to press enter

// Deallocate and free up memory:
void DeleteStringMap(string** arr, int height);
void DeleteIntMap(int** arr, int height);

void PauseProgram(int amount); //Pauses the program for amount of seconds
void ClearScreen(); // Clears the screen.


#endif