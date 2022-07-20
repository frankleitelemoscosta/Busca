#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define zum 50
	//OBJETIVO:jogar as informações para o arquivo, coleta-las e opera-las aqui dentro.
typedef struct jack
{
	int linha;
	int coluna;
	int distancia;
	int uso;
}Position;

Position ordem[zum];

void destino(int *contadordetesouros,int *linha, int *coluna,int *inicioi,int *inicioj,int **matriz,int *fimi,int *fimj,int *numerodetesouros,int *t)
{
	for(int i = 0;i<*linha;i++)
	{
		for(int j=0;j<*coluna;j++)
		{
			if(*numerodetesouros<=*contadordetesouros)
			{
				
				if(matriz[i][j]==2)
				{
					matriz[*fimi][*fimj]=1;
					*inicioi=*fimi;
					*inicioj=*fimj;
					*fimi=i;
					*fimj=j;
					(*contadordetesouros)++;
					return;
				}
				
			}
		}
	}
			if(*numerodetesouros>1 && *t>0)
			{
				for(int i=0;i<*linha;i++)
				{
					for(int j=0;j<*coluna;j++)
						{
							if(i==0)
							{
								matriz[*fimi][*fimj]=1;
								*inicioi=*fimi;
								*inicioj=*fimj;
							}
							if(i!=*fimi && j!=*fimj && matriz[i][j]==3)
							{
								*fimi=i;
								*fimj=j;
								(*contadordetesouros)++;
								return;
							}
						}
				}
			}
			(*contadordetesouros)++;//com essa variavel o programa vai saber quando chegar o ultimo tesouro.
}
	
//tem de ter uma variavel para salvar a posição de onde inicial e para ser segurado até 

void retorno(int *linha,int *coluna,int *fimi,int *fimj,int *inicioi,int *inicioj,int **matriz)
{
	for(int i = 0;i<*linha;i++)
	{
		for(int j=0;j<*coluna;j++)
		{
			matriz[*fimi][*fimj]=1;
			*inicioi=*fimi;
			*inicioj=*fimj;
			if(i!=*fimi && j!=*fimj && matriz[i][j]==2)
			{
				*fimi=i;
				*fimj=j;
			}
		}
	}

}

