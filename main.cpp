#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "AdjacencyList.h"
#include "fileRead.h"
using namespace std;




int main() {

    AdjacencyList adjList;
    bool t=true;
    cout << "Welcome to TradeMasters!" << endl;
    string productCode;
    while(t) {
        cout << "Please enter the HS 6-digit product code of the product you would like to see the data for: ";
        cin >> productCode;

        string filename = "product_codes_HS22_V202401b.csv";
        if (isProductCodeInCSV(filename, productCode)) {
            cout << "Product code " << productCode << " was found in the CSV file!" << endl;

            ifstream file("cleaned3_BACI_HS22_Y2022_V202401b.csv");
            if (!file.is_open()) {
                cerr << "Error: Could not open the file!" << endl;
            }

            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string export1, import, code, price;

                if (getline(ss, export1, ',') && getline(ss, import, ',') &&
                    getline(ss, code, ',') && getline(ss, price)) {

                    if (code == productCode) {
                        adjList.add_keys(import, export1, price);
                    }
                }
            }

            file.close();
            bool second = true;
            while (second) {
                cout << "Chose the country for which you want to see the data for!" << endl;
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
                        {1,  842},
                        {2,  156},
                        {3,  276},
                        {4,  392},
                        {5,  699},
                        {6,  826},
                        {7,  251},
                        {8,  76},
                        {9,  704},
                        {10, 410},
                        {11, 372},
                        {12, 381},
                        {13, 764},
                        {14, 757},
                        {15, 458},
                        {16, 360}
                };
                bool inner = true;
                while (inner) {
                    cin >> imp;
                    if (imp > 16 || imp < 1) {
                        cout << "Wrong input, try to choose again!" << endl;
                        inner = true;
                    } else {
                        adjList.traverse(to_string(importCountryMap[imp]));
                        cout<<endl;
                        cout<<"Do you want to see data for the same good for different country, if yes, please insert 0, otherwise insert any integer"<<endl;
                        int c;
                        cin>>c;
                        if(c==0){
                            second= true;
                            inner= false;
                        }
                        else{

                            t= false;
                            second= false;
                            inner= false;
                        }
                    }
                }
            }
        }else {
            cout << "Product code " << productCode << " was NOT found in the CSV file, please enter valid code." << endl;
            t= true;
        }


    }
    cout<<"Thank you for using TradeMasters!"<<endl;
    return 0;
}
