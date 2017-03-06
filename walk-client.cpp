#include <iostream>

using namespace std;


// speed --> a double  between 0 and 100 to indicate the speed (100 is max)
// angle --> a double in radians where 0 is going straight, negative is to the left, and positive is to the right
void walk(double speed, double angle){
    // DREW FILL THIS IN

    // YOU CAN CALL OTHER FILES ETC. JUST ADD INCLUDES
cout << "walk command recieved\n";

}

void stopWalking(){
    // stops Darwin from walking
    // DREW WRITE THIS
    cout << "stopwalk command recieved\n";
}

void move(double motor_num, double motor_pos){
    //moves Darwin's motors to a certain position
    cout << "move_motors command recieved\n";
    cout << motor_num << "\n" << motor_pos << "\n";
}
