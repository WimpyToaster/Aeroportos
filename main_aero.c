 /* * * * * * * * * * * * * * * * * *
  * Projeto de IAED - IST TagusPark *
  * 				    *
  * Grupo TP___			    *
  * Autores: Antonio Terra nº 84___ *
  * 	     Miguel Viegas nº 84747 *
  * * * * * * * * * * * * * * * * * *



	* * * * * * * * * * * * * * *
	*  Bibliotecas e Constantes *
	* * * * * * * * * * * * * * */


#include <stdio.h>
#include <string.h>

#define ABERTO 1
#define FECHADO 0
#define TRUE 1
#define FALSE 0
#define AERO_MAX 1000
#define FALSO_INDEX_FLAG1 1335
#define FALSO_INDEX_FLAG2 1336
#define DOIS_FALSO_INDEX 1337



	/* * * * * * * * * * * * 
	 *  Estrutura de Dados *
	 * * * * * * * * * * * */

typedef struct{

	int cap_max;   /* Capacidade maxima do aeroporto  */
	char id[4];    /* Id de 3 letras incluindo o '\0' */
	int estado;    /* Fechado ou Aberto		  */
	int incoming;  /* Numero de voos que entram	  */
	int outgoing;  /* Numero de voos que saem	  */
		
}aeroporto;


/* prototipos */
void cria_aeroporto(char id1[], int capacidade);

void alt_cap_aero(char id1[], int capacidade);

void adiciona_voo_idavolta(char id1[], char id2[]);

void adiciona_rota(char id1[], char id2[]);

void remove_voo(char id1[], char id2[]);

void remove_voo_idavolta(char id1[], char id2[]);

void numero_voos(char id1[], char id2[]);

void maior_nr_voos();

void aeroporto_conetado();

void voo_popular();

void fechar_aeroporto(char id1[]);

void reabrir_aeroporto(char id1[]);

void ordenar_entrada_sistema();

void ordenar_alfabetica();

void ordenar_histograma();

int encontra_index_2(char id1[], char id2[], int index[]);	/*o index é o vetor onde se guarda os 2 index's de cada id*/

int encontra_indice(char id[]); /*repeticao da funcao anterior, mas apenas aceita 1 argumento*/

int nr_voos();


/*prototipos funcoes TAD aeroporto */

int aero_cap_max(int index);

int aero_estado(int index);

int aero_incoming(int index);

int aero_outgoing(int index);


/*variaveis globais*/

int total_aeroportos = 0;

aeroporto generico[AERO_MAX];

int voos[AERO_MAX][AERO_MAX] = {{0}};
/*inicializa todos os elementos do vetor a 0*/



int main()
{
	char input = 'U'; /* Inicialiazada a 'U' para entrar no ciclo
						 apenas 1 vez. Não corresponde a nenhuma
						 funcao. */
	char id1[4];
	char id2[4];
	int capacidade;
	int escolha_listagem;
	id1[3] = id2[3] = '\0';	
	
	while (input != 'X')
	{
		scanf(" %c", &input);
					
		switch (input)
		{
			case 'A':
			
				scanf(" %s %d", id1, &capacidade);
				cria_aeroporto(id1, capacidade);
				break;
			
			case 'I':
				
				scanf(" %s %d", id1, &capacidade);
				alt_cap_aero(id1, capacidade);
				break;
			
			case 'F':		
			
				scanf(" %s %s", id1, id2);
				adiciona_voo_idavolta(id1, id2);
				break;
			
			case 'G':		
			
				scanf(" %s %s", id1, id2);
				adiciona_rota(id1, id2);
				break;
				
			case 'R':		
			
				scanf(" %s %s", id1, id2);
				remove_voo(id1, id2);
				break;
				
			case 'S':		
			
				scanf(" %s %s", id1, id2);
				remove_voo_idavolta(id1, id2);
				break;
				
			case 'N':		
			
				scanf(" %s %s", id1, id2);
				numero_voos(id1, id2);
				break;
				
			case 'P':
			
				maior_nr_voos();
				break;
				
			case 'Q':
			
				aeroporto_conetado();
				break;
				
			case 'V':
			
				voo_popular();
				break;
			
			case 'C':
			
				scanf(" %s", id1);
				fechar_aeroporto(id1);
				break;
				
			case 'O':
			
				scanf(" %s", id1);
				reabrir_aeroporto(id1);
				break; 			
				
			case 'X': 
				printf("%d:%d\n",nr_voos() ,total_aeroportos);
				break;
				
			case 'L':
			
				scanf(" %d", &escolha_listagem);
				while ((escolha_listagem < 0) || (escolha_listagem > 2))
				{
					printf("Por favor introduza uma listagem disponivel.\n");
					scanf(" %d", &escolha_listagem);
				}
				switch (escolha_listagem)
				{
					case 0:
						
						ordenar_entrada_sistema();
						break;
						
					case 1:
					
						ordenar_alfabetica();
						break;
					
					case 2:
					
						ordenar_histograma();
						break;
				}
				break;
					
				
			default:
			
				printf("Comando nao reconhecido, por favor reintroduza a operacao.\n");
			
		}
	}
	return 0;
	
}

