//
//  main.cpp
//  merge sort
//
//  Created by Ann Wang on 13/7/22.
//  Copyright (c) 2013年 Lance Bai. All rights reserved.
//

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))
#include <iostream>
#include <vector>
//#include <string.h>
#include <assert.h>

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
 * merge_sort_merge
 * sub function of merge sort, to merge the 2 sorted data
 * @param aData - the source Data
 * @parma uiSortedData1IndexStart - the start loc of Data1
 * @param uiSortedData1IndexEnd   - the end loc of Data1
 * @parma uiSortedData2IndexStart - the start loc of Data2
 * @param uiSortedData2IndexEnd   - the end loc of Data2
 */
template <typename T>
void merge_sort_merge(
T aData[],
unsigned int uiSortedData1IndexStart,
unsigned int uiSortedData1IndexEnd,
unsigned int uiSortedData2IndexStart,
unsigned int uiSortedData2IndexEnd)
{
    assert(aData != NULL);
    //can be only 1 element
    assert(uiSortedData1IndexStart <= uiSortedData1IndexEnd);
    assert(uiSortedData2IndexStart <= uiSortedData2IndexEnd);

    const unsigned int uiSizeOfSortedData1 = uiSortedData1IndexEnd - uiSortedData1IndexStart + 1;
    const unsigned int uiSizeOfSortedData2 = uiSortedData2IndexEnd - uiSortedData2IndexStart + 1;
    const unsigned int uiTotolDataNumber = uiSortedData2IndexEnd - uiSortedData1IndexStart + 1 ;
    
    cout << "we are going to merge:" << endl;
    cout << "data1:";
    dump_data(&aData[uiSortedData1IndexStart], uiSizeOfSortedData1);
    cout << "data2:";
    dump_data(&aData[uiSortedData2IndexStart], uiSizeOfSortedData2);
    
    unsigned int uiIndex = 0;
    
    
    //to store merged result
    T* aTempResult = new T[uiTotolDataNumber];
    unsigned int uiSortedData1Index = uiSortedData1IndexStart;
    unsigned int uiSortedData2Index = uiSortedData2IndexStart;
    

    
    while(uiSortedData1Index <= uiSortedData1IndexEnd && uiSortedData2Index <= uiSortedData2IndexEnd) {
    
        if(aData[uiSortedData1Index] < aData[uiSortedData2Index]) {
            
            *(aTempResult+ uiIndex) = aData[uiSortedData1Index];
            uiSortedData1Index ++;
            
        }else{
            *(aTempResult+ uiIndex) = aData[uiSortedData2Index];
            uiSortedData2Index ++;
        }
        
        uiIndex ++;
    }
    
    //this should not happen
    assert(!((uiSortedData1Index > uiSortedData1IndexEnd)&& (uiSortedData2Index > uiSortedData2IndexEnd)));
    
    //copy the remaining elements to result array
    if(uiSortedData1Index > uiSortedData1IndexEnd) {
        memcpy(aTempResult+uiIndex, &aData[uiSortedData2Index], (uiSortedData2IndexEnd - uiSortedData2Index + 1)*sizeof(T));
    }
    
    if(uiSortedData2Index > uiSortedData2IndexEnd) {
        memcpy(aTempResult+uiIndex, &aData[uiSortedData1Index], (uiSortedData1IndexEnd - uiSortedData1Index + 1)*sizeof(T));
    }
    
    cout << "the merging result is:" << endl;
    dump_data(aTempResult, uiTotolDataNumber);
    //copy back to the source data array
    memcpy(&aData[uiSortedData1IndexStart], aTempResult, uiTotolDataNumber*sizeof(T));
    delete[] aTempResult;
    
    
    //iVec[uiSortedData1IndexStart] = iVec[uiSortedData1IndexStart] < iVec[uiSortedData2IndexStart] ? iVec[uiSortedData1IndexStart]:
    
}

/**
 * merge_sort_split
 *
 * template recursive function, split data array into 2, and then merge
 * @param aData - the data array
 * @param uiIndexStart - the start loc of data array
 * @param uiIndexEnd - the end loc of data array
 */

template <typename T>
void merge_sort_split(T aData[], unsigned int uiIndexStart, unsigned int uiIndexEnd)
{
    
    assert(uiIndexEnd >= uiIndexStart);

    const unsigned int uiSize = uiIndexEnd - uiIndexStart + 1;

    if(uiSize == 1) {
        cout << "reach the recursive bottom! return!" << endl;
        return;
    }
    merge_sort_split(aData, uiIndexStart, uiIndexStart + uiSize/2 -1);
    merge_sort_split(aData, uiIndexStart + uiSize/2 , uiIndexEnd);
    merge_sort_merge(aData, uiIndexStart, uiIndexStart + uiSize/2 -1, uiIndexStart + uiSize/2 , uiIndexEnd);
}


/**
 * merge_sort
 * 
 * the template merge sort main body
 * @param aData - the orignal data array
 * @param uiDataSize - # of aData
 */
template <typename T>
void merge_sort(T aData[], size_t uiDataSize)
{
 
    assert(uiDataSize >0);
    //sort from index 0 to n-1
    merge_sort_split(aData, 0, (unsigned int)uiDataSize -1);

}

int main(int argc, const char * argv[])
{
    const int uiDataNum = ARRAY_SIZE(data);
    int* aResult = new int[uiDataNum];
    
    memcpy(aResult, data, sizeof(data));
    std::cout << "before sort!\n";
    dump_data(data, ARRAY_SIZE(data));
    
    merge_sort(aResult, uiDataNum);
    std::cout << "after sort!\n";
    dump_data(aResult, uiDataNum);
    delete []aResult;
    return 0;
}

