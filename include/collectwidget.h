#ifndef COLLECTWIDGET_H
#define COLLECTWIDGET_H

#include <QWidget>
#include "locationwidget.h"
#include "unitType.h"
#include <QScrollArea>
#include <QList>
#include <QToolButton>
#include <QVBoxLayout>
class CollectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CollectWidget(QWidget *parent = 0,TEMPUNIT tempUnit = CELSIUS,WINDUNIT windUnit = KILOMETERSPERHOUR,PRECIPITATIONUNIT precipitationUnit = MILLIMETERS);
    CollectWidget(QWidget *parent,QVariantList cityList,TEMPUNIT tempUnit = CELSIUS,WINDUNIT windUnit = KILOMETERSPERHOUR,PRECIPITATIONUNIT precipitationUnit = MILLIMETERS);

    
signals:
    void addCitySignal(int flag);

    void deleteCitySignal(QString cityName);

    void setMainPageSignal(QString cityName);

    void viewDetailSingal(QString cityName);

    void hideLoadingWidget();
public slots:
    void addCity(QVariantMap city);

    void setUnits(TEMPUNIT tempUnit,WINDUNIT windUnit,PRECIPITATIONUNIT precipitationUnit);

    void updateDetail();

    void refreshDetail();
private:
    QVariantList _cityList;
    QList<LocationWidget *> _locationWidgetList;
    QScrollArea *_collectArea;
    QWidget* _contentWidget;
    QToolButton *_addCityButton;
    QVBoxLayout *_Vlayout;

    TEMPUNIT _tempUnit;
    WINDUNIT _windUnit;
    PRECIPITATIONUNIT _precipitationUnit;
private slots:
    void deleteCity(QString cityName);

    void setMainpage(QString cityName);

    void viewDetail(QString cityName);

    void onButtonClicked();

};

#endif // COLLECTWIDGET_H
