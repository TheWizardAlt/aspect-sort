#include <iostream>
#include "sorter.h"
using namespace std;

void print(string s);

int main(){
    //TODO: functional main (all code below is temporary/testing)
    sorter *s = new sorter();

    cout << s->toString();

    s = new sorter("/");
    cout << s->toString();

    s = new sorter(2.0, 1.0);
    cout << s->toString();

     s = new sorter("/test/", 0.1, 0.3);
    cout << s->toString();

    return 0;
}