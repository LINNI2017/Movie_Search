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
#include <stdint.h>
#include <assert.h>


#include "gtest/gtest.h"

extern "C" {
  #include "./MovieIndex.h"
  #include "htll/LinkedList.h"
  #include "MovieIndex.h"
  #include "Movie.h"
  #include "MovieReport.h"
  #include "FileParser.h"
  #include <string.h>
}

const char* movie_row_A = "9.3|The Shawshank Redemption|R|Crime|"
  "142|Tim Robbins,Morgan Freeman,Bob Gunton";
const char* movie_row_B = "7.4|Back to the Future Part III|PG|"
  "Adventure|118|Michael J. Fox,Christopher Lloyd,Mary Steenburgen";
const char* movie_row_C = "5.6|AAAAAAAAA|R|Crime|120|"
  "Aaaaaa Aaaa,Bbbb Bbbbbb,Cccc Ccccc,Ddddd Dddd";
const char* movie_row_D = "2.3|XXXXXX|PG|Drama|100|Aaaa Aaa";
const char* movie_row_E = "4.3|VVVV1|PG-12|Comedy|110|Aaaa Aaa";
const char* movie_row_F = "5.3|VVVV2|PG-13|Comedy|120|Baaa Aaa";
const char* movie_row_G = "6.3|VVVV3|PG-14|Comedy|130|Caaa Aaa";
const char* movie_row_H = "6.3|VVVV4|PG-14|Comedy|130|Caaa Aaa";
// const char* movie_row_I = "6.3|VVVV5|PG-14|Comedy|130|Caaa Aaa";

void DestroyLLMovie(void *payload) {
  DestroyMovie((Movie*)payload);
}

TEST(MovieSet, CreateDestroy) {
  MovieSet set = CreateMovieSet("My test set");
  ASSERT_NE(set, nullptr);
  DestroyMovieSet(set);
}

TEST(MovieSet, AddOneMovie) {
  MovieSet set = CreateMovieSet("My test set");
  ASSERT_NE(set, nullptr);
  ASSERT_EQ(NumElementsInLinkedList(set->movies), 0);

  char row[1000];
  snprintf(row, sizeof(row), "%s", movie_row_A);
  MoviePtr movie = CreateMovieFromRow(row);
  int res = AddMovieToSet(set, movie);
  ASSERT_EQ(res, 0);
  ASSERT_EQ(NumElementsInLinkedList(set->movies), 1);

  DestroyMovieSet(set);
}

TEST(MovieIndex, CreateDestroy) {
  Index index = CreateIndex();
  ASSERT_NE(index, nullptr);
  DestroyIndex(index);
}

TEST(MovieIndex, AddMovieToIndexStarRating) {
  // Copying the string from a const to an array
  // (to be more similar to the actual use case)
  printf("============DONE BY LINNI CAI============\n");
  char row[1000];
  snprintf(row, sizeof(row), "%s", movie_row_G);
  // Take a movie
  MoviePtr m1 = CreateMovieFromRow(row);
  snprintf(row, sizeof(row), "%s", movie_row_H);
  MoviePtr m2 = CreateMovieFromRow(row);

  // Create Index
  Index index = CreateIndex();

  // Add movie to index
  AddMovieToIndex(index, m1, StarRating);

  // Check that movie is in index

  // Check size/num elements (should be num of types, not of movies)
  ASSERT_EQ(NumElemsInHashtable(index), 1);

  // // Try to insert movie again
  AddMovieToIndex(index, m1, StarRating);

  // Add another movie to the index (same IndexType)
  AddMovieToIndex(index, m2, StarRating);

  // Destroy movie index
  DestroyIndex(index);
  DestroyLLMovie(m1);
  DestroyLLMovie(m2);
  printf("============DONE BY LINNI CAI============\n");
}

