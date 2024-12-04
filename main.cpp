#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "fileRead.h"

//traverses through the "product_codes_HS22_V202401b.csv" file to determine if the
//product code input by the user is a valid code
bool isProductCodeInCSV(const string& filename, const string& productCode) {
    ifstream file(filename);
    //handles if the file could not open
    if (!file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return false;
    }
    //goes through each line of the file
    string line;
    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos == string::npos) {
            continue;
        }
        string code = line.substr(0, commaPos);
        if (code == productCode) {
            return true;
        }
    }
    file.close();
    return false;
}

//goes through the "country_codes_V202401b.csv" file to add each country name and
//code to the two maps (countryMapWithCodeVal and countryMapWithNameVal) to allow
//for two maps to be created to convert country name to country code and vice versa
vector<unordered_map<string, string>> parseCountryFile(const string& filePath) {
    //this result vector will be returned and contains both maps.
    //a vector was used because it made it easier to create the countryMapCodeToName
    //and countryMapNameToCode functions in the main() function
    vector<unordered_map<string, string>> result = {};
    unordered_map<string, string> countryMapWithCodeVal;
    unordered_map<string, string> countryMapWithNameVal;
    ifstream file(filePath);
    //if the file could not open
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return result;
    }
    //goes through each line in the file
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string country_code, country_name;
        getline(ss, country_code, ',');
        getline(ss, country_name, ',');
        countryMapWithCodeVal[country_code] = country_name;
        countryMapWithNameVal[country_name] = country_code;
    }
    file.close();
    result.push_back(countryMapWithCodeVal);
    result.push_back(countryMapWithNameVal);
    //return the result vector that contains both maps
    return result;
}

//this function searches through the countryMapNameToCode function to determine if
//a key exists for the user input country name
string ensureValidCountryName(const unordered_map<string, string>& countryMapNameToCode, string inputCountryName){
    bool incorrectName = true;
    //this loop continues until the user inputs a valid country name
    while(incorrectName){
        if(countryMapNameToCode.count(inputCountryName) == 0){
            cout << "\nThe country name you entered was not recognized. Please ensure the name is spelled correctly and try again."
                    "\nPlease reference the country codes document for exact spellings.\n" << endl;
            //gets the new input name
            cin >> inputCountryName;
        }else{
            incorrectName = false;
        }
    }
    return inputCountryName;
}

int main() {
    unordered_map<string, string> countryMapCodeToName;
    unordered_map<string, string> countryMapNameToCode;
    vector<unordered_map<string, string>> countryMaps = parseCountryFile("country_codes_V202401b.csv");
    //put the necessary information into the respective map from the parseCountryFile function
    countryMapCodeToName = countryMaps[0];
    countryMapNameToCode = countryMaps[1];
    //creating objects of the adjacency list and adjacency matrix class
    AdjacencyList adjList;
    AdjacencyMatrix adjMatrix;
    bool runProgram = true;
    cout << "Welcome to TradeMasters!" << endl;
    string testStructure;
    string productCode;
    //this while loop continues until the user inputs "1" at the end to exit the program
    while (runProgram) {
        cout << "Please enter number for the data structure you would like to test\n1. Adjacency List\n2. Adjacency Matrix" << endl;
        //accepts user input to determine if the adjacency list or matrix should be used
        cin >> testStructure;
        cout << endl;
        cout << "Please enter the HS 6-digit product code of the product you would like to see the data for:\n";
        cin >> productCode;
        cout << endl;
        string filename = "product_codes_HS22_V202401b.csv";
        //checks if input product code is valid
        if (isProductCodeInCSV(filename, productCode)) {
            cout << "Product code " << productCode << " was found in the CSV file!" << endl;
            cout << endl;
            cout << "Extracting data, please wait (it will take about 20 seconds to generate data)!" << endl;
            ifstream file("BACI_HS22_Y2022_V202401b_final.csv");
            if (!file.is_open()) {
                cerr << "Error: Couldn't open the file!" << endl;
            }
            string line;
            //goes through each line in the "BACI_HS22_Y2022_V202401b_final.csv" file and adds the
            //trade data to either the adjacency list or adjacency matrix
            while (getline(file, line)) {
                stringstream ss(line);
                string exporter1, importer, code, price, weight;
                float perUnitCost;
                if (getline(ss, exporter1, ',') && getline(ss, importer, ',') &&
                    getline(ss, code, ',') && getline(ss, price,',') && getline(ss, weight)) {
                    //calculates the per-unit cost based on value of trade divided by the weight of the trade in tonnes
                    perUnitCost = stof(price) / stof(weight);
                    //either uses an adjacency list or matrix depending on the user input stored in the testStructure variable
                    if (code == productCode) {
                        if (testStructure == "1"){
                            adjList.add_keys(importer, exporter1, to_string(perUnitCost));
                        }
                        if (testStructure == "2")
                            adjMatrix.addTradeRelation(importer, exporter1, perUnitCost);
                    }
                }
            }
            file.close();
            bool choosingCountryData = true;
            //while loop continues until the user types "1" to exit the program
            while (choosingCountryData) {
                cout << "Type in the name of the importing country you would like to see data for: " << endl;
                string inputCountryName;
                bool inner = true;
                //this inner while loop continues until the user enters "1" to exit the program.
                //if "0" is input, the user cannot change the product they selected to search for,
                //but the user can look at trade data for the selected product for a different country
                while (inner) {
                    //clear the input buffer before taking in new input
                    cin.ignore();
                    getline(cin, inputCountryName);
                    string correctCountryName = ensureValidCountryName(countryMapNameToCode, inputCountryName);
                    if (testStructure == "1"){
                        adjList.traverseList(correctCountryName, countryMapCodeToName, countryMapNameToCode);
                    }
                    if (testStructure == "2"){
                        adjMatrix.traverseMatrix(stoi(countryMapNameToCode[correctCountryName]));
                    }
                    cout << endl;
                    cout << "Search Complete\n0. Choose a different importer for the same good\n1. Exit" << endl;
                    int c;
                    cin >> c;
                    if (c == 0) {
                        choosingCountryData = true;
                        inner = false;
                    } else {
                        runProgram = false;
                        choosingCountryData = false;
                        inner = false;
                    }
                }
            }
        } else {
            cout << "Product code " << productCode << " was NOT found in the CSV file, please enter valid code." << endl;
            runProgram = true;
        }
    }
    cout << "Thank you for using TradeMasters!"<<endl;
    return 0;
}