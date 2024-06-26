# 16. How to script MG5 run 

[**chapter fifteen**](15_externalLibs.md)

## 16.1 Madgrapgh scripting

In order to script a run, one has to write a file with all the commands that would be typed interactively, in the same order as the on-line running.
Note that
   1. You can enter the answer to question as well
   2. If you do not provide answer to question, the default value will be assumed.
   3. Edition of the param_card/run_card can be scripted via the "set" command of the associate question.
The script is used as:
```
./bin/mg5_aMC PATH_TO_FILE
```

## 16.2 Example of a script performing a scan on the top mass.

```
    generate p p > t t~ j
    output MYDIRECTORY
    launch MYDIRECTORY
       set mt 170 # changing the top mass
       set wt Auto # changing the top width
       set ptj 40 # changing the ptj cut
   launch
       set mt 175 # changing the top mass
       set wt Auto # changing the top width
   launch
       set mt 180 # changing the top mass
       set wt Auto # changing the top width
   launch MYDIRECTORY -i
       print_results --path=./cross_section_top.txt --format=short
```

  1. The last two command allow you to have a multi-column file with the cross-section/error/... for each of the run
  2. The same can be done with the ./bin/madevent and ./bin/amcatnlo executable .
  3. Indentation in the script file is not important

## 16.3 **check the instructions and find a title**

You already have a created directory then you use the ./bin/madevent and/or ./bin/amcatnlo in the same way as the above one.
so you can for example write the following command in a file

launch
 madspin=ON
 set mt scan:[170,175,180]
 set wt Auto
 set ptj 40
multi_run 10
  madspin=OFF
  set mt 175
  set wt Auto
  set nevents 100k

and then run as
 ./bin/madevent PATH_TO_FILE

Note for large scan it is more efficient to use the "./bin/madevent" executable rather than the "./bin/mg5_aMC" one
