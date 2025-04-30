#ifndef SIGWRAP_H
#define SIGWRAP_H

#include <signal.h>
#include <string.h>

#define Signal(sig) \
    static void handle_##sig(int signum __attribute__((unused))); \
    __attribute__((constructor)) \
    static void register_##sig(void) { \
        struct sigaction sa; \
        memset(&sa, 0, sizeof(sa)); \
        sa.sa_handler = handle_##sig; \
        sigemptyset(&sa.sa_mask); \
        sa.sa_flags = SA_RESTART; \
        sigaction(sig, &sa, NULL); \
    } \
    static void handle_##sig(int signum __attribute__((unused)))

#endif // SIGWRAP_H
