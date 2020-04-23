#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "mt_search.h"

FILE* fp;
sem_t mutex;
int* orig_lst;
int* find_lst;
int range;
int line_max;
int target;
int find_idx;

void* search_num(int idx) {
  int start = idx * range;
  int end = start + range;
  if (end > line_max) {
    end = line_max;
  }
  // printf("start: %d, end: %d, range: %d\n", start, end, range);
  for (int i = start; i < end; i++) {
    if (orig_lst[i] == target) {
      sem_wait(&mutex);
      find_lst[find_idx++] = i + 1;
      sem_post(&mutex);
    }
  }
  return NULL;
}

int main(int argc, char* argv[]) {
  if (argc < 5 || argv[1] == NULL || argv[2] == NULL ||
      argv[3] == NULL || argv[4] == NULL) {
    return -1;
  }

  target = atoi(argv[2]);
  int kThreadNum = atoi(argv[3]);
  line_max = atoi(argv[4]);
  find_lst = malloc(sizeof(1) * line_max);
  orig_lst = malloc(sizeof(1) * line_max);
  find_idx = 0;
  range = line_max / kThreadNum + 1;

  if (find_lst == NULL || orig_lst == NULL ||
      kThreadNum < 1 || kThreadNum < 1) {
    return -1;
  }

  fp = fopen(argv[1], "r");
  char buff[5];
  for (int i = 0; i < line_max; i++) {
    fgets(buff, 5, fp);
    if (buff == NULL || strcmp("", buff) == 0 || strcmp("\n", buff) == 0) {
      return -1;
    }
    orig_lst[i] = atoi(buff);
  }
  fclose(fp);

  sem_init(&mutex, 0, 1);
  printf("\nStart program...\n\n");
  pthread_t thread_id[kThreadNum];
  printf("%d threads spawned\n", kThreadNum);
  int idx = 0;
  for (int i = 0; i < kThreadNum; i++) {
    pthread_create(&thread_id[i], NULL, search_num, idx++);
  }

  for (int i = 0; i < kThreadNum; i++) {
    pthread_join(thread_id[i], NULL);
  }

  printf("%d threads joined\n", kThreadNum);
  sem_destroy(&mutex);

  printf("\nSummary:\n");
  for (int i = 0; i < find_idx; i++) {
    printf("target is found at line: %d\n", find_lst[i]);
  }
  free(orig_lst);
  orig_lst = NULL;
  free(find_lst);
  find_lst = NULL;
  printf("\nEnd program\n\n");

  return 0;
}
