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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

#include "FileParser.h"
#include "Movie.h"
#include "MovieIndex.h"

#define NUM_FIELDS 6
#define MAX_ROW_LENGTH 1000
#define MAX_NUM_ACTORS 10

char* CheckAndAllocateString(char* token) {
  if (strcmp("-", token) == 0) {
    return NULL;
  } else {
    char *out = (char *) malloc((strlen(token) + 1) * sizeof('a'));
    snprintf(out, strlen(token) + 1, "%s", token);
    return out;
  }
}

int CheckInt(char* token) {
  if (strcmp("-", token) == 0) {
    return -1;
  } else {
    return atoi(token);
  }
}

double CheckDouble(char* token) {
  if (strcmp("-", token) == 0) {
    return -1;
  } else {
    return atof(token);
  }
}

Movie* CreateMovieFromRow(char *data_row) {
  if (data_row == NULL) {
    return NULL;
  }
  int cnt = 0;
  int improper = 0;
  int flag = 0;
  for (int i = 0; i < strlen(data_row); i++) {
    if (data_row[i] == '|') {
      if (flag == 1) {
        improper = 1;
      }
      cnt++;
      flag = 1;
    } else {
      flag = 0;
    }
  }
  // missing fields
  // consecutive pipe line with missing field
  // end is pipe line
  if (cnt < 5 || improper == 1 || flag == 1) {
    return NULL;
  }

  Movie* mov = CreateMovie();
  if (mov == NULL) {
    printf("Couldn't create a Movie.\n");
    return NULL;
  }

  // STEP 2(Student): Parse the row to create and populate a Movie.
  // Use the strtok
  char* rest;
  char* token = strtok_r(data_row, "|", &rest);
  if (token != NULL) {
    mov->star_rating = (double)CheckDouble(token);
  }
  token = strtok_r(NULL, "|", &rest);
  if (token != NULL) {
    mov->title = (char*)CheckAndAllocateString(token);
  }
  token = strtok_r(NULL, "|", &rest);
  if (token != NULL) {
    mov->content_rating = (char*)CheckAndAllocateString(token);
  }
  token = strtok_r(NULL, "|", &rest);
  if (token != NULL) {
    mov->genre = (char*)CheckAndAllocateString(token);
  }
  token = strtok_r(NULL, "|", &rest);
  if (token != NULL) {
    mov->duration = (int)CheckInt(token);
  }
  token = strtok_r(NULL, "|", &rest);
  if (token != NULL) {
    int cnt = 1;
    for (int i = 0; i < strlen(token); i++) {
      if (token[i] == ',') {
        cnt++;
      }
    }
    mov->num_actors = cnt;
    mov->actor_list = malloc(cnt * sizeof(char*));
    int idx = 0;
    char* actor_token = strtok_r(token, ",", &rest);
    while (actor_token != NULL) {
      if (actor_token[strlen(actor_token) - 1] == '\n') {
        actor_token[strlen(actor_token) - 1] = 0;
      }
      mov->actor_list[idx] = (char*)CheckAndAllocateString(actor_token);
      actor_token = strtok_r(NULL, ",", &rest);
      idx++;
    }
  }
  // free(rest);
  rest = NULL;
  token = NULL;
  return mov;
}

// Returns a LinkedList of Movie structs from the specified file
LinkedList ReadFile(char* filename) {
  FILE *cfPtr;

  LinkedList movie_list = CreateLinkedList();

  if ((cfPtr = fopen(filename, "r")) == NULL) {
    printf("File could not be opened\n");
    DestroyLinkedList(movie_list, NULL);
    return NULL;
  } else {
    char* row = NULL;
    ssize_t read;
    size_t len = 0;

    while ((read = getline(&row, &len, cfPtr)) != -1) {
      // Got the line; create a movie from it
      MoviePtr movie = CreateMovieFromRow(row);
      if (movie != NULL) {
        InsertLinkedList(movie_list, movie);
      }
    }
    free(row);
    fclose(cfPtr);
  }
  return movie_list;
}
