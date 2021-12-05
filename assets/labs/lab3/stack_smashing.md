---
layout: page
title: 'Lab 3: Stack Smashing, Part 1'
---

<style>
  strong {
    font-size: larger;
    font-variant: small-caps;
    font-weight: bold;
  }
  table {
    border: solid 1px grey;
    border-collapse: collapse;
    border-spacing: 0;
  }
  table thead th {
    background-color: grey;
    border: solid 1px grey;
    color: white;
    padding: 10px;
    text-align: left;
  }
  table tbody td {
    border: solid 1px grey;
    color: #333;
    padding: 10px;
    text-shadow: 1px 1px 1px #fff;
  }
  blockquote {
    margin-left: 2em;
    margin-right: 2em;
  }
  .red {
	color: red;
  }
  .blue {
	color: blue;
  }
  hr.style12 {
	height: 6px;
	background: url(../../images/hr-12.png) repeat-x 0 0;
    border: 0;
  }
  b {
    font-family: sans-serif;
	font-weight: 900;
  }
  .center {
	margin: auto;
	width: 100%;
	text-align: center;
  }
</style>

**Due Sunday, November 17 by 11:59pm**

In this assignment, you will construct and carry out a stack-based buffer overflow attack.  The purpose of the attack is to force the program to divulge secret information without the use of the correct password. Each part of the assignment guides you through systematically building up a buffer overflow exploit that bypasses the program's authentication mechanism.  Upon successfully exploiting the program, you will be rewarded with a secret value.

For each question, be sure to follow the instructions carefully, supplying all of the parts mentioned.  Be sure to supply a `Makefile` that produces whatever artifacts you submit.  Please make sure that your `Makefile` includes updated `all` and `clean` targets.

<hr style="border-color: purple;" />

## Requirements:

_Language_. In order to carry out the attack you will primarily write assembly code.    **Please note that all your assembly code should use Intel syntax.  Many examples on the web use AT&T syntax.  I will not accept assembly handed in using AT&T syntax.** You may also need to write small utilities in C in order to prepare your attack.  Hand in all of the utility programs you write along the way.  Note that you are specifically allowed to use utility programs provided in course handouts _without attribution_.

_Common environment_. Your code must be developed for and work on the class virtual machines.

_Special Note about SSH_.  If you plan to work on your assignment by `ssh`&#39;ing to your VM, please be aware that SSH changes your user's environment.  This means that you will very likely need to alter the offsets in your attack before you submit your assignment.  If you do not understand what I mean, this would be a good question to ask me!

_Stack Overflow_. You are permitted to refer to Stack Overflow for help, but you _must not under any circumstances copy the code you see there_.  If you find a helpful Stack Overflow post, you must attribute the source of your inspiration in a comment at the appropriate location of your code, and you must provide a URL for me to look at.  Unattributed code will be considered an honor code violation.

_Instructions for Compiling and Running_. You must supply a file called `BUILDING.md` with your submission explaining how to:

1. compile your program using your `Makefile`, and
2. how to run your programs on the command line.

_Reflection questions_. This assignment asks you to answer a few questions. You must supply the answers to these questions in a `PROBLEMS.md` file.

_Starter Code_.  For this assignment, your repository includes the program you need to exploit, some sample shellcode, and a `Makefile`.

<hr style="border-color: purple;" />

## Application code

Each of you will be supplied with a program in source code form, `prog.c`, however significant parts of the rest of the program are obscured: you are given a compiled binary and a header file only.  Nevertheless, the function of the program should be clear.

You should compile the program with the supplied `Makefile` and try running it.  For demonstration purposes, you should use the following login and password:

username: "W1234567"

password: "demodemo"

<hr style="border-color: purple;" />

## Environment set-up

Although variants of this attack are still possible on modern computers and operating systems, this particular attack is no longer feasible because of three security countermeasures: stack smashing protection (aka "stack canaries"), the non-executable stack, and address space layout randomization (ASLR).  We need to disable all of these features to perform our attack.

This lab _must_ be performed in the class virtual machine.  Your personal computer has both important architectural differences from the class VM and likely incorporates additional stack smashing countermeasures.

<hr class="style12" />

### Disabling SSP and NX

Any code you compile using `gcc` must disable _stack smashing protection_ (SSP) and the _non-executable stack_ (NX).  The supplied `Makefile` already has these flags, but here they are for posterity:

```
-fno-asynchronous-unwind-tables -fno-exceptions -fno-delete-null-pointer-checks -masm=intel -z execstack -fno-stack-protector
```

SSP works by inserting a guard value, known as a _canary_, between the return address and the rest of the stack frame.  When the function epilogue is run, this canary value is compared against the same canary stored in the program's `DATA` segment.  If the values are different, we know that the return address has likely been tampered with, and the program is terminated.

NX ("no execute") is a hardware feature now present on all modern computers.  Every virtually-addressed page has an entry in a data structure called a _page table_.  The page table maps the virtual address of a page to a physical address so that the operating system can ask the memory controller to fetch memory.  Page tables also store other information about pages, including the "NX bit."  If the NX bit is set (`== 1`) in the page table entry, the computer will refuse to execute instructions found in that page.  Modern compilers set the NX bit for `DATA`, stack, and heap segments, because valid code should only be found in the `TEXT` segment.

