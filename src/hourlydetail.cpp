#include "hourlydetail.h"

HourlyDetail::HourlyDetail(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitation, int hourCount):
    BaseDetail(tempUnit,windUnit,precipitation),
    _hourCount(hourCount)
{
    _hourlyTimeList.clear();
    _maxTempList.clear();
    _minTempList.clear();
    _iconList.clear();
}

void HourlyDetail::updateDetail(QVariant detail)
{
    _hourlyTimeList.clear();
    _maxTempList.clear();
    _minTempList.clear();
    _iconList.clear();

    bool ok;

    QVariantMap obj = detail.toMap();
    QVariantList hourlyList = obj["list"].toList();
    for(int index = 0;index < _hourCount;index++)
    {
        QVariantMap hourlyDetail = hourlyList[index].toMap();
        _hourlyTimeList.append(QDateTime::fromMSecsSinceEpoch(1000 * hourlyDetail["dt"].toLongLong(&ok)).toString("hh:mm"));
        QVariantMap temp = hourlyDetail["main"].toMap();
        _maxTempList.append(temp["temp_max"].toReal(&ok) - 273.15);
        _minTempList.append(temp["temp_min"].toReal(&ok) - 273.15);
        QVariantMap hourlyWeather = hourlyDetail["weather"].toList()[0].toMap();
        _iconList.append(getTrueIcon(hourlyWeather["icon"].toString()));
    }
}

QStringList HourlyDetail::getHourlyTime()
{
    return _hourlyTimeList;
}

QStringList HourlyDetail::getIcon()
{
    return _iconList;
}

QStringList HourlyDetail::getMaxTemp()
{
    QStringList maxTempString;
    foreach (qreal temp, _maxTempList) {
        if(getTempUnit() == CELSIUS)
            maxTempString.append(QString::number(qint32(temp)) + getMagicUnit());
        else
            maxTempString.append(QString::number(qint32(celiusToFahrenheit(temp))) + getMagicUnit());
    }
    return maxTempString;
}

QStringList HourlyDetail::getMinTemp()
{
    QStringList minTempString;
    foreach (qreal temp, _minTempList) {
        if(getTempUnit() == CELSIUS)
            minTempString.append(QString::number(qint32(temp)) + getMagicUnit());
        else
            minTempString.append(QString::number(qint32(celiusToFahrenheit(temp))) + getMagicUnit());
    }
    return minTempString;
}
