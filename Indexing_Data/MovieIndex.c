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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "MovieIndex.h"
#include "htll/LinkedList.h"
#include "htll/Hashtable.h"
#include "Movie.h"
#include "MovieSet.h"
#include "MovieReport.h"

void DestroyMovieSetWrapper(void *movie_set) {
  DestroyMovieSet((MovieSet)movie_set);
}

void toLower(char *str, int len) {
  for (int i = 0; i < len; i++) {
    str[i] = tolower(str[i]);
  }
}

Index BuildMovieIndex(LinkedList movies, enum IndexField field_to_index) {
  Index movie_index = CreateIndex();

  // STEP 4(Student): Check that there is at least one movie
  // What happens if there is not at least one movie?
  if (NumElementsInLinkedList(movies) == 0) {
    return movie_index;
  }

  LLIter iter = CreateLLIter(movies);
  Movie* cur_movie;
  LLIterGetPayload(iter, (void**)&cur_movie);

  AddMovieToIndex(movie_index, cur_movie, field_to_index);

  while (LLIterHasNext(iter)) {
    LLIterNext(iter);
    LLIterGetPayload(iter, (void**)&cur_movie);
    AddMovieToIndex(movie_index, cur_movie, field_to_index);
  }
  DestroyLLIter(iter);
  return movie_index;
}


// HTKeyValue new_kvp;
// new_kvp.key = old_kvp.key;
// new_kvp.value = (void*)new_set;
// PutInHashtable(index, new_kvp, &old_kvp);
// AddMovieToSet((MovieSet)new_kvp.value, movie);
// old_kvp.value = NULL;
// } else {
// AddMovieToSet((MovieSet)old_kvp.value, movie);
// }


char* AllocateString(char* token) {
  char* out = (char*)malloc((strlen(token) + 1) * sizeof('a'));
  snprintf(out, strlen(token) + 1, "%s", token);
  return out;
}

int AddMovieActorsToIndex(Index index, Movie *movie) {
  // HTKeyValue kvp;
  // HTKeyValue old_kvp;

  // STEP 6(Student): Add movies to the index via actors.
  //  Similar to STEP 5.
  for (int i = 0; i < movie->num_actors; i++) {
    Movie* movie_copy = movie;
    movie_copy = CreateMovie();
    movie_copy->title = (char*)AllocateString(movie->title);
    movie_copy->star_rating = (double)movie->star_rating;
    movie_copy->content_rating = (char*)AllocateString(movie->content_rating);
    movie_copy->genre = (char*)AllocateString(movie->genre);
    movie_copy->duration = (int)movie->duration;
    movie_copy->num_actors = (int)movie->num_actors;
    movie_copy->actor_list = (char**)malloc(movie->num_actors * sizeof(char*));
    for (int i = 0; i < movie->num_actors; i++) {
      movie_copy->actor_list[i] = (char*)AllocateString(movie->actor_list[i]);
    }
    HTKeyValue old_kvp;
    old_kvp.key = ComputeKey(movie_copy, Actor, i);
    int status = LookupInHashtable(index, old_kvp.key, &old_kvp);
    if (status == -1) {
      MovieSet new_set = (void*)CreateMovieSet(movie_copy->actor_list[i]);
      if (new_set == NULL) {
        return -1;
      }
      HTKeyValue new_kvp;
      new_kvp.key = old_kvp.key;
      new_kvp.value = (void*)new_set;
      PutInHashtable(index, new_kvp, &old_kvp);
      AddMovieToSet((MovieSet)new_kvp.value, movie_copy);
    } else {
      AddMovieToSet((MovieSet)old_kvp.value, movie_copy);
    }
  }
  return 0;
}

