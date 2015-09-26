//
//  quicksort_mystyle.c
//  jagual1
//
//  Created by Dayoungle on 2014. 11. 8..
//  Copyright (c) 2014년 dayoungle. All rights reserved.
//

#include <stdio.h>

void quickSort(int* arr, int start, int last);
int partition(int* arr, int last);
void swap(int* a, int* b);
int main(){
    int arr[] = {6,1,8,9,5,2,3,7,4};
    int i;
    
    quickSort(arr, 0, sizeof(arr)/sizeof(int)-1);//배열의 마지막 인덱스로 변경
    for(i = 0; i< sizeof(arr)/sizeof(int); i++){
        printf("%d ", arr[i]);
    }
    
    return 0;
}


void quickSort(int* arr, int start, int last){
    if(start<last){
        int pivot = partition(arr, last);
        quickSort(arr, start, pivot-1);
        quickSort(arr,pivot+1, last);
    }
    return ;
}


int partition(int* arr, int last){
    
    return 0;
}