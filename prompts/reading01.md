---
layout: page
title: 'Questions for "The Cuckoo's Egg", chapters 1-9'
---

<style>
  blockquote {
    background: #f9f9f9;
    border-left: 10px solid #ccc;
    margin: 1.5em 10px;
    padding: 0.5em 10px;
    quotes: "\201C""\201D""\2018""\2019";
  }

.latex sub {
  vertical-align: -0.1ex;
  margin-left: -0.1667em;
  margin-right: -0.025em;
}

.xetex sub {
  vertical-align: -0.1ex;
  margin-left: -0.1667em;
  margin-right: -0.125em;
}

.latex sub, .latex sup, .xetex sub {
  font-size: 0.9em;
  text-transform:uppercase;

}
.latex sup {
  font-size: 0.85em;
  vertical-align: -0.2em;
  margin-left: -0.26em;
  margin-right: -0.05em;
}
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

Due on Wednesday, September 15 by 11:59pm

<hr style="border-color: purple;" />

Turn-in instructions: Put a _printed copy_ of your responses in my mailbox in the CS common area in TCL.  I will not accept handwritten responses.

<div style="padding: 1em; background-color: beige;">
Optional, for this one assignment: use a <a href="reading01.tex">LaTeX template</a>.  Convert to PDF with:
<pre>
$ pdflatex reading01.tex
</pre>
You will need to install TeXLive on your personal computer to build LaTeX documents: <a href="https://www.tug.org/mactex/">macOS</a>, <a href="https://www.tug.org/texlive/windows.html">Windows</a>, <a href="https://www.tug.org/texlive/debian.html">Linux</a>.

CS Lab machines already have TeXLive installed.
</div>

<hr class="style12" />

1. Explain the <code>emacs</code> "movemail" bug.  Stoll's description is light on detail, so you will need to do a little research (e.g., using Google) on your own.  Be sure that your answer uses the words "setuid" and "privilege escalation".
1. On page 40, Stoll notes that the hacker accessed an encrypted password file.  First, what is an encrypted password file?  Second, why is or why isn't the hacker's access of this file a cause for concern?  Refer to the <a href="https://man7.org/linux/man-pages/man5/passwd.5.html" target="_blank">official password file documentation for Linux</a> (i.e., the password file "<code>man</code> page") and note that <em>The Cuckoo's Egg</em> takes place in the "good old days."  If you use any jargon in your answer (e.g., "crack"), be sure to define it.  Be prepared to do a little digging to provide a good answer.
1. Here is an entry in the <code>/etc/shadow</code> file for a modern computer on which I have an account:
   <pre>
   dbarowy:$6$Yvba7lX/suhF9Ahd$wbJ0hEVyDhZtli8h6xjV0OtF5i4DHNUsUw0FRpBw.W1tf9v/mAmEa/gyew2ggwsGwbFAt6EiWnMxaezfz4nAQ/:18439:0:99999:7:::
   lxd:!:18439::::::
   </pre>
   What encryption algorithm is being used to obscure my password, and is it a "trapdoor" function or something else?  You will need to find the appropriate <code>man</code> page to answer this question.
1. Stoll notes that the computer running on the network address <code>26.0.0.113</code> belonged to the US Department of Defense.  Who owns it now?  Use the <a href="https://lookup.icann.org/" target="_blank"><code>whois</code></a> tool to answer.
1. Suppose you want to "trace" the path that data takes between your own computer and another computer at a given address.  You can use a <a href="https://tools.keycdn.com/traceroute" target="_blank"><code>traceroute</code></a> tool to perform this task.  What networks do connections from your computer to <code>26.0.0.113</code> cross?  Assume your computer is in New York, NY.  You will need to use the <code>whois</code> tool above to find network names.  What do you think the output <code>???</code> means?
