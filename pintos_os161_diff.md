# Link Utili per la ricerca
- Pintos doc: https://cs162.org/static/proj/pintos-docs/
- Pintos doc by Stanford (PDF): https://web.stanford.edu/class/cs140/projects/pintos/pintos.pdf
- 

Argomenti contro-parte OS:
- System calls: https://ops-class.org/man/syscall/
- Processes scheduling: http://jhshi.me/2012/03/18/os161-process-scheduling/index.html

# Progetto 1.1: Analisi comparativa tra OS161 e altri sistemi operativi open-source all'avanguardia per sistemi embedded e computer general purpose

Per questo progetto abbiamo scelto di analizzare _pintOS_, un sistema operativo didattico open source per l'architettura del set di istruzioni x86, attualmente in uso in diversi istituti. Fu creato all'università di Stanford da Ben Pfaff nel 2004, originariamente pensato per sostituire il sistema operativo NachOS, un sistema simile creato dalla University of California a Berkeley. A differenza di NachOS, PintOS può essere eseguito sull'hardware x86 reale, sebbene venga spesso eseguito su un'emulatore di sistema, come Bochs o Qemu. Noi abbiamo utilizzato il simulatore QEMU.

Di seguito verranno esaminate nel dettaglio le sue caratteristiche e messe a confronto con il sistema operativo OS161, studiato durante il corso di Programmazione di Sistema.  

# Sezione I: Analisi comparativa di OS161 e Pintos #

## Architettura ##

_OS161_ è progettato come un sistema operativo monolitico, dove tutti i componenti chiave, come il kernel e i driver dei dispositivi, risiedono in uno spazio di indirizzamento comune.

_pintOS_ invece è progettato come un sistema operativo di tipo microkernel, che significa che il kernel è diviso in componenti più piccoli e indipendenti chiamati thread utente. Questi thread utente implementano le diverse funzionalità del sistema operativo.

![Architettura di PintOS](./images/Pintos_Architecture.png)

_pintOS_ utilizza il concetto di "thread utente" per rappresentare i processi. Ogni thread utente contiene le informazioni necessarie per l'esecuzione del processo, come il codice del programma, lo stato del processore e lo stato di I/O. I thread utente sono implementati come thread del kernel, il che semplifica la gestione dei processi.

## System Calls ##
Da decidere se fare questa sezione o meno. 

## Scheduling ##

### Obiettivi ###

_OS161_ e _PINTOS_ sono entrambi sistemi operativi utilizzati per scopi didattici, ma presentano approcci diversi rispetto alla gestione dello scheduling dei processi. _OS161_ è principalmente un sistema operativo didattico per l'apprendimento dei concetti dei sistemi operativi con un'implementazione semplice. _PINTOS_ fornisce una base più operativa per gli studenti, poichè mira ad essere un sistema operativo di base che sia in grado di eseguire applicazioni reali.

### Politiche di Scheduling ###

Le politiche di scheduling di _OS161_ e _pintOS_ risultano diverse, pur essendo entrambi sistemi operativi didattici, utilizzati spesso in corsi universitari per insegnare i principi dei sistemi operativi.

In particolare, _OS161_ utilizza una politica di scheduling semplice e predefinita basata sull'approccio Round Robin (RR), dove i processi vengono assegnati in base al loro ordine di arrivo. Inoltre, non è possibile implementare politiche di scheduling personalizzate poiché l'allocazione del tempo della CPU è principalmente gestita dal kernel per ragioni di sicurezza e stabilità.

_pintOS_ utilizza uno scheduling basato sulla priorità come politica di base, dove ogni processo ha un livello di priorità associato, e il processo con la priorità più alta viene selezionato per l'esecuzione. È possibile implementare politiche di scheduling più avanzate come il Multi-Level Feedback Queue (MLFQ) o il Fixed Priority Scheduler. Può anche implementare la donazione della priorità per gestire situazioni in cui un processo a bassa priorità detiene una risorsa necessaria da un processo ad alta priorità. La priorità del processo a bassa priorità può temporaneamente aumentare per garantire il rilascio tempestivo della risorsa.

### Implementazione ###

_OS161_ implementa l'algoritmo Round Robin con una singola coda, in cui ogni processo riceve un quantum di tempo assegnato e, quando il quantum scade, il processo viene messo in coda e viene eseguito il successivo processo pronto. Questo ciclo di esecuzione continua finchè ci sono processi nella coda pronti ad essere eseguiti. 

### Gestione delle priorità ###

OS161 possiede un sistema più semplice e prevedibile, in cui, nella versione base, non esiste il concetto di priorità. Ciò significa che un processo continuerà ad essere eseguito finché non avrà terminato la sua esecuzione, indipendentemente dai requisiti di CPU di altri processi.


### La gestione delle interruzioni ###

_OS161_ ha un semplice sistema di gestione delle interruzioni, in cui le routine di servizio delle interruzioni salvano lo stato del processo corrente, eseguono il gestore di interruzioni ed infine ripristinano lo stato del processo. Questo approccio è facile da implementare, ma non è molto flessibile e può portare a latenze di interruzioni elevate se si verificano molte interruzioni in successione.


### Conclusioni ###

In conclusione, _OS161_ è più orientato all'apprendimento e alla semplificazione, concentrandosi sulla comprensione dei concetti di base dei sistemi operativi e sulla loro implementazione, mentre _Pintos_ è noto per essere altamente modulare, il che facilita la comprensione e la personalizzazione del sistema operativo e mira a fornire un'esperienza più realistica e operativa. Questa struttura modulare offre agli studenti in ambito didattico l'opportunità di esplorare e sperimentare con vari aspetti del sistema operativo.
Entrambi gli ambienti sono validi per l'apprendimento dei principi di scheduling dei processi nei sistemi operativi, ma il loro focus differisce leggermente in base agli obiettivi educativi.

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

