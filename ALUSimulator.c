//*****************************************************************************
//--ALUSimulator.c
//
//		Author: 		Gary J. Minden
//		Organization:	KU/EECS/EECS 645
//		Date:			2017-04-22 (B70422)
//		Version:		1.0
//		Description:	This is the test standin for a simple ALU simulator
//		Notes:
//
//*****************************************************************************
//

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include <stdio.h>

#include "RegisterFile_01.h"
#include "ALUSimulator.h"

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
                    uint32_t ImmediateValue ) {
    
    uint32_t result = 0;

    switch(FunctionCodeResult)
    {
        case 0: //SLL
            
            result = theRegisterFile[Rt] << ShiftAmt;
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 2: //SRL
            
          result = theRegisterFile[Rt] >> ShiftAmt;
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 3: //SRA
            
            result = (signed)theRegisterFile[Rt] >> ShiftAmt;
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 4: //SLLV
            
            result = theRegisterFile[Rt] << theRegisterFile[Rs];
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 6: //SRLV
            
            result = theRegisterFile[Rt] >> theRegisterFile[Rs];
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 32: //ADD
            
            result = (signed)((signed)theRegisterFile[Rs] + (signed)theRegisterFile[Rt]);
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 33: //ADDU
            
            result = (unsigned)((unsigned)theRegisterFile[Rs] + (unsigned)theRegisterFile[Rt]);
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 34: //SUB
            
            result = (signed)((signed)theRegisterFile[Rs] - (signed)theRegisterFile[Rt]);
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 35: //SUBU
            
            result = (unsigned)((unsigned)theRegisterFile[Rs] - (unsigned)theRegisterFile[Rt]);
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 36: //AND
            
            result = theRegisterFile[Rs] & theRegisterFile[Rt];
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 37: //OR
            
            result = theRegisterFile[Rs] | theRegisterFile[Rt];
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 38: //XOR
            
            result = theRegisterFile[Rs] ^ theRegisterFile[Rt];
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 42: //SLT
            
            result = ((signed)theRegisterFile[Rs] < (signed)theRegisterFile[Rt]);
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        case 43: //SLTU
            
            result = (unsigned)((unsigned)theRegisterFile[Rs] < (unsigned)theRegisterFile[Rt]);
            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rd, result);
            break;
            
        default:
            printf("Invalid Function Code!");
            break;
    }
}

//A helper function used to generate the mask from bit a to bit b
unsigned generateMask(unsigned a, unsigned b)
{
    unsigned r = 0;
    unsigned i;
    for (i=a; i<=b; i++)
        r |= 1 << i;

    return r;
}

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
                         uint32_t* Status ) {
    
    //Used in testing
    /*printf( ">>ALU: Opcode: %02X; Rs: %02X; Rt: %02X; Rd: %02X;\n",
           OpCode,
           Rs,
           Rt,
           Rd );
    
    printf( ">>>>ALU: ShiftAmt: %02X; FunctionCode: %02X; ImmediateValue: %04X;\n",
           ShiftAmt,
           FunctionCode,
           ImmediateValue );*/

    unsigned int OpCodeResult;
    unsigned int mask;

    mask = generateMask(0,5); // Generates mask for last 6 bits.
    OpCodeResult = mask & OpCode; // Applies mask. The OpCodeResult variable contains last 6 bits

    unsigned int FunctionCodeResult = mask & FunctionCode;
    unsigned int result;

    uint32_t storeVal = 0;

    switch(OpCodeResult)
    {
        case 0: //NOOP
            
            InternalSwitch(theRegisterFile, OpCodeResult, Rs, Rt, Rd, ShiftAmt, FunctionCodeResult, ImmediateValue);
            break;
            
        case 8: //ADDI

            storeVal = (signed)((signed)theRegisterFile[Rs] + (signed)(int32_t)(int16_t)ImmediateValue);

            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rt, storeVal);

            break;
            
        case 9: //ADDIU

            storeVal = (unsigned)((unsigned)theRegisterFile[Rs] + (unsigned)(int32_t)(int16_t)ImmediateValue);

            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rt, storeVal);

            break;
            
        case 10: //SLTI

            if((signed)theRegisterFile[Rs] < (signed)(int32_t)(int16_t)ImmediateValue)
            {
                storeVal = 1;
            }
            else
            {
                storeVal = 0;
            }

            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rt, storeVal);

            break;
            
        case 11: //SLTIU

            if((unsigned)theRegisterFile[Rs] < (signed)(int32_t)(int16_t)ImmediateValue)
            {
                storeVal= 1;
            }
            else
            {
                storeVal = 0;
            }

            RegisterFile_Read(theRegisterFile, Rs, &theRegisterFile[Rs], Rt, &theRegisterFile[Rt]);
            RegisterFile_Write(theRegisterFile, 1, Rt, storeVal);

            break;
            
        default:
            printf("Invalid OpCode!");
            break;
    }

}
