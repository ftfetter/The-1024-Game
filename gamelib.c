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

int checkGame(int size)
{
	int i,j;
	
	for(i=0;i<size;i++)			 // percorre o tabuleiro inteiro em busca de um bloco com valor 1024
	{
		for(j=0;j<size;j++)
		{
			if(table[i][j].value==1024) 
			{
				// se encontrado o bloco, retorna 2 indicando que o jogador venceu o jogo
				return 2;	
			}
		}
	}
	
	// se não encontrou, retorna o valor de checkTable() que retornará 0 se ainda restar movimentos possíveis ou 1 no caso contrário
	return checkTable(size);
}

int checkTable(int size)
{
	int i,j;
	
	for(i=0;i<size-1;i++)			// percorrendo o tabuleiro sem passar pela coluna mais a direita
	{
		for(j=0;j<size-1;j++)		// e sem passar pela linha mais inferior
		{
			if(table[i][j].value)	// se o valor do bloco atual não for zero, checar: 
			{
				if(table[i+1][j].value == 0 || table[i][j+1].value == 0) // se os blocos próximos ao atual são zero
				{
					return 0;			// existe um movimento possível
				}
				if(table[i][j].value == table[i][j+1].value) // se o bloco atual e o de baixo têm o mesmo valor
				{
					return 0;			// existe um movimento possível
				}
				if(table[i][j].value == table[i+1][j].value) // ou se o bloco atual e o da direita têm o mesmo valor
				{
					return 0;			// existe um movimento possível
				}
							
			}else		// se o próprio bloco for zero
			{
				return 0;	// existe movimento possível
			}
		}
	}
	// com isso foi checados QUASE todos os blocos
	// faltou o do canto inferior direito (table[size-1][size-1])
	// faremos os mesmos testes de antes mas focado nesse bloco e comparando com os blocos acima e à esquerda dele
	if(table[size-1][size-1].value)	// se o valor do bloco não for zero, checar: 
	{
		// como já testamos se os blocos superior e a esquerda eram zero anteriormente, pulamos a verificação
		if(table[size-1][size-1].value == table[size-2][size-1].value) // se o bloco atual e o acima têm o mesmo valor
		{
			return 0;			// existe um movimento possível
		}
		if(table[size-1][size-1].value == table[size-1][size-2].value) // ou se o bloco atual e o à esquerda têm o mesmo valor
		{
			return 0;			// existe um movimento possível
		}			
		
	}else		// se o próprio bloco for zero
	{
		return 0;	// existe movimento possível
	}
	
	return 1;   // se a função chegou até aqui depois de tudo verificado, não existem movimentos possíveis (retorna 1)
}

void control(char key, int size)
{
	int end;
	
	switch(key)
	{
		case UP:
			toUp(size);
			addBlockUp(size);
			break;
		case LEFT:
			toLeft(size);
			addBlockLeft(size);
			break;
		case DOWN:
			toDown(size);
			addBlockDown(size);
			break;
		case RIGHT:
			toRight(size);
			addBlockRight(size);
			break;
		case ESC:
			endGame(plyr);
	}
}

