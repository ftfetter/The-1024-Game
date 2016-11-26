#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio2.h>
#include "gamelib.h"

BLOCK **table;				//matriz para o tabuleiro
COORD **coord;				//coordenadas para os blocos do tabuleiro
PLAYER plyr;				//informações do jogador atual

int pallet[10] = {1,2,4,5,6,8,9,12,13,14};		//paleta de cores dos blocos


void addBlockDown(int size)
{
	BLOCK blck;
	int pos=0, val=0, i=0, count=0;
	
	val = rand() % 2;	
	blck = setBlock(val);
	
	do
	{
		pos = rand() % size;		
	}while(table[0][pos].value);

	table[0][pos] = blck;
}

void addBlockLeft(int size)
{
	BLOCK blck;
	int pos=0, val=0, i=0, count=0;
	
	val = rand() % 2;
	blck = setBlock(val);
	
	do
	{
		pos = rand() % size;
	}while(table[pos][size-1].value);
	
	table[pos][size-1] = blck;
}

void addBlockRight(int size)
{
	BLOCK blck;
	int pos=0, val=0, i=0, count=0;
	
	val = rand() % 2;	
	blck = setBlock(val);
	
	do
	{
		pos = rand() % size;
	}while(table[pos][0].value);

	table[pos][0] = blck;
}

void addBlockUp(int size)
{
	BLOCK blck;
	int pos=0, val=0, i=0, count=0;
	
	val = rand() % 2;	
	blck = setBlock(val);

	do
	{
		pos = rand() % size;
	}while(table[size-1][pos].value);

	table[size-1][pos] = blck;
}

int checkTable(int size)
{
	int i,j,count=0;
	
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(table[i][j].value==1024)
			{
				return 1;	
			}
			if(table[i][j].value>0)
			{
				count++;	
			}	
		}
	}
	if(count==(size*size))
	{
		return 2;
	}else
	{
		return 0;
	}
}

void control(char key, int size)
{
	int end;
	
	switch(key)
	{
		case UP:
			toUp(size);
			if(checkTable(size)!=2)
				addBlockUp(size);
			else
				endGame(2);
			break;
		case LEFT:
			toLeft(size);
			if(checkTable(size)!=2)
				addBlockLeft(size);
			else
				endGame(2);
			break;
		case DOWN:
			toDown(size);
			if(checkTable(size)!=2)
				addBlockDown(size);
			else
				endGame(2);
			break;
		case RIGHT:
			toRight(size);
			if(checkTable(size)!=2)
				addBlockRight(size);
			else
				endGame(2);
			break;
	}
}

void endGame(int end)
{
	if(end==2)
	{
		clrscr();
		printf("GAME OVER");
	}
}

BLOCK eraseBlock(BLOCK blck)
{
	blck.color = 7;			//deixa com a cor do tabuleiro
	blck.value = 0;			//zera o valor
	blck.flag = 0;			//zera a flag
	
	return blck;
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

BLOCK increaseBlock(BLOCK blck)
{
	int ind;
	
	blck.count++;
	blck.value = pow(2,blck.count);
	ind = blck.count % 10;
	blck.color = pallet[ind];
	blck.flag = 1;
	
	increaseScore(blck.value);
	
	return blck;
}

void increaseScore(int score)
{
	plyr.score += score;
}

void moveBlock(int i_origin, int j_origin, int i_target, int j_target)
{
	BLOCK bl_origin, bl_target;
	
	bl_origin = table[i_origin][j_origin];
	bl_target = table[i_target][j_target];
	
	if(bl_target.value!=0)
	{
		if(bl_origin.value==bl_target.value && bl_origin.flag==0 && bl_target.flag==0)	//Verifica-se se esses blocos têm valores iguais e os flags em 0
		{
			table[i_target][j_target] = increaseBlock(bl_target);			//Se sim, aumenta o valor do bloco de destino direto no tabuleiro
			table[i_origin][j_origin] = eraseBlock(bl_origin);				//E exclui o bloco de origem
		}
	}else
	{
		table[i_target][j_target] = bl_origin;							//Se não há blocos na coluna de destino, move-se o bloco para lá
		table[i_origin][j_origin] = eraseBlock(bl_origin);				//E exclui o bloco de origem		
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
			printf(" ");	
		}
	}
	
	if(blck.value)
	{
		gotoxy(coord.x-2,coord.y);
		printf("%4d",blck.value);
	}
	
	textbackground(BLACK); // voltando para o padrão para evitar bugs
}

