/*
UOW Student Name: Rohit Panda
UOW Student ID: 8943060
MAJ40164 - Digital Systems Security
CSCI251 - Advanced Programming
*/

#include "weather_report.h"
#include "algorithms.h"

// Function Prototypes:
string ToString(City_report r); // Converts Struct to string for printing onto screen

// Struct Declaration:
// Convert average value to string format.
struct LevelAssignments
{
    string low;
    string medium;
    string high;
};

// Declaration of some variables:
int * city_size;              // Array store size of each city
int * cloud_summary;              // Array stores summary of cloud cover values for each city
int * pressure_summary;           // Array stores summary of pressure level values for each city
int report_size;             // Size of report list
int id;                      // This variable is temporary for city IDs
City_report *report_list;    // Array of the Struct storing report data for each city
void Assign(City_report &r); // Assignment of levels for cloud cover and pressure levels (for determining possibility of rain)

// Printing of weather reports for all cities onto screen:
void WeatherReport(vector<City_report> alist)
{
    for (int i = 0; i < report_size; i++)
    {
        cout << ToString(alist[i]) << endl;
    }
}

// Additional Feature: 
void SortWeatherReportByID(vector<City_report> & alist)
{
    sort(alist.begin(), alist.end(), [](const City_report &a, const City_report &b){ return a.id < b.id; });
}


// Weather Report Data Handling:
void WeatherReportData(int height, int width, vector<string> raw_weather_name_data, vector<string> &raw_weather_id_data, string **& city_map, string **& cloud_map, string **& pressure_map, int **& pressure_original, int **& cloud_original, vector<City_report> & alist)
{
    string city_belong;

    // initializes report_size and dynamically allocate arrays for report_list, cloud_summary, pressure_summary, and city_size.
    report_size = raw_weather_name_data.size();
    report_list = new City_report[report_size];
    cloud_summary = new int[report_size];
    pressure_summary = new int[report_size];
    city_size = new int[report_size];

    for (int i = 0; i < report_size; i++)
    {
        report_list[i].name = raw_weather_name_data[i];
        report_list[i].id = raw_weather_id_data[i];
        cloud_summary[i] = 0;
        pressure_summary[i] = 0;
        city_size[i] = 0;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) // Iterates through every cell in 2D array
        {
            city_belong = SurroundingCheck(city_map, i, j, height, width);
            if (city_belong != "")
            {
                id = ConvertStringToInteger(city_belong);
                // decrement by 1 to adjust for zero-based indexing
                id--;          

                // Update City Data:
                city_size[id]++;
                cloud_summary[id] += cloud_original[i][j];
                pressure_summary[id] += pressure_original[i][j];
            }
        }
    }

    // loop initialization to iterate over each city report.
    for (int i = 0; i < report_size; i++)
    {
        // Compute Average Cloud Cover:
        report_list[i].average_cloud = cloud_summary[i] / static_cast<double>(city_size[i]);
        // Compute Average Pressure:
        report_list[i].average_pressure = pressure_summary[i] / static_cast<double>(city_size[i]);
    }

    // loop initialization to iterate over each city report.
    for (int i = 0; i < report_size; i++)
    {
        // Assign Additional Details:
        Assign(report_list[i]);
        // Add to alist List:
        alist.push_back(report_list[i]); // contains city reports with weather details.
    }

    // Sort the alist by city ID
    SortWeatherReportByID(alist);
    
    // Safely Deallocating memory by cleaning up dynamically allocated memory to prevent memory leaks:
    delete[] report_list;
    delete[] cloud_summary;
    delete[] pressure_summary;
    delete[] city_size;
}

// Converts a City_report Struct to a string for printing.
string ToString(City_report r)
{

    // Output String Stream:
    ostringstream oss;
    string value;

    // Formatting the Output:
    oss << "City Name\t\t:" << r.name << endl;
    oss << "City ID\t\t\t:" << r.id << endl;
    oss << "Ave. Cloud Cover (ACC)\t:" << setprecision(2) << fixed << r.average_cloud << " (" << r.cloud_level << ")" << endl;
    oss << "Ave. Pressure (AP)\t:" << setprecision(2) << fixed << r.average_pressure << " (" << r.pressure_level << ")" << endl;
    oss << "Probability of rain (%)\t:" << setprecision(2) << fixed << r.rain << endl;
    oss << r.symbol << endl;

    return (oss.str());
}

// Handles cloud levels, pressure levels, rain possibility, and LMH symbol for a city report based on  averages.
void Assign(City_report &r)
{

    // Lambda Function to Determine Levels:
    auto getLevel = [](double value, const LevelAssignments &levels) -> string
    {
        if (value <= 34)
        {
            return levels.low;
        }
        else if (value <= 64)
        {
            return levels.medium;
        }
        else
        {
            return levels.high;
        }
    };
    LevelAssignments cloudLevels{"L", "M", "H"};
    LevelAssignments pressureLevels{"L", "M", "H"};

    r.cloud_level = getLevel(r.average_cloud, cloudLevels);
    r.pressure_level = getLevel(r.average_pressure, pressureLevels);

    // Table for rain values and symbols:
    unordered_map<string, double> rainValues{
        {"LL", 70.0}, {"LM", 80.0}, {"LH", 90.0}, {"ML", 40.0}, {"MM", 50.0}, {"MH", 60.0}, {"HL", 10.0}, {"HM", 20.0}, {"HH", 30.0}

    };
    unordered_map<string, string> symbolValues{
        {"LL", "~~~~\n~~~~~\n  \\\\\\"}, {"LM", "~~~~\n~~~~~\n \\\\\\\\"}, {"LH", "~~~~\n~~~~~\n\\\\\\\\\\"}, {"ML", "~~~~\n~~~~~\n"}, {"MM", "~~~~\n~~~~~\n    \\"}, {"MH", "~~~~\n~~~~~\n   \\\\"}, {"HL", "~\n~~\n"}, {"HM", "~~\n~~~\n"}, {"HH", "~~~\n~~~~\n"}};

    // Combination of levels to get the key for lookup:
    string levelkey = r.pressure_level + r.cloud_level;

    // Assignment of rain and symbol based on lookup:
    r.rain = rainValues[levelkey];
    r.symbol = symbolValues[levelkey];
}
