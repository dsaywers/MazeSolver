#ifndef __WANDERER_AGENT__H
#define __WANDERER_AGENT__H 
#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include "enviro.h"

using namespace enviro;


class MovingForward : public State, public AgentInterface {
    /*
    Move forward State:
    Only transitions to and from stop
    Transition to stop if:
    a) front sensor detects object in path
    b) side sensor detects opening
    */
        public:
        void entry(const Event& e) {
            decorate("<circle x='-5' y='5' r='5' style='fill: green'></circle>");
        }
        void during() { 
               track_velocity(3.5,0);
               label("Moving Forward", 20, 5);
            if ((sensor_value(0) < 30) || (sensor_value(1)>75)) {
                emit(Event(tick_name));
            }     

        }
        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;

    };

class Reverse : public State, public AgentInterface {
    /*
    Reverse State:
    Only transitions to and from stop
    Transition to stop if:
    a) robot has reversed far enough away from detected object
    */

        public:
        void entry(const Event& e) {
            decorate("<circle x='-5' y='5' r='5' style='fill: green'></circle>");
        }
        void during() { 
               track_velocity(-1,0);
               label("Reverse", 20, 5);
            if ((sensor_value(0) > 20)) {
                emit(Event(tick_name));
            }     

        }
        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;

    };



class Rotate_CW : public State, public AgentInterface {

    /*
    Turn Right State:
    Transition to stop if:
        robot has rotated enough to no longer detect nearby obstructing object
    Transition to Reverse if:
        object is too close for robot to rotate
    */

        public:
        void entry(const Event& e) { 
            rate = rand() %1 == 0 ? 1 : -1; 
            decorate("<circle x='-5' y='5' r='5' style='fill: red'></circle>");
        }
        void during() { 

            //if robot pointed in first quandrant rotate to pi/2
            if ((angle()>0) && (angle()<=(M_PI/2))) {
                desired_heading = (M_PI/2)+0.05;
            }
            //if robot pointed in fourth quandrant rotate to 0deg
            else if (((angle()<0) && (angle()>=(-M_PI/2))) || ((angle()<2*M_PI) && (angle()>=(3*M_PI/2)))) {
                desired_heading = -0.05;
            }
            //if robot pointed in second quandrant rotate to 3pi/2
            else if (((angle()+0.05<-M_PI/2) && (angle()+0.05>=(-M_PI))) || ((angle()+0.05<3*M_PI/2) && (angle()+0.05>=(M_PI)))) {
                desired_heading = -(M_PI/2)+0.05;
            }
            //if robot pointed in third quandrant rotate to pi
            else if (((angle()<-M_PI) && (angle()>=(-3*M_PI/2))) || ((angle()+0.05<M_PI) && (angle()+0.05>=(M_PI/2)))) {
             if (angle()>0){
                desired_heading = M_PI+0.05;
             }
             else {
                 desired_heading = -M_PI+0.05;
             }
                
            }
            else {
                desired_heading=0; //reset
            }
            // rotate to desired heading based on what quandrant the robot is oriented
            track_velocity(0,5*sin(desired_heading-angle()) - 100*angular_velocity());
            label(std::to_string(angle()), 20, 5);
            //if object is very close revrse
            if (sensor_value(0)<15) {
                emit(Event(tick_name_2));
            }
            //the next two cases are to calculate if angle() is close to desired_heading
            else if ((angle()<M_PI/2) && ((std::abs(angle())-std::abs(desired_heading))<0.01)) {
                emit(Event(tick_name));
            }
            else if ((angle()>M_PI/2) && ((std::abs(desired_heading)-std::abs(angle()))<0.01)) {
                emit(Event(tick_name));
            }
            
        }

        double rate;
        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
        void set_tick_name_2(std::string s) { tick_name_2 = s; }
        std::string tick_name_2;
        int counter;
        double desired_heading;


    };

