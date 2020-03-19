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


Installation Instructions:
1. docker pull klavins/enviro -a
2. run docker in respective folder
3. make
4. esm start
5. esm generate mazeRobot
6. enviro


