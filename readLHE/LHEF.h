// -*- C++ -*-
#ifndef THEPEG_LHEF_H
#define THEPEG_LHEF_H
//
// This is the declaration of the Les Houches Event File classes,
// implementing a simple C++ parser/writer for Les Houches Event files.
// Copyright (C) 2009-2013 Leif Lonnblad
//
// The code is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <limits>

namespace LHEF {

/**
 * Helper struct for output of attributes.
 */
template <typename T>
struct OAttr {

  /**
   * Constructor
   */
  OAttr(std::string n, const T & v): name(n), val(v) {}

  /**
   * The name of the attribute being printed.
   */
  std::string name;

  /**
   * The value of the attribute being printed.
   */
  T val;

};

/**
 * Output manipulator for writing attributes.
 */
template <typename T>
OAttr<T> oattr(std::string name, const T & value) {
  return OAttr<T>(name, value);
}

/**
 * Output operator for attributes.
 */
template <typename T>
std::ostream & operator<<(std::ostream & os, const OAttr<T> & oa) {
  os << " " << oa.name << "=\"" << oa.val << "\"";
  return os;
}

/**
 * The XMLTag struct is used to represent all information within an
 * XML tag. It contains the attributes as a map, any sub-tags as a
 * vector of pointers to other XMLTag objects, and any other
 * information as a single string.
 */
struct XMLTag {

  /**
   * Convenient typdef.
   */
  typedef std::string::size_type pos_t;

  /**
   * Convenient typdef.
   */
  typedef std::map<std::string,std::string> AttributeMap;

  /**
   * Convenient alias for npos.
   */
  static const pos_t end = std::string::npos;
  
  /**
   * Default constructor.
   */
  XMLTag() ;

  /**
   * The destructor also destroys any sub-tags.
   */
  ~XMLTag() ;

  /**
   * The name of this tag.
   */
  std::string name;

  /**
   * The attributes of this tag.
   */
  AttributeMap attr;

  /**
   * A vector of sub-tags.
   */
  std::vector<XMLTag*> tags;

  /**
   * The contents of this tag.
   */
  std::string contents;

  /**
   * Find an attribute named \a n and set the double variable \a v to
   * the corresponding value. @return false if no attribute was found.
   */
  bool getattr(std::string n, double & v) const ;
  /**
   * Find an attribute named \a n and set the bool variable \a v to
   * true if the corresponding value is "yes". @return false if no
   * attribute was found.
   */
  bool getattr(std::string n, bool & v) const ;
  /**
   * Find an attribute named \a n and set the long variable \a v to
   * the corresponding value. @return false if no attribute was found.
   */
  bool getattr(std::string n, long & v) const ;
  /**
   * Find an attribute named \a n and set the long variable \a v to
   * the corresponding value. @return false if no attribute was found.
   */
  bool getattr(std::string n, int & v) const ;
  /**
   * Find an attribute named \a n and set the string variable \a v to
   * the corresponding value. @return false if no attribute was found.
   */
  bool getattr(std::string n, std::string & v) const ;
  /**
   * Scan the given string and return all XML tags found as a vector
   * of pointers to XMLTag objects. Text which does not belong to any
   * tag is stored in tags without name and in the string pointed to
   * by leftover (if not null).
   */
  static std::vector<XMLTag*> 
  findXMLTags(std::string str, std::string * leftover = 0) ;
  /**
   * Delete all tags in a vector.
   */
  static void deleteAll(std::vector<XMLTag*> & tags) ;
  /**
   * Print out this tag to a stream.
   */
  void print(std::ostream & os) const ;

};

/**
 * Helper function to make sure that each line in the string \a s starts with a
 * #-character and that the string ends with a new-line.
 */
std::string hashline(std::string s) ;

/**
 * This is the base class of all classes representing xml tags.
 */
struct TagBase {

  /**
   * Convenient typedef.
   */
  typedef XMLTag::AttributeMap AttributeMap;

  /**
   * Default constructor does nothing.
   */
  TagBase() ;

  /**
   * Main constructor stores the attributes and contents of a tag.
   */
  TagBase(const AttributeMap & attr, std::string conts = std::string()) ;
 
  /**
   * Find an attribute named \a n and set the double variable \a v to
   * the corresponding value. Remove the correspondig attribute from
   * the list if found and \a erase is true. @return false if no
   * attribute was found.
   */
  bool getattr(std::string n, double & v, bool erase = true) ;

