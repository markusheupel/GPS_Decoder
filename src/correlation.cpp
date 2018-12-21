//
//  correlation.cpp
//  EmbeddedLab_GPS-Decoder
//
//  Created by Markus Heupel on 19.12.18.
//  Copyright © 2018 Markus Heupel. All rights reserved.
//

#include "../includes/correlation.hpp"
using namespace std;

#define codeSize 1023
#define highPeek 828
#define lowPeek -828

int messageBit;

int correlate(int sumSignal[], int chipSequence[]){
    
    // every shift possibility for asynchronous CDMA (<< 0, << 1, << 2 ...)
    for(int i=0; i<codeSize; i++){
        int bitProduct = 0;
        
        // sum of all products for every bit pair of sumSignal and chipSequence
        for(int j=0; j<codeSize; j++){
            bitProduct += sumSignal[((j + i) % 1023)] * chipSequence[j];
        }
        
        if(bitProduct >= highPeek){
            messageBit = 1;
            return i;
        }
        
        if(bitProduct <= lowPeek){
            messageBit = 0;
            return i;
        }
    }
    return -1;
}

int getMessageBit(){
    return messageBit;
}
