#ifndef __VCPU_H
#define __VCPU_H

#include "./error_handler.h"

#define $sp vcpu.reg[29]

typedef unsigned int u32;
struct vcpu {
	u32 reg[32];
	u32 PC;
};
struct vcpu vcpu;

static void initialize_vcpu(void){
	memset(vcpu.reg, 0, sizeof(vcpu.reg));
	vcpu.PC = 0x00000000;
}
static u32 get_regs(int index){
	return vcpu.reg[index];
}
void set_regs(int index, u32 value){
	if( index==0 ){
		/*ERROR*/
		error_report( ERROR_write_to_register_zero );
	}else{
		vcpu.reg[index] = value;
	}
}
static u32 get_PC(void){
	return vcpu.PC;
}
static void set_PC(u32 value){
	vcpu.PC = value;
}
#endif
