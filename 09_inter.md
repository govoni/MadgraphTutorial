# 9. generation with intermediate particles in the process

[**chapter eight**](08_plot.md)

## 9.1 gauge invariant processes

  * The perturbative calculation of a scattering process is **gauge invariant**
    when stable particles are considered in the initial and final states
    of the interaction,
		and **all possible Feynman diagrams** that can be drawn
		from the initial to the final state are considered in the calculation.
  * A **particle is typically considered stable** when its lifetime
    is significantly longer that the time scale of the interaction.
    Therefore, muons, tau leptons, b quarks are considered stable
    to this extent, as well as light quarks and gluons, before they shower.

## 9.2 generation with intermediate particles

  * MG allows to generate processes where specific **intermediate particles
	  are required** to be present:
		 * to allow for a study of the **impact of the various components**
		   (for example in the case of the Drell Yan process at LEP)
		 * to **simplify the generation**,
		   which would otherwise become computationally too expensive
			 (for example for the case of high final state particle multiplicity)
		 * to target a **specific physics case**
		   (for example the Higgs boson physics)
  * There exist different ways to obtain this objective:
	   * the concatenated decay
		 * the comma notation
		 * the use of an external tool

### 9.2.1 the gauge invariant reference

As a comparison,
the full process generation is the following:
```
generate p p > e+ e-
```
  * say here how Madspin works

### 9.2.2 the concatenated decay

Describe the decay chain as a sequence of decays,
as if a specific Feynman diagram is being drawn.
```
generate p p > z > e+ e-
```
  * *down to which depth can one go?*
  * *what are the approximations present here in the calculation?*
	* *what are the corresponding parameters in the ```run_card.dat```*

### 9.2.2 the comma notation

Generate an intermediate particle,
and then describe how the generated particle may decay.
```
generate p p > z, z > e+ e-
```
  * *what is the difference wrt the previous one?*
	* *more sophisticated example: ttbar*
    * *can one indicate separate decays of the two top quarks?*
		* *how deep can one go in the chain?
		  May one let decay the top, and then the W bosons,
			in specific ways?*

### 9.2.3 the use of an external tool

Generate the intermediate particle and let other programs
(for example [Pythia](http://home.thep.lu.se/Pythia/])
generate the decay
```
generate p p > z
```
This last approach is not considered in the tutorial.

## 9.3 exercises

  * generate events with the first three techniques listed:
	  * are there differences in the total cross-sections?
		* are there differences in the invariant mass shapes?
		* are there differences in the number and type of diagrams
		  generated in the three cases?
		* are the effects of cutoffs introduced in the ```run_card.dat``` visible?
