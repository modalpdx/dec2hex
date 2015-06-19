//
// ************************************************************************************
// 
// Class     : PCC CS201
// Assignment: 2
// Project   : Decimal/Hex Converter - intConvert.h
//
// Student   : Erik Ratcliffe
// Date      : May 12, 2014
// 
// ************************************************************************************
//

#ifndef INTCONVERT_H
#define INTCONVERT_H


#define INTBITS (sizeof(int) * 8)                       // Total # of bits in an integer.
                                                        // Can't be a const if it's used to
                                                        // initialize arrays (which it is)

#define HEXINTBITS (INTBITS / 4)                        // Total # of bits in a hex integer.


int  intToBin(int aDecimalNumber, char * binaryBits);   // Convert decimal to binary
void toBigEndian(char * binaryBits);                    // Convert from little endian (default) to big endian
char intToHexChar(int myInt);                           // Convert individual 0-15 integer to hex
void binToHex(char * binaryBits, char * hexBits);       // Convert integer to hex value


#endif
