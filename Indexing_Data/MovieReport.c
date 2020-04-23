/*
 *  Adrienne Slaughter
 *  5007 Spr 2020
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

#include <stdio.h>
#include <stdlib.h>

#include "MovieIndex.h"
#include "MovieReport.h"
#include "Movie.h"
#include "MovieSet.h"
#include "htll/LinkedList.h"
#include "htll/Hashtable.h"


void PrintReport(Index index) {
  // Create Iter
  HTIter iter = CreateHashtableIterator(index);

  HTKeyValue movie_set;

  HTIteratorGet(iter, &movie_set);
  OutputMovieSet((MovieSet)movie_set.value);

  while (HTIteratorHasMore(iter)) {
    HTIteratorNext(iter);
    HTIteratorGet(iter, &movie_set);
    OutputMovieSet((MovieSet)movie_set.value);
  }
  // For every movie set, create a LLIter
  DestroyHashtableIterator(iter);
}

void OutputMovieSet(MovieSet movie_set) {
  // STEP 7(Student): Print the MovieSet to the terminal.

  if (movie_set == NULL) {
    return;
  }

  if (movie_set->desc == NULL) {
    printf("Invalid description.\n");
    return;
  }

  if (movie_set->movies == NULL) {
    printf("Empty movie set.\n");
    return;
  }

  printf("indexType: %s\n", movie_set->desc);
  printf("%d items\n", NumElementsInLinkedList(movie_set->movies));
  LLIter iter = CreateLLIter(movie_set->movies);
  Movie* cur;
  LLIterGetPayload(iter, (void**)&cur);
  printf("  %s\n", cur->title);
  while (LLIterHasNext(iter) == 1) {
    LLIterNext(iter);
    LLIterGetPayload(iter, (void**)&cur);
    printf("  %s\n", cur->title);
  }
  printf("\n");
  DestroyLLIter(iter);
}


