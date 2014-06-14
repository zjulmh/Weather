#ifndef DAILYWIDGET_H
#define DAILYWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <qjson/parser.h>
#include <QPropertyAnimation>
#include "dailydetail.h"
#include "unitType.h"
#include "forcastwidget.h"
#include <QScrollArea>
#include <QList>
class DailyWidget : public QWidget
{
    Q_OBJECT
public:
    DailyWidget(QWidget *parent,int dayCount = 7 ,QString cityName = "",TEMPUNIT tempUnit = CELSIUS,WINDUNIT windUnit = KILOMETERSPERHOUR,PRECIPITATIONUNIT precipitation = MILLIMETERS);
    
private slots:
    void onReply(QNetworkReply *reply);
signals:
    void hideLoadingWidget();
public slots:
    void updateDetail();

    void refreshDetail();

    void setUnits(TEMPUNIT tempUnit,WINDUNIT windUnit,PRECIPITATIONUNIT precipitationUnit);

    void refreshCity(QString cityName);

private:
    QString _cityName;
    DailyDetail *_dailyDetail;
    QNetworkAccessManager* _manager;
    QList<ForcastWidget *> _forcastWidgetList;
    
    int _dayCount;

    QScrollArea *_dailyArea;
    QWidget *contentWidget;
};

#endif // DAILYWIDGET_H
