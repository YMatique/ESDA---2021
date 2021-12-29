/*Operacoes basicas com uma arvore binaria*/
/*
*DISCENTES
			Amarildo Mulandeza
			Imaculada Merissão
			Inalda Cumbane
			Manuel Bindo
			Paulo Joaquim Paulo
			Yuran Cumbane
			Yuvi Albino Matique

*/
#include <stdio.h>
#include <stdlib.h>

//basic struct
struct no
{
	int dado;
	struct no *esq;
	struct no *dir;
};
//
typedef struct no arvore;

/*
** prototipos de funcao
*/
arvore *insert(arvore *r, int val);
arvore *getMax(arvore *r);
arvore *getMin(arvore *r);
void printR(arvore *r);
arvore *busca(arvore *r, int val);
arvore *remocao(arvore *r, int val);

/*
	main function
	@param int, char 
	@return int
*/
int main(int argc, char** argv)
{

	arvore *root = NULL;

	root = insert(root,9);
	root = insert(root,4);
	root = insert(root,7);
	root = insert(root,6);
	root = insert(root,3);
	root = insert(root,2);
	root = insert(root,42);
	root = insert(root,41);
	root = insert(root,24);
	root = insert(root,49);
	
	printR(root);
    root = remocao(root,6);	
    
	printf("\n removido com sucesso...\n");
    
	printR(root);

	printf("\n\nO maximo eh: %d", getMax(root)->dado);
	printf("\nO minimo eh: %d", getMin(root)->dado);

	int n = 8;
	if(busca(root,n)!=NULL)
	{
		printf("\n\nO numero %d foi contrado\n", n);
	}else
	{
		printf("\n\nO numero %d nao foi encontrado \n", n);
	}
	free(root);
	return 0;
}

/*
	Insere um elemento na arvore
	@param tipo arvore
	@return arvore
*/
arvore *insert(arvore *r, int val)
{
	//verifica se o no actual eh nulo, caso seja, inserimos ai
	   if(r==NULL)
	   {
			  r = (arvore*)malloc(sizeof(arvore));
			  r->dado=val;
			  r->esq = NULL;
			  r->dir = NULL;
			  
	   }else
	   {
	   		//se nao for nullo, comparamos o valor existence e o valor a ser inserido
	   		//se o valor a ser inserido for menor, entao inserimos a esquerda
		   	   if(r->dado>val)
			   {
		 	   	  r->esq = insert(r->esq,val);
			   }else
			   {
			   	//se o valor a ser inserido for maior, inserimos a direita
				  r->dir = insert(r->dir,val);
			   }	
	   }
	   
	   return r;
}
/*
	obtem o maior elemento da arvore
	@param tipo arvore
	@return arvore
*/
arvore *getMax(arvore *r)
{
	//obviamente o maior sempre estara no lado direito da arvore
	arvore *aux = r;
	
	while(aux->dir!=NULL)
	{
		aux = aux->dir;
	}
	return aux;
}
/*
	obtem o menor elemento da arvore
	@param tipo arvore
	@return arvore
*/
arvore *getMin(arvore *r)
{
	//obviamente o menor sempre estara no lado esquerdo da arvore
	arvore *aux = r;
	
	while(aux->esq!=NULL)
	{
		aux = aux->esq;
	}
	return aux;
}

/*
	impressao recursiva
	@param tipo arvore
	@return void
*/
void printR(arvore *r)
{
	   arvore *aux = r;
	   
	   if(aux!=NULL)
	   {
	   		printf(" %d ",aux->dado);
	   		printR(aux->esq);
	   		printR(aux->dir);
	   }
}

/*realiza busca por elemento especifico
	@param tipo arvore e int;
	@return arvore
*/
arvore *busca(arvore *r, int val)
{
	arvore *aux =r;
	
	//se for nulo, nao existem elemento a se busca, logo deve retornar falso
	if(aux==NULL)
	{
		return NULL;
	}else
	{
		//caso a arvore nao esteja vazia, verificamos se 
		//o valor a ser buscado eh maior ou menor ao valor existente
		if(aux->dado < val)
		{
			//caso o valor buscado seja maior, 
			//realizamos busca no lado direito da arvore
			return busca(aux->dir,val);
		}else
		{
			if(aux->dado > val)
			{
				//caso o valor buscao seja menos, buscamos a esquerda
				return busca(aux->esq,val);
			}else
			{
				//a funcao vira neste trecho quando o valor procurado
				//nao for maior e nem menor, isto eh, so se for
				//igual
				return aux;
			}			
		}

	}
	
}
/*
	remove um elemento com o valor dado
	@param tipo arvore, int
	@return arvore
*/
arvore *remocao(arvore *r, int val)
{
	arvore *aux = r;

	//arvore vazia
	if(aux==NULL) 
	{
	   	return NULL;	
	}else
	{
	
		//remocao a equerda	
		if(aux->dado > val)
		{
			aux->esq = remocao(aux->esq,val);		
		}else
		{
			//remocao a direita
			if(aux->dado < val)
			{
				aux->dir = remocao(aux->dir,val);
			}else
			{
				//se o no em questao nao tiver filhos
				if(aux->esq==NULL && aux->dir==NULL)
				{
					   free(aux);	
					   aux = NULL;
				}else
				{
					//tem filho a direita
					if(aux->esq == NULL)
					{
						arvore *temp = aux;
						aux = temp->dir;
						free(temp);
						
					}else
					{
						//tem filho a esquerda
						if(aux->dir == NULL)
						{
							arvore *temp = aux;
							aux = temp->esq;
							free(temp);
						}else
						{
							//tem dois filhos
							arvore *temp = aux->esq;
							while(temp->dir != NULL)
							{
								temp = temp->dir;
							}
							aux->dado = temp->dado;
							temp->dado = val;
							aux->esq = remocao(aux->esq,val);
						}
					}
				}				
			}
		}
	}
	return aux;
}