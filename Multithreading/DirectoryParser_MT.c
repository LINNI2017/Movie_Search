/*
 *  Created by Adrienne Slaughter
 *  CS 5007 Summer 2019
 *  Northeastern University, Seattle
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  See <http://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

#include "DirectoryParser.h"
#include "MovieTitleIndex.h"
#include "Movie.h"
#include "DocIdMap.h"
#include "FileParser.h"


#define kBufferSize 1000

//=======================
// To minimize the number of files we have, I'm
// putting the private function prototypes for
// the DirectoryParser here.

/**
 * Helper function to index a single file. 
 *
 * \return a pointer to the number of records (lines) indexed from the file
 */
void* IndexTheFile_MT(void* toBeIter);

pthread_mutex_t ITER_MUTEX = PTHREAD_MUTEX_INITIALIZER;  // global variable
pthread_mutex_t INDEX_MUTEX = PTHREAD_MUTEX_INITIALIZER;  // global variable

// THINK: Why is this global?
MovieTitleIndex movieIndex;
int destroyed = 0;
int file_num;

int ParseTheFiles_MT(DocIdMap docs, MovieTitleIndex index, int kNumThreads) {
  // Create the iterator
  // Create the threads
  // Spawn the threads to work on the function IndexTheFile_MT
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  int num = 0;

  if (pthread_mutex_init(&ITER_MUTEX, NULL) != 0) {
    printf("\n iter mutex init failed\n");
    return -1;
  }

  if (pthread_mutex_init(&INDEX_MUTEX, NULL) != 0) {
    printf("\n index mutex init failed\n");
    return -1;
  }

  // Create the iterator
  HTIter iter = CreateDocIdIterator((Hashtable)docs);
  movieIndex = index;
  pthread_t thread_id[kNumThreads];
  file_num = 0;
  destroyed = 0;

  int num_thread = kNumThreads;
  int num_file = NumElemsInHashtable((Hashtable)docs);
  if (num_thread > num_file) {
    num_thread = num_file;
  }

  for (int i = 0; i < num_thread; i++) {
    pthread_create(&thread_id[i], NULL, IndexTheFile_MT, &iter);
  }

  // pthread_mutex_unlock(&ITER_MUTEX);

  void* temp;
  for (int i = 0; i < num_thread; i++) {
    pthread_join(thread_id[i], &temp);
    if (temp != NULL) {
      free(temp);
      temp = NULL;
    }
  }

  if (iter != NULL) {
    DestroyHashtableIterator(iter);
  }

  pthread_mutex_destroy(&ITER_MUTEX);
  pthread_mutex_destroy(&INDEX_MUTEX);

  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Took %f seconds to execute. \n", cpu_time_used);
  return num;
}

void* IndexTheFile_MT(void* docname_iter) {
  // Lock the iterator
  // Get the filename, unlock the iterator
  // Read the file
  // Create movie from row
  // Lock the index
  // Add movie to index
  // Unlock the index

  // Don't forget to free this at some point!!
  int* num_records = (int*)malloc(sizeof(1));
  *num_records = 0;

  if (docname_iter == NULL) {
    return (void*)num_records;
  }
  HTKeyValue kvp;
  int status = 0;
  while (status == 0) {
    pthread_mutex_lock(&ITER_MUTEX);
    if (destroyed == 1) {
      pthread_mutex_unlock(&ITER_MUTEX);
      return (void*)num_records;
    }
    HTIter iter = *((HTIter*)(docname_iter));
    status = HTIteratorGet(iter, &kvp);
    if (HTIteratorHasMore(iter) != 0) {
      HTIteratorNext(iter);
    } else {
      status = -1;
      destroyed = 1;
    }

    FILE *cfPtr;
    if ((cfPtr = fopen((char*)kvp.value, "r")) == NULL) {
      printf("File could not be opened\n");
    } else {
      char buffer[kBufferSize];
      int row = 0;
      while (fgets(buffer, kBufferSize, cfPtr) != NULL) {
        Movie *movie = CreateMovieFromRow(buffer);
        pthread_mutex_lock(&INDEX_MUTEX);
        // printf("========title: %s, row: %d\n", movie->title, row);
        int result = AddMovieTitleToIndex(movieIndex, movie, kvp.key, row);
        pthread_mutex_unlock(&INDEX_MUTEX);
        row++;
        DestroyMovie(movie);  // Done with this now
        if (result < 0) {
          fprintf(stderr, "Didn't add MovieToIndex.\n");
        }
      }
      (*num_records) += row;
      // printf("========file: %s @ thread id = %ld\n",
      //   (char*)kvp.value, pthread_self());
      fclose(cfPtr);
    }
    pthread_mutex_unlock(&ITER_MUTEX);
  }

  return (void*)num_records;
}
