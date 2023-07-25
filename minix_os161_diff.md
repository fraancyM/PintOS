# Differenze tra MINIX 3 e OS161 #
Partire da questi link

_Per la guida a MINIX 3, cliccare al seguente link: https://wiki.minix3.org/doku.php_

_Per il source code di minix: https://github.com/Stichting-MINIX-Research-Foundation/minix_

_Per la presentazione, verrà aggiunto anche un file powerpoint_

Argomenti /RICERCA COMPARATIVA/:
- MINIX 3 Kernel API (important for SYSTEM CALLS and MEMORY MANAGEMENT): https://wiki.minix3.org/doku.php?id=developersguide:kernelapi
- Memomory grant (transfer datas): https://wiki.minix3.org/doku.php?id=developersguide:memorygrants
- Message passing (a sort of IPC): https://wiki.minix3.org/doku.php?id=developersguide:messagepassing
- Memory management: https://lass.cs.umass.edu/~shenoy/courses/spring20/lectures/lecture11-scribe.pdf (minix post 3.2) oppure https://wiki.minix3.org/doku.php?id=developersguide:vminternals
- Scheduling (processes): https://wiki.minix3.org/doku.php?id=releases:3.2.1:developersguide:userspace-scheduling&s[]=scheduling oppure https://minixnitc.github.io/scheduling.html (affidabile)

Argomenti contro-parte OS:
- System calls: https://ops-class.org/man/syscall/
- Processes scheduling: http://jhshi.me/2012/03/18/os161-process-scheduling/index.html

Reminder dell'architettura: 

- OS161: OS161 è progettato come un sistema operativo monolitico, dove tutti i componenti chiave, come il kernel e i driver dei dispositivi, risiedono in uno spazio di indirizzamento comune.
- MINIX: MINIX, nelle sue prime versioni, era anche un sistema operativo monolitico, ma con l'evoluzione verso MINIX 3, si è adottata un'architettura a microkernel. In un microkernel, le funzionalità del sistema operativo sono suddivise in moduli separati che vengono eseguiti nello spazio utente, riducendo così la complessità del kernel e aumentando la sicurezza e la stabilità.

## Parte I comparazione System Calls ##

Alcune delle principali system calls che caratterizzano entrambi i sistemi operativi sono (per analisi comparativa):
- SYS_FORK / https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/master/minix/kernel/system/do_fork.c#L26
- SYS_EXEC / https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/master/minix/kernel/system/do_exec.c
- SYS_EXIT / https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/master/minix/kernel/system/do_exit.c
- SYS_CLEAR / https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/master/minix/kernel/system/do_clear.c
- SYS_KILL / https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/master/minix/kernel/system/do_kill.c

- SYS_REBOOT / https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/4db99f4012570a577414fe2a43697b2f239b699e/minix/servers/pm/misc.c#L199
- SYS_WAITPID / https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/4db99f4012570a577414fe2a43697b2f239b699e/minix/servers/pm/forkexit.c#L475
 etc...

... (comparazioni possono essere fatte su fork, exec, exit, abort, waitpid, kill ...)

### SYS_FORK ###

La system call FORK causa la creazione di un nuovo processo "figlio" a partire da un "padre", e il processo che si verrà a creare sarà esattamente una copia del "padre", fatta eccezzione per alcune caratteristiche, come ad esempio l'ID del "figlio" che è unico e diverso da quello del "padre". Non c'è una sostanziale differenza tra le due FORK eseguite in MINIX o OS161, possiedono lo stesso obiettivo ma differenziano su altri piccoli aspetti, quali: 
1) Architettura: OS161 è basato su MIPS, mentre MINIX è più general purpose e può essere usato su varie architetture Hardware.
2) Gestione della memoria: OS161 ha una gestione della memoria abbastanza semplificata (paginazione, visti a lezione), mentre MINIX possiede uno spazio "segmentato" (cioè distinzione/separazione tra spazio kernel ed utente, offrendo anche protezione dello spazio kernel in questo caso). Può risultare che questo modello di gestione della memoria di MINIX sia più semplice rispetto a quello di OS161 (che utilizza modelli di memoria paging più avanzata).
3) Portabilità: MINIX risulta essere più portabile rispetto ad OS161, in quanto supporta diverse architetture Hardware. 
 
 + da aggiungere la dichiarazione delle due funzioni FORK

### SYS_EXEC ###


### SYS_EXIT ###


### SYS_CLEAR ###


### SYS_KILL ###

## Parte II comparazione Scheduling ##
_NB: OS161 round-robin, MINIX con multilevel queueing system (di base round-robin ma più flessibile) (es: politiche di schedulazione, flessibilità)_

**Politiche di Scheduling**
Le politiche di scheduling di OS161 e MINIX 3 sono diverse poichè i due sistemi operativi hanno scopi e approcci diversi rispetto alla gestione dello scheduling dei processi.
In particolare, OS161 utilizza una politica di scheduling semplice e predefinita basata sull'approccio Round Robin (RR), in cui ogni processo riceve un quantum di tempo assegnato e, quando il quantum scade, il processo viene messo in coda e viene eseguito il successivo processo pronto. Questo ciclo di esecuzione continua finchè ci sono processi nella coda pronti ad essere eseguiti. Inoltre, in OS161 non è possibile implementare politiche di scheduling personalizzate poiché l'allocazione del tempo della CPU è principalmente gestita dal kernel per ragioni di sicurezza e stabilità.
MINIX invece utilizza una politica di scheduling più sofisticata, chiamata Multilevel Feedback Queue (MFQ). L'algoritmo MFQ prevede l'esistenza di più code con diversi livelli di priorità. I processi vengono inizialmente inseriti nella coda di priorità più alta e se un processo utilizza tutto il suo quantum di tempo senza terminare, viene degradato nella coda di priorità inferiore. D'altra parte, se un processo è bloccato o termina prima di utilizzare tutto il suo quantum, viene promosso alla coda di priorità superiore. Questa politica offre maggiore flessibilità e consente agli sviluppatori di definire algoritmi di scheduling specifici per gruppi di processi con esigenze diverse o applicazioni particolari.

