#include <iostream>

using namespace std;

// BEGIN CLASS home
class home {
    private:
        double length;
        double breadth;
        double height;

    public:
    // BEGIN FUNCTION getData

        // function to initialize private variables
        void getData(double len, double brth, double hgt) {
            length = len;
            breadth = brth;
            height = hgt;
        }
    // END FUNCTION getData

    // BEGIN FUNCTION calArea
        double calArea() {
            return length * breadth;
        }
    // END FUNCTION calArea

    // BEGIN FUNCTION calVolume
        double calVolume() {
            return length * breadth * height;
        }
    // END FUNCTION calVolume

};
// END CLASS home

// BEGIN CLASS main
int main() {

// create object of home1 class
home home;

// pass the values of private variables as arguments
home1.getData(42.5, 30.8, 19.2);

cout << "Area of home = " << home1.calArea() << endl;
cout << "Volume of home1 = " << home1.calVolume() << endl;

return 0;
}
//END CLASS main