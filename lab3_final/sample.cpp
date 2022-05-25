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

// BEGIN FUNCTION main
int main() {

// create object of home class
home obj;

// pass the values of private variables as arguments
obj.getData(42.5, 30.8, 19.2);

cout << "Area of home = " << obj.calArea() << endl;
cout << "Volume of home = " << obj.calVolume() << endl;

return 0;
}
// END FUNCTION main