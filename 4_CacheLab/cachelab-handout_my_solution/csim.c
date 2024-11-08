#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

void get_params(int *s, int *E, int *b, char **file_path, int argc, char **argv){
  int opt;
  while ((opt = getopt(argc, argv, "s:E:b:t:")) != -1){
    switch(opt){
      case 's':
        *s = atoi(optarg);
        break;
      case 'E':
        *E = atoi(optarg);
        break;
      case 'b':
        *b = atoi(optarg);
        break;
      case 't':
        *file_path = optarg;
        break;
      default:
        fprintf(stderr, "Usage: %s -s <num> -E <num> -b <num> -t <path>\n", argv[0]);
        exit(1);
        break;
    }
  }
  
  if (*s <= 0 || *b <= 0 || *E <= 0 || *file_path == NULL){
    fprintf(stderr, "Usage: %s -s <num> -E <num> -b <num> -t <path>\n", argv[0]);
    exit(1);
  }
}

typedef struct cache_line {
  int valid_bit;
  long long tag;
  int queue;
} cache_line_t;

typedef cache_line_t *cache_line_ptr;

cache_line_ptr *create_cache(int S, int E){
  cache_line_ptr *cache;
  cache = malloc(sizeof(cache_line_ptr) * S);
  
  for (size_t i = 0; i < S; i++){
    cache[i] = malloc(sizeof(cache_line_t) * E);
    for (size_t j = 0; j < E; j++){
      cache[i][j].valid_bit = 0;
      cache[i][j].tag = 0;
      cache[i][j].queue = 0;
    }
  }
  return cache;
}

void free_cache(cache_line_ptr *cache, int S){
  for (size_t i = 0; i < S; i++){
    free(cache[i]);
  }
  free(cache);
}

void do_sim(cache_line_ptr *cache, int set_index, long long tag, int E, int *hit_count, int *miss_count, int *eviction_count){
  int match = 0;
  int emptyIndex = -1;
  for (size_t i = 0; i < E; i++){
    if (cache[set_index][i].valid_bit == 1){
      if (cache[set_index][i].tag == tag){ // hit
        match = 1;
        (*hit_count)++;
        cache[set_index][i].queue = 0;
        for (size_t j = 0; j < E; j++){
          if (j != i && cache[set_index][j].valid_bit == 1){
            cache[set_index][j].queue++;
          }
        }
        break;
        } 
      } else if (emptyIndex == -1){
        emptyIndex = i; // to find empty cache_line_t
      }
    }

  if (match == 0){ // miss
    if (emptyIndex != -1){ // miss with no eviction
      cache[set_index][emptyIndex].valid_bit = 1;
      cache[set_index][emptyIndex].tag = tag;
      cache[set_index][emptyIndex].queue = 0;
      (*miss_count)++;
      for (size_t i = 0; i < E; i++){
        if (i != emptyIndex && cache[set_index][i].valid_bit == 1){
          cache[set_index][i].queue++;
        }
      }
    } else { // miss with eviction
      int max = 0;
      int evictIndex = -1;
      for (size_t i = 0; i < E; i++){
        if (cache[set_index][i].valid_bit == 1 && cache[set_index][i].queue >= max){
          max = cache[set_index][i].queue;
          evictIndex = i;
        }
      }
      cache[set_index][evictIndex].valid_bit = 1;
      cache[set_index][evictIndex].tag = tag;
      cache[set_index][evictIndex].queue = 0;
      (*miss_count)++;
      (*eviction_count)++;
      for (size_t i = 0; i < E; i++){
        if (i != evictIndex && cache[set_index][i].valid_bit == 1){
          cache[set_index][i].queue++;
        }
      }
    }
  }
}

void read_traces(char *file_path, int b, int s, int E, cache_line_ptr *cache, int *hit_count, int *miss_count, int *eviction_count){
  FILE *file = fopen(file_path, "r");
  if (file == NULL){
    fprintf(stderr, "Could not open file %s.\n", file_path);
    exit(1);
  }
  char operation;
  long long address;
  int size;
  while(fscanf(file, " %c %llx,%d", &operation, &address, &size) != EOF){
    int set_mask = ~((-1) << s);
    int set_index = (address >> b) & set_mask;
    long long tag = address >> (b + s);
    if (operation == 'I'){
      continue;
    } else if (operation == 'M'){
      printf("hit");
      (*hit_count)++;
    }
    do_sim(cache, set_index, tag, E, hit_count, miss_count, eviction_count);
    }
  fclose(file);
}

int main(int argc, char **argv){
  // Declaration of variables
  int s = 0; // Number of bits in a set
  int E = 0; // Number of cache lines in a set
  int b = 0; // Number of bits in a cache block
  char *file_path = NULL;

  int hit_count = 0;
  int miss_count = 0;
  int eviction_count = 0;

  // Get parameters from terminal
  get_params(&s, &E, &b, &file_path, argc, argv);
  // printf("s: %d, E: %d, b: %d, file path: %s\n", s, E, b, file_path);

  // Create cache
  int S = 1 << s; 
  cache_line_ptr *cache = create_cache(S, E);

  // Read traces
  read_traces(file_path, b, s, E, cache, &hit_count, &miss_count, &eviction_count);

  // Print result
  printSummary(hit_count, miss_count, eviction_count);

  // Free memory
  free_cache(cache, S);

  return 0;
}
