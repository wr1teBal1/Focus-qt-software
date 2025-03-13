#include <QApplication>
// #include <ros/ros.h>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Initialize ROS
    // ros::init(argc, argv, "ros_qt_controller");

    // Initialize Qt
    QApplication app(argc, argv);

    // Create main window
    MainWindow mainWindow;
    mainWindow.show();

    // Run the Qt event loop
    return app.exec();
}