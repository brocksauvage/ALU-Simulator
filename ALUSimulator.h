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

//
//	A subroutine that simulates an Arithmetic Logic Unit
//
//  Parameters: theRegisterFile: the file whose value will be read and written to
//              OpCode: the operation code for the MIPS instructions
//              Rs: the first register
//              Rt: the second register
//              Rd: the destination register
//              ShiftAmt: the amount by which to shift a value
//              FunctionCode: the function code of a given instruction
//              Immediate Value: A value
//              Status: Basically useless
//
//  Brief: This fucntion will essentially use the OpCode and a switch statement to determine
//         the instructions (with differeing opCodes) to be executed.
//
extern void ALUSimulator( RegisterFile theRegisterFile,
                         uint32_t OpCode,
                         uint32_t Rs, uint32_t Rt, uint32_t Rd,
                         uint32_t ShiftAmt,
                         uint32_t FunctionCode,
                         uint32_t ImmediateValue,
                         uint32_t* Status );

//
//	A subroutine that assists the ALUSimulator function in determining instructions
//
//  Parameters: theRegisterFile: the file whose value will be read and written to
//              OpCodeResult: the operation code for the MIPS instructions
//              Rs: the first register
//              Rt: the second register
//              Rd: the destination register
//              ShiftAmt: the amount by which to shift a value
//              FunctionCodeResult: the function code of a given instruction
//              Immediate Value: A value
//
//  Brief: This function will essentially use the FunctionCodeResult and a switch statement to determine
//         the instructions (with the same OpCodes, but different Function codes) to be executed.
//
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