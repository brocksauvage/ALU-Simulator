
//
//	A subroutine that simulates an Arithmetic Logic Unit
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "alu_simulator.h"

//NOTE:ADDU AND ADD LOOK THE SAME

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
	
    printf( ">>ALU: Opcode: %02X; Rs: %02X; Rt: %02X; Rd: %02X;\n",
           OpCode,
           Rs,
           Rt,
           Rd );
				
    printf( ">>>>ALU: ShiftAmt: %02X; FunctionCode: %02X; ImmediateValue: %04X;\n",
           ShiftAmt,
           FunctionCode,
           ImmediateValue );
    
	switch ( OpCodeResult )
	{
    unsigned int functionCodeResult;
    unsigned int result;
            
	case 0:
		// Goes through Function/Register Code
            
		functionCodeResult = mask & FunctionCode; // Applies mask. The functionResult variable contains last 6 bits
		
		switch ( functionCodeResult )
		{
		case 0:
			//function
			break;
		case 2:
			//SRL function -CHECK
			// Shift Word Right Logical
			// Rt >> ShiftAmt where ShiftAmt is the bit shift count
			// Store in Rd -STORE
			
			
			
			// Shifts the bits on Rt to the right by ShiftAmt
			result = (int)((unsigned int)Rt >> ShiftAmt);
			
			// Prints the SRL instruction result
			//printf("%i", result);
			
			//Rd = result;
			
			break;
		case 3:
			//SRA function -CHECK
			// Shift Word Right Arithmetic
			// Rt >> ShiftAmt preserve the sign bit
			// Store in Rd -STORE
			
			
			
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
			//printf("%i", result);
			
			//Rd = result;
			
			break;
		case 4:
			//SLLV function
			// Shift Word Left Logical Variable
			// Rt << Rs
			// Store in Rd
			
			
			// Shifts the bits on Rt to the left by Rs
			result = (int)((unsigned int)Rt << Rs);
			
			// Prints the SLLV instruction result
			//printf("%i", result);
			
			//Rd = result;
			
			break;
		case 6:
			//SRLV function
			// Shift Word Right Logical Variable
			// Rt >> Rs
			// Store in Rd
			
			// Shifts the bits on Rt to the right by Rs
			result = (int)((unsigned int)Rt >> Rs);
			
			// Prints the SRL instruction result
			//printf("%i", result);
			
			//Rd = result;
			
			break;
		case 16:
			//MFHI function
			// DO NOT IMPLEMENT
			
			break;
		case 18:
			//MFLO function
			// DO NOT IMPLEMENT
			
			break;
		case 24:
			//MULT function
			// DO NOT IMPLEMENT
			
			break;
		case 25:
			//MULTU function
			// DO NOT IMPLEMENT
			
			break;
		case 26:
			//DIV function
			// DO NOT IMPLEMENT
			
			break;
		case 27:
			//DIVU function
			// DO NOT IMPLEMENT
			
			break;
		case 32:
			//ADD function
			// Rs + Rt
			// Store in Rd
			// If overflow occurs, then trap and display error
			
			//OVERFLOW DETECTION NEEDS TO BE IMPLEMENTED
			
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
			//printf("%i", Rs);
			//Rd = Rs;
			
			break;
		case 33:
			//ADDU function
			// Rs + Rt
			// Store in Rd
			// Adds unsigned integers
			// Since Rs and Rt are unsigned, we can just straight-up add them.
			// Iterate until carry is 0
			
			Rd = Rs + Rt;
			
			break;
		case 34:
			//SUB function
			// Rs - Rt
			// Store in Rd
			// If overflow occurs, trap
			
			//
			// IMPLEMENT
			//
			
			break;
		case 35:
			//SUBU function
			// Rs - Rt
			// Store in Rd
			// Subtracts unsigned integers
			// No integer overflow exception occurs
			
			result = Rs - Rt;
			
			//Rd = result;
			
			break;
		case 36:
			//AND function
			// Rs & Rt
			// Store in Rd
			
			//Rd = Rs & Rd;
			
			break;
		case 37:
			//OR function
			// Rs | Rt
			// Store in Rd
			
			//Rd = Rs | Rt;
			
			break;
		case 38:
			//XOR function
			// Rs ^ Rt
			// Store in Rd
			
			//Rd = Rs^Rt;
			
			break;
		case 42:
			//SLT function
			// Rs < Rt
			// Store bool value (0 or 1) in Rd
			if(Rs < Rt)
			{
				//Rd = 1;
			}
			else
			{
				//Rd = 0;
			}
			
			break;
		case 43:
			//SLTU function
			// Rs < Rt
			// Store bool value (0 or 1) in Rd
			//((0 || Rs) < (0 || Rt))
			// || bitwise string concat? IMPLEMENT?
			if((0 || Rs) < (0 || Rt))
			{
				//Rd = 1;
			}
			else
			{
				//Rd = 0;
			}
			
			break;
		default:
			printf("Invalid FunctionCode!");
			break;
		}
	  break;
	case 8:
		//ADDI function
		// Instruction type I
		// To add a constant to a 32-bit integer. If overflow occurs, trap
		// Rs + ImmediateValue
		// Store in Rt
		
		//Rt = Rs + ImmediateValue;
		
		break;
	case 9:
		//ADDIU function
		// Instruction type I
		// To add a constant to a 32-bit integer.
		// Rs + ImmediateValue
		// Store in Rt
		// No Integer overflow exception occurs under any circumstances
		
		//Rt = Rs + ImmediateValue;
		
		break;
	case 10:
		//SLTI function
		// Instruction type I
		// To record the result of a less-than comparison with a constant.
		// Rs < ImmediateValue
		// Store in Rt
		
		//
		// IMPLEMENT
		//
		
		break;
	case 11:
		//SLTIU function
		// Instruction type I
		// To record the result of an unsigned less-than comparison with a constant.
		// Rs < ImmediateValue
		// Store in Rt
		
		//
		// IMPLEMENT
		//
		
		break;
	default:
		printf("Invalid OpCode!");
		break;
	}
    
    printf( ">>ALU: Opcode: %02X; Rs: %02X; Rt: %02X; Rd: %02X;\n",
           OpCode,
           Rs,
           Rt,
           Rd );
				
    printf( ">>>>ALU: ShiftAmt: %02X; FunctionCode: %02X; ImmediateValue: %04X;\n",
           ShiftAmt,
           FunctionCode,
           ImmediateValue );
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






//
//
//




