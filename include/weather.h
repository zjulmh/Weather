#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include "mainpage.h"
#include "unitType.h"
#include "dailywidget.h"
#include "collectwidget.h"
#include "settingwidget.h"
#include "addlocationdialog.h"
#include "titlewidget.h"
#include "contentwidget.h"
#include "hourlywidget.h"
#include <QSettings>
#include "loadingwidget.h"
#include <QTimer>
namespace Ui {
class Weather;
}

class Weather : public QWidget
{
    Q_OBJECT
    
public:
    explicit Weather(QWidget *parent = 0);
    ~Weather();
    
private:
    Ui::Weather *ui;
    MainPage *_mainPage;
    DailyWidget *_dailyWidget;
    CollectWidget *_collectWidget;
    SettingWidget *_settingWidget;
    AddLocationDialog *_addLocationDialog;
    TitleWIdget *_titleWidget;
    LoadingWidget *_loadingWidget;
    ContentWidget* _contentWidget;
    QList<QWidget* > _widgetList;

    HourlyWidget *_hourlyWidget;
    TEMPUNIT _tempUnit;
    WINDUNIT _windUnit;
    PRECIPITATIONUNIT _precipitationUnit;

    QSettings _settings;

    QVariantList _cityList;

    QMap<int,QString> _gradientsMap;

    int _receiveCount;
    QTimer *_updateTimer;
private:
    void readSettings();

    void writeSettings();

    void createMap();

signals:

private slots:
    void onTimer();

public slots:
    void onSetUnits(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit);
    void addCity(QString cityName,int flag);
    void viewDetail(QString cityName);
    void setMainPage(QString cityName);
    void receiveAddCitySignal(int flag);
    void changeBackground(int temp,TEMPUNIT tempUnit);
    void deleteCity(QString cityName);
    void hideLoadingWidget();
};

#endif // WEATHER_H
