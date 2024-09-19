/*
UOW Student Name: Rohit Panda
UOW Student ID: 8943060
MAJ40164 - Digital Systems Security
CSCI251 - Advanced Programming
*/

#include "city_mapping.h"
#include "algorithms.h"

// To process raw city data in the format given and mapping it to a 2D Array map.
void CityElement(int height, int width, string **&city_map, vector<string> &raw_city_data, vector<string> &raw_city_name_data, vector<string> &raw_city_id_data)
{
    // Declaration of variables
    string value;              // store extracted value from the raw city data
    string name;               // store extracted name from the raw city data
    string s;                  // store processed coordinate string
    vector<string> coordinate; /// store the split coordinates
    vector<string> v;          // store the split raw city data
    int x;                     // store the x coordinate
    int y;                     // store the y coordinate

    // To handle config file re-reads, we need to clear the vectors before computation.
    raw_city_name_data.clear();
    raw_city_id_data.clear();

    // Extraction of data:
    for (int i = 0; i < raw_city_data.size(); i++)
    {
        v = ProcessString(raw_city_data[i], "-"); // Splitting the raw data.
        s = ProcessCoordinate(v[0]);              // Processing Coordinate.
        value = v[1];                             // Process value.
        name = v[2];                              // Process name.

        // Assigning value
        if (!count(raw_city_name_data.begin(), raw_city_name_data.end(), name))
        {
            raw_city_name_data.push_back(name); // Storing of unique names
            raw_city_id_data.push_back(value);  // Storing of unique IDs
        }
        coordinate = ProcessString(s, " "); // Splitting string using delimiter " "(spacing)
        x = ConvertStringToInteger(coordinate[0]);
        y = ConvertStringToInteger(coordinate[1]);

        // rotating and assigning values to the map
        if ((x < width) && (y < height))
        {
            city_map[height - y - 1][x] = value;
        }
    }
}