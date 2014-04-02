typedef unsigned int u32;
struct vcpu {
	u32 reg[32];
	u32 PC;
};
struct vcpu vcpu;

/******************************************************************************/
/*initialize                                                                  */
/******************************************************************************/
static void initialize_vcpu(void){
	memset(vcpu.reg, 0, sizeof(vcpu.reg));
	vcpu.PC = 0x00000000;
}

/******************************************************************************/
/*get register value                                                          */
/******************************************************************************/
static u32 get_regs(int index){
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
static void print_regs(void)
{
	FILE* fout = fopen("Out_register.txt", "w");
	/*
	fprintf(fout,"cycle %d\n", );
	...
	*/
	int i;
	for (i = 0; i < 32; i++) {
		fprintf(fout,"$%02d: 0x%08x\n", i, vcpu.reg[i]);
	}
	fprintf(fout,"PC: 0x%08x\n\n\n", vcpu.PC);
	fclose(fout);
}
