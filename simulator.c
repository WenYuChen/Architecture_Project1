/******************************************************************************/
/*Computer Architecture                                                       */
/*PROJECT 1                                                                   */
/*資工系 101062231 林展逸                                                     */
/*資工系 101062138 陳文諭                                                     */
/*2014.03.29                                                                  */
/******************************************************************************/
#include <stdio.h>
#include <string.h>

typedef unsigned int u32;

struct vcpu {
	u32 reg[32];
	u32 PC;
};
struct rOperand {
	int rs;
	int rt;
	int rd;
	int shamt;
	int funct;
};
struct iOperand {
	int rs;
	int rt;
	int immediate;
};
struct jOperand {
	int address;
};

struct vcpu vcpu;
u32 dMemory[1024];
u32 iMemory[1024];

/******************************************************************************/
/*initialize                                                                  */
/******************************************************************************/
void initialize(){
	memset(vcpu.reg, 0, sizeof(vcpu.reg));
	memset(dMemory, 0, sizeof(dMemory));
	memset(iMemory, 0, sizeof(iMemory));
}
/******************************************************************************/
/*get register value                                                          */
/******************************************************************************/
u32 get_regs(int index){
	return vcpu.reg[index];
}
/******************************************************************************/
/*set register value                                                          */
/******************************************************************************/
void set_regs(int index, u32 value){
	if( index==0 ){
		/*
		printf("ERROR");
		...
		*/
	}else{
		vcpu.reg[index] = value;
	}
}
/******************************************************************************/
/*OUTPUT                                                                      */
/******************************************************************************/
static void print_regs(FILE* fout)
{
	/*
	fprintf(fout,"cycle %d\n", );
	...
	*/
	int i;
	for (i = 0; i < 32; i++) {
		fprintf(fout,"$%02d: 0x%08x\n", i, vcpu.reg[i]);
	}
	fprintf(fout,"PC: 0x%08x\n\n\n", vcpu.PC);
}
static void print_dMemory(FILE* fout)
{
	/*
	...
	*/
	int i;
	for(i=0; i<1024 && dMemory[i]!=0; i++){
		fprintf(fout,"dMemory[0x%3x]: %08x\n", i, dMemory[i]);
	}
}
static void print_iMemory(FILE* fout)
{
	/*
	...
	*/
	int i;
	for(i=0; i<1024 && iMemory[i]; i++){
		fprintf(fout,"iMemory[0x%3x]= %08x\n", i, iMemory[i]);
	}
}
/******************************************************************************/
/*int main()                                                                  */
/******************************************************************************/
int main(int argc, char const *argv[])
{
	/*initialize memory amd register*/
	initialize();

	/*Input*/
	FILE* fin = fopen(argv[1], "rb");
	int i = 0;
	while( !feof(fin) )
	{
		fread(&dMemory[i++], sizeof(u32), 1, fin);
	}
	fclose(fin);

	fin = fopen(argv[2], "rb");
	int i = 0;
	while( !feof(fin) )
	{
		fread(&iMemory[i++], sizeof(u32), 1, fin);
	}
	fclose(fin);

	/*process*/
	/*
	u32 instr;
	u32 op;
	...
	*/

	/*Output*/
	FILE* fout = fopen("Out_register.txt", "w");
	print_regs(fout);
	fclose(fout);

	fout = fopen("Out_dMemory.txt", "w");
	print_dMemory(fout);
	fclose(fout);

	fout = fopen("Out_iMemory.txt", "w");
	print_iMemory(fout);
	fclose(fout);

	return 0;
}
