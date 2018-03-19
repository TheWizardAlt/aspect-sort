#include <iostream>
#include "sorter.h"
#include <string>
using namespace std;

vector<string> parseCommas(string setting);
int main(){
    //TODO: functional main (all code below is temporary/testing)
    sorter *s = new sorter();

    s = new sorter("./", 0, 2, "./sort/");

    cout << s->toString();
    s->findImages();
    cout << s->toString();
    s->aspectSort();
    cout << s->toString();

    vector<string> v = parseCommas(s->toCSV());

    return 0;
}

vector<string> parseCommas(string setting){
    vector<string> settings;
    //string setting1 = setting.find(",");
    cout << setting.substr(0, setting.find(","));
}