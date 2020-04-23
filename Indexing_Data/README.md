# Building a Data Indexer

## Files: 
* ```FileParser```: Responsible for reading in a file, checking for errors, and parse out movies.
* ```Movie```: A struct holding all the Movie info (id, title, type, genre, etc.)
* ```MovieIndex```: A hashtable that indexes movies according to specified field. Basically wraps a hashtable with functionality specific to adding/removing/destroying with MovieSets. The key is the description for the document set, and the value is the document set.
* ```MovieReport```: Responsible for printing out a report given a MovieIndex, to the command line or file.
* ```MovieSet```: A set of Movies that are connected somehow: they have the same value for a given field. If the field is Year, all the movies in the set are made in the same year. It consists of a description and a LinkedList of Movies.


## To run a single Google test

Instead of running all the tests at once, you can run just a single test something like this: 

```
./test_fileparser --gtest_filter=FileParser.CreateMovieFromRow
```

Here, only the ```FileParser.CreateMovieFromRow``` test will run. 

### Memory Check
```
valgrind --leak-check=full -v ./test_fileparser
```
```
==18908== 
==18908== HEAP SUMMARY:
==18908==     in use at exit: 0 bytes in 0 blocks
==18908==   total heap usage: 361 allocs, 361 frees, 125,431 bytes allocated
==18908== 
==18908== All heap blocks were freed -- no leaks are possible
==18908== 
==18908== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==18908== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
valgrind --leak-check=full -v ./test_movieindex
```
```
==18909== 
==18909== HEAP SUMMARY:
==18909==     in use at exit: 0 bytes in 0 blocks
==18909==   total heap usage: 1,928 allocs, 1,928 frees, 174,487 bytes allocated
==18909== 
==18909== All heap blocks were freed -- no leaks are possible
==18909== 
==18909== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==18909== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
valgrind --leak-check=full -v ./example -a ./data/test
```
```
==18920== 
==18920== HEAP SUMMARY:
==18920==     in use at exit: 0 bytes in 0 blocks
==18920==   total heap usage: 400 allocs, 400 frees, 18,456 bytes allocated
==18920== 
==18920== All heap blocks were freed -- no leaks are possible
==18920== 
==18920== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==18920== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
valgrind --leak-check=full -v ./example -c ./data/test
```
```
==18922== 
==18922== HEAP SUMMARY:
==18922==     in use at exit: 0 bytes in 0 blocks
==18922==   total heap usage: 243 allocs, 243 frees, 12,952 bytes allocated
==18922== 
==18922== All heap blocks were freed -- no leaks are possible
==18922== 
==18922== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==18922== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
valgrind --leak-check=full -v ./example -g ./data/test
```
```
==18932== 
==18932== HEAP SUMMARY:
==18932==     in use at exit: 0 bytes in 0 blocks
==18932==   total heap usage: 243 allocs, 243 frees, 12,972 bytes allocated
==18932== 
==18932== All heap blocks were freed -- no leaks are possible
==18932== 
==18932== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==18932== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
valgrind --leak-check=full -v ./example -s ./data/test
```
```
==18934== 
==18934== HEAP SUMMARY:
==18934==     in use at exit: 0 bytes in 0 blocks
==18934==   total heap usage: 260 allocs, 260 frees, 13,492 bytes allocated
==18934== 
==18934== All heap blocks were freed -- no leaks are possible
==18934== 
==18934== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==18934== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
valgrind --leak-check=full -v ./example -a imdb_1000.csv
```
```
==18935== 
==18935== HEAP SUMMARY:
==18935==     in use at exit: 0 bytes in 0 blocks
==18935==   total heap usage: 50,702 allocs, 50,702 frees, 1,891,700 bytes allocated
==18935== 
==18935== All heap blocks were freed -- no leaks are possible
==18935== 
==18935== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==18935== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
``` 

