#ifndef ADDLOCATIONDIALOG_H
#define ADDLOCATIONDIALOG_H

#include <QWidget>
#include "locationedit.h"
#include <QToolButton>
class AddLocationDialog : public QWidget
{
    Q_OBJECT
public:
    explicit AddLocationDialog(QWidget *parent = 0,int flag = 1);
    
signals:
    void addCitySignal(QString cityName,int flag);
public slots:

private:
    QToolButton *_confirmBtn;
    LocationEdit *_locationEdit;
    int _flag;
private slots:
    void onConfirmBtnClicked();
    
};

#endif // ADDLOCATIONDIALOG_H
