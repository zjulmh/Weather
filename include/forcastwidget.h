#ifndef FORCASTWIDGET_H
#define FORCASTWIDGET_H

#include <QWidget>

namespace Ui {
class ForcastWidget;
}

class ForcastWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ForcastWidget(QWidget *parent = 0);
    ~ForcastWidget();

    void setDateTime(QString dateTime);

    void setIcon(QString icon);

    void setMinTemp(QString minTemp);

    void setMaxTemp(QString maxTemp);
    
private:
    Ui::ForcastWidget *ui;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // FORCASTWIDGET_H
