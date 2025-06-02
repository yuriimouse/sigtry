// main.c
#include "sigtry.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Register global signal handlers
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
        raise(SIGINT); // Local SIGINT inside Try block
        // char *str = NULL;
        // *str = '!'; // Uncomment to test SIGSEGV
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

    raise(SIGINT); // Global SIGINT (outside Try)

    printf("After Try/Catch block\n");
    printf("Now sleeping... Press Ctrl+C to test global SIGINT handler.\n");
    sleep(5);

    return 0;
}
