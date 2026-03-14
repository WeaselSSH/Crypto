#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "manejoarchivos.h"

#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->hide();
    QRegularExpression regex("[A-Za-z]+");
    QValidator *validador = new QRegularExpressionValidator(regex, this);
    ui->txtKey->setValidator(validador);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSeleccionarArchivo_clicked()
{
    QString ruta = QFileDialog::getOpenFileName(this, "Seleccionar archivo", "", "Archivo de textos (*.txt)");

    if (!ruta.isEmpty()) {
        ui->txtRutaArchivo->setText(ruta);
        actualizarEstadoBotones();
    }
}

void MainWindow::on_btnEncriptar_clicked()
{
    aplicarCifrado(OperacionCriptografica::Encriptar);
}

void MainWindow::on_btnDesencriptar_clicked()
{
    aplicarCifrado(OperacionCriptografica::Desencriptar);
}

void MainWindow::on_rbCesar_clicked()
{
    actualizarStackedWidget(1);
    actualizarEstadoBotones();
    ui->txtKey->clear();
}


void MainWindow::on_rbXor_clicked()
{
    actualizarStackedWidget(0);
    actualizarEstadoBotones();
}


void MainWindow::on_rbVigenere_clicked()
{
    actualizarStackedWidget(0);
    actualizarEstadoBotones();
}

void MainWindow::on_btnSalir_clicked()
{
    QApplication::quit();
}

void MainWindow::on_txtKey_textChanged(const QString &arg1)
{
    actualizarEstadoBotones();
}

//funciones auxiliares
void MainWindow::aplicarCifrado(OperacionCriptografica operacion)
{
    string rutaArchivo = ui->txtRutaArchivo->text().trimmed().toStdString();

    AlgoritmoCriptografico algoritmo = obtenerAlgoritmoCriptografico();
    int desplazamiento = ui->spinDesplazamiento->value();
    string key = ui->txtKey->text().trimmed().toStdString();

    bool sePudoProcesar = procesarArchivo(rutaArchivo, algoritmo, operacion, desplazamiento, key);

    if (!sePudoProcesar) {
        mostrarError("Error: no se pudo procesar el archivo. Verifique que el archivo exista y no se encuentre vacio.");
        return;
    }

    if (operacion == OperacionCriptografica::Encriptar) mostrarExito("Archivo encriptado correctamente.");
    else mostrarExito("Archivo desencriptado correctamente.");
}

AlgoritmoCriptografico MainWindow::obtenerAlgoritmoCriptografico()
{
    if (ui->rbCesar->isChecked()) return AlgoritmoCriptografico::Cesar;
    if (ui->rbXor->isChecked()) return AlgoritmoCriptografico::XOR;
    return AlgoritmoCriptografico::Vigenere;
}

void MainWindow::actualizarEstadoBotones()
{
    //se crean variables booleanas por operaciones en vez de un solo if para una mejor legibilidad
    bool esCesar = ui->rbCesar->isChecked();
    bool esXor = ui->rbXor->isChecked();
    bool esVigenere = ui->rbVigenere->isChecked();

    bool hayArchivo = !ui->txtRutaArchivo->text().trimmed().isEmpty();
    bool hayKey = !ui->txtKey->text().trimmed().isEmpty();

    bool requiereKey = (esXor || esVigenere);
    bool habilitarBotones = hayArchivo && (esCesar || hayKey && requiereKey);

    ui->btnEncriptar->setEnabled(habilitarBotones);
    ui->btnDesencriptar->setEnabled(habilitarBotones);
}

void MainWindow::actualizarStackedWidget(int idx)
{
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex(idx);
}

void MainWindow::mostrarError(const QString &mensaje)
{
    QMessageBox::critical(this, "Error", mensaje);
}

void MainWindow::mostrarExito(const QString &mensaje)
{
    QMessageBox::information(this, "Exito", mensaje);
}

