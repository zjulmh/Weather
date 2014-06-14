#ifndef CURRENTDETAIL_H
#define CURRENTDETAIL_H
#include "basedetail.h"
class CurrentDetail : public BaseDetail
{
public:
    CurrentDetail(TEMPUNIT tempUnit = CELSIUS, WINDUNIT windUnit = KILOMETERSPERHOUR,PRECIPITATIONUNIT precipitationUnit = MILLIMETERS);

    virtual void updateDetail(QVariant detail);

public:
    QString getCurrentTemp();
    QString getMaxTemp();
    QString getminTemp();
    QString getWindSpeed();
    QString getWindDirection();
    QString getPressure();
    QString getHumidity();
    QString getPrecipitation();
    QString getUpdateTime();
    QString getIcon();

private:
    QVariantMap _detail;
};

#endif // CURRENTDETAIL_H
