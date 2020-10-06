#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

typedef int pid_t;

void validate_user_address(int *esp, int num_args);

void syscall_init (void);

void exit(int status);

#endif /* userprog/syscall.h */
