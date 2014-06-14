#ifndef LOCATIONEDIT_H
#define LOCATIONEDIT_H

#include <QLineEdit>
#include <QCompleter>
#include <QWidget>
#include <QAbstractItemModel>

class LocationEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LocationEdit(QWidget *parent = 0);
    
private:
    QCompleter *_completer;
    QAbstractItemModel *modelFromFile(const QString &fileName);
    
};

#endif // LOCATIONEDIT_H
