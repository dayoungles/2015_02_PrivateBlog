//
//  calculateRankByFastTranspose.c
//  jagual1
//
//  Created by Dayoungle on 2014. 11. 11..
//  Copyright (c) 2014년 dayoungle. All rights reserved.
//

#include <stdio.h>
int calculateRanks(int* score, int* rank, int totalNum);

int main(){
    int score[] = {10,70,40,99,100};
    int rank[] = {};
    int totalNum = sizeof(score)/sizeof(int);
    int i;
    calculateRanks(score, rank, totalNum);
    
    for(i = 0; i< totalNum; i++){
        printf("%d ", rank[i]);
    }
    
    return 0;
}

int calculateRanks(int* score, int* rank, int totalNum){
    int scoreArr[102]={0};
    int i, j;
    int temp;
    
    
    if(!score || !rank) return 0;
    for(i = 0; i < totalNum; i++){
        scoreArr[score[i]] += 1;
    }

    for(j = 100; j >=0; j--){
        temp = score[j];
        score[j] = temp+ score[j+1];
        
    }
    for(i = 0; i< totalNum; i++){
        rank[i] = scoreArr[score[i]+1]+1;
    }
    
    
    return 1;
}