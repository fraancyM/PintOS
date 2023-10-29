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

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  thread_exit ();

  switch (syscall_number)
  {

    case SYS_HALT:
      halt();
      break;
    
    case SYS_OPEN:
      if(!check (p+1) || !check(*(p+1)))
        kill();
      f->eax = open (*(p+1));
      break;
    
    default:
      // Numero System Call invalido, kill del processo
      hex_dump(p,p,64,true);
      printf("Invalid System Call number\n");
      //kill();      
      break;
  }
}

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