int AddMovieToIndex(Index index, Movie *movie, enum IndexField field) {
  if (field == Actor) {
    return AddMovieActorsToIndex(index, movie);
  }
  HTKeyValue old_kvp;
  old_kvp.key = ComputeKey(movie, field, 0);

  Movie* movie_copy = movie;
  movie_copy = CreateMovie();
  movie_copy->title = (char*)AllocateString(movie->title);
  movie_copy->star_rating = (double)movie->star_rating;
  movie_copy->content_rating = (char*)AllocateString(movie->content_rating);
  movie_copy->genre = (char*)AllocateString(movie->genre);
  movie_copy->duration = (int)movie->duration;
  movie_copy->num_actors = (int)movie->num_actors;
  movie_copy->actor_list = (char**)malloc(movie->num_actors * sizeof(char*));
  for (int i = 0; i < movie->num_actors; i++) {
    movie_copy->actor_list[i] = (char*)AllocateString(movie->actor_list[i]);
  }

  // STEP 5(Student): How do we add movies to the index?
  // The general idea:
  // Check hashtable to see if relevant MovieSet already exists
  // If it does, grab access to it from the hashtable
  // If it doesn't, create the new MovieSet and get the pointer to it
  // Put the new MovieSet into the Hashtable.
  int status = LookupInHashtable(index, old_kvp.key, &old_kvp);
  if (status == -1) {
    char* field_str;
    switch (field) {
      case Genre:
        field_str = movie->genre;
        break;
      case StarRating:
        field_str = (char*)malloc(10 * sizeof('a'));
        snprintf(field_str, 10, "%f", movie->star_rating);
        break;
      case ContentRating:
        field_str = movie->content_rating;
        break;
      default:
        return -1;
    }
    MovieSet new_set = CreateMovieSet(field_str);
    if (field == StarRating) {
      free(field_str);
    }
    field_str = NULL;
    if (new_set == NULL) {
      DestroyMovie(movie_copy);
      return -1;
    }
    HTKeyValue new_kvp;
    new_kvp.key = old_kvp.key;
    new_kvp.value = (void*)new_set;
    PutInHashtable(index, new_kvp, &old_kvp);
    AddMovieToSet((MovieSet)new_kvp.value, movie_copy);
  } else {
    MovieSet ms = old_kvp.value;
    LLIter iter = CreateLLIter(ms->movies);
    Movie* cur;
    int exist = 0;
    LLIterGetPayload(iter, (void**)&cur);
    if (strcmp(movie->title, cur->title) == 0) {
      exist = 1;
    }
    while (LLIterHasNext(iter) == 1) {
      LLIterNext(iter);
      LLIterGetPayload(iter, (void**)&cur);
      if (strcmp(movie->title, cur->title) == 0) {
        exist = 1;
      }
    }
    if (exist == 0) {
      AddMovieToSet((MovieSet)old_kvp.value, movie_copy);
    } else {
      DestroyMovie(movie_copy);
    }
    DestroyLLIter(iter);
  }

  // old_kvp.value = NULL;

  // DestroyMovie(movie);
  // After we either created or retrieved the MovieSet from the Hashtable:
  return 0;
}

uint64_t ComputeKey(Movie* movie,
  enum IndexField which_field, int which_actor) {
  char rating_str[10];
  switch (which_field) {
    case Genre:
      return FNVHash64((unsigned char*)movie->genre, strlen(movie->genre));
    case StarRating:
      snprintf(rating_str, 10, "%f", movie->star_rating);
      return FNVHash64((unsigned char*)rating_str, strlen(rating_str));
    case ContentRating:
      return FNVHash64((unsigned char*)movie->content_rating,
                       strlen(movie->content_rating));
    case Actor:
      if (which_actor < movie->num_actors) {
        return FNVHash64((unsigned char*)movie->actor_list[which_actor],
                         strlen(movie->actor_list[which_actor]));
      }
      break;
  }
  return -1u;
}

// Removed for simplicity
// MovieSet GetMovieSet(Index index, const char *term){}

int DestroyIndex(Index index) {
  DestroyHashtable(index, &DestroyMovieSetWrapper);
  return 0;
}

Index CreateIndex() {
  return CreateHashtable(128);
}
