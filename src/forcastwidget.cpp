#include "forcastwidget.h"
#include "ui_forcastwidget.h"
#include <QStyleOption>
#include <QPainter>
ForcastWidget::ForcastWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForcastWidget)
{
    ui->setupUi(this);
}

ForcastWidget::~ForcastWidget()
{
    delete ui;
}


void ForcastWidget::setDateTime(QString dateTime)
{
    ui->dateLabel->setText(dateTime);
}

void ForcastWidget::setMinTemp(QString minTemp)
{
    ui->minTempLabel->setText(minTemp);
}


void ForcastWidget::setMaxTemp(QString maxTemp)
{
    ui->maxTempLabel->setText(maxTemp);
}

void ForcastWidget::setIcon(QString icon)
{
//    ui->iconLabel->setText(icon);
    QImage iconImage(QString(":/images/%1.png").arg(icon));
    ui->iconLabel->setPixmap(QPixmap::fromImage(iconImage));
}

void ForcastWidget::paintEvent(QPaintEvent *)
{

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}
