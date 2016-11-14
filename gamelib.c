#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "gamelib.h"

BLOCK **table;
COORD **coord;

/*
void addBlock(char key)
{
	BLOCK blck;
	int pos=0, val=0;
	
	val = 1+(rand() % 1);
	
	switch(key)
	{
		case UP:
			table[pos][3] = blck;
			break;
		case LEFT:
			table[3][pos] = blck;
			break;
		case RIGHT:
			//function
			break;
		case DOWN:
			//function
			break;
	}
}
*/
void control(char key, int size)
{
	int i;
	
	switch(key)
	{
		case UP:
			for (i=1;i<size;i++)
				toUp(size,i);
			break;
		case LEFT:
			for (i=1;i<size;i++)
				toLeft(size,i);
			break;
		case DOWN:
			for (i=1;i<size;i++)
				toDown(size,i);
			break;
		case RIGHT:
			for (i=1;i<size;i++)
				toRight(size,i);
			break;
	}
}

void eraseBlock(BLOCK blck)
{
	blck.color = 7;		//deixa com a cor do tabuleiro
	blck.value = 0;		//zera o valor
	blck.flag = 0;		//zera a flag
}

char getKey()
{
    char code = 0;
    int teste = 0;

    do
    {
        code = getch();  			//recebe o codigo da tecla
        if(code==-32)    			//caso seja um caractere especial, deve-se pegar novamente
        {
            code = getch();
            if(code==UP||code==LEFT||code==RIGHT||code==DOWN)
            {
                teste = 1;
            }
        }else if(code==ESC)
        {
            teste = 1;
        }
    }while(teste==0);

    return code;
}

void increaseBlock(BLOCK blck)
{
	blck.value = blck.value*2;
	blck.flag = 1;
	blck.color++;
}

void increaseScore(PLAYER plyr, int score)
{
	plyr.score += score;
}

void moveBlock(BLOCK bl_origin, BLOCK bl_target)
{
	if(bl_target.value!=0)
	{
		if(bl_origin.value==bl_target.value && bl_origin.flag==0 && bl_target.flag==0)	//Verifica-se se esses blocos têm valores iguais e os flags em 0
		{
			increaseBlock(bl_target);			//Se sim, aumenta o valor do bloco de destino
			eraseBlock(bl_origin);				//E apaga o bloco de origem 
		}
	}else
	{
		bl_target = bl_origin;					//Se não há blocos na coluna de destino, move-se o bloco para lá
		eraseBlock(bl_origin);
	}

}

void printBlock(COORD coord, BLOCK blck)
{
	int i=0, j=0, nx=0, ny=0;
	
	textbackground(blck.color);
	gotoxy(coord.x,coord.y);
	
	for(i=-HEIGHT; i<=HEIGHT; i++)
	{
		ny = coord.y+i;
		for(j=-WIDTH; j<=WIDTH; j++)
		{
			nx = coord.x+j;	
			gotoxy(nx,ny);	
			if(i==0 && j==0)
			{
				printf("%d",blck.value);
			}else
			{
				printf(" ");
			}	
		}
	}
}

void printPlayer(PLAYER plyr)
{
	if(plyr.win)
	{
		printf("Nome: %s || Pontuacao: %d || Ganhou? Sim", plyr.name, plyr.score);
	}else
	{
		printf("Nome: %s || Pontuacao: %d || Ganhou? Nao", plyr.name, plyr.score);
	}
	
}

BLOCK readBlock()
{
	BLOCK blck;
	blck.flag = 0;
	
	printf("Digite um valor para a cor do bloco: ");
	scanf("%d", &blck.color);
	printf("Digite um valor para o bloco: ");
	scanf("%d", &blck.value);
	
	return blck;
}

PLAYER readPlayer()
{
	PLAYER plyr;
	char name[SIZE_NAME];
	int score, win;
	
	fflush(stdin);
	printf("Digite o nome de jogador: ");
	gets(plyr.name);
	printf("Digite a pontuacao do jogador: ");
	scanf("%d", &plyr.score);
	printf("Digite algum valor (!=0) caso o jogador ganhou: ");
	scanf("%d", &plyr.win);
		
	return plyr;
}

