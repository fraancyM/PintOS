# Link Utili per la ricerca
- Pintos doc: https://cs162.org/static/proj/pintos-docs/
- Pintos doc by Stanford (PDF): https://web.stanford.edu/class/cs140/projects/pintos/pintos.pdf
- 

Argomenti contro-parte OS:
- System calls: https://ops-class.org/man/syscall/
- Processes scheduling: http://jhshi.me/2012/03/18/os161-process-scheduling/index.html
- Understanding system calls: https://tddg.github.io/cs571-spring20/proj2_understand_syscalls.html

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

_Os161_ e _Pintos_, sono sistemi operativi progettati per scopi didattici, per cui in entrambi nativamente manca il supporto completo delle system calls, come si può vedere di seguito:

* `kern/arch/mips/syscall/syscall.c` in _OS161_

```c
 void syscall(struct trapframe *tf) {
	int callno;
	int32_t retval;
	int err;
    ...

	callno = tf->tf_v0;
	retval = 0;

	switch (callno) {
	    case SYS_reboot:
		err = sys_reboot(tf->tf_a0);
		break;

	    case SYS___time:
		err = sys___time((userptr_t)tf->tf_a0,
				 (userptr_t)tf->tf_a1);
		break;

	    /* Add stuff here */

	    default:
		kprintf("Unknown syscall %d\n", callno);
		err = ENOSYS;
		break;
	}
    ...
 ```

 * `src/userprog/syscall.c` in _Pintos_

 ```c
#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void syscall_init (void) {
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void syscall_handler (struct intr_frame *f UNUSED) {
  printf ("system call!\n");
  thread_exit ();
}
 ```
 Vedremo l'implementazione di alcune system calls in _Pintos_ nella **sezione II** del progetto.

## Scheduling ##

### Politiche di Scheduling ###

Le politiche di scheduling di _OS161_ e _pintOS_ risultano simili, essendo sistemi operativi didattici, utilizzati spesso in corsi universitari per insegnare i principi dei sistemi operativi.

Infatti, entrambi utilizzano una politica di scheduling semplice e predefinita basata sull'approccio Round Robin (RR), dove i processi vengono assegnati in base al loro ordine di arrivo. 
Tuttavia, sia in _OS161_ che in _Pintos_, è possibile implementare, come estensione del sistema operativo, politiche di scheduling più avanzate come il Multi-Level Feedback Queue (MLFQ), il Dynamic Priority Scheduling o l'Inverse Priority Scheduling. 

### Implementazione ###

Entrambi i sistemi operativi, implementano l'algoritmo Round Robin, in cui i processi vengono schedulati in modo circolare. Ogni processo riceve un quantum di tempo assegnato (in _Pintos_ `#define TIME_SLICE 4`) e, quando il quantum scade, il processo viene messo in coda e viene eseguito il successivo processo pronto. Questo ciclo di esecuzione continua finchè ci sono processi nella coda pronti ad essere eseguiti. Non c'è nessuna gestione di priorità: tutti i thread sono trattati allo stesso modo.

In _Pintos_ la funzione responsabile di "restituire" la CPU allo scheduler e consentire agli altri thread di essere eseguiti è la `thread_yield`.

```c
void thread_yield (void) {

  /* Puntatore al thread corrente */
  struct thread *cur = thread_current ();
  enum intr_level old_level;

  /* Si verifica che la funzione non sia chiamata da un gestore di interrupt */
  ASSERT (!intr_context ());

  old_level = intr_disable ();
  if (cur != idle_thread)
    list_push_back (&ready_list, &cur->elem);
  cur->status = THREAD_READY;
  schedule ();
  intr_set_level (old_level);
}
```
La funzione `thread_yield` consente al thread corrente di rilasciare volontariamente la CPU e di diventare pronto per essere eseguito nuovamente, ma senza mettersi in attesa. Ciò è utile per consentire allo scheduler di determinare quale thread deve essere eseguito successivamente, senza causare un ritardo significativo.

