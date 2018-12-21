//
//  main.cpp
//  EmbeddedLab_GPS-Decoder
//
//  Created by Markus Heupel on 12.12.18.
//  Copyright © 2018 Markus Heupel. All rights reserved.
//

#include <fstream>
#include <stdio.h>
#include "../includes/fileReader.hpp"
#include "../includes/generator.hpp"
#include "../includes/correlation.hpp"
using namespace std;

#define satellites 24
#define sumSignalSize 1023
#define chipSequenceSize 1023

int main(int argc, const char* argv[]) {
    
    const char* filename = argv[1];
    //const char* filename = "../assets/signal7.txt";
    int sumSignal[sumSignalSize];
    int chipSequence[chipSequenceSize];
    int shift;
    
    // read file, store in sumSignal
    int fs = read(filename, sumSignal);
    // stop if file is empty
    if(fs != 0)
        return -1;

    // loop through all satellites
    printf(".\n.\n.\n");
    for(int id=0;id<satellites;id++){
        
        // generate chip sequence for every satellite
        generateCode(id, chipSequence, sumSignalSize);
        
        // get shift info for asynchronous CDMA
        shift = correlate(sumSignal, chipSequence);
        
        // peek found for satellite
        if(shift != -1){
            printf("Satellite %d has sent bit %d (delta = %d)\n", id+1, getMessageBit(), shift);
        }
    }
    printf(".\n.\n.\n");
    
    return 0;
}
