#ifndef BASEDETAIL_H
#define BASEDETAIL_H
#include <QVariant>
#include <QVariantMap>
#include <QDateTime>
#include "unitType.h"
#include <QTextCodec>

class BaseDetail
{
public:
    BaseDetail(TEMPUNIT tempUnit = CELSIUS, WINDUNIT windUnit = KILOMETERSPERHOUR,PRECIPITATIONUNIT precipitationUnit = MILLIMETERS);

    void setTempUnit(TEMPUNIT tempUnit);

    void setWindUnit(WINDUNIT windUnit);

    void setPrecipitationUnit(PRECIPITATIONUNIT precipitationUnit);

    QString getTempUnitString();

    QString getWindUnitString();

    QString getPrecipitationUnitString();

    QString getTrueIcon(QString icon);

    TEMPUNIT getTempUnit();
    WINDUNIT getWindUnit();
    PRECIPITATIONUNIT getPrecipitationUnit();

    virtual void updateDetail(QVariant detail);


public:
    QString calcWindDir(const qreal &degrees);

    QDateTime calcUnixTime(const qint64 &time);

    qreal celiusToFahrenheit(qreal celius);

    qreal millimeterToInches(qreal millimeter);

    qreal kilometersToMiles(qreal kilometers);

    qreal calcKmph(qreal mps){return mps * 3.6;}

    QString getMagicUnit();

    static int FahrenheitToCelius(int fahrenheit);

private:
    TEMPUNIT _tempUnit;
    WINDUNIT _windUnit;
    PRECIPITATIONUNIT _precipitationUnit;
    QString _magicUnit;

    QMap<QString,QString> _iconMap;

};

#endif // BASEDETAIL_H
