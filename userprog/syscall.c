#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void validate_user_address(int *esp, int num_args)
{
  if (!is_user_vaddr(esp+num_args))
  {
    exit(-1);
  }
  return;
}

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  void *esp = f->esp;
  validate_user_address(esp, 1);

  switch (*(int *)(esp))
  {
    case SYS_HALT:
      halt();
      break;
    case SYS_WAIT:
      esp=esp+4;
      validate_user_address(esp,1);
      f->eax=wait(*(int *)(esp));
      break;
    default:
      break;
  }
}

void halt()
{
  shutdown_power_off();
}

void exit(int status) {
  struct thread *curr = 
}