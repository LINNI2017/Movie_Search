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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "QueryProcessor.h"
#include "MovieTitleIndex.h"
#include "LinkedList.h"
#include "Hashtable.h"
#include "DocSet.h"

SearchResultIter CreateSearchResultIter(DocumentSet set) {
  SearchResultIter iter =
    (SearchResultIter)malloc(sizeof(struct searchResultIter));

    // STEP 7: Implement the initialization of the iter.
    iter->doc_iter = CreateHashtableIterator(set->doc_index);
    HTKeyValue kvp;
    if (HTIteratorGet(iter->doc_iter, &kvp) != 0) {
      return NULL;
    }
    iter->cur_doc_id = kvp.key;
    iter->offset_iter = CreateLLIter((LinkedList)kvp.value);
  return iter;
}

void DestroySearchResultIter(SearchResultIter iter) {
  // Destroy LLIter
  if (iter->offset_iter != NULL) {
    DestroyLLIter(iter->offset_iter);
  }

  // Destroy doc_iter
  DestroyHashtableIterator(iter->doc_iter);

  free(iter);
}



SearchResultIter FindMovies(MovieTitleIndex index, char *term) {
  DocumentSet set = GetDocumentSet(index, term);
  if (set == NULL) {
    return NULL;
  }
  printf("Getting docs for movieset term: \"%s\"\n", set->desc);
  SearchResultIter iter = CreateSearchResultIter(set);
  return iter;
}


int SearchResultGet(SearchResultIter iter, SearchResult output) {
  // STEP 9: Implement SearchResultGet
  if (iter == NULL) {
    return -1;
  }
  int* row_id_ptr;
  if (LLIterGetPayload(iter->offset_iter, (void**)&row_id_ptr) == 0) {  // get
    output->doc_id = iter->cur_doc_id;
    output->row_id = (int)*row_id_ptr;
  } else {  // fail get
    return -1;
  }
  return 0;
}

int SearchResultNext(SearchResultIter iter) {
  // STEP 8: Implement SearchResultNext


  if (iter == NULL || SearchResultIterHasMore(iter) == 0) {
    return -1;
  }

  // printf("====== lliter has next: %d\n", LLIterHasNext(iter->offset_iter));
  if (LLIterHasNext(iter->offset_iter) == 0) {  // offset has no next
    // printf("====== offset has no next\n");
    DestroyLLIter(iter->offset_iter);
    iter->offset_iter = NULL;
    if (HTIteratorNext(iter->doc_iter) != 0) {  // doc has no next
      // printf("====== htiter has no next\n");
      return -1;
    } else {  // doc has next
      // printf("====== htiter has next\n");
      HTKeyValue kvp;
      if (HTIteratorGet(iter->doc_iter, &kvp) != 0) {  // fail get
        // printf("====== htiter get fail\n");
        return -1;
      } else {  // get
        // printf("====== htiter get\n");
        iter->cur_doc_id = kvp.key;
        iter->offset_iter = CreateLLIter((LinkedList)kvp.value);
      }
    }
  } else {  // offset has next
    // printf("====== offset has next\n");
    LLIterNext(iter->offset_iter);
  }
  return 0;
}

// Return 0 if no more
int SearchResultIterHasMore(SearchResultIter iter) {
  if (iter->doc_iter == NULL) {
    return 0;
  }
  if (LLIterHasNext(iter->offset_iter) == 0) {
    return (HTIteratorHasMore(iter->doc_iter));
  }

  return 1;
}
