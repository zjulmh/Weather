#ifndef HORIZONALSLIDER_H
#define HORIZONALSLIDER_H

#include <QWidget>
#include <QRect>
#include <QPropertyAnimation>
#include <QObjectList>
#include <QHBoxLayout>

class HorizonalSlider : public QWidget
{
    Q_OBJECT
public:
    explicit HorizonalSlider(QWidget *parent = 0);
    
    ~HorizonalSlider();
    void setChildren(const QList<QWidget *> &widgetList);

    void addChild(QWidget* widget);

    int numberOfChildren() const;

    int currentIndex() const;

    void scrollToIndex(int index);

    QWidget* currentWidget() const;

    QWidget* preWidget() const;

    QWidget* nextWidget() const;

    void clear();

    void setShowNumber(int count);
protected:
    void resizeEvent(QResizeEvent *re);

private:
    QWidget* _container;

    QHBoxLayout *_hBox;

    QList<QWidget* > _items;

    QList<int> _widths;

    int _currentIndex;

    int _showCount;

    int _childrenSize;
    
};

#endif // HORIZONALSLIDER_H