  /**
   * Find an attribute named \a n and set the bool variable \a v to
   * true if the corresponding value is "yes". Remove the correspondig
   * attribute from the list if found and \a erase is true. @return
   * false if no attribute was found.
   */
  bool getattr(std::string n, bool & v, bool erase = true) ;

  /**
   * Find an attribute named \a n and set the long variable \a v to
   * the corresponding value. Remove the correspondig attribute from
   * the list if found and \a erase is true. @return false if no
   * attribute was found.
   */
  bool getattr(std::string n, long & v, bool erase = true) ;

  /**
   * Find an attribute named \a n and set the long variable \a v to
   * the corresponding value. Remove the correspondig attribute from
   * the list if found and \a erase is true. @return false if no
   * attribute was found.
   */
  bool getattr(std::string n, int & v, bool erase = true) ;

  /**
   * Find an attribute named \a n and set the string variable \a v to
   * the corresponding value. Remove the correspondig attribute from
   * the list if found and \a erase is true. @return false if no
   * attribute was found.
   */
  bool getattr(std::string n, std::string & v, bool erase = true) ;

  /**
   * print out ' name="value"' for all unparsed attributes.
   */
  void printattrs(std::ostream & file) const ;

  /**
   * Print out end of tag marker. Print contents if not empty else
   * print simple close tag.
   */
  void closetag(std::ostream & file, std::string tag) const ;

  /**
   * The attributes of this tag;
   */
  XMLTag::AttributeMap attributes;

  /**
   * The contents of this tag.
   */
  std::string contents;

  /**
   * Static string token for truth values.
   */
  static const std::string yes;

};


/**
 * The Generator class contains information about a generator used in a run.
 */
struct Generator : public TagBase {

  /**
   * Construct from XML tag.
   */
  Generator(const XMLTag & tag) ;

  /**
   * Print the object as a generator tag.
   */
  void print(std::ostream & file) const ;

  /**
   * The name of the generator.
   */
  std::string name;

  /**
   * The version of the generator.
   */
  std::string version;

};

/**
 * The XSecInfo class contains information given in the xsecinfo tag.
 */
struct XSecInfo : public TagBase {

  /**
   * Intitialize default values.
   */
  XSecInfo() ;

  /**
   * Create from XML tag
   */
  XSecInfo(const XMLTag & tag) ;

  /**
   * Print out an XML tag.
   */
  void print(std::ostream & file) const ;

  /**
   * The number of events.
   */
  long neve;

  /**
   * The total cross section in pb.
   */
  double totxsec;

  /**
   * The maximum weight.
   */
  double maxweight;

  /**
   * The average weight.
   */
  double meanweight;

  /**
   * Does the file contain negative weights?
   */
  bool negweights;

  /**
   * Does the file contain varying weights?
   */
  bool varweights;


};

/**
 * The Cut class represents a cut used by the Matrix Element generator.
 */
struct Cut : public TagBase {

  /**
   * Intitialize default values.
   */
  Cut() ;

  /**
   * Create from XML tag.
   */
  Cut(const XMLTag & tag,
      const std::map<std::string,std::set<long> >& ptypes) ;

  /**
   * Print out an XML tag.
   */
  void print(std::ostream & file) const ;

  /**
   * Check if a \a id1 matches p1 and \a id2 matches p2. Only non-zero
   * values are considered.
   */
  bool match(long id1, long id2 = 0) const ;

  /**
   * Check if the particles given as a vector of PDG \a id numbers,
   * and a vector of vectors of momentum components, \a p, will pass
   * the cut defined in this event.
   */
  bool passCuts(const std::vector<long> & id,
		const std::vector< std::vector<double> >& p ) const ;

  /**
   * Return the pseudorapidity of a particle with momentum \a p.
   */
  static double eta(const std::vector<double> & p) ;

  /**
   * Return the true rapidity of a particle with momentum \a p.
   */
  static double rap(const std::vector<double> & p) ;

  /**
   * Return the delta-R of a particle pair with momenta \a p1 and \a p2.
   */
  static double deltaR(const std::vector<double> & p1,
		       const std::vector<double> & p2) ;

  /**
   * Return true if the given \a value is outside limits.
   */
  bool outside(double value) const ;

