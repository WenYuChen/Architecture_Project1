#ifndef __I_TYPE_H
#define __I_TYPE_H

#include ".\opcode.h"
#include ".\vcpu.h"
#include ".\valu.h"

typedef unsigned int u32;

struct iOperand {
	int rs;
	int rt;
	int immediate;
};

struct iOperand ioperand;

static void print_itype(u32 instr){
	printf("-----------------------------------------\n");
	printf("instr = 0x%08x\n", instr);
	printf("op = 0x%08x\n", ( (instr>>26) & 0x3F ) );
	printf("rs = 0x%08x\n", ioperand.rs);
	printf("rt = 0x%08x\n", ioperand.rt);
	printf("immediate = 0x%08x\n", ioperand.immediate);
	printf("-----------------------------------------\n");
}

/******************************************************************************/
/*I-type instruction                                                          */
/******************************************************************************/
static void emu_addi(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = alu_add( rs, immediate );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_lw(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = get_dMemory( rs+immediate );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_lh(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = ( get_dMemory( rs+immediate ) & 0x0000FFFF );
	value_to_be_stored = alu_extend( value_to_be_stored, 16, 32 );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_lhu(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = ( get_dMemory( rs+immediate ) & 0x0000FFFF );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_lb(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = ( get_dMemory( rs+immediate ) & 0x000000FF );
	value_to_be_stored = alu_extend( value_to_be_stored, 8, 32 );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_lbu(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = ( get_dMemory( rs+immediate ) & 0x000000FF );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_sw(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = get_regs( ioperand.rt );
	set_dMemory( rs+immediate , value_to_be_stored );
}
static void emu_sh(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = ( get_regs( ioperand.rt ) & 0x0000FFFF ) + ( get_dMemory( rs+immediate ) & 0xFFFF0000 );
	set_dMemory( rs+immediate , value_to_be_stored );
}
static void emu_sb(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = ( get_regs( ioperand.rt ) & 0x000000FF ) + ( get_dMemory( rs+immediate ) & 0xFFFFFF00 );
	set_dMemory( rs+immediate , value_to_be_stored );
}
static void emu_lui(void){
	u32 value_to_be_stored = ( ioperand.immediate<<16 );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_andi(void){
	u32 rs = get_regs( ioperand.rs );
	u32 value_to_be_stored = ( rs & ioperand.immediate );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_ori(void){
	u32 rs = get_regs( ioperand.rs );
	u32 value_to_be_stored = ( rs | ioperand.immediate );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_nori(void){
	u32 rs = get_regs( ioperand.rs );
	u32 value_to_be_stored = ~( rs | ioperand.immediate );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_slti(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = alu_isSmaller( rs, immediate );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_beq(void){
	u32 rs = get_regs( ioperand.rs );
	u32 rt = get_regs( ioperand.rt );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	if( rs==rt ){
		set_PC( alu_add( get_PC() , (immediate<<2) ) );
	}
}
static void emu_bne(void){
	u32 rs = get_regs( ioperand.rs );
	u32 rt = get_regs( ioperand.rt );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	if( rs!=rt ){
		set_PC( alu_add( get_PC() , (immediate<<2) ) );
	}
}
/******************************************************************************/
/*I-type decoder                                                              */
/******************************************************************************/
static void i_decoder( u32 instr ){
	u32 op = ( (instr>>26) & 0x3F );
	ioperand.rs = ( (instr>>21) & 0x1F );
	ioperand.rt = ( (instr>>16) & 0x1F );
	ioperand.immediate = ( instr & 0xFFFF );

	if( op==OP_addi ){
printf("---------------------------------addi\n");
		emu_addi();
	}else if( op==OP_lw ){
printf("---------------------------------lw\n");
		emu_lw();
	}else if( op==OP_lh ){
printf("---------------------------------lh\n");
		emu_lh();
	}else if( op==OP_lhu ){
printf("---------------------------------lhu\n");
		emu_lhu();
	}else if( op==OP_lb ){
printf("---------------------------------lb\n");
		emu_lb();
	}else if( op==OP_lbu ){
printf("---------------------------------lbu\n");
		emu_lbu();
	}else if( op==OP_sw ){
printf("---------------------------------sw\n");
		emu_sw();
	}else if( op==OP_sh ){
printf("---------------------------------sh\n");
		emu_sh();
	}else if( op==OP_sb ){
printf("---------------------------------sb\n");
		emu_sb();
	}else if( op==OP_lui ){
printf("---------------------------------lui\n");
		emu_lui();
	}else if( op==OP_andi ){
printf("---------------------------------andi\n");
		emu_andi();
	}else if( op==OP_ori ){
printf("---------------------------------ori\n");
		emu_ori();
	}else if( op==OP_nori ){
printf("---------------------------------nori\n");
		emu_nori();
	}else if( op==OP_slti ){
printf("---------------------------------slti\n");
		emu_slti();
	}else if( op==OP_beq ){
printf("---------------------------------beq\n");
		emu_beq();
	}else if( op==OP_bne ){
printf("---------------------------------bne\n");
		emu_bne();
	}
}
#endif
