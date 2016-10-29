#define TAM 45 				//tamanho da string 'name'

typedef struct player_struct
{
	char name[TAM];			//nome do jogador
	int score;			//pontuação do jogador
	int win;			//booleano que indica se o player ganhou(!=0) ou não(==0)
} player;	

typedef struct block_struct
{
	int color;			//valor da cor do bloco
	int valor;			//valor contido no bloco para a soma
} block;

typedef struct coordinate_struct
{
	int x;				//coordenada x do console
	int y;				//coordenada y do console
} coordinate;

//função para ler os atributos do jogador
//readPlayer() -> player
player readPlayer();

//função para ler os atributos do bloco
//readBlock() -> block
block readBlock();

//função para imprimir os atributos do jogador
//printPlayer(player) -> "Nome: <player.name> || Pontuacao: <player.score> || Ganhou? Sim/Nao" (dependendo do valor de <player.win>)
void printPlayer(player plyr);

//função para imprimir os atributos do bloco
//printBlock(block) -> "Cor: <block.color> || Valor: <block.valor>"
void printBlock(block blck);

//função que soma a pontuação do jogador
//addScore(player,integer) -> <player.score> = <player.score> + integer
void addScore(player plyr, int score);

//função que adiciona um bloco na tela
//addBlock(coordinate,integer1,integer2,block) -> bloco de tamanho integer1xinteger2, cor <block.color> e valor <block.valor>
void addBlock(coordinate coord, int height, int width, block blck);

//função que mostra todos os jogadores que pontuaram mais que um determinado valor
//showPlayers(player[],integer1,integer2) -> "<player.name>" de player[integer2] cuja pontuacao >= integer1
void showPlayers(player vecPlyr[], int score, int qntPlyr);