```
valgrind --leak-check=full -v ./example -c imdb_1000.csv
```
```
==18937== 
==18937== HEAP SUMMARY:
==18937==     in use at exit: 0 bytes in 0 blocks
==18937==   total heap usage: 19,767 allocs, 19,767 frees, 798,332 bytes allocated
==18937== 
==18937== All heap blocks were freed -- no leaks are possible
==18937== 
==18937== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==18937== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
valgrind --leak-check=full -v ./example -g imdb_1000.csv
```
```
==18948== 
==18948== HEAP SUMMARY:
==18948==     in use at exit: 0 bytes in 0 blocks
==18948==   total heap usage: 19,779 allocs, 19,779 frees, 798,760 bytes allocated
==18948== 
==18948== All heap blocks were freed -- no leaks are possible
==18948== 
==18948== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==18948== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
valgrind --leak-check=full -v ./example -s imdb_1000.csv
```
```
==18949== 
==18949== HEAP SUMMARY:
==18949==     in use at exit: 0 bytes in 0 blocks
==18949==   total heap usage: 19,816 allocs, 19,816 frees, 800,064 bytes allocated
==18949== 
==18949== All heap blocks were freed -- no leaks are possible
==18949== 
==18949== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==18949== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### Sample Test

```
./test_fileparser
```
```
[==========] Running 10 tests from 2 test cases.
[----------] Global test environment set-up.
[----------] 7 tests from Movie
[ RUN      ] Movie.CreateDestroyMovie
[       OK ] Movie.CreateDestroyMovie (0 ms)
[ RUN      ] Movie.CreateManualAndDestroyMovie
[       OK ] Movie.CreateManualAndDestroyMovie (0 ms)
[ RUN      ] Movie.CreateWithMallocdData
[       OK ] Movie.CreateWithMallocdData (0 ms)
[ RUN      ] Movie.CreateFromRow
[       OK ] Movie.CreateFromRow (0 ms)
[ RUN      ] Movie.CreateFromAlternativeRow
============DONE BY LINNI CAI============
============DONE BY LINNI CAI============
[       OK ] Movie.CreateFromAlternativeRow (0 ms)
[ RUN      ] Movie.CreateFromMissingActorRow
============DONE BY LINNI CAI============
============DONE BY LINNI CAI============
[       OK ] Movie.CreateFromMissingActorRow (0 ms)
[ RUN      ] Movie.CreateFromMissingTitleRow
============DONE BY LINNI CAI============
============DONE BY LINNI CAI============
[       OK ] Movie.CreateFromMissingTitleRow (0 ms)
[----------] 7 tests from Movie (0 ms total)

[----------] 3 tests from FileParser
[ RUN      ] FileParser.ReadGoodFile
[       OK ] FileParser.ReadGoodFile (0 ms)
[ RUN      ] FileParser.ReadNonexistentFile
File could not be opened
[       OK ] FileParser.ReadNonexistentFile (1 ms)
[ RUN      ] FileParser.ReadBinaryFile
File could not be opened
[       OK ] FileParser.ReadBinaryFile (0 ms)
[----------] 3 tests from FileParser (1 ms total)

[----------] Global test environment tear-down
[==========] 10 tests from 2 test cases ran. (1 ms total)
[  PASSED  ] 10 tests.
```

```
./test_movieindex 
```
```
[==========] Running 11 tests from 2 test cases.
[----------] Global test environment set-up.
[----------] 2 tests from MovieSet
[ RUN      ] MovieSet.CreateDestroy
[       OK ] MovieSet.CreateDestroy (0 ms)
[ RUN      ] MovieSet.AddOneMovie
[       OK ] MovieSet.AddOneMovie (0 ms)
[----------] 2 tests from MovieSet (0 ms total)

[----------] 9 tests from MovieIndex
[ RUN      ] MovieIndex.CreateDestroy
[       OK ] MovieIndex.CreateDestroy (0 ms)
[ RUN      ] MovieIndex.AddMovieToIndexStarRating
============DONE BY LINNI CAI============
============DONE BY LINNI CAI============
[       OK ] MovieIndex.AddMovieToIndexStarRating (0 ms)
[ RUN      ] MovieIndex.AddMovieToIndexActor
============DONE BY LINNI CAI============
============DONE BY LINNI CAI============
[       OK ] MovieIndex.AddMovieToIndexActor (0 ms)
[ RUN      ] MovieIndex.AddMovieToIndexContentRating
[       OK ] MovieIndex.AddMovieToIndexContentRating (0 ms)
[ RUN      ] MovieIndex.AddMovieToIndexGenre
============DONE BY LINNI CAI============
============DONE BY LINNI CAI============
[       OK ] MovieIndex.AddMovieToIndexGenre (0 ms)
[ RUN      ] MovieIndex.AddThreeMovieToIndex
============DONE BY LINNI CAI============
============DONE BY LINNI CAI============
[       OK ] MovieIndex.AddThreeMovieToIndex (1 ms)
[ RUN      ] MovieIndex.AddThreeMovieSameGenreToIndex
============DONE BY LINNI CAI============
============DONE BY LINNI CAI============
[       OK ] MovieIndex.AddThreeMovieSameGenreToIndex (0 ms)
[ RUN      ] MovieIndex.AddThreeMovieTwoGenreToIndex
============DONE BY LINNI CAI============
============DONE BY LINNI CAI============
[       OK ] MovieIndex.AddThreeMovieTwoGenreToIndex (0 ms)
[ RUN      ] MovieIndex.BuildMovieIndexFromFile
[       OK ] MovieIndex.BuildMovieIndexFromFile (0 ms)
[----------] 9 tests from MovieIndex (4 ms total)

[----------] Global test environment tear-down
[==========] 11 tests from 2 test cases ran. (5 ms total)
[  PASSED  ] 11 tests.
```

```
./example -g ./data/test
```
```
indexType: Crime
4 items
  The Shawshank Redemption
  The Godfather
  The Godfather: Part II
  Pulp Fiction

indexType: Action
1 items
  The Dark Knight
```