# 4. MG running parameters

[**chapter three**](03_firstRun.md)

## 4.1 the saved folder

The folder created by the ```output``` command contains
what is needed to generate events:
```
cd test_Z
ls
```
among the other, the following files are present:

|     |     |
| --- | --- |
| Cards/ | configuration files |
| Events/ | where generated events will be stored |
| HTML/ | files for the process homepage |
| MGMEVersion.txt | version of MG used |
| README | detailed set of usage instructions |
| README.systematics | detailed set of instructions on systematics |
| Source/ | FIXME |
| SubProcesses/ | FIXME |
| TemplateVersion.txt | version of FIXME used |
| bin/ | executables |
| index.html | summary page |
| lib/ | PDF information |
| madevent.tar.gz | compressed version of the code |

In the ```Cards``` folder, the **configuration files**
for the process description and running can be found.
Three of them are of interest in particular.
There, parameters can be modified according to the needs of the generation.

## 4.2 the ```proc_card.dat```

Contains the **instructions to generate the process**,
as inserted in the command line.
This file may be modified before starting the event generation.
In this case:
```
cat Cards/proc_card.dat
```
ends with:
```
set default_unset_couplings 99
set group_subprocesses Auto
set ignore_six_quark_processes False
set loop_optimized_output True
set loop_color_flows False
set gauge unitary
set complex_mass_scheme False
set max_npoint_for_channel 0
import model sm
define p = g u c d s u~ c~ d~ s~
define j = g u c d s u~ c~ d~ s~
define l+ = e+ mu+
define l- = e- mu-
define vl = ve vm vt
define vl~ = ve~ vm~ vt~
generate   p p > z
output test_Z
```

## 4.3 the ```param_card.dat```

Sets the value of the **model parameters**
to be used for the event generation,
for example:
```
###################################
## INFORMATION FOR MASS
###################################
Block mass
    5 4.700000e+00 # MB
    6 1.730000e+02 # MT
   15 1.777000e+00 # MTA
   23 9.118800e+01 # MZ
   25 1.250000e+02 # MH
```

All lines starting with ```#``` are ignored,
as well as all the text put after a ```!``` in any line.

## 4.4 the ```run_card.dat```

Contains the **information for the production** setup:
  * **number of events** to be generated
  * **random seed** to be used in the generation:
    * set it to a known number allows reproducibility
    * if the production is split in several jobs, the random seed has to change from one job to another
  * **initial state** information:
    * collider beams type
    * collider beams energy  
    * parton distribution functions
  * **general parameters** of the process
    * renormalisation and factorisation scales
    * handling of helicities
    * whether to create a gridpack (see later maybe)
    * whether to bias the sample (see later maybe)
  * **selections** to be applied to final state partons
  * whether to use systematics (see later maybe)

[**chapter five**](05_gen.md)
