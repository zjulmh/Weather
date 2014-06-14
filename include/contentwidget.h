#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include "horizonalslider.h"
#include <QHBoxLayout>
#include <QWheelEvent>

class ContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContentWidget(QWidget *parent = 0);
    
//    void wheelEvent(QWheelEvent *ev);
signals:
    void nextWidgetSignal();

    void prevWidgetSignal();

    void firstWidgetSignal();
    
public slots:
    void setWidget(const QList<QWidget* > &widgetList);

    void nextWidget();

    void prevWidget();

    void firstWidget();

protected:
    void resizeEvent(QResizeEvent *re);

private:
    QList<QWidget *> _widgets;

    HorizonalSlider *_horizonalSlider;
};

#endif // CONTENTWIDGET_H
