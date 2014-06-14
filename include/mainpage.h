#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include "currentdetail.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "unitType.h"
#include <qjson/parser.h>
#include <QPropertyAnimation>

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int iconNumber READ getIconNumber WRITE setIconNumber NOTIFY iconNumberChanged)
    
public:

    MainPage(QWidget *parent,QString cityName = "",TEMPUNIT tempUnit = CELSIUS,WINDUNIT windUnit = KILOMETERSPERHOUR,PRECIPITATIONUNIT precipitation = MILLIMETERS);
    ~MainPage();

    int getIconNumber() const {return _iconNumber;}

    void setIconNumber(int number);

signals:
    void iconNumberChanged(int number);

    void backgroundSignal(int temp,TEMPUNIT tempUnit);

    void hideLoadingWidget();
private slots:
    void onReply(QNetworkReply *reply);

    void finishAnim();

public slots:
    void updateDetail();

    void refreshDetail();

    void setUnits(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit);

    void refreshCity(QString cityName);
    
private:
    Ui::MainPage *ui;
    QString _cityName;
    CurrentDetail *_currentDetail;
    QNetworkAccessManager *_manager;

    QPropertyAnimation *anim;
    int _iconNumber;
    QString _mainWeather;

};

#endif // MAINPAGE_H
