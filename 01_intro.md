# 1. introduzione

## 1.1 simulazione di un evento fisico

### 1.1.1 un evento fisico

  * una misura acquisita da un rivelatore di particelle è un evento fisico

  ![event display image](https://cds.cern.ch/record/2713462/files/VVVEventDisplays.001.jpeg?subformat=icon-640)

### 1.1.2 analisi di un evento fisico

Che cosa deve accadere per portare all'evento fisico finale: **la collisione**

  * creazione dei fasci di particelle
  * collisione di pacchetti di particelle, uno per fascio
    * interazione inelastica di almeno una particella per fascio
    * se si tratta di protoni, interazione di due partoni (scelto secondo le parton ditribution functions)
  * interazione delle particelle elementari, descritta perturbativamente   
  * interazione dei proton remnant che generano underlying event (UE)
  * parte non perturbativa dell'interazione: showering ed adronizzazione
  * interazioni aggiuntive generano pile-up (PU)  

Che cosa deve accadere per osservare l'evento fisico finale: **la rivelazione**

  * i prodotti della collisione viaggiano nel vuoto fino a raggiungere il rivelatore (dopo aver attraversato il tubo a vuoto del fascio)
  * le particelle cariche tipicamente curvano immerse in un campo magnetico
  * alcune particelle decadono in volo
  * le particelle interagiscono con il rivelatore depositando energia al suo interno
  * i singoli elementi di rivelazione trasformano l'energia in segnale elettrico

Che cosa deve accadere per osservare l'evento fisico finale: **la ricostruzione**

  * i segnali elettrici vengono salvati su disco e nello stesso tempo processati
  * in caso di eventi molto frequenti, solamente una parte degli eventi viene salvata, con una scelta effettuata durante l'acquisizione dati
  * i segnali elettrici vengono analizzati per ricostruire numero, tipo e cinematica delle particelle che hanno attraversato il rivelatore

### 1.1.3 l'analisi dei dati

  * obiettivo finale: determinazione di **parametri di un modello**
  * ottenuta attraverso il confronto dei dati con un modello (**fit**)
  * la simulazione è il modello che si utilizza nel confronto, quindi si tratta di un **calcolo teorico** svolto con un sistema sofisticato di strumenti software

### 1.1.4 la simulazione di un evento fisico

Solitamente suddivisa in diversi passaggi, che riproducono le fasi nelle quali abbiamo suddiviso l'evento fisico

| fase | descrizione |
| ---  | -------- |
| collisione delle particelle elementari | calcolo perturbativo dell'urto |
| showring e adronizzazione | calcolo della parte non perturbativa dell'urto |
| simulazione (abuso di linguaggio) | interazione radiazione-materia fino al deposito dell'enegia |
| pile-up addition | sovrapposizione dei depositi energetici dovuti agli eventi di pile-up |
| digitizzazione | descrizione della risposta dell'elettronica di acquisizione dati |
| trigger | simulazione delle selezioni *on-line* |
| ricostruzione | esecuzione degli algoritmi di ricostruzione, solitamente gli stessi utilizzati per gli eventi reali |

## 1.2 la generazione a livello partonico: vantaggi e limitazioni

### 1.2.1 la collisione delle particelle elementari

  * Ogni fase descritta precedentemente è svolta da **programmi dedicati**
  * Il calcolo perturbativo della collisione è solitamente svolto da programmi detti **a matrix element**
  * calcolano le probabilità differenziali che la collisione accada, cioè le **sezioni d'urto differenziali**, a partire dagli elementi di matrice costruiti dalla Lagrangiana del processo di interesse
  * le sezioni d'urto sono differenziali nel massimo numero di variabili possibili per descrivere completamente l'evento: la **cinematica completa di ogni particella di stato finale**
  * le sezioni d'urto finali da confrontare con le misure sperimentali si calcolano integrando le distribuzioni differenziali

### 1.2.2 lo studio degli eventi a livello partonico

  * l'integrazione viene fatta con il **metodo di Monte Carlo**, cioè con la generazione di punti casuali nello spazio N-dimensionale e il conteggio di quelli che stanno sotto le curve da integrare
  * all'atto pratico, i programmi di simulazione producono **sequenze dei punti che stanno sotto le curve** da integrare
  * siccome lo spazio delle fasi è uguale alla cinematica completa dello stato finale, ogni punto è assimilabile ad un evento, come se fosse la **simulazione della parte perturbativa di una collisione**

![particle collision drawing](https://www.hep.lu.se/delphi/images/twophot_col.gif)

## 1.3 la precisione nelle simulazioni

### 1.3.1 non si tratta di eventi reali

  * i punti generati dai programmi di simulazione sono solitamente chiamati eventi
  * non si tratta di eventi reali
    * **manca la parte non-perturbativa del calcolo**, sia nello stato finale che nello stato iniziale, dove viene applicato il teorema di fattorizzazione
    * la parte perturbativa **non è nota a tutti gli ordini perturbativi!**
    * circa ogni processo di collisione di particelle elementari è **noto a tree level** (leading order, LO)
    * la maggior parte dei processi osservati finora è **nota e simulabile a NLO QCD**
    * pochissimi processi sono noti a NLO EWK
  * la simlazione differenziale è **meno precisa di calcoli integrali**
    * alcuni processi sono noti analiticamente a NNLO QCD, quasi nessuno simulato con questa precisione
    * un processo (la produzione di bosoni di Higgs tramite gluon fusion) è noto a N3LO, non simulato
    * per alcuni processi si conoscono le correzioni NNLO EWK

### 1.3.2 non si tratta nemmeno di eventi simulati

  * le correzioni perturbative NLO aggiungono **termini reali e virtuali alla sezione d'urto totale**
  * questo si ripercuote sul fatto che gli eventi simulati non hanno tutti la stessa importanza per il calcolo della sezione d'urto: **acquisicono un peso**
    * questo significa che non obbediscono più alla statistica poissoniana, come invece fanno le misure
  * alcuni eventi acquisiscono **peso negativo** che proviene dai termini di correzione NLO virtuale

[**capitolo secondo**](02_mg.md)
