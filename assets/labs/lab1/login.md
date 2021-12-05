---
layout: page
title: 'Lab 1: Login Security'
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
This lab explores the "hardening" of a program against a given attack.  You will begin by writing a simple program. Next, you will try to circumvent protections against the program. Then you will strengthen this program, and so on.  In real life, programs often undergo similar enhancements as security vulnerabilities are reported or exploited. This back-and-forth between hardening and exploitation is a form of technological escalation often referred to as an "arms race."

The application we focus on in this lab is a program you have used many times before, but probably never really thought much about: `login`.  A `login` program controls access to a resource (like a user account on your machine) and therefore must have at least some privileged access to your system.  As a result, bugs in a `login` program can lead to serious vulnerabilities.

**NOTE**: This assignment also functions as a warm-up for C programming.  Although none of the topics in this course require skills you have not already been exposed to (assembly/C/Java programming), you may find that some of your programming skills are a little rusty or underdeveloped.  If you struggle with this or any other lab, make a note of the problem areas, and please come see me for help.  Computer security often exploits subtle weaknesses in computer systems.  It is essential that you develop an awareness of the limits of your knowledge, and that you seek to rectify them. If you find this lab too easy---great!  That means that you're ready for the next one.

<hr style="border-color: purple;" />

## Virtual Machine Setup and Configuration

