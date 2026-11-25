#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QProcessEnvironment>
#include <QCloseEvent>
#include <QDebug>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_outputsInitialized = false;
    variablesPLC.H1 = false;
    variablesPLC.H2 = false;
    variablesPLC.H3 = false;
    variablesPLC.H4 = false;
    variablesPLC.H5 = false;
    variablesPLC.S1 = false;
    variablesPLC.S13 = false;
    variablesPLC.S14 = false;
    variablesPLC.S15 = false;
    variablesPLC.S16 = false;
    variablesPLC.S2 = false;
    variablesPLC.S7 = false;
    variablesPLC.S8 = false;
    variablesPLC.E0 = false;
    variablesPLC.E1 = false;
    variablesPLC.E2 = false;
    variablesPLC.E3 = false;
    variablesPLC.E4 = false;
    variablesPLC.E5 = false;
    variablesPLC.E6 = false;
    variablesPLC.E7 = false;
    variablesPLC.E8 = false;
    variablesPLC.E9 = false;
    variablesPLC.E10 = false;
    variablesPLC.E11 = false;
    variablesPLC.E12 = false;
    variablesPLC.E13 = false;
    variablesPLC.E14 = false;
    variablesPLC.E15 = false;
    variablesPLC.E16 = false;
    variablesPLC.E17 = false;
    variablesPLC.E18 = false;
    variablesPLC.E19 = false;
    variablesPLC.E20 = false;
    variablesPLC.E21 = false;
    variablesPLC.E22 = false;
    variablesPLC.E23 = false;
    variablesPLC.E24 = false;
    cambiar_aspecto_actuadores(false, false, false, false, false);
    cambiar_aspecto_fines_de_carreras(false, false, false, false);
    cambiar_aspecto_pulsadores(false, false);
    cambiar_aspecto_sensores_piezas(false, false);
    ui->texto->clear();
    iniciar_opcworker();

    anima_icono(ui->animacion_H1, "/home/juno/informaticaai/PRACTICA2026_carpeta/ejemplo_opc_cliente/recursos/girar.gif");
    ui->animacion_H1->setVisible(false);
    connect (&temporizador_arriba_abajo, &QTimer::timeout, this, &MainWindow::slot_temporizador_arriba_abajo);
    connect (&temporizador_izquierda_derecha, &QTimer::timeout, this, &MainWindow::slot_temporizador_izquierda_derecha);
    connect (&temporizador_abajo_arriba, &QTimer::timeout, this, &MainWindow::slot_temporizador_abajo_arriba);
    connect (&temporizador_derecha_izquierda, &QTimer::timeout, this, &MainWindow::slot_temporizador_derecha_izquierda);

    cambiar_height(ui->label_eje_grua, 10);

    // --- Temporizador de cajas y estadísticas (Ejercicio 4) ---
    int tiempo = 10000;
    TimerCajas = new QTimer(this);
    connect(TimerCajas, &QTimer::timeout, this, &MainWindow::guardarDatosVector);
    TimerCajas->start(tiempo);
    actualizarEstadisticas();

    // --- Voz para la Parada de Emergencia (Ejercicio 5) ---
    connect(&temporizador_locucion, &QTimer::timeout, this, &MainWindow::reproducir_locucion_parada);

    // --- Integración y Nodo de ROS2 (Ejercicio 6) ---
    nodo_ros = rclcpp::Node::make_shared("nodo_qt_cliente");

    suscriptor_ros = nodo_ros->create_subscription<std_msgs::msg::Bool>(
        "/mensajeS7",
        10,
        std::bind(&MainWindow::callback_mensaje_ros, this, std::placeholders::_1)
        );

    connect(&temporizador_ros, &QTimer::timeout, this, &MainWindow::slot_spin_ros);
    temporizador_ros.start(20);
}


void MainWindow::procesar_E2(bool value){
    static bool firsttime = true;
    if (firsttime){
        firsttime = false;
    }
    else{
        if (value){
            temporizador_abajo_arriba.start(20);
            ui->animacion_H1->setVisible(true);
        }
        else{
            temporizador_abajo_arriba.stop();
            ui->animacion_H1->setVisible(false);
            cambiar_height(ui->label_eje_grua, 10);
        }

    }
    variablesPLC.E2 = value;
}

