//
//  quicksort.c
//  jagual1
//
//  Created by Dayoungle on 2014. 11. 7..
//  Copyright (c) 2014년 dayoungle. All rights reserved.
//

#include <stdio.h>

int partition(int* arr, int size);
void quickSort(int* arr, int start, int last);
void swap (int* a, int* b);
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
        int q = partition(arr, last);
        quickSort(arr, start, q-1);
        quickSort(arr, q+1, last);
    }
    return ;
}

int partition(int* arr, int last){
    int index= -1;//왜 안될까요?
    int unCheckedPos= 0;
    int key = arr[last];
    for( ; unCheckedPos < last; unCheckedPos++){
        if(arr[unCheckedPos] <= key){
            index++;
            swap(&arr[unCheckedPos], &arr[index]);
        }
    }
    swap(&arr[last], &arr[index+1]);
    return index+1;
}

void swap (int* a, int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    
}