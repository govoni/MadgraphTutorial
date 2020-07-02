# 11. generate a specific decay process

[**chapter ten**](10_specify.md)

## 11.1 the production of top quark pairs at the LHC

  * *top quark pairs* are abundantly produced at the Large Hadron Collider
    * a top quark, once produced, decays into a W boson and a b quark
    * the W boson then in turn disintegrates in a lepton-neutrino pair or in a quark pair
  * the production of a pair of undecayed top quarks is coded as follows:
```
generate p p > t t~
```

## 11.2 the particle decay syntax

  * instructions on how to use the ```generate``` instruction can be obtained
    from MG itself:
```
generate p p > t t~
```
  * this will produce an ouptut, where the section concerning the decay chains is the folliwng,
    where in particular the example for the top quark pairs is reported,
    for the semi-leptonic decay when the top quark decays leptonically, 
    while the anti-top decays hadronically:
```
./bin/mg5_aMC 
MG5_aMC>help generate
[...]
Decay chain syntax:
 o core process, decay1, (decay2, (decay2', ...)), ...  etc
 o Example: generate p p > t~ t QED=0, (t~ > W- b~, W- > l- vl~), t > j j b @2
 > Note that identical particles will all be decayed.
[...]
```  

## 11.2 the possible decay chains

### 11.2.1 the fully leptonic decay

  * assuming the multi-particle definitions of [Chapter 3](03_firstRun.md), 
    the *fully leptonic case* happens when the W bosons produced in both top and anti-top
    quark decays disintegrate into lepton-neutrino:
```
generate p p > t~ t, (t~ > W- b~, W- > l- vl~), (t > W+ b, W+ > l+ vl)
```
  * the generated decays can be inspected within MG:
```
MG5_aMC>display processes
Process: g g > t~ t WEIGHTED<=2 @1
Process: u u~ > t~ t WEIGHTED<=2 @1
Process: c c~ > t~ t WEIGHTED<=2 @1
Process: d d~ > t~ t WEIGHTED<=2 @1
Process: s s~ > t~ t WEIGHTED<=2 @1
Decays:
  Process: t~ > w- b~ WEIGHTED<=2
  Decays:
    Process: w- > e- ve~ WEIGHTED<=2
    Process: w- > mu- vm~ WEIGHTED<=2
  Process: t > w+ b WEIGHTED<=2
  Decays:
    Process: w+ > e+ ve WEIGHTED<=2
    Process: w+ > mu+ vm WEIGHTED<=2
```

### 11.2.2 the fully hadronic decay

  * still assuming the multi-particle definitions of [Chapter 3](03_firstRun.md), 
    the *fully hadronic case* happens when the W bosons produced in both top and anti-top
    quark decays disintegrate into quarks:
```
generate p p > t~ t, (t~ > W- b~, W- > j j), (t > W+ b, W+ > j j)
```

### 11.2.3 the semi-leptonic decay

  * always assuming the multi-particle definitions of [Chapter 3](03_firstRun.md), 
    the *semi-leptonic case* happens when one W boson produced in either the top or the anti-top
    quark decay disintegrates into a lepton-neutrino pair,
    while the other one into quarks.
  * in this situation, either the W+ or the W- may decay leptonically,
    therefore two processes have to be considered:  
```
generate p p > t~ t, (t~ > W- b~, W- > j j), (t > W+ b, W+ > l+ vl) @1
add process p p > t~ t, (t~ > W- b~, W- > l- vl~), (t > W+ b, W+ > j j) @2

```
  * the ```@``` symbol indicates the identification of the process

### 11.3 exercises

  * generate the fully-leptonic top pair production 
    charaterised by two leptons of different flavour in the final state
  * generate the same final state without specifying 
    any intermediate particles or decay paths:
      * what is the difference with respect to the previous generation?
      * when is it appropriate to use one or the other generation?

[**chapter twelve**](12_pdf.md)
