# Link Utili per la ricerca
- Pintos doc: https://cs162.org/static/proj/pintos-docs/
- Pintos doc by Stanford (PDF): https://web.stanford.edu/class/cs140/projects/pintos/pintos.pdf
- 

Argomenti contro-parte OS:
- System calls: https://ops-class.org/man/syscall/
- Processes scheduling: http://jhshi.me/2012/03/18/os161-process-scheduling/index.html

# Progetto 1.1: Analisi comparativa tra OS161 e altri sistemi operativi open-source all'avanguardia per sistemi embedded e computer general purpose

Per questo progetto abbiamo scelto di analizzare _pintOS_, un semplice framework di sistema operativo didattico per l'architettura del set di istruzioni x86, attualmente in uso in diversi istituti. Fu creato all'università di Stanford da Ben Pfaff nel 2004, originariamente pensato per sostituire il sistema operativo NACHOS.

Di seguito verranno esaminate nel dettaglio le sue caratteristiche e messe a confronto con il sistema operativo OS161, studiato durante il corso di Programmazione di Sistema.  

# Sezione I: Analisi comparativa di OS161 e Pintos #

## Architettura ##

_OS161_ è progettato come un sistema operativo monolitico, dove tutti i componenti chiave, come il kernel e i driver dei dispositivi, risiedono in uno spazio di indirizzamento comune.

_pintOS_ è progettato come un sistema operativo di tipo microkernel, che significa che il kernel è diviso in componenti più piccoli e indipendenti chiamati thread utente. Questi thread utente implementano le diverse funzionalità del sistema operativo.

![Architettura microkernel di Minix 3](./images/Pintos_Architecture.png)

_pintOS_ utilizza il concetto di "thread utente" per rappresentare i processi. Ogni thread utente contiene le informazioni necessarie per l'esecuzione del processo, come il codice del programma, lo stato del processore e lo stato di I/O. I thread utente sono implementati come thread del kernel, il che semplifica la gestione dei processi.

## System Calls ##
Da decidere se fare questa sezione o meno. 

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

Pintos implementa una gestione della memoria virtuale di base. Questo include la paginazione e la gestione dello spazio degli indirizzi dei processi, consentendo ai processi di operare in spazi di indirizzamento separati e protetti... TBC


**Gestione delle chiamate**


## Meccanismi di sincronizzazione ##

### Problemi della programmazione concorrente ###

### Mutex e Spinlock ###

### Semafori ###

### Condition variables ###



# Sezione II: Implementazione di nuove funzionalità  #

