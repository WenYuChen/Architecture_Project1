/******************************************************************************/
/*Computer Architecture                                                       */
/*PROJECT 1                                                                   */
/*��u�t 101062231 �L�i�h                                                     */
/*��u�t 101062138 �����                                                     */
/*2014.03.29                                                                  */
/******************************************************************************/
#include <stdio.h>
#include <string.h>
#include ".\libs\dmemory.h"
#include ".\libs\imemory.h"
#include ".\libs\vcpu.h"

/******************************************************************************/
/*int main()                                                                  */
/******************************************************************************/
int main(int argc, char const *argv[])
{
	/*initialize memory amd register*/
	initialize_dMemory();
	initialize_iMemory();
	initialize_vcpu();

	/*Input*/
	load_dMemory();
	load_iMemory();

	/*process*/
	/*
	u32 instr;
	u32 op;
	...
	*/

	/*Output*/
	print_regs();
	print_dMemory();
	print_iMemory();

	return 0;
}
