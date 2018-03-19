#include <iostream>
#include "sorter.h"
#include <string>
#include <vector>
using namespace std;

sorter *newSorterFromString(string s);
vector<string> parseCSVSetting(string setting);

int main(){
    
    return 0;
}

sorter *newSorterFromString(string s){
    sorter *newSorter;
    vector<string> csv = parseCSVSetting(s);

    double minAR, maxAR;
    string searchPath = csv[0], outputPath = csv[3];

    stringstream ss;
    ss << csv[1];
    ss >> minAR;

    ss.str("");
    ss.clear();
    ss << csv[2];
    ss >> maxAR;

    newSorter = new sorter(searchPath, minAR, maxAR, outputPath);

    return newSorter;
}

vector<string> parseCSVSetting(string setting){
    vector<string> settings;
    for(int i = 0; i < 4; i++){
        string s = setting.substr(0,setting.find(","));
        setting = setting.substr(setting.find(",")+1,setting.length() - 1);
        settings.push_back(s);
    }
    return settings;
}