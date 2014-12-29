Fractals
=============

This is a basic framework for rendering 3D fractal plots based on lines. 

It was all developed in C++ and the graphics are done using OpenGL. 

The whole system is developed around the 'Branch' class that models a tree branch. The basic idea is that the user will call the init method, that takes all the basic parameters and recurively creates child branches. The main available parameters are: 

- maxAngle: Next child will be a branch with an angle that is within that range, generated randomly at birth. 

- depth: Number of 'generations' of child branches, i.e., depth of the tree. 

- maxChilds: Number of direct childs per branch. To highlight the tree structure, each generation is assigned a different collor, following a determied collor gradient.