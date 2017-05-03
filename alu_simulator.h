
//
//	A subroutine that simulates an Arithmetic Logic Unit
//

#ifndef alu_simulator_h
#define alu_simulator_h

#include "RegisterFile_01.h"
//

void ALUSimulator( RegisterFile theRegisterFile,
							uint32_t OpCode,
							uint32_t Rs, uint32_t Rt, uint32_t Rd,
							uint32_t ShiftAmt,
							uint32_t FunctionCode,
							uint32_t ImmediateValue,
							uint32_t* Status );
							
// Generate a mask.
// Example usage: Want bits 0 to 6:
// r = generateMask(0,6);
// uint32_t result = r & numberGiven;
unsigned generateMask(unsigned a, unsigned b);

// Prints bits of an int
// Example usage: printBits(5);
void printBits(unsigned int num);


#endif