  /**
   * The variable in which to cut.
   */
  std::string type;

  /**
   * The first types particle types for which this cut applies.
   */
  std::set<long> p1;

  /**
   * Symbolic name for p1.
   */
  std::string np1;

  /**
   * The second type of particles for which this cut applies.
   */
  std::set<long> p2;

  /**
   * Symbolic name for p1.
   */
  std::string np2;

  /**
   * The minimum value of the variable
   */
  double min;
  /**
   * The maximum value of the variable
   */
  double max;

};

/**
 * The ProcInfo class represents the information in a procinfo tag.
 */
struct ProcInfo : public TagBase {

  /**
   * Intitialize default values.
   */
  ProcInfo() ;

  /**
   * Create from XML tag.
   */
  ProcInfo(const XMLTag & tag) ;

  /**
   * Print out an XML tag.
   */
  void print(std::ostream & file) const ;

  /**
   * The id number for the process.
   */
  int iproc;

  /**
   * The number of loops
   */
  int loops;

  /**
   * The number of QCD vertices.
   */
  int qcdorder;

  /**
   * The number of electro-weak vertices.
   */
  int eworder;

  /**
   * The factorization scheme used.
   */
  std::string fscheme;

  /**
   * The renormalization scheme used.
   */
  std::string rscheme;

  /**
   * The NLO scheme used.
   */
  std::string scheme;

};

/**
 * The MergeInfo class represents the information in a mergeinfo tag.
 */
struct MergeInfo : public TagBase {

  /**
   * Intitialize default values.
   */
  MergeInfo() ;

  /**
   * Creat from XML tag.
   */
  MergeInfo(const XMLTag & tag) ;

  /**
   * Print out an XML tag.
   */
  void print(std::ostream & file) const ;

  /**
   * The id number for the process.
   */
  int iproc;

  /**
   * The merging scale used if different from the cut definitions.
   */
  double mergingscale;

  /**
   * Is this event reweighted as if it was the maximum multiplicity.
   */
  bool maxmult;

};

/**
 * The WeightInfo class encodes the description of a given weight
 * present for all events.
 */
struct WeightInfo : public TagBase {

  /**
   * Constructors
   */
  WeightInfo() ;

  /**
   * Construct from the XML tag
   */
  WeightInfo(const XMLTag & tag) ;

  /**
   * Print out an XML tag.
   */
  void print(std::ostream & file) const ;

  /**
   * If inside a group, this is the index of that group.
   */
  int inGroup;

  /**
   * Is this a weightinfo or an rwgt tag?
   */
  bool isrwgt;

  /**
   * The name.
   */
  std::string name;

  /**
   * Factor multiplying the nominal factorization scale for this weight.
   */
  double muf;

  /**
   * Factor multiplying the nominal renormalization scale for this weight.
   */
  double mur;

  /**
   * The LHAPDF set relevant for this weight
   */
  long pdf;

  /**
   * The LHAPDF set for the second beam relevant for this weight if
   * different from pdf.
   */
  long pdf2;

};

/**
 * The WeightGroup assigns a group-name to a set of WeightInfo objects.
 */
struct WeightGroup : public TagBase {

  /**
   * Default constructor;
   */
  WeightGroup() ;

  /**
   * Construct a group of WeightInfo objects from an XML tag and
   * insert them in the given vector.
   */
  WeightGroup(const XMLTag & tag, int groupIndex, std::vector<WeightInfo> & wiv) ;

  /**
   * The type.
   */
  std::string type;

  /**
   * The way in which these weights should be combined.
   */
  std::string combine;

};


/**
 * The Weight class represents the information in a weight tag.
 */
struct Weight : public TagBase {

  /**
   * Initialize default values.
   */
  Weight() ;

  /**
   * Create from XML tag
   */
  Weight(const XMLTag & tag) ;

  /**
   * Print out an XML tag.
   */
  void print(std::ostream & file) const ;

  /**
   * The identifyer for this set of weights.
   */
  std::string name;

  /**
   * Is this a wgt or a weight tag
   */
  bool iswgt;

  /**
   * The relative size of the born cross section of this event.
   */
  double born;

  /**
   * The relative size of the sudakov applied to this event.
   */
  double sudakov;

  /**
   * The weights of this event.
   */
  mutable std::vector<double> weights;

