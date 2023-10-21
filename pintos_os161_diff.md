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

Le system calls (chiamate di sistema) sono funzioni fornite dal sistema operativo per consentire ai programmi di interagire con il kernel (il nucleo del sistema operativo) e sfruttare le risorse del sistema, come l'hardware, i file, la memoria e altro. Sono fondamentali per il funzionamento dei sistemi operativi e svolgono un ruolo cruciale in vari aspetti:

1. **Gestione delle risorse**: Le system calls consentono ai programmi di richiedere l'allocazione e la liberazione di risorse hardware, come memoria, CPU e dispositivi di I/O. Ad esempio, una system call può essere utilizzata per richiedere memoria dinamica o per leggere da un file su disco.

2. **Protezione**: Le system calls impediscono ai programmi utente di accedere direttamente alle risorse hardware o di eseguire operazioni pericolose. Questo garantisce che il sistema operativo abbia il controllo su quali risorse vengono allocate o condivise tra i processi e previene l'accesso non autorizzato.

3. **Comunicazione tra processi**: Le system calls consentono la comunicazione tra i processi. Ad esempio, è possibile utilizzare system calls per creare processi figlio, condividere dati tra processi o sincronizzare l'esecuzione di processi diversi.

4. **Gestione dei file**: Molte system calls sono dedicate alla gestione dei file, inclusa la creazione, l'apertura, la lettura, la scrittura e la chiusura dei file. Queste operazioni sono fondamentali per l'archiviazione e il recupero dei dati.

5. **Gestione delle interruzioni**: Le system calls consentono al kernel di gestire le interruzioni hardware e rispondere a eventi come la pressione di un tasto sulla tastiera o l'arrivo di dati in una porta di rete.

6. **Comunicazione di rete**: System calls sono spesso utilizzate per la comunicazione di rete, consentendo ai programmi di inviare e ricevere dati su una rete, come Internet.

_Os161_ e _Pintos_, sono sistemi operativi progettati per scopi didattici, per cui in entrambi nativamente manca il supporto completo delle system calls, come vedremo successivamente nella **sezione II** del progetto. 

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

Pintos implementa una gestione della memoria virtuale di base. Questo include la paginazione e la gestione dello spazio degli indirizzi dei processi, consentendo ai processi di operare in spazi di indirizzamento separati e protetti. Utilizza, inoltre, un file speciale chiamato "pagina di swap" per memorizzare temporaneamente le pagine fisiche quando la memoria fisica è esaurita. Questo permette di gestire i casi in cui la memoria fisica è piena, spostando le pagine meno utilizzate in memoria su disco e recuperandole quando necessario.

Più in particolare, la memoria fisica di Pintos è suddivisa in pagine di dimensioni fisse, e ogni pagina ha un numero di pagina univoco. Ogni processo ha un proprio spazio di indirizzamento virtuale, suddiviso in pagine. La mappatura tra gli indirizzi virtuali dei processi e gli indirizzi fisici delle pagine è gestita da una tabella delle pagine (Page Table) specifica per ciascun processo. Esso fa uso di strutture dati quali vettori, liste, bitmap ecc... ma principalmente Pintos include una struttura di tipo BitMap per tenere traccia dell'utilizzo in un insieme di risorse (identiche), e inoltre utilizza anche una struttura di tipo Hash Table che supporta, in maniera efficiente, le inserimenti ed eliminazioni su un'ampia gamma di tabelle. 

Per questi motivi Pintos possiede un sistema di paginazione e memoria virtuale simile a quello presente su OS161, mentre la sostanziale differenza risiede nel livello di complessità con cui sono state implementate queste funzioni.
La paginazione presente in OS161 è più avanzata, offrendo quindi funzionalità aggiuntive rispetto a Pintos.


**Gestione delle chiamate**

## Meccanismi di sincronizzazione ##

### Problemi della programmazione concorrente ###