/* FUNCOES ANTONIO*/

void cria_aeroporto(char id1[], int capacidade)	/*funcao A*/
{
	generico[total_aeroportos].cap_max = capacidade;
    strcpy(generico[total_aeroportos].id, id1);
    generico[total_aeroportos].estado = ABERTO;
    generico[total_aeroportos].incoming = 0;
    generico[total_aeroportos].outgoing = 0;
	total_aeroportos++;
	
}

void alt_cap_aero(char id1[], int capacidade) /*funcao I*/
{
	int i = encontra_indice(id1);
	
	if (i == FALSO_INDEX_FLAG1 || 
		aero_estado(i) == FECHADO ||
		(capacidade + aero_cap_max(i)) <= 0 ||
		(capacidade + aero_cap_max(i)) < (aero_incoming(i) + aero_outgoing(i)))
	{
		printf("*Capacidade de %s inalterada\n", id1);
	}
	else
	{
		generico[i].cap_max += capacidade;
	}
}


void adiciona_voo_idavolta(char id1[], char id2[]) /*funcao F*/
{
	int index[2];
	int encontrados = encontra_index_2(id1, id2, index);

	if (encontrados == DOIS_FALSO_INDEX || 
		encontrados == FALSO_INDEX_FLAG1 || 
		encontrados == FALSO_INDEX_FLAG2 || 
		aero_cap_max(index[0]) < (aero_outgoing(index[0]) + 1 + aero_incoming(index[0]) + 1) || 
		aero_cap_max(index[1]) < (aero_outgoing(index[1]) + 1 + aero_incoming(index[1]) + 1) || 
		generico[index[0]].estado == FECHADO ||
		generico[index[1]].estado == FECHADO)
	{
		printf("*Impossivel adicionar voo RT %s %s\n", id1, id2);
	}
	else
	{
		voos[index[0]][index[1]] += 1;
		generico[index[1]].incoming += 1;
		generico[index[0]].outgoing += 1;
		
		voos[index[1]][index[0]] += 1;
		generico[index[0]].incoming += 1;
		generico[index[1]].outgoing += 1;

	}
}

void adiciona_rota(char id1[], char id2[])/*funcao G*/
{
	int index[2];
	int encontrados = encontra_index_2(id1, id2, index);

	if (encontrados == DOIS_FALSO_INDEX || 
		encontrados == FALSO_INDEX_FLAG1 || 
		encontrados == FALSO_INDEX_FLAG2 || 
		aero_cap_max(index[0]) < (aero_outgoing(index[0]) + 1 + aero_incoming(index[0])) || 
		aero_cap_max(index[1]) < (aero_outgoing(index[1]) + aero_incoming(index[1]) + 1) ||
		strcmp(id1, id2) == 0 || 
		generico[index[0]].estado == FECHADO ||
		generico[index[1]].estado == FECHADO)
	{
		printf("*Impossivel adicionar voo %s %s\n", id1, id2);
	}
	else
	{
		voos[index[0]][index[1]] += 1;
		generico[index[0]].outgoing += 1;
		generico[index[1]].incoming += 1;
		
	}
}

void remove_voo(char id1[], char id2[])/*funcao R*/
{
	int index[2];
	int encontrados = encontra_index_2(id1, id2, index);

	if (encontrados == DOIS_FALSO_INDEX || 
		encontrados == FALSO_INDEX_FLAG1 || 
		encontrados == FALSO_INDEX_FLAG2 || 
		voos[index[0]][index[1]] == 0 || 
		generico[index[0]].estado == FECHADO ||
		generico[index[1]].estado == FECHADO)
	{
		printf("*Impossivel remover voo %s %s\n", id1, id2);
	}
		
	else
	{
		voos[index[0]][index[1]] -= 1;
		generico[index[0]].outgoing -= 1;
		generico[index[1]].incoming -= 1;
	}

}

