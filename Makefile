all: compile
compile: main.o algorithms.o DisplayUserMenu.o city_mapping.o cloud_mapping.o pressure_mapping.o weather_report.o
	g++ -std=c++11 main.o algorithms.o DisplayUserMenu.o city_mapping.o cloud_mapping.o pressure_mapping.o weather_report.o -o csci251_a1.app
		./csci251_a1.app
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
algorithms.o: algorithms.cpp algorithms.h
	g++ -std=c++11 -c algorithms.cpp
DisplayUserMenu.o:DisplayUserMenu.cpp DisplayUserMenu.h
	g++ -std=c++11 -c DisplayUserMenu.cpp
city_mapping.o:city_mapping.cpp city_mapping.h
	g++ -std=c++11 -c city_mapping.cpp
cloud_mapping.o:cloud_mapping.cpp cloud_mapping.h
	g++ -std=c++11 -c cloud_mapping.cpp
pressure_mapping.o:pressure_mapping.cpp pressure_mapping.h
	g++ -std=c++11 -c pressure_mapping.cpp
weather_report.o:weather_report.cpp weather_report.h
	g++ -std=c++11 -c weather_report.cpp