Una **critical section** è un concetto fondamentale nell'ambito della programmazione concorrente e parallela. Rappresenta una porzione di codice in un programma in cui viene eseguita un'operazione che coinvolge risorse condivise, come variabili o strutture dati, che possono essere accessibili da più thread o processi contemporaneamente. L'obiettivo principale della protezione di una critical section è garantire la correttezza e l'integrità dei dati, evitando situazioni di accesso concorrente che potrebbero portare a risultati indesiderati o inconsistenze.

I problemi principali che possono sorgere in relazione alle critical section sono:

1. **Race Condition**:  si verifica quando due o più thread o processi cercano di accedere contemporaneamente alla stessa risorsa condivisa senza sincronizzazione adeguata. Questo può portare a risultati imprevedibili o errati poiché l'ordine di esecuzione delle istruzioni non è garantito.
2. **Deadlock**: si verifica quando due o più thread o processi si bloccano reciprocamente, ciascuno aspettando che una risorsa venga rilasciata dall'altro. In altre parole, si crea una situazione in cui nessun thread può procedere, impedendo il completamento dell'esecuzione.
3. **Starvation**: si verifica quando un thread viene continuamente prevenuto dall'accedere a una risorsa condivisa da altri thread che la monopolizzano. Ciò potrebbe portare a un'inefficienza complessiva del sistema, poiché alcuni thread potrebbero essere costantemente trascurati.
4. **Livelock**: è una situazione simile al deadlock, ma in questo caso i thread non sono bloccati completamente; invece, sono in uno stato attivo e in continuo scambio di risorse, ma senza alcun progresso reale nell'esecuzione.
Le critical section sono quindi parti cruciali di un programma in cui l'accesso concorrente alle risorse condivise deve essere attentamente gestito per garantire la correttezza e l'affidabilità del software.

I **meccanismi di sincronizzazione** fungono da ponti tra i thread o i processi, permettendo loro di coordinarsi e collaborare nell'accesso alle risorse condivise. 
I principali meccanismi di sincronizzazione sono: Mutex, Semaphore, Locks e Condition Variables.

### Mutex e Spinlock ###

### Semafori ###

### Condition variables ###

# Sezione II: Implementazione di nuove funzionalità #

Come detto precedentemente, _Pintos_ è stato progettato principalmente per scopi didattici e per aiutare gli studenti a comprendere i concetti chiave dei sistemi operativi. Per questo progetto abbiamo scelto di focalizzarci sull'implementazione di alcune system calls poichè in Pintos non sono gestite per semplicità.

Le system calls definite nativamente in Pintos in `src/lib/syscall-nr.h` sono:

 ```c
/* System call numbers. */
enum 
  {
    SYS_HALT,                   /* Halt the operating system. */
    SYS_EXIT,                   /* Terminate this process. */
    SYS_EXEC,                   /* Start another process. */
    SYS_WAIT,                   /* Wait for a child process to die. */
    SYS_CREATE,                 /* Create a file. */
    SYS_REMOVE,                 /* Delete a file. */
    SYS_OPEN,                   /* Open a file. */
    SYS_FILESIZE,               /* Obtain a file's size. */
    SYS_READ,                   /* Read from a file. */
    SYS_WRITE,                  /* Write to a file. */
    SYS_SEEK,                   /* Change position in a file. */
    SYS_TELL,                   /* Report current position in a file. */
    SYS_CLOSE,                  /* Close a file. */

    SYS_MMAP,                   /* Map a file into memory. */
    SYS_MUNMAP,                 /* Remove a memory mapping. */

    SYS_CHDIR,                  /* Change the current directory. */
    SYS_MKDIR,                  /* Create a directory. */
    SYS_READDIR,                /* Reads a directory entry. */
    SYS_ISDIR,                  /* Tests if a fd represents a directory. */
    SYS_INUMBER                 /* Returns the inode number for a fd. */
  };
 ```
Noi abbiamo scelto di implementare ...

