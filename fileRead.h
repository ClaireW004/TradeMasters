//#ifndef FILEREAD_H
//#define FILEREAD_H
//
//#include <unordered_map>
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
////#include "AdjacencyList.h"
//using namespace std;
//
//
//
//unordered_map<string, string> parseCountryFile(const string& filePath) {
//    unordered_map<string, string> countryMapCodeToName;
//    ifstream file(filePath);
//
//    if (!file.is_open()) {
//        std::cerr << "Error opening file: " << filePath << std::endl;
//        return countryMapCodeToName;
//    }
//
//    string line;
//    getline(file, line);
//
//    while (getline(file, line)) {
//        stringstream ss(line);
//        string country_code, country_name_abbreviation;
//
//        getline(ss, country_code, ',');
//        getline(ss, country_name_abbreviation, ',');
//
//
//        countryMapCodeToName[country_code] = country_name_abbreviation;
//    }
//
//    file.close();
//    return countryMapCodeToName;
//}
//bool isProductCodeInCSV(const string& filename, const string& productCode) {
//    ifstream file(filename);
//    if (!file.is_open()) {
//        cerr << "Error: Could not open the file!" << endl;
//        return false;
//    }
//
//    string line;
//    while (getline(file, line)) {
//        size_t commaPos = line.find(',');
//        if (commaPos == string::npos) {
//            continue;
//        }
//
//        string code = line.substr(0, commaPos);
//        if (code == productCode) {
//            return true;
//        }
//    }
//
//    file.close();
//    return false;
//}
//
//#endif
