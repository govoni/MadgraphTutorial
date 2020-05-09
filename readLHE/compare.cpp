/*
c++ -o compare `root-config --cflags --glibs`  -lm  LHEF.cc compare.cpp
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
#include "TLegend.h"

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


void readFile (TH1F * h_minv, string LHEfile, int maxEvents = -1)
{

  cout << "reading " << LHEfile << endl ;
  std::ifstream ifs (LHEfile.c_str ()) ;
  LHEF::Reader reader (ifs) ;

  int events = 0 ;
   
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
      h_minv->Fill (resonance.M (), eventWeight) ; 

      // check maximum number of events
      if (maxEvents > 0 && maxEvents < events) 
        {
          cout << maxEvents << " events reached, exiting" << endl ;
          break ;
        }
    } //PG loop over input events

  ifs.close () ;

} 


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


int main (int argc, char ** argv) 
{

  // read input information from command line 
  // and prepare for processing
  // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 

  if (argc < 4)
    {
      cerr << "usage " << argv[0] << " LHEfile1 LHEfile2 LHEfile3" << endl ;
      return 1 ;
    }

  // read the input file names
  vector<string> LHEfiles ;
  for (int i = 1 ; i < 4 ; ++i) LHEfiles.push_back (argv[i]) ;

  // prepare the histograms
  vector<TH1F *> h_minv_v ;
  for (int i = 0 ; i < 3 ; ++i) 
    h_minv_v.push_back (
      new TH1F ( (string ("h_minv") + LHEfiles.at (i)).c_str (),
                 "", 100, 10., 120.)
     ) ;

  // read input files and fill histograms
  // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 

  for (int i = 0 ; i < 3 ; ++i) 
    readFile (h_minv_v.at (i), LHEfiles.at (i)) ;

  // draw the histograms
  // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 

  // find the histogram with the highest mode
  TH1F * max = h_minv_v.at (0) ;
  for (int i = 1 ; i < 3 ; ++i) 
    {
      if (h_minv_v.at (i)->GetBinContent (h_minv_v.at (i)->GetMaximumBin ()) > 
          max->GetBinContent (max->GetMaximumBin ()) ) 
        max = h_minv_v.at (i) ;

    }

  // prepare canvas and legend
  TCanvas c1 ;
  TLegend legend (0.10, 0.60, 0.70, 0.90) ;
  legend.SetBorderSize (0) ;
  legend.SetFillStyle (0) ;

  // draw the highest histogram with axis title
  max->GetXaxis ()->SetTitle ("e+e- invariant mass (GeV)") ;
  max->SetStats (0) ;
  max->Draw ("hist") ;

  // redraw all histograms with different colors
  // and add them to the legend
  for (int i = 0 ; i < 3 ; ++i) 
    {
      h_minv_v.at (i)->SetLineWidth (2) ;
      h_minv_v.at (i)->SetLineStyle (2 * i) ;
      h_minv_v.at (i)->SetLineColor (30 + 10*i) ;
      legend.AddEntry (h_minv_v.at (i), h_minv_v.at (i)->GetName (), "L") ;
      h_minv_v.at (i)->Draw ("hist same") ;
    }
  legend.Draw () ;
  c1.Print ("minv.png", "png") ;
  c1.Print ("minv.pdf", "pdf") ;

  return 0 ;

}