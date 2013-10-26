//
//  main.cpp
//  quick sort
//
//  Created by Lance Bai on 13/8/5.
//  Copyright (c) 2013 Lance Bai. All rights reserved.
//

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))
#include <iostream>
#include <vector>
#include <algorithm>    // std::swap
#include <assert.h>
#include <ctime>
#include <cstdlib>
using namespace std;

const int data[] = {7, 23, 4, 82, 67, 33, 17, 29, 46};

template<typename T>
void dump_data(vector<T>& iVec)
{
    
    for (typename vector<T>::iterator it = iVec.begin(); it!=iVec.end(); ++it)
    {
        cout << *it ;
        
        if(iVec.end() != it+1) {
            cout << ",";
        }
    }
    cout << endl;
}

/**
 * dump_data
 * dump the content of data vector with bracket on left index and right index
 *
 * @param vData the data to be dump
 * @param uiLeftBracket the left index
 * @param uiRightBracket the right index
 * @return nothing useful
 */
template<typename T>
void dump_data(vector<T>& vData, unsigned int uiLeftBracket, unsigned int uiRightBracket)
{
    assert(uiLeftBracket >=0 && uiLeftBracket <= vData.size());
    assert(uiRightBracket >=0 && uiRightBracket <= vData.size());

    unsigned int i;
    typename vector<T>::iterator it;
    for ( i=0, it = vData.begin(); it != vData.end(); ++it, ++i)
    {
        if(i == uiLeftBracket){
            cout << "[";
        }
        
        cout << *it ;
        
        if(i == uiRightBracket){
            cout << "]";
        }
        if(vData.end() != it+1) {
            cout << ",";
        }
    }
    cout << endl;
}


/**
 * dump_data
 * dump the content of data array 
 *
 * @param aData the data to be dump
 * @param uiDataNumber the size of data array
 * @return nothing useful
 */

template <typename T>
void dump_data(T aData[], size_t uiDataNumber)
{
    unsigned int uiIndex;
    assert(uiDataNumber > 0);
    for(uiIndex = 0; uiIndex < uiDataNumber; uiIndex ++) {
        cout << aData[uiIndex] << ",";
    }
    cout << endl;
}


/**
 * quick_selection_partition
 * subroutine partition
 *
 * @param vData        vector data to be partitioned
 * @param uiIndexStart the start position of data, i.e pivot
 * @param uiIndexEnd   the end position of data
 * @return the order of vData[uiIndexStart] in vector data
 */
template <typename T>
unsigned int quick_selection_partition(vector<T> &vData, unsigned int uiIndexStart, unsigned int uiIndexEnd, unsigned int uiPivotIndex)
{
    assert(uiIndexStart >= 0 && uiIndexStart < uiIndexEnd);
    assert(uiIndexEnd >= 1 && uiIndexEnd < vData.size());
    assert(vData.size() >= 0);
    assert(uiPivotIndex >= uiIndexStart && uiPivotIndex <= uiIndexEnd);
    
    unsigned int i, j;
    swap(vData[uiIndexStart], vData[uiPivotIndex]);
    for (i = uiIndexStart, j = uiIndexStart+1; j <= uiIndexEnd; j++ ) {
        //cout << "comparing " << vData[j] << " with " << vData[uiIndexStart] << endl;
        if(vData[j] <= vData[uiIndexStart]){
            //cout << "swap " << vData[j] << " with " << vData[i] << "!"<< endl;
            i++;
            swap(vData[i], vData[j]);
        }
    }
    
    assert(i <= uiIndexEnd);
    
    //swap pivot with index i
    swap(vData[uiIndexStart], vData[i]);
    
    //i.e. pivot is nth element in aData
    cout << vData[i] << " is " << i << "th element in order" << endl;
    return i;
}

/**
 * quick_selection
 * the recursive function quick sort
 *
 * @param vData        vector data to be sorted
 * @param uiStart the start position of data
 * @param uiEnd   the end position of data
 * @param uiSel   the position of data we are looking for
 * @return nothing useful
 */
template <typename T>
void quick_selection(vector<T> &vData, unsigned int uiStart, unsigned int uiEnd, unsigned int uiSel)
{
    
    
    assert(uiStart >= 0 && uiStart < vData.size());
    assert(uiEnd >= 0 && uiEnd < vData.size());
    
    
    //check if it is boundary
    if(uiStart >= uiEnd) {
        //only one element
        cout << uiStart << ":" << uiEnd << ",boundary condition! do nothing!" << endl;
        return;
    }
    
    cout << "before partition("<< uiStart << ":" << uiEnd << ")"  << endl;
    dump_data(vData, uiStart, uiEnd);
    
    
    if(uiStart < uiEnd){
        unsigned int uiPivotIndex;

        //get a randon pivot index
        std::srand((unsigned int)std::time(0)); // use current time as seed for random generator
        unsigned int uiRandom = std::rand();
        uiRandom = uiRandom%(uiEnd - uiStart + 1) + uiStart;

        cout << "using " << uiRandom << "th element ("<< vData[uiRandom]<<") as pivot" \
             << " to partition(" << uiStart << ":" << uiEnd <<")"<< endl;


        uiPivotIndex = quick_selection_partition(vData, uiStart, uiEnd, uiRandom);
        cout << "after partition" << endl;
        dump_data(vData, uiStart, uiEnd);
        assert(uiPivotIndex >= uiStart && uiPivotIndex <= uiEnd);
        
        cout << "divide into 2 groups" << endl;
        cout << "from "<< uiStart << " to " <<  uiPivotIndex - 1 << endl;
        cout << "and " << uiPivotIndex+1 << " to " << uiEnd << endl;
        cout << "===========================" << endl;
       
         
        if(uiPivotIndex >  uiSel) {
            quick_selection(vData, uiStart, uiPivotIndex - 1, uiSel);
        }
        
        if(uiPivotIndex < uiSel) {
            quick_selection(vData, uiPivotIndex+1, uiEnd, uiSel);
        }

        if(uiPivotIndex == uiSel) { 
          return;
        }
        
    }
    
}


int main(int argc, const char * argv[])
{

    vector<int> iVec(data, data+ ARRAY_SIZE(data));
    
    std::cout << "before sort!\n";
    dump_data(iVec);
    
    quick_selection(iVec, 0, (unsigned int)(iVec.size()-1), ARRAY_SIZE(data)/2);
    std::cout << "after sort!\n";
    dump_data(iVec);
    std::cout << "medium is " << iVec[ARRAY_SIZE(data)/2] << std::endl;

    return 0;
}

