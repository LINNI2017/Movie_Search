// /*
//  *  Created by Adrienne Slaughter
//  *  CS 5007 Summer 2019
//  *  Northeastern University, Seattle
//  *
//  *  This is free software: you can redistribute it and/or modify
//  *  it under the terms of the GNU General Public License as published by
//  *  the Free Software Foundation, either version 3 of the License, or
//  *  (at your option) any later version.
//  *
//  *  It is distributed in the hope that it will be useful,
//  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  *  GNU General Public License for more details.
//  *
//  *  See <http://www.gnu.org/licenses/>.
//  */

#include "gtest/gtest.h"

extern "C" {
#include <string.h>

#include "Hashtable.h"
#include "LinkedList.h"
#include "DirectoryParser.h"
#include "DocIdMap.h"
#include "DocSet.h"
#include "FileCrawler.h"
#include "MovieTitleIndex.h"
#include "QueryProcessor.h"
#include "DirectoryParser_MT.h"
}


const char* kMovie1 = "1|movie|Sleepless in Seattle|Sleepless in Seattle|0|1984|-|120|Comedy,Romance";
const char* kMovie2 = "tt3247810|tvEpisode|Jonathan Kite|Jonathan Kite|0|2012|-|-|Comedy";
const char* kMovie3 = "tt0003609|movie|Alexandra|Alexandra|0|1915|-|-|-";
const char* kMovie4 = "tt0003620|short|Among the Mourners|Among the Mourners|0|1914|-|-|Comedy,Short";

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// TEST(DirectoryParser, ParseTheFiles_OG_2_1) {
//   printf("=======OG Parse 2 with 1 thread=======\n");

//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);
//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/fourth/fifth/tinyaa");
//   PutFileInMap(f1, docs);
//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);
//   ParseTheFiles(docs, ind);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 57);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

// TEST(DirectoryParser, ParseTheFiles_MT_2_1) {
//   printf("=======MT Parse 2 with 1 threads=======\n");

//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);
//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/fourth/fifth/tinyaa");
//   PutFileInMap(f1, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 1);
//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 2);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);
//   ParseTheFiles_MT(docs, ind, 1);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 57);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

// TEST(DirectoryParser, ParseTheFiles_MT_2_2) {
//   printf("=======MT Parse 2 with 2 threads=======\n");

//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);
//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/fourth/fifth/tinyaa");
//   PutFileInMap(f1, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 1);
//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 2);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);
//   ParseTheFiles_MT(docs, ind, 2);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 57);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

// TEST(DirectoryParser, ParseTheFiles_OG_3_1) {
//   printf("=======OG Parse 3 with 1 thread=======\n");
//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);

//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/tinybr");
//   PutFileInMap(f1, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 1);

//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 2);

//   char *f3 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f3, "data_tiny/tinyce");
//   PutFileInMap(f3, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 3);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);

//   ParseTheFiles(docs, ind);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 80);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

// TEST(DirectoryParser, ParseTheFiles_MT_3_1) {
//   printf("=======MT Parse 3 with 1 thread=======\n");
//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);

//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/tinybr");
//   PutFileInMap(f1, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 1);

//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 2);

//   char *f3 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f3, "data_tiny/tinyce");
//   PutFileInMap(f3, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 3);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);

//   ParseTheFiles_MT(docs, ind, 1);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 80);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

// TEST(DirectoryParser, ParseTheFiles_MT_3_2) {
//   printf("=======MT Parse 3 with 2 threads=======\n");
//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);

//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/tinybr");
//   PutFileInMap(f1, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 1);

//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 2);

//   char *f3 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f3, "data_tiny/tinyce");
//   PutFileInMap(f3, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 3);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);

//   ParseTheFiles_MT(docs, ind, 2);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 80);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

// TEST(DirectoryParser, ParseTheFiles_MT_3_3) {
//   printf("=======MT Parse 3 with 3 threads=======\n");
//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);

//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/tinybr");
//   PutFileInMap(f1, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 1);

//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 2);

//   char *f3 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f3, "data_tiny/tinyce");
//   PutFileInMap(f3, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 3);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);

//   ParseTheFiles_MT(docs, ind, 3);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 80);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

// TEST(DirectoryParser, ParseTheFiles_OG_4_1) {
//   printf("=======OG Parse 4 with 1 thread=======\n");
//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);