Se il thread corrente non è l'`idle_thread` (il thread inattivo), il thread corrente viene inserito nella coda dei thread pronti (`ready_list`) utilizzando la `list_push_back()`. Questo significa che il thread è pronto ad essere eseguito, ma lo scheduler può decidere di concedere la CPU ad un altro thread prima di eseguirlo nuovamente. Viene impostato lo stato del thread corrente a `THREAD_READY`, indicando che il thread è pronto per l'esecuzione ma non è attualmente in esecuzione. Viene chiamata poi la funzione `schedule()` per permettere allo scheduler di decidere quale thread eseguire successivamente.

Alla fine viene ripristinato il livello di interrupt utilizzando `intr_set_level (old_level)` e permettere che gli interrupt siano nuovamente abilitati alla priorità iniziale, prima della chiamata a `thread_yield`.

```c
static void schedule (void) {
  struct thread *cur = running_thread ();
  struct thread *next = next_thread_to_run ();
  struct thread *prev = NULL;

  /* Asserzioni per verificare che le interruzioni siano disabilitate e che il thread corrente non sia più in uno stato di esecuzione. */
  ASSERT (intr_get_level () == INTR_OFF);
  ASSERT (cur->status != THREAD_RUNNING);
  ASSERT (is_thread (next));

  if (cur != next)
    prev = switch_threads (cur, next);
  thread_schedule_tail (prev);
}
```
La funzione `schedule()`, nel dettaglio, svolge un ruolo essenziale: ottiene un riferimento al thread corrente con `running_thread()` e un riferimento al successivo thread da eseguire con `next_thread_to_run()`. Il `next_thread_to_run` è selezionato dallo scheduler e rappresenta il successivo thread nella coda dei thread pronti (`ready_list`). Se il thread corrente (`cur`) è diverso dal successivo thread da eseguire (`next`), la funzione chiama `switch_threads` per effettuare una commutazione di contesto tra i due thread, ossia restituire un riferimento al thread che stava precedentemente in esecuzione. Questa operazione comporta la modifica dei registri della CPU in modo che il successivo thread possa essere eseguito. La funzione `schedule` richiama poi `thread_schedule_tail` per completare il processo di pianificazione e assicurarsi che il successivo thread sia in esecuzione. La variabile `prev` è utilizzata per tracciare il thread precedentemente in esecuzione, se è stato commutato.

### Gestione delle priorità ###

Nella versione base, per entrambi i sistemi, non esiste il concetto di priorità. Ciò significa che un processo continuerà ad essere eseguito finché non avrà terminato la sua esecuzione, indipendentemente dai requisiti di CPU di altri processi.

### La gestione delle interruzioni ###

_OS161_ ha un semplice sistema di gestione delle interruzioni, in cui le routine di servizio delle interruzioni salvano lo stato del processo corrente, eseguono il gestore di interruzioni ed infine ripristinano lo stato del processo. Questo approccio è facile da implementare, ma non è molto flessibile e può portare a latenze di interruzioni elevate se si verificano molte interruzioni in successione.

### Conclusioni ###

In conclusione, _OS161_ e _Pintos_, sono entrambi sistemi operativi utilizzati per scopi didattici, tuttavia il primo è più orientato all'apprendimento dei concetti dei sistemi operativi con un'implementazione semplice, il secondo fornisce una base più operativa per gli studenti, poichè mira ad essere un sistema operativo di base che sia in grado di eseguire applicazioni reali.
Entrambi gli ambienti sono validi per l'apprendimento dei principi di scheduling, ma il loro focus differisce leggermente in base agli obiettivi educativi.

## Gestione della memoria ##

**Paging e virtual memory**

