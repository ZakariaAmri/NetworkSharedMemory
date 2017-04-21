#include "var.h" 

static void tsigsegv(int sig, siginfo_t *si, void *context);

void init_sig(SOCKET flux);