#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define SIZE_EQUIPA 5
#define  SIZE_PLAYER 10
typedef struct
{
   int dia, mes, ano;	
} DATA;

typedef  struct 
{
	int id, nGolos, ativo,idEquipa;
	char nome[20], apelido[20], dataCont[10],dataFimCon[10], estado[8];
//	DATA dataContrato, dataFimContrato;
} Jogadores;

typedef struct 
{
   int id;
   char nome[30];
   Jogadores jogadores[20];
} Equipas;

int mainMenu();

void addEquipa();
void addJogador(int idEquipa);
/*Listagem*/
void listEquipas(Equipas equipa[]);
void listJogadores(Equipas equipa);
void listAllPlayers();
void deleteThirdOne(Equipas *equipa);
void listBestOneEquipa(Equipas equipa);
void listLastOneEquipa(Equipas equipa);
/*Obtem os ultimos ids*/
int lastIdEquipa();
int lastIdJogador();
/*select */
void fillStruct(Equipas equipa[]);
int checkId(Equipas equipa[],int id);
/*with files*/

void insertEquipa(Equipas equipa);
void insertJogador(Jogadores jogadoor);

extern struct Equipas Equipa;
extern struct Jogadores player;
#endif