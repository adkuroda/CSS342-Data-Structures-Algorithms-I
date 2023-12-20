#include "greedy_robot.h"
/**               CONSTRUCTORS                           */
GreedyRobot::GreedyRobot():max_steps_(0), num_paths_(0){
    robot_ = {0, 0};
    treasure_ = {0, 0};
}
GreedyRobot:: GreedyRobot(const int max_steps, const Point& start_pos,const Point& treasure_pos){
    max_steps_ = max_steps;
    num_paths_ = 0;
    robot_ = start_pos;
    treasure_ = treasure_pos;
}

/**               ACCESSORS                            */
int GreedyRobot::max_steps() const{
    return max_steps_;
}
int GreedyRobot::num_paths() const{
    return num_paths_;
}
vector<string> GreedyRobot::paths() const{
    return paths_;
}

/**               MUTATORS                            */
void GreedyRobot::set_steps(const int max_steps){
    max_steps_ = max_steps;
}

void GreedyRobot::set_num_paths(const int num_paths){
    num_paths_ = num_paths;
}

void GreedyRobot::set_robot(const Point &start_pos){
    robot_ = start_pos;
}
void GreedyRobot::set_treasure_pos(const Point &treasure_pos){
    treasure_ = treasure_pos;
}

/**               PRIVATE MEMBER FUNCTIONS                            */

/**
 *  Based on provide formula, this determines minimum number of steps from starting position
 *  to treasure position.
 */
int GreedyRobot::FindMinNumSteps() const{
    int x_result = treasure_.x_pos - robot_.x_pos;
    int y_result = treasure_.y_pos - robot_.y_pos;
    if(x_result < 0){
        x_result *= -1;
    }
    if (y_result < 0){
        y_result *= -1;
    }
    return x_result + y_result;
}

/**Assume robot is at the center and based on that this function determines which direction it suppose to move.
 * In case if the treasure and robot are in same position then it return 0, and if x or y cordinate of robot is same
 * returns -1. Otherwise returns respective quadrant on xy plane in respect to robot's position.
 */
int GreedyRobot::DetermineQuadrant() const{
    
    // variables are created to make the code more readable.
    bool x_status = robot_.x_pos == treasure_.x_pos;
    bool y_status = robot_.y_pos == treasure_.y_pos;
    int x_start = robot_.x_pos;
    int y_start = robot_.y_pos;
    int x_treasure = treasure_.x_pos;
    int y_treasure = treasure_.y_pos;

    if (x_status && y_status){
        return 0;
    }else if(x_status || y_status){
        return -1;
    }else if(y_treasure > y_start && x_treasure > x_start){
        return 1;
    }else if (y_treasure > y_start && x_treasure < x_start){
        return 2;
    }else if (y_treasure < y_start && x_treasure < x_start){
        return 3;
    }else{
        return 4;
    }
}
/** Determines what is the difference or change from robot position to treature on x cordinate.
 */
int GreedyRobot::ChangeInX() const{
    int change = robot_.x_pos - treasure_.x_pos;
    if (change < 0){
        change *= -1;
    }
    return change;
}
/** Determines what is the difference or change from robot position to treature on y cordinate.
 */
int GreedyRobot::ChangeInY() const{
    int change = robot_.y_pos - treasure_.y_pos;
    if (change < 0){
        change *= -1;
    }
    return change;
}
/** If treasure cordinate is not is 1st quadrant on XY plane in respect to robot cordinate, This function adds
 * change in x and y to to robot's position to make it in first quadrant.
 */
void GreedyRobot::ChangePointToFirstQaudrant() {
    treasure_.x_pos = robot_.x_pos + ChangeInX();
    treasure_.y_pos = robot_.y_pos + ChangeInY();
}

/** This function moves either to North or East or both direction, depending on how many steps it took or
 * and if it reached the max steps. If it is going N and reached the max steps, then it will stop and move
 * to E and vice-versa. If it did not reach the max steps then it will move recursively both directions.
 *  As soon as it reaches the treasure postion, it append the result to 
 */
int GreedyRobot::MoveToTreasure(int x_start, int y_start, string x_dir, string y_dir,int xstep, int ystep, string steps){
    if (x_start == treasure_.x_pos && y_start == treasure_.y_pos){
        paths_.push_back(steps);
        return 1;
    }
    int num_paths = 0;
    if (x_start <= treasure_.x_pos && y_start <= treasure_.y_pos){
        if (xstep >= max_steps_){
            num_paths += MoveToTreasure(x_start, y_start+1, x_dir, y_dir, 0, 1, steps + y_dir);
        }else if (ystep >= max_steps_){
            num_paths += MoveToTreasure(x_start +1, y_start, x_dir, y_dir, 1, 0, steps + x_dir);
        }else{
            num_paths += MoveToTreasure(x_start, y_start+1, x_dir, y_dir, 0, ystep + 1, steps + y_dir);
            num_paths += MoveToTreasure(x_start +1, y_start, x_dir, y_dir, xstep + 1, 0, steps + x_dir);
        }
    }
    return num_paths;
}


/**           PUBLIC ACCESS MEMBER FUNCTIONS                             */

/**
 * This function utilizing the helper functions and generates all the paths that meets the criteria.  Since
 *  MoveToTreasure function moves only one direction (NE), it trasforms treasures postion to be NE of
 *  robots posion. MoveToTreasure based on quadrant in respect to robot's position, it generates apropriate
 *  paths based on parameters.
 */
void GreedyRobot::FindPath(){
    if (max_steps() <= 0){
        cout << "Number of steps should be greater than 0" << endl;
        return;
    }
    int x_start = robot_.x_pos;
    int y_start = robot_.y_pos;
    int quadrant = DetermineQuadrant();
    switch (quadrant) {
        case 0:
            set_num_paths(0);
            break;
        case 1:
            // move NE
            set_num_paths( MoveToTreasure(x_start, y_start, "E", "N"));
            break;
        case 2:
            // move NW
            ChangePointToFirstQaudrant();
            set_num_paths(MoveToTreasure(x_start, y_start, "W", "N"));
            break;
        case 3:
            // move SW
            ChangePointToFirstQaudrant();
            set_num_paths(MoveToTreasure(x_start, y_start, "W", "S"));
            break;
        case 4:
            // move SE
            ChangePointToFirstQaudrant();
            set_num_paths(MoveToTreasure(x_start, y_start, "E", "S"));
            break;
            
        default:
            if (FindMinNumSteps() > max_steps_){
                set_num_paths(0);
            }else{
                if(robot_.x_pos == treasure_.x_pos){
                    if(robot_.y_pos < treasure_.y_pos){
                        num_paths_ = MoveToTreasure(x_start, y_start, "", "N");
                    }else{
                        ChangePointToFirstQaudrant();
                        num_paths_ = MoveToTreasure(x_start, y_start, "", "S");
                    }
                }else{
                    if(robot_.x_pos < treasure_.x_pos){
                        num_paths_ = MoveToTreasure(x_start, y_start, "E", "");
                    }else{
                        ChangePointToFirstQaudrant();
                        num_paths_ = MoveToTreasure(x_start, y_start, "W", "");
                    }
                }
            }
            break;
    }
}
/**
 *   Outputs all the paths and number of paths that meets the criteria
 */
ostream& operator<<(ostream& os, const GreedyRobot& robot){
    for(auto s: robot.paths_){
        os << s << endl;
    }
    os << "Number of paths: " << robot.num_paths();
    return os;
}


