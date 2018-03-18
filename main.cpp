#include <iostream>
#include "sorter.h"
using namespace std;

void print(string s);

int main(){
    //TODO: functional main (all code below is temporary/testing)
    cout << "Search path..." << endl;
    sorter *s = new sorter();
    
    string inputPath = "";
    getline(cin, inputPath);

    s = new sorter("./images", 0.1, 0.3);

    cout << s->toString();
    s->findImages();
    cout << s->toString();
    return 0;
}