/*
UOW Student Name: Rohit Panda
UOW Student ID: 8943060
MAJ40164 - Digital Systems Security
CSCI251 - Advanced Programming
*/

#include "cloud_mapping.h"
#include "algorithms.h"

void CloudElement(int height, int width, string **cloud_map, vector<string> &raw_cloud_data, int **&cloud_original, string **&cloud_converted)
{
    vector<string> v; //stores processed delimters "-" (dash), (e.g, ["1 3", "10"])
    string s; //store processed coordinates , (e.g, "1 3")
    vector<string> coordinates; // stores split coordinates, (e.g, ["1", "3"])
    int x;
    int y;

    // Extraction of data from config.txt
    for (int i = 0; i < raw_cloud_data.size(); i++)
    {
        v = ProcessString(raw_cloud_data[i], "-");
        s = ProcessCoordinate(v[0]);

        coordinates = ProcessString(s, " ");

        x = ConvertStringToInteger(coordinates[0]);
        y = ConvertStringToInteger(coordinates[1]);

        // Values going into the map
        if ((x < width) && (y < height))
        {
            cloud_map[height - y - 1][x] = ConvertToIndex(v[1]);
            cloud_original[height - y - 1][x] = ConvertStringToInteger(v[1]);
        }
        if ((x < width) && (y < height))
        {
            cloud_converted[height - y - 1][x] = ConvertToLMHSymbols(ConvertStringToInteger(v[1]));
        }
        
    }
}