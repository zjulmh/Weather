#ifndef LOCATIONWIDGET_H
#define LOCATIONWIDGET_H

#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <QVariantMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <qjson/parser.h>
#include "currentdetail.h"
#include "unitType.h"

namespace Ui {
class LocationWidget;
}

class LocationWidget : public QWidget
{
    Q_OBJECT
    
public:
    LocationWidget(QWidget *parent,QVariantMap city,TEMPUNIT tempUnit = CELSIUS,WINDUNIT windUnit = KILOMETERSPERHOUR,PRECIPITATIONUNIT precipitationUnit = MILLIMETERS);
    ~LocationWidget();
public slots:
    void updateDetail();

    void refreshDetail();

    void setUnits(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit);

    void toggleFlag();

signals:
    void setMainPage(QString city);

    void deleteCity(QString city);

    void viewDetailCity(QString city);

private:
    Ui::LocationWidget *ui;
    QAction *_setMainPage;
    QAction *_deleteAction;
    QAction *_viewDetail;
    QVariantMap _city;
    QMenu *cMenu;
    QNetworkAccessManager *_manager;
    CurrentDetail *_currentDetail;

private slots:
    void setMainPage();

    void deleteCity();

    void viewDetail();

    void onReply(QNetworkReply *reply);

protected:
    void contextMenuEvent(QContextMenuEvent *ev);

    void paintEvent(QPaintEvent *ev);
};

#endif // LOCATIONWIDGET_H
