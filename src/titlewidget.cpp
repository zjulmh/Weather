#include "titlewidget.h"
#include <QLabel>
#include <QFont>
#include <QDebug>
const QString HIGHTLIGHT_STYLE = "font-size:25px;font-style:bold;color:white";
const QString DARK_STYLE = "font-size:20px;font-style:normal; color:darkgrey";

TitleWIdget::TitleWIdget(QWidget *parent) :
    QWidget(parent)
{
    setStyleSheet("background-color:transparent");
    _horizonalSlider = new HorizonalSlider(this);
    _horizonalSlider->setGeometry(0,0,this->width(),this->height());
    _horizonalSlider->setShowNumber(2);
}

void TitleWIdget::wheelEvent(QWheelEvent *ev)
{
    if(ev->delta() > 0)
    {
        prevTitle();
        emit prevTitleSignal();
    }
    else
    {
        nextTitle();
        emit nextTitleSignal();
    }
}


void TitleWIdget::nextTitle()
{
    if(_horizonalSlider->currentIndex() == _horizonalSlider->numberOfChildren() - 1)
        return;
    _horizonalSlider->scrollToIndex(_horizonalSlider->currentIndex() + 1);
    _horizonalSlider->currentWidget()->setStyleSheet(HIGHTLIGHT_STYLE);
    _horizonalSlider->preWidget()->setStyleSheet(DARK_STYLE);
    if(_horizonalSlider->nextWidget())
        _horizonalSlider->nextWidget()->setStyleSheet(DARK_STYLE);
}

void TitleWIdget::prevTitle()
{
    if(_horizonalSlider->currentIndex() == 0)
        return;
    _horizonalSlider->scrollToIndex(_horizonalSlider->currentIndex() - 1);
    _horizonalSlider->currentWidget()->setStyleSheet(HIGHTLIGHT_STYLE);
    _horizonalSlider->nextWidget()->setStyleSheet(DARK_STYLE);
    if(_horizonalSlider->preWidget())
        _horizonalSlider->preWidget()->setStyleSheet(DARK_STYLE);
}

void TitleWIdget::firstTitle()
{
    _horizonalSlider->scrollToIndex(0);
    _horizonalSlider->currentWidget()->setStyleSheet(HIGHTLIGHT_STYLE);
    _horizonalSlider->nextWidget()->setStyleSheet(DARK_STYLE);
    emit firstTitleSignal();
}


void TitleWIdget::setTitles(const QStringList &titles)
{
    _titles = titles;
    int currentIndex = 0;
    QList<QWidget* > labelList;
    foreach (QString title, _titles) {
        QLabel *label = new QLabel(title,_horizonalSlider);
        label->setStyleSheet(DARK_STYLE);
        label->resize(_horizonalSlider->width(),_horizonalSlider->height());
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QFont font("Tahoma",20);
        label->setFont(font);
        labelList.append(label);
    }
    _horizonalSlider->setChildren(labelList);
    _horizonalSlider->scrollToIndex(currentIndex);
}

void TitleWIdget::resizeEvent(QResizeEvent *re)
{

    _horizonalSlider->setGeometry(0,0,this->width(),this->height());
    _horizonalSlider->currentWidget()->setStyleSheet(HIGHTLIGHT_STYLE);
    QWidget::resizeEvent(re);
}
