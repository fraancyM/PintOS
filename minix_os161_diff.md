# Differenze tra MINIX 3 e OS161 #
Partire da questi link

_Per la guida a MINIX 3, cliccare al seguente link: https://wiki.minix3.org/doku.php_

_Per il source code di minix: https://github.com/Stichting-MINIX-Research-Foundation/minix_

_Per la presentazione, verrà aggiunto anche un fil powerpoint_

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
_NB differenze tra scopi, architetture e compatibilità/portabilità oltre al codice scritto._

La system call FORK causa la creazione di un nuovo processo "figlio" a partire da un "padre", e il processo che si verrà a creare sarà esattamente una copia del "padre", fatta eccezzione per alcune caratteristiche, come ad esempio l'ID del "figlio" che è unico e diverso da quello del "padre". Non c'è una sostanziale differenza tra le due FORK eseguite in MINIX o OS161, possiedono lo stesso obiettivo ma differenziano su altri piccoli aspetti, quali: 
1) Architettura: OS161 è basato su MIPS, mentre MINIX è più general purpose e può essere usato su varie architetture Hardware.
2) Gestione della memoria: OS161 ha una gestione della memoria abbastanza semplificata (paginazione, visti a lezione), mentre MINIX possiede uno spazio "segmentato" (cioè distinzione/separazione tra spazio kernel ed utente, offrendo anche protezione dello spazio kernel in questo caso). Può risultare che questo modello di gestione della memoria di MINIX sia più semplice rispetto a quello di OS161 (che utilizza modelli di memoria paging più avanzata).
3) Portabilità: MINIX risulta essere più portabile rispetto ad OS161, in quanto supporta diverse architetture Hardware.

### SYS_EXEC ###

## Parte II comparazione Scheduling ##
_NB: OS161 round-robin, MINIX con multilevel queueing system (di base round-robin ma più flessibile) (es: politiche di schedulazione, flessibilità)_



## Parte III comparazione gestione di memoria ##
NB: Post-3.2 Minix supporta la virtualizzazione, il paging e il demand paging. Inoltre ha una nuova VM (virtual memory) server separato da PM.Supponiamo che i segmenti dei processi siano disposti in modo contiguo in virtual memoria ma nessuna assunzione contigua sulla memoria fisica.

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