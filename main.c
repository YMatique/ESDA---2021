#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int getPosition(Equipas equipa[], int id);

void redirect(Equipas equipa[])
{
	int op = mainMenu();
	int idEquipa;
	switch(op)
	{
	case 1:
		printf("Selecione a equipa:\n");
		listEquipas(equipa);
		scanf("%d",&idEquipa);
		if(checkId(equipa,idEquipa))
		{
			addJogador(idEquipa);
		}else
		{
			printf("nao encontrado");
		}
		break;
	case 2:
		printf("Selecione a equipa: \n");
		listEquipas(equipa);
		scanf("%d",&idEquipa);
		if(checkId(equipa,idEquipa))
		{
			int position = getPosition(equipa, idEquipa);
			listJogadores(equipa[position]);			
		}else
		{
			printf("nao encontrado");
		}
		break;
	case 3:
		listAllPlayers();
		break;
	case 4:
		printf("Selecione a equipa: \n");
		listEquipas(equipa);
		scanf("%d",&idEquipa);
					int position = getPosition(equipa, idEquipa);
			  		deleteThirdOne(&equipa[position]);
		break;
	case 5:
		break;
	default:
		break;
	}
}

int main()
{


	Equipas equipa[5];


	fillStruct(equipa);



	redirect(equipa);
	redirect(equipa);
	return 0;
}
void lixo()
{
	FILE *jog=fopen("equipas.txt","r");
	char nome[20];
	int id;
	if(jog!=NULL)
	{
		printf("\nId \t Equipa");
		while((fscanf(jog,"%d %s\n",&id,nome))!=EOF)
		{
			printf("\n%d \t %s",id,nome);
		}
	}else
	{
		printf("File not found!");
	}
	fclose(jog);	
}
int getPosition(Equipas equipa[], int id)
{
	int i=0, pos=1;
	for(i; i<SIZE_EQUIPA; i++)
	{
		if(equipa[i].id==id)
		{
			pos=i;
			break;
		}
	} 
	return pos;
}