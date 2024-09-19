/*
UOW Student Name: Rohit Panda
UOW Student ID: 8943060
MAJ40164 - Digital Systems Security
CSCI251 - Advanced Programming
*/


#include "pressure_mapping.h"
#include "algorithms.h"

void PressureElement(int height, int width, vector<string> &raw_pressure, string **&pressure_map, string **&pressure_converted, int **&pressure_orginal)
{
    // Declaration of variables
    string s;                  // store processed coordinate string
    vector<string> coordinate; /// store the split coordinates
    vector<string> v;          // store the split raw city data
    int x;                     // store the x coordinate
    int y;                     // store the y coordinate

    // Extraction of data: Data Extraction for loop:
    for (int i = 0; i < raw_pressure.size(); i++) //Iterates through eaxh element in the vector
    {
        v = ProcessString(raw_pressure[i], "-"); // Splitting the raw data using delimiter "-" (dash symbol)
        s = ProcessCoordinate(v[0]);             // Processing Coordinate.
        coordinate = ProcessString(s, " ");      // Splitting string using delimiter " "(spacing)
        x = ConvertStringToInteger(coordinate[0]); // Converts x coordinate to integer
        y = ConvertStringToInteger(coordinate[1]); // Converts y coordinate to integer

        // Values going into the map

        if ((x < width) && (y < height)) // Checks (x,y) are within the boundary of map rendered
        {
            pressure_map[height - y - 1][x] = ConvertToIndex(v[1]); // updates pressure map with converted index value
            pressure_orginal[height - y - 1][x] = ConvertStringToInteger(v[1]); // updates pressure map with converted integer value
        }
        if ((x < width) && (y < height))
        {
            pressure_converted[height - y - 1][x] = ConvertToLMHSymbols(ConvertStringToInteger(v[1])); // updates pressure map with converted LMH values
        }
    }
}
