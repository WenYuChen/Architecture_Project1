typedef unsigned int u32;
u32 dMemory[1024];

static void load_dMemory(void);
static void print_dMemory(void);

/******************************************************************************/
/*initialize                                                                  */
/******************************************************************************/
static void initialize_dMemory(void){
	memset(dMemory, 0, sizeof(dMemory));
}
/******************************************************************************/
/*INPUT                                                                      */
/******************************************************************************/
static void load_dMemory(void){
	FILE* fin = fopen(".\\input\\dimage.bin", "rb");
	int i = 0;
	while( !feof(fin) )
	{
		fread(&dMemory[i++], sizeof(char), 1, fin);
	}
	fclose(fin);
}
/******************************************************************************/
/*OUTPUT                                                                      */
/******************************************************************************/
static void print_dMemory(void)
{
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
