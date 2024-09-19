/*
UOW Student Name: Rohit Panda
UOW Student ID: 8943060
MAJ40164 - Digital Systems Security
CSCI251 - Advanced Programming
*/

// Comparation between two OS system. Program will choose the optimal path.
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// Declaration of Preprocessor directives:
#include "algorithms.h"

//Pause Program function can run on both window and unix:
void PauseProgram(int amount)
{
#ifdef WIN32
    Sleep(amount * 1000);
#define window
#else
    sleep(amount);
#define unix
#endif
}

/* Clear screen function can run on both window and unix */
void ClearScreen()
{
#ifdef WIN32
    system("cls");
#define window
#else
    system("clear");
#define unix
#endif
}

// Remove extra blank spaces
string RemoveSpace(string str)
{
    //reorders the elements in the range such that all elements that are not equal to the specified value:
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    //returns string:
    return str;
}

// Read in weather data from a file
vector<string> ReadDataFromFile(string name)
{

    fstream inputFile; // User given input file
    string lineByLine; // Gets data from input file, line by line.
    vector<string> result;
    cout << name << " ... "; //Reading File Name
    inputFile.open(name.c_str()); // Converts string object to a C-style string array (with a null-terminated character)

    // Implementing if..else statement to ensure file is open:
    if (inputFile.is_open())
    {
        // Reading from the file.

        while (inputFile)
        {
            getline(inputFile, lineByLine);
            if (lineByLine == "") // if line is a blank space
            {
                continue;
            }
            result.push_back(lineByLine);
        }
        // Outside of While Loop: Close File
        inputFile.close();
        cout << "done!" << endl;
    }
    else
    {

    }
    return result;
}
// Get data from a string with seperator (a/b/c to a b c)
vector<string> ProcessString(string input, string delimiter)
{
    size_t pos = 0; // holds the position of the delimiter found inside the input string
    string element; //  is a temp storage to hold the substring found
    vector<string> result;

    while ((pos = input.find(delimiter)) != string::npos)
    {
        element = input.substr(0, pos); /*Extracts the substring from the beginning of the input string up to (but not including)the position of the delimiter.*/
    result.push_back(element);                // Adds this substring to the result vector.
        input.erase(0, pos + delimiter.length()); // Removes the processed part of the input string, including the delimiter.
    }

    result.push_back(input);
    return (result);
}

// Convert a string to integer using sstream
int ConvertStringToInteger(string s)
{
    int x; // Helper variable
    stringstream ss;
    ss.clear(); // Good practice to clear any error flags that might be inside stringstream. Ensure stream is good before usage
    ss.str(s);
    ss >> x;  // Converts String to Integer automatically.
    return x; // int val
}

// Initializes a 2D array of strings (arr) with the given width and height. Each element in this array is initially set to a single space character " ":
void GenerateStringMap(string ** arr, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        arr[i] = new string[width]; // allocate an array of strings for each row
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = " "; // initialize each element to a single space
        }
    }
}
// Initializes a 2D array of integers (arr) with the given width and height. Each element in this array is initially set to character 0:
void GenerateIntegerMap(int **arr, int width, int height) //initializes a 2D array of strings with the specified width and height
{
    for (int i = 0; i < height; i++)
    {
        arr[i] = new int[width];// allocate an array of integers for each row
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = 0;// initialize each element to 0
        }
    }
}
// Get coordinate data inside bracket and removes characters ([0, 8] -> 0 8): 
string ProcessCoordinate(string str) {
	char chars[] = "[],"; //input: A string with coordinates in brackets (e.g., [0, 8])
   	for (unsigned int i = 0; i < sizeof(chars); ++i) {
      str.erase (std::remove(str.begin(), str.end(), chars[i]), str.end());
   	} 	
   	return str; //output: The string with brackets and commas removed (e.g., "0 8")
}

// displays a 2D array (map) on the screen with a border around thre processed coordinates.
void RenderMap(string **arr, int width, int height)
 { 
	string border = " ";
	for(int i=0; i< width + 2; i++) //the for loop constructs the top and bottom border by appending "# " to the border string width + 2 times to account for the left and right borders.
    {
		border += "#  "; // Prints out the border
	}
	
	cout <<" "<<"  "<< border << endl; // prints top border
	
	for (int i = 0; i < height; i++) //this for loop iterates through each row of the map.
    {
		cout<< setw(2) << height - i - 1 << "  " << "#" << "  "; //this print the row index (right-aligned to width 2), followed by the left border.
        for (int j = 0; j < width; j++) 
        {
            cout << arr[i][j] << "  "; //print each element with spacing
        }
        cout << "#"; //print right column border
        cout << endl;
    }
    cout << " " << "  " << border << endl;//print bottom border
    cout << setw(6) << " ";
    for(int i=0; i< width; i++) 
    {
    	cout << setw(2) << i << " ";//print column
	}
	cout << "\n" << endl;
}

// Wait for user to press enter:
void UserPressEnter()
{
    string state = "1";
    cout << "Press <Enter> button to go back to the main menu..." << endl;
    cin.ignore();
    do
    {
        getline(cin, state);
    } while (state.length() != 0);
}

// Safely Deallocate memory:
void DeleteStringMap(string **arr, int height)
{
    for (int i = 0; i < height; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

void DeleteIntMap(int **arr, int height)
{
    for (int i = 0; i < height; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

// To check city neighbour
string SurroundingCheck(string **map, int x, int y, int tableWidth, int tableHeight) {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) {
                continue;  // Skip the current position
            }
            //calculate new coordinates:
            int newX = x + dx;
            int newY = y + dy;

            // check boundaries and value:
            if (newX >= 0 && newX < tableWidth && newY >= 0 && newY < tableHeight) {
                const std::string& value = map[newX][newY];
                if (value != " ") {
                    return value;
                }
            }
        }
    }

    return "";
}



string ConvertToPressure(string val)
{
    string value;
    if (RemoveSpace(val).size() == 1)
    {
        value = "0";
    }
    else
    {
        value = val.substr(0, 1);
    }
    return value;
}

// Convert Data into Symbols
string ConvertToLMHSymbols(int val)
{
    string value;
    switch (val)
    {
    case 0 ... 34:
        value = "L";
        break;
    case 35 ... 64:
        value = "M";
        break;

    default:
        value = "H";
        break;
    }
    
    return value;
}
// To print out could index into screen
string ConvertToIndex(string val) {
	string value;
	if (RemoveSpace(val).size() == 1) {
		value = "0";
	} else {
		value = val.substr(0, 1);
	}
	return value;
}

