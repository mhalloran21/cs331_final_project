---
layout: page
title: 'How to Enable the SSH Server on Your Raspberry Pi'
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

Installing the SSH server (aka "daemon", pronounced "demon") on your Raspberry Pi will free you from having to plug your Raspberry Pi into your computer's USB port every time you want to work with it.  Instead, you can connect your Raspberry Pi to an outlet in your dorm room, and then SSH into the Raspberry Pi elsewhere from a terminal.

Pros:

* You no longer need to use the `stty` command when you resize your terminal.  `ssh` understands the `SIGWINCH` signal, which means that it will run `stty` for you.
* `emacs` works over `ssh`, unlike our serial console where it appears to drop control characters.
* You can leave your Raspberry Pi running, and you can even use `screen` inside `ssh` to "detach" a running session, which you can later resume.

Cons:

* You will need to save your Raspberry Pi's IP address.  There is a small probability it will change (IPs on campus are "dynamically allocated"), so you will need to periodically check that it hasn't changed before you leave your Raspberry Pi in a far-away place.  It would be annoying to walk to lab only to find your lab computer was unreachable!
* You probably will not be able to reach your Raspberry Pi off campus due to the campus firewall.
* SSH is of limited usefulness for Labs 5 and 7.  You can perform your analysis and attacks, _but you will probably have to make small modifications to your attack code_ before submission.  This is because SSH modifies the shell environment significantly (and somewhat unpredictably), meaning that getting the same attack to work on both the serial console and SSH is difficult.  Remember that assignments are graded using the serial console.

In general, the pros outweigh the cons.  Just be aware of the tradeoffs.

Also: these instructions assume that your personal computer is a UNIX-like machine, either the macOS or Linux.  If you are using Windows, you have two alternatives: WSL or PuTTY.

If you install [WSL](https://docs.microsoft.com/en-us/windows/wsl/install) on Windows, then you can follow these instructions as if you have a Linux machine (because, in a sense, you do).  The other alternative is to install [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) and its key-generation utility, PuTTYgen.  Here's [a tutorial for using PuTTYgen](https://www.ssh.com/academy/ssh/putty/windows/puttygen).

<hr class="style12" />

### Install OpenSSH

On your Raspberry Pi:

1. Install it.
   ```
   $ sudo apt install openssh-server
   ```
2. Start the server.
   ```
   $ sudo systemctl start ssh
   ```
3. Ensure that the server will start itself up when you reboot the computer.
   ```
   $ sudo systemctl enable ssh
   ```

<hr class="style12" />

### Change your password on your Raspberry Pi!

Now that you've opened your Raspberry Pi up to the internet, anybody who knows the default username and password can get in.  You _really_ should change your password.  Run:

```
$ passwd
```

<hr class="style12" />

### Generate SSH keypairs

On your personal machine (not your Raspberry Pi):

1. `cd` to `~/.ssh`.  If that folder does not exist, create it.
2. Generate a keypair:
  ```
  $ ssh-keygen -t rsa -b 1024 -f <yourname>-pi
  ```
  For example, I might run
  ```
  $ ssh-keygen -t rsa -b 1024 -f dbarowy-pi
  ```
3. You will be asked, when you generate a keypair, whether you would like to set a password.  If you are comfortable with the idea that anybody in possession of your keys can get into your Raspberry Pi, then you can omit the password.  Otherwise, set one.
4. If you `ls` your directory, you will see two files, `<yourname>-pi` and `<yourname-pi>.pub`.  The `.pub` file is a _public key_.  Anyone who has it can encrypt messages to send to you.  The other file is a _private key_.  Anyone who has it can decrypt messages sent to you.  You _really_ want to keep your private key secret.
5. Type
   ```
   $ cat <yourname>-pi.pub
   ```
  then copy the _entire output_, including the `ssh-rsa` bit at the beginning.

<hr class="style12" />

### Install SSH public key on your Raspberry Pi

On your Raspberry Pi,

1. `cd` to the `~/.ssh` folder.  Create it if it does not exist.
2. Edit (or create) a file in that folder called `authorized_keys`.
3. Paste the public key you just copied above into this file, and save it.

<hr class="style12" />

### Find your Raspberry Pi's IP address

On your Raspberry Pi, type

```
$ ifconfig
```

You should see output like the following:

```
pi@raspberrypi:~ $ ifconfig
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.172.172.10  netmask 255.255.255.0  broadcast 172.172.172.255
        inet6 fe80::5e85:7eff:fe30:809f  prefixlen 64  scopeid 0x20<link>
        ether 5c:85:7e:30:80:9f  txqueuelen 1000  (Ethernet)
        RX packets 787554  bytes 78475249 (74.8 MiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 752475  bytes 199113190 (189.8 MiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 27  bytes 2160 (2.1 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 27  bytes 2160 (2.1 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

My Raspberry Pi is hardwired, so yours will look a little different.  Yours uses wifi.  Look for the section titled `wlan0` and find the number prefixed with `inet`.  The IP address printed right after `inet` is your IP address.  Since mine is hardwired, the section I look for is in `eth0`, and right after `inet` I see `172.172.172.10`.  That's my IP address.

Valid Williams IP addresses, usually start with `137`.

<hr class="style12" />

### Set up a SSH `config` file on your personal computer

1. Again, `cd` to `~/.ssh` on your personal computer (not the Raspberry Pi).
2. Edit (or create) a file called `config`.  Type in the following:
  ```
  host pi
       hostname <your IP address>
       user pi
       identityfile ~/.ssh/<yourname>-pi
  ```

  For example, mine is:

  ```
  host pi
       hostname 172.172.172.10
       user pi
       identityfile ~/.ssh/dbarowy-pi
  ```

<hr class="style12" />

### Try logging in

Now, try to SSH from your personal computer to your Raspberry Pi

```
$ ssh pi
```

The first time you log in, you will be asked to verify your Raspberry Pi's _fingerprint_.  This fingerprint will never change.  If it does, `ssh` will warn you, and ask you to verify it again.  A changed fingerprint is evidence of a "man-in-the-middle" attack.  Alternatively, it might also mean that you reinstalled the OS on your Raspberry Pi.  If you didn't change anything, you should worry.

