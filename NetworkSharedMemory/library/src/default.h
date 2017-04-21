#include "var.h" 

#ifndef DEFAULT_H_
#define DEFAULT_H_

static void tsigsegv(int sig, siginfo_t *si, void *context);

void init_sig(SOCKET flux);

#endif
