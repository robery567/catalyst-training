#include <iostream>
#include <cmath>

#define PI 3.14159265

using namespace std;

double calculateTurnRadius(double wheelBase, double steeringAngle) {
    return wheelBase/sin(steeringAngle*PI/180);
}

double roundTwoDecimals(double number) {
   return round(number*100)/100;
}

pair<double, pair<double, double> > calculateNewDirection(double wheelBase, double distance, double steeringAngle) {
    // If our steering angle is 0 then it's clear we do no rotation
    if (steeringAngle == 0) {
        return make_pair(0.00, make_pair(0.00, distance));
    }

    double turnRadius = calculateTurnRadius(wheelBase, steeringAngle);
    double length = (2*PI) * turnRadius;

    double computedNewDirection = distance*360 / length;

    while (computedNewDirection > 360) {
        computedNewDirection -= 360;
    }

    // we round it to 2 decimals
    computedNewDirection = roundTwoDecimals(computedNewDirection);

    double radianAngle =  computedNewDirection*PI/180;

    double xCoordinate;

    //if (steeringAngle > 0) {
        xCoordinate = cos(radianAngle) * turnRadius;
    //} else {
    //    xCoordinate = turnRadius + cos(radianAngle) * turnRadius;
    //}

    while (computedNewDirection < 0) {
        computedNewDirection += 360;
    }

    double yCoordinate = sin(radianAngle) * turnRadius;

    // We round the coordinates to 2 decimals
    xCoordinate = roundTwoDecimals(xCoordinate);
    yCoordinate = roundTwoDecimals(yCoordinate);


    return make_pair(computedNewDirection, make_pair(xCoordinate, yCoordinate));
}

int main() {
    double x, y, z;

    cin >> x >> y >> z;

    auto computedNewDirectionResult = calculateNewDirection(x, y, z);

    cout << computedNewDirectionResult.second.first << " " << computedNewDirectionResult.second.second << " " << computedNewDirectionResult.first << endl;

    cout << endl << calculateTurnRadius(x, z);
    return 0;
}