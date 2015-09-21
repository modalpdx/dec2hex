//
// ************************************************************************************
// 
// Class     : PCC CS201
// Assignment: 2
// Project   : Decimal/Hex Converter - intConvert.c
//
// Student   : Erik Ratcliffe
// Date      : May 12, 2014
// 
// ************************************************************************************
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "intConvert.h"



// ----------------------------------------------------------------- 
// intToBin: converts an integer (base 10) number to binary (base 2)
// -----------------------------------------------------------------
//
// Input:
//   int    aDecimalNumber - an integer, range is platform-dependent
//   char * binaryBits     - pointer to array that holds bit values
//
// Returns:
//   int totalBits         - number of bits used in conversion (not padding bits)
//
// Notes:
//   - binaryBits[] array stores bits in low-to-high order
//   
int intToBin(int aDecimalNumber, char * binaryBits)
{

    int idx;               // Reused for all index values
    int totalBits = 0;     // Bits generated during binary conversion (no padding)
    int absDecimalNumber;  // Absolute value of decimal number
    int carry;             // Holds the carry value during binary addition
    int bitTotal;          // Holds total value of all bits during binary addition

    // Start by filling binaryBits[] with '0's
    //
    for(idx = 0; idx < INTBITS; idx++)
    {
        binaryBits[idx] = '0';
    }


    // Make sure we're starting with a positive decimal number
    //
    absDecimalNumber = abs(aDecimalNumber);

    // Convert decimal number to binary bits, tracking number of bits generated
    //
    idx = 0;
    while(absDecimalNumber > 0)
    {
        binaryBits[idx++] = (absDecimalNumber % 2 ? '1' : '0');
        absDecimalNumber /= 2;
        totalBits++;
    }

    // If the decimal number is negative, generate two's complement
    //
    if(aDecimalNumber < 0) 
    {
        // Step 1: "Flip" the bits.
        //
        idx = 0;
        while(idx < INTBITS)
        {
            binaryBits[idx] = (binaryBits[idx] == '0' ? '1' : '0');
            idx++;
        }

        // Step 2: Add 1.
        //
        carry = 1; // Let carry hold the initial 1 that is being added
        idx = 0;
        while(idx < INTBITS)
        {
            // The int value of a char is the char minus char value of '0'
            //
            bitTotal = (binaryBits[idx] - '0') + carry;

            // Replace bit values as necessary to accommodate for binary math
            //
            switch(bitTotal)
            {
                case 0:
                    binaryBits[idx] = '0';
                    carry = 0;
                    break;
                case 1:
                    binaryBits[idx] = '1';
                    carry = 0;
                    break;
                case 2:
                    binaryBits[idx] = '0';
                    carry = 1;
            }
            idx++;
        }

        // SPECIAL CASE, "max negative value" exception: binary value must be 1 
        // followed by all 0s.
        //
        if(aDecimalNumber == INT_MIN)
        {
            binaryBits[INTBITS - 1] = '1';
        }
    }

    return totalBits;

} // end of intToBin()



// ------------------------------------------------------------------- 
// toLittleEndian: converts byte ordering of binary array
// -------------------------------------------------------------------
//
// Input:
//   char * binaryBits     - pointer to array that holds bit values
//
// Returns:
//   nothing
//
// Notes:
//   none
// 
void toLittleEndian(char * binaryBits)
{

    int  byteIdx;                   // index of byte in bytes[]
    int  bitIdx;                    // index of bits within a byte in bytes[]
    int  binIdx;                    // index to iterate through binaryBits[]
    int  iterations = INTBITS / 8; 
    char bytes[iterations][9];      // temp array to hold reordered bytes

    // populate the temporary bytes[] array in little endian order
    //
    binIdx = 0;
    for(byteIdx = iterations - 1; byteIdx >= 0; byteIdx--)
    {
        for(bitIdx = 0; bitIdx < 8; bitIdx++)
        {
          bytes[byteIdx][bitIdx] = binaryBits[binIdx++];
        }
    }

    // write bytes[] values back to binaryBits[]
    //
    binIdx = 0;
    for(byteIdx = 0; byteIdx < iterations; byteIdx++)
    {
        for(bitIdx = 0; bitIdx < 8; bitIdx++)
        {
          binaryBits[binIdx++] = bytes[byteIdx][bitIdx];
        }
    }

} // end of toLittleEndian()



// ----------------------------------------------------------------------- 
// intToHexChar: converts an integer 0-15 to a hexadecimal (base 16) value
// -----------------------------------------------------------------------
//
// Input:
//   int myInt      - decimal value 0-15 to convert to a hexadecimal value
//
// Returns:
//   hexChar        - hexadecimal character representation of myInt
//
// Notes:
//   none
// 
char intToHexChar(int myInt)
{

    int absInt = abs(myInt);               // absolute value of myInt
    char hexChar;                           

    // determine the correct hex value for myInt
    //
    if((absInt >= 0) && (absInt < 16))
    {
      if(abs(myInt) > 9)
      {
          // all values from 10-15 need to be changed to letters A-F
          //
          switch(myInt)
          {
            case 10:
              hexChar = 'A';
              break;
            case 11:
              hexChar = 'B';
              break;
            case 12:
              hexChar = 'C';
              break;
            case 13:
              hexChar = 'D';
              break;
            case 14:
              hexChar = 'E';
              break;
            case 15:
              hexChar = 'F';
          }
      }
      else
      {
          hexChar = myInt + '0';
      }
    }
    else
    {
        hexChar = '-'; // error condition, out of range
    }

  return hexChar;

} // end of intToHexChar()



// ------------------------------------------------------------------- 
// binToHex: converts a binary value (base 2) to hexadecimal (base 16)
// -------------------------------------------------------------------
//
// Input:
//   char * binaryBits     - pointer to array that holds bit values
//   char * hexBits        - pointer to array that holds hex values
//
// Returns:
//   nothing
//
// Notes:
//   - binaryBits[] array needs to be sorted already in the correct byte order
//     for little- or big-endian. This function does no endian conversions.
// 
void binToHex(char * binaryBits, char * hexBits)
{

    int binIdx;                    // index that iterates through binaryBits[]
    int hexIdx;                    // index of element in hexBits[]
    int binExp;                    // binary exponent (position based)
    int decResult;                 // holds decimal value of bits
    int decTotal;                  // final decimal number to convert to hex value
    int iterations = HEXINTBITS;   // max iterations, one for each hex character


    binIdx = INTBITS - 1;
    hexIdx = 0;
    while(iterations > 0)
    {
        decTotal = decResult = 0;  // reset accumulators

        for(binExp = 3; binExp >= 0; binExp--) // highest binary exponent is 3
        {
            decResult = (binaryBits[binIdx] - '0') * pow(2, binExp); // Decimal value of bit
            decTotal += decResult;

            binIdx--;              // prepare to read next bit
        }

        hexBits[hexIdx] = intToHexChar(decTotal);
        iterations--;
        hexIdx++;
    }

} // end of binToHex()

