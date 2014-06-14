#include "currentdetail.h"

CurrentDetail::CurrentDetail(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit):
    BaseDetail(tempUnit,windUnit,precipitationUnit)
{
    _detail.clear();

}


void CurrentDetail::updateDetail(QVariant detail)
{
    _detail.clear();
    bool ok;
    QVariantMap obj = detail.toMap();
    QVariantMap mainContent = obj["main"].toMap();
    _detail["currentTemp"] = mainContent["temp"].toReal(&ok) - 273.15;
    _detail["maxTemp"] = mainContent["temp_max"].toReal(&ok) - 273.15;
    _detail["minTemp"] = mainContent["temp_min"].toReal(&ok) - 273.15;
    _detail["humidity"] = mainContent["humidity"].toString();
    _detail["pressure"] = mainContent["pressure"].toReal(&ok);
    QVariantMap windDetail = obj["wind"].toMap();
    _detail["windSpeed"] = calcKmph(windDetail["speed"].toReal(&ok));
    _detail["windDirection"] = calcWindDir(windDetail["deg"].toReal(&ok));
    QVariantMap weather = obj["weather"].toList()[0].toMap();
    _detail["icon"] = weather["icon"].toString();
    QVariantMap rainPrecipitation = obj["rain"].toMap();
    QVariantMap snowPrecipitation = obj["snow"].toMap();
    if(rainPrecipitation.isEmpty() && snowPrecipitation.isEmpty())
    {
        _detail["precipitation"] = 0;
    }
    else if(!rainPrecipitation.isEmpty())
    {
        _detail["precipitation"] = rainPrecipitation["3h"].toUInt(&ok);

    }
    else
    {
        _detail["precipitation"] = snowPrecipitation["3h"].toUInt(&ok);
    }
    _detail["updateTime"] = calcUnixTime(obj["dt"].toLongLong(&ok)).toString("hh:mm");

}

QString CurrentDetail::getCurrentTemp()
{


    bool ok;
    if(_detail.isEmpty())
        return QString("");
    if(getTempUnit() == CELSIUS)
        return QString::number(qint32(_detail["currentTemp"].toReal(&ok)));
    else
        return QString::number(qint32(celiusToFahrenheit(_detail["currentTemp"].toReal(&ok))));
}

QString CurrentDetail::getMaxTemp()
{
    bool ok;
    if(_detail.isEmpty())
        return QString("");
    if(getTempUnit() == CELSIUS)
        return QString::number(qint32(_detail["maxTemp"].toReal(&ok))) + getMagicUnit();
    else
        return QString::number(qint32(celiusToFahrenheit(_detail["maxTemp"].toReal(&ok)))) + getMagicUnit();
}

QString CurrentDetail::getminTemp()
{
    bool ok;
    if(_detail.isEmpty())
        return QString("");
    if(getTempUnit() == CELSIUS)
        return QString::number(qint32(_detail["minTemp"].toReal(&ok))) + getMagicUnit();
    else
        return QString::number(qint32(celiusToFahrenheit(_detail["minTemp"].toReal(&ok)))) + getMagicUnit();

}

QString CurrentDetail::getWindSpeed()
{
    bool ok;
    if(_detail.isEmpty())
        return QString("");
    if(getWindUnit() == KILOMETERSPERHOUR)
        return QString::number(qint32(_detail["windSpeed"].toReal(&ok)));
    else
        return QString::number(qint32(kilometersToMiles(_detail["windSpeed"].toReal(&ok))));
}

QString CurrentDetail::getWindDirection()
{
    if(_detail.isEmpty())
        return QString("");
    else
        return _detail["windDirection"].toString();
}

QString CurrentDetail::getPressure()
{
    if(_detail.isEmpty())
        return "";
    else
        return _detail["pressure"].toString();
}
QString CurrentDetail::getHumidity()
{
    bool ok;
    if(_detail.isEmpty())
        return "";
    else
        return _detail["humidity"].toString();
}
QString CurrentDetail::getPrecipitation()
{
    bool ok;
    if(_detail.isEmpty())
        return "";
    if(getPrecipitationUnit() == MILLIMETERS)
        return QString::number(_detail["precipitation"].toUInt(&ok));
    else
        return QString::number(qint32(millimeterToInches(_detail["precipitation"].toReal(&ok))));
}

QString CurrentDetail::getUpdateTime()
{
    if(_detail.isEmpty())
        return QString("");
    else
        return _detail["updateTime"].toString();
}

QString CurrentDetail::getIcon()
{
    if(_detail.isEmpty())
        return QString("");
    else
        return getTrueIcon(_detail["icon"].toString());
}
