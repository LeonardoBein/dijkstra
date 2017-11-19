#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "header.h"


int main() {
  int origem, final;
  sARESTA arestas[TAM_VERTICES][TAM_VERTICES];
  sVERTICE vertices[TAM_VERTICES];

  clear(arestas,vertices);



  //VERMELHO
  criar_aresta(arestas,1,2,VERMELHO,16);
	criar_aresta(arestas,2,3,VERMELHO,14);
	criar_aresta(arestas,3,4,VERMELHO,12);
	criar_aresta(arestas,4,5,VERMELHO,12);
	criar_aresta(arestas,5,6,VERMELHO,14);
  //AMARELO
  criar_aresta(arestas,2,15,AMARELO,7);
	criar_aresta(arestas,2,8, AMARELO,8);
	criar_aresta(arestas,8,12,AMARELO,11);
	criar_aresta(arestas,15,16,AMARELO,7);
	criar_aresta(arestas,16,17,AMARELO,12);
	criar_aresta(arestas,17,18,AMARELO,9);
  //ROXO
	criar_aresta(arestas,3,16, ROXO, 11);
	criar_aresta(arestas,3,13, ROXO, 13);
	criar_aresta(arestas,10,13, ROXO, 11);
	criar_aresta(arestas,16,19, ROXO, 13);
	criar_aresta(arestas,19,20, ROXO, 12);
  //AZUL
	criar_aresta(arestas,5,17,AZUL,10);
	criar_aresta(arestas,5,14,AZUL,9);
	criar_aresta(arestas,9,12,AZUL,17);
	criar_aresta(arestas,9,13,AZUL,7);
	criar_aresta(arestas,13,14,AZUL,9);
  //VERDE
	criar_aresta(arestas,6,11,VERDE,15);
	criar_aresta(arestas,7,8,VERDE,15);
	criar_aresta(arestas,8,9,VERDE,11);
	criar_aresta(arestas,9,10,VERDE,13);
	criar_aresta(arestas,10,11,VERDE,16);


  printf("Estacao inicial: " );
  scanf("%d",&origem );

  abrir_vertices(vertices);
  estimativa(vertices,origem);
  // for (int i = 0; i < TAM_VERTICES; i++) {
  //   printf("%.2d  ", vertices[i].aberto );
  // }
  // printf("\n");

  dijkstra(vertices,arestas);

  // for (int i = 0; i < TAM_VERTICES; i++) {
  //   for (int j = 0; j < TAM_VERTICES; j++) {
  //     if (arestas[i][j].custo != 0) {
  //       printf("%.2d|",arestas[i][j].linha );
  //     }
  //     else{
  //       printf("  |");
  //     }
  //   }
  //   printf("\n");
  // }
  //
  // for (int i = 0; i < TAM_VERTICES; i++) {
  //   printf("%X  ", vertices[i].nome );
  // }

  printf("Estacao final: ");
  scanf("%d",&final );

  mostrar_rota(&vertices[final-1]);


  return 0;
}
