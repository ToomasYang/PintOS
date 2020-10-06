#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);
void check_valid_ptr(const void *ptr);
void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}
void check_valid_ptr (const void *ptr)
{
    if (!is_user_vaddr(ptr))
    {
        exit(-1);
    }

    void *check = pagedir_get_page(thread_current()->pagedir, ptr);
    if (check == NULL)
    {
        exit(-1);
    }
}

static void
syscall_handler (struct intr_frame *f UNUSED)
{
  bool ret;
  int fd;
  void* buffer;
  unsigned size;
  unsigned return_code;

  printf ("system call!\n");
  //int sys_code = *(int*) f->esp;
  int *sys_code = f->esp;
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
	check_valid_ptr(((const void*)f->esp + 1));
	ret = filesys_create(*((const char *)f->esp + 1),((unsigned)f->esp + 2));
	f->eax = ret;
    break;

  case SYS_REMOVE:
	check_valid_ptr(((const void*)f->esp + 1));
	ret = filesys_remove(*((const char *)f->esp + 1));
	f->eax = ret;
    break;

  case SYS_OPEN:
	check_valid_ptr(((const void*)f->esp + 1));
	filesys_open(*((const char *)f->esp + 1));
	f->eax = true;
    break;

  case SYS_FILESIZE:

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
