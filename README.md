# ft_printf - Recreating printf()

![Score](https://img.shields.io/badge/Score-122%25-brightgreen)  
📌 **42 School - Core Curriculum Project**  

## ▌ Description
The goal of this project is to **reimplement** the standard C `printf()` function from scratch.  
This project provided a deep dive into **variadic functions**, memory management, and formatted output handling.

```mermaid
flowchart TB
    A[Caller code] --> B[ft_printf(format, ...)]
    B --> C[Init va_list<br/>va_start(args)]
    C --> D{Scan format string<br/>char by char}
    
    D -->|Regular char| E[write char to stdout]
    E --> F[Increment printed length]
    F --> D

    D -->|% found| G[Parse conversion]
    G --> H[Parse flags<br/>- 0 # + space]
    H --> I[Parse width<br/>number or *]
    I --> J[Parse precision<br/>.number or .*]
    J --> K[Parse specifier<br/>c s p d i u x X %]
    
    K --> L{Dispatch by specifier}
    
    L -->|%c| M1[Fetch arg (int)\nformat char]
    L -->|%s| M2[Fetch arg (char*)\napply precision (max len)]
    L -->|%p| M3[Fetch arg (void*)\n0x + hex]
    L -->|%d/%i| M4[Fetch arg (int)\nsign + precision]
    L -->|%u| M5[Fetch arg (unsigned)\nprecision]
    L -->|%x/%X| M6[Fetch arg (unsigned)\nhex + optional prefix (#)]
    L -->|%%| M7[Literal '%' char]
    
    M1 --> N[Build formatted output chunk]
    M2 --> N
    M3 --> N
    M4 --> N
    M5 --> N
    M6 --> N
    M7 --> N
    
    N --> O[Apply width & alignment<br/>padding: spaces/zeros]
    O --> P[write() buffer/chars]
    P --> Q[Update total length]
    Q --> D

    D -->|End of string| R[va_end(args)]
    R --> S[Return total printed length]

```


## ▌ Objectives
▸ Recode a **simplified version of `printf()`**  
▸ Learn and use **variadic functions** (`va_start`, `va_arg`, `va_end`)  
▸ Implement **multiple format specifiers** (`c`, `s`, `p`, `d`, `i`, `u`, `x`, `X`, `%`)  
▸ Handle **bonus flags**: `-`, `0`, `.`, width, `#`, `+`, and space  

## ▌ Result: **122% with Bonus**
I successfully completed all mandatory parts and **bonus features**, achieving an excellent **122%** score. 🎉

## ▌ Files
- `ft_printf.h` → Contains function prototypes and required macros  
- `libftprintf.a` → Compiled static library  
- `Makefile` → Automates compilation (`all`, `clean`, `fclean`, `re`, `bonus`)  

## ▌ Implemented Functions
### ■ **Mandatory Part**
| Specifier | Description |
|-----------|-------------|
| `%c` | Prints a single character |
| `%s` | Prints a string |
| `%p` | Prints a pointer address in hexadecimal format |
| `%d` | Prints a decimal (base 10) integer |
| `%i` | Prints an integer in base 10 |
| `%u` | Prints an unsigned decimal (base 10) integer |
| `%x` | Prints a number in lowercase hexadecimal (base 16) |
| `%X` | Prints a number in uppercase hexadecimal (base 16) |
| `%%` | Prints a percent sign `%` |

### ■ **Bonus Features**
| Feature | Description |
|---------|-------------|
| `-` | Left-align output within the field width |
| `0` | Pad numbers with leading zeros instead of spaces |
| `.` | Precision specifier for numbers and strings |
| Width | Defines a minimum field width for output |
| `#` | Adds `0x` or `0X` for hexadecimal numbers |
| `+` | Forces a plus sign (`+`) for positive numbers |
| (space) | Inserts a space before positive numbers |

## ▌ Installation & Usage
1️⃣ **Clone the repository**  
```sh
git clone https://github.com/ai-dg/ft_printf.git
cd ft_printf
```

2️⃣ Compile the library
```sh
make
```

3️⃣ Use ft_printf in another project
Include the header and link libftprintf.a:
```c
#include "ft_printf.h"

int main() {
    ft_printf("Hello, ft_printf! My number is: %d\n", 42);
    return 0;
}
```

Compile with:
```sh
gcc main.c -Wall -Wextra -Werror -L. -lftprintf -o my_program
./my_program
```

## 📜 License

This project was completed as part of the **42 School** curriculum.  
It is intended for **academic purposes only** and follows the evaluation requirements set by 42.  

Unauthorized public sharing or direct copying for **grading purposes** is discouraged.  
If you wish to use or study this code, please ensure it complies with **your school's policies**.
