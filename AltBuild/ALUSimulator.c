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

void InternalSwitch( RegisterFile theRegisterFile,
                    uint32_t OpCodeResult,
                    uint32_t Rs, uint32_t Rt, uint32_t Rd,
                    uint32_t ShiftAmt,
                    uint32_t FunctionCodeResult,
                    uint32_t ImmediateValue ) {
    
    switch(FunctionCodeResult)
    {
        case 0: //SLL
            break;
        case 2: //SRL
            break;
        case 3: //SRA
            break;
        case 4: //SLLV
            break;
        case 6: //SRLV
            break;
        case 32: //ADD
            break;
        case 33: //ADDU
            break;
        case 34: //SUB
            break;
        case 35: //SUBU
            break;
        case 36: //AND
            break;
        case 37: //OR
            break;
        case 38: //XOR
            break;
        case 42: //SLT
            break;
        case 43: //SLTU
            break;
        default:
            printf("Invalid Function Code!");
            break;
    }
}

unsigned generateMask(unsigned a, unsigned b)
{
    unsigned r = 0;
    unsigned i;
    for (i=a; i<=b; i++)
        r |= 1 << i;
    
    return r;
}

extern void ALUSimulator( RegisterFile theRegisterFile,
                         uint32_t OpCode,
                         uint32_t Rs, uint32_t Rt, uint32_t Rd,
                         uint32_t ShiftAmt,
                         uint32_t FunctionCode,
                         uint32_t ImmediateValue,
                         uint32_t* Status ) {
    
    printf( ">>ALU: Opcode: %02X; Rs: %02X; Rt: %02X; Rd: %02X;\n",
           OpCode,
           Rs,
           Rt,
           Rd );
    
    unsigned int OpCodeResult;
    unsigned int mask;
		
    mask = generateMask(0,5); // Generates mask for last 6 bits.
    OpCodeResult = mask & OpCode; // Applies mask. The OpCodeResult variable contains last 6 bits
    
    unsigned int FunctionCodeResult = mask & FunctionCode;
    unsigned int result;
   
    switch(OpCodeResult)
    {
        case 0: //NOOP
            InternalSwitch(theRegisterFile, OpCodeResult, Rs, Rt, Rd, ShiftAmt, FunctionCodeResult, ImmediateValue);
            break;
        case 8: //ADDI
            break;
        case 9: //ADDIU
            break;
        case 10: //SLTI
            break;
        case 11: //SLTIU
            break;
        default:
            printf("Invalid OpCode!");
            break;
    }
				
    printf( ">>>>ALU: ShiftAmt: %02X; FunctionCode: %02X; ImmediateValue: %04X;\n",
           ShiftAmt,
           FunctionCode,
           ImmediateValue );
				
}