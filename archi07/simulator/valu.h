#ifndef __VALU_H
#define __VALU_H

#include "vcpu.h"
#include "error_handler.h"

typedef unsigned int u32;

static u32 alu_add(u32 a, u32 b){
	u32 sum = a+b;

	int sign_a = ( a>>31 );
	int sign_b = ( b>>31 );
	int sign_sum = ( sum>>31 );
	if( sign_a==sign_b && sign_a!=sign_sum ){
		/*ERROR*/
		error_report( ERROR_number_overflow );
	}

	return sum;
}
static u32 alu_complement(u32 value){
	if( value==0x8000000 ){
		/*ERROR*/
		error_report( ERROR_number_overflow );
	}

	/*1's complement*/
	u32 ans = ~( value );
	/*2's complement*/
	ans += 1;
	return ans;
}
static u32 alu_extend(u32 value, int origin_size, int new_size){
	u32 sign = ( value>>(origin_size-1) );
	u32 sign_extend = 0;

	int i;
	for(i=origin_size+1; i<=new_size; i++){
		sign_extend = (sign_extend<<1)+sign;
	}
	sign_extend = ( sign_extend<<origin_size );

	return ( value+sign_extend );
}
static int alu_isSmaller(u32 a, u32 b){
	int sign_a = ( a>>31 );
	int sign_b = ( b>>31 );

	if( sign_a==sign_b ){
		if( a<b ){
			return 1;
		}else{
			return 0;
		}
	}else if( sign_a==0 && sign_b==1 ){
		return 0;
	}else{
		return 1;
	}
}

#endif