//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/tinybr");
//   PutFileInMap(f1, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 1);

//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 2);

//   char *f3 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f3, "data_tiny/tinyce");
//   PutFileInMap(f3, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 3);

//   char *f4 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f4, "data_tiny/first/tinydi");
//   PutFileInMap(f4, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 4);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);

//   ParseTheFiles(docs, ind);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 101);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

// TEST(DirectoryParser, ParseTheFiles_MT_4_1) {
//   printf("=======MT Parse 4 with 1 thread=======\n");
//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);

//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/tinybr");
//   PutFileInMap(f1, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 1);

//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 2);

//   char *f3 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f3, "data_tiny/tinyce");
//   PutFileInMap(f3, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 3);

//   char *f4 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f4, "data_tiny/first/tinydi");
//   PutFileInMap(f4, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 4);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);

//   ParseTheFiles_MT(docs, ind, 1);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 101);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

// TEST(DirectoryParser, ParseTheFiles_MT_4_2) {
//   printf("=======MT Parse 4 with 2 threadS=======\n");
//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);

//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/tinybr");
//   PutFileInMap(f1, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 1);

//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 2);

//   char *f3 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f3, "data_tiny/tinyce");
//   PutFileInMap(f3, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 3);

//   char *f4 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f4, "data_tiny/first/tinydi");
//   PutFileInMap(f4, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 4);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);

//   ParseTheFiles_MT(docs, ind, 2);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 101);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

// TEST(DirectoryParser, ParseTheFiles_MT_4_3) {
//   printf("=======MT Parse 4 with 3 thread=======\n");
//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);

//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/tinybr");
//   PutFileInMap(f1, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 1);

//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 2);

//   char *f3 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f3, "data_tiny/tinyce");
//   PutFileInMap(f3, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 3);

//   char *f4 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f4, "data_tiny/first/tinydi");
//   PutFileInMap(f4, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 4);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);

//   ParseTheFiles_MT(docs, ind, 3);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 101);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

// TEST(DirectoryParser, ParseTheFiles_MT_4_4) {
//   printf("=======MT Parse 4 with 4 threads=======\n");
//   DocIdMap docs = CreateDocIdMap();
//   ASSERT_NE(docs, nullptr);

//   char *f1 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f1, "data_tiny/tinybr");
//   PutFileInMap(f1, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 1);

//   char *f2 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f2, "data_tiny/tinybu");
//   PutFileInMap(f2, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 2);

//   char *f3 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f3, "data_tiny/tinyce");
//   PutFileInMap(f3, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 3);

//   char *f4 = (char*)(malloc(sizeof('a')*30));
//   strcpy(f4, "data_tiny/first/tinydi");
//   PutFileInMap(f4, docs);
//   EXPECT_EQ(NumElemsInHashtable(docs), 4);

//   MovieTitleIndex ind = CreateMovieTitleIndex();
//   ASSERT_NE(ind, nullptr);

//   ParseTheFiles_MT(docs, ind, 4);
//   EXPECT_EQ(NumElemsInHashtable(ind->ht), 101);

//   DestroyMovieTitleIndex(ind);
//   DestroyDocIdMap(docs);
// }

TEST(DirectoryParser, ParseTheFiles_OG_7_1) {
  printf("=======OG Parse 7 with 1 thread========\n");
  DocIdMap docs = CreateDocIdMap();
  ASSERT_NE(docs, nullptr);

  char *f1 = (char*)(malloc(sizeof('a')*30));
  strcpy(f1, "data_tiny/tinybr");
  PutFileInMap(f1, docs);

  char *f2 = (char*)(malloc(sizeof('a')*30));
  strcpy(f2, "data_tiny/tinybu");
  PutFileInMap(f2, docs);

  char *f3 = (char*)(malloc(sizeof('a')*30));
  strcpy(f3, "data_tiny/tinyce");
  PutFileInMap(f3, docs);

  char *f4 = (char*)(malloc(sizeof('a')*30));
  strcpy(f4, "data_tiny/first/tinydi");
  PutFileInMap(f4, docs);

  char *f5 = (char*)(malloc(sizeof('a')*30));
  strcpy(f5, "data_tiny/first/tinydv");
  PutFileInMap(f5, docs);

  char *f6 = (char*)(malloc(sizeof('a')*30));
  strcpy(f6, "data_tiny/second/tinybs");
  PutFileInMap(f6, docs);

  char *f7 = (char*)(malloc(sizeof('a')*30));
  strcpy(f7, "data_tiny/second/tinycc");
  PutFileInMap(f7, docs);

  MovieTitleIndex ind = CreateMovieTitleIndex();
  ASSERT_NE(ind, nullptr);

  ParseTheFiles(docs, ind);
  EXPECT_EQ(NumElemsInHashtable(ind->ht), 141);

  DestroyMovieTitleIndex(ind);
  DestroyDocIdMap(docs);
}

