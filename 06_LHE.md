# 6. the event files

[**chapter five**](05_gen.md)

## 6.1 where the event file is stored

  * **Event files** hold the kinematics of the input,
    intermediate and output particles of each event in a specific XML format,
    called **Les Houches format (LHE)**,
    from the name of the place where it was designed.
  * **Generate a sample** for the first tests:
```
./bin/mg5_aMC
> generate p p > e+ e-
> output test_epem
> quit
cd test_epem
printf "0\n done\n" | ./bin/generate_events
cd Events/run_01/
gunzip unweighted_events.lhe.gz
```

## 6.2 its format and content

The LHE files are divided into three main sections.
  * the ``<header>`` section contains information
    regarding the **generation configuration**,
    filled differently by each Monte Carlo program.
    * MG reports the whole banner, including the cross-section
  * the ``<init>`` section contains **information valid for all the events**
    to be read only once
  * the ``<events>`` contains the **set of events** stored in the file  
  * a detailed description of the LHE file may be found
    [here](http://govoni.web.cern.ch/govoni/tesi/docs/LHEreading.pdf)

## 6.3 an event example

  * the event starts and information concerning the whole event is reported
```
<event>
 5      1 +8.4300000e+02 9.20849300e+01 7.54677100e-03 1.29788000e-01
 ```
  * the list of particles follows
 ```
       -2 -1    0    0    0  501 -0.0000000000e+00 +0.0000000000e+00 +1.7485182150e+01 1.7485182150e+01 0.0000000000e+00 0.0000e+00 1.0000e+00
        2 -1    0    0  501    0 +0.0000000000e+00 -0.0000000000e+00 -1.2124029558e+02 1.2124029558e+02 0.0000000000e+00 0.0000e+00 -1.0000e+00
       23  2    1    2    0    0 +0.0000000000e+00 +0.0000000000e+00 -1.0375511343e+02 1.3872547773e+02 9.2084931496e+01 0.0000e+00 0.0000e+00
      -11  1    3    3    0    0 -2.1817482672e+01 -2.9064364399e+01 -9.2895879886e+00 3.7510482176e+01 0.0000000000e+00 0.0000e+00 1.0000e+00
       11  1    3    3    0    0 +2.1817482672e+01 +2.9064364399e+01 -9.4465525442e+01 1.0121499555e+02 0.0000000000e+00 0.0000e+00 -1.0000e+00
 ```
  * a set of weights follows, useful to estimate theory uncertainties
 ```
<mgrwt>
<rscale>  0 0.92084931E+02</rscale>
<asrwt>0</asrwt>
<pdfrwt beam="1">  1        2 0.18652354E-01 0.92084931E+02</pdfrwt>
<pdfrwt beam="2">  1       -2 0.26900280E-02 0.92084931E+02</pdfrwt>
<totfact> 0.12680605E+05</totfact>
</mgrwt>
```
  * after the weights section, the event terminates
```
</event>
```

[**chapter seven**](07_read.md)
