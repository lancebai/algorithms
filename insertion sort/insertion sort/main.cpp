//
//  main.cpp
//  insertion sort
//
//  Created by Lance Bai on 13/4/27.
//  Copyright (c) 2013年 Lance Bai. All rights reserved.
//

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))
#include <iostream>
using namespace std;

int data[] = {7,23, 4, 82, 67,33, 17, 29, 46};

void dump_data(void)
{
    for(int i = 0; i< ARRAY_SIZE(data); i++)
    {
        cout << data[i] << ",";
    }
    cout << endl;
}

void insertion_sort(int iArray[], int size)
{
    int j = 0, key = 0, i = 0;
    for(j =1; j< size; j++) {
        key = iArray[j];
        i = j - 1;
        while (i >= 0 && iArray[i] > key){
            iArray[i+1] = iArray[i];
            i --;
        }
        iArray[i+1] = key;
    }
}

int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "before sort!\n";
    dump_data();
    insertion_sort(data, ARRAY_SIZE(data));
    std::cout << "after sort!\n";
    dump_data();
    return 0;
}

