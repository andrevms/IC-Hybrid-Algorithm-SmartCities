#include <stdio.h>
#include <stdlib.h>

int *row_size, *col_size, *num_passageiros;
int *v_matrix, *v_pessoas;
int *path;
int *path_peso;

void init_v_matrix(){
  //Type cast por causa que row_size e col_size são unsigned int
  if(row_size != NULL && col_size != NULL){
    v_matrix = malloc ((int)row_size * (int)col_size * sizeof(int));
  }else {
    printf("Null pointers exceptions - init_v_matrix\n");
    exit;
  }
}

void read_matrix_size(char file_name[]){
  FILE *fp;
    if ((fp=fopen (file_name,"r")) != NULL) {
      printf("Arquivo encontrado\n");
      fscanf(fp, "%d %d %d", &row_size, &col_size, &num_passageiros);
    }

    init_v_matrix();

    for (size_t i = 0; i < (int)row_size * (int)col_size; i++)
    {
      fscanf(fp, "%d ", &v_matrix[i]);
    }
    
  fclose(fp);
}

void imprime_v(){
  printf("row_size = %d\n", row_size);
  printf("col_size = %d\n", col_size);
  printf("num_passageiros = %d\n", num_passageiros);

  for (size_t i = 0; i < (int)row_size * (int)col_size; i++) {
    if (i%(int)col_size == 0)
    {
      printf("\n%d ", v_matrix[i]);  
    }else{
      printf("%d ", v_matrix[i]);
    }
  }
}

//Randomizado sem checar valores
void find_path_random() {

  path = malloc ((int)row_size * sizeof(int));
  int i = 0, equal;

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

void calculate_path_peso(){
  int count = 0;
  for (size_t i = 0; i < (int)row_size - 1; i++)  {
      count += v_matrix[path[i]*(int)col_size + path[i+1]];
  }
  path_peso = &count;
  printf("Valor path = %d", count);
}

int main ( int argc, char **argv){
   
  ///TODO Open all files in a given directory -- Abrir todos os arquivos de um diretorio 
  read_matrix_size("instancias/TIC01-10-10-3.in");
  //imprime_v();
  find_path_random();
  calculate_path_peso();
  
  free(path);
  free(v_matrix);
  
  return 0;
}

