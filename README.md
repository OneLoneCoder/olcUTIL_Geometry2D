# olcUTIL_Geometry2D
A stand-alone single header file that handles many and various 2D geometric interactions.

**NOTE! The olc::PixelGameEngine is NOT required to use this file, though it works very well with it!**

The Geometry2D (& PGE) utility file defines:
* Points
* Lines
* Circles
* Rectangles
* Triangles
* Rays

I would like this file to provide functions that cover every combination Shape Vs Shape for the following functions:
* [true/false] **contains** (Shape A, Shape B) - Shape B entirely exists with Shape A. Points from Shape B can touch Shape A boundary.
* [true/false] **overlaps** (Shape A, Shape B) - Some part or Shape A and some part of Shape B occupy the same 2D space.
* [vector<points>] **intersects** (Shape A, Shape B) - Return all points (or none) where the boundaries of Shape A and Shape B overlap.
* [optional<point>] **project** (Shape A, Shape B, Ray) - Project Shape A along Ray until it is in contact with Shape B (or not).
* [optional<normal, double>] **collide** (Shape A, Shape B, Ray) - Check if Shape A, when moved along Ray, collides with Shape B. If it does, return the distance along the ray and the normal of Shape B at the point of collision.
* [optional<ray>] **reflect** (Ray A, Shape B) - Return a ray (if possible) that is a reflection of incident Ray A, when reflected off Shape B.
* [point] **closest** (Shape A, Shape B) - Return a point on Shape A, which is closest to any part of Shape B.
* [point] **constrain** (Shape A, Point B) - Return a point within Shape A closest to Point B.
* [circle] **envelope_c** (Shape A) - Return a minimum size circle shape that fully encapsulates Shape A
* [rect] **envelope_r** (Shape A) - Return a minimum size rectangle shape that fully encapsulates Shape A

This project is a collaborative effort, and a continuous "Work-In-Progress" - If you feel you can contribute then please do so! There are many functions required, and we've not yet implemented all of them. Check the header file for the completion matrix. All contributors will becredited in the header file, and this will be a fantastic resource/reference for those that might need a function or two for their other projects!

  **So, please, help me!**

I've included a simple test application (that will also need some improvement as the library matures), submit issues and PRs to get it finished :D

(Issues and PRs for PGE or QuickGUI will be ignored, please use appropriate repo/forums for that)

