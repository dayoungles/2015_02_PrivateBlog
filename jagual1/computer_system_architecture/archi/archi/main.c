//
//  main.c
//  archi
//
//  Created by Dayoungle on 2014. 11. 2..
//  Copyright (c) 2014년 dayoungle. All rights reserved.
//

#include <stdio.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, int len);
int main(int argc, const char * argv[]) {
    int name = 123;//0x7b;
    int d = 1234;//0x4d2;
    printf("in hex: %x\n", name);
    show_bytes((byte_pointer)&name, sizeof(int));
    printf("in hex: %x\n", d);
    show_bytes((byte_pointer)&d, sizeof(int));
    return 0;
}
void show_bytes(byte_pointer start, int len){
    int i;

    for(i = 0; i< len; i++){
        printf("%.2x \n", start[i]);
    }
    printf("\n");
}