TEST(DirectoryParser, ParseTheFiles_MT_7_1) {
  printf("=======MT Parse 7 with 1 thread========\n");
  DocIdMap docs = CreateDocIdMap();
  ASSERT_NE(docs, nullptr);

  char *f1 = (char*)(malloc(sizeof('a')*30));
  strcpy(f1, "data_tiny/tinybr");
  PutFileInMap(f1, docs);

  char *f2 = (char*)(malloc(sizeof('a')*30));
  strcpy(f2, "data_tiny/tinybu");
  PutFileInMap(f2, docs);

  char *f3 = (char*)(malloc(sizeof('a')*30));
  strcpy(f3, "data_tiny/tinyce");
  PutFileInMap(f3, docs);

  char *f4 = (char*)(malloc(sizeof('a')*30));
  strcpy(f4, "data_tiny/first/tinydi");
  PutFileInMap(f4, docs);

  char *f5 = (char*)(malloc(sizeof('a')*30));
  strcpy(f5, "data_tiny/first/tinydv");
  PutFileInMap(f5, docs);

  char *f6 = (char*)(malloc(sizeof('a')*30));
  strcpy(f6, "data_tiny/second/tinybs");
  PutFileInMap(f6, docs);

  char *f7 = (char*)(malloc(sizeof('a')*30));
  strcpy(f7, "data_tiny/second/tinycc");
  PutFileInMap(f7, docs);

  MovieTitleIndex ind = CreateMovieTitleIndex();
  ASSERT_NE(ind, nullptr);

  ParseTheFiles_MT(docs, ind, 1);
  EXPECT_EQ(NumElemsInHashtable(ind->ht), 141);

  DestroyMovieTitleIndex(ind);
  DestroyDocIdMap(docs);
}

TEST(DirectoryParser, ParseTheFiles_MT_7_2) {
  printf("=======MT Parse 7 with 2 threads=======\n");
  DocIdMap docs = CreateDocIdMap();
  ASSERT_NE(docs, nullptr);

  char *f1 = (char*)(malloc(sizeof('a')*30));
  strcpy(f1, "data_tiny/tinybr");
  PutFileInMap(f1, docs);

  char *f2 = (char*)(malloc(sizeof('a')*30));
  strcpy(f2, "data_tiny/tinybu");
  PutFileInMap(f2, docs);

  char *f3 = (char*)(malloc(sizeof('a')*30));
  strcpy(f3, "data_tiny/tinyce");
  PutFileInMap(f3, docs);

  char *f4 = (char*)(malloc(sizeof('a')*30));
  strcpy(f4, "data_tiny/first/tinydi");
  PutFileInMap(f4, docs);

  char *f5 = (char*)(malloc(sizeof('a')*30));
  strcpy(f5, "data_tiny/first/tinydv");
  PutFileInMap(f5, docs);

  char *f6 = (char*)(malloc(sizeof('a')*30));
  strcpy(f6, "data_tiny/second/tinybs");
  PutFileInMap(f6, docs);

  char *f7 = (char*)(malloc(sizeof('a')*30));
  strcpy(f7, "data_tiny/second/tinycc");
  PutFileInMap(f7, docs);

  MovieTitleIndex ind = CreateMovieTitleIndex();
  ASSERT_NE(ind, nullptr);

  ParseTheFiles_MT(docs, ind, 2);
  EXPECT_EQ(NumElemsInHashtable(ind->ht), 141);

  DestroyMovieTitleIndex(ind);
  DestroyDocIdMap(docs);
}

