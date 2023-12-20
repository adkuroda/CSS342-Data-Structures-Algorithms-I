
#include "greedy_robot.h"

/** This is a driver for GreedyRobot class. It parses input arguments ensures
 *   It meets all the creteria before proceeding create a GreedyRobot and
 *   finding a path.
 */

int main(int argc, const char * argv[]) {
    if (argc > 6){

        cout << "Please enter valid input: There should be 6 arguments." << endl;
    }else if(argc < 6){
        cout << "Please enter valid input: There should be 6 arguments." << endl;  
    }else{
        int max_steps  = stoi(argv[1]);
        int x_robot  = stoi(argv[2]);
        int y_robot  = stoi(argv[3]);
        int x_treasure  = stoi(argv[4]);
        int y_treasure  = stoi(argv[5]);
        Point robot{x_robot, y_robot};
        Point treasure{x_treasure, y_treasure};
        GreedyRobot greedy_robot(max_steps, robot, treasure);
        greedy_robot.FindPath();
        cout << greedy_robot << endl;
    }
    
    return 0;
}

