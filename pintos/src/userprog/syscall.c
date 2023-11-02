#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

//Aggiunte
#include "process.h"
#include "pagedir.h"
#include "threads/vaddr.h"
#include "devices/shutdown.h"
#include "filesys/filesys.h"

static void syscall_handler (struct intr_frame *);
void halt(void);
int open(const char * file);
void exit(int status);

// Funzione per verificare se l'indirizzo è valido
bool check (void *addr);

void
syscall_init (void)
{
  lock_init(&file_lock); //Inizializzazione per sincronizzare l'accesso a risorse condivise ed evitare race conditions.
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f)
{
  int *ptr = f->esp;
  if(check(ptr) == false)
    exit(-1);

  int syscall_number = *ptr;
  ASSERT(sizeof(syscall_number) == 4 ); // x86

  switch (syscall_number){

    case SYS_HALT:
      halt();
      break;

    case SYS_EXIT:
        if(check(ptr+1)==false)
            exit(-1);

        exit(*(ptr+1));
        break;

    case SYS_OPEN:
      if(!check (ptr+1) || !check(*(ptr+1)))
        exit(-1);
      f->eax = open (*(ptr+1));
      break;

    default:
      // Numero System Call invalido, kill del processo
      printf("Invalid System Call number\n");
      exit(-1);
      break;
  }
}


/* Implementazioni system calls */


/* Shutdown Pintos */
void halt (void){
  shutdown_power_off(); //Funzione già esistente in Pintos
}

int open(const char * file)
{
  // finire di implementare
  lock_acquire(&file_lock);  // acquisco il lock
  struct file *file_p = filesys_open(file);   // apertura del file
  lock_release(&file_lock);  // rilascio del lock

  if(file_p == NULL)  // controllo se il file è stato aperto con successos
    return -1;

  struct file_desc * file_desc = malloc (sizeof(struct file_desc)); // alloco dinamicamente una struttura dati che tiene traccia delle informazioni relative al file aperto
  file_desc->fd = ++thread_current()->fd_count;  // viene assegnato un numero univoco (a ogni file aperto da questo thread)
  file_desc->fp = file_p;  // assegno il puntatore del file
  list_push_front(&thread_current()->file_list, &file_desc->elem);  // inserisco il file nella lista dei file aperti dal thread

  return file_desc->fd;  // restituisco il numero univoco (descrittore)
}

void exit (int status){

    /* Per gestire il processo di terminazione di un thread,
    devo memorizzare il valore di uscita, notificare il processo genitore (se in attesa),
    e terminare il thread corrente */

    /* Memorizzo il valore di uscita del thread che può essere recuperato dal processo genitore.*/
    struct thread *cur = thread_current ();
    cur->exit_code = status;
    //printf("%s: exit(%d)\n", cur->name, status);

    struct thread *parent_thread = cur->parent;
    struct child *children = get_child(cur->tid,parent_thread);

    if(children->id == cur->tid ){
        children->used = 1;
        children->ret_val = status; //Valore di ritorno del figlio

        /* Se il genitore sta aspettando il completamento del thread figlio,
        occorre svegliare il genitore con sema_up e notificare che il figlio ha terminato
        per consentirgli di continuare l'esecuzione.
        waiton_child è l'id del thread in attesa */
        if(parent_thread->waiton_child == cur->tid)
            sema_up(&parent_thread->child_sem);
    }

    //il thread ha completato la sua esecuzione, posso terminare e liberare le risorse associate al thread
    thread_exit();
}

// Funzione per verificare se l'indirizzo è valido
bool check(void *addr) {

    if (is_user_vaddr(addr) == true &&
        pagedir_get_page(thread_current()->pagedir,addr)!=NULL)
        return true;
    else
        return false;
}
