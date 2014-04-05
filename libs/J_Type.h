#ifndef __J_TYPE_H
#define __J_TYPE_H

#include ".\vcpu.h"

typedef unsigned int u32;

struct jOperand{
	u32 address;
};

struct jOperand joperand;

/******************************************************************************/
/*J-type instruction                                                          */
/******************************************************************************/
static void emu_j(void){
    u32 pc = ( get_PC() &0xF0000000 );
    u32 C = ( joperand.address<<2 );
    set_PC( pc | C );
}
static void emu_jal(void){
	set_regs( 31, get_PC() );

    u32 pc = ( get_PC() &0xF0000000 );
    u32 C = ( joperand.address<<2 );
    set_PC( pc | C );
}
/******************************************************************************/
/*J-type decoder                                                              */
/******************************************************************************/
static void j_decoder(u32 instr){
    u32 opcode = ( (instr >> 26) & 0x3F );
    joperand.address = ( instr & 0x03FFFFFF );

    if(opcode == 0x02){
        emu_j();
    }
    else{
        emu_jal();
    }
}

#endif
