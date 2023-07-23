# Differenze tra MINIX 3 e OS161 #


_Per la guida a MINIX 3, cliccare al seguente link: https://wiki.minix3.org/doku.php_

_Per il source code di minix: https://github.com/Stichting-MINIX-Research-Foundation/minix_

Argomenti /RICERCA COMPARATIVA/:
- MINIX 3 Kernel API (important for SYSTEM CALLS and MEMORY MANAGEMENT): https://wiki.minix3.org/doku.php?id=developersguide:kernelapi
- Memomory grant (transfer datas): https://wiki.minix3.org/doku.php?id=developersguide:memorygrants
- Message passing (a sort of IPC): https://wiki.minix3.org/doku.php?id=developersguide:messagepassing
- Memory management: https://lass.cs.umass.edu/~shenoy/courses/spring20/lectures/lecture11-scribe.pdf (minix post 3.2) oppure https://wiki.minix3.org/doku.php?id=developersguide:vminternals
- User scheduling (processes): https://wiki.minix3.org/doku.php?id=releases:3.2.1:developersguide:userspace-scheduling&s[]=scheduling

Argomenti contro-parte OS:
- System calls: https://ops-class.org/man/syscall/fork.html
- Processes scheduling: http://jhshi.me/2012/03/18/os161-process-scheduling/index.html

Reminder dell'architettura: 

- OS161: OS161 è progettato come un sistema operativo monolitico, dove tutti i componenti chiave, come il kernel e i driver dei dispositivi, risiedono in uno spazio di indirizzamento comune.
- MINIX: MINIX, nelle sue prime versioni, era anche un sistema operativo monolitico, ma con l'evoluzione verso MINIX 3, si è adottata un'architettura a microkernel. In un microkernel, le funzionalità del sistema operativo sono suddivise in moduli separati che vengono eseguiti nello spazio utente, riducendo così la complessità del kernel e aumentando la sicurezza e la stabilità.

### Parte I comparazione System Calls ###

Le principali system calls che caratterizzano entrambi i sistemi operativi sono (per analisi comparativa):
- SYS_FORK
- SYS_EXEC
- SYS_EXIT
- SYS_CLEAR
- SYS_KILL
- SYS_REBOOT
- SYS_WAITPID

write, read and pipe ???

SYS_SETGRANT /* get/set own parameters */ ???

... (comparazioni possono essere fatte su fork, exec, exit, abort, waitpid, kill, in totale 6 system calls)

### Parte II comparazione Scheduling ###
NB: entrambi round-robin ma con piccole differenze tra loro

### Parte III comparazione gestione di memoria ###
NB: Post-3.2 Minix supporta la virtualizzazione, il paging e il demand paging. Inoltre ha una nuova VM (virtual memory) server separato da PM.Supponiamo che i segmenti dei processi siano disposti in modo contiguo in virtual memoria ma nessuna assunzione contigua sulla memoria fisica.
