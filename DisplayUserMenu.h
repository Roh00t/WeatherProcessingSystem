/*
UOW Student Name: Rohit Panda
UOW Student ID: 8943060
MAJ40164 - Digital Systems Security
CSCI251 - Advanced Programming
*/

//Declaration of header guards
#ifndef DISPLAY_USER_MENU_H
#define DISPLAY_USER_MENU_H


// Declaration of the standard c++ Preprocessor directives:
#include <iostream>
#include<string>
// Preprocessor directives for file read input and output:
#include <fstream>
using namespace std;

int DisplayUserMenu(); // Displays the program menu
bool PromptUser(string userChoice); // Prompt and stores user's choice
void ReadConfigFile(); // Read the file given by the user
void SafelyAllocateMemory(); // Memory management
void SafelyDeallocateMemory(); // Freeing up memory because program exit.



#endif