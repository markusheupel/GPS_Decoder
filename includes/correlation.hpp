//
//  correlation.hpp
//  EmbeddedLab_GPS-Decoder
//
//  Created by Markus Heupel on 19.12.18.
//  Copyright © 2018 Markus Heupel. All rights reserved.
//

#ifndef correlation_hpp
#define correlation_hpp

#include <stdio.h>

int correlate(int* sumSignal, int* chipSequence);
int getMessageBit();

#endif /* correlation_hpp */
