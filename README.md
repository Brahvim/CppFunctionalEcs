# Functional Entity-Component-System
This is an ECS written in C++, in C-style, using as less modern C++ facilities as possible.  
(SonarLint talked me into using `functional` once!)

Now, I scrapped *this one* because... well, forget that - *hey*, I HATED that use of `static_cast<>()`!  
Code's been optimized *a bunch* according to access patterns.

Not using the STL got kind-of confusing this time. However, I literally decided to move to C next!  
I didn't want to leave `namespace`s behind, but the C version *actually* feels easier to type!...  

Complete list of reasons as to why I chose C afterwards (part of *an "informal message"* I sent):  
"""  
- I like `namespace`s, but I don't want to `static_cast<>()` results from every call to `malloc()`/`calloc()`/`realloc()`, so...
- I also dislike being given C++ suggestions for my ECS, which I want to keep as close as possible to C.
- I was using `enum class`es that `: size_t` too, but it seems that even this is going away now.
- SonarLint somehow forced me into using `functional`.  
- I've also totally ignored references for some reason. Just wanted that "complete C feel", I guess.

- I want this code to run in many places as possible, which is why I'm writing it in C, I suppose. I don't really know, though. I just want to avoid mixing and mashing C and C++ a bit and avoid that useless `static_cast<>()` at all costs!

...Alright. So... I guess you now understand my motivation behind my wish to switch to C.  
"""

Enjoy looking at the code - have a good day! ":D!~
