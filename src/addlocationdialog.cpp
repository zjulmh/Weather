#include "addlocationdialog.h"
#include <QPalette>
AddLocationDialog::AddLocationDialog(QWidget *parent,int flag) :
    QWidget(parent),
    _flag(flag)
{
    resize(400,460);
    this->setAutoFillBackground(true);
    QPalette myPalette = this->palette();
    myPalette.setColor(QPalette::Window,QColor(141,141,141,255));
    this->setPalette(myPalette);
    _confirmBtn = new QToolButton(this);
    QIcon icon(":/images/add.png");
    _confirmBtn->setIcon(icon);
    _locationEdit = new LocationEdit(this);
    _locationEdit->setGeometry(5,20,this->width() - 10,50);
    _locationEdit->setText("Input location...");
    _confirmBtn->setGeometry(0,this->height() - 50,this->width(),50);
    _locationEdit->setStyleSheet("background:transparent;border-color:white;border-width:2px;border-style:solid");
    _confirmBtn->setStyleSheet("QToolButton{background-color:transparent;color:white;border-top-color:white;border-top-width:2px;border-top-style:solid}\nQToolButton:hover{color:darkgrey}");
    connect(_confirmBtn,SIGNAL(clicked()),SLOT(onConfirmBtnClicked()));
}

/*
 *transfer the location text and main City flag
 */
void AddLocationDialog::onConfirmBtnClicked()
{
    if(_flag == 1)
    {
        emit addCitySignal(_locationEdit->text(),_flag);
        _flag = 0;
    }
    else
        emit addCitySignal(_locationEdit->text(),_flag);
    _locationEdit->setText("");
}
