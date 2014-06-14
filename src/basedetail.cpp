#include "basedetail.h"
/*
 *base class for getting weather detail;derived
 *by HourlyDetail, DailyDetail and CurrentDetail
 */


BaseDetail::BaseDetail(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit):
    _tempUnit(tempUnit),
    _windUnit(windUnit),
    _precipitationUnit(precipitationUnit)
{
    QTextCodec *codec = QTextCodec::codecForName ("utf-8");
    QByteArray unitsArray;
    unitsArray.append("°");
    _magicUnit = codec->toUnicode(unitsArray);
    _iconMap.clear();
    _iconMap.insert("01d","sun");
    _iconMap.insert("01n","moon");
    _iconMap.insert("02d", "cloud_sun");
    _iconMap.insert("02n", "cloud_moon");
    _iconMap.insert("03d", "cloud_sun");
    _iconMap.insert("03n", "cloud_moon");
    _iconMap.insert("04d", "cloud");
    _iconMap.insert("04n", "cloud");
    _iconMap.insert("09d", "rain");
    _iconMap.insert("09n", "rain");
    _iconMap.insert("10d", "rain");
    _iconMap.insert("10n", "rain");
    _iconMap.insert("11d", "thunder");
    _iconMap.insert("11n", "thunder");
    _iconMap.insert("13d", "snow_shower");
    _iconMap.insert("13n", "snow_shower");
    _iconMap.insert("50d", "fog");
    _iconMap.insert("50n", "fog");

}


void BaseDetail::updateDetail(QVariant detail)
{

}

void BaseDetail::setTempUnit(TEMPUNIT tempUnit)
{
    _tempUnit = tempUnit;
}

void BaseDetail::setWindUnit(WINDUNIT windUnit)
{
    _windUnit = windUnit;
}

void BaseDetail::setPrecipitationUnit(PRECIPITATIONUNIT precipitationUnit)
{
    _precipitationUnit = precipitationUnit;
}

QString BaseDetail::getTempUnitString()
{
    QTextCodec *codec = QTextCodec::codecForName ("utf-8");
    QByteArray unitsArray;
    if(_tempUnit == CELSIUS)
        unitsArray.append("°C");
    else
        unitsArray.append("°F");
    return codec->toUnicode(unitsArray);
}

QString BaseDetail::getWindUnitString()
{
    if(_windUnit == KILOMETERSPERHOUR)
        return QString("km/h");
    else
        return QString("mph");
}

TEMPUNIT BaseDetail::getTempUnit()
{
    return _tempUnit;
}

WINDUNIT BaseDetail::getWindUnit()
{
    return _windUnit;
}

QString BaseDetail::getPrecipitationUnitString()
{
    if(_precipitationUnit == MILLIMETERS)
        return QString("mm");
    else
        return QString("inch");
}

PRECIPITATIONUNIT BaseDetail::getPrecipitationUnit()
{
    return _precipitationUnit;
}

QString BaseDetail::calcWindDir(const qreal &degrees)
{
    QString windDirection;
    if(degrees >=0 && degrees <= 30){
        windDirection = "N";
    } else if(degrees >30 && degrees <= 60){
        windDirection = "NE";
    } else if(degrees >60 && degrees <= 120){
        windDirection = "E";
    } else if(degrees >120 && degrees <= 150){
        windDirection = "SE";
    } else if(degrees >150 && degrees <= 210){
        windDirection = "S";
    } else if(degrees >210 && degrees <= 240){
        windDirection = "SW";
    } else if(degrees >240 && degrees <= 300){
        windDirection = "W";
    } else if(degrees >300 && degrees <= 330){
        windDirection = "NW";
    } else if(degrees >330 && degrees <= 360){
        windDirection = "N";
    }
    return windDirection;
}

QDateTime BaseDetail::calcUnixTime(const qint64 &time)
{
    return QDateTime::fromMSecsSinceEpoch(time * 1000);
}

qreal BaseDetail::celiusToFahrenheit(qreal celius)
{
    return 32 + celius * 1.8;
}

qreal BaseDetail::millimeterToInches(qreal millimeter)
{
    return millimeter / 25.4;
}

qreal BaseDetail::kilometersToMiles(qreal kilometers)
{
    return kilometers / 1.61;
}

QString BaseDetail::getMagicUnit()
{
    return _magicUnit;
}

int BaseDetail::FahrenheitToCelius(int fahrenheit)
{
    return qint32((fahrenheit - 32) / 1.8);
}

QString BaseDetail::getTrueIcon(QString icon)
{
    return _iconMap[icon];
}
