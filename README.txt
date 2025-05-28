### README.txt

#### Project Title:
Recursive Descent Parser for Control Structures and Nested Expressions

#### Course:
Programming Languages and Structures (CSC 461)  
IUBAT – Spring 2025

---

#### Description:
This project implements a **recursive descent parser** in C to validate control structures (`if`, `else`, `while`) and arithmetic expressions using the provided EBNF grammar. It includes:

- Lexer to tokenize input code
- Parser functions for each non-terminal
- Error handling and syntax validation
- Replacement of special token `LTD` with the student's last 3 digits of ID

---

#### Compilation Instructions:

```bash
gcc -o parser parser.c
```

---

#### Execution Instructions:

```bash
./parser
```

The input is embedded in the `main()` function. You can modify the `sample_input` string or adapt the program to read from a file.

---

#### Example Valid Input:

```c
{
    if (a == LTD) {
        while (b < 100) {
            (a + b) * (b - LTD);
        }
    } else {
        (x + y) * (a - b);
    }
}
```

#### Example Invalid Inputs:

1. **Missing semicolon**:
```c
{
    a + b
}
```

2. **Unbalanced brackets**:
```c
{
    if (a == b) {
        a + b;
}
```

3. **Invalid identifier**:
```c
{
    3a + 5;
}
```

---

#### Notes:
- Replace the `LTD_VALUE` in `parser.c` with the last three digits of your ID.
- Extensive nested conditions and arithmetic expressions are supported.
- Error messages include token and position context for debugging.
