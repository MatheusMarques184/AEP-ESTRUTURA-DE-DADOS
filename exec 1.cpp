#include <stdlib.h>
#include <stdio.h>
#include <conio.c>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAX 5
#define ERRO -1

typedef int TIPOCHAVE;

typedef struct{
  TIPOCHAVE chave;
  int nroElem;
  char nomeCooperativa[40];
  char regResponsavel[40];
  char cultura[40];
  float hectares;
} REGISTRO;

typedef struct {
  REGISTRO A[MAX+1];
  int nroElem;
} LISTA;


//------------------------------------------------------------------------------
void inicializarLista(LISTA *l){
  l->nroElem = 0;
} 

void exibirLista(LISTA *l){
  int i;
  printf("Lista: \" ");
  for (i=0; i < l->nroElem; i++)
    printf("%d ", l->A[i].chave); 
  printf("\"\n");
} 

int tamanho(LISTA *l) {
  return(l->nroElem);
} 

int tamanhoEmBytes(LISTA *l) {
  return(sizeof(LISTA));
} 

void destruirLista(LISTA *l) {
  l->nroElem = 0;
} 

bool inserirElemLista(REGISTRO reg, int i, LISTA *l){
  int j;
  if ((l->nroElem >= MAX) || (i < 1) || (i > (l->nroElem+1))) {
    return(false);
  }
  if((l->nroElem > 0) && (i < l->nroElem+1)){
    for (j = l->nroElem; j >= i; j--) {
       l->A[j] = l->A[j-1];
       }
  }   
  l->A[i-1] = reg;
  l->nroElem++;
  return(true);
} 

int buscaSeq(TIPOCHAVE ch, LISTA *l) {
  int i = 0;
  while (i < l->nroElem){
    if(ch == l->A[i].chave) {
          return(i);
    }
    else {
         i++;
    }
  }
  return(ERRO);
}

bool inserirElemListaOrd(REGISTRO reg, LISTA *l) {
  int i = 0;
  TIPOCHAVE ch = reg.chave;
  if(l->nroElem >= MAX) {
    return(false);
  }
  l->A[l->nroElem].chave = ch;
  while(l->A[i].chave < ch) {
    i++;
  } 
  if((l->A[i].chave == ch) && (i < l->nroElem)) {
    return(false); 
  }
  else {
    return(inserirElemLista(reg, i+1, l));
  }  
}

bool excluirElemLista(TIPOCHAVE ch, LISTA *l) { 
  int pos, j;
  pos = buscaSeq(ch, l);
  if(pos == ERRO) {
    return(false);
  }
  for(j = pos; j < l->nroElem-1; j++) {
    l->A[j] = l->A[j+1];
  }
  l->nroElem--;
  return(true);
}

