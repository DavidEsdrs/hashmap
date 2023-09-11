/*
TODO:
- [ ] Evitar colisão de hash
- [ ] Realocar hash table quando necessário
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LENGTH 50
#define LOAD_FACTOR_THRESHOLD 0.02
#define VERBOSE 1

unsigned long hash_function(char*);
void store_value(char**, int*);
void get_value(char**);
int verify_load_factor(int);
void reallocate_if_needed(char***, int);
void free_arrays();


int CURR_CAPACITY = 100;

int main() {  
  // aloca o array de ponteiros para as strings
  char** arr = (char**)malloc(CURR_CAPACITY * sizeof(char*));;

  int ITEMS = 0;
  
  if(arr == NULL) {
    printf("nao conseguiu alocar array!");
    exit(0);
  }

  // aloca o espaço das strings em si
  for(int i = 0; i < CURR_CAPACITY; i++) {
    arr[i] = (char*)malloc(STR_LENGTH);

    if(arr[i] == NULL) {
      printf("nao conseguiu alocar array!");
      exit(0);
    }
  }

  while(1) {
    int want_store_value = 1;
    printf("voce quer guardar valor ou criar um novo? 1 ou 0: ");
    scanf("%d", &want_store_value);

    if(want_store_value == 1) {
      store_value(arr, &ITEMS);
      reallocate_if_needed(&arr, ITEMS);

    } else {
      get_value(arr);
    }
  }

  free_arrays(&arr, CURR_CAPACITY);

  return 0;
}

void store_value(char** arr, int* ITEMS) {
  char str[STR_LENGTH];
  char value[STR_LENGTH];

  printf("digite a chave: ");
  scanf("%s", str);

  int index = hash_function(str);

  printf("hash eh: %d\n", index);

  printf("digite o valor: ");
  scanf("%s", value);

  strcpy(arr[index], value);

  *ITEMS = *ITEMS + 1;
}

void reallocate_if_needed(char*** arr, int ITEMS) {
  int need_reallocate = verify_load_factor(ITEMS);
  if(need_reallocate == 1) {
    CURR_CAPACITY *= 2;
    char** new_array = (char**)realloc(*arr, CURR_CAPACITY * sizeof(char*));
    if(new_array == NULL) {
      printf("nao conseguiu realocar!");
      exit(0);
    }
    *arr = new_array;
  }
}

int verify_load_factor(int ITEMS) {
  float load_factor = (float)ITEMS / CURR_CAPACITY;
  printf("fator de carga: %f\n", load_factor);
  return load_factor > LOAD_FACTOR_THRESHOLD;
}

void get_value(char** arr) {
  char str[STR_LENGTH];

  printf("digite a chave: ");
  scanf("%s", str);

  int index = hash_function(str);

  printf("%s\n", arr[index]);

  printf("o valor de %s eh %s\n", str, arr[index]);
}

unsigned long hash_function(char* str) {
  unsigned long i = 0;

  for (int j = 0; str[j]; j++)
    i += str[j];

  return i % CURR_CAPACITY;
}

void free_arrays(char** array, int capacity) {
  for(int i = 0; i < capacity; i++) {
    free(array[i]);
  }
  free(array);
}