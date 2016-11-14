#define SIZE_NAME 45		//tamanho da string 'name'
#define NORMAL 4			//tamanho do tabuleiro normal
#define HEIGHT 2			//altura do bloco (partindo do centro)
#define WIDTH 4				//largura do bloco (partindo do centro) 
#define UP 72				//codigo da tecla CIMA
#define LEFT 75				//codigo da tecla ESQUERDA
#define RIGHT 77			//codigo da tecla DIREITA
#define DOWN 80				//codigo da tecla BAIXO
#define ESC 27				//codigo da tecla ESC

typedef struct player_struct
{
	char name[SIZE_NAME];	//nome do jogador
	int score;				//pontua��o do jogador
	int win;				//booleano que indica se o player ganhou(!=0) ou n�o(==0)
} PLAYER;	

typedef struct coordinate_struct
{
	int x;					//coordenada x do console
	int y;					//coordenada y do console
} COORD;

typedef struct block_struct
{
	int color;				//valor da cor do bloco
	int value;				//valor contido no bloco para a soma
	int flag;				//flag que indicar� se esse bloco aumentou de valor
} BLOCK;


//
//
//void addBlock(COORD coord, BLOCK blck);

//
//
void control(char key, int size);

//
//
void eraseBlock(BLOCK blck);

//fun��o para detectar se um comando v�lido foi digitado
//getKey() -> codigo da tecla
char getKey();

//
//
void increaseBlock(BLOCK blck);


//fun��o que soma a pontua��o do jogador
//addScore(player,integer) -> <player.score> = <player.score> + integer
void increaseScore(PLAYER plyr, int score);

//
//
void moveBlock(BLOCK bl_origin,BLOCK bl_target);

//fun��o que adiciona um bloco na tela
//addBlock(coordinate,block) -> bloco de tamanho 9x5 px, cor <block.color> e valor <block.valor>
void printBlock(COORD coord, BLOCK blck);

//fun��o para imprimir os atributos do jogador
//printPlayer(player) -> "Nome: <player.name> || Pontuacao: <player.score> || Ganhou? Sim/Nao" (dependendo do valor de <player.win>)
void printPlayer(PLAYER plyr);

//fun��o para ler os atributos do bloco
//readBlock() -> block
BLOCK readBlock();

//fun��o para ler os atributos do jogador
//readPlayer() -> player
PLAYER readPlayer();

//
//
void refreshTable(int size);

//
//
void setCoord(COORD coord_t, int size);

//
//
void setTable(int size);

//fun��o que mostra todos os jogadores que pontuaram mais que um determinado valor
//showPlayers(player[],integer1,integer2) -> "<player.name>" de player[integer2] cuja pontuacao >= integer1
void showPlayers(PLAYER vecPlyr[], int score, int qntPlyr);

//fun��o que inicia o jogo no modo selecionado
//startGame(size) -> tabuleiro do jogo
void startGame(int size);

//
//
void toDown(int size, int times);

//
//
void toLeft(int size, int times);

//
//
void toRight(int size, int times);

//
//
void toUp(int size, int times);


void teste();

