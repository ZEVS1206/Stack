# Stack Realization

![C](https://img.shields.io/badge/language-C-blue.svg)
![G++](https://img.shields.io/badge/compiler-g++-orange.svg)
![Makefile](https://img.shields.io/badge/build-Makefile-green.svg)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)
![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)

## 📖 About the Project

**Stack** is one of the most famous and important structure in all programming languages. So, the aim of this **educational project** was to create realization of this container and defend it with using different methods of **secure developing**.
### ⚠️ Important fact
For **educational purposes**, the repository version of the program contains several **vulnerabilities** so that anyone can download it and try their hand at finding them. The description of vulnerabilities will be in the end of README:).

---

## ✨ Features

* Used only **simple functional** of C-language
* Created auxiliary function **recalloc** for simple use of stack
* Used several methods for defending programm
* This realization can be used as a separate library(when you correct vulnerabilities:))!

---

## 🛠 Technologies Used

* **C**
* **g++**
* **Makefile**
* **Standard Library**
* **Methods of saving data(description below)**

---

## 📂 Project Structure

```
Stack/
│
├── source/         # Source files
├── include/        # Header files
├── build/          # Compiled binaries
├── Makefile        # Build configuration
└── README.md
```

---

## Desciption of structure

### Key features of implementation

So, this programm has all basic opportunities of standart container stack.
You can use:
```
stack_push
stack_pop
stack_dump
stack_check
stack_constructor
stack_destructor
```

Also it has **Debug mode**. If you want to use it, you need to:
```
//#define DEBUG
//#define FULL_DEBUG
```
Use one of this macros. Also you can change:
```
const float COEFFICIENT = 2;
```
This coefficient used by stack to increase or decrease its size.
Realization has own system of errors, so you can get decryption of error code by the function:
```
const char *get_error(Errors error);
```

### Methods of defending stack

So, here I will give some information about methods, which I used for security of stack.

#### Canaries!!!

Canaries is **fundamental tool** of protecting data. Usually it uses for defending some structures with a linear representation model that is, those that are stored in memory as an array of consecutive blocks, which move sequentially. In the stack canaries used to protect all internal information of structure(data, size, hash and etc).

```
struct MyStack
{
    Stack_Canary_t LEFT_CANARY;
    //some internal information
    Stack_Canary_t RIGHT_CANARY;
};
```

#### Hash!!!

Hash is one of the most famous principle in the programming! Usually, we use hash to check data integrity and immutability. The basic concept is that a function is selected that accepts an array of data and returns a number obtained according to certain rules.Thus, in most cases, any, even the most minor, changes in the information array are easily tracked. Of cause this way also has minus, because it can be possible, that for different data arrays hash function will give same result(it called **collision**).
The implementation uses a variation of djb2

---

## ⚙️ Build and Run


### Clone the repository

```bash
git clone https://github.com/ZEVS1206/Stack.git
cd Stack
```

### Prepare main
You can create your **own** main in the folder **source** or use my *main.cpp* for create test programm

### Build the project

```bash
make
```

### Run

```bash
make run
```

## Description of vulnerabilities

Here I will discuss three vulnerabilities, which I know from my programm). Of course, you can try to find another more).

### Vulnerability of beginner

The problem is that in some methods I intentionally do not check whether a null pointer is passed to the function, so the program simply dies.

For example:
```
Errors stack_push(struct MyStack *stack, Stack_Elem_t element)
{
    //Here we need to add check of *stack
    hash_check(stack, stack->capacity);
....
```

### Vulnerabilities of pro)

#### First

This vulnerability lies in the fact that the fields of the structure can be directly accessed from anywhere, so despite the fact that for the integrity and prevention of data changes in each method, the hash is checked, the information can be changed!

For example:

```
stack.data[stak.size - 1] = 13;
stack.hash_result = hash(&stack, stack.capacity);
```

#### Second
In fact, it is similar to the previous one. The hashing function should not be available to anyone. We need to use **static**.

---

## 📚 Educational Purpose

This project was created as part of a programming course to practice:

* work with structures and **enum**
* memory management
* methods of protecting data
* using of macros for changing the behaviour of program

---

## 📄 License

This project is licensed under the **MIT License**.

---

## 👨‍💻 Author

This project is a part of [Ilya Dedinskiy's](https://vk.com/ded32_ru) course of C-language!

Created by [Zevs](https://github.com/ZEVS1206)
