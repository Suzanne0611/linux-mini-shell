# 🐚 MyShell

A minimal Unix-like shell implemented in C.

This project focuses on understanding process control, inter-process communication, and core Unix system programming concepts.

---

## ✨ Features

* Execute external commands using `fork()` and `execvp()`
* Support single pipe (`|`)
* Modular structure (parser / executor separation)
* Built with a Makefile

### Example

```
mysh> ls -l
mysh> ls -l | grep .c
```

---

## 🧠 Concepts Covered

* Process creation (`fork`)
* Program execution (`execvp`)
* Inter-process communication (`pipe`)
* File descriptor redirection (`dup2`)
* Argument vector handling (`char **argv`)
* Token parsing using `strtok`

---

## 🏗 Project Structure

```
src/
 ├── main.c        # Shell loop
 ├── parser.c      # Command parsing
 ├── executor.c    # Execution and pipe handling

include/
 ├── parser.h
 ├── executor.h

Makefile
```

---

## 🔧 Build

```bash
make
```

---

## ▶ Run

```bash
./mysh
```

---

## ⚙ Implementation Overview

### Execution Flow

1. Read user input
2. Detect pipe (`|`)
3. Split into left and right commands
4. Parse each command into `argv[]`
5. Create a pipe
6. Fork left child → redirect stdout
7. Fork right child → redirect stdin
8. Parent waits for both children

### Pipe Handling

* `pipe(pipefd)` creates communication channel
* `dup2()` redirects file descriptors
* `execvp()` executes commands
* Parent process closes pipe ends and waits

---

## 🔬 Debugging Challenges

* Incorrect argument type (`char ***`) caused `execvp failed`
* Pipe output buffering required flushing
* Command parsing errors resulted in incorrect executable name

## ⚠ Limitations

* Only supports single pipe
* No built-in commands (`cd`, `exit`)
* No I/O redirection (`>`, `<`)
* No background execution (`&`)
* No advanced quote handling

---

## 🚀 Future Improvements

* Multiple pipe support
* Built-in commands
* I/O redirection
* Background process handling
* Signal handling (Ctrl+C)
* Quote-aware tokenizer

---

