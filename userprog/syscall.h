#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void validate_user_address(int *esp, int num_args);

void syscall_init (void);

void halt(void);
void exit(int status);

#endif /* userprog/syscall.h */
