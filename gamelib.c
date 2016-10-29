#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "gamelib.h"

player readPlayer()
{
	player plyr;
	char name[TAM];
	int score, win;
	
	fflush(stdin);
	printf("Digite o nome de jogador: ");
	gets(name);
	printf("Digite a pontuacao do jogador: ");
	scanf("%d", &score);
	printf("Digite algum valor (!=0) caso o jogador ganhou: ");
	scanf("%d", &win);
	
	strcpy(plyr.name,name);
	plyr.score = score;
	plyr.win = win;
	
	return plyr;
}

block readBlock()
{
	block blck;
	int color, valor;
	
	printf("Digite um valor para a cor do bloco: ");
	scanf("%d", &color);
	printf("Digite um valor para o bloco: ");
	scanf("%d", &valor);
	
	blck.color = color;
	blck.valor = valor;
	
	return blck;
}

void printPlayer(player plyr)
{
	if(plyr.win)
	{
		printf("Nome: %s || Pontuacao: %d || Ganhou? Sim", plyr.name, plyr.score);
	}else
	{
		printf("Nome: %s || Pontuacao: %d || Ganhou? Não", plyr.name, plyr.score);
	}
	
}

void printBlock(block blck)
{
	printf("Cor: %d || Valor: %d", blck.color, blck.valor);
}

void addScore(player plyr, int score)
{
	plyr.score += score;
}

void addBlock(coordinate coord, int height, int width, block blck)
{
	int h=0, w=0, i=0, j=0;
	
	h = height/2;
	w = width/2;
	
	textbackground(blck.color);
	
	for(i=0; i<height; i++)
	{
		for(j=0; i<width; j++)
		{
			coord.x -= w+j;
			coord.y -= h+i;
			
			gotoxy(coord.x,coord.y);
			printf(" ");
		}
	}
}

void showPlayers(player vecPlyr[], int score, int qntPlyr)
{
	int i;
	
	for(i=0; i<qntPlyr; i++)
	{
		if(vecPlyr[i].score>=score)
		{
			printf("%s", vecPlyr[i].name);
		}
	}
}
