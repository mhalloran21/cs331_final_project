---
layout: page
title: 'Why Stolen Password Databases are a Problem'
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

Although a great deal of effort has been invested in making login programs difficult to break or circumvent, attackers still regularly obtain password databases.  Consequently, passwords in databases are not usually stored as-is, to make reading a stolen password database difficult.

<hr style="border-color: purple;" />

## A Simple Password Database

At its core, a password database maps a user identifier, or _user name_, to a password.  It usually has the following form.

    user_1,password_1
	user_2,password_2
	...
	user_n,password_n

When a user attempts to login to a service, they provide their username and password, and we check our password database to see whether these _credentials_ match the ones we stored.  This scheme is simple, and as long as the login program does not leak stored credentials, it _seems_ reasonably secure.

<hr class="style12" />

### What are our assumptions?

Even if we rule out bugs in our login program that might leak sensitive information to an attacker, there are a number of other ways that credentials can be leaked to an attacker.  First, a password database must be stored on a server somewhere.  That means:

1. Anyone with superuser access levels (aka _root privileges_) can read the database.  IT workers typically have these privileges because they are necessary to configure and maintain machines.  IT workers are sometimes susceptible to social engineering, extortion, or are sometimes willing to help attackers (e.g., a worker that is unhappy about their pay).
1. Password databases are sometimes misconfigured such that they are readable by non-root users.
1. A login program typically needs to be hosted on a publicly-available computer, in order to authenticate outsiders.  If _other_ programs on that computer (including the operating system itself) contain vulnerabilities that can lead to arbitrary disk reads, then the password database can be leaked, even if the login program has no bugs and even if the access level is configured correctly.

Therefore, it is probably a bad idea to assume that an attacker cannot obtain a password database.  Can we redesign our system so that, even if the database is leaked, an attacker cannot easily obtain passwords?  The answer is yes.

<hr style="border-color: purple;" />

## Hash Functions

You have likely seen hash functions before.  Before we get into how they are used in password databases, let's see how they are used in other applications.  If you feel comfortable in your knowledge of hash functions, feel free to skip ahead to the section titled "Cryptographic Hashes."

<hr class="style12" />

### Background: Hash Tables

A _hash table_ is a data structure that can store an arbitrary amount of information (like a list and unlike an array, which is fixed-size) but which has access properties closer to an array (O(1) (amortized) read instead of O(n) read for a list).

A _hash function_ is any function that can be used to map data of arbitrary size onto data of a fixed size.  When we are building hash tables, this enables us to use data of arbitrary length, like a string, to an array _index_.

For example, suppose that we are keeping scores among our friends for a golf match.  It would be really quite useful to be able to look someone's score up by their name.  We want the data structure analog to the following table:

|Name|Score|
|----|-----|
|Joe | 13  |
|Fay | 10   |
|Dan | 451 |
|Tiger| 3 |
|Erin| 43 |

(low scores win in golf)

If people had numbers for names, I bet that you could immediately think of a good data structure.  An array!

|Index|Score|
|----|-----|
|0 | 13  |
|1 | 10   |
|2 | 451 |
|3| 3 |
|4| 43 |

We can lookup items in this form very quickly: O(1) time in the worst case.

Of course, people have names, and those names can be of arbitrary length.  But could we obtain a data structure that behaves the same way, even for names?  With some suitable sleight of hand, we can.  The trick is to use a hash function.  Recall that a hash function is _any function that can be used to map data of arbitrary size onto data of a fixed size_.  That sounds a lot like our problem here: strings can be of any length, but array indices must be of fixed length (e.g., a 32-bit integer in Java).

Suppose our hash function were the following:

```
def hash(value):
    Look up the ASCII character code for the first character in the value, mod the code by 5, and return the result.
```

Here's a [handy table of ASCII character codes](http://www.asciitable.com/).

Let's apply our hash function to the names in our table.  Since `Joe` is the first name in our table, let's start there.  Suppose we have a table of length 5. 

1. The first character of `Joe` is `J`.
1. The ASCII character code for `J` is 74.
1. 74 % 5 = 4
1. Return 4

If we use 4 an an index, then in our table of 5 players, Joe's score is stored in index 4.

|Index|Score|
|----|-----|
|0 |  |
|1 |  |
|2 |  |
|3| |
|4| 13 |

Let's hash the rest of the names:

`Joe` -> 4 <br />
`Fay` ->  0 <br />
`Dan` ->  3 <br />
`Tiger` ->  4 <br />
`Erin` -> 4

