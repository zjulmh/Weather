#include "horizonalslider.h"

HorizonalSlider::HorizonalSlider(QWidget *parent) :
    QWidget(parent),
    _hBox(NULL),
    _showCount(1),
    _childrenSize(0)
{
    _container = new QWidget(this);
    _container->setGeometry(0,0,this->width(),this->height());

    _currentIndex = 0;
}


HorizonalSlider::~HorizonalSlider()
{
    delete _container;
}

void HorizonalSlider::setShowNumber(int count)
{
    _showCount = count;
}

void HorizonalSlider::clear()
{
    if(_hBox != NULL)
    {
        _container->setLayout(NULL);
        delete _hBox;
    }
    _hBox = new QHBoxLayout(_container);
    _hBox->setMargin(0);
    _hBox->setSpacing(0);
    _hBox->setContentsMargins(0,0,0,0);
    _hBox->setGeometry(QRect(0,0,_container->width(),_container->height()));
    _container->setLayout(_hBox);
    _items.clear();
    _widths.clear();
    _childrenSize = 0;
}

void HorizonalSlider::setChildren(const QList<QWidget *> &widgetList)
{
    clear();
    _items = widgetList;
    int stepWidth = this->width() / _showCount;
    foreach (QWidget* item, _items) {
        item->setParent(_container);
        _hBox->addWidget(item);
        _childrenSize++;
    }
    _container->setGeometry(0,0,stepWidth * _childrenSize,this->height());
    foreach (QWidget* item, _items) {
        _widths.append(item->width());
    }
    _container->move(0,0);
}

void HorizonalSlider::addChild(QWidget *widget)
{
    _items.append(widget);
    int wholeWidth = _container->width();
    wholeWidth += widget->width();
    _widths.append(widget->width());
    _hBox->addWidget(widget);
    _childrenSize++;
}

void HorizonalSlider::scrollToIndex(int index)
{
    if(index > _childrenSize - 1)
        return;
    _currentIndex = index;

    QPropertyAnimation *anim = new QPropertyAnimation(_container,"geometry");
    anim->setDuration(300);
    anim->setStartValue(_container->geometry());

    int endWidth = 0;
    if(index == 0)
        endWidth = 0;
    else if(index == _childrenSize - 1)
    {
        endWidth = _container->width();
        for(int i = 1;i <= _showCount;i++)
            endWidth -= _widths[_childrenSize - i];
    }
    else
    {
        endWidth = 0;
        for(int i = 0;i < index - 1;i++)
            endWidth += _widths[i];
        endWidth += _widths[index - 1] / _showCount;
    }

    QRect endVal(-endWidth,_container->geometry().y(),_container->geometry().width(),_container->geometry().height());
    anim->setEndValue(endVal);
    anim->setEasingCurve(QEasingCurve::Linear);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

int HorizonalSlider::numberOfChildren() const
{
    return _childrenSize;
}

int HorizonalSlider::currentIndex() const
{
    return _currentIndex;
}

QWidget* HorizonalSlider::currentWidget() const
{
    return _items[_currentIndex];
}

QWidget* HorizonalSlider::preWidget() const
{
    if(_currentIndex > 0)
        return _items[_currentIndex - 1];
    else
        return NULL;
}

QWidget* HorizonalSlider::nextWidget() const
{
    if(_currentIndex < _childrenSize - 1)
        return _items[_currentIndex + 1];
    else
        return NULL;
}

void HorizonalSlider::resizeEvent(QResizeEvent *re)
{
    QWidget::resizeEvent(re);
    _container->resize(this->width() / _showCount * _childrenSize,this->height());
    _widths.clear();
    foreach(QWidget *item,_items)
    {
        item->resize(_container->width() / _childrenSize,_container->height());
        _widths.append(item->width());
    }
    scrollToIndex(_currentIndex);

}
