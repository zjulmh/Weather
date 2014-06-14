#include "settingwidget.h"
#include "ui_settingwidget.h"
SettingWidget::SettingWidget(QWidget *parent, TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitation) :
    QWidget(parent),
    _windUnit(windUnit),
    _tempUnit(tempUnit),
    _precipitationUnit(precipitation),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
    ui->tempValue->setCurrentIndex(_tempUnit);
    ui->windValue->setCurrentIndex(_windUnit);
    ui->precipitationValue->setCurrentIndex(_precipitationUnit);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::on_confirmBtn_clicked()
{
    _tempUnit = TEMPUNIT(ui->tempValue->currentIndex());
    _windUnit = WINDUNIT(ui->windValue->currentIndex());
    _precipitationUnit = PRECIPITATIONUNIT(ui->precipitationValue->currentIndex());
    emit updateUnits(_tempUnit,_windUnit,_precipitationUnit);
}

void SettingWidget::on_cancelBtn_clicked()
{
    ui->tempValue->setCurrentIndex(_tempUnit);
    ui->windValue->setCurrentIndex(_windUnit);
    ui->precipitationValue->setCurrentIndex(_precipitationUnit);
}

