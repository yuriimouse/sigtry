#include "sigtry.h"
#include "sigwrap.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Signal(SIGINT) {
    printf("Caught global SIGINT (Ctrl+C)\n");
}

Signal(SIGTERM) {
    printf("Caught SIGTERM — shutting down gracefully\n");
}

int main()
{
    printf("Try block starting...\n");

    Try(SIGINT, SIGTERM, SIGSEGV)
    {
        printf("Inside Try block\n");
        raise(SIGINT);
        // char *str = NULL;
        // *str = '!';
        printf("This line will not be printed if signal occurs.\n");
    }
    Catch
    {
        On(SIGINT)
        {
            printf("Caught SIGINT\n");
        }
        On(SIGTERM)
        {
            printf("Caught SIGTERM\n");
        }
        On(SIGSEGV)
        {
            printf("Caught SIGSEGV\n");
        }
        Default
        {
            printf("Caught unknown SIG %d\n", _sigtry_ctx.caught_signal);
        }
    }

    raise(SIGINT);

    printf("After Try/Catch block\n");
    return 0;
}
