#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/time.h>
#include <time.h>

#include <unistd.h>
#include <errno.h>

#include "Hashtable.h"

#include "DocIdMap.h"
#include "FileCrawler.h"
#include "MovieTitleIndex.h"

#include "DirectoryParser.h"
#include "DirectoryParser_MT.h"


int main(int argc, char *argv[]) {
  // Check arguments
  if (argc != 2) {
    printf("Wrong number of arguments.\n");
    printf("usage: main <directory_to_crawl>\n");
    return 0;
  }

  DocIdMap docs;

  // Create a DocIdMap
  docs = CreateDocIdMap();
  CrawlFilesToMap(argv[1], docs);
  printf("Crawled %d files.\n", NumElemsInHashtable(docs));
  printf("Created DocIdMap\n");

  MovieTitleIndex doc_index_MT;

  // You can use these to do timing from Benchmarker if you want.
  // clock_t start2, end2;
  // double cpu_time_used;

  // clock_t start, end;
  // double cpu_time_used;

  // Create the index
  MovieTitleIndex doc_index = CreateMovieTitleIndex();

  // Index the files
  printf("Parsing and indexing files...\n");
  printf("=======OG Parse with 1 thread=========\n");
  ParseTheFiles(docs, doc_index);
  printf("%d entries in the index.\n",
    NumElemsInHashtable(doc_index->ht));
  printf("======================================\n");
  DestroyMovieTitleIndex(doc_index);

  // ======================
  // Index using 1 thread
  // ======================
  doc_index_MT = CreateMovieTitleIndex();
  // printf("Parsing and indexing files...\n");
  printf("=======MT Parse with 1 thread=========\n");
  ParseTheFiles_MT(docs, doc_index_MT, 1);
  printf("%d entries in the index.\n",
    NumElemsInHashtable(doc_index_MT->ht));
  printf("======================================\n");
  DestroyMovieTitleIndex(doc_index_MT);

  // ======================
  // Index using 5 threads
  // ======================
  doc_index_MT = CreateMovieTitleIndex();
  printf("=======MT Parse with 5 threads========\n");
  ParseTheFiles_MT(docs, doc_index_MT, 5);
  printf("%d entries in the index.\n",
    NumElemsInHashtable(doc_index_MT->ht));
  printf("======================================\n");
  DestroyMovieTitleIndex(doc_index_MT);

  // ======================
  // Index using 10 threads
  // ======================
  doc_index_MT = CreateMovieTitleIndex();
  printf("=======MT Parse with 10 threads=======\n");
  ParseTheFiles_MT(docs, doc_index_MT, 10);
  printf("%d entries in the index.\n",
    NumElemsInHashtable(doc_index_MT->ht));
  printf("======================================\n");
  DestroyMovieTitleIndex(doc_index_MT);

  // // ======================
  // // Index using 15 threads
  // // ======================
  // doc_index_MT = CreateMovieTitleIndex();
  // printf("=======MT Parse with 15 threads=======\n");
  // ParseTheFiles_MT(docs, doc_index_MT, 15);
  // printf("%d entries in the index.\n",
  //   NumElemsInHashtable(doc_index_MT->ht));
  // printf("======================================\n");
  // DestroyMovieTitleIndex(doc_index_MT);

  // ======================
  // Index using 20 threads
  // ======================
  doc_index_MT = CreateMovieTitleIndex();
  printf("=======MT Parse with 20 threads=======\n");
  ParseTheFiles_MT(docs, doc_index_MT, 20);
  printf("%d entries in the index.\n",
    NumElemsInHashtable(doc_index_MT->ht));
  printf("======================================\n");
  DestroyMovieTitleIndex(doc_index_MT);

  // // ======================
  // // Index using 30 threads
  // // ======================
  // doc_index_MT = CreateMovieTitleIndex();
  // printf("=======MT Parse with 30 threads=======\n");
  // ParseTheFiles_MT(docs, doc_index_MT, 30);
  // printf("%d entries in the index.\n",
  //   NumElemsInHashtable(doc_index_MT->ht));
  // printf("======================================\n");
  // DestroyMovieTitleIndex(doc_index_MT);

  // // ======================
  // // Index using 40 threads
  // // ======================
  // doc_index_MT = CreateMovieTitleIndex();
  // printf("=======MT Parse with 40 threads=======\n");
  // ParseTheFiles_MT(docs, doc_index_MT, 40);
  // printf("%d entries in the index.\n",
  //   NumElemsInHashtable(doc_index_MT->ht));
  // printf("======================================\n");
  // DestroyMovieTitleIndex(doc_index_MT);

  // // ======================
  // // Index using 50 threads
  // // ======================
  // doc_index_MT = CreateMovieTitleIndex();
  // printf("=======MT Parse with 50 threads=======\n");
  // ParseTheFiles_MT(docs, doc_index_MT, 50);
  // printf("%d entries in the index.\n",
  //   NumElemsInHashtable(doc_index_MT->ht));
  // printf("======================================\n");
  // DestroyMovieTitleIndex(doc_index_MT);

  // // ======================
  // // Index using 52 threads
  // // ======================
  // doc_index_MT = CreateMovieTitleIndex();
  // printf("=======MT Parse with 52 threads=======\n");
  // ParseTheFiles_MT(docs, doc_index_MT, 52);
  // printf("%d entries in the index.\n",
  //   NumElemsInHashtable(doc_index_MT->ht));
  // printf("======================================\n");
  // DestroyMovieTitleIndex(doc_index_MT);

  // Add more tests (or modify the above) if you'd like

  DestroyDocIdMap(docs);
}