int main()
{
	int linha,coluna,produto=0,i=0;
	int **matriz;
	char vetor[1000];//O VETOR É UTILIZADO APENAS COMO AUXILIADOR PARA PASSAR OS DADOS PARA MATRIZ DINAMICA.
	int linha2=0,coluna2=0,z=0;
	int fimi=0,fimj=0;
	int inicioi=0,inicioj=0;
	int numerodetesouros=0;
	
	
	printf("determine as linhas e colunas da matriz respectivamente:\n");
	scanf("%d%d",&linha,&coluna);//AQUI ESTOU DETERMINANDO O TAMANHO DA MATRIZ,FOI VEERIFICADO COM DOIS PRINTFS, ESTA SENDO PREENCHIDO CORRETAMENTE.

	
	linha2=linha;
	coluna2=coluna;
	
	linha2++;
	coluna2++;

	produto=linha2*coluna2;//COM ESSE CALCULO EU POSSIBILITO ENCOTRAR O TAMANHO CORRETO DO VETOR QUE VAI SER ARMAZENADO OS CARACTERES.
	

	matriz = (int**)malloc(linha*sizeof(int*));//AQUI EU FRANKINHO ALOCO MEMORIA PARA AS LINHAS.
	
	for(int i=0;i<linha;i++)
	{
		matriz[i]=(int*)malloc(coluna*sizeof(int));
	}	//AQUI EU FRANKINHO ALOCO MEMÓRIA PARA CADA ELEMENTO DA MATRIZ.
	
	

	
	FILE *arq = fopen("arq.txt","r");//AQUI EU ABRO O ARQUIVO PARA LEITURA.
	

	char aux;//ESSE AUXILIAR SERVE PARA SALVAR MOMENTANEAMENTE A VARIÁVEL.

	
	while(i<produto)//AQUI EU MOSTRO QUE A CONDIÇÃO 
	{
		aux=fgetc(arq);//COM O GETC SALVO CARACTER POR CARACTER DE CADA VEZ.
		if(aux!='\n' && aux!='\0')
		{
			vetor[i]=aux;
			i++;
		}
	}//COM ESSE WHILE EU FRANKINHO ADICIONEI TODOS OS CARACTERES DO ARQUIVO AO VETOR.
	

	fclose(arq);

	

	for(i = 0;i<linha;i++)
	{
		for(int j=0;j<coluna;j++)
		{
			if(vetor[z]!='\n' && vetor[z]!='\0')
			{
				if(vetor[z]=='~')
				{
					matriz[i][j]=5;
				}
				if(vetor[z]=='#')
				{
					matriz[i][j]=5;
				}
				if(vetor[z]=='*')
				{
					matriz[i][j]=5;
					matriz[i-1][j]=5;
					matriz[i+1][j]=5;
					matriz[i-1][j-1]=5;
					matriz[i-1][j+1]=5;
					matriz[i+1][j-1]=5;
					matriz[i+1][j+1]=5;
					matriz[i][j-1]=5;
					matriz[i][j+1]=5;
				}
				if(vetor[z]=='@')
				{
					matriz[i][j]=2;
					inicioi=i;
					inicioj=j;
				}
				if(vetor[z]=='!')
				{
					matriz[i][j]=3;
					fimi=i;
					fimj=j;
					numerodetesouros++;
				}
				if(vetor[z]=='.' && matriz[i][j]!=5)
				{
					matriz[i][j]=1;
				}
				z++;
			}
			
		}
	}//COM ESSE FOR EU SALVO TODAS OS CARACTERES DO VETOR NA MATRIZ DINÂMICA.


	printf("\n\n----printando o primeiro mapa do Jack Espirro-----\n\n");

	for(int i=0;i<linha;i++)
	{
		for(int j=0;j<coluna;j++)
		{
			printf("[%d]\t",matriz[i][j]);
		}
		printf("\n");
	}//COM ESSE FOR EU PRINTO A MATRIZ PARA O ABENÇOADO USUARIO.


	//DAQUI EM DIANTE VOU TRATAR DE COMEÇAR A ANDAR NA MATRIZ.

	int  distancia=0,contador=0; 
	

	for(int i=0;i<linha;i++)
	{
		for(int j=0;j<coluna;j++)
		{
			if(matriz[i][j]==1 && i<=inicioi && j<=inicioj || matriz[i][j]==2 && i<=inicioi && j<=inicioj)
			{
					contador++;
				
			}
				
		}	
	}// ESSE FOR É NECESSARIO POIS SE NÃO COMO VOU TER UMA CONDIÇÃO DE PARADA?
		
		int distaciacima=0,distanciabaixo=0,distanciaantecessor=0,distanciasucessor=0;//essas variaveis armazenam momentaneamente a distancia de cada casa próxima ao jack espirro.
		int icima=0,jcima=0, iantecessor=0,jantecessor=0, ibaixo=0,jbaixo=0,isucessor=0,jsucessor=0;//essas variaveis armazenam momentaneamente o valor da linha e da coluna para analise da distancia das casas que estão próximas da casa que o jack espirro andou
		int vetordecisao[4];//esse vetor tem por objetivo calcular a menor distancia para o jack andar.
		int p=0;
		int u=0;
		int contadorinformacao=0;
		int parada=2;
		int contadordehoras=0, aux12=0;
		int contadordetesouros=1;
		int t=0;

while(parada>1 || contadordetesouros<=numerodetesouros)
{
	i=i;
		if(i==0)//coloquei essa condição para determinar que o primeiro a ser armazenado na distancia vai ser a posição inicial do jackzão//A QUESTÃO É QUE ACHO QUE ISSO DEVERIA TER SIDO ARMAZENADO QUANDO LI OS POSSIVEIS LUGARES ONDE ELE PODE ANDAR.
			{
				ordem[u].linha=inicioi;
				ordem[u].coluna=inicioj;
				distancia=abs(fimi-inicioi)+abs(fimj-inicioj);
				vetordecisao[p]=distancia;
				ordem[u].distancia=distancia;
				u++;
				p++;
				contadorinformacao++;
			}//com esse if eu garanto que a primeira posição vai ser a do jackzão.
			i=i;
			if(i>0)//depois que é salvo a primeira casa não entra na condicional de cima e sim nessa aqui.
			{

				//AQUI SE TRATA A CASA DE CIMA

				if(matriz[inicioi-1][inicioj]==1 && inicioi<=linha && inicioj<=coluna)
				{
					icima=inicioi-1;
					jcima=inicioj;
					ordem[u].linha=icima;
					ordem[u].coluna=jcima;
					distancia=abs(fimi-icima)+abs(fimj-jcima);
					vetordecisao[p]=distancia;
					ordem[u].distancia=distancia;
					p++;
					u++;
					contadorinformacao++;
				}
				else if(matriz[inicioi-1][inicioj]!=1 && inicioi<=linha && inicioj<=coluna)
				{
					vetordecisao[p]=1000;
					p++;
				}
				
				//AQUI SE TRATA A CASA ANTECESSORA

				if(matriz[inicioi][inicioj-1]==1 && inicioi<=linha && inicioj<=coluna)
				{
					iantecessor=inicioi;
					jantecessor=inicioj-1;
					ordem[u].linha=iantecessor;
					ordem[u].coluna=jantecessor;
					distancia=abs(fimi-iantecessor)+abs(fimj-jantecessor);
					vetordecisao[p]=distancia;
					ordem[u].distancia=distancia;
					p++;
					u++;
					contadorinformacao++;
				}
				else if(matriz[inicioi][inicioj-1]!=1 && inicioi<=linha && inicioj<=coluna)
				{
					vetordecisao[p]=1000;
					p++;
				}
				i=i;
				//AQUI SE TRATA A CASA DE BAIXO

				if(matriz[inicioi+1][inicioj]==1 && inicioi<=linha && inicioj<=coluna)
				{
					ibaixo=inicioi+1;
					jbaixo=inicioj;
					ordem[u].linha=ibaixo;
					ordem[u].coluna=jbaixo;
					distancia=abs(fimi-ibaixo)+abs(fimj-jbaixo);
					vetordecisao[p]=distancia;
					ordem[u].distancia=distancia;
					p++;
					u++;
					contadorinformacao++;

				}
				else if(matriz[inicioi+1][inicioj]!=1 && inicioi<=linha && inicioj<=coluna)
				{
					vetordecisao[p]=1000;
					p++;
				}
				contadorinformacao=contadorinformacao;
				u=u;
				contadordehoras=contadordehoras;

				//AQUI SE TRATA DA CASA SUCESSORA

				if(matriz[inicioi][inicioj+1]==1 && inicioi<=linha && inicioj<=coluna)
				{
					isucessor=inicioi;
					jsucessor=inicioj+1;
					ordem[u].linha=isucessor;
					ordem[u].coluna=jsucessor;
					distancia=abs(fimi-isucessor)+abs(fimj-jsucessor);
					vetordecisao[p]=distancia;// assim apos o calculo da distancia eu armazeno no vetor.
					ordem[u].distancia=distancia;//to utilizando i pois assim eu consigo acompanhar a contagem de mudança
					p++;
					u++;
					contadorinformacao++;
				}
				else if(matriz[inicioi][inicioj+1]!=1 && inicioi<=linha && inicioj<=coluna)//coloquei o se não para caso ser rodado novamente ele não comparar com lixo de memoria que pode resultar em 0
				{
					vetordecisao[p]=1000;
					p++;
				}
			}

				for(int l=0;l<4;l++)//COM ESSE FOR É FEITO A AVERIGUAÇÃO DO MENOR RESULTADO.
				{
					for(int g=l+1;g<4;g++)
					{
						if(vetordecisao[l]>vetordecisao[g])
						{
							aux12=vetordecisao[l];
							vetordecisao[l]=vetordecisao[g];//esse vetor permite o programa decidir a menor distancia, para que eu possa escolher qual posição da struct printar.
							vetordecisao[g]=aux12;
						}
					}
				}//cada vez que ele decidir eu posso colocar para printar de acordo com uma comparação quando lido a struct,// o que tem de ir para essa struct é a linha a coluna e a distancia, pois assim consigo comparar a distancia e encontrar o conjunto de informações associados a ela.
				//E AI TENHO QUE ALTERAR O VALOR DE IINICIO E JINICIO PARA QUE ELE FASSA A LEITURA NESSA CASA NA MATRIZ
			p=0;
			for(int k=0;k<contadorinformacao;k++)
			{
				if(ordem[k].distancia==vetordecisao[0] && ordem[k].uso==0)//aqui como ordenei o vetor
				{
					ordem[k].uso=1;
					contadordehoras++;
					inicioi=ordem[k].linha;
					inicioj=ordem[k].coluna;
				}	
			}

			//AQUI É ENCERRADO O FOR QUE TRATA DE ANALISAR A DISTANCIA E SE AS CASAS VIZINHAS PARA O JACKZÃO ANDAR.
		
		parada=abs(fimi-inicioi)+abs(fimj-inicioj);
		if(parada==1)
		{
			destino(&contadordetesouros,&linha,&coluna,&inicioi,&inicioj,matriz,&fimi,&fimj,&numerodetesouros,&t);
			
			if(t>0 && numerodetesouros==1)
			{

				printf("numero de horas para pegar o tesouro \n[%d]\n", contadordehoras);

				for(int i=0;i<linha;i++)
				{
					free(matriz[i]);
				}//LIBERA A MEMORIA ARMAZENADA.

				free(matriz);

				return 0;
			}
			t++;
		}
		if(contadordetesouros>numerodetesouros && numerodetesouros>1)
		{
			retorno(&linha,&coluna,&fimi,&fimj,&inicioi,&inicioj,matriz);
		}
		parada=abs(fimi-inicioi)+abs(fimj-inicioj);
	i++;	
}

}