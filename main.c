#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct no_ld {
	char dado[256];
	int frequencia;
	struct no_ld *prox, *ant;
}  Tno_ld;

/*******************************************************/
int Inicializar_LD(Tno_ld **inicio);
int Inserir_fim_LD (Tno_ld **inicio, char info[256]);
int Listar_LD (Tno_ld *inicio);
int Procurar_dado (Tno_ld *inicio, char *dado);
Tno_ld* addord(Tno_ld* t, float f, char n[256]);
Tno_ld* ordenarlista(Tno_ld *inicio);
int carrega(char *arq);
/*******************************************************/

/*******************************************************/
FILE *imagem;
Tno_ld *lista1;
/*******************************************************/

void gotoxy( int x, int y ){
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(){
    Inicializar_LD (&lista1);
    char arq[256];
	int erro,q;

    /*
    char a[10]="abcde",b[10]="abcde";
    erro=strcmp(a,b);
    printf("%d\n\n",erro);
    system("pause");
    */


    do {
	    system("cls");
	    gotoxy (20,1); printf("Algoritmo de Huffman");
		gotoxy(0,3); printf("Opcoes:");
		gotoxy(0,5);
		printf("1. Carregar Arquivo \n");
		printf("2. Exibir Lista de ocorrencias \n");
		printf("3. Criar arvore de huffman \n");
		printf("4. Exibir lista de criptografia \n");
		printf("5. Criptografar dados \n");
		printf("9. Sair \n");
		printf("\n> ");
		scanf("%d", &q);     /* Ler a opcao do usuario */
		switch(q) {
			case 1: printf("> Qual o nome do arquivo a ser comprimido?\n> ");
                    scanf("%s",arq);
                    erro=carrega(arq);
                    if (erro==0){
                        lfrequencia();
                        lista1=ordenarlista(lista1);
                    }
					break;
			case 2: erro=Listar_LD(lista1);
			        break;
			case 3: arvorehuffman();
                    system("pause");
			        break;
			case 4:
			        break;
			case 5:
			        break;
			case 9: break;
			default: printf("\n\n Opcao nao valida");
		}
		getchar();
	}
	while ( (q != 9) );


    return 0;
}

int carrega(char *arq){
    if ((imagem = fopen(arq, "r")) == NULL) {
        printf("Arquivo corrompido ou apagado -- %s\n",arq);
        system("pause");
        return 1;
    }
    return 0;
}

void lfrequencia(){
    Inicializar_LD (&lista1);
    char lixo[256]="0";
    char *aux=lixo;

    int existe=0;
    while( (fscanf(imagem,"%1s", aux))!=EOF ){
        existe=Procurar_dado (lista1,aux);
        if (existe==0){
            Inserir_fim_LD (&lista1, aux );
        }
    }
}

void arvorehuffman(){
    int au1,au2,au3;
    char aux1[256],aux2[256],aux3[256];
    strcpy(aux1,(lista1->dado));
    au1=lista1->frequencia;
    strcpy(aux2,(lista1->prox)->dado);
    au2=(lista1->prox)->frequencia;
    strcpy(aux3,(lista1->dado));
    au3=lista1->frequencia;
    strcat(aux3,aux2);
    int freq=(lista1->frequencia+(lista1->prox)->frequencia);
    lista1=addord(lista1, freq, aux3);
    Remover_inicio_LD (&lista1);
    Remover_inicio_LD (&lista1);

    if (lista1->prox!=NULL){
        arvorehuffman();
        printf("> Insere %s-%d\n",aux2,au2);
        printf("> Insere %s-%d\n",aux1,au1);
    }
    else{
        printf("> Insere %s-%d\n",lista1->dado,freq);
        printf("> Insere %s-%d\n",aux2,au2);
        printf("> Insere %s-%d\n",aux1,au1);
    }
    system("pause");
}

/***************** Lista ******************/
int Inicializar_LD (Tno_ld **inicio){
	*inicio= NULL;
	return 0; /* sem erro */
} /* Fim da fun��o de INICIALIZAR */

int Inserir_fim_LD (Tno_ld **inicio, char info[256]){
    Tno_ld *no_novo, *percorre;

    /* Criacao do novo no - Aloca��o de memoria */
    no_novo = (Tno_ld *) malloc(sizeof(Tno_ld));
    strcpy(no_novo -> dado, info);
    no_novo -> frequencia = 1;
    no_novo -> prox = NULL;

	if (*inicio==NULL)
	{ // lista vazia.
	    *inicio = no_novo;
	    no_novo -> ant = NULL;
	}
	else { // lista nao vazia
	     percorre = *inicio;
	     while (percorre->prox != NULL) // ate o ultimo
	     {
	         percorre = percorre -> prox;
	     }
	    percorre->prox = no_novo;  // liga��o do ultimo com o novo
	    no_novo -> ant = percorre; // liga o novo ultimo ao anterior
	}
	return 0;
}

int Listar_LD (Tno_ld *inicio){
	if (inicio == NULL){
        printf("Lista Vazia, impossivel listar\n");
        system("pause");

        return 1;  /* lista vazia */
	}

    printf("\n> LISTA:\n");
	while (inicio != NULL) {
		   printf(" -Caractere:%2s   ",inicio->dado);
		   printf(" Frequencia:%d\n",inicio->frequencia);
		   inicio = inicio->prox;
    }
    printf("\n");
    system("pause");
	return 0;
}

int Procurar_dado (Tno_ld *inicio, char *dado){
	if (inicio == NULL)
        return 0;

	while (inicio != NULL) {
        if( strcmp(dado , (inicio->dado))==0 ){
            inicio->frequencia +=1;
            return 1;
        }
        inicio = inicio->prox;
    }
	return 0;
}

Tno_ld* addord(Tno_ld* t, float f, char n[256]){
    Tno_ld* novo_no = (Tno_ld*) malloc(sizeof(Tno_ld)); //alocando memória para o novo nó
    Tno_ld* p; //ponteiro auxiliar para percorrer a lista
    int controle=0;

    strcpy(novo_no->dado, n);
    novo_no->frequencia = f;

    /*-------------------------------INSERE INICIO--------------------------------*/
    if(t==NULL){
        novo_no->ant = &t;
        novo_no->prox = NULL;
        t=novo_no;
        return t;
    }

    /*-------------------------------INSERE MEIO--------------------------------*/
    p=t;
    if(p->frequencia > f){
        novo_no->ant = &t;
        novo_no->prox = p;
        t->ant=novo_no;
        t=novo_no;
        return t;
    }
    while (p->prox!=NULL){ //percorrer até o final da lista
        if ((p->prox)->frequencia > f){
            novo_no->prox=p->prox;
            novo_no->ant=p->ant;
            p->prox=novo_no;
            (p->prox)->ant=novo_no;
            return t;
        }
        p = p->prox;
    }

    /*-------------------------------INSERE FIM--------------------------------*/
    (p->prox)=novo_no;  //chegou no final, amarrando o ultimo ao novo nó
    novo_no->ant=p;
    novo_no->prox=NULL;
    return t;
}

Tno_ld* ordenarlista(Tno_ld *inicio){
    if (inicio == NULL)
        return 1;  /* lista vazia */

    Tno_ld* auxiliar;
    auxiliar=inicio;
    Inicializar_LD (&inicio);

    while (auxiliar != NULL) {
        inicio=addord(inicio, auxiliar->frequencia, auxiliar->dado);
        auxiliar = auxiliar->prox;
    }

    return inicio;
}

int Remover_inicio_LD (Tno_ld **inicio){
    Tno_ld *aux;
    if (*inicio == NULL)
    {
         printf("\nLISTA VAZIA ! \nRemocao Impossivel\n");
        return 1;  /* lista vazia, impossivel remover primeiro */
    }
    else {
        aux = *inicio;
        *inicio = (*inicio)->prox;
        (*inicio)->ant = NULL;
        free(aux);
        return 0;
    }
}
/******************************************/
