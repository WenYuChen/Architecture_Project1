#include<stdio.h>
#include<string.h>

int main(void){
	FILE* f1 = fopen("..\\input\\snapshot.rpt", "r");
	FILE* f2 = fopen("..\\Out_register.txt", "r");
	FILE* fout = fopen(".\\Out_compare.txt", "w");

	int cycle = 0;
	char s1[100], s2[100];

	while( NULL!=fgets( s1, 100, f1 ) ){
		fprintf(fout,"cycle %d\n", cycle);

		fgets( s2, 100, f2 );

		int flag = 1;

		int i;
		for(i=0; i<35; i++){
			fgets( s1, 100, f1 );
			fgets( s2, 100, f2 );
			if( strcmp( s1, s2 )!=0 ){
				flag = 0;
				fprintf(fout,"snapshot:   %s",s1);
				fprintf(fout,"Out_regs:   %s",s2);
			}
		}

		if( flag ){
			fprintf(fout,"----------------------------------Correct\n");
		}

		cycle++;
	}

	fclose( f1 );
	fclose( f2 );
	fclose( fout );

	return 0;
}