  /**
   * The indices where the weights are stored.
   */
  std::vector<int> indices;

};

/**
 * The Clus class represents a clustering of two particle entries into
 * one as defined in a clustering tag.
 */
struct Clus : public TagBase {

  /**
   * Initialize default values.
   */
  Clus() ;

  /**
   * Initialize default values.
   */
  Clus(const XMLTag & tag) ;

  /**
   * Print out an XML tag.
   */
  void print(std::ostream & file) const ;

  /**
   * The first particle entry that has been clustered.
   */
  int p1;

  /**
   * The second particle entry that has been clustered.
   */
  int p2;

  /**
   * The particle entry corresponding to the clustered particles.
   */
  int p0;

  /**
   * The scale in GeV associated with the clustering.
   */
  double scale;

  /**
   * The alpha_s used in the corresponding vertex, if this was used in
   * the cross section.
   */
  double alphas;

};

/**
 * Collect different scales relevant for an event.
 */
struct Scales : public TagBase {

  /**
   * Empty constructor.
   */
  Scales(double defscale = -1.0) ;

  /**
   * Construct from an XML-tag
   */
  Scales(const XMLTag & tag, double defscale = -1.0) ;

  /**
   * Print out the corresponding XML-tag.
   */
  void print(std::ostream & file) const ;

  /**
   * The factorization scale used for this event.
   */
  double muf;

  /**
   * The renormalization scale used for this event.
   */
  double mur;

  /**
   * The starting scale for the parton shower as suggested by the
   * matrix element generator.
   */
  double mups;

  /**
   * The default scale in this event.
   */
  double SCALUP;

};

/**
 * The PDFInfo class represents the information in a pdfinto tag.
 */
struct PDFInfo : public TagBase {

  /**
   * Initialize default values.
   */
  PDFInfo(double defscale = -1.0) ;

  /**
   * Create from XML tag.
   */
  PDFInfo(const XMLTag & tag, double defscale = -1.0) ;

  /**
   * Print out an XML tag.
   */
  void print(std::ostream & file) const ;

  /**
   * The type of the incoming particle 1.
   */
  long p1;

  /**
   * The type of the incoming particle 2.
   */
  long p2;

  /**
   * The x-value used for the incoming particle 1.
   */
  double x1;

  /**
   * The x-value used for the incoming particle 2.
   */
  double x2;

  /**
   * The value of the pdf for the incoming particle 1.
   */
  double xf1;

  /**
   * The value of the pdf for the incoming particle 2.
   */
  double xf2;

  /**
   * The scale used in the PDF:s
   */
  double scale;

  /**
   * THe default scale in the event.
   */
  double SCALUP;

};

/**
 * The HEPRUP class is a simple container corresponding to the Les Houches
 * accord (<A HREF="http://arxiv.org/abs/hep-ph/0109068">hep-ph/0109068</A>)
 * common block with the same name. The members are named in the same
 * way as in the common block. However, fortran arrays are represented
 * by vectors, except for the arrays of length two which are
 * represented by pair objects.
 */
class HEPRUP : public TagBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  HEPRUP() ;

  /**
   * Assignment operator.
   */
  HEPRUP & operator=(const HEPRUP & x) ;

  /**
   * Construct from a given init tag.
   */
  HEPRUP(const XMLTag & tag, int versin) ;

  /**
   * Destructor.
   */
  ~HEPRUP() ;
  //@}

public:


  /**
   * Print out the corresponding XML tag to a stream.
   */
  void print(std::ostream & file) const ;

  /**
   * Clear all information. 
   */
  void clear() ;

  /**
   * Set the NPRUP variable, corresponding to the number of
   * sub-processes, to \a nrup, and resize all relevant vectors
   * accordingly.
   */
  void resize(int nrup) ;

  /**
   * Assuming the NPRUP variable, corresponding to the number of
   * sub-processes, is correctly set, resize the relevant vectors
   * accordingly.
   */
  void resize() ;

  /**
   * @return the index of the weight with the given \a name
   */
  int weightIndex(std::string name) const ;

  /**
   * @return the number of weights (including the nominial one).
   */
  int nWeights() const ;

public:

  /**
   * PDG id's of beam particles. (first/second is in +/-z direction).
   */
  std::pair<long,long> IDBMUP;

