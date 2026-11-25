#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "worker.h"
#include <QLabel>
#include <QThread>
#include "definiciones.h"
#include <QTimer>
#include <QVector>
#include <QDateTime>
#include <QFile>
#include <QtMath> // añadido para ejrcicio 4
#include <QTextStream> //intorduccion de librerias
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct RegistroCajas {//añadido estructura
    int numeroCajas;
    qint64 marcaTiempo;
};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void cambiar_aspecto_actuadores(bool H1, bool H2, bool H3, bool H4, bool H5);
    void cambiar_aspecto_fines_de_carreras(bool S13, bool S14, bool S15, bool S16);
    void cambiar_aspecto_pulsadores(bool S1, bool S2);
    void cambiar_aspecto_sensores_piezas(bool S7, bool S8);
    void onThreadStarted();
    QStringList configurar_nss();
    QStringList configurar_iss();
    void iniciar_opcworker();
    void closeEvent(QCloseEvent *e);
    void cambiar_mensaje();
    void anima_icono(QLabel *milabel, QString ruta);
    void cambiar_height(QLabel *milabel, int valor_height);
    void cambiar_x(QLabel *milabel, int valor_x);
    void procesar_E9(bool value);
    void procesar_E8(bool value);
    void procesar_E6(bool value);
    void procesar_E2(bool value);
    void procesar_E10(bool value);
    void procesar_E4(bool value);
public slots:
    void onvalorBoolChanged(int which, bool value);
    void slot_temporizador_arriba_abajo();
    void slot_temporizador_izquierda_derecha();
    void slot_temporizador_abajo_arriba();
    void slot_temporizador_derecha_izquierda();
    void onOpcConnected();
signals:
    void set_E9();
    void reset_E9();
    void set_E8();
    void reset_E8();
protected:

private slots:

    void guardarDatosVector(); //introduccion de funcion

    void on_b_ponerpieza_clicked();

    void on_b_quitarpieza_clicked();

private:

    Ui::MainWindow *ui;

    int contadorCajasActuales = 0;//Aqui añadimos el contador de cajas
    QTimer *TimerCajas;  //Declaramos nuestro vector para llevar el tiempo
    QVector<RegistroCajas> vectorLogs; //Vector de Registro Cajas guardado en el vector llamado vectorlogs

    Worker *m_worker;
    QThread m_workerThread;
    TVariablesPLC variablesPLC;

    QTimer temporizador_arriba_abajo;
    QTimer temporizador_izquierda_derecha;
    QTimer temporizador_abajo_arriba;
    QTimer temporizador_derecha_izquierda;
    QTimer temporizador_locucion;
    void reproducir_locucion_parada();

    bool m_outputsInitialized = false;

    QList<int> historialCajas; // Aquí guardaremos TODOS los valores para la estadística ejercicio 4
    void actualizarEstadisticas(); // Función que hará el cálculo
    // ─── VARIABLES Y MÉTODOS PARA ROS2 (EJERCICIO 6) ───
    std::shared_ptr<rclcpp::Node> nodo_ros;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr suscriptor_ros;
    QTimer temporizador_ros;

    void slot_spin_ros();
    void callback_mensaje_ros(const std_msgs::msg::Bool::SharedPtr msg);
};
#endif // MAINWINDOW_H