Before you start this lab, you will need to [download and configure the class VM](../../misc/vmware_howto.html).  This VM can be run using the VMWare Player application, which is already installed on our UNIX lab machines in TCL 312.  This software can be [downloaded for free](https://www.vmware.com/products/workstation-player/workstation-player-evaluation.html) for Linux and Windows.  If you use the MacOS, you will need to [purchase VMWare Fusion](https://www.vmware.com/products/fusion.html) (or just use our UNIX lab machines).

<hr style="border-color: purple;" />

## Finding Documentation for C Functions

In Linux and in other UNIX-like operating systems, you can find documentation on all system and C standard library calls using the `man` command.  `man` is short for "manual", and it is broken into the following 9 sections:

```
       1   Executable programs or shell commands
       2   System calls (functions provided by the kernel)
       3   Library calls (functions within program libraries)
       4   Special files (usually found in /dev)
       5   File formats and conventions eg /etc/passwd
       6   Games
       7   Miscellaneous (including macro packages and conventions), e.g. man(7), groff(7)
       8   System administration commands (usually only for root)
       9   Kernel routines [Non standard]
```

For example, if I want to obtain documentation for the `fgets` function, which is a part of the C standard library (aka `libc`), I would type the following command into my shell:

```
$ man 3 fgets
```
If you don't know what section a command or function might belong to, you can use the `apropos` command:

```
$ apropos fgets
fgets (3)            - input of characters and strings
fgets_unlocked (3)   - nonlocking stdio functions
fgetspent (3)        - get shadow password file entry
fgetspent_r (3)      - get shadow password file entry
```
The output says that the `fgets` function is in section `3`, which is what we used above.

Becoming familiar with `man` is your first step toward becoming a competent systems programmer.  If you want to know how to use a function, you should turn to it first, since there are sometimes subtle distinctions between the same function call from one operating system to the next.  Only the `man` page installed on your own computer is guaranteed to be correct for your use (in other words, sometimes Google is wrong!).

<hr style="border-color: purple;" />

## Starter Code

This assignment comes with a small set of libraries and a `Makefile` for you to use.  You will need to modify the `Makefile` as a part of this assignment, but you need not modify any of the provided libraries.

The starter code contains the following files:

|File|Purpose|
|----|-------|
| `password.db` | A password database. |
| `console.c` | File that contains the `fgets_wrapper` helper method. |
| `console.h` | Header for `console.c`. |
| `database.c` | Library for reading the `password.db` database. |
| `database.h` | Header for `database.c`. |
| `ptyhelper.c` | Library for working with pseudoterminals. |
| `ptyhelper.h` | Header for `ptyhelper.c` |

You will need to add additional files as specified in each part below.

You are strongly advised to use the `fgets_wrapper` function provided in the `console` library to obtain user input.

<hr style="border-color: purple;" />

### Password Database

The password database, `password.db`, uses the following format:

```
username_1:password_1
username_2:password_2
...
username_n:password_n
```

Usernames and passwords may be _up to 8_ alphanumeric characters long.  Each username and password pair must be terminated with a newline (`\n`).

<hr style="border-color: purple;" />

## Part 1: `login0`, a naive login program

In part 1, you will write a login program in a file called `login0.c`.  You should be able to compile this program by typing `make login0`, which should produce a binary file called `login0`.  You will need to modify the `Makefile` to add a `login0` target.

Specification:

1. The program should prompt the user to enter a username.
2. The program should attempt to locate the username in the database.
   - If the username is in the database, the program should prompt the user to enter a password;
   - otherwise, the program should print `USER NOT FOUND` and then go to step 1.
3. If the username is in the password database _and_ the entered password matches the stored password in the database, then the program should print `ACCESS GRANTED` and terminate.
4. Otherwise, go to step 1.

The following is a sample `login0` session.  Make sure your program behaves exactly like this:

```
$ ./login0 
Enter a username: barowy
USER NOT FOUND
Enter a username: dbarowy
Enter a password: password
ACCESS GRANTED
```
<hr style="border-color: purple;" />

## Part 2: Attacking `login0`

Before you write attack code, you will need to write code that lets you supply inputs to `login0`.  For those command-line applications that accept input on the "standard input stream" (aka, `STDIN`) and provide output on the "standard output stream" (`STDOUT`), programmatically supplying inputs and capturing outputs is easy.  If you have played around with UNIX long enough, you've probably seen the "pipe" character, `|`.  For example, the command `echo "heya" | mail -s "just saying hi" mail@example.com` will send "heya" to the `mail` program via `STDIN` which then sends email to the given address.  Give it a try (be sure to change the email address first).

Unfortunately, _interactive_ programs like `login0` are not so straightforward.  The problem is that  an interactive program is attached to a user's terminal, and it usually expects user input to be more nuanced than that provided via `STDIN`.  For example, if you use the provided `fgets_wrapper` call, the function captures some number of characters up to the size of the given buffer; any characters after that limit up to the next newline or the end of the stream are removed (this is called _flushing `STDIN`_).  Why does `fgets_wrapper` do this?  So that if the user types in a 9-character password when we're expecting an 8-character password, we don't "overflow the buffer."  If you pipe input to a program using `fgets_wrapper`, whatever is left over after the first `fgets_wrapper` call will be erased, and the program will not work as you expect.

Fortunately, there is a way around this.  Instead of trying to feed input to the program through `STDIN`, we can instead attach the program directly to a terminal under _our_ control.  Because this helper program is not actually a screen it is called a _pseudoterminal_.

<hr class="style12" />

### `pty0`, a pseudoterminal wrapper

The `ptyhelper.c` program in your starter code is to help you set up a pseudoterminal attached to the controlled process.  The "[Pseudoterminal Cheatsheet](../../misc/pseudoterminals.html)" explains how to use the helper code to create a program that controls another program.

In this part, you will create a file called `pty0.c`.  You should be able to compile this program by typing `make pty0`, which should produce a binary file called `pty0`.  You will need to modify the `Makefile` to add a `pty0` target.  _Take note_ that when compiling with `gcc` any program that makes use of the `ptyhelper` library, you will need to add the `-lutil` flag to `gcc`.  The `-lutil` flag tells `gcc` to find several of the pseudoterminal functions in the `libutil.so` system library (Why? Because `man openpty` tells us that we have to `¯\_(ツ)_/¯`).

* Write a program that attaches to `login0`.  Call this program `pty0`.
	1. Write a `masterf` function that controls `login0` by calling `read` and `write` as appropriate.
	2. Call `exec_on_pty` with an appropriately constructed `argv` and with `masterf`.
	3. For `pty0`, all it needs to be able to do is to supply a single correct username and password (look in the `password.db` file) to `login0`, and return `It worked!` when `login0` returns `ACCESS GRANTED`.

<hr class="style12" />

### `attack0`: brute force attack on `login0`

In this part, you will copy `pty0.c` into a new file called `attack0.c`.  You should be able to compile this program by typing `make attack0`, which should produce a binary file called `attack0`.  You will need to modify the `Makefile` to add an `attack0 ` target.

* Write a program that "attacks" `login0`.  The purpose of this program is simply to harvest usernames, which is often the first step in attacking logins. Call this new program `attack0`.
	3. Your attack program should supply a randomly-generated up-to-8-character username at the username prompt.  Make sure that you only generate alphanumeric characters.  To generate a random integer, use the `rand()` C library call.  You will also need `srand()`.  See `man 3 rand`.
	4. If `login0` prompts `attack0` for a password, you have successfully harvested a valid username. Since we don't know the password, if this happens, just provide the password `password` to the prompt.  We don't care about the response just yet.
	5. Your program should attempt to login up to 10,000 times.  If it finds at least one valid username, it should print `SUCCESS` along with that username and quit, otherwise it should keep trying.  If it tries 10,000 times without success, it should print `FAILURE` and quit.

<hr style="border-color: purple;" />

## Part 3: `login1`, an improved login program

In retrospect, it is obviously a bad idea to tell the user when they have successfully found a username.  Instead, we should accept the username _and_ the password before checking against the database.

In this part, you will copy `login0.c` into a new file called `login1.c`.  You should be able to compile this program by typing `make login1`, which should produce a binary file called `login1`.  You will need to modify the `Makefile` to add a `login1 ` target.

* Modify `login0`.  Call this program `login1`.	2. The program should prompt the user to enter a username.
	3. The program should prompt the user for a password.
	4. If the username is in the password database _and_ the entered password matches the stored password in the database then the program should print `ACCESS GRANTED` and terminate.
	5. Otherwise, it should print `ACCESS DENIED` and go back to step 1.

The following is a sample `login1` session.  Make sure your program behaves exactly like this:

```
$ ./login1 
Enter a username: barowy
Enter a password: password
ACCESS DENIED
Enter a username:
...
```

<hr style="border-color: purple;" />

## Part 4: `attack1`, a brute force attack on `login1`

In this part, you will copy `attack0.c` into a new file called `attack1.c`.  You should be able to compile this program by typing `make attack1`, which should produce a binary file called `attack1`.  You will need to modify the `Makefile` to add a `attack1` target.

* Modify `attack0` to attack `login1`.  Call this program `attack1`.
	1. `login1` makes it hard to harvest usernames. Unfortunately, usernames are usually pretty easy to guess even if you can't harvest them.  For example, in the CS department, most faculty usernames are the first character of their first name and their last name.  Assume that you have already harvested usernames from another source, like a company directory.  You may use the usernames (but not the passwords) from the `password.db` file for `attack1`.  Create a username database for `attack1` called `usernames.db` and put the usernames in it.
	2. Your attack program should randomly select a username from its username database and randomly-generate an up-to-8-character password.
	5. Your program should attempt to login up to 10,000 times.  If it finds a valid username and password combination, it should print "SUCCESS" along with the username and password and immediately quit, otherwise it should keep trying.  If it tries 10,000 times without success, it should print "FAILURE" and quit.

<hr style="border-color: purple;" />

## Reflection Questions

In addition, answer the following questions in a file called `PROBLEMS.md`, and submit it with the rest of your code this week.

1. For our username scheme, how many possible usernames are there?
2. For our password scheme, how many possible passwords are there?
1. When you ran `attack0` against `login0`, did it find any working usernames?  If not, does it mean that `login0` is "secure"?  Why or why not?
1. How might you modify `attack0` to find valid usernames faster?
1. `login1` is obviously better than `login0`.  Can you quantify why?  Think about your answers to the first two questions.
1. When you ran `attack1` against `login1`, did it find any working password?  If not, does it mean that `login1` is "secure"?  Why or why not? 
1. How might you further improve `login1`?  If you want a bonus challenge, see the `login2` bonus section below and implement this improvement.

<hr style="border-color: purple;" />

## Bonus: `login2`, an even-more-improved login program

In this part, you will copy `login1.c` into a new file called `login2.c`.  You should be able to compile this program by typing `make login2`, which should produce a binary file called `login2`.  You will need to modify the `Makefile` to add a `login2` target.

You should implement the improvement you suggested above.  Is it actually better?  How do you know?  Only answers that provide a full mathematical justification for their improvement will receive full bonus points.

<hr style="border-color: purple;" />

## Development Tips

Writing C can be a challenge.  One way to deal with this is to log things that happen, and use that information to help debug.  Because this assignment puts restrictions on what you consume and print, you _should not_ use `printf` to log things.  Instead, use a handy function like this one, which prints to a log file instead.

```
void  mylog(char *desc) {
  static int n = 0;
  FILE* file = fopen("DEBUGLOG.txt", "a");
  if(file != NULL)
  {
    n += 1;
    fprintf(file, "%d: %s", n, desc);
  }
  fclose(file);
}
```

Remember to be patient and systematic.  If you don't understand your own code, you should consider setting it aside and starting over.

<hr style="border-color: purple;" />

## Lab Deliverables

By the start of lab, you should see a new private repository called `cs331lab01_login-{USERNAME}` in your GitHub account (where `USERNAME` is replaced by your username).

For this lab, please submit the following: 

    cs331lab01_login-{USERNAME}/
		attack0.c
		attack1.c
		console.c
		console.h
		database.c
		database.h
		login0.c
		login1.c
		login2.c (optionally)
		Makefile
		password.db
		PROBLEMS.md
		pty0.c
		ptyhelper.c
		ptyhelper.h
		README.md
		usernames.db
		
where the `login*.c`, `attack*.c`, and `pty0.c` files contain your _well-documented_ source code.

It is always a good practice to create a small set of tests to facilitate development, and you are encouraged to do so here.

As in all labs, you will be graded on _design_, _documentation_, _style_, and _correctness_. Be sure to document your program with appropriate comments, including a general description at the top of the file, and a description of each function with pre- and post-conditions when appropriate. Also, use comments and descriptive variable names to clarify sections of the code which may not be clear to someone trying to understand it.

Whenever you see yourself duplicating functionality, consider moving that code to a helper function. There are several opportunities in this lab to simplify your code by using helper functions.

<hr style="border-color: purple;" />

## Submitting Your Lab

As you complete portions of this lab, you should `commit` your changes and `push` them. <u>Commit early and often.</u> When the deadline arrives, we will retrieve the latest version of your code. If you are confident that you are done, please use the phrase `"Lab Submission"` as the commit message for your final commit. If you later decide that you have more edits to make, it is OK. We will look at the latest commit before the deadline.

* <u>Be sure to push your changes to GitHub</u>.
* <u>Verify your changes on GitHub.</u> Navigate in your web browser to your private repository on GitHub. It should be available at [https://github.com/williams-cs/cs331lab01_logins-{USERNAME}](https://github.com/williams-cs/cs331lab01_logins-{USERNAME}). You should see all changes reflected in the files that you `push`. If not, go back and make sure you have both committed and pushed.

We will know that the files are yours because they are in _your_ `git` repository. <u>Do not include identifying information in the code that you submit.</u> We grade your lab programs anonymously to avoid bias. In your `README.md` file, please cite any sources of inspiration or collaboration (e.g., conversations with classmates). We take the honor code very seriously, and so should you. Please include the statement `"I am the sole author of the work in this repository."` in the comments at the top of your C files. 

<hr style="border-color: purple;" />

## The squeaky wheel gets the grease

I am always looking to make my labs better.  For one bonus point, please submit answers to the following questions using the [anonymous feedback form](http://barowy.net/cs331f19/) for this class:

1. How difficult was this assignment on a scale from 1 to 5 (1 = super easy, ..., 5 = super hard)?
1. Anything else that you want to tell me?
1. Your name, for the bonus point (if you want them).

<hr style="border-color: purple;" />

## Bonus: Mistakes

Did you find any mistakes in this writeup?  If so, add a file called `MISTAKES.md` to your GitHub repository and describe the mistakes using bullets.  For example, you might write

    * Where it says "bypass the auxiliary sensor" you should have written "bypass the primary sensor".
	* You spelled "college" wrong ("collej").
	* A quadrilateral has four edges, not "too many to count" as you state.
	
You will receive one bonus point on this assignment for each mistake I am able to validate.

<hr style="border-color: purple;" />
