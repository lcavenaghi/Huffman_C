#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct no_ld {
	char dado;
	int frequencia;
	struct no_ld *prox, *ant;
}  Tno_ld;

int Inicializar_LD(Tno_ld **inicio);
int Inserir_fim_LD (Tno_ld **inicio, char info);
int Listar_LD (Tno_ld *inicio);
int Procurar_dado (Tno_ld *inicio, char dado);

FILE *imagem;
Tno_ld *lista1;
Inicializar_LD (lista1);

void gotoxy( int x, int y ){
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(){
	int erro,pos;
    carrega();
    lfrequencia();
    erro=Listar_LD (lista1);
    if (erro==1)
        printf("\nLista vazia. Impossivel listar\n");

    return 0;
}

void carrega(){
    if ((imagem = fopen("hue.txt", "r")) == NULL) {
        system("cls");
        printf("Arquivo corrompido ou apagado -- hue.bmp\n ");
        exit(0);
    }
}

void lfrequencia(){
    char aux;
    int existe;
    while( (fscanf(imagem,"%c", &aux))!=EOF ){
        existe=Procurar_dado (lista1,aux);
        if (existe==0)
            Inserir_fim_LD (&lista1, aux);
    }
}

/***************** Lista ******************/
int Inicializar_LD (Tno_ld **inicio){
	*inicio= NULL;
	return 0; /* sem erro */
} /* Fim da fun��o de INICIALIZAR */

int Inserir_fim_LD (Tno_ld **inicio, char info){
    Tno_ld *no_novo, *percorre;

    /* Criacao do novo no - Aloca��o de memoria */
    no_novo = (Tno_ld *) malloc(sizeof(Tno_ld));
    no_novo -> dado = info;
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
	int i;
	if (inicio == NULL)
        return 1;  /* lista vazia */

    printf("LISTA :\n");
	while (inicio != NULL) {
		   printf("  Caractere:%c \t",inicio->dado);
		   printf("  Frequencia:%d\n",inicio->frequencia);
		   inicio = inicio->prox;
    }
    printf("\n");
	return 0;
}

int Procurar_dado (Tno_ld *inicio, char dado){
	int i;
	if (inicio == NULL)
        return 0;

	while (inicio != NULL) {
        if(dado == (inicio->dado) ){
            inicio->frequencia +=1;
            return 1;
        }
        inicio = inicio->prox;
    }
	return 0;
}
/******************************************/
