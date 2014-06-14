#include "dailywidget.h"
#include <QDebug>
DailyWidget::DailyWidget(QWidget *parent,int dayCount,QString cityName, TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitation):
    QWidget(parent),
    _manager(NULL),
    _cityName(cityName),
    _dayCount(dayCount)
{
    resize(400,400);
    int margin = 10;
    _dailyDetail = new DailyDetail(tempUnit,windUnit,precipitation,dayCount);
    _dailyArea = new QScrollArea(this);
    _dailyArea->setGeometry(0,0,this->width(),this->height());
    _dailyArea->setAlignment(Qt::AlignHCenter);
    _dailyArea->setStyleSheet("background-color:rgba(255,255,255,0);border:none");
    _dailyArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    contentWidget = new QWidget(_dailyArea);
    contentWidget->resize(300,(60 + margin) * _dayCount);

    for(int count = 0;count < _dayCount;count++)
    {
        ForcastWidget *forcastWidget = new ForcastWidget(contentWidget);
        forcastWidget->setGeometry(0,(forcastWidget->height() + margin) * count,forcastWidget->width(),forcastWidget->height());
        _forcastWidgetList.append(forcastWidget);
    }
    _dailyArea->setWidget(contentWidget);
    contentWidget->show();
    if(!_cityName.isEmpty())
        updateDetail();
}

void DailyWidget::updateDetail()
{
    if(_cityName.isEmpty())
        return;
    if(_manager == NULL)
    {
        _manager = new QNetworkAccessManager(this);
        connect(_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onReply(QNetworkReply*)));
    }

    QString location = "q=" + _cityName + "&cnt=" + QString::number(_dayCount);
    QString address = "http://api.openweathermap.org/data/2.5/forecast/daily?" + location + "&APPID=255cb28e2c88da079d8c94fbccd17068";
    _manager->get (QNetworkRequest(QUrl(address)));
}

void DailyWidget::refreshDetail()
{
    QStringList dateList = _dailyDetail->getDailyDate();
    QStringList iconList = _dailyDetail->getIcon();
    QStringList maxTempList = _dailyDetail->getMaxTemp();
    QStringList minTempList = _dailyDetail->getMinTemp();
    for(int count = 0;count < _dayCount;count++)
    {
        _forcastWidgetList[count]->setDateTime(dateList[count]);
        _forcastWidgetList[count]->setIcon(iconList[count]);
        _forcastWidgetList[count]->setMaxTemp(maxTempList[count]);
        _forcastWidgetList[count]->setMinTemp(minTempList[count]);
    }

}

void DailyWidget::setUnits(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit)
{
    _dailyDetail->setTempUnit(tempUnit);
    _dailyDetail->setWindUnit(windUnit);
    _dailyDetail->setPrecipitationUnit(precipitationUnit);
    refreshDetail();
}

void DailyWidget::refreshCity(QString cityName)
{
    _cityName = cityName;
    updateDetail();
}

void DailyWidget::onReply(QNetworkReply *reply)
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
        _dailyDetail->updateDetail(result);
        refreshDetail();
        qDebug() << "daily:in";
        emit hideLoadingWidget();
    }
    reply->deleteLater();
}
