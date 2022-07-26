#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <genericMatrizAdjacente.h>

int *matrix_size, *num_passageiros, *num_car_passageiros;
int n_atributos_pessoas = 2;
float *val_max_pessoa;
int *v_matrix, *v_pessoas;

int *path, *path_peso;
int *passageiros_path;


void imprime_matrix(){
  printf("Matrix_size = %d x %d\n", matrix_size, matrix_size);
  printf("Total de passageiros a espera = %d\n", num_passageiros);
  printf("Num_passageiros possiveis no carro = %d\n", num_car_passageiros);
  
  for (size_t i = 0; i < (int)matrix_size * (int)matrix_size; i++) {
    if (i%(int)matrix_size == 0)
    {
      printf("\n%d ", v_matrix[i]);  
    }else{
      printf("%d ", v_matrix[i]);
    }
  }

  printf("\n\nPassageiros\n");

  for (size_t i = 0; i < (int)matrix_size; i++) {
      printf("%f %d %d\n", val_max_pessoa[i], v_pessoas[(2*i)], v_pessoas[(2*i)+1]);
  }

  printf("\nPath\n");

  for (size_t i = 0; i < (int)matrix_size; i++) {
      printf("%d ", path[i]);
  }

   printf("\nPath Peso = %d\n ", path_peso[0]);
}

//
void alloc_v_matrix(int* num){
  //Type cast por causa que row_size e col_size são unsigned int
  if( num != NULL){
    v_matrix = malloc ( ((int)num * (int)num)* sizeof(int) );
  }else {
    printf("Null pointers exceptions - init_v_matrix\n");
    exit;
  }
}
void alloc_v_pessoas(int* num){
  //Type cast por causa que row_size e col_size são unsigned int
  if( num != NULL){
    v_pessoas = malloc ( (((int)num)* n_atributos_pessoas) * sizeof(int) );
  }else {
    printf("Null pointers exceptions - init_v_pessoas\n");
    exit;
  }

}
void alloc_v_val_max_pessoa(int* num){
  //Type cast por causa que row_size e col_size são unsigned int
  if( num != NULL){
    val_max_pessoa = malloc ( (((int)num)) * sizeof(float) );
  }else {
    printf("Null pointers exceptions - init_v_val_max_pessoa\n");
    exit;
  }

}
void alloc_v_path(int* num){
   //Type cast por causa que num pode ser unsigned int
  if( num != NULL){
    path = malloc ( (((int)num)) * sizeof(int) );
  }else {
    printf("Null pointers exceptions - init_v_path\n");
    exit;
  }
}

// le o arquivo e coloca na memoria
void load_files_memory(char file_name[]){
  FILE *fp;

    // Lê e atribui o valores de row_size, col_size e num_passageiros no carro
    if ((fp=fopen (file_name,"r")) != NULL) {
      printf("Arquivo encontrado\n");
      fscanf(fp, "%d %d %d", &matrix_size, &num_passageiros, &num_car_passageiros);
    }

    // Aloca o vetor com o tamanho da row_size * col_size matriz de adjacencia
    alloc_v_matrix(matrix_size);

    for (size_t i = 0; i < (int)matrix_size * (int)matrix_size; i++)
    {
      fscanf(fp, "%d ", &v_matrix[i]);
    }

    fscanf(fp, "\n");

    // Aloca o vetor com as pessoas
    alloc_v_pessoas(matrix_size);
    alloc_v_val_max_pessoa(matrix_size);

    for (size_t i = 0; i < (int)matrix_size; i++)
    {
      fscanf(fp, "%f %d %d", &val_max_pessoa[i], &v_pessoas[(n_atributos_pessoas*i)], &v_pessoas[(n_atributos_pessoas*i)+1]);
    }

    fscanf(fp, "\n");
    
  fclose(fp);
}


void att_with_number(int* ptr, int value, int quantity){
  for (size_t i = 0; i < quantity; i++)
  {
    ptr[i] = value;
  }
}
// testa se ja foi adicionado essa entrada ao caminho
int isInPath(int entrada, int entrada_atual){
  //0 = não existe
  int flag = 0;
  for (size_t i = 0; i < entrada_atual; i++)
  {
    if(path[i] == entrada){
      //existe
      flag = 1;
    }
  }
  return flag;
}

//ponderado
// soma todos os pesos das arestas ver qual o menor e dar a ele a maior fatia e subsequente
//1 a 115 -> escolhe o 4 
//de 116 a 218 escolhe 7 
//e 219 a 293 escolhe o 1 

