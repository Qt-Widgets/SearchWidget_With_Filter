#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "searchwidget.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SearchWidget* searchWidget = new SearchWidget();
    searchWidget->show();
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(searchWidget);
    this->ui->sWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