You can see that we have a small problem.  Joe, Tiger, and Erin all hash to the same number.  This problem is called a _hash collision_.  With hash tables, this is a common problem, and there are many solutions.  One simple solution is to keep hashing whenever a collision occurs.  Let's modify our hash to take another parameter, `i`.

```
def hash(value,i):
    Look up the ASCII character code for the character at position i in the value, mod the code by 5, and return the result.
```

We increment `i` on collision, and start with `i = 0`.  The character at position `0` is the first character, so when `i = 0`, the hash function behaves the same as the one we had before.

For example, if we start with `i = 0` and insert all of the hashed values up until the first collision, we get

|Index|Score|
|----|-----|
|0 | `<Fay, 10>` |
|1 |  |
|2 |  |
|3| `<Dan, 451>` |
|4| `<Joe, 13> |

Since `Tiger` hashes to `4` when `i = 0` and since Joe's score is already at that location, we hash again with `i=1`.

1. `i = 1`. The second character of `Tiger` is `i`.
1. The ASCII character code for `i` is 105.
1. 105 % 5 = 0
1. Return 0

Sadly, this also collides, with Fay's score.  So we keep going until we find an `i` that does not collide.

1. `i = 2`. The third character of `Tiger` is `g`.
1. The ASCII character code for `g` is 103.
1. 103 % 5 = 3
1. Return 3.

Collides with Dan's score.

1. `i = 3`. The fourth character of `Tiger` is `e`.
1. The ASCII character code for `e` is 101.
1. 101 % 5 = 1
1. Return 1.

Finally, we can put Tiger's score at location 1.  This technique is called _probing_.  There are many different probing algorithms.

|Index|Score|
|----|-----|
|0 | `<Fay, 10>` |
|1 | `<Tiger, 3>` |
|2 |  |
|3| `<Dan, 451>` |
|4| `<Joe, 13>` |

If you continue this exercise, you will see that this hash function is not particularly good.  But it _is_ fast (there are only a few simple operations) and we can repeat it quickly.  Furthermore, if we make our table bigger (i.e., we overprovision it such that it is bigger than the number of items we expect to store), the number of collisions will go down, so for a big enough table, the number of times we need to probe gets small.  We typically employ all of these tricks in designing hash tables.

One thing is clear, though: a good hash function distributes its outputs _uniformly_ across the space of desired table indices.  We will come back to this uniformity property.

<hr class="style12" />

## Cryptographic Hashes

Aside from hash tables, hash functions are also useful for the exact stolen-password database as described above.  What we want to do is to convert a password database, something that looks like:

```
user_1, password_1
user_2, password_2
...
user_3, password_3
```

into something like

```
user_1, encrypted_password_1
user_2, encrypted_password_2
...
user_3, encrypted_password_3
```

where an `encrypted_password_1` is an encoding of `password_1` such that it is difficult to recover `password_1`.

<hr class="style12" />

#### Cryptography, a primer

What is encryption?  _Encryption_ is the process of encoding a message so that it can be read only by the sender and the intended recipient. There are _many_ ways to do this.  First, some terminology:

* A _plaintext_ \\(p\\) is the original, unobfuscated data.  This is information you want to protect.
* A _ciphertext_ \\(c\\) is encoded, or encrypted, data.
* A _cipher_ \\(f\\) is an algorithm that converts _plaintext_ to _cipertext_.  We sometimes call this function an _encryption function_.
* A _sender_ is the person (or entity) who _enciphers_ or _encrypts_ a message, i.e., the party that converts the plaintext into cipertext.
* A _receiver_ is the person (or entity) who _deciphers_ or _decrypts_ a message, i.e., the party that converts the ciphertext back into plaintext.
  * Sometimes the sender and receiver are the same party.  E.g., a login program both enciphers and decipers a password.
* More formally, a _cipher_ is a _function_ from _plaintext_ to _ciphertext_, \\(f(p) = c\\).  The properties of this function determine what kind of encryption scheme is being used.

Let's look at a simple encryption scheme using the ROT-\\(k\\) cipher.  You may have learned a variation of this in elementary school.  It's the same cipher used by Julius Caesar, which is why it is sometimes called the [Caesar cipher](https://en.wikipedia.org/wiki/Caesar_cipher).

Let's start with a version where \\(k\\) = 13.  Given a mapping, \\(\alpha\\), from a character \\(c\\) to a number in \\(\{0 \ldots 25\}\\), the _ROT-13 cipher_ is

```
f(p):
   for each p[i] in p, (alpha(p[i]) + 13) % 26
