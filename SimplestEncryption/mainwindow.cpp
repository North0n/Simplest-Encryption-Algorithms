#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <array>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FillAlgorithms();
    ui->rbEncryption->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FillAlgorithms()
{
    ui->cbAlgorithm->addItem("Железнодорожная изгородь [Ru]", (int)Algrotihms::RailwayFence);
    ui->cbAlgorithm->addItem("Поворачивающаяся решётка [En]", (int)Algrotihms::RotatingMatrix);
    ui->cbAlgorithm->addItem("Виженер, прогрессивный ключ [Ru]", (int)Algrotihms::Vigenere);
}


void MainWindow::on_pbChooseFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл"), tr("../data"),
                                                    tr("Текстовые файлы (*.txt)"));
    if (!filename.isEmpty()) {
        QFile inputFile(filename);
        if (!inputFile.open(QIODevice::ReadOnly))
            return;
        QTextStream in(&inputFile);
        ui->teInput->clear();
        while (!in.atEnd())
            ui->teInput->append(in.readLine());
        inputFile.close();
    }
}

void MainWindow::on_pbSave_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), tr("../data"),
                        tr("Текстовые файлы (*.txt)"));
    if (filename.isEmpty())
        return;
    QFile outputFile(filename);
    if (!outputFile.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&outputFile);
    out << ui->teInput->toPlainText();
    outputFile.close();
}


void MainWindow::on_pbExecute_clicked()
{
    if (ui->rbEncryption->isChecked())
        ui->teOutput->setText(encryptors[ui->cbAlgorithm->currentData().toInt()]->encrypt
                (ui->teInput->toPlainText(), ui->teKey->toPlainText()));
    else
        ui->teInput->setText(encryptors[ui->cbAlgorithm->currentData().toInt()]->decrypt
                (ui->teOutput->toPlainText(), ui->teKey->toPlainText()));
}


void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл"), tr("../data"),
                                                    tr("Текстовые файлы (*.txt)"));
    if (!filename.isEmpty()) {
        QFile inputFile(filename);
        if (!inputFile.open(QIODevice::ReadOnly))
            return;
        QTextStream in(&inputFile);
        ui->teOutput->clear();
        while (!in.atEnd())
            ui->teOutput->append(in.readLine());
        inputFile.close();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), tr("../data"),
                        tr("Текстовые файлы (*.txt)"));
    if (filename.isEmpty())
        return;
    QFile outputFile(filename);
    if (!outputFile.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&outputFile);
    out << ui->teOutput->toPlainText();
    outputFile.close();
}

