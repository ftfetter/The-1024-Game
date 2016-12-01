#define SIZE_NAME 45		//tamanho da string 'name'
#define RECORDS 10			//quantidade de registros salvos nos recordes
#define NORMAL 4			//tamanho do tabuleiro normal
#define MEDIUM 5			//tamanho do tabuleiro médio
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
	int score;				//pontuação do jogador
	int win;				//booleano que indica se o player ganhou(!=0) ou não(==0)
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
	int count;				//um contador para associar cor à valores do bloco
	int flag;				//flag que indicará se esse bloco aumentou de valor
} BLOCK;


//função que adiciona um bloco ao tabuleiro quando pressionada a tecla DOWN
//addBlockDown(integer) -> bloco na parte superior do tabuleiro
void addBlockDown(int size);

//função que adiciona um bloco ao tabuleiro quando pressionada a tecla LEFT
//addBlockLeft(integer) -> bloco na parte mais a direita do tabuleiro
void addBlockLeft(int size);

//função que adiciona um bloco ao tabuleiro quando pressionada a tecla RIGHT
//addBlockRight(integer) -> bloco na parte mais a esquerda do tabuleiro
void addBlockRight(int size);

//função que adiciona um bloco ao tabuleiro quando pressionada a tecla UP
//addBlockUp(integer) -> bloco na parte inferior do tabuleiro
void addBlockUp(int size);

//função para verificar se ainda há jogadas a se fazer
//checkGame(integer) -> retorna 0 (não acabou), 1 (jogador perdeu) ou 2 (jogador ganhou)
int checkGame(int size);

//função para checar se o jogador ganhou ou se o jogo terminou verificando os valores dos blocos da matriz com o tamanho informado
//checkTable(integer) -> Se houver um bloco com valor 1048, retorna 1; se não há mais movimentação, retorna 2; senão, retorna 0
int checkTable(int size);

//função que executa os comandos das teclas pressionadas
//control(character, integer) -> movimentação esperada para a tecla pressionada
void control(char key, int size);

//função que termina o jogo, exibindo uma mensagem e salvando a pontuação
//endGame() -> exibe a mensagem de fim de jogo
void endGame();

//função que "apaga" o bloco indicado
//eraseBlock(BLOCK) -> BLOCK é totalmente zerado com exceção da sua cor que é setada para a cor do tabuleiro LIGHT_GRAY ou 7
BLOCK eraseBlock(BLOCK blck);

//função para detectar se um comando válido foi digitado
//getKey() -> codigo da tecla
char getKey();

//função que busca todos os recordes registrados, grava eles no ponteiro e retorna a quantidade de registros
//getRecords(&players) -> integer (quantidade de registros)
int getRecords(PLAYER *players);

//função que aumenta o valor do bloco, altera a sua cor de acordo com o seu valor e marca a sua flag
//increaseBlock(BLOCK) -> um BLOCK com BLOCK.value aumentado, BLOCK.color alterado e BLOCK.flag == 1
BLOCK increaseBlock(BLOCK blck);

//função que soma a pontuação do jogador
//addScore(integer) -> <player.score> = <player.score> + integer
void increaseScore(int score);

//função que move um bloco da posição i_origin e j_origin para i_target e j_target no tabuleiro, verificando a possibilidade de soma dos blocos
//	e apagando o bloco de origem caso seja feita a movimentação
//moveBlock(integer1, integer2, integer3, integer4) -> altera a table diretamente com a movimentação ou soma dos blocos
void moveBlock(int i_origin, int j_origin, int i_target, int j_target);

//função que adiciona um bloco na tela
//addBlock(coordinate,block) -> bloco de tamanho 9x5 px, cor <block.color> e valor <block.valor>
void printBlock(COORD coord, BLOCK blck);

//função que só imprime na tela uma mensagem de derrota
//printLoseMessage() -> imprime texto no console
void printLoseMessage();

//função para imprimir os atributos do jogador
//printPlayer(string) -> "Nome: <player.name> Modo: <string> Recorde: <recorde> Pontuacao: <player.score>"
void printPlayer(char mode[]);

//função que só imprime na tela uma mensagem de vitória
//printWinMessage() -> imprime texto no console
void printWinMessage();

//função que atualiza o tabuleiro após uma jogada
//refreshTable(integer, string) -> imprime na tela um tabuleiro integerXinteger com as informações do jogador no topo
void refreshTable(int size, char mode[]);

//função que gera um bloco inicial para ser adicionado ao tabuleiro após um movimento
//setBlock(integer) -> BLOCK com valor 2^integer e cor == pallet[integer]
BLOCK setBlock(int count);

//função responsável por gerar as coordenadas de um tabuleiro de tamanho 'size'
//setCoord(COORD, integer) -> coordenadas para a impressão do tabuleiro integerXinteger sendo COORD as cordenadas pro primeiro bloco desse tabuleiro
void setCoord(COORD coord_t, int size);

//função para inicializar os atributos do jogador
//readPlayer() -> player
PLAYER setPlayer();

//função que gera um arquivo binário com os recordes do jogo
//setRecord(player) -> pega os recordes registrados, compara com a pontuação atual e grava um arquivo binário
void setRecord(PLAYER player);

//função responsável por gerar um tabuleiro nas proporções passadas por parâmetro
//setTable(integer) -> cria um tabuleiro de integerXinteger de blocos
void setTable(int size);

//função que gera uma versão .txt dos recordes registrados
//setTxtRecord() -> pega o arquivo binário e cria um .txt formatado com as informaçoes citadas
void setTxtRecord();

//função que exibe o menu principal
//showMenu() -> imprime o menu e espera a opção
void showMenu();

//função que exibe o menu do jogo personalizado
//showMenuPersonGame() -> imprime o menu e espera a opção
void showMenuPersonGame();

//função que exibe o menu dos rankings
//showMenuRank() -> imprime o menu e espera a opção
void showMenuRank();

//função que mostra todos os jogadores que pontuaram mais que um determinado valor
//showPlayers(player[],integer1,integer2) -> "<player.name>" de player[integer2] cuja pontuacao >= integer1
void showPlayers(PLAYER vecPlyr[], int score, int qntPlyr);

//função que inicia o jogo no modo selecionado
//startGame(size) -> tabuleiro do jogo
void startGame(int size);

//função que controla a movimentação dos blocos para baixo
//toDown(integer1,integer2) ->  movimenta os blocos para a linha inferior do tabuleiro de tamanho integer
void toDown(int size);

//função que controla a movimentação dos blocos para a esquerda
//toLeft(integer1,integer2) ->  movimenta os blocos para a linha mais a esquerda do tabuleiro de tamanho integer
void toLeft(int size);

//função que controla a movimentação dos blocos para a direita
//toRight(integer) -> movimenta os blocos para a linha mais a direita do tabuleiro de tamanho integer
void toRight(int size);

//função que controla a movimentação dos blocos para cima
//toUp(integer) -> movimenta os blocos para a linha superior do tabuleiro de tamanho integer
void toUp(int size);

//função que exibe a mensagem de vitória e adiciona a flag de vitoria no jogador
//winGame(player) -> player.win = 1
void winGame(PLAYER plyr);
