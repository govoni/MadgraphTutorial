# 5. generate events

[**chapter four**](04_cfg.md)

## 5.1 generating events in the interactive mode

### 5.1.1 prepare for the actual event generation

After issuing the command of generating a process,
one can directly issue the event generation,
with the command launch:
```
./bin/mg5_aMC
MG5_aMC> generate p p > z
launch
```
The command ```launch``` automatically creates an output folder.
From the output folder, the configuration files are then read:
```
INFO: load configuration from /.../MGTutorial/MG5_aMC_v2_7_2/PROC_sm_0/Cards/me5_configuration.txt  
INFO: load configuration from /.../MGTutorial/MG5_aMC_v2_7_2/input/mg5_configuration.txt  
INFO: load configuration from /.../MGTutorial/MG5_aMC_v2_7_2/PROC_sm_0/Cards/me5_configuration.txt  
```
And the current generation configuration is shown to the user:

```
The following switches determine which programs are run:
/=================== Description ===================|============= values ==============|======== other options ========\
| 1. Choose the shower/hadronization program        |        shower = Not Avail.        |     Please install module     |
| 2. Choose the detector simulation program         |      detector = Not Avail.        |     Please install module     |
| 3. Choose an analysis package (plot/convert)      |      analysis = Not Avail.        |     Please install module     |
| 4. Decay onshell particles                        |       madspin = OFF               |     ON|onshell                |
| 5. Add weights to events for new hypp.            |      reweight = OFF               |     ON                        |
\=======================================================================================================================/
```

### 5.1.2 parameters setting and event generation

  * Before triggering the actual event generation,
    one can **change the values of parameters**:
    ```
    > set ebeam1 4000
    > set ebeam2 4000
    > done
    ```
  * The instruction ```done``` will let the **event generation begin**.
    The first phase will be compiling the code for the event generation,
    the second phase will be the actual production of events
    (as many as marked in the ```run_card.dat``` file).
    * In cases of sophisticated processes,
      MG may not be able to produce many events in a single run.
      In this case, multiple runs with smaller events is the way to go.
  * At the end of the generation,
    the **total cross section of the process** in displayed:
    ```
    === Results Summary for run: run_01 tag: tag_1 ===

       Cross-section :   2.437e+04 +- 23.46 pb
       Nb of events :  10000
    ```       
 * All the information is **summarised in the ```index.html```** file
   present in the generation folder,
   as also prompted by MG:
   ```
   more information in /.../MGTutorial/MG5_aMC_v2_7_2/PROC_sm_0/index.html
   ```

### 5.1.3 datacards editing in interactive mode

  * in interactive mode,
    after issuing the instruction ```launch```,
    it is possible to **directly edit
    the ```run_card.dat``` and ```param_card.dat``` files**:
    ```
    Do you want to edit a card (press enter to bypass editing)?
    /------------------------------------------------------------\
    |  1. param : param_card.dat                                 |
    |  2. run   : run_card.dat                                   |
    \------------------------------------------------------------/
    ```
   * By typing ```1``` or ```2```,
     the corresponding datacard is opened in the editor of choice
     for the user to modify it.
     Saving the file propagates any modifications.
   * The instruction ```done``` will let the **event generation begin**.

## 5.2 generating events with the command line

### 5.2.1 launching the generation

The folder created by MG for the process generation
contains an executable that **runs the event production**,
with the input parameters read from the datacards
present in the ```Cards``` subfolder:
```
cd test_Z
./bin/generate_events
```
This command will prompt the user with the same interface
of the interactive event generation.

### 5.2.2 running the generation without answering questions

The answers to the interactive questions
may be **passed as input** to the ```generate_events``` program:
```
printf "0\n done\n" | ./bin/generate_events
```
**Additional instructions** may be added:
```
printf "0\n set ebeam1 4000\n set ebeam2 4000\n done\n" | ./bin/generate_events
```

## 5.3 the output of the event generation

  * Every time a generation run is executed,
    a **subfolder in the ```Events```** folder is created:
  ```
  ls Events/
  run_01  run_02  run_03
  ```
  * In each folder,
    the events compressed (```unweighted_events.lhe.gz```)
    and the summary of the running conditions (```run_01_tag_1_banner.txt```)
    are saved:
  ```
  ls Events/run_01/
  run_01_tag_1_banner.txt  unweighted_events.lhe.gz
  ```  
  * At the end of the ```*banner.txt``` file,
    the resulting cross-section is reported:
  ```
  <MGGenerationInfo>
  #  Number of Events        :       10000
  #  Integrated weight (pb)  :       42107.0
  </MGGenerationInfo>
  ```    
  * The value of the cross-section (```42107```)
    and its numerical uncertainty (```39.4```) in pb
    can also be found in the HTML folder,
    for each run:
  ```
  cat HTML/run_01/results.html  | grep "(pb)"
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>s= 42107 &#177 39.4 (pb)</b><br><br>
  ```     

[**chapter six**](06_LHE.md)
