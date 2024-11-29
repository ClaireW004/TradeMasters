#include "AdjacencyList.h"

void AdjacencyList::add_keys(const string& importer, const string& exporter1, const string& price) {
    if(graph.find(importer) == graph.end()) {
        graph[importer] = {};
    }
    graph[importer].push_back(make_pair(exporter1, price));
}

void AdjacencyList::traverseList(const string& inputCountryName, unordered_map<string, string> countryMapCodeToName, unordered_map<string, string> countryMapNameToCode){
    string countryCode = countryMapNameToCode[inputCountryName];
    for (const auto& pair : graph[countryCode]) {
        if (graph[countryCode].empty()){
            cout << "Country is not importing certain good from other countries!" << endl;
            return;
        }
        outputMap[stof(pair.second)].push_back(pair.first);
        //std::cout << countryMapCodeToName[pair.first] << " -> " << pair.second << std::endl;
    }

    for (const auto& key : outputMap){
        for (const auto& value: key.second){
            cout << countryMapCodeToName[value] << " --> " << key.first << endl;
        }
    }
}
