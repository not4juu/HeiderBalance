# Heider Balance
Aplication was created based on proposed by Fritz Heider balance theory ( theory of attitude change). Regarding to theory Heider illuminated this thus as simple sentece:

> my friend’s friend is my friend

> my friend’s enemy is my enemy

> my enemy’s friend is my enemy

> my enemy’s enemy is my friend

### Description
Firstly you should comprehensible how heider theory works it will help you explore an  aplication. The main practicality of application is visualization impact on initial points of trajectory in accordance with differential eqations inspired by balance theory.   

### Application
Two main facilities of application :
  - Draws in real-time trajectories based on initial points in 3D
  - Creates statistic based on huge amount of initial points 

Application was written in **C++** language + **OpenGL**  library to render 3D scene + **QT**  - application GUI.

*Main Features*:
  - Solves differential equations based on Rungego-Kutty algorithm 
  - Draws planes based on ax+by+cz+d=0 equation.
  - Controls drawing (manipulate spped of drwaing , stop , start, restart drwaing) + progress bar shows the rendering porgress of trajectories.
  - Initial points selection (random, from definded range, based on small cubes(stere) etc.)
  - Coordinate system and stere properties 
  - Image snapshot saving
  - Generats well-formed xml statistic based on huge amount of initial points. 

- http://iopscience.iop.org/article/10.1209/0295-5075/118/58005/met
- http://www.ftj.agh.edu.pl/~kulakowski/wroclaw92.pdf
