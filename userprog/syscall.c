#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

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
    case SYS_EXEC:
      break;
    default:
      break;
  }

void halt()
{
  shutdown_power_off();
}