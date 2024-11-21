#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

using namespace cv;
using namespace std;

// Function to draw clock hands
void drawHand(Mat &image, Point center, double angle, int length, Scalar color, int thickness) {
    Point end(center.x + length * cos(angle), center.y - length * sin(angle));
    line(image, center, end, color, thickness, LINE_AA);
}

// Function to convert time values to angles
double calculateAngle(double value, double maxValue) {
    return value * (2 * PI / maxValue);
}

int main() {
    // Get user input for hours, minutes, and seconds
    int hours, minutes, seconds;
    cout << "Enter time (HH MM SS): ";
    cin >> hours >> minutes >> seconds;

    // Validate input
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59) {
        cout << "Invalid time input!" << endl;
        return -1;
    }

    // Adjust hours to 12-hour format for the clock
    if (hours >= 12) hours -= 12;

    // Create a blank image
    int size = 500; // Clock size
    Mat clockImage(size, size, CV_8UC3, Scalar(255, 255, 255));

    // Clock center and radius
    Point center(size / 2, size / 2);
    int radius = size / 2 - 20;

    // Draw clock bezel
    circle(clockImage, center, radius, Scalar(0, 0, 0), 2);

    // Draw clock indexes
    for (int i = 0; i < 12; ++i) {
        double angle = calculateAngle(i, 12);
        Point inner(center.x + (radius - 20) * cos(angle), center.y - (radius - 20) * sin(angle));
        Point outer(center.x + radius * cos(angle), center.y - radius * sin(angle));
        line(clockImage, inner, outer, Scalar(0, 0, 0), 2, LINE_AA);
    }

    // Calculate angles for clock hands
    double hourAngle = calculateAngle(hours % 12 + minutes / 60.0, 12);
    double minuteAngle = calculateAngle(minutes + seconds / 60.0, 60);
    double secondAngle = calculateAngle(seconds, 60);

    // Draw clock hands
    drawHand(clockImage, center, hourAngle, radius * 0.5, Scalar(0, 0, 255), 6);     // Hour hand (red)
    drawHand(clockImage, center, minuteAngle, radius * 0.7, Scalar(0, 255, 0), 4);  // Minute hand (green)
    drawHand(clockImage, center, secondAngle, radius * 0.9, Scalar(255, 0, 0), 2);  // Second hand (blue)

    // Show the clock
    imshow("Analog Clock", clockImage);

    // Save the image to a file
    imwrite("analog_clock.png", clockImage);
    cout << "Clock image saved as 'analog_clock.png'." << endl;

    waitKey(0);
    return 0;
}