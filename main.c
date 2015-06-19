//
// ************************************************************************************
// 
// Class     : PCC CS201
// Assignment: 2
// Project   : Decimal/Hex Converter - main.c
//
// Student   : Erik Ratcliffe
// Date      : May 12, 2014
// 
// ************************************************************************************
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include "intConvert.h"



// ----------------------------------------- 
// main function
// -----------------------------------------
//
// Input:
//   none
//
// Returns:
//   0/1 - success/failure
//
// Notes:
//   - character input is not handled yet.
// 
int main(void)
{
  int  idx;                      // general purpose index
  int  inputIdx;                 // index specific to stepping through user input 
  int  bigEndian = 0;            // flag for big endian: 0 = false, 1 = true
  int  jump;                     // amount to jump when parsing user input string
  int  decimalNumber;            // final integer to convert
  long long inputDecimalNumber;  // temp placeholder for value to convert 

  char ch, scrap;                // holds prompt for big endian conversion + stdin flush

  char decIntBits[INTBITS + 1];  // holds bits that describe decimal integer
  char hexBits[HEXINTBITS + 1];  // holds hex value for decIntBits[]

  char promptString[] = "Enter a number (0 to cancel): "; 

  int  maxchars = 100;           // maximum number of characters in user input
  char inputNumbers[maxchars];   // holds user input


  // Prompt for big endian or little endian output
  //
  printf("Byte ordering is set to little endian. Switch to big endian? (Y = yes): ");
  scanf(" %c", &ch);
  while ((scrap = getchar()) != '\n' && scrap != EOF);  // flush stdin
  if(tolower(ch) == 'y')
  {
      bigEndian = 1;
      printf("Byte order: big-endian\n");
  }
  else
  {
      printf("Byte order: little-endian\n");
  }


  // Prompt for a number. Loop until we get a number we can use, then
  // display the binary number and break the loop.
  //
  while(1 && (inputDecimalNumber != 0))
  {
      printf("\n%s", promptString);

      if(fgets(inputNumbers, sizeof(inputNumbers), stdin) != NULL)  // no valid characters input?
      {
          for(inputIdx = 0; (sscanf(&inputNumbers[inputIdx], "%25lld%n", &inputDecimalNumber, &jump) != EOF) && (jump <= maxchars); inputIdx += jump)
          {
              // If the number entered was outside the min/max range of regular integers...
              //
              if( inputDecimalNumber < INT_MIN || inputDecimalNumber > INT_MAX )
              {
                  printf("Number is outside of integer range (%d to %d).\n", INT_MIN, INT_MAX);
              }
              // If we get this far, we have a valid number. Convert it, then
              // display it and break from the while loop.
              //
              else if( inputDecimalNumber != 0 )
              {
                  decimalNumber = (int)inputDecimalNumber;   // convert input number to normal int
                  intToBin(decimalNumber, decIntBits);       // convert int to binary


                  // print the integer being converted
                  //
                  printf("%10d ", decimalNumber);

                  // convert to big endian byte ordering if requested
                  //
                  if(bigEndian == 1)
                  {
                      toBigEndian(decIntBits);
                  }

          
                  // convert final bit array to hex
                  //
                  idx = 0;
                  while(idx < HEXINTBITS)
                  {
                      hexBits[idx++] = '0';                      
                  }

                  binToHex(decIntBits, hexBits);             // convert to hex
                  printf("0x");                              // start the hex string


                  // display the hex string
                  //
                  idx = 0;
                  while(idx < strlen(hexBits))
                  {
                      printf("%c", hexBits[idx]);
                      idx++;
                  }
                  printf("\n");
              }
          }
      }
      else
      {
          break;
      }
  }

  return 0;

} // end of main()