```

where `p` is a plaintext (password) as a `string` and where `p[i]` is the `char` at position `i` in string `p`.  A typical \\(\alpha\\) is something like the ASCII character code table I showed above, restricted to letters, and where all uppercase characters are converted to lowercase, with 97 is subtracted from the code.  So `a` maps to 0, `b` maps to 1, and so on.

So `apple` is enciphered as `nccyr` in ROT-13.

To generalize this a little, we often parametrize a cipher with a _cryptographic key_. You can think of this as a generalization of a keyless cipher.  For example, \\(f(p,k) = c\\).  One way to think of a cipher with a key is that it _selects a cipher from a family of cipher algorithms using the key as an index_.

The _Caesar cipher_ is a generalization of ROT13.

```
f(p, k):
    for each p[i] in p, (alpha(p[i]) + k) % 26
```

We usually assume ciphers are keyed, so if we leave out the key in the notation, you should remember that keys are typically an important part of the process.

<hr class="style12" />

#### Encrypting our password database

Could we use the ROT-13 cipher to encrypt our password database?  Suppose we have the following database.

```
dbarowy,password
wjannen,drowssap
ihowley,sosecure
...
```

We encrypt this database using ROT-13 so that it now looks like:

```
dbarowy,cnffjbeq
wjannen,qebjffnc
ihowley,fbfrpher
...
```

Note that we usually keep password databases in sorted order, by username, so that username lookups can happen in \\(O(\log_2 n\\)) time using binary search.

When a user attempts to log in, supplying their username and password, our imaginary login program encrypts the password, looks up the entry corresponding to the username, and then checks to see that the encrypted passwords match.  For example, suppose `dbarowy` attempts to login, with password `password`.  The login program converts this password to `cnffjbeq`, looks up `dbarowy`, and compares the stored password `cnffjbeq` against the newly-encrypted password.  Since these two strings match, `dbarowy` is granted access.

This is not a very good password scheme, however.  Remember our scenario: the password database is stolen.  It turns out, in this case, the cipher we chose has a property that makes it a very poor fit for encrypting passwords: if we know the cipher, we can recover all of the passwords.  For a good encryption scheme, knowledge of the cipher should not help you.

<hr class="style12" />

#### Security through obscurity

In the example above, maintaining the secrecy of passwords requires maintaining secrecy of the cipher.  Remember, a cipher is just an algorithm.  Unfortunately, it is very difficult to keep algorithms secret.

Often, algorithms need to be distributed widely to be useful.  For example, the UNIX operating system comes with a password scheme.  Since the code is open-source, anyone can look at the cipher algorithm.  Even when the code cannot be directly examined, it must still be in executable form, in machine code.  Machine code can trivially be converted to assembly code, which is human readable.  Furthermore, good [disassemblers](https://en.wikipedia.org/wiki/Disassembler) exist that can turn assembly into surprisingly readable C code.

Relying on the secrecy of an implementation is sometimes called _security through obscurity_.  Often, people are surprised at how easy it is for a seasoned hacker to pierce the veil of secrecy.  Therefore, knowledgable security practitioners observe the following rule:

_An algorithm must continue provide security guarantees even when it is known by an attacker._

Fortunately both keyed ciphers and hash functions can improve our password encryption scheme.

<hr class="style12" />

### Invertibility

We are going to depend on a mathematical property called _invertibility_ to improve our cipher.

A cipher is _invertible_ if \\(\forall p, k \; f^{-1}(f(p, k), k) = p\\).  In other words, a cipher is invertible if you can recover the plaintext by using an inverse function on the ciphertext.

Note that the above definition uses a key.  Keys are much easier to keep secret than ciphers, because a key does not need to be distributed widely to work.  In fact, every password database should (and every good one does) have its _own, unique key_ used to encipher it.

But invertibility goes further.  A cipher is _non invertible_ if the above property does not hold.   The important insight is that you _cannot_ recover the plaintext with a non-invertible cipher, _even if you have the key_.

You might think it is hard to come up with a good, non-invertible cipher, and you'd be right.  But it turns out that it is pretty easy to come up with a bad, non-invertible cipher, and even bad non-invertible ciphers work reasonably well.  Recall one of our earlier hash functions:

```
def hash(value,i):
    Look up the ASCII character code for the character at position i in the value, mod the code by 5, and return the result.
```

Let's modify our function a little to use our cryptography terminology.

```
def f(p, k):
	Look up the ASCII character code for the character at position k in p, mod the code by 5, and return the result.