The above set of `gcc` flags also disables a few things that will complicate stack frames for your program (like exception handler support).

<hr class="style12" />

### Disabling ASLR

Your operating system also includes a feature called _address space layout randomization_ (ASLR).  ASLR is a security feature that changes the layout of your program from run to run.  In particular, it randomly alters the starting offsets of the call stack, heap, and library functions.  This has the effect of making it difficult to determine where things like return addresses are unless an attacker can run a program many, many times.

On your virtual machine, run:

```
$ echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
```

Your machine will prompt you to enter the password for user `cs331`.  Recall that the password is the door code for the UNIX lab (TCL 312).

You can verify that ASLR is off by running:

```
$ cat /proc/sys/kernel/randomize_va_space
```
`0` means ASLR is off. `1` or `2` means that ASLR is on.

The setting you changed above does not persist after reboots.  To disable ASLR permanently, run

```
$ sudo emacs /etc/sysctl.d/01-disable-aslr.conf
```

and when in `emacs`, add the following line:

```
kernel.randomize_va_space = 0
```

To test that you configured this setting correctly, reboot your virtual machine:

```
$ sudo shutdown -r now
```

and when it comes back up, in your terminal, run the same command we used to check ASLR above:

```
$ cat /proc/sys/kernel/randomize_va_space 
```

where `0` means that ASLR is off, and `1` or `2` means that ASLR is on.

<hr class="style12" />

### Shell Environment

Lastly, your shell's environment may make finding your addresses difficult, because if the environment changes, the program will be in a different location in memory.  Both `ssh` and `gdb` load variables into the environment, so you may discover that when you get your exploit running in `gdb`, running the program outside of `gdb` (and/or `ssh`) may not work.  When I developed my exploit, I found that the address of the exploitable buffer in `gdb` was 64 bytes lower than the address I needed without `gdb`.  There are a couple ways to address this:

1. Adjust your attack's new return address for use outside `gdb` so that you jump to the right place, or
2. Add a `NOP` sled to the beginning of your buffer and then adjust the return address so that both attacks will jump inside the sled.

How did I know how much `gdb` altered the offset?  I temporarily inserted the following handy function

```
void print_stack_pointer() {
  void* p = NULL;
  printf("%p", (void*)&p);
}
```

into `prog.c`.  Generally speaking, your exploit should work on an unmodified `prog.c`, but you may change it temporarily to figure out how to exploit it.  Remember to ensure that your exploit works on an unmodified `prog.c` before you hand it in!

<hr class="style12" />

### Step 1: Find the Vulnerability

The supplied application contains two weaknesses, which together form a vulnerability.  The first weakness is that the only thing guarding the program's sensitive data, obtained by calling the `decrypt` function, is a `student_id`, which is public knowledge.

_Reflection Q1_: What is the second weakness?  Identify the second weakness and explain how the two weaknesses combine to constitute a vulnerability.  Be sure to explain, in general terms, how an attacker might exploit this vulnerability.  Please record your answer in `PROBLEMS.md`.

<hr class="style12" />

### Step 2: Jump to a Different Function

After identifying the vulnerability, use `gdb` or simulate the program in order to find your point of attack.  You will need to craft an input that overwrites a return address left on the stack.  The function you should call is called `test2`.

Please supply this input (which is likely to contain binary characters) in two forms:

1. as a string of escaped hexadecimal literals in a file called `input1.hex`, and
1. in binary form in a file called `input1`.

I should be able to run the exploit like this:

```
cs331@ubuntu:~$ ./prog < input1
```

Crafting an input requires that you answer the following questions.  Think of these questions as a general recipe for a buffer overflow exploit.

