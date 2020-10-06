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
syscall_handler (struct intr_frame *f)
{
  int fd;
  void* buffer;
  unsigned size;
  unsigned return_code;

  int *sys_code = f->esp;
  validate_user_address(esp, 1);
  
  switch(*(int*)f->esp){
    case SYS_HALT:;
      shutdown_power_off();
      break;

    case SYS_EXIT:;
      //check_addr(sys_code+1);
      thread_exit();
      break;

  case SYS_EXEC:

    break;

  case SYS_WAIT:

    break;

  case SYS_CREATE:

    break;

  case SYS_REMOVE:

    break;

  case SYS_OPEN:

    break;

  case SYS_FILESIZE:;

    fd = *((int*)f->esp + 1);
    return_code = file_length(fd);
    f->eax = (uint32_t) return_code;
    break;

  case SYS_READ:;
    fd = *((int*)f->esp + 1);
    buffer = (void*)(*((int*)f->esp + 2));
    size = *((unsigned*)f->esp + 3);
    return_code = file_read(fd, buffer, size);
    f->eax = (uint32_t) return_code;
    break;

  case SYS_WRITE:;
    fd = *((int*)f->esp + 1);
    buffer = (void*)(*((int*)f->esp + 2));
    size = *((unsigned*)f->esp + 3);
    return_code = file_write(fd, buffer, size);
    f->eax = (uint32_t) return_code;
    break;

  case SYS_SEEK:;
    fd = *((int*)f->esp + 1);
    size = *((unsigned*)f->esp + 2);
    file_seek(fd, size);
    break;

  case SYS_TELL:

    break;

  case SYS_CLOSE:

    break;
  }
  thread_exit ();
}

void exit(int status) {
  struct thread *curr = 
}