#ifndef __R_TYPE_H
#define __R_TYPE_H

#include ".\funct.h"
#include ".\vcpu.h"
#include ".\valu.h"

typedef unsigned int u32;

struct rOperand {
	u32 rs;
	u32 rt;
	u32 rd;
	u32 shamt;
	u32 funct;
};
struct rOperand roperand;

/******************************************************************************/
/*R-type instruction                                                          */
/******************************************************************************/
static void emu_add(void){
	u32 rs = get_regs( roperand.rs );
    u32 rt = get_regs( roperand.rt );
    u32 value_to_be_stored = alu_add( rs, rt );
    set_regs( roperand.rd, value_to_be_stored );
}
static void emu_sub(void){
	u32 rs = get_regs( roperand.rs );
    u32 rt = get_regs( roperand.rt );
    rt = alu_complement( rt );
	u32 value_to_be_stored = alu_add( rs, rt );
    set_regs( roperand.rd, value_to_be_stored );
}
static void emu_and(void)
{
    u32 rs = get_regs( roperand.rs );
    u32 rt = get_regs( roperand.rt );
    u32 value_to_be_stored = ( rs & rt );
    set_regs( roperand.rd, value_to_be_stored );
}
static void emu_or(void)
{
    u32 rs = get_regs( roperand.rs );
    u32 rt = get_regs( roperand.rt );
    u32 value_to_be_stored = ( rs | rt );
    set_regs( roperand.rd, value_to_be_stored );
}
static void emu_xor(void)
{
    u32 rs = get_regs( roperand.rs );
    u32 rt = get_regs( roperand.rt );
    u32 value_to_be_stored = ( rs ^ rt );
    set_regs( roperand.rd, value_to_be_stored );
}
static void emu_nor(void)
{
    u32 rs = get_regs( roperand.rs );
    u32 rt = get_regs( roperand.rt );
    u32 value_to_be_stored = ~( rs | rt );
    set_regs( roperand.rd, value_to_be_stored );
}
static void emu_nand(void)
{
    u32 rs = get_regs( roperand.rs );
    u32 rt = get_regs( roperand.rt );
    u32 value_to_be_stored = ~( rs & rt );
    set_regs( roperand.rd, value_to_be_stored );
}
static void emu_slt(void){
	u32 rs = get_regs( roperand.rs );
    u32 rt = get_regs( roperand.rt );
    u32 value_to_be_stored = alu_isSmaller( rs, rt );
    set_regs( roperand.rd, value_to_be_stored );
}
static void emu_sll(void){
	u32 rt = get_regs( roperand.rt );
	u32 value_to_be_stored = ( rt << roperand.shamt );
	set_regs( roperand.rd, value_to_be_stored );
}
static void emu_srl(void){
	u32 rt = get_regs( roperand.rt );
	u32 value_to_be_stored = ( rt >> roperand.shamt );
	set_regs( roperand.rd, value_to_be_stored );
}
static void emu_sra(void){
	u32 rt = get_regs( roperand.rt );

	int sign_rt = ( rt>>31 );
	int i;
	for(i=0; i<roperand.shamt; i++){
		rt = ( rt>>1 );
		rt += (sign_rt<<31);
	}

	set_regs( roperand.rd, rt );
}
static void emu_jr(void){
	u32 rs = get_regs( roperand.rs );
	set_PC( rs );
}
/******************************************************************************/
/*R-type decoder                                                              */
/******************************************************************************/
static void r_decoder( u32 instr ){
	roperand.rs = ( (instr >> 21) & 0x1F );
    roperand.rt = ( (instr >> 16) & 0x1F );
    roperand.rd = ( (instr >> 11) & 0x1F );
    roperand.shamt = ( (instr >> 6) & 0x1F );
	roperand.funct = ( instr & 0x3F );

    if(roperand.funct == FUNCT_add){
printf("---------------------------------add\n");
        emu_add();
    }
    else if(roperand.funct == FUNCT_sub){
printf("---------------------------------sub\n");
        emu_sub();
    }
    else if(roperand.funct == FUNCT_and){
printf("---------------------------------and\n");
        emu_and();
    }
    else if(roperand.funct == FUNCT_or){
printf("---------------------------------or\n");
        emu_or();
    }
    else if(roperand.funct == FUNCT_xor){
printf("---------------------------------xor\n");
        emu_xor();
    }
    else if(roperand.funct == FUNCT_nor){
printf("---------------------------------nor\n");
        emu_nor();
    }
    else if(roperand.funct == FUNCT_nand){
printf("---------------------------------nand\n");
        emu_nand();
    }
    else if(roperand.funct == FUNCT_slt){
printf("---------------------------------slt\n");
        emu_slt();
    }
    else if(roperand.funct == FUNCT_sll){
printf("---------------------------------sll\n");
        emu_sll();
    }
    else if(roperand.funct == FUNCT_srl){
printf("---------------------------------srl\n");
        emu_srl();
    }
    else if(roperand.funct == FUNCT_sra){
printf("---------------------------------sra\n");
        emu_sra();
    }
    else if(roperand.funct == FUNCT_jr){
printf("---------------------------------jr\n");
        emu_jr();
    }
    /*是否做funct的例外處理*/
}
#endif
