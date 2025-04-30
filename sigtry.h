#ifndef SIGTRY_H
#define SIGTRY_H

#define _GNU_SOURCE
#include <signal.h>
#include <setjmp.h>
#include <stddef.h>

#define SIGTRY_MAX_SIGNALS 16

typedef struct {
    sigjmp_buf env;
    int caught_signal;
    int watched_signals[SIGTRY_MAX_SIGNALS];
    struct sigaction old_actions[SIGTRY_MAX_SIGNALS];
    size_t num_signals;
} sigtry_context_t;

static sigtry_context_t _sigtry_ctx;

static void _sigtry_dispatcher(int sig) {
    _sigtry_ctx.caught_signal = sig;
    siglongjmp(_sigtry_ctx.env, 1);
}

#define Try(...) \
    do { \
        _sigtry_ctx.num_signals = 0; \
        int _sigs[] = {__VA_ARGS__}; \
        size_t _sig_count = sizeof(_sigs) / sizeof(int); \
        for (size_t _i = 0; _i < _sig_count && _i < SIGTRY_MAX_SIGNALS; ++_i) { \
            _sigtry_ctx.watched_signals[_i] = _sigs[_i]; \
            struct sigaction _new_action = {0}; \
            _new_action.sa_handler = _sigtry_dispatcher; \
            sigemptyset(&_new_action.sa_mask); \
            _new_action.sa_flags = 0; \
            sigaction(_sigs[_i], &_new_action, &_sigtry_ctx.old_actions[_i]); \
            _sigtry_ctx.num_signals++; \
        } \
        if (sigsetjmp(_sigtry_ctx.env, 1) == 0)

#define Catch \
        else \
            for (size_t _j = 0; _j < _sigtry_ctx.num_signals; ++_j) \
                sigaction(_sigtry_ctx.watched_signals[_j], &_sigtry_ctx.old_actions[_j], NULL); \
    } while (0);

#define On(sig) \
    if (_sigtry_ctx.caught_signal == (sig))

#endif // SIGTRY_H
