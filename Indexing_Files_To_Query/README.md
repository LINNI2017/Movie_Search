# Indexing Files to Query

### Clint.py style check
```
./clint.py DirectoryParser.c DocIdMap.c DocSet.c MovieTitleIndex.c QueryProcessor.c main.c
```
```
Done processing DirectoryParser.c
Done processing DocIdMap.c
Done processing DocSet.c
Done processing MovieTitleIndex.c
Done processing QueryProcessor.c
Done processing main.c
Total errors found: 0
```

### Valgrind memory check
```
valgrind ./test_suite 
```
```
==31523== Memcheck, a memory error detector
==31523== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==31523== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==31523== Command: ./test_suite
==31523== 
[==========] Running 8 tests from 5 test cases.
[----------] Global test environment set-up.
[----------] 2 tests from DirectoryParser
[ RUN      ] DirectoryParser.IndexTheFile_OneFile
[       OK ] DirectoryParser.IndexTheFile_OneFile (79 ms)
[ RUN      ] DirectoryParser.ParseTheFiles
[       OK ] DirectoryParser.ParseTheFiles (28 ms)
[----------] 2 tests from DirectoryParser (122 ms total)

[----------] 2 tests from DocumentSet
[ RUN      ] DocumentSet.CreateDestroy
[       OK ] DocumentSet.CreateDestroy (4 ms)
[ RUN      ] DocumentSet.AddMovieToSet
[       OK ] DocumentSet.AddMovieToSet (11 ms)
[----------] 2 tests from DocumentSet (15 ms total)

[----------] 1 test from DocIdMap
[ RUN      ] DocIdMap.Full
[       OK ] DocIdMap.Full (8 ms)
[----------] 1 test from DocIdMap (8 ms total)

[----------] 1 test from FileCrawler
[ RUN      ] FileCrawler.CrawlFilesToMap
[       OK ] FileCrawler.CrawlFilesToMap (21 ms)
[----------] 1 test from FileCrawler (21 ms total)

[----------] 2 tests from MovieTitleIndex
[ RUN      ] MovieTitleIndex.Full
[       OK ] MovieTitleIndex.Full (12 ms)
[ RUN      ] MovieTitleIndex.GetDocumentSet
[       OK ] MovieTitleIndex.GetDocumentSet (12 ms)
[----------] 2 tests from MovieTitleIndex (25 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 5 test cases ran. (252 ms total)
[  PASSED  ] 8 tests.
==31523== 
==31523== HEAP SUMMARY:
==31523==     in use at exit: 0 bytes in 0 blocks
==31523==   total heap usage: 4,638 allocs, 4,638 frees, 472,292 bytes allocated
==31523== 
==31523== All heap blocks were freed -- no leaks are possible
==31523== 
==31523== For counts of detected and suppressed errors, rerun with: -v
==31523== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
valgrind ./main data_small/
```
```==31707== Memcheck, a memory error detector
==31707== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==31707== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==31707== Command: ./main data_small/
==31707== 
Crawling directory tree starting at: data_small/
Crawled 24 files.
Parsing and indexing files...
20062 entries in the index.

Enter a term to search for, or q to quit: seattle

Getting docs for movieset term: "seattle"
indexType: tvEpisode
7 items
	Seattle Seahawks: Road to 2008
	St. Louis Cardinals vs. Seattle Seahawks
	Seattle
	Denver Broncos vs. Seattle Seahawks
	Seattle Seahawks vs. Dallas Cowboys
	Seattle Seahawks vs. Los Angeles Raiders
	Wasted in Seattle

Enter a term to search for, or q to quit: seattle

Getting docs for movieset term: "seattle"
indexType: tvEpisode
7 items
	Seattle Seahawks: Road to 2008
	St. Louis Cardinals vs. Seattle Seahawks
	Seattle
	Denver Broncos vs. Seattle Seahawks
	Seattle Seahawks vs. Dallas Cowboys
	Seattle Seahawks vs. Los Angeles Raiders
	Wasted in Seattle

Enter a term to search for, or q to quit: louis

Getting docs for movieset term: "louis"
indexType: tvMiniSeries
1 items
	The African Americans: Many Rivers to Cross with Henry Louis Gates, Jr
indexType: tvEpisode
7 items
	Hollywood USA: Louis Malle
	Arizona Cardinals vs. St. Louis Rams
	St. Louis Cardinals vs. Seattle Seahawks
	St. Louis Rams: Road to 2008
	St. Louis Cardinals vs. Los Angeles Rams
	New Orleans Saints vs. St. Louis Cardinals
	St. Louis Cardinals vs. Milwaukee Brewers

Enter a term to search for, or q to quit: q
Thanks for playing! 
==31707== 
==31707== HEAP SUMMARY:
==31707==     in use at exit: 0 bytes in 0 blocks
==31707==   total heap usage: 1,141,133 allocs, 1,141,133 frees, 66,010,721 bytes allocated
==31707== 
==31707== All heap blocks were freed -- no leaks are possible
==31707== 
==31707== For counts of detected and suppressed errors, rerun with: -v
==31707== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
