---
layout: page
title: 'Project Part 2: Proposal'
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

**Due Sunday, November 14 by 11:59pm**

For part 2 of your final project, you will:

* choose a partner for your final project (or choose to work by yourself),
* choose a topic both partners are interested in,
* write a five page proposal.

Recall that your final project will culminate in a final research paper, a programmed demonstration written by you and your partner, and a 10 minute presentation in front of the class.  When feasible, the most convincing presentations demonstrate your topic by running your code in front of the class.

Although you ultimately have to convince me (Dan) that your project is a good idea, part 2 really is about convincing yourself.  After this project deadline, you will be off to the races to develop your attack/countermeasure.  As always, I am happy to share my expertise with you, but I am not an expert in everything.  The burden will be on you to successfully achieve the goals you set out for yourself.  Use this phase to demonstrate to yourself that you and your partner can get it done.

<hr style="border-color: purple;" />

## Step 0: Finding a partner

When looking for a partner, keep in mind that you are not limited to choosing a project idea that you came up with yourself.

You should feel welcome to reach out to any of your classmates via email.  If you already have a partner and someone reaches out to you, remember to be considerate, and politely let them know that you already found a partner.  It's sometimes hard to work up the courage to ask somebody to partner up!

If you are having trouble finding a partner, or if you would like my assitance, I am happy to help.  Just send me an email.

<hr style="border-color: purple;" />

## Step 1: Tell me who your partner will be

Please [fill out this form](https://forms.gle/x4QzmJK41wjhbQz2A) by Sunday, October 31 at 11:59pm.  I need this information so that GitHub project repositories can be created for you and your partner.

You may choose to work by yourself.  Be aware that working by yourself may be significantly more challenging.

<hr style="border-color: purple;" />

## Step 2: Proposal

For this assignment, you should choose _one_ security related topic.  Recall that you should focus on a _class_ of security vulnerability/countermeasure rather than a specific instance of an attack.  Describe your topic in detail.  You should answer the following questions:

1. What is the vulnerability/countermeasure?
1. What resources are affected?
1. In what way are resources affected? (confidentiality, integrity, authenticity/non-repudiation, availability)
1. Characterize potential attackers.  What are their motivations?  Do they need special skills, resources, etc., to be successful?
1. Is the attack difficult?
1. Are the consequences of an attack mild or severe?
1. What is the history of the attack/countermeasure?  Who invented it (if we know)?  If you're focusing on an attack, is it hypothetical or "in the wild"?  If you're focusing on a countermeasure, is it hypothetical or has it been deployed?
1. _How_ does it work?  Explain in detail, as if you were the discoverer of this vulnerability and you are explaining how the attack works to another computer scientist.  This is the most important part of your proposal.  Recall how the research papers we read describe their contributions.  You should:
  * start by conveying the intuition behind the vulnerability, using analogies and diagrams if necessary;
  * describe memory and CPU use, and potentially other resources when appropriate;
  * describe the problem formally, by framing the problem mathematically, using asymptotic arguments when they add clarity;
  * frame the severity of the problem and the likelihood of an attack's success in terms of probability and expected values whenever possible; and
  * describe the attack/countermeasure algorithmically, using pseudocode.
1. Finally, you should describe the best known countermeasures/counterattacks, if there are any.

Your writeup must be at least 5 pages, but you may exceed that amount if needed.  Remember:

* <u>You are trying to convince yourself</u> that you can pull off a demonstration of this vulnerability.  I am going to trust that you are the best judge of your own abilities.  If you're not sure, be conservative-- you can always expand the scope of your project if you find that your project is too easy.
* Any text that you write in your project proposal can be reused in the final paper, so if writing more helps you to understand the problem, write more.
* Your demonstration code, which you will write in part 3, needs to be your own work, but the vulnerability you describe in this paper need not be novel.  I strongly discourage you from attempting to discover _new_ vulnerabilities.  Doing so is difficult and takes a lot of effort!
* If spending a little time creating code experiments helps you understand your vulnerability, do it!  This is time well spent at this phase.

When submitting, use LaTeX for this assignment, and be sure to turn in a `.pdf` file along with your `.tex` file.

<hr style="border-color: purple;" />

## Tips on Technical Writing

Technical writing is a challenging pursuit.  You may even already be an excellent writer.  But you should consider technical writing a totally separate skill from ordinary writing, deserving of your attention.  Why?  In addition to all the virtues that ordinary writing has, like lucidity or beauty, technical writing must also convey an idea _accurately_, _clearly_, and _concisely_.  The best technical writers can explain complex topics without jargon, in a manner that is intuitive and fun.  People who are especially good at this, like [Richard Feynman](https://www.youtube.com/watch?v=XRxAn2DRzgI) or [Grace Hopper](https://www.youtube.com/watch?v=9eyFDBPk4Yw), explain beautifully, and completely alter the way we think about something.

It takes a lot of practice to get to that level.  And you probably won't get there on your first try.  In fact, you probably _shouldn't_ try to get there on your first try.  Here's how I write:

1. First, I just try to get the ideas down.  I usually start with an outline.
2. After I have all the parts, I look at them and ask "what story can I tell?"  I do this because of human nature: people tune out if the story isn't [about them](https://www.ted.com/talks/simon_sinek_how_great_leaders_inspire_action).
3. I then tell that story, as directly as I can, without style or ornamentation.
4. After I've told my story, I start editing.  I make the story simpler.  I remove unnecessary asides, footnotes, parenthetical remarks.  I make sentences shorter.  I use simpler words.
5. Now I have a friend read it.  Do they understand it the first time?  When my friend doesn't understand, I ask myself why.  It's not usually because I got my facts wrong.  It's usually because I painted the wrong picture or I used confusing language.  What's the right picture?  Can I use simpler words?

Notice that I never _added_ style or ornamentation.  Also, this process could just go on forever.  At some point, you will have to stop and submit something, but why not give it a try?  You won't just have a better paper, you'll be happier with yourself, because you did a _good job_.

<hr style="border-color: purple;" />

## Submitting Your Paper

Submit your paper and any necessary supporting materials (e.g., code experiments) to your repository on GitHub.  You should put your `.tex` and `.pdf` files there.

As you complete portions of this assignment, you should `commit` your changes and `push` them. <u>Commit early and often.</u> When the deadline arrives, we will retrieve the latest version of your work. If you are confident that you are done, please use the phrase `"Project Submission"` as the commit message for your final commit. If you later decide that you have more edits to make, it is OK. We will look at the latest commit before the deadline.

* <u>Be sure to push your changes to GitHub</u>.
* <u>Verify your changes on Github.</u> Navigate in your web browser to your private repository on GitHub.  You should see all changes reflected in the files that you `push`. If not, go back and make sure you have both committed and pushed.
