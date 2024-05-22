# Functional Entity-Component-System
This is an ECS written in C++, using modern C++ facilities.  

I scrapped this one because I wanted to go lower-level and "make things faster" by not using the STL.
(...That may sound like very, very bad idea to you, but trust me, it's not - or that at least, it **wasn't!**)

...Also look at how naively it uses an `std::unordered_map`.
That kind of speed is just sad...

I knew of the "use a bitset as a sparse data structure!" optimization, but I wanted my ECS to be *fully dynamic*, as in - to allow users to be able to load ECS components at any time, which is why I didn't go for it, because... it requires you to have a fixed, statically-written, compile-time-ready `enum` of component types, and... I love the freedom of hackability!...
For the love of performance, please never use RTTI.

Enjoy looking at the code - have a good day! ":D!~
