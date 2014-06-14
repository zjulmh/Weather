#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include "unitType.h"
namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SettingWidget(QWidget *parent = 0,TEMPUNIT tempUnit = CELSIUS,WINDUNIT windUnit = KILOMETERSPERHOUR,PRECIPITATIONUNIT precipitation = MILLIMETERS);
    ~SettingWidget();

signals:
    void updateUnits(TEMPUNIT tempIndex,WINDUNIT windIndex,PRECIPITATIONUNIT precipitationIndex);
    
private slots:
    void on_confirmBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::SettingWidget *ui;
    TEMPUNIT _tempUnit;
    WINDUNIT _windUnit;
    PRECIPITATIONUNIT _precipitationUnit;
};

#endif // SETTINGWIDGET_H
