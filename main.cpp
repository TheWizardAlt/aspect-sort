#include <iostream>
#include "sorter.h"
#include <string>
#include <vector>
using namespace std;

void newSorterFromString(sorter *curs, string s);
vector<string> parseCSVSetting(string setting);

int main(){
    //TODO: functional main (all code below is temporary/testing)
    sorter *s = new sorter();

    s = new sorter("./", 1, 2, "./sort/");

    s->findImages();
    s->aspectSort();
    cout << s->toString();

    cout << "CONVERT TO CSV AND RE INITIALIZE" << string(3, '\n');

    newSorterFromString(s, s->toCSV());

    s->findImages();
    s->aspectSort();
    cout << s->toString();

    return 0;
}

void newSorterFromString(sorter *curs, string s){
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

    curs = new sorter(searchPath, minAR, maxAR, outputPath);
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