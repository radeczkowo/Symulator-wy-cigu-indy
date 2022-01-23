#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    scena = new Scena(this);
    QGraphicsView *widok = new QGraphicsView();
    wyscig = new Wyscig(scena);



    widok->setScene(scena);
    //widok->setFixedSize(1450,900);

    widok->show();

   this->setCentralWidget(widok);


}

MainWindow::~MainWindow()
{
    delete ui;
}



