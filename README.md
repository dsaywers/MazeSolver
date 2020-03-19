Maze Solver

The maze solver uses the enviro ("https://github.com/klavinslab/enviro") and elma ("https://github.com/klavinslab/elma")
packages developed by Eric Klavins for educational purposes.

The approach to the Maze Solver was to uses a wall follower approach similar to the Pledge algorithm. To implement this
a finite state machine is used with the following states:
1. Moving forward
2. Stop
3. Turn Right
4. Turn Left
5. Reverse


State transitions occur based on the following criteria:

forward --> stop : if object detected

stop --> turn right : if both sensor read small distances

stop --> turn left : if the left sensor senses an opening

turn_right --> stop : if desired orientation is met (~90 degree turn)

turn_left --> stop : if desired orientation is met (~90 degree turn)

turn_left or turn_right --> reverse : if robot stuck

reverse--> stop : if robot is a good distance away form object

stop --> forward  : if side sensor detects nearby wall and front sensor does not detect nearby object



Installation Instructions (in bash):
1. create MazeSolver directory 
2. git add .
3. git remote add origin https://github.com/dsaywers/MazeSolver.git
4. git pull origin master
5. docker pull klavins/enviro -a
6. docker run -p80:80 -p8765:8765 -v //your_directory:/source -it klavins/enviro:v1.6 bash
7. esm start (do not run esm generate as file's are already made)
8. make
9. enviro


