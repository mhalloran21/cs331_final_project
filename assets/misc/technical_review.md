---
layout: page
title: 'How to Write a Technical Review'
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

If you have never written a technical review, be aware that it is a special kind of writing.  Unless you've had a career as a scientist, you might never have even seen one before.

Technical reviews serve a specific purpose: to evaluate the quality and impact of a piece of research for the purposes of publication.  Technical reviews are a part of the system of "peer review" used by scientists, and as such, they follow a number of conventions.

Some of you may already be excellent writers.  I have certainly encountered undergraduates who write better than I do.  Unfortunately, excellence in writing literature (or even literature reviews) does not generally translate to writing good technical reviews.  Think of this as a _new skill_ that you need to master.

For what it's worth, I think I'm probably pretty bad at writing fiction.

<hr class="style12" />

### What is the Purpose of a Technical Review?

Technical reviews are the primary form of communication that scientists use when discussing new work.  They tend to be formulaic (see my formula below) because it helps scientists quickly locate the salient points of a reviewer's arguments.  In essence, the goal of peer review is to decide whether a scientific work makes a compelling argument using strong enough evidence to warrant widespread publication.  Although peer review is an imperfect process, to end goal of peer review is to ensure that true and important facts are published and false and unimportant ones are not.

We will imitate this process.  Importantly, you should render a conclusion: does this paper say something true and important?

While most of you are not yet scientists, I believe that you should graduate with some familiarity with how the scientific community operates, particularly how computer scientists operate.  Beyond that, I find that writing a technical review sharpens my understanding of a piece of writing.  I occasionally change my mind about a technical article while writing one!  Summarizing somebody's work and critiquing their logic often reveals flaws in one's own understanding...

<hr class="style12" />

### Formula (and Grading Criteria)

Here are the things I am looking for in your review:

1. <span style="text-decoration: underline;">Your first paragraph is a concise summary of the paper.</span>  Think of it as answering the question "What did the authors claim?"  You may need to go back and reread bits of the paper to remember this.   <span style="font-weight: bold;">Please limit yourself to 7-10 sentences.</span>
1. <span style="text-decoration: underline;">Your second paragraph should enumerate what you think are some "pros" or "cons" of the work.</span>  You may either write this out as prose or just use bullets.  <span style="font-weight: bold;">Keep this brief.</span>  Also, if you can't think of anything nice to say... try harder.
1. <span style="text-decoration: underline;">The next section should explain in detail your opinion about the paper.</span>  Is it a <span style="font-weight: bold;">good</span> paper or a <span style="font-weight: bold;">bad</span> paper?  Why?  Is the topic important?  Do the authors address all of the salient points?  Do they have methodological issues?  Is their writing clear?  <span style="font-weight: bold;">Does the evidence support their claims?</span>  I want you to focus on the content of the article more than grammar/spelling here, but if the author's writing style makes the paper hard to understand, it is fine to say so.  <span style="font-weight: bold;">This section should have at least two paragraphs, one for the good and one for the bad points outlined in section 2.  Please keep it concise: if you're writing more than four paragraphs, you should condense your argument.</span>

If you put the three items above in a checklist, and then tick them off while you're writing, you're very likely to get a good grade on this.  Of course, I am looking for more than just satisfying the requirements; your response should be thoughtful.  We're going to discuss these in class!

Good technical reviews are around 900 words on average.  If you are writing less than 500 words, you probably haven't thought hard enough about the paper.  Although students sometimes write much more than that, you should make a concerted effort to keep your writing concise.

Technical reviews will be graded on a scale of 0-4.  You will get a zero if you turn nothing in.  A grade of 1 means that you turned in a low-quality paper review.  A 2 is an acceptable review that could use more work.  A 3 is a great review-- it informs your fellow "scientists" and helps them make informed decisions.  Hopefully, you'll get lots of 3s.  A 4 is an outstanding review.  These are difficult to write.  I probably won't award many 4s.  If you want advice on writing a great or outstanding review, come see me!  I am always happy to work with someone to improve their writing.

If you really want to go for a 4, here is <a href="http://cs.brown.edu/~sk/Memos/Paper-Reviews/">some additional advice</a> on writing good paper reviews.  Consider it guidance about the kind of review you should _aspire_ to write.  Note I have observed many professional scientists write sub-par paper reviews, and when I'm brave enough to go back and reread my own reviews, I sometimes find myself off the mark too.  Doing this consistently well takes dedication and practice.  However, for those who master this skill, it becomes a kind of technical communication _superpower_.

There's a lot to digest if you're reading this for the first time, so you may want to consider revisiting this page from time to time.  

<hr class="style12" />

### Example

Here's a particularly nice review from a former CS331 student who gave me permission to share it.  I like this review not just because it adheres to the _form_ of a technical review, but also because it is _thoughtful_, utilizing outside facts to make a counterargument against the paper.  The author tells us _what_ they think and _why_.

[Review of Bruce Schneier's "The Psychology of Security", by Isaac Benioff](isaac_benioff.pdf)

<hr class="style12" />

### Template

To assist you in formatting your technical paper review, your reading response repository comes supplied with a template to use.  When submitting, please be sure to commit _both_ your `.tex` file and your `.pdf` file to your GitHub repository.

You can "build" your LaTeX document into a PDF like so:

```
$ pdflatex my_paper_review.tex
```

LaTeX is already installed on lab computers, but if you are using your own machine, you may need to install it.  The easiest version to install is called [TeX Live](https://www.tug.org/texlive/), but you can also install via `apt` (Linux), Homebrew (macos), or Cygwin (Windows).