void endGame(PLAYER plyr)
{
	clrscr();
	//printLoseMessage();
	printf("Fim de jogo. \n\n Pressione 'ESC' para voltar ao Menu Principal.");
	setRecord(plyr);
	if(getKey()==ESC)
		showMenu();
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

int getRecords(PLAYER *players)
{
	FILE *point_arq;
	int count=0;
	
	point_arq = fopen("record","rb");
	if(point_arq==NULL)			// Caso não haja nenhum recorde salvo, a função retornará 0
		return 0;		
	else
	{
		while(!feof(point_arq))
		{
			if(!fread(&players[count],sizeof(PLAYER),1,point_arq)==1)
				printf("Erro ao ler arquivo binário.");
			count++;
		}
		fclose(point_arq);
	}
	
	return count;
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

void printLoseMessage()
{
	clrscr();
	printf("\n");	
	printf("                 ##      ##  ##########  ##########  ##########\n");
	printf("                  ##    ##   ##      ##  ##          ##\n");
	printf("                   ##  ##    ##      ##  ##          #######\n");
	printf("                    ####     ##      ##  ##          ##\n");
	printf("                     ##      ##########  ##########  ##########\n");
	printf("\n");
	printf("     #########   ##########  #########   ########    ##########  ##      ##\n");
	printf("     ##      ##  ##          ##      ##  ##     ##   ##          ##      ##\n");
	printf("     #########   #######     #########   ##      ##  #######     ##      ##\n");
	printf("     ##          ##          ##   ###    ##     ##   ##          ##      ##\n");
	printf("     ##          ##########  ##     ###  ########    ##########   ########\n");
	printf("\n\n              PRESSIONE 'ESC' PARA VOLTAR AO MENU PRINCIPAL");
}

void printWinMessage()
{
	clrscr();
	printf("\n");
	printf("                 ##      ##  ##########  ##########  ##########\n");
	printf("                  ##    ##   ##      ##  ##          ##\n");
	printf("                   ##  ##    ##      ##  ##          #######\n");
	printf("                    ####     ##      ##  ##          ##\n");
	printf("                     ##      ##########  ##########  ##########\n");
	printf("\n");
	printf("     ##      ##  ##########  ####    ##  ##########  ##########  ##      ##\n");
	printf("      ##    ##   ##          ## ##   ##  ##          ##          ##      ##\n");
	printf("       ##  ##    #######     ##  ##  ##  ##          #######     ##      ##\n");
	printf("        ####     ##          ##   ## ##  ##          ##          ##      ##\n");
	printf("         ##      ##########  ##    ####  ##########  ##########   ########\n");
	printf("\n\n                  DESEJA CONTINUAR JOGANDO <N/S>: ");
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

void setRecord(PLAYER player)
{
	FILE *point_arq;
	PLAYER records[RECORDS];
	int i=0, tst=1, n_players=0, flag=0;
	
	n_players = getRecords(records);		// Pega o numero de registros e salva-os no vetor 'records'
	
	point_arq = fopen("record","wb");
	if(point_arq==NULL)
		printf("Erro ao abrir o arquivo binario.");
	else
	{
		if(n_players==0)		// Se n_player for 0, é porque o recorde está sendo criado agora
		{
			if(fwrite(&player,sizeof(PLAYER),1,point_arq)!=1)	// Só adiciona o recorde
				printf("Erro ao escrever arquivo.");
		}
		for(i=0;i<n_players;i++)
		{
			if(records[i].score<player.score && flag==0)			// Verifica se é um recorde e se já foi adicionado um recorde (para não adicionar de novo)
			{
				if(fwrite(&player,sizeof(PLAYER),1,point_arq)!=1)			// Adiciona o novo recorde
					printf("Erro ao escrever arquivo binario.");
				if(fwrite(&records[i],sizeof(PLAYER),1,point_arq)!=1)		// Adiciona o anterior para que ele não seja apagado
					printf("Erro ao escrever arquivo binario.");
				flag++;														// Indica que um jogador já foi adicionado
			}else
			{
				if(fwrite(&records[i],sizeof(PLAYER),1,point_arq)!=1)		// Matém o recorde antigo e continua a verificação
					printf("Erro ao escrever arquivo binario.");
			}
		}
		fclose(point_arq);
	}
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

void setTxtRecord()
{
	FILE *point_arq;
	PLAYER records[RECORDS];
	int i, n_players;
	
	n_players = getRecords(records);		// Pega o numero de registros e salva-os no vetor 'records'
	
	point_arq = fopen("recordes.txt","w");
	if(point_arq==NULL || n_players==0)
		printf("Erro ao abrir o arquivo texto.");
	else
	{
		for(i=0;i<n_players;i++)
		{
			if(records[i].win>0)
			{
				if(fprintf(point_arq,"Jogador: %-15s || Pontuacao: %5d || Ganhou \n", records[i].name, records[i].score)<0)
					printf("Erro ao escrever o arquivo texto.");
			}else
			{
				if(fprintf(point_arq,"Jogador: %-15s || Pontuacao: %5d || Nao ganhou \n", records[i].name, records[i].score)<0)
					printf("Erro ao escrever o arquivo texto.");
			}
		}
	}
	fclose(point_arq);
}

void showMenu()
{
	int option;

	clrscr();	
	printf("THE 1024 GAME\n");
	printf("Created by Felipe T. Fetter & Hector G. Lacerda\n");
	printf("\n \n \n \n");
	printf("MODO CLASSICO<1>\n");
	printf("MODO FACIL<2>\n");
	printf("MODO PERSONALIZADO<3>\n");
	printf("VER O RANKING<4>\n");
	printf("SAIR DO JOGO<5>\n");
	
	scanf("%d", &option);
	
	switch(option)
	{
		case 1:
			startGame(NORMAL);
			break;
		case 3:
			showMenuPersonGame();
			break;
		case 4:
			showMenuRank();
			break;
	}
}

void showMenuPersonGame()
{
	int option;
	
	clrscr();
	printf("TABULEIRO 5x5 <1>\n");
	printf("TABULEIRO 6x6 <2>\n\n");
	printf("VOLTAR AO MENU PRINCIPAL <3>");
	
	scanf("%d", &option);
	
	switch(option)
	{
		case 1:
			startGame(MEDIUM);
			break;
		case 2:
			startGame(LARGE);
			break;
		case 3:
			showMenu();
			break;
	}
}

void showMenuRank()
{
	int option;
	
	clrscr();
	printf("EXIBIR RANK<1>\n");
	printf("RESETAR RANK<2>\n");
	printf("SALVAR RANK<3>\n");
	printf("VOLTAR AO MENU PRINCIPAL<4>\n");
	
	scanf("%d", &option);
	
	switch(option)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			setTxtRecord();
			break;
		case 4:
			showMenu();
			break;
	}
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
		end = checkGame(size);
	}while(end==0);

	if(end==2)
		winGame(plyr);
	else
		endGame(plyr);
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

void winGame(PLAYER plyr)
{
	char resp;
	
	printWinMessage();
	scanf("%c", &resp);
	
}
