//
//  fileReader.cpp
//  EmbeddedLab_GPS-Decoder
//
//  Created by Markus Heupel on 20.12.18.
//  Copyright © 2018 Markus Heupel. All rights reserved.
//

#include <iostream>
#include "../includes/fileReader.hpp"
using namespace std;

int read(const char* filename, int* sumSignal){
    FILE *fs;
    char c;
    char buffer[5];
    
    fs = fopen(filename, "r");
    if(fs == NULL){
        cout << "file empty !!!" << endl;
        return -1;
    }
    
    // go through file and get every char
    int bufferIndex = 0;
    int sumIndex = 0;
    
    while(fs != NULL){
        c = fgetc(fs);
        
        if(c == EOF){
            break;
        }
        
        if(c == ' ' ){
            sumSignal[sumIndex] = atoi((const char*)buffer); // convert char buffer to int for negative numbers
            sumIndex++;
            bufferIndex = 0;
            bzero(buffer, 5); // clear buffer
        }else{
            buffer[bufferIndex] = c;
            bufferIndex++;
        }
    }
    return 0;
}