_to be continued_


## Parte III comparazione gestione di memoria ##
_NB: Post-3.2 Minix supporta la virtualizzazione, il paging e il demand paging. Inoltre ha una nuova VM (virtual memory) server separato da PM.Supponiamo che i segmenti dei processi siano disposti in modo contiguo in virtual memoria ma nessuna assunzione contigua sulla memoria fisica._

_Premessa: il sistema operativo MINIX è basato su architettura a Microkernel, il che semplifica la gestione del kernel e sposta, di conseguenza, le funzionalità più complesse in spazi utente chiamati "server" (es. gestione dei file system, gestione memoria virtuale etc...). Si ricorda anche che MINIX pre-3.1 non supporta paginazione (i processi sono allocati in maniera contigua all'interno della memoria), mentre dalla versione 3.2 supporta questa caratteristica._

Andiamo adesso ad approfondire le differenze/somiglianze sulla gestione di memoria tra MINIX e OS161. Dalla versione 3.2 di MINIX, questo sistema operativo supporta la paginazione, la memoria virtuale e la paginazione su richiesta (paging, virtualization and demand paging), di conseguenza viene introdotto un nuovo "server" VM (virtual memory) per gestire la memoria virtuale: ogni processo ha segmenti allocati in modo contiguo nello spazio di indirizzamento virtuale, ma non vi sono assunzioni di contiguità sulla memoria fisica. Ne deriva il fatto che sia MINIX, sia OS161 hanno supporto per Paging e Memoria virtuale (che quindi consente di separare lo spazio di indirizzamento virtuale di un processo dalla memoria fisica, permettendo maggiore isolamento e protezione dei processi).

Si può, inoltre, evincere che entrambi i sistemi operativi utilizzino le tabelle (Page table) per gestire la paginazione e mappare gli indirizzi virtuali degli utenti agli indirizzi fisici della memoria, oltre che l'uso di strutture dati come Bitmap o Linked List. Anche per quanto riguarda gli algoritmi di allocazione (della memoria fisica), entrambi i sistemi operativi condividono certe soluzioni, quali: First-fit, Best-fit, Worst-fit (MINIX possiede anche Next-fit e Quick-fit); si ricorda, però, che queste soluzioni non riguardano le ultime versioni di MINIX (post-3.2), le quali usano "holes and allocation", ovvero buchi e allocazione nello spazio di indirizzamento virtuale (quindi allocazione anche NON contigua nello spazio d'indirizzamento virtuale).

Passando alla gestione degli errori (quindi i cosiddetti Page fault), entrambi i sistemi operativi gestiscono questo fenomeno in maniera simile. Distiguiamo due casi (della gestione) per MINIX: 

1) Quando un processo tenta di accedere a una parte della memoria virtuale che non è ancora stata mappata a una pagina fisica. In questo caso, il server VM può allocare una nuova pagina fisica e mapparla nello spazio di indirizzamento del processo.

2) Quando un processo tenta di accedere a una parte della memoria virtuale mappata a un file. In questo caso, il server VM, prima di tutto, verifica nella cache delle pagine per vedere se la pagina richiesta è presente. Se è presente, la pagina viene caricata direttamente dalla cache alla memoria fisica. In caso contrario, il server VM dovrà consultare il file system (VFS - Virtual File System) per recuperare la pagina richiesta dal file sorgente e caricarla nella memoria fisica.

to be continued... ( Call Stucture + PM Server )

## (TBD) Parte IV implementazione di nuove funzionalità  ##
Scelte tre:

1) Scheduler più avanzato: Se OS161 ha un scheduler con politiche di pianificazione avanzate (ad esempio, algoritmi di scheduling come Round Robin, Priority-based, etc.), potresti considerare di implementare una versione più avanzata di scheduler in MINIX per ottimizzare l'allocazione delle risorse del sistema.

2) Gestione della memoria fisica migliorata: Esplorare l'implementazione di una gestione della memoria fisica più efficiente o adottare meccanismi di paginazione avanzati presenti in OS161 per ottimizzare l'allocazione e la gestione della memoria fisica.

3) File System più avanzato: Se OS161 ha un file system con funzionalità aggiuntive o prestazioni migliorate, potresti lavorare per implementare un nuovo file system o estendere quello esistente in MINIX per offrire funzionalità avanzate.

4) Miglioramento delle prestazioni: Potresti analizzare il codice e l'implementazione di MINIX per identificare aree che potrebbero essere ottimizzate per migliorare le prestazioni generali del sistema operativo.

5) Sicurezza e Protezione: Aumentare le politiche di sicurezza di MINIX 3.0

6) Gestione dei dispositivi: Migliorare la gestione dei dispositivi in MINIX 3.0 (più semplice rispetto ad OS161)

7) Interfacce di Sistema: Aggiungere nuove interfacce di sistema

8) Supporto per i segnali: Implementare un sistema di gestione dei segnali più completo o estendere le funzionalità esistenti per consentire una maggiore flessibilità nel trattamento dei segnali da parte dei processi.