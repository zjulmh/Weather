#include "contentwidget.h"

ContentWidget::ContentWidget(QWidget *parent) :
    QWidget(parent)
{
    _horizonalSlider = new HorizonalSlider(this);
    _horizonalSlider->setShowNumber(1);
    _horizonalSlider->setGeometry(0,0,this->width(),this->height());
}

//void ContentWidget::wheelEvent(QWheelEvent *ev)
//{
//    if(ev->delta() > 0)
//    {
//        prevWidget();
//        emit prevWidgetSignal();
//    }
//    else
//    {
//        nextWidget();
//        emit nextWidgetSignal();
//    }
//}

void ContentWidget::nextWidget()
{
    if(_horizonalSlider->currentIndex() == _horizonalSlider->numberOfChildren() - 1)
        return;
    else
        _horizonalSlider->scrollToIndex(_horizonalSlider->currentIndex() + 1);
}

void ContentWidget::prevWidget()
{
    if(_horizonalSlider->currentIndex() == 0)
        return;
    else
        _horizonalSlider->scrollToIndex(_horizonalSlider->currentIndex() - 1);
}

void ContentWidget::firstWidget()
{
    _horizonalSlider->scrollToIndex(0);
    emit firstWidgetSignal();
}

void ContentWidget::setWidget(const QList<QWidget *> &widgetList)
{
    _widgets = widgetList;
    _horizonalSlider->setChildren(_widgets);
    _horizonalSlider->scrollToIndex(0);
}


void ContentWidget::resizeEvent(QResizeEvent *re)
{
    _horizonalSlider->setGeometry(0,0,this->width(),this->height());
    QWidget::resizeEvent(re);
}