void refreshTable(int size)
{
	int i, j;
	
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			table[i][j].flag = 0;
			printBlock(coord[i][j],table[i][j]);
		}
	}
}

void setCoord(COORD coord_t, int size)
{
	int i,j;
	
	coord = (COORD **) malloc(size * sizeof(sizeof(COORD *)));
		
	for(i=0;i<size;i++)
	{
		coord[i] = (COORD *) malloc(size * sizeof(COORD));
		for(j=0;j<size;j++)
		{
			coord[i][j].x = coord_t.x+(j*2*(WIDTH+0.5));
			coord[i][j].y = coord_t.y+(i*2*(HEIGHT+0.5));
		}
	}
}

void setTable(int size)
{
	int i,j;
	
	table = (BLOCK **) malloc(size * sizeof(sizeof(BLOCK *)));
	
	for(i=0;i<size;i++)
	{
		table[i] = (BLOCK *) malloc(size * sizeof(BLOCK));
		for(j=0;j<size;j++)
		{
			table[i][j].color = 7;
			table[i][j].value = 0;
		}
	}
}

void showMenu()
{
	printf("THE 1024 GAME");
	printf("Created by Felipe T. Fetter & Hector Lacerda");
	printf("\n \n \n \n");
	printf("MODO CLASSICO");
	printf("MODO FACIL");
	printf("MODO PERSONALIZADO");
	printf("VER O RANKING");
	printf("SAIR DO JOGO");
}

void showMenuRank()
{
	printf("EXIBIR RANK");
	printf("RESETAR RANK");
	printf("SALVAR RANK");
	printf("VOLTAR AO MENU PRINCIPAL");
}

void showPlayers(PLAYER vecPlyr[], int score, int qntPlyr)
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

void startGame(int size)
{
	BLOCK ini_blck;
	COORD coord_t;
	int i=0,j=0;
	ini_blck.color=9;
	ini_blck.value=1;
	
	switch(size)
	{
		case NORMAL:
			coord_t.x = 28;
			coord_t.y = 7;
			break;
	}
	//inicializando o tabuleiro
	setTable(size);
	setCoord(coord_t,size);
	table[1][3] = ini_blck;
	table[3][3] = ini_blck;
	refreshTable(size);

	while(1)
	{
		control(getKey(),size);
		refreshTable(size);
	}
}

void toDown(int size,int times)
{
	int i,j;
	times = size-times-1;
	
	for(i=times; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			moveBlock(table[i][j],table[i+1][j]);			
		}
	}
}

void toLeft(int size,int times)
{
	int i,j;
	
	for(j=times; j>0; j--)
	{
		for(i=0; i<size; i++)
		{
			moveBlock(table[i][j],table[i][j-1]);			
		}
	}
}

void toRight(int size,int times)
{
	int i,j;
	times = size-times-1;
	
	for(j=times; j<size; j++)
	{
		for(i=0; i<size; i++)
		{
			moveBlock(table[i][j],table[i][j+1]);			
		}
	}
}

void toUp(int size,int times)
{
	int i,j;
	
	for(i=times; i>0; i--)
	{
		for(j=0; j<size; j++)
		{
			moveBlock(table[i][j],table[i][j-1]);			
		}
	}
}
/*
void teste()
{
	BLOCK tabuleiro[4][4], ini_blck;
	COORD coord_t;
	
	ini_blck.value=1;
	
	{
		int i=0,j=0;
		setTable(4);
		setCoord(coord_t,4);
		table[3][1] = ini_blck;
		table[3][3] = ini_blck;
		
		for(i=0; i<4; i++)
		{
			for(j=0; j<4; j++)
			{
				tabuleiro[i][j] = table[i][j];
				printf("| %i |", tabuleiro.value[i][j]);				
			}
			printf("\n");
		}
		while(1)
		{
			control(getKey(),4);
			for(i=0; i<4; i++)
			{
				for(j=0; j<4; j++)
				{
					tabuleiro[i][j] = table[i][j];
					printf("| %i |", tabuleiro.value[i][j]);				
				}
				printf("\n");
			}
		}

	}
}*/