void remove_voo_idavolta(char id1[], char id2[])/*funcao S*/
{
	int index[2];
	int encontrados = encontra_index_2(id1, id2, index);

	if (encontrados == DOIS_FALSO_INDEX ||
	    encontrados == FALSO_INDEX_FLAG1 ||
	    encontrados == FALSO_INDEX_FLAG2 ||
	    voos[index[0]][index[1]] == 0 || 
	    voos[index[1]][index[0]] == 0 || 
	    generico[index[0]].estado == FECHADO ||
		generico[index[1]].estado == FECHADO)
	{
		printf("*Impossivel remover voo RT %s %s\n", id1, id2);
	}
		
	else
	{
		voos[index[0]][index[1]] -= 1;
		generico[index[0]].outgoing -= 1;
		generico[index[1]].incoming -= 1;
		
		voos[index[1]][index[0]] -= 1;
		generico[index[0]].incoming -= 1;
		generico[index[1]].outgoing -= 1;
				
	}
}

void numero_voos(char id1[], char id2[])/*funcao N*/
{
	int index[2];
	int nout;
	int nin;
	int encontrados = encontra_index_2(id1, id2, index);

	if (encontrados == DOIS_FALSO_INDEX)
	{
		printf("*Aeroporto %s inexistente\n", id1);
		printf("*Aeroporto %s inexistente\n", id2);
	}

	else if (encontrados == FALSO_INDEX_FLAG1)
	
		printf("*Aeroporto %s inexistente\n", id1);
	
	else if (encontrados == FALSO_INDEX_FLAG2)
	
		printf("*Aeroporto %s inexistente\n", id2);
	
	else
	{
		nout = voos[index[0]][index[1]];
		nin = voos[index[1]][index[0]];
		printf("Voos entre cidades %s:%s:%d:%d\n", id1, id2, nout, nin);
	}
	
}






























/*FUNCOES MIGUEL*/

void maior_nr_voos()	/*funcao P*/
{
	int i = 0;
	int buffer = 0;
	int index = 0;
	int nr_voos = 0;
	
	while (i < total_aeroportos)
	{
		nr_voos = aero_incoming(i) + aero_outgoing(i);
		
		if (buffer < nr_voos)
		{
			buffer = nr_voos;
			index = i;
		}
		i++;
	}
	
	printf("Aeroporto com mais rotas %s:%d:%d\n", generico[index].id, aero_outgoing(index), aero_incoming(index));

}

void aeroporto_conetado()	/*funcao Q*/
{
	int i1 = 0;
	int i2 = 0;
	int buffer = 0;
	int index = 0;
	int nr_aero = 0;
	
	while (i1 < total_aeroportos)
	{
		while (i2 < total_aeroportos)
		{
			if (voos[i1][i2] != 0)
			{
				buffer++;				
			}
			else 
			{
				if (voos[i2][i1] != 0)
				{
					buffer++;
				}
			}
			i2++;
		}
		
		if (nr_aero < buffer)
		{
			nr_aero  = buffer;
			index = i1;
		}
		i1++;
		i2 = 0;
		buffer = 0;
		
	}
	
	printf("Aeroporto com mais ligacoes %s:%d\n", generico[index].id, nr_aero);
			
}

void voo_popular()	/*funcao V*/
{
	int i1 = 0;
	int i2 = 0;
	int acumulador = 0;
	int index1 = 0;
	int index2 = 0;
	
	while (i1 < total_aeroportos)
	{
		while (i2 < total_aeroportos)
		{
			if (acumulador < voos[i1][i2])
			{
				acumulador = voos[i1][i2];
				index1 = i1;
				index2 = i2;
			
			}	
		i2++;
		
		}	
	i1++;
	i2 = 0;
	
	}
	printf("Voo mais popular %s:%s:%d\n", generico[index1].id, generico[index2].id, acumulador);
}

void fechar_aeroporto(char id1[])	/*funcao C*/
{
	int ind = encontra_indice(id1);
	int i = 0;
	if (ind == FALSO_INDEX_FLAG1)
		
		printf("*Aeroporto %s inexistente\n", id1);
	
	else
	{
		generico[ind].estado = FECHADO;
		generico[ind].outgoing = 0;
		generico[ind].incoming = 0;
		
		while (i < total_aeroportos)
		/*Remove todos os voos de ida e volta do aeroporto*/
		{
			if (voos[i][ind] > 0)
			{
				generico[i].outgoing -= voos[i][ind];
				voos[i][ind] = 0;
				
			}
			if (voos[ind][i] > 0)
			{
				generico[i].incoming -= voos[ind][i];
				voos[ind][i] = 0;
				
			}
			
			i++;
		}
	}
}

