#include <iostream>
#include "sorter.h"
using namespace std;

void print(string s);

int main(){
    //TODO: functional main (all code below is temporary/testing)
    sorter *s = new sorter();

    s = new sorter("./images", 0, 2);

    cout << s->toString();
    s->findImages();
    cout << s->toString();
    s->loadImageDatabase();
    s->aspectSort();
    cout << s->toString();
    return 0;
}