```

Looks an awful lot like a cipher to me.  Let's think a little about its properties.

First, it is clearly not invertible.  Having `k` doesn't help you find out that `3` was originally `Dan`.

Second, in the section titled "A Simple Password Database", did you notice that we _did not_ say that we have to "decrypt the password" when describing the login process?  If you think of decrypting as the inverse of encryption, then you might think we have a problem.  If our function is non-invertible, and we need to invert it in order to check passwords, we're stuck.  Fortunately, we can take advantage of the fact that _the login program can just encipher the password itself using the key, and then compare the two ciphertexts_.

Third, remember one of the goals of hash functions: we want the distribution of its outputs to be uniform.  And most good hash functions are.  When you have a good hash function, "nearby" inputs (e.g., "Don" or "Deb" are similar to "Dan") don't tell you anything about the output.  This one, as you might see, is not so good, but real hash functions do not have this problem.

Fourth, and this is a consequence of using hash functions, is that our cipher now also suffers from collisions.  Why?  As the definition of a hash function told us, we need to be able to accept arbitrary input and be able to produce an output of fixed length.  An output of fixed length implies that there are a finite number of possible values.  An `int` is a typical hash output.  But an input of arbitrary length---say, a `string`---has a very large (sometimes infinite) number of possible values.  If you recall the pigeonhole principle, if you have \\(n\\) pigeons and \\(m\\) pigeonholes, and \\(n > n\\), well, at least one pigeon needs to share a pigeonhole with another pigeon.  If we can only produce \\(m\\) outputs for \\(n\\) possible inputs, and \\(n > m\\), our hash function will have at least one collision.

Hash collisions when hashes are used as ciphers lead to the somewhat weird state that _sometimes_ you can match a ciphertext in a password database with a _different_ password or a _different_ key.  We will take advantage of this later in class.  Generally, a good cryptosystem tries to avoid collisions.  One way to do that is to make the output value space so large that it is infeasible to try to find passwords that map to every value.  Supposing that your output space contains \\(2^{64}\\) outputs, and supposing that you can find 1 million unique outputs per second, it would take you 584,942 _CPU years_ to find all of them!

Fifth, hash functions can be designed to run quickly, and they ususally do.

So the big picture is that hashes are actually pretty good for the purpose of encrypting a password database.  They are not invertible, so getting your hands on the cipher and key does not help you find the original password.  They map uniformly across the output space, so discovering that one password hashes to a given value does not help you discover other passwords.  In fact, to "crack" an entire password dictionary requires a tremendous amount of computation, since you basically need to try every possible password and see if it hashes to a value stored in your database.  Although there are tricks for reducing the computational burden, this fundamental fact remains even today.  Finally, hash functions are "fast."  They can usually be computed in milliseconds, where as finding the inverse, even though it can be done by brute force search, is computationally infeasible.

To count as a fully "cryptographic"-strengh hash, hash functions should have the following properties.  They should

1. be deterministic,
1. be inexpensive to run,
1. have output that _appears_ to be drawn uniformly randomly from the space of possible hash values,
1. be _preimage resistant_ (given a hash output \\(h\\), it should be difficult to find a plaintext \\(p\\) that yields \\(h\\) when hashed),
1. be _weakly collision resistant_ (given a plaintext \\(p_1\\), it should be difficult to find a different plaintext \\(p_2\\) such that \\(p_1\\) and \\(p_2\\) yield the same hash), and
1. be _strongly collision resistant_ (it should be difficult to find _any two_ different plaintexts such that yield the same hash).

Where _difficult_ means "computationally expensive."

<hr class="style12" />

### Our database, hashed

Recall our original unencrypted database.

```
dbarowy,password
wjannen,drowssap
ihowley,sosecure
...
```

Encrypted using a real hash function, like SHA-1 (which is unkeyed), you will get

```
dbarowy,5baa61e4c9b93f3f0682250b6cf8331b7ee68fd8
wjannen,d50f3d3d525303997d705f86cd80182365f964ed
ihowley,04c1fcac3465958867e09cca1fe8f0b7c66ab32d
```

<hr style="border-color: purple;" />

## Other Password Database Attacks

Is that it?  Sadly, no.  Although hashed password databases make finding passwords from a stolen database expensive, it does not make doing so impossible.  If a cryptographic hash is weak, then an adversary with lots of resources (think "nation state") sometimes has the capability and patience to find passwords.  We will explore these issues.

But there are other potential attacks against password security.  Some of these can be run against stolen password databases offline; others take advantage of trust and are more insidious.

<hr class="style12" />

### Credential stuffing

Although none of _you_ will make the stupid mistake of leaving a password database unencrypted, others may.  For example, suppose some company---let's call it F-Book---[does not encrypt passwords](https://fortune.com/2019/03/21/facebook-unencrypted-passwords-privacy/), and then their password database is stolen.  An F-Book user might be tempted to think that it only affects their F-Book login.  So that person dutifully changes their F-Book password and forgets about it.

But should they?  Have you ever used the same password in more than one place?  If this person did so, they should worry.

As an attacker, I can look up a password in the unencrypted or cracked database, and then I can compare it against an uncracked database.  Although many people do use different passwords, many don't. Using this technique, called _credential stuffing_, I can usually recover many passwords.

You can find out if your credentials are in a stolen database on the black market because [one security researcher purchases and publishes this information](https://haveibeenpwned.com/).  My credentials are in there.  Am I worred?  No.  Because I do not reuse passwords.  Ever.

<hr class="style12" />

### Password spraying

Let's face it: people do not choose their passwords uniformly randomly from the entire space of random characters.  If we did, passwords would look more like `򴦫ßоػꚱmłߍ`.

This means that an attacker can focus their password cracking efforts on _representative_ inputs.  This space is _much_ smaller, and consequently, can be searched much more quickly than the space of all possible strings.  Often, a list of common passwords is sufficient to crack many passwords in a password database.  This technique is called _password spraying_.

The [following table should convince you that people regularly choose bad passwords](https://en.wikipedia.org/wiki/List_of_the_most_common_passwords).

A good countermeasure?  Have a [long password](https://www.xkcd.com/936/).  And while you're at it, try to work some unusual characters in there.

<hr class="style12" />

### Keylogging

This is an especially nasty attack, that requires very little in terms of effort.  _Keyloggers_ are typically hardware devices that require no special privileges on a computer.  Usually, these devices act as USB "passthrough" cables, and they are both [cheap and legal](https://www.keelog.com/) to obtain, although using them is not legal except by law enforcement with a search warrant.

Sadly, our stance toward inserting hardware in a modern computer is altogether too lenient.  You can surreptitiously insert one of these into a computer when somebody isn't looking.  Because nearly all computers have hardware autodetection, and they automatically load the appropriate driver, the user is never prompted to do anything to enable the device.  Good targets are desktop computers, which are still very common in offices and some homes, and since workers rarely inspect their cables, they can go unnoticed for a long time.  Later, the attacker retrieves the device, which contains a log of all keystrokes.

Good countermeasures are: two-factor authentication, using the saved passwords feature in your browser, and occasionally looking at your USB ports.  Unfortunately, requiring authentication to insert USB devices still appears to be [research](https://users.encs.concordia.ca/home/m/mmannan/publications/DeviceVeil-dsn2019.pdf).

<hr class="style12" />

### Post-It Notes

Although computer hackers seem like a big threat because of news stories and movies and TV depicting them in [glamorous ways](https://www.youtube.com/watch?v=0PxTAn4g20U), in fact, your biggest threat are likely your acquaintances.  Unlike strangers, they tend to have powerful motivations (e.g., the ex-boyfriend/girlfriend you dumped last week), they know your habits, and if you're foolish, they either know your passwords or where to find them.  Post-It notes are one common source of vulnerability.  Don't do this!

I know what you're thinking.  "But I have so many passwords!"  There are two countermeasures:

1. use a [password manager](https://en.wikipedia.org/wiki/Password_manager), or
1. develop a cipher for personal use.

I will illustrate the latter one, as you might not know what I mean.  Remember, a cipher is simply a function, or formula, for enciphering data.  Instead of remembering \\(n\\) passwords, instead, come up with a formula that lets you _generate_ passwords from information on your screen.  For instance, let's say I need a password for `ebay.com`.

Believe it or not, something like ROT-1, with a little extra information, is not a terrible choice.  What if I used the domain name, say, `ebay`, enciphered it with ROT-1 (`fcbz`), append the count of the number of characters (`fcbz4`) and repeated it, alternating with uppercase, and then I append some punctuation at the end (`fcbz4 FCBZ4 fcbz4,`).  That's actually a reasonably strong password:

1. The words are not in the dictionary.
1. If I am paranoid, I can make it longer, which makes it harder to find.
1. I am using some unusual characters in my password (namely `" "` and `","`).

I can generate such a password in my head, just by using information available on the page.  And best yet, I do not need to write it down.  I just need to remember my one cipher.

<hr class="style12" />

### Others

It's safe to assume that there are other attacks against passwords.  Can you think of any?
