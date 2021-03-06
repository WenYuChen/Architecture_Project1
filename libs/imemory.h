#ifndef __IMEMORY_H
#define __IMEMORY_H

#define PATH_iimage ".\\input\\iimage.bin"

typedef unsigned int u32;
u32 iMemory[1024];
u32 iNum;
u32 entry_point;

static void initialize_iMemory(void){
	memset(iMemory, 0, sizeof(iMemory));
}
static void load_iMemory(void){
	FILE* fin = fopen(PATH_iimage, "rb");
	/*
	The first four bytes indicates the initial value of PC,
	i.e. the starting address to load the instruction image.
	*/
	if( !feof(fin) ){
		fread(&entry_point, sizeof(u32), 1, fin);
		vcpu.PC = entry_point;
	}
	/*
	The next four bytes specify the number of words to be loaded into I memory.
	*/
	if( !feof(fin) ){
		fread(&iNum, sizeof(u32), 1, fin);
	}
	/*
	Start load data into I memory.
	*/
	int i = vcpu.PC;
	while( !feof(fin) )
	{
		fread(&iMemory[i++], sizeof(char), 1, fin);
	}
	fclose(fin);
}
static void print_iMemory(void){
	FILE* fout = fopen("Out_iMemory.txt", "w");
	/*
	...
	*/
	int i;
	for(i=0; i<1024; i++){
		fprintf(fout,"iMemory[0x%3x]: %02x\n", i, iMemory[i]);
	}
	fclose(fout);
}

#endif
