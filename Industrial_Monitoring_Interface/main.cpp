#include "mainwindow.h"
#include <QApplication>
#include <rclcpp/rclcpp.hpp> // ◄ Librería de ROS2

int main(int argc, char *argv[])
{
    // 1. Inicializamos el entorno de ROS2
    rclcpp::init(argc, argv);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Ejecutamos la aplicación de Qt
    int resultado_qt = a.exec();

    // 2. Al cerrar la ventana, cerramos ROS2 limpiamente
    rclcpp::shutdown();

    return resultado_qt;
}
