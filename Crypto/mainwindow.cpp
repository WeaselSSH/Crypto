#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manejocriptografia.h"

#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <string>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSalir_clicked()
{
    QApplication::quit();
}


void MainWindow::on_btnSeleccionarArchivo_clicked()
{
    QString ruta = QFileDialog::getOpenFileName(this, "Seleccionar archivo", "", "Archivo de textos (*.txt)");

    if (!ruta.isEmpty()) {
        ui->txtRutaArchivo->setText(ruta);
        actualizarEstadoBotones();
    }
}


void MainWindow::on_rbCesar_clicked()
{
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex(1);
    ui->txtKey->clear();

    actualizarEstadoBotones();
}


void MainWindow::on_rbXor_clicked()
{
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex(0);

    actualizarEstadoBotones();
}


void MainWindow::on_rbVigenere_clicked()
{
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex(0);

    actualizarEstadoBotones();
}

void MainWindow::on_btnEncriptar_clicked()
{
    if(procesarTextoArchivo(true)) {
        QMessageBox::information(this, "Encriptacion", "Encriptacion realizada exitosamente");
    } else {
        QMessageBox::warning(this, "Encriptacion", "Error al encriptar el archivo. Verifique que el archivo a encriptar exista");
    }
}

void MainWindow::on_btnDesencriptar_clicked()
{
    if(procesarTextoArchivo(false)) {
        QMessageBox::information(this, "Desencriptacion", "Desencriptacion realizada exitosamente");
    } else {
        QMessageBox::warning(this, "Desencriptacion", "Error al desencriptar el archivo. Verifique que el archivo a desencriptar exista");
    }
}

void MainWindow::on_txtKey_textChanged(const QString &arg1)
{
    actualizarEstadoBotones();
}

//funciones auxiliares
bool MainWindow::procesarTextoArchivo(bool encriptar) {
    QString rutaArchivo = ui->txtRutaArchivo->text().trimmed();
    string textoAProcesar = getTextoArchivo(ui->txtRutaArchivo->text().trimmed());

    //debe ir en un if realmente
    int desplazamiento = ui->spinDesplazamiento->value();
    string textoProcesado = algoritmoCesar(textoAProcesar, desplazamiento, encriptar);

    if (setTextoArchivo(rutaArchivo, textoProcesado)) return true;

    return false;
}

string MainWindow::getTextoArchivo(const QString &ruta) {
    string rutaArchivo = ruta.toStdString();

    ifstream archivo(rutaArchivo.c_str(), ios::binary);

    if (!archivo.is_open()) {
        return "";
    }

    archivo.seekg(0, ios::end);
    streamsize tamanio = archivo.tellg();
    archivo.seekg(0, ios::beg);

    string contenido(tamanio, '\0');
    archivo.read(&contenido[0], tamanio);

    archivo.close();
    return contenido;
}

bool MainWindow::setTextoArchivo(const QString &ruta, const string &texto) {
    string rutaArchivo = ruta.toStdString();

    ofstream archivo(rutaArchivo.c_str(), ios::binary);

    if (!archivo.is_open()) {
        return false;
    }

    archivo.write(texto.c_str(), texto.size());

    archivo.close();
    return true;
}

void MainWindow::actualizarEstadoBotones() {
    bool hayArchivo = !ui->txtRutaArchivo->text().trimmed().isEmpty();
    bool hayKey = !ui->txtKey->text().trimmed().isEmpty();

    if ( (ui->rbCesar->isChecked() && hayArchivo) || ((ui->rbXor->isChecked() || ui->rbVigenere->isChecked()) && hayArchivo && hayKey) ) {
        ui->btnEncriptar->setEnabled(true);
        ui->btnDesencriptar->setEnabled(true);
    } else {
        ui->btnDesencriptar->setEnabled(false);
    }
}