void MainWindow::procesar_E10(bool value){
    static bool firsttime = true;
    if (firsttime){
        firsttime = false;
    }
    else{
        if (value){
            temporizador_arriba_abajo.start(20);
            ui->animacion_H1->setVisible(true);
        }
        else{
            temporizador_arriba_abajo.stop();
            ui->animacion_H1->setVisible(false);
            cambiar_height(ui->label_eje_grua, 301);
        }
    }
    variablesPLC.E10 = value;
}

void MainWindow::procesar_E6(bool value){
    static bool firsttime = true;
    if (firsttime){
        firsttime = false;
    }
    else{
        if (value){
            temporizador_arriba_abajo.start(20);
            ui->animacion_H1->setVisible(true);
        }
        else{
            temporizador_arriba_abajo.stop();
            ui->animacion_H1->setVisible(false);
            cambiar_height(ui->label_eje_grua, 301);
        }
    }
    variablesPLC.E6 = value;
}


void MainWindow::procesar_E8(bool value){
    static bool firsttime = true;
    if (firsttime){
        firsttime = false;
    }
    else{
        if (value){
            temporizador_abajo_arriba.start(20);
            ui->animacion_H1->setVisible(true);
        }
        else{
            temporizador_abajo_arriba.stop();
            ui->animacion_H1->setVisible(false);
            cambiar_height(ui->label_eje_grua, 10);
        }

    }
    variablesPLC.E8 = value;
}
void MainWindow::procesar_E9(bool value){
    static bool firsttime = true;
    if (firsttime){
        firsttime = false;
    }
    else{
        if (value){
            temporizador_izquierda_derecha.start(4);
        }
        else{
            temporizador_izquierda_derecha.stop();
            cambiar_x(ui->label_eje_grua, 1040);
        }
    }
    variablesPLC.E9 = value;
}

void MainWindow::procesar_E4(bool value){
    static bool firsttime = true;
    if (firsttime){
        firsttime = false;
    }
    else{
        if (value){
            temporizador_derecha_izquierda.start(4);
        }
        else{
            temporizador_derecha_izquierda.stop();
            cambiar_x(ui->label_eje_grua, 120);
        }
    }
    variablesPLC.E4 = value;
}

void MainWindow::slot_temporizador_abajo_arriba(){
    if (ui->label_eje_grua->height() > 10){
        cambiar_height(ui->label_eje_grua, ui->label_eje_grua->height()-2);
    }
}

void MainWindow::slot_temporizador_arriba_abajo(){
    if (ui->label_eje_grua->height() < 301){
        cambiar_height(ui->label_eje_grua, ui->label_eje_grua->height()+2);
    }
}

void MainWindow::slot_temporizador_izquierda_derecha(){
    if (ui->label_eje_grua->x() < 1040){
        cambiar_x(ui->label_eje_grua, ui->label_eje_grua->x()+2);
    }
}

void MainWindow::slot_temporizador_derecha_izquierda(){
    if (ui->label_eje_grua->x() > 120){
        cambiar_x(ui->label_eje_grua, ui->label_eje_grua->x()-2);
    }
}

void MainWindow::cambiar_height(QLabel *milabel, int valor_height){
    milabel->resize(milabel->width(), valor_height);
}

void MainWindow::cambiar_x(QLabel *milabel, int valor_x){
    milabel->move(valor_x, milabel->y());
}

void MainWindow::anima_icono(QLabel *milabel, QString ruta){
    QMovie *movie = new QMovie(ruta);
    milabel->setMovie(movie);
    connect(movie, &QMovie::frameChanged, this, [=](int){
        QImage frame = movie->currentImage();
        QImage scaled = frame.scaled(
            milabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation   // ✅ evita el sharpening
            );
        milabel->setPixmap(QPixmap::fromImage(scaled));
    });
    movie->setCacheMode(QMovie::CacheAll);
    movie->setSpeed(100);  // velocidad normal
    movie->start();
}

