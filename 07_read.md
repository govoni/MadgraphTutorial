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

### 7.3.1 opening the LHE file

Read the filename as a shell argument,
checking that it's actually passed,
and set as optional argument the maximum number of events to be read:
```c
int main (int argc, char ** argv)
{

  if (argc < 2)
    {
      cerr << "usage " << argv[0] << " LHEfile [maxEvents]" << endl ;
      return 1 ;
    }

  string LHEfile = argv[1] ;
  cout << "reading " << LHEfile << endl ;

  int maxEvents = -1 ;
  if (argc > 2)
    {
      maxEvents = atoi (argv[2]) ;
    }
  cout << "reading " << maxEvents << " events" << endl ;
```
Open the LHE file,
create a on object of type ``LHEF::Reader`` to read it
and prepare a counter for the number of events:
```c
std::ifstream ifs (LHEfile.c_str ()) ;
LHEF::Reader reader (ifs) ;

int events = 0 ;
```
Start the loop over the events:
```c
// loop over input events
while (reader.readEvent ())
  {
```
### 7.3.2 read each event

Write something once in a while,
and prepare the containers
where to store the information for each particle read
(note that the ```event``` variable gets incremented here):
```c
if (events++ % 10000 == 0) cout << "        reading event in file: " << events << endl ;

// for each event, save the collection of particles as ROOT TLorentzVectors    
vector<TLorentzVector> v_f_quarks ;
vector<TLorentzVector> v_f_leptons ;
vector<TLorentzVector> v_f_neutrinos ;
```
Loop over all particles in the event,
look only at the outgoing ones
and fill the containers with the relevant information:
```c
// loop over particles in the event
for (int iPart = 0 ; iPart < reader.hepeup.IDUP.size (); ++iPart)
  {
    // outgoing particles          
    if (reader.hepeup.ISTUP.at (iPart) == 1)
      {
        TLorentzVector dummy = buildLP (reader, iPart) ;
        // quarks
        if (abs (reader.hepeup.IDUP.at (iPart)) < 7)
          {
            v_f_quarks.push_back (dummy) ;        
          } // quarks
        else if (abs (reader.hepeup.IDUP.at (iPart)) == 11 ||
                 abs (reader.hepeup.IDUP.at (iPart)) == 13 ||
                 abs (reader.hepeup.IDUP.at (iPart)) == 15)
          {
            v_f_leptons.push_back (dummy) ;
          }
        else if (abs (reader.hepeup.IDUP.at (iPart)) == 12 ||
                 abs (reader.hepeup.IDUP.at (iPart)) == 14 ||
                 abs (reader.hepeup.IDUP.at (iPart)) == 16)
          {
            v_f_neutrinos.push_back (dummy) ;        
          }
      } // outgoing particles
  } // loop over particles in the event
```
After the loop on the particles,
write some information for each event
(this is tedious when running over many events,
to be used only for debugging reasons)
```c
cout << "found " << reader.hepeup.IDUP.size () << " particles, "
     << v_f_quarks.size () << " outgoing quarks, "
     << v_f_leptons.size () << " outgoing charged leptons, "
     << v_f_neutrinos.size () << " outgoing neutrinos\n" ;
```
check whether the maximum number of events is reached:
```c
// check maximum number of events
if (maxEvents > 0 && maxEvents < events)
  {
    cout << maxEvents << " events reached, exiting" << endl ;
    break ;
  }
```

## 7.4 exercises

  * check that the number of electrons and positrons corresponds
    to the total number of events
  * count the fraction of times in which a Z boson in present in the event,
    for the production ```p p > e+ e-```
  * check whether the electron and positron are back-to-back in all the events  
  * replace the ROOT [TLorentzVector](https://root.cern.ch/doc/master/classTLorentzVector.html) class
    with the [ROOT::Math::LorentzVector ](https://root.cern.ch/doc/master/classROOT_1_1Math_1_1LorentzVector.html) template
