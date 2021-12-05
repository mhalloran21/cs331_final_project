---
layout: page
title: 'Prompt for "Preventing Privilege Escalation"'
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

Due on Wednesday, December 1 by 11:59pm

<hr style="border-color: purple;" />

Write a technical paper review, and in your discussion, please address the following questions.

* Privilege separating an existing codebase clearly requires a lot of work from a programmer.  Do you think the cost is worth the effort?  Why or why not?  If you were writing a new program, would you privilege-separate it?

<hr class="style12" />

Turn-in instructions: commit your response to your reading responses Github repository.  Please use the LaTeX template supplied in your repository.  Be sure to turn in both your source `.tex` file and a compiled `.pdf` file.

<div style="padding: 1em; background-color: beige;">
You can generate a PDF from the template with the command:
<pre>
$ pdflatex reading09.tex
</pre>
<em>Please</em> be sure to name your generated PDF <code class="language-plaintext highlighter-rouge">reading09.pdf</code>.

You will need to install TeXLive on your personal computer to build LaTeX documents: <a href="https://www.tug.org/mactex/">macOS</a>, <a href="https://www.tug.org/texlive/windows.html">Windows</a>, <a href="https://www.tug.org/texlive/debian.html">Linux</a>.

CS Lab machines already have TeXLive installed.
</div>