//
//  generator.cpp
//  EmbeddedLab_GPS-Decoder
//
//  Created by Markus Heupel on 13.12.18.
//  Copyright © 2018 Markus Heupel. All rights reserved.
//

#include <stdio.h>
using namespace std;

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0])) // get size of array
#define registerLength 10
#define codeLength 1023

short reg1Bits[2] = {3,10};
short reg2Bits[6] = {2,3,6,8,9,10};
short satteliteBits[24][2] = {
    {2,  6}, //  1
    {3,  7}, //  2
    {4,  8}, //  3
    {5,  9}, //  4
    {1,  9}, //  5
    {2, 10}, //  6
    {1,  8}, //  7
    {2,  9}, //  8
    {3, 10}, //  9
    {2,  3}, // 10
    {3,  4}, // 11
    {5,  6}, // 12
    {6,  7}, // 13
    {7,  8}, // 14
    {8,  9}, // 15
    {9, 10}, // 16
    {1,  4}, // 17
    {2,  5}, // 18
    {3,  6}, // 19
    {4,  7}, // 20
    {5,  8}, // 21
    {6,  9}, // 22
    {1,  3}, // 23
    {4,  6}  // 24
};

// get bit at position
bool getBit(short reg, short position){
    return reg >> (registerLength - position) & 1U;
}

// get all bits from register and xor bits
bool xorBit(short reg, short position[], short positionsLength){
    bool xorBit = getBit(reg, position[0]);
    for(int i=1; i<positionsLength; i++){
        xorBit = xorBit ^ getBit(reg, position[i]);
    }
    return xorBit;
}

// prnting bits
void printRegister(short reg) {
    for (int i=6; i<16; i++) {
        printf("%d", !!((reg << i) & 0b1000000000000000));
    }
    printf("\n");
}

void generateCode(short satteliteID, int* chipSequence, int sumSignalSize){
    short register1 = 0b1111111111;
    short register2 = 0b1111111111;
    
    for(int i=0; i<sumSignalSize; i++){
        
        // get xor bits for sattelite
        bool xorBitReg1 = (getBit(register2, satteliteBits[satteliteID][0]) ^ getBit(register2, satteliteBits[satteliteID][1]));
        bool xorBitReg2 = getBit(register1, reg1Bits[1]); // get last bit
        bool chipBit = xorBitReg1 ^ xorBitReg2;
        
        // chip sequence
        if(chipBit == 0)
            chipSequence[i] = -1;
        else
            chipSequence[i] = chipBit;

        // register 1 shift
        bool shiftBitReg1 = xorBit(register1, reg1Bits, NELEMS(reg1Bits));
        register1 = (register1 >> 1) | (shiftBitReg1 << 9);
        
        // register 2 shift
        bool shiftBitReg2 = xorBit(register2, reg2Bits, NELEMS(reg2Bits));
        register2 = (register2 >> 1) | (shiftBitReg2 << 9);
    }
    return;
}


