#ifndef __I_TYPE_H
#define __I_TYPE_H

#include "./declaration_opcode.h"
#include "./vcpu.h"
#include "./valu.h"
#include "./error_handler.h"

typedef unsigned int u32;

struct iOperand {
	u32 rs;
	u32 rt;
	u32 immediate;
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
	u32 address = alu_add(rs,immediate);
	if( address%4!=0 ){
		error_report( ERROR_data_misaligned );
	}
	u32 value_to_be_stored = get_dMemory( address );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_lh(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 address = alu_add(rs,immediate);
	if( address%4!=0 ){
		error_report( ERROR_data_misaligned );
	}
	u32 value_to_be_stored = ( get_dMemory( address ) & 0x0000FFFF );
	value_to_be_stored = alu_extend( value_to_be_stored, 16, 32 );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_lhu(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 address = alu_add(rs,immediate);
	if( address%4!=0 ){
		error_report( ERROR_data_misaligned );
	}
	u32 value_to_be_stored = ( get_dMemory( address ) & 0x0000FFFF );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_lb(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = ( get_dMemory( alu_add(rs,immediate) ) & 0x000000FF );
	value_to_be_stored = alu_extend( value_to_be_stored, 8, 32 );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_lbu(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = ( get_dMemory( alu_add(rs,immediate) ) & 0x000000FF );
	set_regs( ioperand.rt, value_to_be_stored );
}
static void emu_sw(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = get_regs( ioperand.rt );
	u32 address = alu_add(rs,immediate);
	if( address%4!=0 ){
		error_report( ERROR_data_misaligned );
	}
	set_dMemory( address , value_to_be_stored );
}
static void emu_sh(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = ( get_regs( ioperand.rt ) & 0x0000FFFF ) + ( get_dMemory( rs+immediate ) & 0xFFFF0000 );
	set_dMemory( alu_add(rs,immediate) , value_to_be_stored );
}
static void emu_sb(void){
	u32 rs = get_regs( ioperand.rs );
	u32 immediate = alu_extend( ioperand.immediate, 16, 32 );
	u32 value_to_be_stored = ( get_regs( ioperand.rt ) & 0x000000FF ) + ( get_dMemory( rs+immediate ) & 0xFFFFFF00 );
	u32 address = alu_add(rs,immediate);
	if( address%2!=0 ){
		error_report( ERROR_data_misaligned );
	}
	set_dMemory( address , value_to_be_stored );
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
		emu_addi();
	}else if( op==OP_lw ){
		emu_lw();
	}else if( op==OP_lh ){
		emu_lh();
	}else if( op==OP_lhu ){
		emu_lhu();
	}else if( op==OP_lb ){
		emu_lb();
	}else if( op==OP_lbu ){
		emu_lbu();
	}else if( op==OP_sw ){
		emu_sw();
	}else if( op==OP_sh ){
		emu_sh();
	}else if( op==OP_sb ){
		emu_sb();
	}else if( op==OP_lui ){
		emu_lui();
	}else if( op==OP_andi ){
		emu_andi();
	}else if( op==OP_ori ){
		emu_ori();
	}else if( op==OP_nori ){
		emu_nori();
	}else if( op==OP_slti ){
		emu_slti();
	}else if( op==OP_beq ){
		emu_beq();
	}else if( op==OP_bne ){
		emu_bne();
	}else{
		printf("Undefine opcode!\n");
		printf("insrtuction : 0x08X\n", instr);
    }
}
#endif