class Rotate_CCW : public State, public AgentInterface {
    /*
    Turn Left State
    Transition to stop if:
        robot has rotated enough to reach desired heading
    Transition to Reverse if:
        object is too close for robot to rotate
    */
        public:
        void entry(const Event& e) { 
            rate = rand() %1 == 0 ? 1 : -1; 
            decorate("<circle x='-5' y='5' r='5' style='fill: red'></circle>");
        }
        void during() { 
            //if fourth quandrant rotate left toward 0deg
            if ((angle()>0) && (angle()<=(M_PI/2))) {
                desired_heading = -0.1;
            }
            //if in first quandrant rotate left toward pi/2
            else if (((angle()<0) && (angle()>=(-M_PI/2))) || ((angle()<2*M_PI) && (angle()>=(3*M_PI/2)))) {
                desired_heading = -(M_PI/2)-0.1;
            }
            //if in second quandrant rotate towards pi
            else if (((angle()-0.07<-M_PI/2) && (angle()-0.07>=(-M_PI))) || ((angle()<3*M_PI/2) && (angle()>=(M_PI)))) {
                desired_heading = (M_PI)-0.1;
            }

            //if in third quandrant rotate towards 3pi/2
            else if (((angle()<-M_PI) && (angle()>=(-3*M_PI/2))) || ((angle()<M_PI) && (angle()>=(M_PI/2)))) {
                desired_heading = (M_PI/2)-0.1;   
            }



            //if sensor reads large distance move forward and turn
            if (sensor_value(0)>100){
                track_velocity(1.5,4*sin(desired_heading-angle()) - 100*angular_velocity());
            }
            //else just turn left
            else {
                track_velocity(0,5*sin(desired_heading-angle()) - 100*angular_velocity());
            }
            
            label(std::to_string(angle()), 20, 5);
            //the next two cases are to calculate if angle() is close to desired_heading
            if ((angle()>M_PI/2) && ((std::abs(angle())-std::abs(desired_heading))<0.05)) {
                emit(Event(tick_name));
            }
            else if ((angle()<M_PI/2) && ((std::abs(desired_heading)-std::abs(angle()))<0.05)) {
                emit(Event(tick_name));
            }
            //if object too close reverse
            else if (sensor_value(0)<25) {
                emit(Event(tick_name_2));
            }
            
        }
        double rate;
        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
        void set_tick_name_2(std::string s) { tick_name_2 = s; }
        std::string tick_name_2;
        double desired_heading;
     
    };

class Stop: public State, public AgentInterface {

    /*
    Stop State
    Transition to turn left :
        if front sensor reads close and side sensor far
        or if side sensor reads far
    Transition to turn right :
        if object is in path
    Transition to move forward:
        if not object in path
    */
        public:
        void entry(const Event& e) {}
        void during() { 
            auto vel=velocity();
            track_velocity(0,0);
            //turn left
            if ((sensor_value(0)<30) && (sensor_value(1)>50)){
                emit(Event(tick_name_2));
            } 
            //turn left
            else if (sensor_value(1)>50) {
                emit(Event(tick_name_2));
                
            } 
            //turn right
            else if (sensor_value(0)<30){
                    emit(Event(tick_name));
            } 
            // move forward
            else if (sensor_value(0)>30) {
                emit(Event(tick_name_3));
            }  
            // move forward
            else {
                emit(Event(tick_name_3));
            }

        }
        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name= s; }
        std::string tick_name;
        void set_tick_name_2(std::string s) { tick_name_2= s; }
        std::string tick_name_2;
        void set_tick_name_3(std::string s) { tick_name_3= s; }
        std::string tick_name_3;

    };

class WandererController : public StateMachine, public AgentInterface {

    public:
    WandererController() : StateMachine(){
            set_initial(moving_forward);
            tick_name = "tick_" + std::to_string(rand()%1000);
            tick_name_2 = "tick_" + std::to_string(rand()%1000);
            tick_name_3 = "tick_" + std::to_string(rand()%1000);
            tick_name_4 = "tick_" + std::to_string(rand()%1000);
            tick_name_5 = "tick_" + std::to_string(rand()%1000);
            tick_name_6 = "tick_" + std::to_string(rand()%1000);
            tick_name_7 = "tick_" + std::to_string(rand()%1000);
            add_transition(tick_name, moving_forward, stop);
            add_transition(tick_name_2, stop, rotate_cw);
            add_transition(tick_name_4, stop, rotate_ccw);
            add_transition(tick_name_3, rotate_cw, stop);
            add_transition(tick_name_5, rotate_ccw, stop);
            add_transition(tick_name_6, stop, moving_forward);
            add_transition(tick_name_7, rotate_cw, reverse);
            add_transition(tick_name_7, rotate_ccw, reverse);
            add_transition(tick_name, reverse, rotate_cw);
            
            moving_forward.set_tick_name(tick_name);
            stop.set_tick_name(tick_name_2);
            rotate_cw.set_tick_name(tick_name_3);
            stop.set_tick_name_2(tick_name_4);
            rotate_ccw.set_tick_name(tick_name_5);
            stop.set_tick_name_3(tick_name_6);
            rotate_cw.set_tick_name_2(tick_name_7);
            rotate_ccw.set_tick_name_2(tick_name_7);
            reverse.set_tick_name(tick_name);

    }
    MovingForward moving_forward;
    Rotate_CW rotate_cw;
    Rotate_CCW rotate_ccw;
    Stop stop;
    Reverse reverse;
    std::string tick_name;
    std::string tick_name_2;
    std::string tick_name_3;
    std::string tick_name_4;
    std::string tick_name_5;
    std::string tick_name_6;
    std::string tick_name_7;

};

class Wanderer : public Agent {
    public:
    Wanderer(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    WandererController c;
};

DECLARE_INTERFACE(Wanderer)

#endif