Pintos implementa una gestione della memoria virtuale di base. Questo include la paginazione e la gestione dello spazio degli indirizzi dei processi, consentendo ai processi di operare in spazi di indirizzamento separati e protetti. Utilizza, inoltre, un file speciale chiamato "pagina di swap" per memorizzare temporaneamente le pagine fisiche quando la memoria fisica è esaurita. Questo permette di gestire i casi in cui la memoria fisica è piena, spostando le pagine meno utilizzate in memoria su disco e recuperandole quando necessario.

Più in particolare, la memoria fisica di _Pintos_ è suddivisa in pagine di dimensioni fisse, e ogni pagina ha un numero di pagina univoco. Ogni processo ha un proprio spazio di indirizzamento virtuale, suddiviso in pagine. La mappatura tra gli indirizzi virtuali dei processi e gli indirizzi fisici delle pagine è gestita da una tabella delle pagine (Page Table) specifica per ciascun processo. Esso fa uso di strutture dati quali vettori, liste, bitmap ecc... ma principalmente _Pintos_ include una struttura di tipo BitMap per tenere traccia dell'utilizzo in un insieme di risorse (identiche), e inoltre utilizza anche una struttura di tipo Hash Table che supporta, in maniera efficiente, le inserimenti ed eliminazioni su un'ampia gamma di tabelle. 

Per questi motivi _Pintos_ possiede un sistema di paginazione e memoria virtuale simile a quello presente su OS161, mentre la sostanziale differenza risiede nel livello di complessità con cui sono state implementate queste funzioni.
La paginazione presente in OS161 è più avanzata, offrendo quindi funzionalità aggiuntive rispetto a Pintos.


**Gestione delle chiamate**

In _Pintos_, le chiamate di sistema (system calls) sono gestite tramite una serie di passaggi che coinvolgono l'utente, il kernel e il sistema operativo.

Quando un processo utente desidera effettuare una chiamata di sistema utilizza una funzione o un'istruzione speciale, che genera un'interruzione o una trap e questa operazione passa il controllo al kernel. Una volta generata l'interruzione, il controllo viene passato al dispatcher di sistema del kernel. Il dispatcher è responsabile di identificare il tipo di chiamata di sistema richiesta e di instradare l'esecuzione al gestore appropriato. Il kernel di _Pintos_ effettua la validazione e l'autenticazione delle chiamate di sistema. Verifica che il processo utente abbia i diritti necessari per eseguire la chiamata di sistema richiesta e che i parametri passati siano validi, e una volta che il kernel ha verificato e autenticato la chiamata di sistema, esegue il servizio richiesto dal processo utente. Dopo aver eseguito la chiamata di sistema e soddisfatto la richiesta del processo utente, il kernel restituisce il controllo al processo utente.

_OS161_ implementa in maniera simile a Pintos la gestione delle chiamate, tenendo però conto delle differenze di codice e strutture dati utilizzate da entrambi i sistemi operativi.

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

Sia _Pintos_ che _OS161_ condividono parti comuni nella gestione di **Mutex** e **Spinlock**. Innanzitutto, definiscono strutture di dati specializzate che contengono informazioni cruciali, come lo **stato del lock** e l'**identificatore** del thread/processo detentore. Inoltre, entrambi offrono funzionalità per l'inizializzazione di questi meccanismi, consentendo di configurare adeguatamente le loro proprietà iniziali.
L'**acquisizione** dei mutex o spinlock è un altro aspetto comune: entrambi i sistemi forniscono funzioni attraverso le quali un thread o un processo può richiedere l'accesso esclusivo a una risorsa condivisa. Nel caso in cui il lock sia già detenuto, il thread/processo richiedente dovrà attendere fino a quando il lock non sarà rilasciato.
Il **rilascio** è altrettanto importante: una volta che un thread o processo ha terminato di utilizzare una risorsa condivisa, è cruciale rilasciare il lock corrispondente per permettere ad altri thread/processi in attesa di accedere alla risorsa.

### Semafori ###