TEST(DirectoryParser, ParseTheFiles_MT_7_3) {
  printf("=======MT Parse 7 with 3 threads=======\n");
  DocIdMap docs = CreateDocIdMap();
  ASSERT_NE(docs, nullptr);

  char *f1 = (char*)(malloc(sizeof('a')*30));
  strcpy(f1, "data_tiny/tinybr");
  PutFileInMap(f1, docs);

  char *f2 = (char*)(malloc(sizeof('a')*30));
  strcpy(f2, "data_tiny/tinybu");
  PutFileInMap(f2, docs);

  char *f3 = (char*)(malloc(sizeof('a')*30));
  strcpy(f3, "data_tiny/tinyce");
  PutFileInMap(f3, docs);

  char *f4 = (char*)(malloc(sizeof('a')*30));
  strcpy(f4, "data_tiny/first/tinydi");
  PutFileInMap(f4, docs);

  char *f5 = (char*)(malloc(sizeof('a')*30));
  strcpy(f5, "data_tiny/first/tinydv");
  PutFileInMap(f5, docs);

  char *f6 = (char*)(malloc(sizeof('a')*30));
  strcpy(f6, "data_tiny/second/tinybs");
  PutFileInMap(f6, docs);

  char *f7 = (char*)(malloc(sizeof('a')*30));
  strcpy(f7, "data_tiny/second/tinycc");
  PutFileInMap(f7, docs);

  MovieTitleIndex ind = CreateMovieTitleIndex();
  ASSERT_NE(ind, nullptr);

  ParseTheFiles_MT(docs, ind, 3);
  EXPECT_EQ(NumElemsInHashtable(ind->ht), 141);

  DestroyMovieTitleIndex(ind);
  DestroyDocIdMap(docs);
}

TEST(DirectoryParser, ParseTheFiles_MT_7_4) {
  printf("=======MT Parse 7 with 4 threads=======\n");
  DocIdMap docs = CreateDocIdMap();
  ASSERT_NE(docs, nullptr);

  char *f1 = (char*)(malloc(sizeof('a')*30));
  strcpy(f1, "data_tiny/tinybr");
  PutFileInMap(f1, docs);

  char *f2 = (char*)(malloc(sizeof('a')*30));
  strcpy(f2, "data_tiny/tinybu");
  PutFileInMap(f2, docs);

  char *f3 = (char*)(malloc(sizeof('a')*30));
  strcpy(f3, "data_tiny/tinyce");
  PutFileInMap(f3, docs);

  char *f4 = (char*)(malloc(sizeof('a')*30));
  strcpy(f4, "data_tiny/first/tinydi");
  PutFileInMap(f4, docs);

  char *f5 = (char*)(malloc(sizeof('a')*30));
  strcpy(f5, "data_tiny/first/tinydv");
  PutFileInMap(f5, docs);

  char *f6 = (char*)(malloc(sizeof('a')*30));
  strcpy(f6, "data_tiny/second/tinybs");
  PutFileInMap(f6, docs);

  char *f7 = (char*)(malloc(sizeof('a')*30));
  strcpy(f7, "data_tiny/second/tinycc");
  PutFileInMap(f7, docs);

  MovieTitleIndex ind = CreateMovieTitleIndex();
  ASSERT_NE(ind, nullptr);

  ParseTheFiles_MT(docs, ind, 4);
  EXPECT_EQ(NumElemsInHashtable(ind->ht), 141);

  DestroyMovieTitleIndex(ind);
  DestroyDocIdMap(docs);
}

TEST(DirectoryParser, ParseTheFiles_MT_7_5) {
  printf("=======MT Parse 7 with 5 threads=======\n");
  DocIdMap docs = CreateDocIdMap();
  ASSERT_NE(docs, nullptr);

  char *f1 = (char*)(malloc(sizeof('a')*30));
  strcpy(f1, "data_tiny/tinybr");
  PutFileInMap(f1, docs);

  char *f2 = (char*)(malloc(sizeof('a')*30));
  strcpy(f2, "data_tiny/tinybu");
  PutFileInMap(f2, docs);

  char *f3 = (char*)(malloc(sizeof('a')*30));
  strcpy(f3, "data_tiny/tinyce");
  PutFileInMap(f3, docs);

  char *f4 = (char*)(malloc(sizeof('a')*30));
  strcpy(f4, "data_tiny/first/tinydi");
  PutFileInMap(f4, docs);

  char *f5 = (char*)(malloc(sizeof('a')*30));
  strcpy(f5, "data_tiny/first/tinydv");
  PutFileInMap(f5, docs);

  char *f6 = (char*)(malloc(sizeof('a')*30));
  strcpy(f6, "data_tiny/second/tinybs");
  PutFileInMap(f6, docs);

  char *f7 = (char*)(malloc(sizeof('a')*30));
  strcpy(f7, "data_tiny/second/tinycc");
  PutFileInMap(f7, docs);

  MovieTitleIndex ind = CreateMovieTitleIndex();
  ASSERT_NE(ind, nullptr);

  ParseTheFiles_MT(docs, ind, 5);
  EXPECT_EQ(NumElemsInHashtable(ind->ht), 141);

  DestroyMovieTitleIndex(ind);
  DestroyDocIdMap(docs);
}

