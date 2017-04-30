
//
//	A subroutine that simulates an Arithmetic Logic Unit
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "alu_simulator.h"

void ALUSimulator( RegisterFile theRegisterFile,
							uint32_t OpCode,
							uint32_t Rs, uint32_t Rt, uint32_t Rd,
							uint32_t ShiftAmt,
							uint32_t FunctionCode,
							uint32_t ImmediateValue,
							uint32_t* Status )
{
	// Goes through the OpCode

	unsigned int OpCodeResult;
	unsigned int mask;
	
	mask = generateMask(0,5); // Generates mask for last 6 bits.
	OpCodeResult = mask & OpCode; // Applies mask. The OpCodeResult variable contains last 6 bits
	
	switch ( OpCodeResult )
	{
	case 0:
		// Goes through Function/Register Code
		
		unsigned int functionCodeResult;
		
		functionCodeResult = mask & FunctionCode; // Applies mask. The functionResult variable contains last 6 bits
		
		switch ( functionCodeResult )
		{
		case 0:
			//function
			break;
		case 0:
			// redundant function
			break;
		case 2:
			//SRL function -CHECK
			// Shift Word Right Logical
			// Rt >> ShiftAmt where ShiftAmt is the bit shift count
			// Store in Rd -STORE
			
			unsigned int result;
			
			// Shifts the bits on Rt to the right by ShiftAmt
			result = (int)((unsigned int)Rt >> ShiftAmt);
			
			// Prints the SRL instruction result
			printf("%i", result);
			
			break;
		case 3:
			//SRA function -CHECK
			// Shift Word Right Arithmetic
			// Rt >> ShiftAmt preserve the sign bit
			// Store in Rd -STORE
			
			unsigned int result;
			
			if(Rt < 0 && ShiftAmt > 0)
			{
				// Shift Rt bits to right ShiftAmt OR NOT(NOT 0(unsigned) shift right ShiftAmt)
				// ~0u is 000...000 to 111...111
				result = Rt >> ShiftAmt | ~(~0u >> ShiftAmt);
			}
			else
			{
				result = Rt >> ShiftAmt;
			}
			
			// Prints the SRA instruction result
			printf("%i", result);
			
			break;
		case 4:
			//SLLV function
			// Shift Word Left Logical Variable
			// Rt << Rs
			// Store in Rd
			
			unsigned int result;
			
			// Shifts the bits on Rt to the left by Rs
			result = (int)((unsigned int)Rt << Rs);
			
			// Prints the SLLV instruction result
			printf("%i", result);
			
			break;
		case 6:
			//SRLV function
			// Shift Word Right Logical Variable
			// Rt >> Rs
			// Store in Rd
			
			unsigned int result;
			
			// Shifts the bits on Rt to the right by Rs
			result = (int)((unsigned int)Rt >> Rs);
			
			// Prints the SRL instruction result
			printf("%i", result);
			
			break;
		case 16:
			//MFHI function
			// Move From HI Register
			// Copies the special purpose HI register to Rd
			// Rd <- HI
			
			//
			
			break;
		case 18:
			//MFLO function
			
			
			//
			
			break;
		case 24:
			//MULT function
			// Multiply Word
			// Rs * Rt
			// Store in (LO, HI)
			
			unsigned int result;
			
			unsigned int reg = 0;
			while(y != 0)
			{
				if(y & 1)
				{
					reg += Rs;
				}
				// Left shifts and then assigns to Rs variable
				Rs <<= 1;
				// Right shifts and then assigns to Rt variable
				Rt >>= 1;
			}
			result = reg;
			
			printf("%i", result);
			
			break;
		case 25:
			//function
			break;
		case 26:
			//function
			break;
		case 27:
			//function
			break;
		case 32:
			//ADD function
			// rs + rt
			
			// Iterate until carry is 0
			while(Rt !=0)
			{
				// carry contains common bits of Rs and Rt
				unsigned int carry = Rs & Rt;
				
				// Sum of bits of Rs and Rt where at least one of the bits is not set
				Rs = Rs ^ Rt; // The ^ operator is for XOR
				
				// carry is shifted by one so that adding it to Rt gives the required sum
				Rt = carry << 1;
			}
			
			// Print Rs
			printf("%i", Rs);
			
			break;
		case 33:
			//function
			break;
		case 34:
			//function
			break;
		case 35:
			//function
			break;
		case 36:
			//function
			break;
		case 37:
			//function
			break;
		case 38:
			//function
			break;
		case 42:
			//function
			break;
		case 43:
			//function
			break;
		default:
			printf("Invalid FunctionCode!");
			break;
		}
	  break;
	case 8:
		//function
		break;
	case 9:
		//function
		break;
	case 10:
		//function
		break;
	case 11:
		//function
		break;
	default:
		printf("Invalid OpCode!");
		break;
	}
}

//
//	HELPER METHODS
//

// Generate a mask.
// Example usage: Want bits 0 to 6:
// r = generateMask(0,5);
// uint32_t result = r & numberGiven;
unsigned generateMask(unsigned a, unsigned b)
{
   unsigned r = 0;
   unsigned i;
   for (i=a; i<=b; i++)
       r |= 1 << i;

   return r;
}

// Prints bits of an int
// Example usage: printBits(5);
void printBits(unsigned int num)
{
	unsigned int size = sizeof(unsigned int);
    unsigned int maxPow = 1<<(size*8-1);
    printf("MAX POW : %u\n",maxPow);
    int i=0,j;
    for(;i<size*8;++i){
        // print last bit and shift left.
        printf("%u",num&maxPow ? 1 : 0);
        num = num<<1;
    }
}

int main()
{
	unsigned int someNumber;
	someNumber = 12;
	unsigned int  result;
	unsigned int mask;
	
	mask = generateMask(0,5);
	result = mask & someNumber;
	
        printBits(someNumber);
        printf("\n\n");
        printBits(mask);
        printf("\n\n");
        printBits(result);
	
	
	return 0;
}




//
//
//




