#include <iostream>
#include "sorter.h"
#include <string>
#include <vector>
#include<experimental/filesystem>
using namespace std;
namespace fs = std::experimental::filesystem;


sorter *newSorterFromString(string s);
vector<string> parseCSVSetting(string setting);
bool getInput();
void msg(string s);

int main(){
    msg("---Aspect Sorting---");
    ifstream setStream;
    setStream.open("oldRuns.csv", ifstream::in);
    if(!setStream.fail()){
        msg("Would you like to re-run previous runs?");
        if(getInput()){
            string oldRun = "";
            while(getline(setStream,oldRun)){
                sorter *s = newSorterFromString(oldRun);
                s->findImages();
                s->aspectSort();
                msg(s->toString());
            }
        }
    }
    return 0;
}

void msg(string s){
    cout << s << endl;
}

bool getInput(){
    cout << "y/n:     ";
    string response = "n";
    getline(cin,response);
    if(response == "Y" || response == "y")
        return true;
    return false;
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