TEST(MovieIndex, AddMovieToIndexActor) {
  // Copying the string from a const to an array
  // (to be more similar to the actual use case)
  printf("============DONE BY LINNI CAI============\n");
  char row[1000];
  snprintf(row, sizeof(row), "%s", movie_row_G);
  // Take a movie
  MoviePtr m1 = CreateMovieFromRow(row);
  snprintf(row, sizeof(row), "%s", movie_row_H);
  MoviePtr m2 = CreateMovieFromRow(row);

  // Create Index
  Index index = CreateIndex();

  // Add movie to index
  AddMovieToIndex(index, m1, Actor);

  // Check that movie is in index

  // Check size/num elements (should be num of types, not of movies)
  ASSERT_EQ(NumElemsInHashtable(index), 1);

  // // Try to insert movie again
  AddMovieToIndex(index, m1, Actor);

  // Add another movie to the index (same IndexType)
  AddMovieToIndex(index, m2, Actor);

  // Destroy movie index
  DestroyIndex(index);
  DestroyLLMovie(m1);
  DestroyLLMovie(m2);
  printf("============DONE BY LINNI CAI============\n");
}

TEST(MovieIndex, AddMovieToIndexContentRating) {
  // Copying the string from a const to an array
  // (to be more similar to the actual use case)
  char row[1000];
  snprintf(row, sizeof(row), "%s", movie_row_A);
  // Take a movie
  MoviePtr m1 = CreateMovieFromRow(row);
  snprintf(row, sizeof(row), "%s", movie_row_B);
  MoviePtr m2 = CreateMovieFromRow(row);

  // Create Index
  Index index = CreateIndex();

  // Add movie to index
  AddMovieToIndex(index, m1, ContentRating);

  // Check that movie is in index

  // Check size/num elements (should be num of types, not of movies)
  ASSERT_EQ(NumElemsInHashtable(index), 1);

  // // Try to insert movie again
  AddMovieToIndex(index, m1, ContentRating);

  // Add another movie to the index (same IndexType)
  AddMovieToIndex(index, m2, ContentRating);

  // Destroy movie index

  DestroyIndex(index);
  DestroyLLMovie(m1);
  DestroyLLMovie(m2);
}

TEST(MovieIndex, AddMovieToIndexGenre) {
  printf("============DONE BY LINNI CAI============\n");
  // Copying the string from a const to an array
  // (to be more similar to the actual use case)
  char row[1000];
  snprintf(row, sizeof(row), "%s", movie_row_G);
  // Take a movie
  MoviePtr m1 = CreateMovieFromRow(row);
  snprintf(row, sizeof(row), "%s", movie_row_H);
  MoviePtr m2 = CreateMovieFromRow(row);

  // Create Index
  Index index = CreateIndex();

  // Add movie to index
  AddMovieToIndex(index, m1, ContentRating);

  // Check that movie is in index

  // Check size/num elements (should be num of types, not of movies)
  ASSERT_EQ(NumElemsInHashtable(index), 1);

  // // Try to insert movie again
  AddMovieToIndex(index, m1, Genre);

  // Add another movie to the index (same IndexType)
  AddMovieToIndex(index, m2, Genre);

  // Destroy movie index

  DestroyIndex(index);
  DestroyLLMovie(m1);
  DestroyLLMovie(m2);
  printf("============DONE BY LINNI CAI============\n");
}

TEST(MovieIndex, AddThreeMovieToIndex) {
  printf("============DONE BY LINNI CAI============\n");
  // Copying the string from a const to an array
  // (to be more similar to the actual use case)
  char row[1000];
  snprintf(row, sizeof(row), "%s", movie_row_C);
  MoviePtr m1 = CreateMovieFromRow(row);
  snprintf(row, sizeof(row), "%s", movie_row_D);
  MoviePtr m2 = CreateMovieFromRow(row);
  snprintf(row, sizeof(row), "%s", movie_row_E);
  MoviePtr m3 = CreateMovieFromRow(row);

  // Create Index
  Index index = CreateIndex();

  // Add movie to index
  AddMovieToIndex(index, m1, ContentRating);
  ASSERT_EQ(NumElemsInHashtable(index), 1);

  AddMovieToIndex(index, m2, ContentRating);
  ASSERT_EQ(NumElemsInHashtable(index), 2);

  AddMovieToIndex(index, m3, ContentRating);
  ASSERT_EQ(NumElemsInHashtable(index), 3);

  // Destroy movie index
  DestroyIndex(index);
  DestroyLLMovie(m1);
  DestroyLLMovie(m2);
  DestroyLLMovie(m3);
  printf("============DONE BY LINNI CAI============\n");
}