I semafori sono meccanismi di sincronizzazione utilizzati per coordinare l'accesso a risorse condivise tra più processi o thread, consentono di regolare l'ordine di esecuzione delle attività evitando problemi come le condizioni di gara e l'accesso simultaneo a risorse critiche. Sono usati per garantire la coerenza e la correttezza dei dati in ambienti concorrenti, controllando l'accesso alle risorse attraverso operazioni di incremento e decremento.

_Pintos_ fornisce funzioni standard per l'inizializzazione dei semafori, l'acquisizione e il rilascio di semafori, nonché altre operazioni comuni. Ad esempio, sema_init(), sema_down(), e sema_up() sono alcune delle funzioni standard utilizzate per lavorare con i semafori. Inoltre, offre anche un sistema di gestione delle priorità, e i semafori sono spesso utilizzati per la sincronizzazione e il rilascio di thread in base alle priorità.

(Da mettere o no ?)Il principale punto di differenza tra Pintos e OS161 nella gestione dei semafori riguarda il livello di astrazione e personalizzazione. _Pintos_ offre una libreria di sincronizzazione standard con funzioni predefinite per semplificare l'uso dei semafori, mentre _OS161_ potrebbe richiedere di implementare i semafori da zero o definire le proprie API.

Nel caso di OS161, l'implementazione dei semafori si differenzia in alcuni aspetti. 
Il sistema offre due tipi principali di semafori: **semafori di conteggio** e **semafori binari**.
I primi possono assumere valori interi in un dominio illimitato; i semafori binari presentano solo due valori, 0 o 1, simili alle mutex.

Le operazioni principali sono:

•	**wait(S)**: sospende un processo o un thread fino a quando il valore del semaforo S non diventa maggiore di 0,

•	**signal(S)**: incrementa il valore del semaforo 

In OS161 sono implementati anche i **semafori interrupt-based**, che utilizzano interruzioni per notificare ai thread i cambiamenti di stato. Questo approccio evita il consumo energetico associato alla pratica del "busy waiting", migliorando l'efficienza delle attese.

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
Noi abbiamo scelto di implementare:
+ SYS_HALT
+ SYS_EXIT
+ ...
+ ...

Le implementazioni sono state aggiunte in `src/userprog/syscall.c` e gestite nella `syscall_handler` tramite uno switch-case in base al numero di syscall.  

```c
static void syscall_handler (struct intr_frame *f) {

  int *ptr = f->esp;
  int syscall_number = *ptr;

  switch (syscall_number) {
    case SYS_HALT:
      /* ... */
      break;
		case SYS_EXIT:
      /* ... */
      break;

    /* ... */

    default:
      // Numero System Call non valido    
      break;
	}
}
```
I prototipi delle system calls implementate sono stati aggiunti in `src/userprog/syscall.h`

### SYS_HALT ###

La syscall HALT è utilizzata per terminare l'esecuzione del sistema operativo e spegnere il computer o la macchina virtuale in cui il sistema operativo è in esecuzione. In sostanza, viene utilizzata per spegnere il sistema in modo controllato e si implementa richiamando semplicemente la `shutdown_power_off()`, funzione già esistente in _Pintos_. 

```c
void halt (void){
  shutdown_power_off();
}
```

### SYS_EXIT ###

La system call EXIT è una chiamata di sistema utilizzata per terminare un processo in un sistema operativo. Quando un programma chiama la funzione `exit`, il processo corrente viene terminato e le risorse associate ad esso, come la memoria, i file aperti e altre risorse di sistema, vengono rilasciate. Prima di terminare il processo viene di solito restituito un valore di uscita al chiamante, che può essere recuperato dal processo padre o dal sistema operativo e utilizzato per valutare lo stato di terminazione del processo.

```c
void exit (int status){

// continuare

}
```
Il parametro `status` è il codice di uscita del processo che sta terminando e verrà restituito al processo genitore per indicare lo stato di terminazione del processo.


### SYS_ ###

### SYS_ ###

### SYS_ ###

### SYS_ ###
