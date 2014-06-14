#include "locationedit.h"
#include <QFile>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QApplication>
#include <QFont>
LocationEdit::LocationEdit(QWidget *parent) :
    QLineEdit(parent)
{
    QFont font("Ubuntu",20);
    setFont(font);
    _completer = new QCompleter(this);
    _completer->setMaxVisibleItems(15);
    _completer->setModel(modelFromFile(":/cityList.txt"));
    _completer->setCompletionMode(QCompleter::InlineCompletion);
    _completer->setCaseSensitivity(Qt::CaseInsensitive);
    _completer->setCompletionColumn(0);
    setCompleter(_completer);
}

QAbstractItemModel* LocationEdit::modelFromFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))
        return new QStringListModel(_completer);
    QStringList words;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        if(!line.isEmpty())
            words << line;
    }

    QApplication::restoreOverrideCursor();
    QStandardItemModel *model = new QStandardItemModel(words.count(),1,_completer);
    for(int i = 0;i < words.count();i++)
    {
        QModelIndex cityIndex = model->index(i,0);
        QStringList str = words[i].split(QRegExp("\\s+"),QString::SkipEmptyParts);
        int strSize = str.count();
        QString name = str[1];
        for(int count = 2;count <= strSize - 4;count++)
            name += (" " + str[count]);
        name += ("," + str[strSize - 1]);
        model->setData(cityIndex,name);
    }
    return model;
}