TEST(MovieIndex, AddThreeMovieSameGenreToIndex) {
  printf("============DONE BY LINNI CAI============\n");
  // Copying the string from a const to an array
  // (to be more similar to the actual use case)
  char row[1000];
  snprintf(row, sizeof(row), "%s", movie_row_E);
  MoviePtr m1 = CreateMovieFromRow(row);
  snprintf(row, sizeof(row), "%s", movie_row_F);
  MoviePtr m2 = CreateMovieFromRow(row);
  // strcpy(row, movie_row_G);
  // MoviePtr m3 = CreateMovieFromRow(row);

  // Create Index
  Index index = CreateIndex();

  // Add movie to index
  AddMovieToIndex(index, m1, Genre);
  ASSERT_EQ(NumElemsInHashtable(index), 1);

  AddMovieToIndex(index, m2, Genre);
  ASSERT_EQ(NumElemsInHashtable(index), 1);

  // AddMovieToIndex(index, m3, Genre);
  // ASSERT_EQ(NumElemsInHashtable(index), 1);

  // Destroy movie index
  DestroyIndex(index);
  DestroyLLMovie(m1);
  DestroyLLMovie(m2);
  printf("============DONE BY LINNI CAI============\n");
}

TEST(MovieIndex, AddThreeMovieTwoGenreToIndex) {
  printf("============DONE BY LINNI CAI============\n");
  // Copying the string from a const to an array
  // (to be more similar to the actual use case)
  char row[1000];
  snprintf(row, sizeof(row), "%s", movie_row_A);
  MoviePtr m1 = CreateMovieFromRow(row);
  snprintf(row, sizeof(row), "%s", movie_row_F);
  MoviePtr m2 = CreateMovieFromRow(row);
  snprintf(row, sizeof(row), "%s", movie_row_G);
  MoviePtr m3 = CreateMovieFromRow(row);

  // Create Index
  Index index = CreateIndex();

  // Add movie to index
  AddMovieToIndex(index, m1, Genre);
  ASSERT_EQ(NumElemsInHashtable(index), 1);

  AddMovieToIndex(index, m2, Genre);
  ASSERT_EQ(NumElemsInHashtable(index), 2);

  AddMovieToIndex(index, m3, Genre);
  ASSERT_EQ(NumElemsInHashtable(index), 2);

  // Destroy movie index
  DestroyIndex(index);
  DestroyLLMovie(m1);
  DestroyLLMovie(m2);
  DestroyLLMovie(m3);
  printf("============DONE BY LINNI CAI============\n");
}

TEST(MovieIndex, BuildMovieIndexFromFile) {
  LinkedList movie_list  = ReadFile(const_cast<char *>("data/test"));

  ASSERT_EQ(5u, NumElementsInLinkedList(movie_list));

  Index index = BuildMovieIndex(movie_list, Genre);
  // // Do a few spot checks.
  // // E.g., Pull out a MovieSet from the Hashtable;
  // // Check to see if the set has expected number of movies,
  // // a particular movie, etc.
  DestroyIndex(index);
  // printf("==========LL=number: %d\n", NumElementsInLinkedList(movie_list));
  // free(movie_list);
  // Movie* data;
  // int status = PopLinkedList(movie_list, (void**)&data);
  // // printf("==========LL=status: %d\n", status);
  // while (status == 0) {
  //   status = PopLinkedList(movie_list, (void**)&data);
  //   // printf("==========LL=status: %d\n", status);
  // }
  // data = NULL;
  // printf("==========LL=number: %d\n", NumElementsInLinkedList(movie_list));
  DestroyLinkedList(movie_list, &DestroyLLMovie);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
