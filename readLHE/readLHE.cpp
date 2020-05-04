/*
c++ -o readLHE `root-config --cflags --glibs --cxx`  -lm  LHEF.cc readLHE.cpp
*/

#include <iomanip>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <algorithm>

#include "TLorentzVector.h"

#include "LHEF.h"

using namespace std ;


TLorentzVector buildLP (LHEF::Reader & reader, int iPart)
{
  TLorentzVector tlv
    (
      reader.hepeup.PUP.at (iPart).at (0), //PG px
      reader.hepeup.PUP.at (iPart).at (1), //PG py
      reader.hepeup.PUP.at (iPart).at (2), //PG pz
      reader.hepeup.PUP.at (iPart).at (3)  //PG E
    ) ;
  return tlv ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


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

  std::ifstream ifs (LHEfile.c_str ()) ;
  LHEF::Reader reader (ifs) ;

  int events = 0 ;
   
  // loop over input events
  while (reader.readEvent ()) 
    {
      if (events++ % 10000 == 0) cout << "        reading event in file: " << events << endl ;
      
      // for each event, save the collection of particles as ROOT TLorentzVectors    
      vector<TLorentzVector> v_f_quarks ;
      vector<TLorentzVector> v_f_leptons ;
      vector<TLorentzVector> v_f_neutrinos ;

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

      cout << "found " << reader.hepeup.IDUP.size () << " particles, "
           << v_f_quarks.size () << " outgoing quarks, "
           << v_f_leptons.size () << " outgoing charged leptons, "
           << v_f_neutrinos.size () << " outgoing neutrinos\n" ;

      // check maximum number of events
      if (maxEvents > 0 && maxEvents < events) 
        {
          cout << maxEvents << " events reached, exiting" << endl ;
          break ;
        }
    } //PG loop over input events

  return 0 ;

}