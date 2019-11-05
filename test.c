#include "Rii.h"
#include <time.h>
u32 max(u32 num1, u32 num2){return (num1 > num2 ) ? num1 : num2;}
u32 min(u32 num1, u32 num2){return (num1 < num2 ) ? num1 : num2;}
int cmpfunc1 (const void * a, const void * b) {return ( *(u32*)a > *(u32*)b );}
int error = 0;


void coloreo_propio(Grafo G, u32 num_vert) {
  bool band = true;
  for(u32 i = 0; i < num_vert; i++) {
    for(u32 j = 0; j < GradoDelVertice(G, i); j++) {
      if(ColorDelVertice(G, i) != ColorJotaesimoVecino(G, i, j)) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
        i = num_vert;
        break;
      }
    }
  }
  if(band == false) {
    printf("✔\n");
    band = true;
  }
}

void comp_bip(Grafo G, u32 num_vert, int re) {
  bool band = true;
  int comp = 2;
  for(u32 i = 0; i < num_vert; i++) {
    for(u32 j = 0; j < GradoDelVertice(G, i); j++) {
      if(band == true && (ColorDelVertice(G,i) == 0 && ColorJotaesimoVecino(G,i,j) == 1)) {
        comp = 1;
        band = true;
        } else if (band == true && ColorDelVertice(G,i)==1 && ColorJotaesimoVecino(G,i,j)==0){
        comp = 1;
        band = true;
        } else {
        comp = 0;
        band = false;
        break;
      }
    }
  }
  if(re == comp) {
    if (re == 0) {
      printf("No es Bipartito ✔\n");
      band = true;
    } else if (re == 1) {
      printf("Si es Bipartito ✔\n");
      band = true;
    }
  } else {
    error++;
    printf("✖\n");
    band = true;
  }
}

void greed_test(Grafo G, u32 num_vert) {
  bool band = true;
  for(u32 i = 0; i < num_vert; i++) {
    u32 *aux = calloc(GradoDelVertice(G, i), sizeof(u32));
    for(u32 j = 0; j < GradoDelVertice(G, i); j++) {
      aux[j] = ColorJotaesimoVecino(G, i, j);
    }
    qsort(aux, GradoDelVertice(G, i), sizeof(u32), cmpfunc1);
    if (ColorDelVertice(G, i) == 0 && aux[0] > 0) {
      band = false;
    } else if (ColorDelVertice(G, i) == aux[GradoDelVertice(G, i)-1] + 1) {
      band = false;
    } else {
      for(u32 j = 0; j < GradoDelVertice(G, i); j++) {
        if(aux[j] + 1 < aux[j+1]) {
          if(ColorDelVertice(G, i) == aux[j] + 1) {
            band = false;
            break;
          } else {
            band = true;
            break;
          }
        }
      }
    }
   free(aux);
  }
  if(band == false) {
    printf("✔\n");
    band = true;
  } else {
    error++;
    printf("✖\n");
  }
}

