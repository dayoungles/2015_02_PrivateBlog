//
//  mergeSort_C2.c
//  jagual1
//
//  Created by Dayoungle on 2014. 10. 23..
//  Copyright (c) 2014년 dayoungle. All rights reserved.
//

#include <stdio.h>

void mergeSort(int* arr, int start, int last);
void merge(int* arr1, int start, int mid, int last);

int main(){
    int i;
    int arr[10] = {3,10,4,9,5, 2,8,1,6, 7};
    printf("%lu", sizeof(arr)/sizeof(int)-1);
    mergeSort(&arr, 0, sizeof(arr)/sizeof(int)-1);
        
    for(i = 0; i< 10; i++){
        printf("%d ", arr[i]);
    }
}

void mergeSort(int* arr, int start, int last){
    int mid;
    if(start< last){
        mid = start + (last-start)/2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid+1, last);
        merge(arr, start, mid, last);
    }
}

//0, mid, last 값이면

void merge(int* arr, int start, int mid, int size){
    int i,j, k, leftPos, rightPos;
    int leftArr[mid - start + 1];
    int rightArr[size - mid];
    //왼쪽 어레이로 복사.
    for(i = 0; i <= mid; i++){
        leftArr[i]= arr[start+i];
    }
    for(j = 0; j < size-mid; j++){
        rightArr[j] = arr[mid+1 + j];
    }
    for(k = 0; k< size; k++){
        leftPos = 0; rightPos = 0;
        if(leftArr[leftPos]<= arr[mid+1+ rightPos]){
            arr[k] = leftArr[leftPos];
            ++leftPos;
        } else {
            arr[k] = rightArr[mid+1 + rightPos];
            ++rightPos;
        }
    }

}