void reabrir_aeroporto(char id1[])/*funcao O*/
{
	int ind = encontra_indice(id1);
	
	if (ind == FALSO_INDEX_FLAG1)
		
		printf("Aeroporto %s inexistente\n", id1);
	
	else
		
		generico[ind].estado = ABERTO;
	
}

void ordenar_entrada_sistema()/*funcao L0*/
{
	int i = 0;
	for(; i < total_aeroportos; i++)
	{
		printf("%s:%d:%d:%d\n", generico[i].id, aero_cap_max(i), aero_outgoing(i), aero_incoming(i));
	}
	
}

void ordenar_alfabetica()/*funcao L1*/
{
	int i = 0;
	int j = 0;
	int buffer = 0;
	int pointer = 0;
	int index = 0;
	int memoria[total_aeroportos];
	
	i = 0;
	while (i < total_aeroportos)
	{
		memoria[i] = i;
		i++;	
	}
	
	i = 0;
	while (i < total_aeroportos)
	{
		while (j < total_aeroportos)
		{
			if (strcmp(generico[memoria[pointer]].id, generico[memoria[j]].id) > 0)
			{
				pointer = j;
			}
			j++;
		}	
		buffer = memoria[i];
		memoria[i] = memoria[pointer];
		memoria[pointer] = buffer;
		i++;
		j = i;
		pointer = i;
	}
	
	i = 0;
	while (i < total_aeroportos)
	{
		index = memoria[i];
		printf("%s:%d:%d:%d\n", generico[index].id, aero_cap_max(index), aero_outgoing(index), aero_incoming(index));
		i++;
		
	}
}

void ordenar_histograma()/*funcao L2*/
{
	int i = 0, t = 0;
	int buffer;
	int nr_voos = 0;
	int nr_aeros;
	
	/* ve qual o maior numero de voos */
	for(buffer = 0; i < total_aeroportos; i++) 
	{
		nr_voos = aero_incoming(i) + aero_outgoing(i);
		
		if (buffer < nr_voos)
		{
			buffer = nr_voos;
		}
	}

	/* faz print do histograma */
	for(i=0; i <= buffer ; i++)
	{
		t = 0;
		for(nr_aeros = 0; t < total_aeroportos; t++)
		{
			if( (aero_outgoing(t) + aero_incoming(t)) == i )
			{
				nr_aeros++;
			}
		}

		if (nr_aeros != 0)
			printf("%d:%d\n", i, nr_aeros);		
	} 
		
}























/* Funcoes TAD aeroporto */

int aero_cap_max(int index)
{
	return generico[index].cap_max;
}

int aero_estado(int index)
{
	return generico[index].estado;
}

int aero_incoming(int index)
{
	return generico[index].incoming;
}

int aero_outgoing(int index)
{
	return generico[index].outgoing;
}



/*FUNCOES AUXILIARES*/

int encontra_index_2(char id1[], char id2[], int index[])
{

	int i = 0;
	int flag1 = 0 , flag2 = 0;

	for (; i < total_aeroportos; i++)
	{
		if (flag1 == 0)
		{
			if(strcmp(generico[i].id, id1)==0)
			{
				index[0] = i;
				flag1 = 1;
			}
		}

		if (flag2 == 0)
		{
			if (strcmp(generico[i].id, id2)==0)
			{
				index[1] = i;
				flag2 = 1;
			}
		}
	}

	if (flag1 == 0 && flag2 == 0)

		return DOIS_FALSO_INDEX;

	else if (flag1 == 0)
		
		return FALSO_INDEX_FLAG1;

	else if (flag2 == 0)

		return FALSO_INDEX_FLAG2;

	else
		
		return 0;
		
}

int encontra_indice(char id[])
{
	int index = -1;
	int i = 0;
	
	while (i < total_aeroportos)
	{
		if (strcmp(generico[i].id, id) == 0)
		{
			index = i;
			break;
		}
		i++;
	}
	if (index == -1)
	
		return FALSO_INDEX_FLAG1;
	
	else
	
		return index;
}

int nr_voos()
{
	int i = 0;
	int acc = 0;
	
	while (i < total_aeroportos)
	{
		acc += generico[i].outgoing;
		i++;
	}
	
	return acc;

}


		
		
		
		
		
		
		
		
		
		
		
		
		
	
	
