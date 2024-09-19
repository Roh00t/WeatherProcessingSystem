/*
UOW Student Name: Rohit Panda
UOW Student ID: 8943060
MAJ40164 - Digital Systems Security
CSCI251 - Advanced Programming
*/

// this code ensures that it can use the correct system-specific functions:
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// Declaration of Preprocessor directives:
#include "DisplayUserMenu.h"
#include "algorithms.h"
#include "city_mapping.h"
#include "cloud_mapping.h"
#include "pressure_mapping.h"
#include "weather_report.h"

// Declare Global Variables
string student_ID = "8943060";
string student_Name = "Rohit Panda";
string divider = "======================================";

bool userInputFile = false;
vector<string> fileInformation;
string user_file_inside;

// For City Mapping:
string ** city_map;
vector<string> raw_city_data;
vector<string> raw_name_data;
vector<string> raw_id_data;

// For Cloud Mapping:
string ** cloud_map;
string ** cloud_converted;
vector<string> raw_cloud_data;
int ** cloud_original;

// For Pressure Mapping:
string ** pressure_map;
string ** pressure_converted;
vector<string> raw_pressure_data;
int ** pressure_orginal;

// For Weather Report:
vector<City_report> alist;
int height;
int width;

// Display User Menu:

int DisplayUserMenu()
{
    string userChoice;
    while (true)
    {
        cout << divider << '\n';
        cout << "Student ID: " << student_ID << '\n';
        cout << "Student ID: " << student_Name << '\n';
        cout << divider << '\n';

        //if user did not give configuration file:
        cout << "Welcome to Weather Information Processing System!\n"
             << '\n';
        cout << "1)\tRead in and process a configuration file" << '\n';

        //if user gave the configuration file:
        if (userInputFile)
        {
            cout << "2)\tDisplay city map" << endl;
            cout << "3)\tDisplay cloud coverage map (cloudiness index)" << endl;
            cout << "4)\tDisplay cloud coverage map (LMH symbols)" << endl;
            cout << "5)\tDisplay atmospheric pressure map (pressure index)" << endl;
            cout << "6)\tDisplay atmospheric pressure map (LMH symbols index)" << endl;
            cout << "7)\tShow weather forecast summary report" << endl;
        }
        cout << "8)\tQuit\n"
             << endl;
        cout << "Please enter your choice: ";
        while (userChoice == "") //loop continously until user type in choice.
        {
            cin >> userChoice; // get the user's choice
        }

        // Process the file given by user:
        userChoice = RemoveSpace(userChoice); //take in the user's choice, get the first integer, remove spaces, clean the input
        bool result = PromptUser(userChoice); // based on user's choice, pass the integer to PromptUser function which maps the corresponding choice to the elements

        // if user quits program(Option 8):
        if (result)
            break;
        userChoice = ""; //user's choice becomes empty again
    }

    return 0;
}

// Implement the logic of the userChoice and react accordingly:
bool PromptUser(string userChoice)
{
    // implementation of PromptUser
    if (userChoice == "1")
    {
        // Initialize and Process Data:
        // Read config file provided by user:
        ReadConfigFile();

        // Allocate Memory:
        SafelyAllocateMemory();

        // Pre-process data:
        CityElement(height, width, city_map, raw_city_data, raw_name_data, raw_id_data);
        CloudElement(height, width,cloud_map, raw_cloud_data, cloud_original, cloud_converted);
        PressureElement(height, width, raw_pressure_data, pressure_map, pressure_converted, pressure_orginal);
        alist.clear(); // clear the buffer after all Elements have been initialized

        //Processing Weather Data:
        WeatherReportData(height, width, raw_name_data, raw_id_data, city_map, cloud_map, pressure_map, pressure_orginal, cloud_original, alist);
	    return false;
    }
    else if ((userChoice == "2") && (userInputFile))
    {
		ClearScreen(); // equivilent to user typing 'clear' to clear the screen. 
		cout << endl;
		cout << "[Display city map]\n" << endl; 

		//Display city map:
		RenderMap(city_map, width, height);
		UserPressEnter(); // waiting for user input
		ClearScreen(); //clears the screen and User Menu gets displayed
    return false;
    }

    else if ((userChoice == "3") && (userInputFile))
    {
		ClearScreen();
		cout << endl;
		cout << "[Display cloud coverage map (cloudiness index)]\n" << endl;

		//Display cloud map (cloud index):
		RenderMap(cloud_map, width, height);
		UserPressEnter();
		ClearScreen();
    return false;
    }

    else if ((userChoice == "4") && (userInputFile))
    {
		ClearScreen();
		cout << endl;
		cout << "[Display cloud coverage map (LMH symbols)]\n" << endl;

		//Display cloud map (LMH format):
		RenderMap(cloud_converted, width, height);
		UserPressEnter();
		ClearScreen();
    return false;
    }

    else if ((userChoice == "5") && (userInputFile))
    {
		ClearScreen();
		cout << endl;
		cout << "[Display atmospheric pressure map (pressure index)]\n" << endl;

		//Display pressure map (pressure index):
		RenderMap(pressure_map, width, height);
		UserPressEnter();
		ClearScreen();
    return false;
    }

    else if ((userChoice == "6") && (userInputFile))
    {
		ClearScreen();
		cout << endl;
		cout << "[Display atmospheric pressure map (LMH symbols index)]\n" << endl;

		//Display pressure map (LMH format):
		RenderMap(pressure_converted, width, height);
		UserPressEnter();
		ClearScreen();
    return false;
    }

    else if ((userChoice == "7") && (userInputFile))
    {
		ClearScreen();
		cout << endl;
		cout << "Weather Forecast Summary Report" << endl;
		cout << "-------------------------------" << endl;

		//Display weather forecase report:
		WeatherReport(alist);
		UserPressEnter();
		ClearScreen();
	return false;
    }

    else if (userChoice == "8")
    {
        cout << "[Quiting...]";
        cout << endl;

        // Safely Deallocate memory
        SafelyDeallocateMemory();
        PauseProgram(1);
        ClearScreen();
        
        // Signal Program to terminate
        return true;
    }
    else
    {
        cout << endl;
        ClearScreen();
        return false;
    }
}

