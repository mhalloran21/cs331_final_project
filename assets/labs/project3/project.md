---
layout: page
title: 'Project Part 3: Final Project Submission'
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

**Due Friday, December 10 by 5pm**

For part 3 of your final project, you will:

* hand in an at-least-7-page paper using \\(\LaTeX{}\\),
* provide _original_ code that demonstrates your exploit, and
* deliver a _no more than_ 10 minute final presentation, including
* a short in-class demo.

Final project demonstrations will be on Saturday, December 18.  There will be two timeslots: from 1:30-3pm, and from 3:30-5pm.  Location TBD.

<hr style="border-color: purple;" />

## Final Paper

Your final paper, which covers _one_ security vulnerability or countermeasure, should be at least 7 pages in length.  Recall that your paper's discussion should focus on a class of security vulnerability/countermeasure rather than a specific instance of an attack.  You must describe this vulnerability in detail.  You should answer the following questions:

1. **NEW** <b>Abstract</b>  This is an executive summary of the entire paper, usually no more than 2 paragraphs in length.
1. <b>What is the vulnerability or countermeasure?</b>
1. <b>What resources are affected?</b>
1. <b>In what way are resources affected?</b> (confidentiality, integrity/authorization, availability, non-repudiation)
1. <b>Who would gain from undertaking such an attack/defense?</b>  What kind of background or resources does that person need?
1. <b>Is the attack/defense difficult?</b>
1. <b>Are the consequences of the attack/defense mild or severe?</b>
1. <b>What is the history of this attack/defense?</b>  Who invented it (if we know)?  Is it hypothetical or "in the wild"?  Has it ever been deployed maliciously?
1. **EXPAND** <b>How does it work?</b>  Please explain this in detail, as if you were the discoverer of this vulnerability and you are explaining how the attack works to another computer scientist.  This is the most important part of your paper.  You should:
  * start by conveying the intuition behind the vulnerability, using analogies and diagrams if necessary;
  * include aspects of computation such as memory and CPU time when discussing resources;
  * describe the problem formally, by framing the problem mathematically, using asymptotic arguments _when appropriate_;
  * frame the severity of the problem and the likelihood of an attack's success in terms of probability and expected values whenever possible; and
  * describe the attack/defense algorithm (whichever you choose) in detail, using pseudocode.
1. <b>Countermeasures/counterattacks</b>. You should describe the best known countermeasures/counterattacks, if there are any.
1. **NEW** <b>Conclusion</b>. What are the broader implications of this attack for technology and society?

In part 3 of the project, you should focus on writing the new sections, "Abstract" and "Conclusion", and expanding the "How does it work?" section.  Because you have now spent time implementing your attack, you should have additional insights into how the attack works.  Please provide those insights.

To make it easy for me to check whether you have included the relevant sections, I encourage you to provide one section heading corresponding with each of the bolded topics above, ideally in the order that I provide.

When submitting, use \\(\LaTeX{}\\) for this assignment, and be sure to turn in a `.pdf` file along with your `.tex` file.

I will be posting your writeup on our course webpage for your classmates to read, so please be sure to write something that you would be proud to let others read!  Your paper will be graded on objective criteria (like: Did you answer the questions above?  Do you have spelling or grammar problems?) as well as subjective and aesthetic criteria (like: Is your paper readable? Is there a compelling and coherent narrative?).

<hr style="border-color: purple;" />

## Your Presentation

Your final presentation should be <b>no more than 10 minutes in length</b>, and it should have no more than 5-10 slides.  It should

1. describe the history and significance of your attack,
1. how it works,
1. should include a short demo (if possible),
1. and conclude by briefly discussing defenses against such an attack

Remember, you only have 10 minutes to give your talk, so please keep it high-level and concise.  Think of your talk as an advertisement for your paper.  <u><b>Any talk longer than 12 minutes will lose 10 points per every extra minute used.</b></u>  I will give you a two-minute warning at the 8-minute mark.  If you see that, please wrap it up ASAP!  <b>Practice your talk</b>, and remember, we can read your paper if we want to know more.

A good way to structure your talk is to answer the following questions, which are inspired by the [Heilmeier Catechism](https://www.darpa.mil/work-with-us/heilmeier-catechism):

* What is the attack? Articulate your objectives using absolutely no jargon.
* Who cares? What difference does the attack make?
* How does it work?
* What are the risks of your attack?
* How expensive is the attack for the attacker?
* How long does it take?
* What can a defender do to stop such attacks?

Here are some wonderful tips on [delivering a technical talk](https://www.youtube.com/watch?v=Z2NToI2XIR8) by Simon Peyton-Jones.  Although the focus of Simon's tips are for research talks, most of the lessons apply.  If you really want to kick your talk up a notch, you may enjoy [this talk by Simon Sinek](https://www.ted.com/talks/simon_sinek_how_great_leaders_inspire_action).

Finally, here's a [20-minute talk delivered by me](https://www.youtube.com/watch?time_continue=985&v=WTnwl_skD-Q), which is actually two 10-minute talks back to back.  It's not a perfect talk, by any means.  But my biggest objection to the talk is that I am out of shape. :(

<hr style="border-color: purple;" />

## Attack Code

Your code should clearly demonstrate the attack you describe.  Although your paper discusses a class of attack, your code may focus specifically on one instance.  The code you submit must be original work, but it may be inspired by code you've looked at.  Along with your code, you must provide two short documents in Markdown format:

1. A `BUILDING.md` file that explains how to build your code, and
1. a `RUNNING.md` file that explains how to run your code and how to interpret the output.

You are strongly encouraged to provide a `Makefile` to help build your code.  If your attack code makes architectural assumptions, please be sure to include that information in your `BUILDING.md` and/or `RUNNING.md` files.  For example, if your attack must be run on the 32-bit version of Raspbian 10 on ARM, please say so.  You are not required to use your Raspberry Pi in your project, although you are welcome to do so.  You are allowed to use third-party libraries for this project, as long as such libraries do perform the essential parts of an attack, which must be written by you.  Please be sure to either include whatever libraries you use or explain how to obtain them.

To demonstrate that your code is original work, I expect to see ample comments that demonstrate that you understand its function.  Please be sure to comment your code.  If you are not sure whether you provided enough comments, err on the side of providing more!

Finally, if you've looked at someone else's code for inspiration, be sure to provide a citation.  If you are worried about sufficiently differentiating your code from someone else's, please come speak with me.

<hr style="border-color: purple;" />

## Tips on Technical Writing

I will not reproduce these tips here, but if you are looking for some, go have a look at the section in [part 2 of the project](../project2/project.html).

<hr style="border-color: purple;" />

## Submitting Your Paper

Submit your paper and any necessary supporting materials (e.g., code experiments) to your reading response repository on GitHub.  You should put your `.tex` and `.pdf` files in a folder called `project/final`.

As you complete portions of this assignment, you should `commit` your changes and `push` them. <b>Commit early and often.</b> When the deadline arrives, we will retrieve the latest version of your work. If you are confident that you are done, please use the phrase `"Project Submission"` as the commit message for your final commit. If you later decide that you have more edits to make, it is OK. We will look at the latest commit before the deadline.

* <b>Be sure to push your changes to GitHub</b>.
* <b>Verify your changes on Github.</b> Navigate in your web browser to your private repository on GitHub.  You should see all changes reflected in the files that you `push`. If not, go back and make sure you have both committed and pushed.

<hr style="border-color: purple;" />

## Questions?

Feel free to ask me.  I tried to be very explicit about what you need to provide for me, but chances are, you are not the only one with your question!  Good luck, and I look forward to your presentation!
