# BEN - Better, Easier Ncurses

A renaming, continuation/reimagining, and vast improvement of NCU (NCursesUtils). While NCU is a super cool acronym, BEN is my name and NCU ended up being not so much a collection of utilities, but rather a complete wrapper of ncurses.

## But why?
Glad you asked. Ncurses can be a pain to work with, but BEN is here to help.

With BEN, you can quickly get snazzy command line interfaces (CLI) up and running quickly and with minimal boilerplate code.

But why even CLIs, you ask? They run on basically any hardware specs and can be run without a display server (X, Wayland, etc.), which means you can have fancy interfaces remotely, such as over SSH. Plus, there is even mouse support.

## But how?
Also a great question, theoretical person reading me.

#### High level explanation
BEN uses 3 main layers:

- BenView: The base that contains all the ncurses stuff
- BenServer: Takes events and sorta-kinda asyncronously tells BenView what to do
- Ben: User-facing code

## Count me in!
Your excitement for command line interfaces pleases me!

Right now, BEN is only going to be implemented in C++, but if this works out well enough, I'll try to port it to Python as well. Maybe even C, but don't quote me on that.
