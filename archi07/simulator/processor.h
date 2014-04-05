#ifndef __PROCESSOR_H
#define __PROCESSOR_H

#include "./dmemory.h"
#include "./imemory.h"
#include "./vcpu.h"
#include "./valu.h"
#include "./r_type.h"
#include "./i_type.h"
#include "./j_type.h"
#include "./error_handler.h"
#include "./declaration_file_path.h"

typedef unsigned int u32;
int cycle;

/******************************************************************************/
/*Fetch                                                                       */
/******************************************************************************/
static u32 fetch(void){
	u32 fetch_instr = 0;
	fetch_instr += get_iMemory( get_PC()+3 );
	fetch_instr = (fetch_instr<<8);
	fetch_instr += get_iMemory( get_PC()+2 );
	fetch_instr = (fetch_instr<<8);
	fetch_instr += get_iMemory( get_PC()+1 );
	fetch_instr = (fetch_instr<<8);
	fetch_instr += get_iMemory( get_PC() );

	/*int i;
	for(i=vcpu.PC+3; i>=vcpu.PC; i--){
		fetch_instr = (fetch_instr<<8);
		fetch_instr += iMemory[i];
	}*/

	set_PC( get_PC()+4 );

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
	FILE* fout_regs = fopen(PATH_SNAPSHOT_rpt, "w");

	cycle = 0;
	print_regs( fout_regs );

	while( vcpu.PC < (entry_point+(iNum<<2)) ){
		error_clear();
		cycle++;

		instr = fetch();

		op = ( (instr>>26) & 0x3F );

		if( op==0x3F ){
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

		error_print( cycle );

		if( error_halt() ){
			break;
		}else{
			print_regs( fout_regs );
		}
	}

	fclose( fout_regs );
	error_close();
}

#endif
