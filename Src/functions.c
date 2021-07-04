/*
 * functions.c
 *
 *  Created on: 25-Jun-2021
 *      Author: Rajlee
 */

#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include "main.h"

//RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
RCC_AHB1ENR_t volatile *const pClkCtrlReg 	 	= 	ADDR_REG_AHB1ENR;
//GPIO port mode register
GPIOx_MODE_t volatile *const pGPIODModeReg  	= 	ADDR_REG_GPIOD_MODE;
//GPIO port input data register
GPIOx_IDR_t volatile *const pInPutDataReg  		= 	ADDR_REG_GPIOD_ID;
//GPIO port output data register
GPIOx_ODR_t volatile *const pOutPutDataReg 		= 	ADDR_REG_GPIOD_OD;
//GPIO port pull-up/pull-down register
GPIOx_PUPDR_t volatile *const pPullUpDownReg  	= 	ADDR_REG_GPIOD_PUPD;

uint8_t count = 0, op_count = 0;
//uint8_t all_count = 0;
uint32_t array[10];
//char all[50];
char op[20];
int32_t A, ans;
int32_t B=0;

void delay(void)
{
	for(uint32_t i =0 ; i < DELAY_COUNT ; i++);
}

void print_array(void)
{
	for(int j = 0; j<count; j++)
	    {
	    printf("array[%d] = %lu\t", j, array[j]);
	    }
	printf("\n");
}

void clear_array(void){
	for(int k= 0 ; k<count; k++){
		array[k] = 0;
		}
	count = 0;
}

void clear_op(void){
	for(int k= 0 ; k<op_count; k++){
			op[k] = 0;
			}
	op_count = 0;
}

void clear_everything(void){
	clear_array();
	clear_op();
}

void addition(int32_t A, int32_t B){
	ans = B+A;
}
void subtraction(int32_t A,int32_t B){
	ans = B-A;
}
void multiplication(int32_t A,int32_t B){
	ans = B*A;
}
void division(int32_t A,int32_t B){
	ans = B/A;
}

void interrupt(void){
	//print_array();
	B = A;
	A = 0;
	for(int8_t i = 0; i<count; i++)
	{
		A = A*10 + array[i];
	}
	//printf("  A = %d\n",A);
	if(op_count>=2)
	{
		switch(op[op_count-2])
			{
			case '+': addition(A,B); __asm volatile ("MOV %0,R0":"=r"(A)); break;
			case '-': subtraction(A,B); __asm volatile ("MOV %0,R0":"=r"(A)); break;
			case 'x': multiplication(A,B); __asm volatile ("MOV %0,R0":"=r"(A)); break;
			case '/': division(A,B); __asm volatile ("MOV %0,R0":"=r"(A)); break;
			default : printf("Went in default case\n"); break;
			}
	}
	clear_array();
}

void answer(){
	printf("\t=\t%ld\n", ans);
	fflush(stdout);
	clear_everything();
}

void  make_all_rows_HIGH(void){
	pOutPutDataReg->pin_0 = HIGH;
	pOutPutDataReg->pin_1 = HIGH;
	pOutPutDataReg->pin_2 = HIGH;
	pOutPutDataReg->pin_3 = HIGH;
}

void check_R1(void){
	//make R1 LOW(PD0)(pin_0)
    pOutPutDataReg->pin_0  = LOW;

    //scan the columns
    //check C1(PD8)(pin_8) low or high
    if(pInPutDataReg->pin_8 == LOW){
    	//key is pressed
    	delay();
    	printf("1 ");
    	fflush(stdout);
    	array[count++] = 1;
    }

    //check C2(PD9) low or high
    if(pInPutDataReg->pin_9 == LOW){
    	//key is pressed
    	delay();
    	printf("2 ");
    	fflush(stdout);
    	array[count++] = 2;
    }

    //check C3(PD10) low or high
    if(pInPutDataReg->pin_10 == LOW){
    	//key is pressed
    	delay();
    	printf("3 ");
    	fflush(stdout);
    	array[count++] = 3;
    }

    //check C4(PD11) low or high
    if(pInPutDataReg->pin_11 == LOW){
    	//key is pressed
    	delay();
    	printf("\t+\t");
    	fflush(stdout);
    	op[op_count++] = '+';
    	interrupt();
    }
}

void check_R2(void){
	//make R2 LOW(PD1)
    pOutPutDataReg->pin_1 = LOW;

    //scan the columns
    //check C1(PD8) low or high
    if(pInPutDataReg->pin_8 == LOW){
    	//key is pressed
    	delay();
    	printf("4 ");
    	fflush(stdout);
    	array[count++] = 4;
    }

    //check C2(PD9) low or high
    if(pInPutDataReg->pin_9 == LOW){
    	//key is pressed
    	delay();
    	printf("5 ");
    	fflush(stdout);
    	array[count++] = 5;
    }

    //check C3(PD10) low or high
    if(pInPutDataReg->pin_10 == LOW){
    	//key is pressed
    	delay();
    	printf("6 ");
    	fflush(stdout);
    	array[count++] = 6;
    }

    //check C4(PD11) low or high
    if(pInPutDataReg->pin_11 == LOW){
    	//key is pressed
    	delay();
    	printf("\t-\t");
    	fflush(stdout);
    	op[op_count++] = '-';
    	interrupt();
    }
}

void check_R3(void){
	//make R3 LOW(PD2)
    pOutPutDataReg->pin_2 = LOW;

    //scan the columns
    //check C1(PD8) low or high
    if(pInPutDataReg->pin_8 == LOW){
    	//key is pressed
    	delay();
    	printf("7 ");
    	fflush(stdout);
    	array[count++] = 7;
    }

    //check C2(PD9) low or high
    if(pInPutDataReg->pin_9 == LOW){
    	//key is pressed
    	delay();
    	printf("8 ");
    	fflush(stdout);
    	array[count++] = 8;
    }

    //check C3(PD10) low or high
    if(pInPutDataReg->pin_10 == LOW){
    	//key is pressed
    	delay();
    	printf("9 ");
    	fflush(stdout);
    	array[count++] = 9;
    }

    //check C4(PD11) low or high
    if(pInPutDataReg->pin_11 == LOW){
    	//key is pressed
    	delay();
    	printf("\tx\t");
    	fflush(stdout);
    	op[op_count++] = 'x';
    	interrupt();
    }
}

void check_R4(void){
	//make R4 LOW(PD3)
	pOutPutDataReg->pin_3 = LOW;

    //scan the columns
    //check C1(PD8) low or high
    if(pInPutDataReg->pin_8 == LOW){
    	//key is pressed
    	delay();
    	clear_everything();
    	printf("\ncleared everything\n");
    }

    //check C2(PD9) low or high
    if(pInPutDataReg->pin_9 == LOW){
    	//key is pressed
    	delay();
    	printf("0 ");
    	fflush(stdout);
    	array[count++] = 0;
    }

    //check C3(PD10) low or high
    if(pInPutDataReg->pin_10 == LOW){
    	//key is pressed
    	delay();
    	op[op_count++] = '=';
    	interrupt();
    	answer();
    }

    //check C4(PD11) low or high
    if(pInPutDataReg->pin_11 == LOW){
    	//key is pressed
    	delay();
    	printf("	/	");
    	fflush(stdout);
    	op[op_count++] = '/';
    	interrupt();
    }
}


