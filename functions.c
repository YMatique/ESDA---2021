#include <stdio.h>
#include "functions.h"
struct Equipas;
struct Jogadores;

int mainMenu()
{
	int opcao;
	printf("======BEM VINDO AO CAMPEONATO========");
	printf("\nSelecione uma opcao");
	printf("\n1. Cadastrar Jogador\n2. Listar jogador\n3. Listar todos jogadores\n4.Eliminar o terceiro maior \n5. Sair\n");
	scanf("%d",&opcao);
	return opcao;
}

void addEquipa()
{
	Equipas equipa;
	printf("Introduza o nome da equipa: ");
	gets(equipa.nome);
	equipa.id=2;
	insertEquipa(equipa);
}
void addJogador(int idEquipa)
{
	Jogadores jogador;
	srand(time(NULL));
	jogador.id = rand()%(SIZE_EQUIPA*SIZE_PLAYER) + 1;
	fflush(stdin);
	printf("Introduza o nome: ");
	gets(jogador.nome);
	fflush(stdin);
	printf("Introduza o apelido: ");
	gets(jogador.apelido);
	fflush(stdin);
	printf("Introduza o numero de golos: ");
	scanf("%d",&jogador.nGolos);
	fflush(stdin);
	printf("Introduza a data do inicio do contrato ex. 10/20/2019: ");
	fflush(stdin);
	scanf("%s",jogador.dataCont);
	printf("Introduza a data do fim do contrato ex. 10/20/2022: ");
	fflush(stdin);
	scanf("%s",jogador.dataFimCon);
	jogador.idEquipa=idEquipa;
	strcpy(jogador.estado,"inativo");
	insertJogador(jogador);
}
void insertEquipa(Equipas equipa)
{
	FILE *fileW = fopen("equipas.txt","a+");
	if(fileW==NULL)
	{
		printf("\nErro cod 0x98! File not found");
	}
	fprintf(fileW,"\n%d %s",equipa.id,equipa.nome);
	fclose(fileW);
	printf("Equipa adicionada com sucesso!\n");
}
void insertJogador(Jogadores jog)
{
	FILE *fileW = fopen("jogadores.txt","a+");
	if(fileW==NULL)
	{
		printf("\nErro cod 0x98! File not found");
	}else
	{
		fprintf(fileW,"\n%d %s %s %d %s %s %d %s",jog.id,jog.apelido,jog.nome,jog.nGolos,jog.dataCont,jog.dataFimCon,jog.idEquipa,jog.estado);
		
	}
	fclose(fileW);
}
void listEquipas(Equipas equipa[])
{
	int i=0;
	printf("Id \t Nome\n");
	for(i=0; i<SIZE_EQUIPA; i++)
	{
		printf("%d \t %s\n",equipa[i].id,equipa[i].nome);
	}
}

void listJogadores(Equipas equipa)
{
	int i=0;
	printf("\nId\tApelido\tNome\tGolos\tInicio\tFim\tActivo\n");
	for(i; i<SIZE_PLAYER; i++)
	{
			if(equipa.jogadores[i].id>0 && equipa.jogadores[i].id<SIZE_PLAYER*SIZE_EQUIPA)
			{
            	printf("%d\t%s\t%s\t%d\t\%s\t\%s\t\%s\n",equipa.jogadores[i].id,equipa.jogadores[i].apelido,equipa.jogadores[i].nome,equipa.jogadores[i].nGolos,equipa.jogadores[i].dataCont,equipa.jogadores[i].dataFimCon,equipa.jogadores[i].ativo);	
			}
		
	}
}
/****/
void deleteThirdOne(Equipas *equipa)
{
	int i, line=0, col=0;
	
	Jogadores jog[SIZE_PLAYER],jogAux;
	
	for(i=0; i<SIZE_PLAYER; i++)
	{
		if(equipa->jogadores[i].id>0 && equipa->jogadores[i].id<SIZE_PLAYER*SIZE_EQUIPA)
		{
			for(line; line<SIZE_PLAYER; line++)
			{
				for(col=line; col<SIZE_PLAYER; col++)
				{
					if(equipa->jogadores[line].nGolos>equipa->jogadores[col].nGolos)
					{
						jogAux = equipa->jogadores[line];
						equipa->jogadores[line] = equipa->jogadores[col];
						equipa->jogadores[col] = jogAux;				
					}				
				}
			}
		}
	}
	
}
void listAllPlayers()
{
	Jogadores jogador;
	   	FILE *jog = fopen("jogadores.txt","r");
   	printf("\nId\tApelido\tNome\tGolos\tInicio\tFim\tActivo\n");
	if(jog!=NULL)
	{
		while((fscanf(jog,"%d %s %s %d %s %s %d %s\n",&jogador.id,jogador.apelido,jogador.nome,&jogador.nGolos,jogador.dataCont,jogador.dataFimCon,&jogador.idEquipa,jogador.estado))!=EOF)
		{
			printf("%d\t%s\t%s\t%d\t%s\t%s\t%d\t%s\n",jogador.id,jogador.apelido,jogador.nome,jogador.nGolos,jogador.dataCont,jogador.dataFimCon,jogador.idEquipa,jogador.estado);
		}
	}
	fclose(jog);	
}
/*Fill the Struct*/
void fillStruct(Equipas equipa[])
{
	FILE *ekip=fopen("equipas.txt","r");
	int i=0,j=0;
	Jogadores jogador [SIZE_EQUIPA*SIZE_PLAYER];
	if(ekip!=NULL)
	{
		while((fscanf(ekip,"%d %s\n",&equipa[i].id,equipa[i].nome))!=EOF)
		{
			i++;
		}
	}else
	{
		printf("File not found!");
	}
	fclose(ekip);
	FILE *jog = fopen("jogadores.txt","r");
	i=0;

	if(jog!=NULL)
	{
		while((fscanf(jog,"%d %s %s %d %s %s %d %s\n",&jogador[i].id,jogador[i].apelido,jogador[i].nome,&jogador[i].nGolos,jogador[i].dataCont,jogador[i].dataFimCon,&jogador[i].idEquipa,jogador[i].estado))!=EOF)
		{
			i++;
		}
	}
	fclose(jog);
	completeFill(equipa,jogador);
}
/*Puts players into teams(equipas)**/
void completeFill(Equipas equipa[], Jogadores jogadores[])
{
	int i=0, j=0, index=0;
	for(i; i<SIZE_EQUIPA;i++)
	{
		for(j; j<SIZE_PLAYER; j++)
		{
			if(equipa[i].id==jogadores[j].idEquipa)
			{
				equipa[i].jogadores[index] = jogadores[j];
				index++;
			}
		}
		j=0;
		index=0;
	}
}
/**Check if Id exist or nor*/
int checkId(Equipas equipa[],int id)
{
	int i=0, retorno=0;
	for(i; i<SIZE_EQUIPA; i++)
	{
		if(equipa[i].id==id)
		{
			retorno=1;
			break;
		}
	}
	return retorno;
}