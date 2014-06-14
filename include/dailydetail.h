#ifndef DAILYDETAIL_H
#define DAILYDETAIL_H
#include "basedetail.h"
#include <QStringList>
class DailyDetail : public BaseDetail
{
public:
    DailyDetail(TEMPUNIT tempUnit = CELSIUS,WINDUNIT windUnit = KILOMETERSPERHOUR,PRECIPITATIONUNIT precipitation = MILLIMETERS,int dayCount = 7);

    virtual void updateDetail(QVariant detail);

public:
    QStringList getDailyDate();
    QStringList getMaxTemp();
    QStringList getMinTemp();
    QStringList getIcon();

private:
    QStringList _dailyDateList;
    QList<qreal> _maxTempList;
    QList<qreal> _minTempList;
    QStringList _iconList;

    int _dayCount;
};

#endif // DAILYDETAIL_H
