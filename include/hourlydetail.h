#ifndef HOURLYDETAIL_H
#define HOURLYDETAIL_H
#include "basedetail.h"
#include <QStringList>
class HourlyDetail : public BaseDetail
{
public:
    HourlyDetail(TEMPUNIT tempUnit = CELSIUS,WINDUNIT windUnit = KILOMETERSPERHOUR,PRECIPITATIONUNIT precipitation = MILLIMETERS,int hourCount = 7);

    virtual void updateDetail(QVariant detail);

public:
    QStringList getHourlyTime();
    QStringList getMaxTemp();
    QStringList getMinTemp();
    QStringList getIcon();

private:
    QStringList _hourlyTimeList;
    QList<qreal> _maxTempList;
    QList<qreal> _minTempList;
    QStringList _iconList;

    int _hourCount;
};

#endif // HOURLYDETAIL_H
