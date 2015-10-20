#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct no_ld {
	char dado[256];
	char cripto[256];
	int frequencia;
	struct no_ld *prox, *ant;
}  Tno_ld;

/*******************************************************/
int Inicializar_LD(Tno_ld **inicio);
int Inserir_fim_LD (Tno_ld **inicio, char info[256]);
int Listar_LD (Tno_ld *inicio);
int Procurar_dado (Tno_ld *inicio, char *dado);
int Procurar_cripto (Tno_ld *inicio);
Tno_ld* addord(Tno_ld* t, float f, char n[256]);
Tno_ld* ordenarlista(Tno_ld *inicio);
int carrega(char *arq);
int carrega2(char *arq);
void converte(Tno_ld *inicio, char *dado);
void displayBits(char value);
void displayBits2(char value);
/*******************************************************/

/*******************************************************/
FILE *imagem;
FILE *saida;
FILE *criptografado;
FILE *descriptografado;
Tno_ld *lista1;
Tno_ld *lista2;
char cript[256]=" ";
char encriptado=NULL;
char descrip[256]="";
int bits=0;
int totalbits=0;
int totalbits2=0;
/*******************************************************/

void gotoxy( int x, int y ){
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(){
    Inicializar_LD (&lista1);
    Inicializar_LD (&lista2);
    char arq[256],arq2[256];
	int erro,opt;
	int arvorizado=0;

    do {
	    system("cls");
	    gotoxy (20,1); printf("Algoritmo de Huffman");
		gotoxy(0,3); printf("Opcoes:");
		gotoxy(0,5);
		printf("1. Carregar Arquivo \n");
		printf("2. Comprimir dados \n");
		printf("3. Descomprimir dados \n");
		printf("8. Exibir lista de criptografia \n");
		printf("9. Sair \n");
		printf("\n> ");
		scanf("%d", &opt);
		switch(opt) {
			case 1: printf("> Qual o nome do arquivo a ser comprimido?\n> ");
                    scanf("%s",arq);
                    erro=carrega(arq);
                    if (erro==0){
                        lfrequencia();
                        lista1=ordenarlista(lista1);
                    }
                    if(arvorizado==0){
                        lista2=ordenarlista(lista1); //copia de lista1
                        arvorizado=arvorehuffman();
                    }
                    else{
                        printf("Ja foi criado\n");
                        system("pause");
                    }
                    fclose(imagem);
					break;
			case 2: if(arvorizado==0){
                        printf("Ainda nao existe lista de conversao\n");
                        system("pause");
                    }
                    else{
                        printf("> Qual o nome do arquivo de saida?\n> ");
                        erro=carrega(arq);
                        scanf("%s",arq);
                        erro=carrega2(arq);
                        criptografa(arq);
                        fclose(saida);
                        fclose(imagem);
                    }
			        break;
			case 3: printf("> Qual o nome do arquivo comprimido?\n> ");
                    scanf("%s",arq);
                    printf("> Qual o nome do arquivo de saida?\n> ");
                    scanf("%s",arq2);
                    erro=descriptografa(arq,arq2);
                    fclose(criptografado);
                    fclose(descriptografado);
                    break;
            case 8: erro=Listar_LD(lista2);
			        break;
			case 9: break;
			default: printf("\n\n Opcao nao valida");
		}
		getchar();
	}
	while ( (opt != 9) );

    return 0;
}

int carrega(char *arq){
    if ((imagem = fopen(arq, "rb")) == NULL) {
        printf("Arquivo corrompido ou apagado -- %s\n",arq);
        system("pause");
        return 1;
    }
    return 0;
}

int carrega2(char *arq){
    if ((saida = fopen(arq, "wb")) == NULL) {
        printf("Arquivo nao pode ser criado -- %s\n",arq);
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
    while( (fgets (aux, 2, imagem))!=0 ){
        existe=Procurar_dado (lista1,aux);
        if (existe==0){
            Inserir_fim_LD (&lista1, aux );
        }
    }
}

int arvorehuffman(){
    if (lista1==NULL){
        printf("Arquivo nao carregado ou Lista Vazia\n");
        system("pause");
        return 0;
    }

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
        insereesq(lista2,aux2);
        inseredir(lista2,aux1);
    }
    else{
        printf("> Raiz %s-%d\n",lista1->dado,freq);
        insereesq(lista2,aux2);
        inseredir(lista2,aux1);
    }

    return 1;
}

void insereesq(Tno_ld *inicio,char *dadocompleto){
	if (inicio == NULL)
        return 0;
    int i=0;
    char aux[10];

    while(dadocompleto[i]!=NULL){
        aux[0]=dadocompleto[i];
        while (inicio != NULL) {
            if( strcmp(aux , (inicio->dado))==0 ){
                strcat(inicio->cripto,"1");
            }
            inicio = inicio->prox;
        }
        inicio=lista2;
        i++;
    }
    return 0;
}

void inseredir(Tno_ld *inicio,char *dadocompleto){
	if (inicio == NULL)
        return 0;
    int i=0;
    char aux[10];

    while(dadocompleto[i]!=NULL){
        aux[0]=dadocompleto[i];
        while (inicio != NULL) {
            if( strcmp(aux , (inicio->dado))==0 ){
                strcat(inicio->cripto,"0");
            }
            inicio = inicio->prox;
        }
        inicio=lista2;
        i++;
    }
    return 0;
}

void criptografa(){
    char aux2[256]="0";
    char *aux=aux2;

    printf("Convertendo dados\n");
    _sleep(10);

    while( (fgets (aux, 2, imagem))!=0){
        converte(lista2,aux);
    }
    printf("Resto(%d)=",bits);
    if(bits>0){
        encriptado<<=(8-bits);
        displayBits(encriptado);
        fprintf(saida, "%c", encriptado);
    }

    printf("Total de bits=%d\n\n",totalbits);
    system("pause");
}

void converte(Tno_ld *inicio, char *dado){
    int i;
    char aux;
	while (inicio != NULL) {
        if( strcmp(dado , (inicio->dado))==0 ){
            i=0;
            while(inicio->cripto[i]!=NULL){
                if(bits==8){
                    bits=0;
                    displayBits(encriptado);
                    fprintf(saida, "%c", encriptado);
                    encriptado=NULL;
                }

                if (inicio->cripto[i]=='0')
                    aux=0x00;
                if (inicio->cripto[i]=='1')
                    aux=0x01;
                encriptado<<=1;
                encriptado=encriptado|aux;
                bits++;
                totalbits++;
                //printf("%c\n", inicio->cripto[i]);
                i++;
            }
        }
        inicio = inicio->prox;
    }
    return 0;
}

int descriptografa(char *arq, char *arq2){
    if ((descriptografado = fopen(arq2, "wb")) == NULL) {
        printf("Arquivo nao pode ser criado -- %s\n",arq2);
        system("pause");
        return 1;
    }

    if ((criptografado = fopen(arq, "rb")) == NULL){
        printf("Arquivo corrompido ou apagado -- %s\n",arq);
        system("pause");
        return 1;
    }

    /*
    int i=0;
    char aux;
    while( (aux = fgetc(criptografado)) != EOF){
        i++;
        printf("%d Dado- %c\n",i,aux);
        //displayBits2(aux);
    }
    */


    char aux2;
    char aux[2];
    while( (fgets (aux, 2, criptografado))!=0 ){
        aux2=aux[0];
        displayBits2(aux2);
        //printf("%c", aux2);
    }



    printf("\n");
    system("pause");
    return 0;
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
    strcpy(no_novo->cripto, "");
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
		   printf(" Frequencia:%4d   ",inicio->frequencia);
		   printf(" Cripto:%s\n",inicio->cripto);
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
    strcpy(novo_no->cripto, "");
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

/*************** Bits *********************/
void displayBits(char value){
    unsigned c;
    unsigned displayMask = 1 << 8;
    for(c=1;c<=8;c++){
        //putchar(value & displayMask ?'1':'0');
        value <<= 1;
    }
    //putchar('\n');
}

void displayBits2(char value){
    int i,achou;
    unsigned displayMask = 1 << 8;
    char auxiliar[1];
    Tno_ld* p;

    //printf("%c - %d = ",value,value);
    for(i=1;i<=8;i++){
        auxiliar[0]=(value & displayMask ?'1':'0');
        strcat(descrip,auxiliar);

        //achou=Procurar_cripto (lista2);
        p=lista2;
        while (p != NULL) {
            if( strcmp(descrip , (p->cripto))==0 ){
                //printf("Imprimindo %s dado<%d> de <%d>\n", p->dado,totalbits2,totalbits);
                fprintf(descriptografado, "%s", p->dado);
                strcpy(descrip,"");
                break;
            }
            if (totalbits2>=totalbits)
                break;
            p = p->prox;
        }
        totalbits2++;

        value <<= 1;
    }
}
/******************************************/
