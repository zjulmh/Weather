#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include "horizonalslider.h"
#include <QWheelEvent>

class TitleWIdget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWIdget(QWidget *parent = 0);
    
    void wheelEvent(QWheelEvent *ev);
signals:
    void nextTitleSignal();

    void prevTitleSignal();

    void firstTitleSignal();
public slots:
    void setTitles(const QStringList &titles);

    void nextTitle();

    void prevTitle();

    void firstTitle();

protected:
    void resizeEvent(QResizeEvent *re);

private:
    QStringList _titles;

    HorizonalSlider *_horizonalSlider;


};

#endif // TITLEWIDGET_H
