#include "mainpage.h"
#include "ui_mainpage.h"
#include <QDebug>

MainPage::MainPage(QWidget *parent, QString cityName, TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitation):
    QWidget(parent),
    ui(new Ui::MainPage),
    _cityName(cityName),
    _manager(NULL),
    _iconNumber(1),
    _mainWeather("test")
{
    ui->setupUi(this);
    _currentDetail = new CurrentDetail(tempUnit,windUnit,precipitation);
    ui->unitLabel->setText(_currentDetail->getTempUnitString());
    ui->punitLabel->setText(_currentDetail->getPrecipitationUnitString());
    ui->wunitLabel->setText(_currentDetail->getWindUnitString());
    QImage iconImage(QString(":/images/%1/%2.png").arg(_mainWeather).arg(_iconNumber));
    ui->iconLabel->setPixmap(QPixmap::fromImage(iconImage));

    anim = new QPropertyAnimation(this,"iconNumber");
    anim->setDuration(500);
    anim->setStartValue(1);
    anim->setEndValue(50);
    anim->setEasingCurve(QEasingCurve::Linear);
    connect(anim,SIGNAL(finished()),this,SLOT(finishAnim()));

    if(!_cityName.isEmpty())
        updateDetail();
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::refreshCity(QString cityName)
{
    _cityName = cityName;
    updateDetail();
}

void MainPage::updateDetail()
{
    if(_cityName.isEmpty())
        return;
    if(_manager == NULL)
    {
        _manager = new QNetworkAccessManager(this);
        connect(_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onReply(QNetworkReply*)));
    }

    QString location = "q=" + _cityName;
    QString address = "http://api.openweathermap.org/data/2.5/weather?" + location + "&APPID=255cb28e2c88da079d8c94fbccd17068";
    _manager->get (QNetworkRequest(QUrl(address)));
}

void MainPage::onReply(QNetworkReply *reply)
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
        qDebug() << "mainpage:in";
        _currentDetail->updateDetail(result);
        refreshDetail();
        emit hideLoadingWidget();
    }
    reply->deleteLater();

}

void MainPage::refreshDetail()
{
    bool ok;
    ui->locationLabel->setText(_cityName);
    ui->dateLabel->setText(QDateTime::currentDateTime().toString("dddd,dd,MMMM"));
    ui->highLabel->setText("H:" + _currentDetail->getMaxTemp());
    ui->lowLabel->setText("L:" + _currentDetail->getminTemp());
    ui->valueLabel->setText(_currentDetail->getPressure());
    ui->pvalueLabel->setText(_currentDetail->getPrecipitation());
    ui->hvalueLabel->setText(_currentDetail->getHumidity());
    ui->wvalueLabel->setText(_currentDetail->getWindSpeed());
    ui->wunitLabel->setText(_currentDetail->getWindUnitString() + " " + _currentDetail->getWindDirection());
    ui->tempLabel->setText(_currentDetail->getCurrentTemp());
    ui->updateLabel->setText("updated : " + _currentDetail->getUpdateTime());
    _mainWeather = _currentDetail->getIcon();
    anim->start();
    emit backgroundSignal(_currentDetail->getCurrentTemp().toInt(&ok),_currentDetail->getTempUnit());
}

void MainPage::setUnits(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit)
{
    _currentDetail->setTempUnit(tempUnit);
    _currentDetail->setWindUnit(windUnit);
    _currentDetail->setPrecipitationUnit(precipitationUnit);
    ui->unitLabel->setText(_currentDetail->getTempUnitString());
    ui->punitLabel->setText(_currentDetail->getPrecipitationUnitString());
    ui->wunitLabel->setText(_currentDetail->getWindUnitString());
    refreshDetail();
}

void MainPage::finishAnim()
{
    QImage iconImage(QString(":/images/%1.png").arg(_currentDetail->getIcon()));
    ui->iconLabel->setPixmap(QPixmap::fromImage(iconImage));
}

void MainPage::setIconNumber(int number)
{
    _iconNumber = number;
    QImage iconImage(QString(":/images/%1/%2.png").arg(_mainWeather).arg(_iconNumber));
    ui->iconLabel->setPixmap(QPixmap::fromImage(iconImage));
    emit iconNumberChanged(number);
}