1. Where is the return address stored in the stack frame for the function you plan to exploit?
1. Where is the buffer located that you plan to exploit?
1. How many bytes do you need to write in order to overwrite the return address?
1. What is the address you plan to put in the overwritten return address slot?
1. What order should your overwritten return address be written? Recall that x86 is [little-endian](https://en.wikipedia.org/wiki/Endianness).
1. What bytes should you write into the buffer?  If you plan to write x86 instructions into the buffer, you may find [this 32-bit instruction reference useful](http://ref.x86asm.net/coder32.html).  If you do not understand this reference, please ask!
1. Since you cannot type in certain bytes, how can you write those bytes to a _shellcode file_?
1. How does one feed a shellcode file to a program?

You will need to be able to answer all of the above questions in order to perform part 2.  See the "key skills" sections below.  When you are done, please answer the following question in detail in `PROBLEMS.md`.

_Reflection Q2_: How does your attack work?

<hr class="style12" />

#### Key Skill: How to debug an assembly program

Refer to the handout [Assembly-level debugging with GDB](../../misc/assembly_debugging_with_gdb.html) on using GDB to debug assembly.

<hr class="style12" />

#### Key Skill: How to use GDB to find a return address

Watch the video, [Finding a return address on the stack using GDB](https://youtu.be/YPfHpO9QiDk), to learn how to find the return address that you want to overwrite.  Note that I made this video a couple years ago, so the program you need to attack has changed a little.  You will need to figure out addresses on your own!

<hr class="style12" />

#### Key Skill: Creating a shellcode file

The handout, [Creating a shellcode file](../../misc/tips_and_tricks_for_exploiting_vulnerable_programs.html), explains how to create your `input1` file.

<hr class="style12" />

### Step 3: Filling a buffer with shellcode and executing it

Your second attack should first fill a buffer with shellcode and then, after overwriting a function return address, transfer control to the shellcode in the buffer.  To make this step easier, you are supplied with sample shellcode (`part1/shellcode.s`) in assembly form.  You will need to:

1. Compile the shellcode (`gcc shellcode.s -o shellcode`).  If you've done this correctly, you should be able to run the shellcode on the command line like so:
    ```
	cs331@ubuntu:~$ ./shellcode
	```
	You know that you are inside the new shell when the prompt changes to a bare `$`.  Type `exit` to return to your original shell.
1. Extract all the machine code from your compiled `shellcode` binary associated with the `main`, `main2`, and `shell` labels.
1. Now, craft an input that exploits the program, stores the shellcode in a buffer, padding with `nop` instructions if necessary, and then overwrites a return address that calls your shellcode stored in a buffer.  You should be able to run the exploit like this:
    ```
	cs331@ubuntu:~$ ./prog < input2
	```

Be sure to supply `input2` in two forms:

1. as a string of escaped hexadecimal literals in a file called `input2.hex`, and
1. in binary form in a file called `input2`.

Please answer the following question in detail in `PROBLEMS.md`.

_Reflection Q3:_ How does your attack work?

<hr style="border-color: purple;" />

## Lab Deliverables

By the start of lab, you should see a new private repository called `cs331lab03_04_stack_smashing-{USERNAME}` in your GitHub account (where `USERNAME` is replaced by your username).

For this lab, please submit the following: 

    cs331lab03_04_stack_smashing-{USERNAME}/
        README.md
        PROBLEMS.md
        part1/
            BUILDING.md
            Makefile
            enc.h
            enc.o
            prog.c
            shellcode.s
            input1
            input1.hex
            input2
            input2.hex
        part2/
            Makefile
            enc.h
            enc.o
            prog.c

You should also add additional source files if you create helper utilities.

It is always a good practice to create a small set of tests to facilitate development, and you are encouraged to do so here.

As in all labs, you will be graded on _design_, _documentation_, _style_, and _correctness_. Be sure to document your program with appropriate comments, including a general description at the top of the file, and a description of each function with pre- and post-conditions when appropriate. Also, use comments and descriptive variable names to clarify sections of the code which may not be clear to someone trying to understand it.

<hr style="border-color: purple;" />

## Submitting Your Lab

As you complete portions of this lab, you should `commit` your changes and `push` them. <u>Commit early and often.</u> When the deadline arrives, we will retrieve the latest version of your code. If you are confident that you are done, please use the phrase `"Lab Submission"` as the commit message for your final commit. If you later decide that you have more edits to make, it is OK. We will look at the latest commit before the deadline.

* <u>Be sure to push your changes to GitHub</u>.
* <u>Verify your changes on Github.</u> Navigate in your web browser to your private repository on GitHub. It should be available at [https://github.com/williams-cs/cs331lab03_04_stack_smashing-{USERNAME}](https://github.com/williams-cs/cs331lab03_04_stack_smashing-{USERNAME}). You should see all changes reflected in the files that you `push`. If not, go back and make sure you have both committed and pushed.

We will know that the files are yours because they are in _your_ `git` repository. <u>Do not include identifying information in the code that you submit.</u> We grade your lab programs anonymously to avoid bias. In your `README.md` file, please cite any sources of inspiration or collaboration (e.g., conversations with classmates). We take the honor code very seriously, and so should you. Please include the statement `"I am the sole author of the work in this repository."` in the comments at the top of your files. 

<hr style="border-color: purple;" />

## The squeaky wheel gets the grease

I am always looking to make my labs better.  For one bonus point, please submit answers to the following questions using the [anonymous feedback form](http://barowy.net/cs331f19/) for this class:

1. How difficult was this assignment on a scale from 1 to 5 (1 = super easy, ..., 5 = super hard)?
1. Did this assignment help you to understand stack smashing?
1. If you could tell your past self something about this assignment, what would it be?
1. Your name, for the bonus point (if you want it).

<hr style="border-color: purple;" />

## Bonus: Mistakes

Did you find any mistakes in this writeup?  If so, add a file called `MISTAKES.md` to your GitHub repository and describe the mistakes using bullets.  For example, you might write

    * Where it says "bypass the auxiliary sensor" you should have written "bypass the primary sensor".
	* You spelled "college" wrong ("collej").
	* A quadrilateral has four edges, not "too many to count" as you state.
	
You will receive one bonus point on this assignment for each mistake I am able to validate.

<hr style="border-color: purple;" />
