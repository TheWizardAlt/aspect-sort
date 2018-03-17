#include <iostream>
#include "sorter.h"
using namespace std;

void print(string s);

int main(){
    //TODO: functional main (all code below is temporary/testing)
    sorter *s = new sorter();

    string inputPath = "";
    getline(cin, inputPath);

    s = new sorter(inputPath, 0.1, 0.3);
    
    cout << s->toString();
    s->findImages();
    s->toString();
    return 0;
}