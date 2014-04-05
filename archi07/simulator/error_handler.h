#ifndef __ERROR_HANDLER_H
#define __ERROR_HANDLER_H

#include <stdio.h>
#include <string.h>
#include "./declaration_error.h"
#include "./declaration_file_path.h"

static FILE* fout_error;
int error_list[4];
int should_halt;

static void error_clear(void){
	memset( error_list, 0, sizeof(error_list) );
	should_halt = 0;
}
static void error_report(int declar_error){
	error_list[declar_error] = 1;

	if( declar_error==ERROR_memory_address_overflow ){
		should_halt = 1;
	}
	if( declar_error==ERROR_data_misaligned ){
		should_halt = 1;
	}
}
static int error_halt(void){
	if( should_halt ){
		return 1;
	}else{
		return 0;
	}
}
static void error_print(int cycle){
	if( !fout_error ){
		fout_error = fopen( PATH_ERROR_DUMP_rpt, "w" );
	}

	if( error_list[ ERROR_write_to_register_zero ] ){
		fprintf( fout_error , "Write $0 error in cycle: %d\n", cycle);
	}
	if( error_list[ ERROR_number_overflow ] ){
		fprintf( fout_error , "Number overflow in cycle: %d\n", cycle);
	}
	if( error_list[ ERROR_memory_address_overflow ] ){
		fprintf( fout_error , "Address overflow in cycle: %d\n", cycle);
	}
	if( error_list[ ERROR_data_misaligned ] ){
		fprintf( fout_error , "Misalignment error in cycle: %d\n", cycle);
	}
}
static void error_close(void){
	fclose( fout_error );
}

#endif
