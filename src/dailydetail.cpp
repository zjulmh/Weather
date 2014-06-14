#include "dailydetail.h"



DailyDetail::DailyDetail(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitation, int dayCount):
    BaseDetail(tempUnit,windUnit,precipitation),
    _dayCount(dayCount)
{
    _dailyDateList.clear();
    _maxTempList.clear();
    _minTempList.clear();
    _iconList.clear();
}

void DailyDetail::updateDetail(QVariant detail)
{
    _dailyDateList.clear();
    _maxTempList.clear();
    _minTempList.clear();
    _iconList.clear();

    bool ok;
    QVariantMap obj = detail.toMap();
    QVariantList dailyList = obj["list"].toList();
    for(int index = 0;index < _dayCount;index++)
    {
        QVariantMap dailyDetail = dailyList[index].toMap();
        _dailyDateList.append(QDateTime::fromMSecsSinceEpoch(1000 * dailyDetail["dt"].toLongLong(&ok)).toString("ddd,dd,MMM"));
        QVariantMap temp = dailyDetail["temp"].toMap();
        _maxTempList.append(temp["max"].toReal(&ok) - 273.15);
        _minTempList.append(temp["min"].toReal(&ok) - 273.15);
        QVariantMap dailyWeather = dailyDetail["weather"].toList()[0].toMap();
        _iconList.append(getTrueIcon(dailyWeather["icon"].toString()));
    }
}

QStringList DailyDetail::getDailyDate()
{
    return _dailyDateList;
}

QStringList DailyDetail::getIcon()
{
    return _iconList;
}

QStringList DailyDetail::getMaxTemp()
{
    QStringList maxTempString;
    foreach(qreal temp,_maxTempList)
    {
        if(getTempUnit() == CELSIUS)
        {
            maxTempString.append(QString::number(qint32(temp)) + getMagicUnit());
        }
        else
        {
            maxTempString.append(QString::number(qint32(celiusToFahrenheit(temp))) + getMagicUnit());
        }
    }
    return maxTempString;
}

QStringList DailyDetail::getMinTemp()
{
    QStringList minTempString;
    foreach(qreal temp,_minTempList)
    {
        if(getTempUnit() == CELSIUS)
        {
            minTempString.append(QString::number(qint32(temp)) + getMagicUnit());
        }
        else
        {
            minTempString.append(QString::number(qint32(celiusToFahrenheit(temp))) + getMagicUnit());
        }
    }
    return minTempString;
}
