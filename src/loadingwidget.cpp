#include "loadingwidget.h"
#include "ui_loadingwidget.h"
#include <QPalette>
LoadingWidget::LoadingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadingWidget)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPalette myPalette = this->palette();
    myPalette.setColor(QPalette::Window,QColor(255,255,255,255));
    this->setPalette(myPalette);
    _movie = new QMovie(":/images/loading.gif");
    ui->loadingLabel->setMovie(_movie);
    _movie->start();
}

LoadingWidget::~LoadingWidget()
{
    delete ui;
}

void LoadingWidget::onLoad()
{
    move(0,0);
}

void LoadingWidget::onHide()
{
    move(0,-this->height());
    hide();
}
