typedef unsigned int u32;
u32 iMemory[1024];

static void load_iMemory(void);
static void print_iMemory(void);

/******************************************************************************/
/*initialize                                                                  */
/******************************************************************************/
static void initialize_iMemory(void){
	memset(iMemory, 0, sizeof(iMemory));
}
/******************************************************************************/
/*INPUT                                                                      */
/******************************************************************************/
static void load_iMemory(void){
	FILE* fin = fopen(".\\input\\iimage.bin", "rb");
	int i = 0;
	while( !feof(fin) )
	{
		fread(&iMemory[i++], sizeof(char), 1, fin);
	}
	fclose(fin);
}
/******************************************************************************/
/*OUTPUT                                                                      */
/******************************************************************************/
static void print_iMemory(void)
{
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
