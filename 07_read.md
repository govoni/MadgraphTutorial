# 7. reading a LHE file

[**chapter six**](06_LHE.md)

## 7.1 reading library

  * There exist **libraries** written to read a LHE file
    without the need to develop a parser
  * The parser reads the ``<header>`` and ``<init>`` sections
    and makes the information available
  * reading of the events is **done in a loop**,
    so that for each event the same variables are filled,
    at each event with the values corresponding to that event
    * since the number of particles is unknown,
      the information is stored in arrays

## 7.2 typical reading process of a LHE file

### 7.2.1 beginning of the file reading

  * read the **initial information**
  * **prepare** all the counters and histograms to be filled while iterating
    over the events
    (remember that cross-sections are calculated by counting events)

### 7.2.2 loop over the events

  * for each event, read the **generic information** of the event
  * for each event, **loop over the particles** it contains,
    and extract the needed information
  * increment counters, **fill** histograms

### 7.2.3 after the loop over the events

  * **close** the input file
  * **post-process** all counters and histograms to obtain the pieces of
    information sought for

## 7.3 C++ library to read the events

An example of file reading can be found in the [readLHE](./readLHE) folder
  * the library to read the LHE files is [LHEF.h](./readLHE/LHEF.h)
  * the example file reading it is [readLHE.cpp](./readLHE/readLHE.cpp)