void detalheLote(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {1,FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");
  textbackground(0);
  textcolor(15);
  TIPOCHAVE ch;
  printf("Digite o numero do lote que deseja consultar: ");
  scanf("%d",&ch);
  int i = buscaSeq(ch,l);
  printf("Numero do lote: %i\n",l->A[i].chave);
  if(strcmp(l->A[i].nomeCooperativa,"")!=0){
    printf("Nome da cooperativa que ira comprar a producao do lote: %s\n",l->A[i].nomeCooperativa); 
  }
  printf("Registro do responsavel pelo lote: %s\n",l->A[i].regResponsavel); 
  printf("Tipo de cultura plantada no lote: %s\n",l->A[i].cultura); 
  printf("Tamanho em hectare do lote: %f\n",l->A[i].hectares);
  textcolor(15);
  printf("\n\n\n");
  system("pause"); 
}

void inserir(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {2,TRUE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");
  textbackground(0);
  textcolor(15);
  TIPOCHAVE ch;
  bool flag;
  int pos;
  do{
  	flag=false;
    printf("Digite o numero do lote que deseja registrar: ");
    scanf("%d",&ch);
    fflush(stdin);
    pos = buscaSeq(ch, l);
    if(pos == ERRO) {
      flag=true;
    }
    else{
         printf("\nERROR: Numero do lote ja esta registrado\n\n");
         }
  }while(flag==false);
  REGISTRO reg;
  reg.chave = ch;
  char res[40]="";
  if (inserirElemListaOrd(reg,l)) {
    textcolor(2);
    printf("Elemento %d inserido corretamente.\n",ch);
    pos = buscaSeq(ch, l);
    textcolor(15);
    printf("\nDigite o nome da cooperativa que vai ser destinado a producao do lote (caso nao houver aperte enter): ");
    gets(res);
    fflush(stdin);
    if(strcmp(res,"")!=0){
      strcpy(l->A[pos].nomeCooperativa, res);
    }
    printf("\nDigite o registro do responsavel pelo lote: ");
    scanf("%s",&l->A[pos].regResponsavel);
    fflush(stdin);
    printf("\nDigite o tipo de cultura que sera plantada do lote: ");
    scanf("%s",&l->A[pos].cultura);
    fflush(stdin);
    printf("\nDigite o tamanho em hectares do lote: ");
    scanf("%f",&l->A[pos].hectares);
    fflush(stdin);
  }
  else {
    textcolor(4);
    printf("Nao foi possivel inserir elemento %d.\n",ch);
  }
  printf("\n\n\n");
  system("pause");
}

void excluir(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {1,FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");
  textbackground(0);
  textcolor(15);
  TIPOCHAVE ch;
  printf("Digite o numero do lote que deseja excluir: ");
  scanf("%d",&ch);
  if (excluirElemLista(ch,l)) {
    textcolor(2);
    printf("lote %d excluido com sucesso.\n",ch);
  }
  else {
    textcolor(4);
    printf("Nao foi possivel excluir o lote %d.\n",ch);
  }
  textcolor(15);
  printf("\n\n\n");
  system("pause"); 
}

void imprimir_elementos(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {1,FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");
  textbackground(0);
  textcolor(15);
  int i;
  printf("Lotes: \"");
  for (i=0; i < l->nroElem; i++){
    printf("%d", l->A[i].chave);
    if(i<l->nroElem-1){
      printf(", ");
    }
  }
  printf("\""); 
  printf("\n\n\n");
  system("pause");
}

void exibir_detalhes_fila(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {1,FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");
  textcolor(2);
  printf("Numero de elementos na lista: %d.\n",tamanho(l));
  printf("Tamanho da lista (em bytes): %d.\n",tamanhoEmBytes(l));
  textcolor(15);
  printf("\n\n\n");
  system("pause");
}

void destruir(LISTA *l){
    CONSOLE_CURSOR_INFO cursor = {1,FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    system("cls");
    textcolor(2);
    destruirLista(l);
    printf("Lista de lotes restaurados.\n");\
    textcolor(15);
    printf("\n\n\n");
    system("pause");
}

int main(){
  LISTA lista;
  inicializarLista(&lista);
  int p=1,x,tecla;
  char item[8][37]={"",
  "Inserir numero de um novo lote     ", 
  "Excluir um lote                    ", 
  "Mostrar todos os lotes registrados ", 
  "Restaurar lotes                    ",
  "Exibir log de utilizacao da lisla   ",
  "Mostrar detalhes do lote           ",
  "Sair                               ",
};
  do{
    CONSOLE_CURSOR_INFO cursor = {1,FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    system("cls");
    textcolor(1);
    gotoxy(37,2); printf("H O M E");
    textcolor(15); 
    textbackground(0);
    for (x=1; x<=7; x++){
      gotoxy(10,9+x);
      printf(item[x]);  
    }
    textcolor(1);
    textbackground(3);
    gotoxy(10,9+p);
    printf("%s",item[p]);
    textcolor(15); 
    textbackground(0); 
    tecla=getch();
    if (tecla==224 || tecla==0){
      tecla=getch();
    }
    switch (tecla){
      case 72:p--; break;     
      case 80:p++; break;            
    }
    if (p==0) p=7;
    if (p==8) p=1;
    if (tecla==13){
       switch(p) {
         case 1 : inserir(&lista); break;
         case 2 : excluir(&lista); break;
         case 3 : imprimir_elementos(&lista); break;
         case 4 : destruir(&lista); break;
         case 5 : exibir_detalhes_fila(&lista); break;
         case 6 : detalheLote(&lista); break;
         case 7 : tecla=27; break;                
       }
    }
  }while (tecla!=27);
}
