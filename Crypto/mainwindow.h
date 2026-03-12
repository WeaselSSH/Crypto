#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

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
    void actualizarEstadoBotones();
    void on_txtKey_textChanged(const QString &arg1);

    std::string getTextoArchivo(const QString &ruta);
    bool setTextoArchivo(const QString &ruta, const std::string &texto);
    bool procesarTextoArchivo(bool encriptar);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
