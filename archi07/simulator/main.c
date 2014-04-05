/******************************************************************************/
/*Computer Architecture                                                       */
/*PROJECT 1                                                                   */
/*資工系 101062231 林展逸                                                     */
/*資工系 101062138 陳文諭                                                     */
/*2014.03.29                                                                  */
/******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "./processor.h"

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
	process();

	return 0;
}
