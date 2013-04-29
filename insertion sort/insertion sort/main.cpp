//
//  main.cpp
//  insertion sort
//
//  Created by Lance Bai on 13/4/27.
//  Copyright (c) 2013 Lance Bai. All rights reserved.
//

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))
#include <iostream> 
#include <vector>

using namespace std;

const int data[] = {7,23, 4, 82, 67,33, 17, 29, 46};

void dump_data(vector<int>& iVec)
{
    
    for (vector<int>::iterator it = iVec.begin(); it!=iVec.end(); ++it)
    {
        cout << *it << ",";
    }
    cout << endl;
}

template <typename T>
void insertion_sort(vector<T>& iVec)
{
    int j = 0, i = 0;
    T key;
    for(j =1; j< iVec.size(); j++) {
        key = iVec[j];
        i = j - 1;
        while (i >= 0 && iVec[i] > key){
            iVec[i+1] = iVec[i];
            i --;
        }
        iVec[i+1] = key;
    }
}

int main(int argc, const char * argv[])
{

    vector<int> iVec(data, data+ ARRAY_SIZE(data));
    // insert code here...
    std::cout << "before sort!\n";
    dump_data(iVec);
    insertion_sort(iVec);
    std::cout << "after sort!\n";
    dump_data(iVec);
    return 0;
}

