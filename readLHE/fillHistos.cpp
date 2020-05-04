/*
c++ -o fillHistos `root-config --cflags --glibs --cxx`  -lm  LHEF.cc fillHistos.cpp
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


#include <Math/GenVector/LorentzVector.h>
#include <Math/Vector4D.h>
#include "TH1F.h"
#include "TCanvas.h"

#include "LHEF.h"

using namespace std ;
using namespace ROOT::Math ;



XYZTVector buildLV (LHEF::Reader & reader, int iPart)
{
  XYZTVector lv
    (
      reader.hepeup.PUP.at (iPart).at (0), //PG px
      reader.hepeup.PUP.at (iPart).at (1), //PG py
      reader.hepeup.PUP.at (iPart).at (2), //PG pz
      reader.hepeup.PUP.at (iPart).at (3)  //PG E
    ) ;
  return lv ;
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

  TH1F h_minv ("h_minv", "", 100, 10., 120.) ;
   
  // loop over input events
  while (reader.readEvent ()) 
    {
      if (events++ % 10000 == 0) cout << "        reading event in file: " << events << endl ;
      
      // for each event, save the collection of particles as ROOT XYZTVectors    
      vector<XYZTVector> v_f_quarks ;
      vector<XYZTVector> v_f_leptons ;
      vector<XYZTVector> v_f_neutrinos ;

      // loop over particles in the event
      for (int iPart = 0 ; iPart < reader.hepeup.IDUP.size (); ++iPart) 
        {
          // outgoing particles          
          if (reader.hepeup.ISTUP.at (iPart) == 1)
            {
              XYZTVector dummy = buildLV (reader, iPart) ;

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

      // check that there's exactly two charged leptons
      if (v_f_leptons.size () != 2) continue ;

      float eventWeight = reader.hepeup.XWGTUP ;

      XYZTVector resonance = v_f_leptons.at (0) + v_f_leptons.at (1) ;
      h_minv.Fill (resonance.M (), eventWeight) ; 

      // check maximum number of events
      if (maxEvents > 0 && maxEvents < events) 
        {
          cout << maxEvents << " events reached, exiting" << endl ;
          break ;
        }
    } //PG loop over input events

  // draw the histogram

  TCanvas c1 ;
  h_minv.GetXaxis ()->SetTitle ("e+e- invariant mass (GeV)") ;
  h_minv.SetFillColor (kOrange + 1) ;
  h_minv.Draw ("hist") ;
  c1.Print ("minv.png", "png") ;

  return 0 ;

}