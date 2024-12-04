#include "AdjacencyMatrix.h"

//searches the country__codes file to determine if the input country code is valid
int AdjacencyMatrix::countryToIndex(string countryCode) {
    ifstream file("country_codes_V202401b.csv");
    if (!file.is_open()) {
        cout << "Error: Couldn't open the file!" << endl;
        return -1;
    }
    string line;
    //goes through each line in the file
    while (getline(file, line)) {
        stringstream ss(line);
        string country_code, country_name, country_iso2, country_iso3;
        if (getline(ss, country_code, ',') && getline(ss, country_name, ',') && getline(ss, country_iso2, ',') && getline(ss, country_iso3, ',')) {
            if (country_code == countryCode) {
                try {
                    file.close();
                    return stoi(country_code);
                } catch (const invalid_argument&) {
                    cerr << "Error: Invalid country code in file for " << countryCode << endl;
                    file.close();
                    return -1;
                }
            }
        }
    }
    file.close();
    return -1;
}

//uses the input country index and gets the country name by going through the whole
//country_codes files
string AdjacencyMatrix::indexToCountry(int index) {
    ifstream file("country_codes_V202401b.csv");
    if (!file.is_open()) {
        cerr << "Error: Couldn't open the file!" << endl;
        return "";
    }
    string line;
    //goes through each line in the file
    while (getline(file, line)) {
        stringstream ss(line);
        string country_code, country_name, country_iso2, country_iso3;
        if (getline(ss, country_code, ',') && getline(ss, country_name, ',') &&
            getline(ss, country_iso2, ',') && getline(ss, country_iso3, ',')) {
            try {
                if (index == stoi(country_code)) {
                    file.close();
                    return country_name;
                }
            } catch (const invalid_argument&) {
                continue;
            }
        }
    }
    file.close();
    cerr << "Error: Index " << index << " not found in file." << endl;
    return "";
}

//this adds each importer the corresponding information for the exporter and unit-cost of the trade
void AdjacencyMatrix::addTradeRelation(string importCountry, string exportCountry, float productUnitCost) {
    int row = countryToIndex(importCountry);
    int col = countryToIndex(exportCountry);
    if (row < 0 || row >= num_countries || col < 0 || col >= num_countries) {
        cerr << "Error: Invalid index. Row: " << row << ", Col: " << col << endl;
        return;
    }
    //adds to the matrix where row is the import country and column is the exporting country
    matrix[row][col] = productUnitCost;
}

//goes through each item in the matrix for the user-input importing country and gets
//all of the exporting countries and unit-cost of the trade
void AdjacencyMatrix::traverseMatrix(int importerCode) {
    //the result vector stores pairs of the exporting country name and unit-cost of that trade to be output for each
    //exporting country
    vector<pair<string, float>> result;
    vector<float> values = matrix[importerCode];
    for (int i = 0; i < matrix.size(); i++) {
        if (i == importerCode) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] != -1) {
                    string exportCountry = indexToCountry(j);
                    result.emplace_back(exportCountry, matrix[i][j]);
                }
            }
        }
    }
    // Sort based on second element in pair: https://www.geeksforgeeks.org/sort-a-vector-of-pairs-based-on-second-element-of-pair-in-cpp/
    sort(result.begin(), result.end(), [](const auto& country, const auto& cost) {
        return country.second < cost.second;
    });

    for (auto value : result) {
        //outputs the list of exporting country name and unit-cost value of the trade
        cout << value.first << " --> " << value.second << endl;
    }
}