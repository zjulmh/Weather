#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QWidget>
#include <QMovie>

namespace Ui {
class LoadingWidget;
}

class LoadingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LoadingWidget(QWidget *parent = 0);
    ~LoadingWidget();
public slots:
    void onLoad();

    void onHide();
    
private:
    Ui::LoadingWidget *ui;
    QMovie *_movie;
};

#endif // LOADINGWIDGET_H
