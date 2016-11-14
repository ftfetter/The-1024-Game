#include <stdio.h>
#include <stdlib.h>
#include "lib/gamelib.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	int modo=0;

	
	printf("Digite um modo <0 == teste><0 != jogo>: ");
	scanf("%d",&modo);
	
	startGame(NORMAL);
	/*
	if(modo)
	{
		startGame(NORMAL);
	}else
	{
		teste();
	}*/
	return 0;
}
