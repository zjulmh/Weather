#ifndef HOURLYWIDGET_H
#define HOURLYWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <qjson/parser.h>
#include "hourlydetail.h"
#include "unitType.h"
#include "forcastwidget.h"
#include <QScrollArea>
#include <QList>
#include <QFrame>


class HourlyWidget : public QWidget
{
    Q_OBJECT
public:
    HourlyWidget(QWidget *parent,int hourCount = 8 ,QString cityName = "",TEMPUNIT tempUnit = CELSIUS,WINDUNIT windUnit = KILOMETERSPERHOUR,PRECIPITATIONUNIT precipitation = MILLIMETERS);
private slots:
    void onReply(QNetworkReply *reply);
signals:
    void hideLoadingWidget();
public slots:
    void updateDetail();

    void refreshDetail();

    void setUnits(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit);

    void refreshCity(QString cityName);

private:
    QString _cityName;
    HourlyDetail *_hourlyDetail;
    QNetworkAccessManager* _manager;
    QList<ForcastWidget *> _forcastWidgetList;

    int _hourCount;

    QScrollArea *_hourlyArea;
    QWidget *_contentWidget;
};

#endif // HOURLYWIDGET_H