void MainWindow::iniciar_opcworker(){
    QStringList nss = configurar_nss();
    QStringList ies = configurar_iss();
    QStringList nss_nobit;
    QStringList ies_nobit;
    m_worker = new Worker(38, nss, ies, 0, nss_nobit, ies_nobit);
    m_worker->moveToThread(&m_workerThread);
    connect(&m_workerThread, &QThread::started, this, &MainWindow::onThreadStarted);
    connect(&m_workerThread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(m_worker, &Worker::valorBoolChanged, this, &MainWindow::onvalorBoolChanged);
    connect(m_worker, &Worker::connected,
            this, &MainWindow::onOpcConnected);

    m_workerThread.start();
}

void MainWindow::onOpcConnected(){
    if (!m_outputsInitialized){
        QMetaObject::invokeMethod(
            m_worker,
            "writeBoolNodeSlot",
            Qt::QueuedConnection,
            Q_ARG(quint16, 4),
            Q_ARG(quint32, 40),
            Q_ARG(bool, false)
            );
        QMetaObject::invokeMethod(
            m_worker,
            "writeBoolNodeSlot",
            Qt::QueuedConnection,
            Q_ARG(quint16, 4),
            Q_ARG(quint32, 41),
            Q_ARG(bool, false)
            );
        m_outputsInitialized = true;
    }
}

void MainWindow::onvalorBoolChanged(int which, bool value){
    qInfo() << "Me ha llegado which = " << which << " con valor " << value;
    switch(which){
        case 1: variablesPLC.H1 = value;
                break;
        case 2: variablesPLC.H2 = value;
                break;
        case 3: variablesPLC.H3 = value;
                break;
        case 4: variablesPLC.H4 = value;
                break;
        case 5: variablesPLC.H5 = value;
                break;
        case 6: variablesPLC.S1 = value;
            break;
        case 7: variablesPLC.S13 = value;
            break;
        case 8: variablesPLC.S14 = value;
            break;
        case 9: variablesPLC.S15 = value;
            break;
        case 10: variablesPLC.S16 = value;
            break;
        case 11:
            variablesPLC.S2 = value;
            // Si S2 es true (significa que el botón físico está hundido)
            if (value == true) {
                reproducir_locucion_parada();        // Habla inmediatamente
                temporizador_locucion.start(60000);  // Programa que repita cada 1 minuto (60000 ms)
            } else {
                temporizador_locucion.stop();        // Si se libera la parada, desactiva el bucle de voz
            }
            break;
        case 12: variablesPLC.S7 = value;
            break;
        case 13: //cambios realizados
            //Detectamos flanco de subida: si el nuevo valor es true y antes era false
            if (value == true && variablesPLC.S8 == false) {
                contadorCajasActuales++;
                qInfo() << "¡Caja procesada! Total actual: " << contadorCajasActuales;
                actualizarEstadisticas();
            }
            variablesPLC.S8 = value;
            break;
        case 14: variablesPLC.E0 = value; // Estado inicial en reposo
            break;
        case 15: variablesPLC.E1 = value; // Estado inicial tras pulsar S1
            break;
        case 16: procesar_E10(value); // La grúa está a la derecha y tiene que bajar de arriba a abajo para depositar la pieza
            break;
        case 17: variablesPLC.E11 = value;
            break;
        case 18: variablesPLC.E12 = value;
            break;
        case 19: variablesPLC.E13 = value;
            break;
        case 20: variablesPLC.E14 = value;
            break;
        case 21: variablesPLC.E15 = value;
            break;
        case 22: variablesPLC.E16 = value;
            break;
        case 23: variablesPLC.E17 = value;
            break;
        case 24: variablesPLC.E18 = value;
            break;
        case 25: variablesPLC.E19 = value;
            break;
        case 26: procesar_E2(value); // Estado de subida de la grúa sin tener activado el imán
            break;
        case 27: variablesPLC.E20 = value;
            break;
        case 28: variablesPLC.E21 = value;
            break;
        case 29: variablesPLC.E22 = value;
            break;
        case 30: variablesPLC.E23 = value;
            break;
        case 31: variablesPLC.E24 = value;
            break;
        case 32: variablesPLC.E3 = value; // Estado en el que la grúa está arriba
            break;
        case 33: procesar_E4(value); // Estado en el que la grúa se mueve de derecha a izquierda
            break;
        case 34: variablesPLC.E5 = value; // Estado en el que la grúa está arriba y a la izquierda parada (reposo)
            break;
        case 35: procesar_E6(value); // Estado en el que la grúa se mueve de arriba a abajo dejando el estado de reposo
            break;
        case 36: variablesPLC.E7 = value; // Estado en el que la grúa está abajo a la izquierda y debe activar el imán
            break;
        case 37: procesar_E8(value); // Estado en el que la grúa se mueve de abajo a arriba con el imán activado (recogiendo pieza)
            break;
        case 38: procesar_E9(value); // Estado en el que la grúa de se mueve a izquierda a derecha con el imán activado (lleva la pieza)
            break;
    }
    cambiar_aspecto_actuadores(variablesPLC.H1, variablesPLC.H2, variablesPLC.H3, variablesPLC.H4, variablesPLC.H5);
    cambiar_aspecto_pulsadores(variablesPLC.S1, variablesPLC.S2);
    cambiar_aspecto_sensores_piezas(variablesPLC.S7, variablesPLC.S8);
    cambiar_aspecto_fines_de_carreras(variablesPLC.S13, variablesPLC.S14, variablesPLC.S15, variablesPLC.S16);
    cambiar_mensaje();
}

void MainWindow::cambiar_mensaje(){
    QString estado;
    if (variablesPLC.E0){
        estado = "E0: ";
    }
    if (variablesPLC.E1){
        estado = "E1: ";
    }
    if (variablesPLC.E2){
        estado = "E2: ";
    }
    if (variablesPLC.E3){
        estado = "E3: ";
    }
    if (variablesPLC.E4){
        estado = "E4: ";
    }
    if (variablesPLC.E5){
        estado = "E5: ";
    }
    if (variablesPLC.E6){
        estado = "E6: ";
    }
    if (variablesPLC.E7){
        estado = "E7: ";
    }
    if (variablesPLC.E8){
        estado = "E8: ";
    }
    if (variablesPLC.E9){
        estado = "E9: ";
    }
    if (variablesPLC.E10){
        estado = "E10: ";
    }
    if (variablesPLC.E11){
        estado = "E11: ";
    }
    if (variablesPLC.E12){
        estado = "E12: ";
    }
    if (variablesPLC.E13){
        estado = "E13: ";
    }
    if (variablesPLC.E14){
        estado = "E14: ";
    }
    if (variablesPLC.E15){
        estado = "E15: ";
    }
    if (variablesPLC.E16){
        estado = "E16: ";
    }
    if (variablesPLC.E17){
        estado = "E17: ";
    }
    if (variablesPLC.E18){
        estado = "E18: ";
    }
    if (variablesPLC.E19){
        estado = "E19: ";
    }
    if (variablesPLC.E20){
        estado = "E20: ";
    }
    if (variablesPLC.E21){
        estado = "E21: ";
    }
    if (variablesPLC.E22){
        estado = "E22: ";
    }
    if (variablesPLC.E23){
        estado = "E23: ";
    }
    if (variablesPLC.E24){
        estado = "E24: ";
    }
    ui->texto->setText(estado);
    if (!(variablesPLC.S14) && (variablesPLC.H5)){
        ui->texto->setText(estado + "Tomando pieza");
    }
    if ((variablesPLC.S13) && (variablesPLC.S14) && (variablesPLC.H5)){
        ui->texto->setText(estado + "Desplazando pieza verticalmente");
    }
    if ((variablesPLC.S15) && (variablesPLC.S16) && (variablesPLC.H5)){
        ui->texto->setText(estado + "Desplazando pieza horizontalmente");
    }
    if ((variablesPLC.S15) && (variablesPLC.S16) && (!variablesPLC.H5)){
        ui->texto->setText(estado + "Desplazando grúa vacía horizontalmente");
    }
    if ((variablesPLC.S13) && (variablesPLC.S14) && (!variablesPLC.H5)){
        ui->texto->setText(estado + "Desplazando grúa vacía verticalmente");
    }
    if (!(variablesPLC.S14) && (!variablesPLC.S15) && (!variablesPLC.H5)){
        ui->texto->setText(estado + "Depositando pieza");
    }
    if (!(variablesPLC.S13) && (!variablesPLC.H5) && (!variablesPLC.S16)){
        ui->texto->setText(estado + "En reposo");
    }
}

QStringList MainWindow::configurar_nss(){
    QStringList nss;
    for (int i = 0; i < 38; i++){
        nss.append("4");
    }
    return nss;
}

QStringList MainWindow::configurar_iss(){
    QStringList iss;
    for (int i = 0; i < 38; i++){
        QString mi_i = QString::number(i+2);
        iss.append(mi_i);
    }
    return iss;
}

void MainWindow::onThreadStarted(){

    // Lanzar conexión cuando el event loop ya esté activo

    QString urlopc = "opc.tcp://192.168.0.27:4840";

    const QUrl endpoint(urlopc.trimmed());

    QMetaObject::invokeMethod(m_worker, "start",

                              Qt::QueuedConnection,

                              Q_ARG(QUrl, endpoint),

                              Q_ARG(QString, QString()),

                              Q_ARG(QString, QString()));

}

void MainWindow::cambiar_aspecto_actuadores(bool H1, bool H2, bool H3, bool H4, bool H5){
    ui->l_H1->setStyleSheet(
        H1 ? "background-color: rgb(0,120,215);"
           : "background-color: #444444;"
        );
    ui->l_H2->setStyleSheet(
        H2 ? "background-color: rgb(0,120,215);"
           : "background-color: #444444;"
        );
    ui->l_H3->setStyleSheet(
        H3 ? "background-color: rgb(0,120,215);"
           : "background-color: #444444;"
        );
    ui->l_H4->setStyleSheet(
        H4 ? "background-color: rgb(0,120,215);"
           : "background-color: #444444;"
        );
    ui->l_H5->setStyleSheet(
        H5 ? "background-color: rgb(0,120,215);"
           : "background-color: #444444;"
        );
}
void MainWindow::cambiar_aspecto_fines_de_carreras(bool S13, bool S14, bool S15, bool S16){
    ui->l_S13->setStyleSheet(
        S13 ? "background-color: rgb(0,255,0);"
           : "background-color: #444444;"
        );
    ui->l_S14->setStyleSheet(
        S14 ? "background-color: rgb(0,255,0);"
            : "background-color: #444444;"
        );
    ui->l_S15->setStyleSheet(
        S15 ? "background-color: rgb(0,255,0);"
            : "background-color: #444444;"
        );
    ui->l_S16->setStyleSheet(
        S16 ? "background-color: rgb(0,255,0);"
            : "background-color: #444444;"
        );
}
void MainWindow::cambiar_aspecto_pulsadores(bool S1, bool S2){
    ui->l_S1->setStyleSheet(
        S1 ? "background-color: rgb(0,255,0);"
            : "background-color: #444444;"
        );
    ui->l_S2->setStyleSheet(
        S1 ? "background-color: rgb(0,255,0);"
            : "background-color: #444444;"
        );
}
void MainWindow::cambiar_aspecto_sensores_piezas(bool S7, bool S8){
    ui->l_S7->setStyleSheet(
        S7 ? "background-color: rgb(0,255,0);"
           : "background-color: #444444;"
        );
    ui->l_S8->setStyleSheet(
        S8 ? "background-color: rgb(0,255,0);"
           : "background-color: #444444;"
        );
}
void MainWindow::closeEvent(QCloseEvent* e){
    // 1) Pide al worker que se pare y espera a que libere recursos (en su hilo)
    if (m_worker) {
        m_worker->requestStop();
    }
    // 2) Para el hilo
    if (!m_workerThread.wait(1000)) {     // espera hasta 1s
        m_workerThread.quit();            // por si acaso hay event loop
        m_workerThread.wait(1000);
    }
    // 3) Continúa con el cierre de la ventana
    e->accept();
}
MainWindow::~MainWindow()
{
    // 1) Pide al worker que pare (no bloquea, no depende del event loop)
    if (m_worker) {
        m_worker->requestStop();    // ↓ m_running = 0; el while saldrá solo
    }

    // 2) Espera a que el hilo del worker termine (el bucle sale en <= 100 ms,
    //    o lo que hayas puesto en UA_Client_run_iterate)
    if (!m_workerThread.wait(1000)) {
        // 3) Por si acaso (si tuvieras event loop en el worker):
        m_workerThread.quit();
        m_workerThread.wait(1000);
        // No uses terminate() salvo que sea estrictamente necesario
    }
    delete ui;
}

void MainWindow::on_b_ponerpieza_clicked()
{
    QMetaObject::invokeMethod(
        m_worker,
        "writeBoolNodeSlot",
        Qt::DirectConnection,
        Q_ARG(quint16, 4),
        Q_ARG(quint32, 40),
        Q_ARG(bool, true)
        );

    QTimer::singleShot(500, this, [this] {
        QMetaObject::invokeMethod(
            m_worker,
            "writeBoolNodeSlot",
            Qt::DirectConnection,
            Q_ARG(quint16, 4),
            Q_ARG(quint32, 40),
            Q_ARG(bool, false)
            );
        });

}


void MainWindow::on_b_quitarpieza_clicked()
{
    QMetaObject::invokeMethod(
        m_worker,
        "writeBoolNodeSlot",
        Qt::DirectConnection,
        Q_ARG(quint16, 4),
        Q_ARG(quint32, 41),
        Q_ARG(bool, true)
        );

    QTimer::singleShot(500, this, [this] {
        QMetaObject::invokeMethod(
            m_worker,
            "writeBoolNodeSlot",
            Qt::DirectConnection,
            Q_ARG(quint16, 4),
            Q_ARG(quint32, 41),
            Q_ARG(bool, false)
            );
    });

}

void MainWindow::guardarDatosVector() {
    // 1. Registrar el dato actual (incluso 0) en el historial y actualizar estadísticas
    historialCajas.append(contadorCajasActuales);



    // 2. Guardar el registro en la memoria temporal y reiniciar el contador
    RegistroCajas nuevoRegistro;
    nuevoRegistro.numeroCajas = contadorCajasActuales;
    nuevoRegistro.marcaTiempo = QDateTime::currentSecsSinceEpoch();

    vectorLogs.append(nuevoRegistro);
    contadorCajasActuales = 0;

     actualizarEstadisticas();

    qInfo() << "Datos guardados temporalmente. Total:" << vectorLogs.size();

    // 3. Al alcanzar 10 registros, guardar en el archivo y actualizar la lista visual
    if (vectorLogs.size() >= 10) {
        QFile file("log_cajas_procesadas.txt");

        // Añadir datos al final del archivo
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            for (const auto &reg : vectorLogs) {
                out << reg.marcaTiempo << " - Cajas: " << reg.numeroCajas << "\n";
            }
            file.close();
        }

        // Recargar la pantalla visual directamente desde el mismo archivo
        ui->listWidget->clear();
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                ui->listWidget->addItem(in.readLine());
            }
            file.close();
        }

        // 4. Vaciar el vector de memoria tras guardar
        vectorLogs.clear();
    }
}

