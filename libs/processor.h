#ifndef __PROCESSOR_H
#define __PROCESSOR_H

#include ".\dmemory.h"
#include ".\imemory.h"
#include ".\vcpu.h"
#include ".\valu.h"
#include ".\r_type.h"
#include ".\i_type.h"
#include ".\j_type.h"
typedef unsigned int u32;
int cycle;

/******************************************************************************/
/*Fetch                                                                       */
/******************************************************************************/
static u32 fetch(void){
	u32 fetch_instr = 0;
	int i;
	for(i=vcpu.PC+3; i>=vcpu.PC; i--){
		fetch_instr = (fetch_instr<<8);
		fetch_instr += iMemory[i];
	}

	/*
	...
	*/
	vcpu.PC += 4;

	return fetch_instr;
}
static void print_regs(FILE* fout_regs){
	fprintf(fout_regs,"cycle %d\n", cycle);

	int i;
	for (i = 0; i < 32; i++) {
		fprintf(fout_regs,"$%02d: 0x%08X\n", i, vcpu.reg[i]);
	}
	fprintf(fout_regs,"PC: 0x%08X\n\n\n", vcpu.PC);
}
/******************************************************************************/
/*Process                                                                     */
/******************************************************************************/
static void process(void){
	u32 instr;
	u32 op;
	FILE* fout_regs = fopen("Out_register.txt", "w");

	cycle = 0;
	print_regs( fout_regs );
//printf("iNUM=0x%08x\n", iNum);
//printf("end=0x%08x\n", (entry_point+iNum));
	while( vcpu.PC < (entry_point+(iNum<<2)) ){
		cycle++;

		instr = fetch();

		op = ( (instr>>26) & 0x3F );

//printf("PC=0x%08x\n", vcpu.PC);
printf("====================cycle %d====================\n", cycle);
printf("instr = 0x%08x\n", instr);
		if( op==0x3F ){
//printf("halt!\n");
			/*S-type*/
			break;/*halt*/
		}else if( op==0x00 ){
			/*R-type*/
			r_decoder( instr );
		}else if( op==0x02 || op==0x03 ){
			/*J-type*/
			j_decoder( instr );
		}else{
			/*I-type*/
			i_decoder( instr );
		}

		print_regs( fout_regs );
	}

	fclose( fout_regs );
}

#endif
