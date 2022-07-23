void m_2_opt (int* matrix){

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






