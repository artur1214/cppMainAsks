#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "functions.h"
using namespace std;
template <class T>
string printVector(vector<T> vec){
    const int start = 0;
    const int end = vec.size();
    string res = "";
    for (int i = start; i != end; ++i) {
            res += to_string(vec[i]);
        }
    return res;
}


int main()
{

    Game a;

    for(int i = 0; i < 100; i ++){
        cout << printVector(a.newNumber()) << endl;
    }


    return 0;
}