TEST(DirectoryParser, ParseTheFiles_MT_7_6) {
  printf("=======MT Parse 7 with 6 threads=======\n");
  DocIdMap docs = CreateDocIdMap();
  ASSERT_NE(docs, nullptr);

  char *f1 = (char*)(malloc(sizeof('a')*30));
  strcpy(f1, "data_tiny/tinybr");
  PutFileInMap(f1, docs);

  char *f2 = (char*)(malloc(sizeof('a')*30));
  strcpy(f2, "data_tiny/tinybu");
  PutFileInMap(f2, docs);

  char *f3 = (char*)(malloc(sizeof('a')*30));
  strcpy(f3, "data_tiny/tinyce");
  PutFileInMap(f3, docs);

  char *f4 = (char*)(malloc(sizeof('a')*30));
  strcpy(f4, "data_tiny/first/tinydi");
  PutFileInMap(f4, docs);

  char *f5 = (char*)(malloc(sizeof('a')*30));
  strcpy(f5, "data_tiny/first/tinydv");
  PutFileInMap(f5, docs);

  char *f6 = (char*)(malloc(sizeof('a')*30));
  strcpy(f6, "data_tiny/second/tinybs");
  PutFileInMap(f6, docs);

  char *f7 = (char*)(malloc(sizeof('a')*30));
  strcpy(f7, "data_tiny/second/tinycc");
  PutFileInMap(f7, docs);

  MovieTitleIndex ind = CreateMovieTitleIndex();
  ASSERT_NE(ind, nullptr);

  ParseTheFiles_MT(docs, ind, 6);
  EXPECT_EQ(NumElemsInHashtable(ind->ht), 141);

  DestroyMovieTitleIndex(ind);
  DestroyDocIdMap(docs);
}

TEST(DirectoryParser, ParseTheFiles_MT_7_7) {
  printf("=======MT Parse 7 with 7 threads=======\n");
  DocIdMap docs = CreateDocIdMap();
  ASSERT_NE(docs, nullptr);

  char *f1 = (char*)(malloc(sizeof('a')*30));
  strcpy(f1, "data_tiny/tinybr");
  PutFileInMap(f1, docs);

  char *f2 = (char*)(malloc(sizeof('a')*30));
  strcpy(f2, "data_tiny/tinybu");
  PutFileInMap(f2, docs);

  char *f3 = (char*)(malloc(sizeof('a')*30));
  strcpy(f3, "data_tiny/tinyce");
  PutFileInMap(f3, docs);

  char *f4 = (char*)(malloc(sizeof('a')*30));
  strcpy(f4, "data_tiny/first/tinydi");
  PutFileInMap(f4, docs);

  char *f5 = (char*)(malloc(sizeof('a')*30));
  strcpy(f5, "data_tiny/first/tinydv");
  PutFileInMap(f5, docs);

  char *f6 = (char*)(malloc(sizeof('a')*30));
  strcpy(f6, "data_tiny/second/tinybs");
  PutFileInMap(f6, docs);

  char *f7 = (char*)(malloc(sizeof('a')*30));
  strcpy(f7, "data_tiny/second/tinycc");
  PutFileInMap(f7, docs);

  MovieTitleIndex ind = CreateMovieTitleIndex();
  ASSERT_NE(ind, nullptr);

  ParseTheFiles_MT(docs, ind, 7);
  EXPECT_EQ(NumElemsInHashtable(ind->ht), 141);

  DestroyMovieTitleIndex(ind);
  DestroyDocIdMap(docs);
}
