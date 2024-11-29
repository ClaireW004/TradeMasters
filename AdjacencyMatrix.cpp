#include "AdjacencyMatrix.h"

int AdjacencyMatrix::countryToIndex(string countryCode) {
    ifstream file("country_codes_V202401b.csv");
    if (!file.is_open()) {
        cout << "Error: Couldn't open the file!" << endl;
        return -1;
    }

    string line;
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

string AdjacencyMatrix::indexToCountry(int index) {
    ifstream file("country_codes_V202401b.csv");
    if (!file.is_open()) {
        cerr << "Error: Couldn't open the file!" << endl;
        return "";
    }

    string line;
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
//                    cerr << "Error: Invalid country code '" << country_code << "' in file." << endl;
                continue;
            }
        }
    }

    file.close();
    cerr << "Error: Index " << index << " not found in file." << endl;
    return "";
}

void AdjacencyMatrix::addTradeRelation(string importCountry, string exportCountry, float productUnitCost) {
    int row = countryToIndex(importCountry);
    int col = countryToIndex(exportCountry);
    if (row < 0 || row >= num_countries || col < 0 || col >= num_countries) {
        cerr << "Error: Invalid index. Row: " << row << ", Col: " << col << endl;
        return;
    }
    matrix[row][col] = productUnitCost;
}

void AdjacencyMatrix::traverseMatrix(int importerCode) {
    vector<pair<string, float>> result;

    vector<float> values = matrix[importerCode];
    for (int i = 0; i < matrix.size(); i++) {
        if (i == importerCode) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] != -1) {
                    string exportCountry = indexToCountry(j);
//                        cout << exportCountry << " --> " << to_string(matrix[i][j]) << endl;
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
        cout << value.first << " --> " << value.second << endl;
    }
}