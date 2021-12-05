---
layout: page
title: 'Project Part 1: Background Research'
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

**Due Sunday, October 3 by 11:59pm**

For your final project, you will:

* research a computer security-related topic that interests you (e.g., SQL injection vulnerabilities);
* demonstrate it using code that you write (e.g., attack code);
* discuss threats and mitigations using the CIAA framework we've discussed (e.g., attack: "missing quote", defense: "input validation");
* and, finally, discuss the cost-benefit tradeoffs that a systems designer should make.

You will present your work in the form of a final research paper, and you will demonstrate your findings to the class in the form of a 10-minute final project presentation at the end of the semester.

But before you get to all of that, we start with something fun and easy: background research.  The purpose of this assignment is to scout out potential final project topics.

<hr style="border-color: purple;" />

## What to turn in

For this assignment, you should research three different topics.  You should turn in a short writeup on the three topics you find.  Your writeup must be at least 1000 words.  Please use LaTeX for this assignment, and be sure to turn in a `.pdf` file along with your `.tex` file.

<hr style="border-color: purple;" />

## Topics

There are many topics you might choose.  At a high level, the most important criterion of your topic is that it be computer-related.

More concretely, many students enjoy researching either vulnerabilities or countermeasures.  Although all of you need to write code for your final project, this does not mean that you must implement a system.  Proof-of-concept attack code is perfectly acceptable.  However, if you want to build a system (e.g., a secure protocol for _foo_), you may do so; just keep in mind that time is short during a semester, so your implementation should be achievable.

Finally, although you must do your own research, this does not mean that you must produce novel research.  Finding novel vulnerabilities or designing novel countermeasures is generally difficult and time-consuming, and I discourage you from attempting to do so during the semester.  Instead, consider learning about and replicating someone else's work.  What makes the project interesting is _technical depth_: you must eventually produce your own, original code, even if it is inspired by someone else's.

<hr class="style12" />

### Where to find interesting topics

There are vast numbers of security vulnerabilities reported each year.  In this course, we are not interested in [particular instances of attack like this proftpd attack](https://seclists.org/bugtraq/1999/Sep/328), but rather, the entire category a given attack falls under.  For example, the previously mentioned attack is a kind of [format string vulnerability](https://en.wikipedia.org/wiki/Uncontrolled_format_string).  Most of vulnerabilities fall into an already-known class of attack.  Understanding classes of attacks facilitates building countermeasures that work for many possible attacks.

Some useful starting points are [the Wikipedia page on vulnerabilities](https://en.wikipedia.org/wiki/Vulnerability_(computing)) and the [OWASP Periodic Table of Vulnerabilities](https://www.owasp.org/index.php/OWASP_Periodic_Table_of_Vulnerabilities).  But there are also many other places to look.

There is a great deal of academic research on security vulnerabilities.  Popular venues are the [USENIX Security Symposium](https://www.usenix.org/conference/usenixsecurity19), the [IEEE Symposium on Security and Privacy (aka "Oakland")](https://www.ieee-security.org/TC/SP-Index.html), and the [ACM Conference on Computer and Communications Security](https://www.sigsac.org/ccs.html).  The conference proceedings (i.e., papers) for most, if not all, of these conferences should be available via the [Williams Library](https://library.williams.edu/).

There is also a great deal of non-academic research on security vulnerabilities.  These venues, like [DEFCON](https://defcon.org/), are often the first place that brand-new attacks appear.  Although these communities reliably produce interesting work, be aware that their criteria are quite different than the academic communities listed above, emphasizing fun and/or cleverness over novelty or technical merit.

There are also, quite literally, [hundreds of books on security vulnerabilities](https://librarysearch.williams.edu/primo-explore/search?query=any,contains,computer%20security%20vulnerabilities&tab=default_tab&search_scope=everything_scope&vid=01WIL_SPECIAL&mfacet=rtype,include,books,1&lang=en_US&offset=0).  Our library can obtain many of these books for you via interlibrary loan if they are not available online or locally.

Finally, there are a number of tutorial sites that teach you how attacks work.  One really beautiful one is called [hacksplaining](https://www.hacksplaining.com).  For example, have a look at the lesson on [SQL injection attacks](https://www.hacksplaining.com/exercises/sql-injection).

The above resources primarily focus on _classes of attack_ as opposed to _instances of attacks_.

As for instance of attacks, you can find [thousands](https://news.google.com/search?q=security%20vulnerability&hl=en-US&gl=US&ceid=US%3Aen) of articles in the popular press.  Such articles help illuminate the circumstances on an attack, but they are usually light on technical details.  They are also frequently wrong about technical details!

<hr style="border-color: purple;" />

## Guidance

For each of the three classes of vulnerability that you research, you should answer the following questions in your writeup.

1. What is your topic?
1. What resources are affected?
1. In what way are resources affected? (confidentiality, integrity/authorization, availability, non-repudiation)
1. Who would gain from attacking the thing you describe?
1. Is such an attack difficult?
1. Finally, has the topic been demonstrated "in the wild"? (i.e., _not_ in a laboratory setting)  If so, please briefly describe and cite a description (e.g., popular press, blog post, etc.)  If not, describe the hypothetical scenario where a vulnerability might be exploited.

Remember, this is only our first step, so you only need to do enough research to answer the above questions.  In particular, right now, you do not need to understand exactly how such attacks are carried out.  Although you may later work with a partner on your final project, for this part you should do your own independent research.  Later, when you have a partner, this background research will give you and your partner a nice selection of potential projects from which to choose.

Finally, be sure to write this paper for an audience with a general CS background, like a potential partner.  These writeups will be posted on the course website so that you and your classmates can find partners with the same project interests.

<hr style="border-color: purple;" />

## Submitting Your Paper

Please create a folder called `project` in your `readingresponse` repository on GitHub.  You should put your `.tex` and `.pdf` files there.

As you complete portions of this assignment, you should `commit` your changes and `push` them. <u>Commit early and often.</u> When the deadline arrives, we will retrieve the latest version of your work. If you are confident that you are done, please use the phrase `"Project Submission"` as the commit message for your final commit. If you later decide that you have more edits to make, it is OK. We will look at the latest commit before the deadline.

* <u>Be sure to push your changes to GitHub</u>.
* <u>Verify your changes on Github.</u> Navigate in your web browser to your private repository on GitHub. It should be available at [https://github.com/williams-cs/cs331readingresponse-{USERNAME}](https://github.com/williams-cs/cs331readingresponse-{USERNAME}). You should see all changes reflected in the files that you `push`. If not, go back and make sure you have both committed and pushed.