  /**
   * Energy of beam particles given in GeV.
   */
  std::pair<double,double> EBMUP;

  /**
   * The author group for the PDF used for the beams according to the
   * PDFLib specification.
   */
  std::pair<int,int> PDFGUP;

  /**
   * The id number the PDF used for the beams according to the
   * PDFLib specification.
   */
  std::pair<int,int> PDFSUP;

  /**
   * Master switch indicating how the ME generator envisages the
   * events weights should be interpreted according to the Les Houches
   * accord.
   */
  int IDWTUP;

  /**
   * The number of different subprocesses in this file.
   */
  int NPRUP;

  /**
   * The cross sections for the different subprocesses in pb.
   */
  std::vector<double> XSECUP;

  /**
   * The statistical error in the cross sections for the different
   * subprocesses in pb.
   */
  std::vector<double> XERRUP;

  /**
   * The maximum event weights (in HEPEUP::XWGTUP) for different
   * subprocesses.
   */
  std::vector<double> XMAXUP;

  /**
   * The subprocess code for the different subprocesses.
   */
  std::vector<int> LPRUP;

  /**
   * Contents of the xsecinfo tag
   */
  XSecInfo xsecinfo;

  /**
   * Contents of the cuts tag.
   */
  std::vector<Cut> cuts;

  /**
   * A map of codes for different particle types.
   */
  std::map<std::string, std::set<long> > ptypes;

  /**
   * Contents of the procinfo tags
   */
  std::map<long,ProcInfo> procinfo;

  /**
   * Contents of the mergeinfo tags
   */
  std::map<long,MergeInfo> mergeinfo;

  /**
   * The names of the programs and their version information used to
   * create this file.
   */
  std::vector<Generator> generators;

  /**
   * The vector of WeightInfo objects for this file.
   */
  std::vector<WeightInfo> weightinfo;

  /**
   * A map relating names of weights to indices of the weightinfo vector.
   */
  std::map<std::string,int> weightmap;

  /**
   * The vector of WeightGroup objects in this file.
   */
  std::vector<WeightGroup> weightgroup;

  /**
   * Just to be on the safe side we save any junk inside the init-tag.
   */
  std::string junk;

  /**
   * The main version of the information stored.
   */
  int version;

};

/**
 * Forward declaration of the HEPEUP class.
 */
class HEPEUP;

/**
 * The EventGroup represents a set of events which are to be
 * considered together.
 */
struct EventGroup: public std::vector<HEPEUP*> {

  /**
   * Initialize default values.
   */
  EventGroup() ;

  /**
   * The copy constructor also copies the included HEPEUP object.
   */
  EventGroup(const EventGroup &) ;

  /**
   * The assignment also copies the included HEPEUP object.
   */
  EventGroup & operator=(const EventGroup &) ;

  /**
   * Remove all subevents.
   */
  void clear() ;

  /**
   * The destructor deletes the included HEPEUP objects.
   */
  ~EventGroup() ;

  /**
   * The number of real events in this event group.
   */
  int nreal;

  /**
   * The number of counter events in this event group.
   */
  int ncounter;

};


/**
 * The HEPEUP class is a simple container corresponding to the Les Houches accord
 * (<A HREF="http://arxiv.org/abs/hep-ph/0109068">hep-ph/0109068</A>)
 * common block with the same name. The members are named in the same
 * way as in the common block. However, fortran arrays are represented
 * by vectors, except for the arrays of length two which are
 * represented by pair objects.
 */
class HEPEUP : public TagBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  HEPEUP() ;

  /**
   * Copy constructor
   */
  HEPEUP(const HEPEUP & x) ;

  /**
   * Copy information from the given HEPEUP. Sub event information is
   * left untouched.
   */
  HEPEUP & setEvent(const HEPEUP & x) ;

  /**
   * Assignment operator.
   */
  HEPEUP & operator=(const HEPEUP & x) ;

  /**
   * Destructor.
   */
  ~HEPEUP() ;
  //@}

