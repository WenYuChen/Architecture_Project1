#ifndef __DMEMORY_H
#define __DMEMORY_H

#include "./vcpu.h"
#include "./declaration_file_path.h"

typedef unsigned int u32;
u32 dMemory[1024];
u32 dNum;

static void initialize_dMemory(void){
	memset(dMemory, 0, sizeof(dMemory));
}
static void load_dMemory(void){
	FILE* fin = fopen(PATH_DIMAGE_bin, "rb");
	/*
	The first four bytes of dimage shows the initial value of $sp.
	*/
	if( !feof(fin) )
	{
		fread(&$sp, sizeof(u32), 1, fin);
	}
	/*
	The next four bytes specify the number of words to be loaded into D memory.
	*/
	if( !feof(fin) ){
		fread(&dNum, sizeof(u32), 1, fin);
	}
	/*
	Start load data into D memory.
	*/
	int i = 0;
	while( !feof(fin) )
	{
		fread(&dMemory[i++], sizeof(char), 1, fin);
	}
	fclose(fin);
}
static u32 get_dMemory(int index){
	u32 data = 0;
	int i;
	int error_flag = 0;
	for(i=index+3; i>=index; i--){
		if( 0<=i && i<1024 ){
			data = (data<<8);
			data += dMemory[i];
		}else{
			error_flag = 1;
			break;
		}
	}
	if( error_flag ){
		error_report( ERROR_memory_address_overflow );
	}

	return data;
}
static void set_dMemory(int index, u32 value){
	int i;
	for(i=index; i<=index+3; i++){
		if( 0<=i && i<1024 ){
			dMemory[i] = (value&0x000000FF) ;
			value = ( value>>8 );
		}
	}
}
/*For debug*/
static void print_dMemory(void){
	FILE* fout = fopen("Out_dMemory.txt", "w");
	/*
	...
	*/
	int i;
	for(i=0; i<1024; i++){
		fprintf(fout,"dMemory[0x%3x]: %02x\n", i, dMemory[i]);
	}
	fclose(fout);
}

#endif