void MainWindow::actualizarEstadisticas() {
    // 1. Si el historial está vacío, mostrar 0 y salir
    if (historialCajas.isEmpty() && contadorCajasActuales == 0) {
        ui->label_media->setText("Media: 0.00");
        ui->label_desviacion->setText("Desv: 0.00");
        return;
    }
    int totalIntervalos= historialCajas.size() + 1;
    // 2. Calcular la media sumando los valores (usando un bucle for-range)
    double suma = contadorCajasActuales;
    for (int valor : historialCajas) {
        suma += valor;
    }
    double media = suma / historialCajas.size();

    // 3. Calcular la desviación típica poblacional
    double sumaVarianzas = 0.0;
    for (int valor : historialCajas) {
        sumaVarianzas += qPow(valor - media, 2.0);
    }
    double desviacion = qSqrt(sumaVarianzas / historialCajas.size());

    // 4. Actualizar la interfaz formateando los resultados a 2 decimales
    ui->label_media->setText("Media: " + QString::number(media, 'f', 2));
    ui->label_desviacion->setText("Desv: " + QString::number(desviacion, 'f', 2));
}
void MainWindow::reproducir_locucion_parada()
{
    QString estado_actual = ui->texto->text();
    QString frase = "La planta está en situación de parada. " + estado_actual;
    QProcess::startDetached("espeak", QStringList() << "-v" << "es" << frase);
}
void MainWindow::slot_spin_ros()
{
    if (rclcpp::ok()) {
        rclcpp::spin_some(nodo_ros);
    }
}

void MainWindow::callback_mensaje_ros(const std_msgs::msg::Bool::SharedPtr msg)
{
    qInfo() << "Mensaje recibido de ROS2 en /mensajeS7: " << msg->data;
    onvalorBoolChanged(12, msg->data);
}
