#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "fileRead.h"
using namespace std;

int main() {

    AdjacencyList adjList;
    AdjacencyMatrix adjMatrix;
    bool first = true;
    cout << "Welcome to TradeMasters!" << endl;
    string testStructure;
    string productCode;
    while (first) {
        cout << "Please enter number for the data structure you would like to test\n1. Adjacency List\n2. Adjacency Matrix" << endl;
        cin >> testStructure;
        cout << endl;

        cout << "Please enter the HS 6-digit product code of the product you would like to see the data for:\n";
        cin >> productCode;
        cout << endl;

        string filename = "product_codes_HS22_V202401b.csv";
        if (isProductCodeInCSV(filename, productCode)) {
            cout << "Product code " << productCode << " was found in the CSV file!" << endl;
            cout << endl;
            cout << "Extracting data, please wait (it will take about 20 seconds to generate data)!" << endl;

            ifstream file("BACI_HS22_Y2022_V202401b_final.csv");
            if (!file.is_open()) {
                cerr << "Error: Couldn't open the file!" << endl;
            }

            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string exporter1, importer, code, price, weight;
                float perUnitCost;

                if (getline(ss, exporter1, ',') && getline(ss, importer, ',') &&
                    getline(ss, code, ',') && getline(ss, price,',') && getline(ss, weight)) {
                    perUnitCost = stof(price) / stof(weight);

                    if (code == productCode) {
                        if (testStructure == "1")
                            adjList.add_keys(importer, exporter1, to_string(perUnitCost));
                        if (testStructure == "2")
                            adjMatrix.addTradeRelation(importer, exporter1, perUnitCost);
                    }
                }
            }

            file.close();
            bool second = true;
            while (second) {
                cout << "Choose the importing country: " << endl;
                int imp;
                cout <<
                     "1. USA  \n"
                     "2. China  \n"
                     "3. Germany  \n"
                     "4. Japan  \n"
                     "5. India  \n"
                     "6. United Kingdom  \n"
                     "7. France  \n"
                     "8. Brazil  \n"
                     "9. Viet Nam  \n"
                     "10. Rep. of Korea  \n"
                     "11. Ireland  \n"
                     "12. Italy  \n"
                     "13. Thailand  \n"
                     "14. Switzerland  \n"
                     "15. Malaysia  \n"
                     "16. Indonesia \n";

                unordered_map<int, int> importCountryMap = {
                        {1, 842},
                        {2, 156},
                        {3, 276},
                        {4, 392},
                        {5, 699},
                        {6, 826},
                        {7, 251},
                        {8, 76},
                        {9, 704},
                        {10, 410},
                        {11, 372},
                        {12, 380},
                        {13, 764},
                        {14, 757},
                        {15, 458},
                        {16, 360}
                };
                bool inner = true;
                while (inner) {
                    cin >> imp;
                    // TODO: Increase the range or instead provide country by name
                    if (imp > 16 || imp < 1) {
                        cout << "Wrong input, try to choose again!" << endl;
                        inner = true;
                    } else {
                        if (testStructure == "1")
                            adjList.traverseList(to_string(importCountryMap[imp]));
                        if (testStructure == "2")
                            adjMatrix.traverseMatrix(importCountryMap[imp]);
                        cout << endl;
                        cout << "Search Complete\n0. Choose a different importer for the same good\n1. Exit" << endl;
                        int c;
                        cin >> c;
                        if (c == 0) {
                            second = true;
                            inner = false;
                        } else {
                            first = false;
                            second = false;
                            inner = false;
                        }
                    }
                }
            }
        } else {
            cout << "Product code " << productCode << " was NOT found in the CSV file, please enter valid code." << endl;
            first = true;
        }


    }
    cout << "Thank you for using TradeMasters!"<<endl;
    return 0;
}
