#define VERMELHO 1
#define VERDE 2
#define AZUL 3
#define AMARELO 4
#define ROXO 5

#define TAM_VERTICES 20



typedef struct {
  int linha;
  int custo;
}sARESTA;


struct sVERTICE{
  int nome;
  int aberto;
  int custo;
  struct sVERTICE *anterior;
  int linhaAnterior;
};
typedef struct sVERTICE sVERTICE;

void clear(sARESTA arestas[TAM_VERTICES][TAM_VERTICES], sVERTICE vertices[TAM_VERTICES]);
void criar_aresta(sARESTA arestas[TAM_VERTICES][TAM_VERTICES], int u, int v, int linha, int custo);
void estimativa(sVERTICE vertices[TAM_VERTICES],int u);
void abrir_vertices(sVERTICE vertices[TAM_VERTICES]);
int tem_aberto(sVERTICE vertices[TAM_VERTICES]);
int menor_vertice(sVERTICE vertices[TAM_VERTICES]);
int *adjacente(sARESTA arestas[TAM_VERTICES][TAM_VERTICES],int u);
void dijkstra(sVERTICE vertices[TAM_VERTICES], sARESTA arestas[TAM_VERTICES][TAM_VERTICES]);
int quantidade_adj(sARESTA arestas[TAM_VERTICES][TAM_VERTICES],int u);
void mostrar_rota(sVERTICE *vertices);
void percorrer(sVERTICE *vertices,int estacao);
char *linha(int linha);
