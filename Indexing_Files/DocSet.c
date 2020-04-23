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
#include <string.h>

#include "DocSet.h"
#include "Hashtable.h"
#include "Util.h"

int AddDocInfoToSet(DocumentSet set,  uint64_t docId, int rowId) {
  // STEP 4: Implement AddDocInfoToSet.
  // Make sure there are no duplicate rows or docIds.
  Hashtable table = set->doc_index;

  HTKeyValue old_kvp;
  old_kvp.key = (uint64_t)docId;

  int status = LookupInHashtable(table, old_kvp.key, &old_kvp);
  // printf("========== status: %d\n", status);
  if (status == 0) {  // existed key
    // search if exist value
    int* old_row_id;
    LLIter iter = CreateLLIter((LinkedList)old_kvp.value);
    if (LLIterGetPayload(iter, (void**)&old_row_id) == 0) {
      if (rowId == *old_row_id) {
        DestroyLLIter(iter);
        return -1;
      }
    }
    while (LLIterHasNext(iter) == 1) {
      LLIterNext(iter);
      if (LLIterGetPayload(iter, (void**)&old_row_id) == 0) {
        if (rowId == *old_row_id) {
          DestroyLLIter(iter);
          return -1;
        }
      }
    }
    DestroyLLIter(iter);
    // no such value
    int* row_id_ptr = (int*)malloc(sizeof(1)*(rowId / 10 + 1));
    memcpy(row_id_ptr, &rowId, sizeof(1)*(rowId / 10 + 1));
    AppendLinkedList((LinkedList)old_kvp.value, row_id_ptr);
  } else if (status == -1) {  // no such key
    HTKeyValue new_kvp;
    new_kvp.key = old_kvp.key;
    LinkedList list = CreateLinkedList();
    new_kvp.value = list;
    PutInHashtable(table, new_kvp, &old_kvp);
    int* row_id_ptr = (int*)malloc(sizeof(1)*(rowId / 10 + 1));
    memcpy(row_id_ptr, &rowId, sizeof(1)*(rowId / 10 + 1));
    AppendLinkedList(list, row_id_ptr);
  } else {
    return -1;
  }
  return 0;
}

int DocumentSetContainsDoc(DocumentSet set, uint64_t docId) {
  // STEP 5: Implement DocumentSetContainsDoc
  if (set == NULL) {
    return -1;
  }
  HTKeyValue old_kvp;
  old_kvp.key = (uint64_t)docId;
  Hashtable table = set->doc_index;
  int status = LookupInHashtable(table, old_kvp.key, &old_kvp);
  // printf("========== status: %d\n", status);
  if (status == 0) {  // existed key
    return 0;
  } else {
    return -1;
  }
}

void PrintOffsetList(LinkedList list) {
  printf("Printing offset list\n");
  LLIter iter = CreateLLIter(list);
  int* payload;
  while (LLIterHasNext(iter) != 0) {
    LLIterGetPayload(iter, (void**)&payload);
    printf("%d\t", *((int*)payload));
    LLIterNext(iter);
  }
}


DocumentSet CreateDocumentSet(char *desc) {
  DocumentSet set = (DocumentSet)malloc(sizeof(struct docSet));
  if (set == NULL) {
    // Out of memory
    printf("Couldn't malloc for movieSet %s\n", desc);
    return NULL;
  }
  int len = strlen(desc);
  set->desc = (char*)malloc((len + 1) *  sizeof('a'));
  if (set->desc == NULL) {
    printf("Couldn't malloc for movieSet->desc");
    return NULL;
  }
  snprintf(set->desc, len + 1, "%s", desc);
  set->doc_index = CreateHashtable(16);
  return set;
}


void DestroyOffsetList(void *val) {
  LinkedList list = (LinkedList)val;
  DestroyLinkedList(list, &SimpleFree);
}

void DestroyDocumentSet(DocumentSet set) {
  // Free desc
  free(set->desc);
  // Free doc_index
  DestroyHashtable(set->doc_index, &DestroyOffsetList);
  // Free set
  free(set);
}
