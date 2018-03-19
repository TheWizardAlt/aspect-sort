#include <iostream>
#include "sorter.h"
#include <string>
#include <vector>
using namespace std;

vector<string> parseCommas(string setting);
int main(){
    //TODO: functional main (all code below is temporary/testing)
    sorter *s = new sorter();

    s = new sorter("./", 1, 2, "./sort/");

    s->findImages();
    s->aspectSort();
    cout << s->toString();

    vector<string> v = parseCommas(s->toCSV());
    for(string s : v)
        cout << s << endl;

    s = new sorter();
    s->setSearchPath(v[0]);

    stringstream ss(v[1]);
    double temp;
    ss >> temp;
    s->setMinAR(temp);

    temp = 0;
    ss.clear();
    ss << v[2];
    ss >> temp;
    s->setMaxAR(temp);
    s->setOutputPath(v[3]);

    s->findImages();
    s->aspectSort();
    cout << s->toString();

    return 0;
}

vector<string> parseCommas(string setting){
    vector<string> settings;
    for(int i = 0; i < 4; i++){
        string s = setting.substr(0,setting.find(","));
        setting = setting.substr(setting.find(",")+1,setting.length() - 1);
        settings.push_back(s);
    }
    return settings;
}