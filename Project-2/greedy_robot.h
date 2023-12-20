#ifndef GREEDY_ROBOT_H_
#define GREEDY_ROBOT_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;


// pos = position
typedef struct{
    int x_pos;
    int y_pos;
} Point;


class GreedyRobot{
public:
    //Constructors
    GreedyRobot();
    GreedyRobot(const int max_step, const Point& start_pos, const Point& treasure_pos);
    
    //Getters
    int max_steps() const;
    int num_paths() const;
    vector<string> paths() const;
    
    //Setters
    void set_steps(const int max_steps);
    void set_robot(const Point& start_pos);
    void set_treasure_pos(const Point& treasure_pos);
    /** Note: paths_ does not have setter since it is generated through calculation should not be able to set it.*/
     /** Note: num_paths_ does not have public setter since it is generated based on
      * actual viable paths. Being able to set would not be corect*/
  
    // Member functions public. Creates interface with the object 
    void FindPath();
    friend ostream& operator <<(ostream& os, const GreedyRobot& robot);

    vector<string> ObtainPaths(){
        return paths_;
    }
private:
    int max_steps_;
    int num_paths_;
    Point robot_;
    Point treasure_;
    vector<string> paths_;
    // Setter is private: someone else should not be able to set number of paths 
    // without finding all the paths. 
    void set_num_paths(const int num_paths);

    // Helper Member function to find the all the paths with given contraints. 
   
    int FindMinNumSteps() const;
    int DetermineQuadrant() const;
    void ChangePointToFirstQaudrant();
    int ChangeInX() const;
    int ChangeInY() const;
    int MoveToTreasure(int x_start, int y_start, string x_dir, string y_dir, int xstep = 0,
                     int ystep = 0, string steps = "");
    
};


#endif /* greedy_robot_hpp */


