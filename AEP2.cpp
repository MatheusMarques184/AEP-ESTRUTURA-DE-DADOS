#include <stdlib.h>
#include <stdio.h>
#include <conio.c>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <malloc.h>
#define ERRO -1
#define true 1
#define false 0

typedef int TIPOCHAVE;

typedef struct tempRegistro{
  TIPOCHAVE chave;
  int nroElem;
  char nomeCooperativa[40];
  char regResponsavel[40];
  char cultura[40];
  float hectares;
  struct tempRegistro *prox;
} REGISTRO;

typedef REGISTRO* PONT;

typedef struct {
  PONT inicio;
} LISTA;

//------------------------------------------------------------------------------
void inicializarLista(LISTA *l){
  l->inicio = NULL;
}

void exibirLista(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {1,FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");
  
  PONT end = l->inicio;
  printf("Lotes: \"");
  while (end != NULL){
    printf(" %d,", end->chave); 
    end = end->prox;
  }
  printf("\"");
}

int tamanho(LISTA *l) {
  PONT end = l->inicio;
  int tam = 0;
  while (end != NULL){
    tam++;
    end = end->prox;
  }
  return tam;
} 

int tamanhoEmBytes(LISTA *l) {
  return(tamanho(l) * sizeof(REGISTRO)) + sizeof(LISTA); 
}

PONT buscaSeq(TIPOCHAVE ch, LISTA *l){
  PONT pos = l->inicio;
  while (pos != NULL){
    if (pos->chave == ch) {
      return pos;
    }
    pos = pos->prox;
  }
  return NULL;
}

PONT buscaSeqExc(TIPOCHAVE ch, LISTA *l, PONT *ant){
  *ant = NULL;
  PONT pos = l->inicio;
  while ((pos != NULL) && (pos->chave<ch)){
    *ant = pos;
    pos = pos->prox;
  }
  if ((pos != NULL) && (pos->chave == ch)) {
           return pos;
  }
  return NULL;
} 

bool excluirElemLista(TIPOCHAVE ch, LISTA *l){
  PONT ant, i;
  i = buscaSeqExc(ch, l, &ant);
  if (i == NULL) {
    return false;
  }
  if (ant == NULL) {
    l->inicio = i->prox;
  }
  else { 
    ant->prox = i->prox;
  }
  free(i);
  return true;
} 

void destruirLista(LISTA *l) {
  PONT end = l->inicio;
  while (end != NULL){
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  l->inicio = NULL;
} 

bool inserirElemListaOrd(REGISTRO reg, LISTA *l) {
  TIPOCHAVE ch = reg.chave;
  PONT ant, i;
  i = buscaSeqExc(ch, l, &ant);
  if (i != NULL)  {
    return false;
  }
  i = (PONT) malloc(sizeof(REGISTRO));
  *i = reg;
  if (ant == NULL) { 
    i->prox = l->inicio;
    l->inicio = i;
  } else {  
    i->prox = ant->prox;
    ant->prox = i;
  }  
  return true;
} 

PONT retornarPrimeiro(LISTA *l, TIPOCHAVE *ch){
  if (l->inicio != NULL) {
    *ch = l->inicio->chave;
  }
  return l->inicio;
}

PONT retornarUltimo(LISTA *l, TIPOCHAVE *ch){
  PONT ultimo = l->inicio;
  if (l->inicio == NULL) {
    return NULL;
  }
  while (ultimo->prox != NULL) {
    ultimo = ultimo->prox;
  }
  *ch = ultimo->chave;
  return ultimo;

} 

void inserir(LISTA *l){
  system("cls");
  textbackground(0);
  textcolor(15);
  TIPOCHAVE ch;
  bool flag;
  PONT pos;
  do{
  	flag=false;
    printf("Digite o numero do lote que deseja registrar: ");
    scanf("%d",&ch);
    fflush(stdin);
    pos = buscaSeq(ch, l);
    if(pos == NULL) {
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
    printf("Lote %d inserido corretamente.\n",ch);
    textcolor(15);
    pos= buscaSeq(ch, l);
    printf("\nDigite o nome da cooperativa que vai ser destinado a producao do lote (caso nao houver aperte enter): ");
    gets(res);
    fflush(stdin);
    if(strcmp(res,"")!=0){
      strcpy(pos->nomeCooperativa, res);
    }
    printf("\nDigite o registro do responsavel pelo lote: ");
    scanf("%s",pos->regResponsavel);
    fflush(stdin);
    printf("\nDigite o tipo de cultura que sera plantada do lote: ");
    scanf("%s",&pos->cultura);
    fflush(stdin);
    printf("\nDigite o tamanho em hectares do lote: ");
    scanf("%f",&pos->hectares);
    fflush(stdin);
  }
  else {
    textcolor(4);
    printf("Nao foi possivel inserir o lote %d.\n",ch);
  }
  textcolor(15);
  printf("\n\n\n");
  system("pause");
}

void buscar(LISTA *l){
  system("cls");
  textbackground(0);
  textcolor(15);
  TIPOCHAVE ch;
  printf("Digite o numero do lote que deseja consultar: ");
  scanf("%d",&ch);
  PONT pos = buscaSeq(ch, l);
  if(pos != NULL){
    printf("pos: %i\n",pos);
    printf("Numero do lote: %i\n",pos->chave);
    if(strcmp(pos->nomeCooperativa,"")!=0){
      printf("Nome da cooperativa que ira comprar a producao do lote: %s\n",pos->nomeCooperativa); 
    }
    printf("Registro do responsavel pelo lote: %s\n",pos->regResponsavel); 
    printf("Tipo de cultura plantada no lote: %s\n",pos->cultura); 
    printf("Tamanho em hectare do lote: %f\n",pos->hectares);
  }
  if(pos == NULL){
    textcolor(4);
    printf("Lote %d nao encontrado.",ch);
  }
  textcolor(15);
  printf("\n\n\n");
  system("pause"); 
}

void exibirPrimeiro(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {1,FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");
  textcolor(15);
  TIPOCHAVE ch;
  PONT posicao = retornarPrimeiro(l,&ch);
  if (posicao != NULL) {
    textcolor(2);
    printf("Primeiro lote %d encontrado.\n",ch);
  }
  else {
    textcolor(4);
    printf("Nao foi possivel encontrar o primeiro lote (lista vazia).\n");
  }
  textcolor(15);
  printf("\n\n\n");
  system("pause");
}

void exibirUltimo(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {1,FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");
  textcolor(15);
  TIPOCHAVE ch;
  PONT posicao = retornarUltimo(l,&ch);
  if (posicao != NULL) {
    textcolor(2);
    printf("Ultimo lote %d encontrado.\n",ch);
  }
  else {
    textcolor(4);
    printf("Nao foi possivel encontrar o ultimo lote (lista vazia).\n");
  }
  textcolor(15);
  printf("\n\n\n");
  system("pause");
}

void excluir(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {1,FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");
  TIPOCHAVE ch;
  printf("Digite o numero do lote que deseja excluir: ");
  scanf("%d",&ch);
  if (excluirElemLista(ch,l)) {
    textcolor(2);                          
    printf("Lote %d excluido corretamente.\n",ch);
  }
  else {
    textcolor(4);
    printf("Nao foi possivel excluir o lote %d.\n",ch);
  }
  textcolor(15);
  printf("\n\n\n");
  system("pause");
}

void imprimirElementos(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {1,FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");
  exibirLista(l);
  printf("\n\n\n");
  system("pause");
}

void exibirDetalhesLista(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {1,FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");   
  printf("Numero de lotes na lista: %d.\n",tamanho(l));
  printf("Tamanho da lista (em bytes): %d.\n",tamanhoEmBytes(l));
  printf("\n\n\n");
  system("pause");
}

void destruir(LISTA *l){
  CONSOLE_CURSOR_INFO cursor = {1,FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  system("cls");
  textcolor(2);
  destruirLista(l);
  printf("Lista de lotes restaurados.\n");
  textcolor(15);
  printf("\n\n\n");
  system("pause");
}

int main(){
  LISTA lista;
  inicializarLista(&lista);
  int p=1,x,tecla;
  char item[10][37]={"",
  "Inserir numero de um novo lote     ", 
  "Excluir um lote                    ", 
  "Mostrar todos os lotes registrados ", 
  "Restaurar lotes                    ",
  "Exibir log de utilizacao da lista  ",
  "Mostrar detalhes do lote           ",
  "Exibir primeiro lote na lista      ",
  "Exibir ultimo lote na lista        ", 
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
    for (x=1; x<=9; x++){
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
    if (p==0) p=9;
    if (p==10) p=1;
    if (tecla==13){
       switch(p) {
         case 1 : inserir(&lista); break;
         case 2 : excluir(&lista); break;
         case 3 : imprimirElementos(&lista); break;
         case 4 : destruir(&lista); break;
         case 5 : exibirDetalhesLista(&lista); break;
         case 6 : buscar(&lista); break;
         case 7 : exibirPrimeiro(&lista); break;
         case 8 : exibirUltimo(&lista); break;
         case 9 : tecla=27; break;                
       }
    }
  }while (tecla!=27);    
}
