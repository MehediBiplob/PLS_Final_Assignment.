# Recursive Descent Parser with LTD Replacement

## Course Information
- **Course Title:** Programming Languages and Structures
- **Course Code:** CSC 461
- **Instructor:** Md Nazir Ahmed, Lecturer, Deptartment of CSE, IUBAT
- **Student Name:** Md. Latifur Rahman
- **Student ID:** 22103280
- **Section:** E
- **Semester:** Spring 2025

---

## Assignment Overview

This project implements a **Recursive Descent Parser** in C that can:
- Parse and validate simple control structures (`if`, `else`, `while`)
- Handle arithmetic expressions with nested brackets
- Replace a special token `LTD` with the last three digits of my student ID (**280**) at runtime
- Simulate a basic front-end compiler parser with lexical analysis and syntax validation

---

## Grammar Used (EBNF)

```
<program> → <block>
<block> → { <statement> }
<statement> → <if-statement> | <while-statement> | <assignment>
<if-statement> → if ( <condition> ) <block> [ else <block> ]
<while-statement> → while ( <condition> ) <block>
<assignment> → <identifier> = <expression> ;
<condition> → <expression> <relational-operator> <expression>
<relational-operator> → == | != | < | > | <= | >=
<expression> → <term> { (+ | -) <term> }
<term> → <factor> { (* | /) <factor> }
<factor> → <number> | <identifier> | LTD | ( <expression> )
```

---

## Features

- Modular lexer and parser design
- Supports nested `if`-`else` and `while` statements
- Arithmetic expressions and assignments
- Replaces `LTD` with **280** during runtime
- Error handling:
  - Unbalanced brackets
  - Invalid tokens
  - Missing semicolons
  - Unexpected syntax

---

## Compilation Instructions

To compile the `parser.c` source file, follow these steps:

### Requirements
- Must have a C compiler installed (e.g., GCC)
- Terminal/command prompt should have access to the file directory

### Compile Command
```bash
gcc parser.c -o parser
```
on Windows, may use:
```bash
gcc parser.c -o parser.exe
```

### Notes:
- `parser.c` is the name of the source file.
- `-o parser` creates an executable named `parser`.

### If Get Compilation Errors:
- Make sure all braces `{}` and parentheses `()` are balanced.
- Ensure the copied code is fully pasted.
- Double-check semicolons and syntax.

---

## Runtime Instructions

### Step-by-Step Execution

1. Open the terminal or command prompt.
2. Navigate to the folder containing the compiled executable.
3. Run the executable:
```bash
./parser
```

4. Enter the code block line by line.
5. Type `~` on a new line to indicate **end of input**.

### Example Runtime Flow

**Input:**
```c
{
    x = LTD + 10;
}
~
```

**Output:**
```
[FACTOR: LTD -> 280]
[TERM OP: +]
Program parsed successfully.
```

---

### ❌ Common Runtime Mistakes & Fixes

| Issue                         | Fix                                                            |
|------------------------------|----------------------------------------------------------------|
| Program hangs                | You forgot to enter `~` at the end                            |
| Unexpected token             | Check for typo, missing semicolon, or invalid identifier      |
| Unbalanced brackets          | Ensure all `{}`, `()` are properly opened and closed          |
| Invalid symbol like `$`      | Remove it — only allowed symbols: `+`, `-`, `*`, `/`, etc.     |
| Unexpected EOF               | Likely missing closing brace or incomplete block              |

---

## Test Cases

### Valid Test Case 1

**Input:**
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
~
```
**Explanation:**  
This code uses an `if-else` structure with a nested `while` loop. Each control structure has valid syntax, and the expressions inside are arithmetic expressions with brackets. `LTD` is correctly used as a token and replaced with `280` at runtime. All semicolons and braces are properly matched.

**Expected Output:**  
```
Program parsed successfully.
```

---

### Valid Test Case 2

**Input:**
```c
{
    if (a == LTD) {
        b = (LTD * 5) + 1;
    }
}
```
**Explanation:**  
This block includes an `if` statement where the condition uses a valid identifier `a` and `LTD`, followed by a correct block with assignment. Nested expressions like `(LTD * 5)` are valid.

**Expected Output:**
```
[FACTOR: LTD -> 280]
[TERM OP: *]
[TERM OP: +]
Program parsed successfully.
```

---

### Invalid Test Case 1 – Missing Semicolon

**Input:**
```c
{
    a + b
}
```
**Explanation:**  
This block contains a valid arithmetic expression, but it is missing the required `;` at the end. The parser will produce a syntax error: “Expected token ;”.

---

### Invalid Test Case 2 – Mismatched Brackets

**Input:**
```c
{
    if (a == b) {
        a + b;
}
```
**Explanation:**  
The `if` block is not closed properly. The closing brace `}` is missing. This will result in an error such as “Expected token }”.

---

### Invalid Test Case 3 – Invalid Identifier

**Input:**
```c
{
    3a + 5;
}
```
**Explanation:**  
Identifiers must begin with a letter. `3a` is an invalid identifier, and the lexer will report it as an invalid token.

---


## Files to be Submitted

- Cover Page (printed)
- Handwritten Explanation
- `parser.c` – Main source code (printed)
- `README.md` – This document (printed)
- Test Case Output – valid + invalid (printed)