public:

  /**
   * Constructor from an event or eventgroup tag.
   */
  HEPEUP(const XMLTag & tag, HEPRUP & heprupin) ;

  /**
   * Print out the event (group) as an XML tag.
   */
  void print(std::ostream & file) const ;

  /**
   * Reset the HEPEUP object (does not touch the sub events).
   */
  void reset() ;

  /**
   * Clear the HEPEUP object.
   */
  void clear() ;

  /**
   * Set the NUP variable, corresponding to the number of particles in
   * the current event, to \a nup, and resize all relevant vectors
   * accordingly.
   */
  void resize(int nup) ;

  /**
   * Return the total weight for this event (including all sub
   * evenets) for the given index.
   */
  double totalWeight(int i = 0) const ;

  /**
   * Return the total weight for this event (including all sub
   * evenets) for the given weight name.
   */
  double totalWeight(std::string name) const ;

  /**
   * Return the weight for the given index.
   */
  double weight(int i = 0) const ;

  /**
   * Return the weight for the given weight name.
   */
  double weight(std::string name) const ;

  /**
   * Set the weight with the given index.
   */
  void setWeight(int i, double w) ;

  /**
   * Set the weight with the given name.
   */
  bool setWeight(std::string name, double w) ;

  /**
   * Assuming the NUP variable, corresponding to the number of
   * particles in the current event, is correctly set, resize the
   * relevant vectors accordingly.
   */
  void resize() ;

  /**
   * Setup the current event to use weight i. If zero, the default
   * weight will be used.
   */
  bool setWeightInfo(unsigned int i) ;

  /**
   * Setup the current event to use sub event i. If zero, no sub event
   * will be chsen.
   */
  bool setSubEvent(unsigned int i) ;

public:

  /**
   * The number of particle entries in the current event.
   */
  int NUP;

  /**
   * The subprocess code for this event (as given in LPRUP).
   */
  int IDPRUP;

  /**
   * The weight for this event.
   */
  double XWGTUP;

  /**
   * The PDF weights for the two incoming partons. Note that this
   * variable is not present in the current LesHouches accord
   * (<A HREF="http://arxiv.org/abs/hep-ph/0109068">hep-ph/0109068</A>),
   * hopefully it will be present in a future accord.
   */
  std::pair<double,double> XPDWUP;

  /**
   * The scale in GeV used in the calculation of the PDF's in this
   * event.
   */
  double SCALUP;

  /**
   * The value of the QED coupling used in this event.
   */
  double AQEDUP;

  /**
   * The value of the QCD coupling used in this event.
   */
  double AQCDUP;

  /**
   * The PDG id's for the particle entries in this event.
   */
  std::vector<long> IDUP;

  /**
   * The status codes for the particle entries in this event.
   */
  std::vector<int> ISTUP;

  /**
   * Indices for the first and last mother for the particle entries in
   * this event.
   */
  std::vector< std::pair<int,int> > MOTHUP;

  /**
   * The colour-line indices (first(second) is (anti)colour) for the
   * particle entries in this event.
   */
  std::vector< std::pair<int,int> > ICOLUP;

  /**
   * Lab frame momentum (Px, Py, Pz, E and M in GeV) for the particle
   * entries in this event.
   */
  std::vector< std::vector<double> > PUP;

  /**
   * Invariant lifetime (c*tau, distance from production to decay in
   * mm) for the particle entries in this event.
   */
  std::vector<double> VTIMUP;

  /**
   * Spin info for the particle entries in this event given as the
   * cosine of the angle between the spin vector of a particle and the
   * 3-momentum of the decaying particle, specified in the lab frame.
   */
  std::vector<double> SPINUP;

  /**
   * A pointer to the current HEPRUP object.
   */
  HEPRUP * heprup;

  /**
   * The current weight info object.
   */
  const WeightInfo * currentWeight;

  /**
   * The weights associated with this event
   */
  std::vector<Weight> namedweights;

  /**
   * The weights for this event and their corresponding WeightInfo object.
   */
  std::vector< std::pair<double, const WeightInfo *> > weights;

  /**
   * Contents of the clustering tag.
   */
  std::vector<Clus> clustering;

  /**
   * Contents of the pdfinfo tag.
   */
  PDFInfo pdfinfo;

  /**
   * Saved information about pdfs if different in a selected weight.
   */
  std::pair<int,int> PDFGUPsave;

  /**
   * Saved information about pdfs if different in a selected weight.
   */
  std::pair<int,int> PDFSUPsave;
  

  /**
   * Contents of the scales tag
   */
  Scales scales;

  /**
   * Is this an event or an event group?
   */
  bool isGroup;

  /**
   * If this is not a single event, but an event group, the events
   * included in the group are in this vector;
   */
  EventGroup subevents;

  /**
   * Save junk stuff in events just to be on the safe side
   */
  std::string junk;

};


