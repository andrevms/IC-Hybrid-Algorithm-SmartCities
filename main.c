#include <stdio.h>
#include <stdlib.h>

int *row_size, *col_size, *num_passageiros;
int *v_matrix, *v_pessoas;
int *path;
int *path_peso;

void alloc_v_matrix(){
  //Type cast por causa que row_size e col_size são unsigned int
  if(row_size != NULL && col_size != NULL){
    v_matrix = malloc ((int)row_size * (int)col_size * sizeof(int));
  }else {
    printf("Null pointers exceptions - init_v_matrix\n");
    exit;
  }
}

// le o arquivo e coloca na memoria
void load_files_memory(char file_name[]){
  FILE *fp;

    // Lê e atribui o valores de row_size, col_size e num_passageiros no carro
    if ((fp=fopen (file_name,"r")) != NULL) {
      printf("Arquivo encontrado\n");
      fscanf(fp, "%d %d %d", &row_size, &col_size, &num_passageiros);
    }

    // Aloca o vetor com o tamanho da row_size * col_size matriz de adjacencia
    alloc_v_matrix();

    for (size_t i = 0; i < (int)row_size * (int)col_size; i++)
    {
      fscanf(fp, "%d ", &v_matrix[i]);
    }

    fscanf(fp, "\n");
    
  fclose(fp);
}

void imprime_v(){
  printf("row_size = %d\n", row_size);
  printf("col_size = %d\n", col_size);
  printf("num_passageiros possiveis no carro = %d\n", num_passageiros);

  for (size_t i = 0; i < (int)row_size * (int)col_size; i++) {
    if (i%(int)col_size == 0)
    {
      printf("\n%d ", v_matrix[i]);  
    }else{
      printf("%d ", v_matrix[i]);
    }
  }
}

//Gera uma sequencia aleatoria de entradas a ser seguida 
void find_path_random() {

  path = malloc ((int)row_size * sizeof(int));
  int i = 1, equal;

  path[0] = 0;
  printf("\npath[%d]= %d\n",0, path[0]);

  do {
    path[i] = rand() % (int)row_size;
    equal = 0;

    //se for repetido não incrementa o i
    for (size_t j = 0; j < i; j++)  {
      if (path[j] == path[i]) {  equal = 1; }
    }

    if (equal == 0) { 
      printf("path[%d]= %d\n",i, path[i]);
      i++;
    }
    
  }while (i < (int)row_size);
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

void att_with_number(int* ptr, int value, int quantity){
  for (size_t i = 0; i < quantity; i++)
  {
    ptr[i] = value;
  }
}

//ponderado
// soma todos os pesos das arestas ver qual o menor e dar a ele a maior fatia e subsequente
//1 a 115 -> escolhe o 4 
//de 116 a 218 escolhe 7 
//e 219 a 293 escolhe o 1 

//heuristica do vizinho mais proximo e aleatorida
// Gulosa aleatorizada
void find_path_gulosa_aleatorizada() {

  path = malloc ((int)row_size * sizeof(int));
  
  int indice_path = 0;
  //Sempre tem o inicio como 0
  path[indice_path] = 0;
  //printf("\npath[%d]= %d\n", 0, path[0]);

  indice_path++;

  // entrada com as faixas de pesos
  int* faixas_de_peso = malloc ((int)col_size * sizeof(int));
  int* faixas_de_peso_organizado = malloc ((int)col_size * sizeof(int));
  int* possiveis_entradas = malloc ((int)col_size * sizeof(int));
  int num_possiveis_entradas = (int)col_size - indice_path;
  int count_peso = 0;

  //atribui os numeros para cada entradas
  att_with_number(faixas_de_peso, -1, (int)col_size);
  att_with_number(possiveis_entradas, 0, (int)col_size);
  
  do {

    //printf("path[%d]\n", indice_path);

    for ( size_t indice = 0; indice < (int)col_size; indice++ )  {
      /*
        Determina se o indice atual já existe no path
          caso exista :  
      */
      if ( isInPath(indice, indice_path) == 0 ) {
        count_peso += v_matrix[  (path[indice_path-1] * (int)col_size) + indice ];
        faixas_de_peso[indice] = count_peso;
        //Entradas possiveis para path[i]
        printf("node = %d, value = %d\n", indice, v_matrix[path[indice_path-1]*(int)col_size + indice]);
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
    att_with_number(faixas_de_peso, -1, (int)col_size);
    att_with_number(possiveis_entradas, 0, (int)col_size);
    count_peso = 0;

    //increment stop condition
    indice_path++;

  } while (indice_path < (int)row_size);
  

  free(faixas_de_peso);
  free(possiveis_entradas);
  free(faixas_de_peso_organizado);
}

//Calcula o peso do caminho
void calculate_path_peso(){
  int count = 0;
  for (size_t i = 0; i < (int)row_size - 1; i++)  {
      count += v_matrix[path[i]*(int)col_size + path[i+1]];
      printf("Valor entrada [%d][%d]= %d\n",path[i],path[i+1] ,v_matrix[path[i]*(int)col_size + path[i+1]]);
  }

  count += v_matrix[path[(int)row_size - 1]*(int)col_size + path[0]];
  printf("Valor entrada [%d][%d]= %d\n", path[(int)row_size - 1],path[0] ,v_matrix[path[(int)row_size - 1]*(int)col_size + path[0]]);

  path_peso = &count;
  printf("Valor path = %d", count);
}

int main ( int argc, char **argv){
   
  ///TODO Open all files in a given directory -- Abrir todos os arquivos de um diretorio 
  load_files_memory("instancias/TIC01-10-10-3.in");
  //imprime_v();
  //find_path_random();
  //calculate_path_peso();

  find_path_gulosa_aleatorizada();


  free(path);
  free(v_matrix);
  
  return 0;
}