void ReadConfigFile()
{
    // implementation of ReadConfigFile

    // User Input and File Opening:
    fstream inputFile;
    string aLine;
    vector<string> v;
    cout << endl;

    cout << "[Read in and process a configuration file]" << endl;
    cout << "Please enter config file name: ";
    cin >> user_file_inside; //get configuration file
    inputFile.open(user_file_inside.c_str()); // read and store all contents of the configuration file
    cout << endl;
    fileInformation.clear();

    // Extracting data from config file provided by user:

    // Error Handling:
    if (!inputFile)
    {
        cout << "Error when reading input file" << endl;
        cout << endl;
    }
    else
    {
        // Reading File Contents:
        while (inputFile)
        {
            getline(inputFile, aLine);
            if (aLine[0] == '/')
                continue;
            if (aLine == "")
                continue;
            fileInformation.push_back(aLine);
        }
        inputFile.close();

        // Processing Configuration Data:
        cout << "Reading in " << fileInformation[0] << " " << "...";
        cout << " done!" << endl;
        cout << "Reading in " << fileInformation[1] << " " << "...";
        cout << " done!" << endl;
        cout << endl;
        cout << "Storing data from input file :" << endl;

        v = ProcessString(fileInformation[0], "-");
        width = ConvertStringToInteger(v[1]);
        v = ProcessString(fileInformation[1], "-");
        height = ConvertStringToInteger(v[1]);
        width++;
        height++;

        // Read other text files:
        // Reading Additional Data Files:
        raw_city_data = ReadDataFromFile(fileInformation[2]);
        raw_cloud_data = ReadDataFromFile(fileInformation[3]);
        raw_pressure_data = ReadDataFromFile(fileInformation[4]);
        cout << endl;

        // User Feedback and State Update:
        cout << "All records successfully stored. Going back to main menu ... " << endl;
        if (!userInputFile)
            userInputFile = true;
        cout << endl;
    }
    // The PauseProgram(2) function pauses execution for 2 seconds:
    PauseProgram(2);

    // ClearScreen() clears the console screen:
    ClearScreen();
}

void SafelyAllocateMemory()
{
    // implementation of SafelyAllocateMemory

    // For City Mapping:
    city_map = new string * [height];
    GenerateStringMap(city_map, width, height);

    // For Cloud Mapping:
    cloud_map = new string * [height];
    cloud_converted = new string * [height];
    cloud_original = new int * [height];

    GenerateStringMap(cloud_map, width, height);
    GenerateStringMap(cloud_converted, width, height);
    GenerateIntegerMap(cloud_original, width, height);

    // For Pressure Mapping:
    pressure_map = new string * [height];
    pressure_converted = new string * [height];
    pressure_orginal = new int * [height];

    GenerateStringMap(pressure_map, width, height);
    GenerateStringMap(pressure_converted, width, height);
    GenerateIntegerMap(pressure_orginal, width, height);
}

// Safely deallocate using delete:
void SafelyDeallocateMemory()
{
    // implementation of SafelyDeallocateMemory
    // Delete City:
    DeleteStringMap(city_map, height);

    // Delete Cloud:
    DeleteStringMap(cloud_map, height);
    DeleteStringMap(cloud_converted, height);
    DeleteIntMap(cloud_original, height);

    // Delete Pressure:
    DeleteStringMap(pressure_map, height);
    DeleteStringMap(pressure_converted, height);
    DeleteIntMap(pressure_orginal, height);

}