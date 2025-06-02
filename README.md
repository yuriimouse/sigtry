# sigtry.h

Minimalist macro-based `Try/Catch` for Unix signals in C using `sigsetjmp` and `sigaction`.

📂 Files

- sigtry.h – Core macros (Try, Catch, On, Default, Signal)
- main.c – Example usage of local and global signal handling
- Makefile – Build with make, run with make run

🚀 Build & Run
```bash
make run
```

## 🔧 Features

- `Try(...)`, `Catch`, `On(sig)`, `Default` macros
- Supports up to 16 signals per block
- Automatically restores original signal handlers
- Lightweight: only macros and a static context
- Optional `Signal(sig)` macro with `constructor` registration

## 🧪 Example

```c
#include "sigtry.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
    Try(SIGSEGV, SIGFPE) {
        raise(SIGSEGV); // Simulate segmentation fault
    }
    Catch {
        On(SIGSEGV) {
            printf("Caught SIGSEGV\n");
        }
        On(SIGFPE) {
            printf("Caught SIGFPE\n");
        }
        Default {
            printf("Caught unknown signal: %d\n", _sigtry_ctx.caught_signal);
        }
    }
    return 0;
}
```

## 🚦 Optional Global Signal Hook
```c
Signal(SIGINT) {
    printf("Received SIGINT (Ctrl+C)\n");
}
```

## ⚠️ Limitations

- Not thread-safe (uses static context)
- Only supports Unix signals
- Max 16 signals per Try

## 📄 License

MIT License
© 2025 Yurii Prudius (GitHub)[https://github.com/yuriimouse/sigtry]