void printPlayer(char mode[])
{
	int record=0;
	textbackground(WHITE);
	textcolor(BLACK);
	
	gotoxy(0,0);
	
	printf("  Nome: %-15s  Modo: %-13s   Record: %5d   Pontuacao: %5d ", plyr.name, mode, record, plyr.score);
}

void refreshTable(int size, char mode[])
{
	int i, j;
	clrscr();
	
	printPlayer(mode);
	
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			table[i][j].flag = 0;
			printBlock(coord[i][j],table[i][j]);
		}
	}
}

BLOCK setBlock(int count)
{
	BLOCK blck;
	int ind;
	
	blck.count = count;
	blck.value = pow(2,count);
	ind = count % 10;
	blck.color = pallet[ind];
	blck.flag = 1;
	
	return blck;
}

void setCoord(COORD coord_t, int size)
{
	int i,j;
	
	coord = (COORD **) malloc(size * sizeof(COORD *));
		
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

PLAYER setPlayer()
{
	PLAYER plyr;
	char name[SIZE_NAME];
	
	fflush(stdin);
	printf("Digite o seu nome, jogador: ");
	gets(plyr.name);
	plyr.score = 0;
	plyr.win = 0;
		
	return plyr;
}

void setTable(int size)
{
	int i,j;
	
	table = (BLOCK **) malloc(size * sizeof(BLOCK *));
	
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
	int i=0,j=0,end=0;
	char mode[15];
	
	ini_blck = setBlock(1);
	
	plyr = setPlayer();
	
	switch(size)
	{
		case NORMAL:
			coord_t.x = 28;
			coord_t.y = 7;
			strcpy(mode,"Classico");
			break;
		case MEDIUM:
			coord_t.x = 25;
			coord_t.y = 7;
			strcpy(mode,"Personalizado");
			break;
		case LARGE:
			coord_t.x = 23;
			coord_t.y = 7;
			strcpy(mode,"Personalizado");
			break;
	}
	//inicializando o tabuleiro
	setTable(size);
	setCoord(coord_t,size);
	table[1][3] = ini_blck;
	refreshTable(size, mode);

	do
	{
		control(getKey(),size);
		refreshTable(size, mode);
		if(checkTable(size)==1)
			endGame(1);
	}while(1);
}

void toDown(int size)
{
	int i,j,ind,times;
	
	for(ind=1;ind<size;ind++)
	{
		times = size-ind-1;
	
		for(i=times; i<size-1; i++)
		{
			for(j=0; j<size; j++)
			{
				moveBlock(i,j,i+1,j);					//Move o bloco para baixo
			}
		}
	}
}

void toLeft(int size)
{
	int i,j,ind;
	
	for(ind=1;ind<size;ind++)
	{
		for(j=ind; j>0; j--)
		{
			for(i=0; i<size; i++)
			{
				moveBlock(i,j,i,j-1);					//Move o bloco para a esquerda
			}
		}
	}
}

void toRight(int size)
{
	int i,j,ind,times;
	
	for(ind=1;ind<size;ind++)
	{
		times = size-ind-1;
	
		for(j=times; j<size-1; j++)
		{
			for(i=0; i<size; i++)
			{
				moveBlock(i,j,i,j+1);					//Move o bloco para a direita
			}
		}
	}
}

void toUp(int size)
{
	int i,j,ind;
	
	for(ind=1;ind<size;ind++)
	{
		for(i=ind; i>0; i--)
		{
			for(j=0; j<size; j++)
			{
				moveBlock(i,j,i-1,j);					//Move o bloco para cima
			}
		}
	}
}
