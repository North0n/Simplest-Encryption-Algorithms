#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <functional>
#include <QVector>

#include "IEncryptor.h"
#include "RailwayFence.h"
#include "RotatingMatrix.h"
#include "VigenereProgressive.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbChooseFile_clicked();

    void on_pbSave_clicked();

    void on_pbExecute_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    enum class Algrotihms {RailwayFence, RotatingMatrix, Vigenere};
    QVector<IEncryptor *> encryptors {
        new RailwayFence(),
        new RotatingMatrix(),
        new VigenereProgressive()
    };
//    std::vector<std::function<QString(const QString&, const QString &)>> encryptionFuncs {
//        encrRailwayFence, encrRotatingMatrix, encrVigenere
//};
//    std::vector<std::function<QString(const QString&, const QString&)>> decryptionFuncs {
//        {decrRailwayFence, decrRotatingMatrix, decrVigenere},
//};

    void FillAlgorithms();
};
#endif // MAINWINDOW_H