int main() {
  int re, res;
  u32 gr, gree, min_sv;
  char ord_nat, ord_w_p, ord_sv, ord_sc;
  bool band = true;
  u32 max_c = 0;
  clock_t tiempo_inicio, tiempo_final;
  double segundos;
  Grafo G;
  G = ConstruccionDelGrafo();
  if(G != NULL) {
    gr = Greedy(G);
    u32 num_vert = NumeroDeVertices(G);

    time_t t;
    u32 n;
    n = NumeroDeColores(G);
    srand((unsigned) time(&t));

    printf("Test 01 para NumeroDeColores: ------------------------------------- ");
    for(u32 i = 0; i < num_vert; i++) {
      max_c = max(ColorDelVertice(G, i), max_c);
    }
    max_c++ ;
    if(NumeroDeColores(G) == max_c) {
      printf("✔\n");
      max_c = 0;
    } else {
      error++;
      printf("✖\n");
      max_c = 0;
    }

    printf("Test 02 para NumeroDeColores con Greedy: -------------------------- ");
    if(NumeroDeColores(G) == gr) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 03 para OrdenNatural: ---------------------------------------- ");
    ord_nat = OrdenNatural(G);
    gr = Greedy(G);
    for(u32 i = 0; i < num_vert; i++) {
      if(i+1 != num_vert && NombreDelVertice(G, i) <= NombreDelVertice(G, i+1)) {
        band = false;
      } else if (i+1 == num_vert ) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
        break;
      }
    }
    if(band == false && ord_nat== 0) {
      printf("✔\n");
      band = true;
    }

    printf("Test 04 coloreo propio para OrdenNatural: ------------------------- ");
    coloreo_propio(G, num_vert);

    printf("Test 05 coloreo propio para Bipartito antes de WP: ---------------- ");
    res = Bipartito(G);
    coloreo_propio(G, num_vert);

    printf("Test 06 de comprobacion para Bipartito antes de WP: ");
    comp_bip(G, num_vert, res);

    printf("Test 07 para OrdenWelshPowell: ------------------------------------ ");
    ord_w_p = OrdenWelshPowell(G);
    gr = Greedy(G);
    for(u32 i = 0; i < num_vert; i++) {
      if(i+1 != num_vert && GradoDelVertice(G, i) >= GradoDelVertice(G, i+1)) {
        band = false;
      } else if (i+1 == num_vert) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
        break;
      }
    }
    if(band == false && ord_w_p == 0) {
      printf("✔\n");
      band = true;
    }

    printf("Test 08 para NumeroDeColores de OrdenWelshPowell: ----------------- ");
    for(u32 i = 0; i < num_vert; i++) {
      max_c = max(ColorDelVertice(G, i), max_c);
    }
    max_c++ ;
    if(NumeroDeColores(G) == max_c) {
      printf("✔\n");
      max_c = 0;
    } else {
      error++;
      printf("✖\n");
      max_c = 0;
    }

    printf("Test 09 coloreo propio para OrdenWelshPowell: --------------------- ");
    coloreo_propio(G, num_vert);

    printf("Test 10 coloreo propio para Bipartito: ---------------------------- ");
    re = Bipartito(G);
    coloreo_propio(G, num_vert);

    printf("Test 11 de comprobacion para Bipartito: ----------- ");
    comp_bip(G, num_vert, re);

    printf("Test 12 de Bipartito luego de WP: --------------------------------- ");
    if(re == res) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 13 para SwitchColores + RMBCnormal: -------------------------- ");
    OrdenNatural(G);
    gr = Greedy(G);
    u32 comp = 0;
    u32 comp2 = 0;
    u32 min_sc = num_vert +1;
    n = NumeroDeColores(G)/4;
    for(u32 i = 0; i < n; i++) {
      u32 a, b;
      a = rand() % NumeroDeColores(G);
      b = rand() % NumeroDeColores(G);
      if(a != b) {
        comp = NumeroDeColores(G);
        SwitchColores(G, a ,b);
        RMBCnormal(G);
        comp2 = NumeroDeColores(G);
        gree = Greedy(G);
        if(comp == comp2) {
          band = false;
        } else {
          band = true;
          error++;
          printf("✖\n");
          break;
        }
        if(gree < gr) {
          min_sc = min(gree, min_sc);
          band = false;
        }
      }
    }
    if(band == false) {
      printf("✔\n");
      if (min_sc < gr) {
        printf("------------ Mejoro la #de colores era: %u ahora es: %u ------------\n", gr, min_sc);
      }
    }


    printf("Test 14 para SwitchColores + RMBCrevierte: ------------------------ ");
    OrdenNatural(G);
    gr = Greedy(G);
    comp = 0;
    comp2 = 0;
    min_sc = num_vert +1;
    n = NumeroDeColores(G)/4;
    for(u32 i = 0; i < n; i++) {
      u32 a, b;
      a = rand() % NumeroDeColores(G);
      b = rand() % NumeroDeColores(G);
      if(a != b) {
        comp = NumeroDeColores(G);
        SwitchColores(G, a ,b);
        RMBCrevierte(G);
        comp2 = NumeroDeColores(G);
        gree = Greedy(G);
        if(comp == comp2) {
          band = false;
        } else {
          band = true;
          error++;
          printf("✖\n");
          break;
        }
        if(gree < gr) {
          min_sc = min(gree, min_sc);
          band = false;
        }
      }
    }
    if(band == false) {
      printf("✔\n");
      if (min_sc < gr) {
        printf("------------ Mejoro la #de colores era: %u ahora es: %u ------------\n", gr, min_sc);
      }
    }
  printf("Test 15 para SwitchColores + RMBCchicogrande: --------------------- ");
    OrdenNatural(G);
    gr = Greedy(G);
    comp = 0;
    comp2 = 0;
    min_sc = num_vert +1;
    n = NumeroDeColores(G)/4;
    for(u32 i = 0; i < n; i++) {
      u32 a, b;
      a = rand() % NumeroDeColores(G);
      b = rand() % NumeroDeColores(G);
      if(a != b) {
        comp = NumeroDeColores(G);
        SwitchColores(G, a ,b);
        RMBCchicogrande(G);
        comp2 = NumeroDeColores(G);
        gree = Greedy(G);
        if(comp == comp2) {
          band = false;
        } else {
          band = true;
          error++;
          printf("✖\n");
          break;
        }
        if(gree < gr) {
          min_sc = min(gree, min_sc);
          band = false;
        }
      }
    }
    if(band == false) {
      printf("✔\n");
      if (min_sc < gr) {
        printf("------------ Mejoro la #de colores era: %u ahora es: %u ------------\n", gr, min_sc);
      }
    }

    printf("Test 16 para SwitchColores: --------------------------------------- ");
    ord_sc = SwitchColores(G, NumeroDeColores(G) + 1, 0);
    if (ord_sc == 1) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 17 para SwitchVertices: -------------------------------------- ");
    u32 a = NombreDelVertice(G, 0);
    u32 b = NombreDelVertice(G, 1);
    SwitchVertices(G, 1, 0);
    if (NombreDelVertice(G, 0) == b && NombreDelVertice(G, 1) == a) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }
    printf("Test 18 para SwitchVertices: -------------------------------------- ");
    u32 c = NombreDelVertice(G, 0);
    u32 d = NombreDelVertice(G, num_vert - 1);
    SwitchVertices(G, num_vert - 1, 0);
    if (NombreDelVertice(G, 0) == d && NombreDelVertice(G, num_vert - 1) == c) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }
    printf("Test 19 para SwitchVertices: -------------------------------------- ");
    ord_sv = SwitchVertices(G, num_vert + 1, 0);
    if (ord_sv == 1) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 20 para #col con SwitchVertices vs #col con OrdenNatural: ---- ");
    OrdenNatural(G);
    gree = Greedy(G);
    min_sv = num_vert +1;
    for(u32 i = 0; i < 100; i++) {
      u32 e = rand() % num_vert;
      u32 f = rand() % num_vert;
      if (e != f) {
        SwitchVertices(G, e, f);
        gr = Greedy(G);
        min_sv = min(gr, min_sv);
      }
    }
    min_sv = min(min_sv, gree);
    if (min_sv == gree) {
      printf("✔\n");
    } else if (min_sv < gree) {
      printf("✔ y el minimo es %u\n", min_sv);
    } else {
      printf("pinto con mas colores\n");
    }

    printf("Test 21 coloreo propio para SwitchVertices: ----------------------- ");
    for(u32 i = 0; i < num_vert/2; i++) {
      u32 e = rand() % num_vert;
      u32 f = rand() % num_vert;
      if (e != f) {
        SwitchVertices(G, e, f);
      }
    }
    gr = Greedy(G);
    coloreo_propio(G, num_vert);

    printf("Test 22 para Greedy con Orden Natural: ---------------------------- ");
    OrdenNatural(G);
    Greedy(G);
    greed_test(G, num_vert);

    printf("Test 23 para RMBCnormal: ------------------------------------------ ");
    ord_nat = OrdenNatural(G);
    gr = Greedy(G);
    RMBCnormal(G);
    for(u32 i = 0; i < num_vert; i++) {
      if( i+1 != num_vert && ColorDelVertice(G, i) <= ColorDelVertice(G, i+1)) {
        band = false;
      } else if (i+1 == num_vert) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
        break;
      }
    }
    if(band == false) {
      printf("✔\n");
      band = true;
    }

    printf("Test 24 para RMBCrevierte: ---------------------------------------- ");
   ord_nat = OrdenNatural(G);
    gr = Greedy(G);
    RMBCrevierte(G);
    for(u32 i = 0; i < num_vert; i++) {
      if( i+1 != num_vert && ColorDelVertice(G, i) >= ColorDelVertice(G, i+1)) {
        band = false;
      } else if (i+1 == num_vert) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
        break;
      }
    }
    if(band == false) {
      printf("✔\n");
      band = true;
    }

    printf("Test 25 tiempo para 1 RMBCrevierte + Greedy: ---------------------- ");
    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      RMBCrevierte(G);
      gr = Greedy(G);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    if(segundos <= 0.9) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 26 tiempo para 1 RMBCnormal + Greedy: ------------------------ ");
    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      RMBCnormal(G);
      gr = Greedy(G);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    if(segundos <= 0.9) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 27 tiempo para 1 OrdenWelshPowell + Greedy: ------------------ ");
    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      OrdenWelshPowell(G);
      gr = Greedy(G);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    if(segundos <= 0.9) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 28 tiempo para 1 OrdenNatural + Greedy: ---------------------- ");
    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      OrdenNatural(G);
      gr = Greedy(G);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    if(segundos <= 0.9) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 29 tiempo para 1 RMBCchicogrande + Greedy: ------------------- ");
    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      RMBCchicogrande(G);
      gr = Greedy(G);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    if(segundos <= 0.9) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 30 para CopiarGrafo ------------------------------------------ ");
    Grafo g_cpy;
    g_cpy = NULL;
    band = true;
    g_cpy = CopiarGrafo(G);
    if(g_cpy != NULL) {
      if(NumeroDeVertices(g_cpy) == NumeroDeVertices(G)) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
      }
      if(NumeroDeLados(g_cpy) == NumeroDeLados(G)) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
      }
      if(NumeroDeColores(g_cpy) == NumeroDeColores(G)) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
      }
      for(u32 i= 0; i< num_vert; i++) {
        if(NombreDelVertice(g_cpy, i) == NombreDelVertice(G, i)) {
          band = false;
        } else {
          error++;
          printf("✖\n");
          band = true;
          break;
        }
        if(ColorDelVertice(g_cpy, i) == ColorDelVertice(G, i)) {
          band = false;
        } else {
          error++;
          printf("✖\n");
          band = true;
          break;
        }
        if(GradoDelVertice(g_cpy, i) == GradoDelVertice(G, i)) {
          band = false;
          for(u32 j= 0; j< GradoDelVertice(G, i); j++) {
            if(ColorJotaesimoVecino(g_cpy, i,j) == ColorJotaesimoVecino(G, i,j)){
              band = false;
            } else {
              error++;
              printf("✖\n");
              band = true;
              break;
            }
            if(NombreJotaesimoVecino(g_cpy, i,j) == NombreJotaesimoVecino(G, i,j)){
              band = false;
            } else {
              error++;
              printf("✖\n");
              band = true;
              break;
            }
          }
        } else {
          error++;
          printf("✖\n");
          band = true;
          break;
        }
      }
    }
    if(band == false) {
      printf("✔\n");
      band = true;
    }

    printf("Test 31 para cambios en CopiarGrafo: ------------------------------ ");
    SwitchVertices(G, 0, 1);
      if((NombreDelVertice(g_cpy, 0) != NombreDelVertice(G, 0)) && (NombreDelVertice(g_cpy, 1) != NombreDelVertice(G, 1))) {
        printf("✔\n");
      } else {
        error++;
        printf("✖\n");
      }

    printf("Test 32 para RMBCchicogrande: ------------------------------------- ");
    void testcg(Grafo G, u32 num_vert) {
      OrdenNatural(G);
      Greedy(G);
      u32 ccol = NumeroDeColores(G);
      RMBCchicogrande(G);
      u32 *auxc = calloc(ccol, sizeof(int));
      u32 count, tr;
      count = 1,  tr = 0;
      for(u32 i = 0; i < num_vert; i++) {
        if (ColorDelVertice(G,i) == ColorDelVertice(G,i+1)) {
          count++;
       } else {
          auxc[tr] = count;
          tr++;
          count = 1;
        }
      }
      for(u32 i = 0; i < ccol; i++) {
        if(i+1 != ccol && auxc[i] <= auxc[i+1]) {
          band = false;
        } else if (i+1 == ccol) {
          band = false;
        } else {
          error++;
          printf("✖\n");
          band = true;
          break;
        }
      }
      if(band == false) {
        printf("✔\n");
        band = true;
      }
     free(auxc);
    }
    testcg(G, num_vert);

    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      RMBCnormal(G);
      Greedy(G);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    printf("RMBCnormal: %f\n", segundos);


    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      RMBCchicogrande(G);
      Greedy(G);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    printf("RMBCchicogrande: %f\n", segundos);

    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      OrdenWelshPowell(G);
      Greedy(G);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    printf("OrdenWelshPowell: %f\n", segundos);


    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      RMBCrevierte(G);
      Greedy(G);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    printf("RMBCrevierte: %f\n", segundos);

    printf("cantidad de errores: %u\n", error);

    DestruccionDelGrafo(g_cpy);
    DestruccionDelGrafo(G);
  }

  Grafo H;
  H = ConstruccionDelGrafo();
  error = 0;
  if(H != NULL) {
    gr = Greedy(H);
    u32 num_vert = NumeroDeVertices(H);
    u32 n = NumeroDeColores(H);
    time_t t;
    srand((unsigned) time(&t));

    printf("Test 01 para NumeroDeColores: ------------------------------------- ");
    for(u32 i = 0; i < num_vert; i++) {
      max_c = max(ColorDelVertice(H, i), max_c);
    }
    max_c++ ;
    if(NumeroDeColores(H) == max_c) {
      printf("✔\n");
      max_c = 0;
    } else {
      error++;
      printf("✖\n");
      max_c = 0;
    }

    printf("Test 02 para NumeroDeColores con Greedy: -------------------------- ");
    if(NumeroDeColores(H) == gr) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 03 para OrdenNatural: ---------------------------------------- ");
    ord_nat = OrdenNatural(H);
    gr = Greedy(H);
    for(u32 i = 0; i < num_vert; i++) {
      if(i+1 != num_vert && NombreDelVertice(H, i) <= NombreDelVertice(H, i+1)) {
        band = false;
      } else if (i+1 == num_vert ) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
        break;
      }
    }
    if(band == false && ord_nat== 0) {
      printf("✔\n");
      band = true;
    }

    printf("Test 04 coloreo propio para OrdenNatural: ------------------------- ");
    coloreo_propio(H, num_vert);

    printf("Test 05 coloreo propio para Bipartito antes de WP: ---------------- ");
    res = Bipartito(H);
    coloreo_propio(H, num_vert);

    printf("Test 06 de comprobacion para Bipartito antes de WP: ");
    comp_bip(H, num_vert, res);

    printf("Test 07 para OrdenWelshPowell: ------------------------------------ ");
    ord_w_p = OrdenWelshPowell(H);
    gr = Greedy(H);
    for(u32 i = 0; i < num_vert; i++) {
      if(i+1 != num_vert && GradoDelVertice(H, i) >= GradoDelVertice(H, i+1)) {
        band = false;
      } else if (i+1 == num_vert) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
        break;
      }
    }
    if(band == false && ord_w_p == 0) {
      printf("✔\n");
      band = true;
    }

    printf("Test 08 para NumeroDeColores de OrdenWelshPowell: ----------------- ");
    for(u32 i = 0; i < num_vert; i++) {
      max_c = max(ColorDelVertice(H, i), max_c);
    }
    max_c++ ;
    if(NumeroDeColores(H) == max_c) {
      printf("✔\n");
      max_c = 0;
    } else {
      error++;
      printf("✖\n");
      max_c = 0;
    }

    printf("Test 09 coloreo propio para OrdenWelshPowell: --------------------- ");
    coloreo_propio(H, num_vert);

    printf("Test 10 coloreo propio para Bipartito: ---------------------------- ");
    re = Bipartito(H);
    coloreo_propio(H, num_vert);

    printf("Test 11 de comprobacion para Bipartito: ----------- ");
    comp_bip(H, num_vert, re);

    printf("Test 12 de Bipartito luego de WP: --------------------------------- ");
    if(re == res) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 13 para SwitchColores + RMBCnormal: -------------------------- ");
    OrdenNatural(H);
    gr = Greedy(H);
    u32 comp = 0;
    u32 comp2 = 0;
    u32 min_sc = num_vert +1;
    for(u32 i = 0; i < n; i++) {
      u32 a, b;
      a = rand() % NumeroDeColores(H);
      b = rand() % NumeroDeColores(H);
      if(a != b) {
        comp = NumeroDeColores(H);
        SwitchColores(H, a ,b);
        RMBCnormal(H);
        comp2 = NumeroDeColores(H);
        gree = Greedy(H);
        if(comp == comp2) {
          band = false;
        } else {
          band = true;
          error++;
          printf("✖\n");
          break;
        }
        if(gree < gr) {
          min_sc = min(gree, min_sc);
          band = false;
        }
      }
    }
    if(band == false) {
      printf("✔\n");
      if (min_sc < gr) {
        printf("------------ Mejoro la #de colores era: %u ahora es: %u ------------\n", gr, min_sc);
      }
    }


    printf("Test 14 para SwitchColores + RMBCrevierte: ------------------------ ");
    OrdenNatural(H);
    gr = Greedy(H);
    comp = 0;
    comp2 = 0;
    min_sc = num_vert +1;
    for(u32 i = 0; i < n; i++) {
      u32 a, b;
      a = rand() % NumeroDeColores(H);
      b = rand() % NumeroDeColores(H);
      if(a != b) {
        comp = NumeroDeColores(H);
        SwitchColores(H, a ,b);
        RMBCrevierte(H);
        comp2 = NumeroDeColores(H);
        gree = Greedy(H);
        if(comp == comp2) {
          band = false;
        } else {
          band = true;
          error++;
          printf("✖\n");
          break;
        }
        if(gree < gr) {
          min_sc = min(gree, min_sc);
          band = false;
        }
      }
    }
    if(band == false) {
      printf("✔\n");
      if (min_sc < gr) {
        printf("------------ Mejoro la #de colores era: %u ahora es: %u ------------\n", gr, min_sc);
      }
    }
  printf("Test 15 para SwitchColores + RMBCchicogrande: --------------------- ");
    OrdenNatural(H);
    gr = Greedy(H);
    comp = 0;
    comp2 = 0;
    min_sc = num_vert +1;
    for(u32 i = 0; i < n; i++) {
      u32 a, b;
      a = rand() % NumeroDeColores(H);
      b = rand() % NumeroDeColores(H);
      if(a != b) {
        comp = NumeroDeColores(H);
        SwitchColores(H, a ,b);
        RMBCchicogrande(H);
        comp2 = NumeroDeColores(H);
        gree = Greedy(H);
        if(comp == comp2) {
          band = false;
        } else {
          band = true;
          error++;
          printf("✖\n");
          break;
        }
        if(gree < gr) {
          min_sc = min(gree, min_sc);
          band = false;
        }
      }
    }
    if(band == false) {
      printf("✔\n");
      if (min_sc < gr) {
        printf("------------ Mejoro la #de colores era: %u ahora es: %u ------------\n", gr, min_sc);
      }
    }

    printf("Test 16 para SwitchColores: --------------------------------------- ");
    ord_sc = SwitchColores(H, NumeroDeColores(H) + 1, 0);
    if (ord_sc == 1) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 17 para SwitchVertices: -------------------------------------- ");
    u32 a = NombreDelVertice(H, 0);
    u32 b = NombreDelVertice(H, 1);
    SwitchVertices(H, 1, 0);
    if (NombreDelVertice(H, 0) == b && NombreDelVertice(H, 1) == a) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }
    printf("Test 18 para SwitchVertices: -------------------------------------- ");
    u32 c = NombreDelVertice(H, 0);
    u32 d = NombreDelVertice(H, num_vert - 1);
    SwitchVertices(H, num_vert - 1, 0);
    if (NombreDelVertice(H, 0) == d && NombreDelVertice(H, num_vert - 1) == c) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }
    printf("Test 19 para SwitchVertices: -------------------------------------- ");
    ord_sv = SwitchVertices(G, num_vert + 1, 0);
    if (ord_sv == 1) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 20 para #col con SwitchVertices vs #col con OrdenNatural: ---- ");
    OrdenNatural(H);
    gree = Greedy(H);
    min_sv = num_vert +1;
    for(u32 i = 0; i < 100; i++) {
      u32 e = rand() % num_vert;
      u32 f = rand() % num_vert;
      if (e != f) {
        SwitchVertices(H, e, f);
        gr = Greedy(H);
        min_sv = min(gr, min_sv);
      }
    }
    min_sv = min(min_sv, gree);
    if (min_sv == gree) {
      printf("✔\n");
    } else if (min_sv < gree) {
      printf("✔ y el minimo es %u\n", min_sv);
    } else {
      printf("pinto con mas colores\n");
    }

    printf("Test 21 coloreo propio para SwitchVertices: ----------------------- ");
    for(u32 i = 0; i < num_vert/2; i++) {
      u32 e = rand() % num_vert;
      u32 f = rand() % num_vert;
      if (e != f) {
        SwitchVertices(H, e, f);
      }
    }
    gr = Greedy(H);
    coloreo_propio(H, num_vert);

    printf("Test 22 para Greedy con Orden Natural: ---------------------------- ");
    OrdenNatural(H);
    Greedy(H);
    greed_test(H, num_vert);

    printf("Test 23 para RMBCnormal: ------------------------------------------ ");
    ord_nat = OrdenNatural(H);
    gr = Greedy(H);
    RMBCnormal(H);
    for(u32 i = 0; i < num_vert; i++) {
      if( i+1 != num_vert && ColorDelVertice(H, i) <= ColorDelVertice(H, i+1)) {
        band = false;
      } else if (i+1 == num_vert) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
        break;
      }
    }
    if(band == false) {
      printf("✔\n");
      band = true;
    }

    printf("Test 24 para RMBCrevierte: ---------------------------------------- ");
   ord_nat = OrdenNatural(H);
    gr = Greedy(H);
    RMBCrevierte(H);
    for(u32 i = 0; i < num_vert; i++) {
      if( i+1 != num_vert && ColorDelVertice(H, i) >= ColorDelVertice(H, i+1)) {
        band = false;
      } else if (i+1 == num_vert) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
        break;
      }
    }
    if(band == false) {
      printf("✔\n");
      band = true;
    }

    printf("Test 25 tiempo para 1 RMBCrevierte + Greedy: ---------------------- ");
    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      RMBCrevierte(H);
      gr = Greedy(H);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    if(segundos <= 0.9) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 26 tiempo para 1 RMBCnormal + Greedy: ------------------------ ");
    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      RMBCnormal(H);
      gr = Greedy(H);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    if(segundos <= 0.9) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 27 tiempo para 1 OrdenWelshPowell + Greedy: ------------------ ");
    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      OrdenWelshPowell(H);
      gr = Greedy(H);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    if(segundos <= 0.9) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 28 tiempo para 1 OrdenNatural + Greedy: ---------------------- ");
    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      OrdenNatural(H);
      gr = Greedy(H);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    if(segundos <= 0.9) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 29 tiempo para 1 RMBCchicogrande + Greedy: ------------------- ");
    tiempo_inicio = clock();
    for(u32 i = 0; i < 1; i++) {
      RMBCchicogrande(H);
      gr = Greedy(H);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    if(segundos <= 0.9) {
      printf("✔\n");
    } else {
      error++;
      printf("✖\n");
    }

    printf("Test 30 para CopiarGrafo ------------------------------------------ ");
    Grafo g_cpy2;
    g_cpy2 = NULL;
    band = true;
    g_cpy2 = CopiarGrafo(H);
    if(g_cpy2 != NULL) {
      if(NumeroDeVertices(g_cpy2) == NumeroDeVertices(H)) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
      }
      if(NumeroDeLados(g_cpy2) == NumeroDeLados(H)) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
      }
      if(NumeroDeColores(g_cpy2) == NumeroDeColores(H)) {
        band = false;
      } else {
        error++;
        printf("✖\n");
        band = true;
      }
      for(u32 i= 0; i< num_vert; i++) {
        if(NombreDelVertice(g_cpy2, i) == NombreDelVertice(H, i)) {
          band = false;
        } else {
          error++;
          printf("✖\n");
          band = true;
          break;
        }
        if(ColorDelVertice(g_cpy2, i) == ColorDelVertice(H, i)) {
          band = false;
        } else {
          error++;
          printf("✖\n");
          band = true;
          break;
        }
        if(GradoDelVertice(g_cpy2, i) == GradoDelVertice(H, i)) {
          band = false;
          for(u32 j= 0; j< GradoDelVertice(G, i); j++) {
            if(ColorJotaesimoVecino(g_cpy2, i,j) == ColorJotaesimoVecino(H, i,j)){
              band = false;
            } else {
              error++;
              printf("✖\n");
              band = true;
              break;
            }
            if(NombreJotaesimoVecino(g_cpy2, i,j) == NombreJotaesimoVecino(H, i,j)){
              band = false;
            } else {
              error++;
              printf("✖\n");
              band = true;
              break;
            }
          }
        } else {
          error++;
          printf("✖\n");
          band = true;
          break;
        }
      }
    }
    if(band == false) {
      printf("✔\n");
      band = true;
    }

    printf("Test 31 para cambios en CopiarGrafo: ------------------------------ ");
    SwitchVertices(G, 0, 1);
      if((NombreDelVertice(g_cpy2, 0) != NombreDelVertice(H, 0)) && (NombreDelVertice(g_cpy2, 1) != NombreDelVertice(H, 1))) {
        printf("✔\n");
      } else {
        error++;
        printf("✖\n");
      }

    printf("Test 32 para RMBCchicogrande: ------------------------------------- ");
    void testcg(Grafo H, u32 num_vert) {
      OrdenNatural(H);
      Greedy(G);
      u32 ccol = NumeroDeColores(H);
      RMBCchicogrande(H);
      u32 *auxc = calloc(ccol, sizeof(int));
      u32 count, tr;
      count = 1,  tr = 0;
      for(u32 i = 0; i < num_vert; i++) {
        if (ColorDelVertice(H,i) == ColorDelVertice(H,i+1)) {
          count++;
       } else {
          auxc[tr] = count;
          tr++;
          count = 1;
        }
      }
      for(u32 i = 0; i < ccol; i++) {
        if(i+1 != ccol && auxc[i] <= auxc[i+1]) {
          band = false;
        } else if (i+1 == ccol) {
          band = false;
        } else {
          error++;
          printf("✖\n");
          band = true;
          break;
        }
      }
      if(band == false) {
        printf("✔\n");
        band = true;
      }
     free(auxc);
    }
    testcg(H, num_vert);

    tiempo_inicio = clock();
    for(u32 i = 0; i < 10; i++) {
      RMBCnormal(H);
      Greedy(H);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    printf("RMBCnormal: %f\n", segundos);


    tiempo_inicio = clock();
    for(u32 i = 0; i < 10; i++) {
      RMBCchicogrande(H);
      Greedy(H);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    printf("RMBCchicogrande: %f\n", segundos);

    tiempo_inicio = clock();
    for(u32 i = 0; i < 10; i++) {
      OrdenWelshPowell(H);
      Greedy(H);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    printf("OrdenWelshPowell: %f\n", segundos);


    tiempo_inicio = clock();
    for(u32 i = 0; i < 10; i++) {
      RMBCrevierte(H);
      Greedy(H);
    }
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC;
    printf("RMBCrevierte: %f\n", segundos);

    printf("cantidad de errores: %u\n", error);

    DestruccionDelGrafo(g_cpy2);
    DestruccionDelGrafo(H);
  }
};
