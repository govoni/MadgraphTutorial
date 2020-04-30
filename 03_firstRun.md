# 3. primo test di utilizzo

## 3.1 descrizione di un processo

MG è un programma automatico,
quindi è necessario istruire il programma
riguardo al processo che si vuole generare

### 3.1.1 le particelle elementari

Ogni particella elementare ha un nome in Madgraph

| particella  | simbolo | particella  | simbolo |
| ----------- | ------- | ----------- | ------- |
| elettrone   | e-      | positrone   | e+      |
| neutrino-e  | ve      | anti-ve     | ve~     |
| muone       | mu-     | antimuone   | mu+     |
| neutrino-mu | vm      | anti-vm     | vm~     |
| tau         | ta-     | antitau     | ta+     |
| neutrino-ta | vt      | anti-vt     | vt~     |
| quark u     | u       | anti-u      | u~      |
| quark d     | d       | anti-d      | d~      |
| quark c     | c       | anti-c      | c~      |
| quark s     | s       | anti-s      | s~      |
| quark t     | t       | anti-t      | t~      |
| quark b     | b       | anti-b      | b~      |
| fotone      | a       | gluone      | g       |
| bosone W-   | w-      | bosone W+   | w+      |
| bosone Z    | z       | higgs boson | h       |

* più particelle definite qui: [naming scheme](http://madgraph.phys.ucl.ac.be/sm_particles.html)
* si possono definire particelle nuove:
```
define j = g u c d s u~ c~ d~ s~
define l+ = e+ mu+
define l- = e- mu-
define vl = ve vm vt
define vl~ = ve~ vm~ vt~
```
* esistono definizioni già esistenti in MG:
```
define p = g u c d s u~ c~ d~ s~
```

### 3.1.2 la descrizione di un processo elementare

dallo stato iniziale allo stato finale a LO:

  * bosone vettore Z a collider di protoni:
    * stato iniziale: ```p p```
    * stato finale: ```z```
  ```
  p p > z
  ```
  * coppie di elettroni a collider di protoni:
    * stato iniziale: ```p p```
    * stato finale: ```e+ e-```
  ```
  p p > e+ e-
  ```

Il secondo processo **non è equivalente al primo**,
perché contiene tutti i possibili diagrammi a LO che produono
una coppia ```e+ e-``` a partire da due protoni,
mentre il primo produce un bosone vettore non decaduto.

  * coppie di bosoni vettori di segno opposto a collider di protoni:
    * stato iniziale: ```p p```
    * stato finale: ```w+ w-```
  ```
  p p > w+ w-
  ```
  * leptoni carichi e neutri a collider di protoni:
    * stato iniziale: ```p p```
    * stato finale: ```e- ve~ mu+ vm```
  ```
  p p > e- ve~ mu+ vm
  ```

## 3.2 primo test di funzionamento di MG

### 3.2.1 avvio di una sessione interattiva

Avviate una sessione interattiva di MG:
```
cd MG5_aMC_v2_7_2/
./bin/mg5_aMC
```
All'avvio, MG compie una serie di azioni:
  * cerca di caricare LHAPDF e FastJet, in questo caso fallisce perché non sono stati installati
  * carica il modello fisico da utilizzare nella simulazione degli eventi:
  ```
  Loading default model: sm
  INFO: load particles
  INFO: load vertices
  INFO: Restrict model sm with file models/sm/restrict_default.dat .
  INFO: Run "set stdout_level DEBUG" before import for more information.
  INFO: Change particles name to pass to MG5 convention
  ```
  * definisce alcune collezioni di particelle:
  ```
  Defined multiparticle p = g u c d s u~ c~ d~ s~
  Defined multiparticle j = g u c d s u~ c~ d~ s~
  Defined multiparticle l+ = e+ mu+
  Defined multiparticle l- = e- mu-
  Defined multiparticle vl = ve vm vt
  Defined multiparticle vl~ = ve~ vm~ vt~
  Defined multiparticle all = g u c d s u~ c~ d~ s~ a ve vm vt e- mu- ve~ vm~ vt~ e+ mu+ t b t~ b~ z w+ h w- ta- ta+
  ```
    * perché il protone è composto anche da gluoni e anti-quark?
    * come si fa a dire a MG di generare eventi con due protoni nello stato iniziale, oppure un protone e un antiprotone?
    * perché i leptoni carichi sono definiti raggruppando soltanto le prime due famiglie leptoniche?

### 3.2.2 generazione di un processo

  * produzione di un bosone vettore Z a collider di protoni, a LO:
  ```
  MG5_aMC> generate p p > z
  ```
  * outout di MG:e il programma ha identificato 4 processi con 4 diagrammi
  ```
  INFO: Checking for minimal orders which gives processes.
  INFO: Please specify coupling orders to bypass this step.
  INFO: Trying process: g g > z WEIGHTED<=2 @1  
  INFO: Trying process: u u~ > z WEIGHTED<=2 @1  
  INFO: Process has 1 diagrams
  INFO: Trying process: u c~ > z WEIGHTED<=2 @1  
  INFO: Trying process: c u~ > z WEIGHTED<=2 @1  
  INFO: Trying process: c c~ > z WEIGHTED<=2 @1  
  INFO: Process has 1 diagrams
  INFO: Trying process: d d~ > z WEIGHTED<=2 @1  
  INFO: Process has 1 diagrams
  INFO: Trying process: d s~ > z WEIGHTED<=2 @1  
  INFO: Trying process: s d~ > z WEIGHTED<=2 @1  
  INFO: Trying process: s s~ > z WEIGHTED<=2 @1  
  INFO: Process has 1 diagrams
  INFO: Process u~ u > z added to mirror process u u~ > z
  INFO: Process c~ c > z added to mirror process c c~ > z
  INFO: Process d~ d > z added to mirror process d d~ > z
  INFO: Process s~ s > z added to mirror process s s~ > z
  4 processes with 4 diagrams generated in 0.045 s
  Total: 4 processes with 4 diagrams
  ```

### 3.2.3 ispezione del processo generato

  * elenco dei processi generati: MG produce la lista dei processi elementari che possono produrre lo stato finale desiderato
  ```
  MG5_aMC>display processes
  Process: u u~ > z WEIGHTED<=2 @1
  Process: c c~ > z WEIGHTED<=2 @1
  Process: d d~ > z WEIGHTED<=2 @1
  Process: s s~ > z WEIGHTED<=2 @1
  ```
    * pochi per processi semplici, crescono per processi complessi
  * disegno dei diagrammi generati
  ```
  MG5_aMC>display diagrams
  ```
  * MG disegna questo per ogni processo:
  ![Zprod](images/Zprod_diagram.png)
    * livello albero dell'interazione per ogni diagramma che partecipa al processo
    * ordine dei vertici: ```QCD=0``` significa che non ci sono vertici forti, ```QED=1``` significa che c'è un vertice elettrodebole
    * questo diagramma corrisponde al processo ```u u~ > z```
