#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "filesys/filesys.h"
#include "filesys/file.h"

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
  validate_user_address(sys_code, 1);
  
  switch(*(int*)f->esp)
  {
    case SYS_HALT:;
      shutdown_power_off();
      break;

    case SYS_EXIT:;
      exit(0);
      break;

    case SYS_EXEC:
      validate_user_address(sys_code, 1);
      process_execute(*((int *)sys_code + 1));
      break;

    case SYS_WAIT:
      process_wait((pid_t)(sys_code+1));
      break;

    case SYS_CREATE:
      exit(f->eax);
      break;

    case SYS_REMOVE:
      exit(f->eax);
      break;

    case SYS_OPEN:
      exit(f->eax);
      break;

    case SYS_FILESIZE:;
      fd = *((int*)f->esp + 1);
      return_code = file_length(fd);
      f->eax = (uint32_t) return_code;
      exit(f->eax);
      break;

    case SYS_READ:;
      fd = *((int*)f->esp + 1);
      buffer = (void*)(*((int*)f->esp + 2));
      size = *((unsigned*)f->esp + 3);
      return_code = file_read(fd, buffer, size);
      f->eax = (uint32_t) return_code;
      exit(f->eax);
      break;

    case SYS_WRITE:;
      fd = *((int*)f->esp + 1);
      buffer = (void*)(*((int*)f->esp + 2));
      size = *((unsigned*)f->esp + 3);
      return_code = file_write(fd, buffer, size);
      f->eax = (uint32_t) return_code;
      exit(f->eax);
      break;

    case SYS_SEEK:;
      fd = *((int*)f->esp + 1);
      size = *((unsigned*)f->esp + 2);
      file_seek(fd, size);
      exit(f->eax);
      break;

    case SYS_TELL:
      exit(f->eax);
      break;

    case SYS_CLOSE:
      exit(f->eax);
      break;
    }
  
  thread_exit ();
}

void exit(int status) {
  printf("%s: exit(%d)\n", thread_name(), status);
  thread_current()->exit_status = status;
  thread_exit();
  return;
}