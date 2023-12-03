# olcUTIL_Geometry2D
A rare public repo for getting this utility file across the finish line

The olcPixelGameEngine is still a popular way to prototype ideas and create games in C++. To accompany it, I have created a set of "utility" files that encapsulate common functionality found in games and applications.

The Geometry2D (& PGE) utility file defines:
* Points
* Lines
* Circles
* Rectangles
* Triangles

I would like this file to provide functions that cover every combination Shape Vs Shape for the following functions:

* [true/false] **contains** (Shape A, Shape B) - Shape B entirely exists with Shape A. Points from Shape B can touch Shape A boundary.
* [true/false] **overlaps** (Shape A, Shape B) - Some part or Shape A and some part of Shape B occupy the same 2D space.
* [vector<points>] **intersects** (Shape A, Shape B) - Return all points (or none) where the boundaries of Shape A and Shape B overlap.
* [circle] **envelope_c** (Shape A) - Return a minimum size circle shape that fully encapsulates Shape A
* [rect] **envelope_r** (Shape A) - Return a minimum size rectangle shape that fully encapsulates Shape A

  In total there are 25 potential **contains**, 25 potential **overlaps**, 25 potential **intersects** and 10 potential **envelopes**, which need some maths to think about and some C++ expertise to implement efficiently. In short, it's a lot of work! There are many already implemented, but I've left a "TODO" where I think there is something missing. I know many of the community have code snippets buried away somewhere that satisfy some of these functions.

  All contributors will becredited in the header file, and this will be a fantastic resource/reference for those that might need a function or two for their other projects!

  **So, please, help me!**

I've included a simple test application (that will also need some improvement as the library matures), submit issues and PRs to get it finished :D

(Issues and PRs for PGE or QuickGUI will be ignored, please use appropriate repo/forums for that)

