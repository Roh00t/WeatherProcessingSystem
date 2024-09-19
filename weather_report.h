/*
UOW Student Name: Rohit Panda
UOW Student ID: 8943060
MAJ40164 - Digital Systems Security
CSCI251 - Advanced Programming
*/

#ifndef WEATHER_REPORT_H
#define WEATHER_REPORT_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct City_report
{
    string name; //Store name of city
    string id; // Store City ID
    string symbol; // Store weather symbol for the city
    double rain; // Store probability of rain in percentage
    double average_cloud; // Store cloud cover percentage
    string cloud_level; // store cloud level L,M,H 
    double average_pressure; // store pressure average
    string pressure_level; // store pressure level.
};



void WeatherReportData(int height, int width, vector<string> raw_weather_name_data, vector<string> &raw_weather_id_data, string **& city_map, string **& cloud_map, string **& pressure_map, int **& pressure_original, int **& cloud_original, vector<City_report> & alist);
void WeatherReport(vector <City_report> alist);
void SortWeatherReportByID(vector<City_report> &alist);
string ToString(City_report r);
#endif