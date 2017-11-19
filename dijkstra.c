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
  int i=0,j, custoAdicional,k,*adj,linhaAtual,qtd,in=1,l=0;
  while (tem_aberto(vertices)) {
    l=i;
    i = menor_vertice(vertices);
    vertices[i].aberto = 0;
    // printf("%d --> custo %d\tarestas[%d][%d].linha\n",i+1,vertices[i].custo,i,l );
    adj = adjacente(arestas,i);
    qtd = quantidade_adj(arestas,i);
    for ( j = 0, k=0,custoAdicional=0; j <  qtd; j++) {
      k = adj[j];
      if (vertices[k].aberto) {
        if(vertices[i].custo+arestas[i][k].custo < vertices[k].custo && arestas[i][k].custo != 0){
            if (vertices[i].linhaAnterior != arestas[i][k].linha && !in) {
              // printf("-----> mudou de linha %d\n",k+1);
              custoAdicional = 6;
              // vertices[k].linha += 1;
            } else
            {
              custoAdicional = 0;
              // printf("-----> nao mudou de linha %d\n",k+1);

            }

            vertices[k].linhaAnterior = arestas[i][k].linha;
            vertices[k].anterior = &vertices[i];
            vertices[k].custo = vertices[i].custo+arestas[i][k].custo+custoAdicional;
        }else{
          // printf("-----> %d maior %d: %d\n",vertices[i].custo+arestas[i][k].custo ,vertices[k].custo,k+1);
        }
      }

    }
    in=0;
    // er++;
    // break;
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


void mostrar_rota(sVERTICE *vertices){

  printf("\nCaminho a ser percorrido\n" );
  percorrer(vertices,-1);
  printf("Chegou\n" );
  printf("Tempo total: %d\n",vertices->custo );
}

void percorrer(sVERTICE *vertices,int estacao){
  if (vertices->custo == 0) {
    printf("%d-> ", vertices->nome);
  }else{
    percorrer(vertices->anterior,vertices->linhaAnterior);
    // if (estacao != vertices->linhaAnterior) {

      printf("%d-> ", vertices->nome);
    // }
  }
}