//heuristica do vizinho mais proximo e aleatorida
// Gulosa aleatorizada
void find_path_gulosa_aleatorizada() {
  alloc_v_path(matrix_size);
  
  int indice_path = 0;
  //Sempre tem o inicio como 0
  path[indice_path] = 0;
  //printf("\npath[%d]= %d\n", 0, path[0]);

  indice_path++;

  // entrada com as faixas de pesos
  int* faixas_de_peso = malloc ((int)matrix_size * sizeof(int));
  int* faixas_de_peso_organizado = malloc ((int)matrix_size * sizeof(int));
  int* possiveis_entradas = malloc ((int)matrix_size * sizeof(int));
  int num_possiveis_entradas = (int)matrix_size - indice_path;
  int count_peso = 0;

  //atribui os numeros para cada entradas
  att_with_number(faixas_de_peso, -1, (int)matrix_size);
  att_with_number(possiveis_entradas, 0, (int)matrix_size);
  
  do {

    printf("path[%d]\n", indice_path);

    for ( size_t indice = 0; indice < (int)matrix_size; indice++ )  {
      /*
        Determina se o indice atual já existe no path
          caso exista :  
      */
      if ( isInPath(indice, indice_path) == 0 ) {
        count_peso += v_matrix[  (path[indice_path-1] * (int)matrix_size) + indice ];
        faixas_de_peso[indice] = count_peso;
        //Entradas possiveis para path[i]
        printf("node = %d, value = %d\n", indice, v_matrix[path[indice_path-1]*(int)matrix_size + indice]);
      }
    }
      
    int aux = rand()%count_peso;
    printf("Aux = %d\n\n", aux);

    int flag = 0;
    do{
        if (faixas_de_peso[flag] == -1){
          flag++;
        } else if(aux < faixas_de_peso[flag]) {
          path[indice_path] = flag;
          flag = -1;
        }else{
          flag++;
        }
    } while(flag != -1);

    printf("Path = %d\n", path[indice_path]);

    //Reseting values
    att_with_number(faixas_de_peso, -1, (int)matrix_size);
    att_with_number(possiveis_entradas, 0, (int)matrix_size);
    count_peso = 0;

    //increment stop condition
    indice_path++;

  } while (indice_path < (int)matrix_size);
  
  free(faixas_de_peso);
  free(possiveis_entradas);
  free(faixas_de_peso_organizado);
}

//Calcula o peso do caminho
void calculate_path_peso(){
  path_peso = malloc (1* sizeof(int));

  int count = 0;
  for (size_t i = 0; i < (int)matrix_size - 1; i++)  {
      count += v_matrix[path[i]*(int)matrix_size + path[i+1]];
      //printf("Valor entrada [%d][%d]= %d\n",path[i],path[i+1] ,v_matrix[path[i]*(int)matrix_size + path[i+1]]);
  }

  count += v_matrix[path[(int)matrix_size - 1]*(int)matrix_size + path[0]];
  //printf("Valor entrada [%d][%d]= %d\n", path[(int)matrix_size - 1],path[0] ,v_matrix[path[(int)matrix_size - 1]*(int)matrix_size + path[0]]);

  path_peso[0] = count;
  //printf("Valor path = %d\n", count);
}

void find_passageiros_path(){

  int count_num_passageiros_no_carro = 0;
  int node_visitados = 0;
  
  //Inicia vetor com os passageiros do carro
  // -1 como valor default que não tem passageiro
  int *passageiros_no_carro  = malloc ((int)num_car_passageiros * sizeof(int));
  for (size_t i = 0; i < (int)num_car_passageiros; i++)
  {
    passageiros_no_carro[i] = -1;
  }
  
  
  for (size_t i = 0; i < (int)matrix_size; i++)
  {
    int node = path[i];
    node_visitados = i;

    for (size_t i = 0; i < (int)num_car_passageiros; i++)
    {
      if (passageiros_no_carro[i] == node)
      {
        //Remove passageiro e decrementa contador de passageiros
        passageiros_no_carro[i]= -1;
        printf("Deixando um passageiro na posicao %d\n", node);
        count_num_passageiros_no_carro--;
      }
    }

    if(count_num_passageiros_no_carro < (int)num_car_passageiros){
      int flag = 0;

      for (size_t j = 0; j < node_visitados; j++)
      {
        if (v_pessoas[2*node+1] == path[j]){
          flag = 1;
          printf("Passageiro nao embarcara pois node %d ja foi visitado\n", v_pessoas[2*node+1]);
        }
      }
      
      int w = 0;
      while (flag == 0)
      {
        if (passageiros_no_carro[w] == -1) {
          passageiros_no_carro[w]= v_pessoas[2*node+1];
          printf("Entrou um passageiro em %d que vai para %d\n", node, v_pessoas[2*node+1]);
          count_num_passageiros_no_carro++;
          flag = 1;
        }
        w++;
      }
    }
  }  

  free(passageiros_no_carro);
}

int main ( int argc, char **argv){
  srand(time(0));

  printf("Aqui\n");


   
  ///TODO Open all files in a given directory -- Abrir todos os arquivos de um diretorio 
  //load_files_memory("instancias/TIC01-10-10-3.in");
  

  //fazer 100 soluções

  //do {

  //find_path_random();
  //colocar os passageiros

  //find_path_gulosa_aleatorizada();
  // usar o busca local - 2opt
  
  //calculate_path_peso();
  //find_passageiros_path();
  
  // salvar cada resultado 
//}

// 
//fazer desvio padrão 



 // free(path);
  //free(v_matrix);

  //imprime_matrix();
  
  return 0;
}