/**
 * The Reader class is initialized with a stream from which to read a
 * version 1/2 Les Houches Accord event file. In the constructor of
 * the Reader object the optional header information is read and then
 * the mandatory init is read. After this the whole header block
 * including the enclosing lines with tags are available in the public
 * headerBlock member variable. Also the information from the init
 * block is available in the heprup member variable and any additional
 * comment lines are available in initComments. After each successful
 * call to the readEvent() function the standard Les Houches Accord
 * information about the event is available in the hepeup member
 * variable and any additional comments in the eventComments
 * variable. A typical reading sequence would look as follows:
 *
 *
 */
class Reader {

public:

  /**
   * Initialize the Reader with a stream from which to read an event
   * file. After the constructor is called the whole header block
   * including the enclosing lines with tags are available in the
   * public headerBlock member variable. Also the information from the
   * init block is available in the heprup member variable and any
   * additional comment lines are available in initComments.
   *
   * @param is the stream to read from.
   */
  Reader(std::istream & is) ;

  /**
   * Initialize the Reader with a filename from which to read an event
   * file. After the constructor is called the whole header block
   * including the enclosing lines with tags are available in the
   * public headerBlock member variable. Also the information from the
   * init block is available in the heprup member variable and any
   * additional comment lines are available in initComments.
   *
   * @param filename the name of the file to read from.
   */
  Reader(std::string filename) ;

private:

  /**
   * Used internally in the constructors to read header and init
   * blocks.
   */
  void init() ;

public:

  /**
   * Read an event from the file and store it in the hepeup
   * object. Optional comment lines are stored i the eventComments
   * member variable.
   * @return true if the read sas successful.
   */
  bool readEvent() ;

protected:

  /**
   * Used internally to read a single line from the stream.
   */
  bool getline() ;

  /**
   * @return true if the current line contains the given string.
   */
  bool currentFind(std::string str) const ;

protected:

  /**
   * A local stream which is unused if a stream is supplied from the
   * outside.
   */
  std::ifstream intstream;

  /**
   * The stream we are reading from. This may be a reference to an
   * external stream or the internal intstream.
   */
  std::istream & file;

  /**
   * The last line read in from the stream in getline().
   */
  std::string currentLine;

public:

  /**
   * XML file version
   */
  int version;

  /**
   * All lines (since the last readEvent()) outside the header, init
   * and event tags.
   */
  std::string outsideBlock;

  /**
   * All lines from the header block.
   */
  std::string headerBlock;

  /**
   * The standard init information.
   */
  HEPRUP heprup;

  /**
   * Additional comments found in the init block.
   */
  std::string initComments;

  /**
   * The standard information about the last read event.
   */
  HEPEUP hepeup;

  /**
   * Additional comments found with the last read event.
   */
  std::string eventComments;

private:

  /**
   * The default constructor should never be used.
   */
  Reader();

  /**
   * The copy constructor should never be used.
   */
  Reader(const Reader &);

  /**
   * The Reader cannot be assigned to.
   */
  Reader & operator=(const Reader &);

};

/**
 * The Writer class is initialized with a stream to which to write a
 * version 1.0 Les Houches Accord event file. In the constructor of
 * the Writer object the main XML tag is written out, with the
 * corresponding end tag is written in the destructor. After a Writer
 * object has been created, it is possible to assign standard init
 * information in the heprup member variable. In addition any XML
 * formatted information can be added to the headerBlock member
 * variable (directly or via the addHeader() function). Further
 * comment line (beginning with a <code>#</code> character) can be
 * added to the initComments variable (directly or with the
 * addInitComment() function). After this information is set, it
 * should be written out to the file with the init() function.
 *
 * Before each event is written out with the writeEvent() function,
 * the standard event information can then be assigned to the hepeup
 * variable and optional comment lines (beginning with a
 * <code>#</code> character) may be given to the eventComments
 * variable (directly or with the addEventComment() function).
 *
 */
class Writer {

public:

  /**
   * Create a Writer object giving a stream to write to.
   * @param os the stream where the event file is written.
   */
  Writer(std::ostream & os) ;
 
