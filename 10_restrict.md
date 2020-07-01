# 10. restrict the allowed processes in the event generation

[**chapter nine**](09_inter.md)

## 10.1 an example to start with: Z boson plus two jets

  * MG may be used to produce processes *with also quarks in the final state*
  * One example of such a generation is a Z boson accompanied by two quarks
    (where the definition of j can be found in [chapter 3](03_firstRun.md)):
```
generate p p > z j j
output zjj_default
```

### 10.1.1 the analysis of the process

  * The outcome of the process generation will contain diagrams
    featuring *strong and the electroweak coupling vertices*, 
    indicated as QCD and QED respectively in the MG drawings
  * To find the images of the calculated diagrams:  
```
cd zjj_default/
find . -name "*.ps"
```
  * MG will generate the processes with the minimal number of QED vertices needed:




10.2 DY + 2 jets QED

10.3 DY + 2 jets QCD

