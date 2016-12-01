#define SIZE_NAME 45		//tamanho da string 'name'
#define RECORDS 10			//quantidade de registros salvos nos recordes
#define NORMAL 4			//tamanho do tabuleiro normal
#define MEDIUM 5			//tamanho do tabuleiro m�dio
#define LARGE 6				//tamanho do tabuleiro grande
#define HEIGHT 1			//altura do bloco (partindo do centro)
#define WIDTH 2				//largura do bloco (partindo do centro) 
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
	int count;				//um contador para associar cor � valores do bloco
	int flag;				//flag que indicar� se esse bloco aumentou de valor
} BLOCK;


//fun��o que adiciona um bloco ao tabuleiro quando pressionada a tecla DOWN
//addBlockDown(integer) -> bloco na parte superior do tabuleiro
void addBlockDown(int size);

//fun��o que adiciona um bloco ao tabuleiro quando pressionada a tecla LEFT
//addBlockLeft(integer) -> bloco na parte mais a direita do tabuleiro
void addBlockLeft(int size);

//fun��o que adiciona um bloco ao tabuleiro quando pressionada a tecla RIGHT
//addBlockRight(integer) -> bloco na parte mais a esquerda do tabuleiro
void addBlockRight(int size);

//fun��o que adiciona um bloco ao tabuleiro quando pressionada a tecla UP
//addBlockUp(integer) -> bloco na parte inferior do tabuleiro
void addBlockUp(int size);

//fun��o para verificar se ainda h� jogadas a se fazer
//checkGame(integer) -> retorna 0 (n�o acabou), 1 (jogador perdeu) ou 2 (jogador ganhou)
int checkGame(int size);

//fun��o para checar se o jogador ganhou ou se o jogo terminou verificando os valores dos blocos da matriz com o tamanho informado
//checkTable(integer) -> Se houver um bloco com valor 1048, retorna 1; se n�o h� mais movimenta��o, retorna 2; sen�o, retorna 0
int checkTable(int size);

//fun��o que executa os comandos das teclas pressionadas
//control(character, integer) -> movimenta��o esperada para a tecla pressionada
void control(char key, int size);

//fun��o que termina o jogo, exibindo uma mensagem e salvando a pontua��o
//endGame() -> exibe a mensagem de fim de jogo
void endGame();

//fun��o que "apaga" o bloco indicado
//eraseBlock(BLOCK) -> BLOCK � totalmente zerado com exce��o da sua cor que � setada para a cor do tabuleiro LIGHT_GRAY ou 7
BLOCK eraseBlock(BLOCK blck);

//fun��o para detectar se um comando v�lido foi digitado
//getKey() -> codigo da tecla
char getKey();

//fun��o que busca todos os recordes registrados, grava eles no ponteiro e retorna a quantidade de registros
//getRecords(&players) -> integer (quantidade de registros)
int getRecords(PLAYER *players);

//fun��o que aumenta o valor do bloco, altera a sua cor de acordo com o seu valor e marca a sua flag
//increaseBlock(BLOCK) -> um BLOCK com BLOCK.value aumentado, BLOCK.color alterado e BLOCK.flag == 1
BLOCK increaseBlock(BLOCK blck);

//fun��o que soma a pontua��o do jogador
//addScore(integer) -> <player.score> = <player.score> + integer
void increaseScore(int score);

//fun��o que move um bloco da posi��o i_origin e j_origin para i_target e j_target no tabuleiro, verificando a possibilidade de soma dos blocos
//	e apagando o bloco de origem caso seja feita a movimenta��o
//moveBlock(integer1, integer2, integer3, integer4) -> altera a table diretamente com a movimenta��o ou soma dos blocos
void moveBlock(int i_origin, int j_origin, int i_target, int j_target);

//fun��o que adiciona um bloco na tela
//addBlock(coordinate,block) -> bloco de tamanho 9x5 px, cor <block.color> e valor <block.valor>
void printBlock(COORD coord, BLOCK blck);

//fun��o que s� imprime na tela uma mensagem de derrota
//printLoseMessage() -> imprime texto no console
void printLoseMessage();

//fun��o para imprimir os atributos do jogador
//printPlayer(string) -> "Nome: <player.name> Modo: <string> Recorde: <recorde> Pontuacao: <player.score>"
void printPlayer(char mode[]);

//fun��o que s� imprime na tela uma mensagem de vit�ria
//printWinMessage() -> imprime texto no console
void printWinMessage();

//fun��o que atualiza o tabuleiro ap�s uma jogada
//refreshTable(integer, string) -> imprime na tela um tabuleiro integerXinteger com as informa��es do jogador no topo
void refreshTable(int size, char mode[]);

//fun��o que gera um bloco inicial para ser adicionado ao tabuleiro ap�s um movimento
//setBlock(integer) -> BLOCK com valor 2^integer e cor == pallet[integer]
BLOCK setBlock(int count);

//fun��o respons�vel por gerar as coordenadas de um tabuleiro de tamanho 'size'
//setCoord(COORD, integer) -> coordenadas para a impress�o do tabuleiro integerXinteger sendo COORD as cordenadas pro primeiro bloco desse tabuleiro
void setCoord(COORD coord_t, int size);

//fun��o para inicializar os atributos do jogador
//readPlayer() -> player
PLAYER setPlayer();

//fun��o que gera um arquivo bin�rio com os recordes do jogo
//setRecord(player) -> pega os recordes registrados, compara com a pontua��o atual e grava um arquivo bin�rio
void setRecord(PLAYER player);

//fun��o respons�vel por gerar um tabuleiro nas propor��es passadas por par�metro
//setTable(integer) -> cria um tabuleiro de integerXinteger de blocos
void setTable(int size);

//fun��o que gera uma vers�o .txt dos recordes registrados
//setTxtRecord() -> pega o arquivo bin�rio e cria um .txt formatado com as informa�oes citadas
void setTxtRecord();

//fun��o que exibe o menu principal
//showMenu() -> imprime o menu e espera a op��o
void showMenu();

//fun��o que exibe o menu do jogo personalizado
//showMenuPersonGame() -> imprime o menu e espera a op��o
void showMenuPersonGame();

//fun��o que exibe o menu dos rankings
//showMenuRank() -> imprime o menu e espera a op��o
void showMenuRank();

//fun��o que mostra todos os jogadores que pontuaram mais que um determinado valor
//showPlayers(player[],integer1,integer2) -> "<player.name>" de player[integer2] cuja pontuacao >= integer1
void showPlayers(PLAYER vecPlyr[], int score, int qntPlyr);

//fun��o que inicia o jogo no modo selecionado
//startGame(size) -> tabuleiro do jogo
void startGame(int size);

//fun��o que controla a movimenta��o dos blocos para baixo
//toDown(integer1,integer2) ->  movimenta os blocos para a linha inferior do tabuleiro de tamanho integer
void toDown(int size);

//fun��o que controla a movimenta��o dos blocos para a esquerda
//toLeft(integer1,integer2) ->  movimenta os blocos para a linha mais a esquerda do tabuleiro de tamanho integer
void toLeft(int size);

//fun��o que controla a movimenta��o dos blocos para a direita
//toRight(integer) -> movimenta os blocos para a linha mais a direita do tabuleiro de tamanho integer
void toRight(int size);

//fun��o que controla a movimenta��o dos blocos para cima
//toUp(integer) -> movimenta os blocos para a linha superior do tabuleiro de tamanho integer
void toUp(int size);

//fun��o que exibe a mensagem de vit�ria e adiciona a flag de vitoria no jogador
//winGame(player) -> player.win = 1
void winGame(PLAYER plyr);
