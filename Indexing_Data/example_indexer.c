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
#include <assert.h>
#include <string.h>

#include <ctype.h>
#include <unistd.h>


#include "htll/LinkedList.h"
#include "MovieIndex.h"
#include "Movie.h"
#include "MovieReport.h"
#include "./FileParser.h"

void DestroyNothing(void* thing) {
  // Helper method to destroy the LinkedList.
}

void DestroyLLMovie(void *payload) {
  DestroyMovie((Movie*)payload);
}

void Print_Usage() {
  printf("Usage: ./example_indexer.c -option -filename\n");
  printf("-s: index on star rating\n");
  printf("-c: index on content rating\n");
  printf("-g: index on genre\n");
  printf("-a: index on actor\n");
}

int main(int argc, char* argv[]) {
  // STEP 8(Student): Check args, do the right thing.
  if (argc < 3) {
    Print_Usage();
    return -1;
  }
  int field_flag = 0;
  char* filename = "";
  enum IndexField field_enum;
  for (int i = 0; i < argc; i++) {
    int error_flag = 0;
    if (strcmp(argv[i], "valgrind") == 0 ||
        strcmp(argv[i], "./example") == 0) {
      continue;
    } else if (argv[i][0] == '-') {
      if (field_flag == 1) {
        printf("Multiple options provided, require exactly one option.\n");
        error_flag = 1;
      } else if (strlen(argv[i]) < 2) {
        printf("Invalid option provided.\n");
        error_flag = 1;
      } else if (argv[i][1] == 's') {
        field_enum = StarRating;
      } else if (argv[i][1] == 'c') {
        field_enum = ContentRating;
      } else if (argv[i][1] == 'g') {
        field_enum = Genre;
      } else if (argv[i][1] == 'a') {
        field_enum = Actor;
      } else {
        printf("Invalid option provided.\n");
        error_flag = 1;
      }
      if (error_flag == 1) {
        Print_Usage();
        return -1;
      }
      field_flag = 1;
    } else {
      filename = argv[i];
    }
  }

  if (field_flag == 0) {
    printf("No option provided, require exactly one option.\n");
    Print_Usage();
    return -1;
  }
  if (strcmp(filename, "") == 0) {
    printf("No filename provided, require exactlyone filename.\n");
    Print_Usage();
    return -1;
  }
  LinkedList movie_list  = ReadFile(filename);
  // STEP 9(Student): Create the index properly.
  Index index = BuildMovieIndex(movie_list, field_enum);
  PrintReport(index);
  DestroyIndex(index);
  DestroyLinkedList(movie_list, &DestroyLLMovie);
  return 0;
}
