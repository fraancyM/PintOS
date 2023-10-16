# Progetto 1.1: Analisi comparativa tra OS161 e altri sistemi operativi open-source all'avanguardia per sistemi embedded e computer general purpose

Per questo progetto abbiamo scelto di analizzare _pintOS_, ...

Di seguito verranno esaminate nel dettaglio le sue caratteristiche e messe a confronto con il sistema operativo OS161, studiato durante il corso di Programmazione di Sistema.  

# Sezione I: Analisi comparativa di OS161 e MINIX 3 #

## Architettura ##

_OS161_ è progettato come un sistema operativo monolitico, dove tutti i componenti chiave, come il kernel e i driver dei dispositivi, risiedono in uno spazio di indirizzamento comune.

_pintOS_, 



## System Calls ##


## Scheduling ##

### Obiettivi ###



### Politiche di Scheduling ###

Le politiche di scheduling di _OS161_ e _pintOS_ risultano diverse avendo obiettivi diversi.

In particolare, _OS161_ utilizza una politica di scheduling semplice e predefinita basata sull'approccio Round Robin (RR), dove i processi vengono assegnati in base al loro ordine di arrivo. Inoltre, non è possibile implementare politiche di scheduling personalizzate poiché l'allocazione del tempo della CPU è principalmente gestita dal kernel per ragioni di sicurezza e stabilità.


### Implementazione ###

_OS161_ implementa l'algoritmo Round Robin con una singola coda, in cui ogni processo riceve un quantum di tempo assegnato e, quando il quantum scade, il processo viene messo in coda e viene eseguito il successivo processo pronto. Questo ciclo di esecuzione continua finchè ci sono processi nella coda pronti ad essere eseguiti. 

### Gestione delle priorità ###

OS161 possiede un sistema più semplice e prevedibile, in cui, nella versione base, non esiste il concetto di priorità. Ciò significa che un processo continuerà ad essere eseguito finché non avrà terminato la sua esecuzione, indipendentemente dai requisiti di CPU di altri processi.


### La gestione delle interruzioni ###

_OS161_ ha un semplice sistema di gestione delle interruzioni, in cui le routine di servizio delle interruzioni salvano lo stato del processo corrente, eseguono il gestore di interruzioni ed infine ripristinano lo stato del processo. Questo approccio è facile da implementare, ma non è molto flessibile e può portare a latenze di interruzioni elevate se si verificano molte interruzioni in successione.



### Conclusioni ###



## Gestione della memoria ##


**Paging e virtual memory**



**Gestione delle chiamate**


## Meccanismi di sincronizzazione ##

### Problemi della programmazione concorrente ###


### Mutex e Spinlock ###


### Semafori ###


### Condition variables ###



# Sezione II: Implementazione di nuove funzionalità  #

