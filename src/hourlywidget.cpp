#include "hourlywidget.h"
#include <QDebug>


HourlyWidget::HourlyWidget(QWidget *parent, int hourCount, QString cityName, TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitation) :
    QWidget(parent),
    _cityName(cityName),
    _manager(NULL),
    _hourCount(hourCount)
{
    resize(400,400);
    int margin = 10;
    _hourlyDetail = new HourlyDetail(tempUnit,windUnit,precipitation,hourCount);
    _hourlyArea = new QScrollArea(this);
    _hourlyArea->setGeometry(0,0,this->width(),this->height());
    _hourlyArea->setAlignment(Qt::AlignHCenter);
    _hourlyArea->setStyleSheet("background-color:rgba(255,255,255,0);border:none");
    _hourlyArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _contentWidget = new QWidget(_hourlyArea);
    _contentWidget->resize(300,(60 + margin) * _hourCount);


    for(int count = 0;count < _hourCount;count++)
    {
        ForcastWidget *forcastWidget = new ForcastWidget(_contentWidget);
        forcastWidget->setGeometry(0,(forcastWidget->height() + margin) * count,forcastWidget->width(),forcastWidget->height());
        _forcastWidgetList.append(forcastWidget);
    }
    _hourlyArea->setWidget(_contentWidget);

    _contentWidget->show();
    if(!_cityName.isEmpty())
        updateDetail();
}

void HourlyWidget::updateDetail()
{
    if(_cityName.isEmpty())
        return;
    if(_manager == NULL)
    {
        _manager = new QNetworkAccessManager(this);
        connect(_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onReply(QNetworkReply*)));
    }

    QString location = "q=" + _cityName;
    QString address = "http://api.openweathermap.org/data/2.5/forecast?" + location + "&APPID=255cb28e2c88da079d8c94fbccd17068";
    _manager->get (QNetworkRequest(QUrl(address)));
}

void HourlyWidget::onReply(QNetworkReply *reply)
{
    if(reply->error () != QNetworkReply::NoError){
        reply->deleteLater ();
        return;
    }
    QTextCodec *codec = QTextCodec::codecForName ("utf-8");
    QString all = codec->toUnicode (reply->readAll ());
//    qDebug() << all;
    QJson::Parser parser;
    bool ok;
    QVariant result = parser.parse (all.toAscii (),&ok);
    if(ok)
    {
        _hourlyDetail->updateDetail(result);
        refreshDetail();
        qDebug() << "hourly:in";
        emit hideLoadingWidget();
    }
    reply->deleteLater();
}


void HourlyWidget::refreshCity(QString cityName)
{
    _cityName = cityName;
    updateDetail();
}

void HourlyWidget::refreshDetail()
{
    QStringList timeList = _hourlyDetail->getHourlyTime();
    QStringList iconList = _hourlyDetail->getIcon();
    QStringList maxTempList = _hourlyDetail->getMaxTemp();
    QStringList minTempList = _hourlyDetail->getMinTemp();
    for(int count = 0;count < _hourCount;count++)
    {
        _forcastWidgetList[count]->setDateTime(timeList[count]);
        _forcastWidgetList[count]->setIcon(iconList[count]);
        _forcastWidgetList[count]->setMaxTemp(maxTempList[count]);
        _forcastWidgetList[count]->setMinTemp(minTempList[count]);
    }
}


void HourlyWidget::setUnits(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit)
{
    _hourlyDetail->setTempUnit(tempUnit);
    _hourlyDetail->setWindUnit(windUnit);
    _hourlyDetail->setPrecipitationUnit(precipitationUnit);
    refreshDetail();
}



