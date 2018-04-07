#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "header.h"



void clear(sARESTA arestas[TAM_VERTICES][TAM_VERTICES], sVERTICE vertices[TAM_VERTICES]){
  int i,j;
  for ( i = 0; i < TAM_VERTICES; i++) {
    for ( j = 0; j < TAM_VERTICES; j++) {
      arestas[i][j].custo = arestas[i][j].linha = 0;
    }
    vertices[i].nome = 0;
    vertices[i].aberto = 0;
    vertices[i].custo = 0;
    vertices[i].anterior = NULL;
    vertices[i].linhaAnterior = 0;
  }
}


void criar_aresta(sARESTA arestas[TAM_VERTICES][TAM_VERTICES], int u, int v, int linha, int custo){
  u--;
  v--;
  arestas[u][v].linha = linha;
  arestas[u][v].custo = custo;

  arestas[v][u].linha = linha;
  arestas[v][u].custo = custo;
}

void abrir_vertices(sVERTICE vertices[TAM_VERTICES]) {
  int i;
  for ( i = 0; i < TAM_VERTICES; i++) {
    vertices[i].aberto = 1;
    vertices[i].nome = i+1;
  }
}

void estimativa(sVERTICE vertices[TAM_VERTICES],int u) {
  int i;
  --u;
  for ( i = 0; i < TAM_VERTICES; i++) {
    if (u == i ) {
      vertices[i].custo = 0;
    }
    else{
      vertices[i].custo = INT_MAX/2;
    }
    vertices[i].anterior = NULL;
    vertices[i].linhaAnterior = 0;
  }
}


void dijkstra(sVERTICE vertices[TAM_VERTICES], sARESTA arestas[TAM_VERTICES][TAM_VERTICES]){
  int i=0,j, custoAdicional,k,*adj,linhaAtual,qtd,in=1;

  while (tem_aberto(vertices)) {

    i = menor_vertice(vertices);
    vertices[i].aberto = 0;

    adj = adjacente(arestas,i);
    qtd = quantidade_adj(arestas,i);
    for ( j = 0, k=0,custoAdicional=0; j <  qtd; j++) {
      k = adj[j];
      if (vertices[k].aberto) {
        if(vertices[i].custo + arestas[i][k].custo < vertices[k].custo){
            if (vertices[i].linhaAnterior != arestas[i][k].linha && !in) {
              custoAdicional = 6;
            }
            else{ custoAdicional = 0; }

            vertices[k].linhaAnterior = arestas[i][k].linha;
            vertices[k].anterior = &vertices[i];
            vertices[k].custo = vertices[i].custo + arestas[i][k].custo + custoAdicional;
        }
      }

    }
    in=0;
  }
}


void mostrar_rota(sVERTICE *vertices){

  printf("\nCaminho a ser percorrido\n" );
  percorrer(vertices);
  printf("Chegou\n" );
  printf("Tempo total: %d\n",vertices->custo );
}

void percorrer(sVERTICE *vertices){
  if (vertices->custo == 0) {
    printf("%d ", vertices->nome);
  }else{
    percorrer(vertices->anterior);

    printf("(Linha: %s; Tempo: %d) -> %d ", name_station(vertices->linhaAnterior),vertices->custo,vertices->nome);
  }
}


int tem_aberto(sVERTICE vertices[TAM_VERTICES]){
  int i;
  for ( i = 0; i < TAM_VERTICES; i++) {
    // printf("%d\n",i );
    if (vertices[i].aberto) {
      return 1;
    }
  }
  return 0;
}

int menor_vertice(sVERTICE vertices[TAM_VERTICES]){
  int menor =0,i;

  for ( i = 0; i < TAM_VERTICES; i++) {
    if (vertices[i].aberto) {
      menor = i;
      i = TAM_VERTICES;
    }
  }

  for (i = 0; i < TAM_VERTICES; i++) {
    if (vertices[i].aberto) {
      // printf("%s\n", );
      if (vertices[menor].custo > vertices[i].custo) {
        menor = i;
      }
    }
  }

  return menor;
}

int quantidade_adj(sARESTA arestas[TAM_VERTICES][TAM_VERTICES],int u){
  int quantidade = 0,i;
  for (i = 0; i < TAM_VERTICES; i++) {
    if (arestas[u][i].custo > 0) {
      quantidade++;
    }
  }
  return quantidade;
}

int *adjacente(sARESTA arestas[TAM_VERTICES][TAM_VERTICES],int u){
  int quantidade = 0,*adj,i,j;
  for (i = 0; i < TAM_VERTICES; i++) {
    if (arestas[u][i].custo > 0) {
      quantidade++;
    }
  }
  adj = (int *)malloc(quantidade*sizeof(int));

  for (i = 0,j=0; i < TAM_VERTICES; i++) {
    if (arestas[u][i].custo > 0) {
      adj[j++] = i;
    }
  }
  return adj;
}

char *name_station(int estacao){


  switch (estacao) {
    case 1: return "Vermelha";
    case 2: return "Verde";
    case 3: return "Azul";
    case 4: return "Amarela";
    case 5: return "Roxo";
    default: return "";
  }

}

int is_station(int valor) {
  if (valor <= 0 || valor > TAM_VERTICES) {
    return 0;
  }
  return 1;
}