  /**
   * Create a Writer object giving a filename to write to.
   * @param filename the name of the event file to be written.
   */
  Writer(std::string filename) ;

  /**
   * The destructor writes out the final XML end-tag.
   */
  ~Writer() ;

  /**
   * Add header lines consisting of XML code with this stream.
   */
  std::ostream & headerBlock() ;

  /**
   * Add comment lines to the init block with this stream.
   */
  std::ostream & initComments() ;

  /**
   * Add comment lines to the next event to be written out with this stream.
   */
  std::ostream & eventComments() ;

  /**
   * Write out an optional header block followed by the standard init
   * block information together with any comment lines.
   */
  void init() ;

  /**
   * Write the current HEPEUP object to the stream;
   */
  void writeEvent() ;

protected:

  /**
   * A local stream which is unused if a stream is supplied from the
   * outside.
   */
  std::ofstream intstream;

  /**
   * The stream we are writing to. This may be a reference to an
   * external stream or the internal intstream.
   */
  std::ostream & file;

public:

  /**
   * Stream to add all lines in the header block.
   */
  std::ostringstream headerStream;

  /**
   * The standard init information.
   */
  HEPRUP heprup;

  /**
   * Stream to add additional comments to be put in the init block.
   */
  std::ostringstream initStream;

  /**
   * The standard information about the event we will write next.
   */
  HEPEUP hepeup;

  /**
   * Stream to add additional comments to be written together the next event.
   */
  std::ostringstream eventStream;

private:

  /**
   * The default constructor should never be used.
   */
  Writer();

  /**
   * The copy constructor should never be used.
   */
  Writer(const Writer &);

  /**
   * The Writer cannot be assigned to.
   */
  Writer & operator=(const Writer &);

};

}

/** \example LHEFCat.cc This is a main function which simply reads a
    Les Houches Event File from the standard input and writes it again
    to the standard output. 
    This file can be downloaded from
    <A HREF="http://www.thep.lu.se/~leif/LHEF/LHEFCat.cc">here</A>. 
    There are also two sample event files,
    <A HREF="http://www.thep.lu.se/~leif/LHEF/ttV_unweighted_events.lhe">ttV_unweighted_events.lhe</A> and <A HREF="http://www.thep.lu.se/~leif/LHEF/testlhef3.lhe">testlhef3.lhe</A>
    to try it on.
*/

/**\mainpage Les Houches Event File

Here are some example classes for reading and writing Les Houches
Event Files according to the
<A HREF="http://www.thep.lu.se/~torbjorn/lhef/lhafile2.pdf">proposal</A>
by Torbj&ouml;rn Sj&ouml;strand discussed at the
<A HREF="http://mc4lhc06.web.cern.ch/mc4lhc06/">MC4LHC</A>
workshop at CERN 2006.

The classes has now been updated to handle the suggested version 3 of
this file standard as discussed at the <a href="http://phystev.in2p3.fr/wiki/2013:groups:tools:lhef3">Les Houches workshop 2013</a> (The previous suggested version 2.0 was discussed at the <a href="http://www.lpthe.jussieu.fr/LesHouches09Wiki/index.php/LHEF_for_Matching">Les Houches workshop 2009</a>).

There is a whole set of classes available in a single header file
called <A
HREF="http://www.thep.lu.se/~leif/LHEF/LHEF.h">LHEF.h</A>. The idea is
that matrix element or parton shower generators will implement their
own wrapper using these classes as containers.

The two classes LHEF::HEPRUP and LHEF::HEPEUP are simple container
classes which contain the same information as the Les Houches standard
Fortran common blocks with the same names. They also contain the extra
information defined in version 3 in the standard. The other two main
classes are called LHEF::Reader and LHEF::Writer and are used to read
and write Les Houches Event Files

Here are a few <A HREF="examples.html">examples</A> of how to use the
classes:

\namespace LHEF The LHEF namespace contains some example classes for reading and writing Les Houches
Event Files according to the
<A HREF="http://www.thep.lu.se/~torbjorn/lhef/lhafile2.pdf">proposal</A>
by Torbj&ouml;rn Sj&ouml;strand discussed at the
<A HREF="http://mc4lhc06.web.cern.ch/mc4lhc06/">MC4LHC</A>
workshop at CERN 2006.



 */


#endif /* THEPEG_LHEF_H */

