//*****************************************************************************
//--ALUSimulator.h
//
//		Author: 		Gary J. Minden
//		Organization:	KU/EECS/EECS 645
//		Date:			2017-04-22 (B70422)
//		Version:		1.0
//		Description:	This is the prototype for a simple ALU simulator
//		Notes:
//
//*****************************************************************************
//

extern void ALUSimulator( RegisterFile theRegisterFile,
                         uint32_t OpCode,
                         uint32_t Rs, uint32_t Rt, uint32_t Rd,
                         uint32_t ShiftAmt,
                         uint32_t FunctionCode,
                         uint32_t ImmediateValue,
                         uint32_t* Status );

void InternalSwitch( RegisterFile theRegisterFile,
                    uint32_t OpCodeResult,
                    uint32_t Rs, uint32_t Rt, uint32_t Rd,
                    uint32_t ShiftAmt,
                    uint32_t FunctionCodeResult,
                    uint32_t ImmediateValue );

// Generate a mask.
// Example usage: Want bits 0 to 6:
// r = generateMask(0,6);
// uint32_t result = r & numberGiven;
unsigned generateMask(unsigned a, unsigned b);