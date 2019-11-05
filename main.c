#include "Rii.h"

int main() {
  clock_t tiempo_inicio, tiempo_final;
  double segundos;
  tiempo_inicio = clock();
  Grafo G;
  int re = 0;
  u32 gr;
  char ord_nat;
  char ord_r_n;
  char ord_sc;
  G = ConstruccionDelGrafo();
  tiempo_final = clock();
  segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC; 
  printf("grafo construido-------->! %f segs\n", segundos);
  ord_nat = OrdenNatural(G);
  tiempo_inicio = clock();
  gr = Greedy(G);
  for (u32 i = 0; i < G->num_vertices; i++){
    printf("Nomb_vér[%u]---->%u\n", i, G->nombre_vertices[i]);
    printf("Gra_vért[%u]---->%u\n", i, G->grado_vertices[i]);
    printf("Col_vért[%u]---->%u\n", i, G->colores[i]);
  }
  tiempo_final = clock();
  segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC; 
  printf("Greedy -------->! %f segs gred: %u \n", segundos, gr);
  
  tiempo_inicio = clock();//tiempo de orden
  ord_r_n = RMBCchicogrande(G);
  gr = Greedy(G);
  tiempo_final = clock();//tiempo de orden
  segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC; 
  printf("orn-------->! %f segs or_w_p: %d\n", segundos, ord_r_n);
  tiempo_inicio = clock();
  re = Bipartito(G);
  tiempo_final = clock();
  segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC; 
  printf("segs bip: %f bp: %d \n", segundos, re);
  printf("num_colores: %u\n", G->num_colores);
  tiempo_inicio = clock();
  re = Bipartito(G);
  tiempo_final = clock();
  segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC; 
  printf("segs bip: %f bp: %d \n", segundos, re);

  tiempo_inicio = clock();
  gr = Greedy(G);
  tiempo_final = clock();
  segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC; 
  printf("Greedy ord_wp -------->! %f segs gred_wp: %u \n", segundos, gr);
  tiempo_inicio = clock();
  ord_sc = SwitchColores(G, 0,2);
  tiempo_final = clock();
  segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC; 
  printf("Greedy ord_sc -------->! %f segs ord_sc: %u \n", segundos, ord_sc);

  DestruccionDelGrafo(G);
};
