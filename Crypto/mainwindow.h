#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "manejocriptografia.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSalir_clicked();
    void on_btnSeleccionarArchivo_clicked();
    void on_btnEncriptar_clicked();
    void on_btnDesencriptar_clicked();
    void on_rbCesar_clicked();
    void on_rbXor_clicked();
    void on_rbVigenere_clicked();
    void on_txtKey_textChanged(const QString &arg1);

private:
    void aplicarCifrado(OperacionCriptografica operacion);
    void actualizarEstadoBotones();
    void actualizarStackedWidget(int idx);
    AlgoritmoCriptografico obtenerAlgoritmoCriptografico();
    void mostrarError(const QString &mensaje);
    void mostrarExito(const QString &mensaje);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
