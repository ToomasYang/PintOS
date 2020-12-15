#ifndef USERPROG_EXCEPTION_H
#define USERPROG_EXCEPTION_H


#include <stdint.h>
#include <stdbool.h>

/* Page fault error code bits that describe the cause of the exception.  */
#define PF_P 0x1    /* 0: not-present page. 1: access rights violation. */
#define PF_W 0x2    /* 0: read, 1: write. */
#define PF_U 0x4    /* 0: kernel, 1: user process. */

void exception_init (void);
void exception_print_stats (void);


bool access_stack (const void *vaddr);
void stack_grow (const void *vaddr, uint32_t *pd);

#endif /* userprog/exception.h */
