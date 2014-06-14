#include "locationwidget.h"
#include "ui_locationwidget.h"
#include <QDebug>
#include <QPainter>
#include <QPalette>
LocationWidget::LocationWidget(QWidget *parent, QVariantMap city, TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit) :
    QWidget(parent),
    ui(new Ui::LocationWidget),
    _city(city),
    _manager(NULL)
{
    ui->setupUi(this);

    _currentDetail = new CurrentDetail(tempUnit,windUnit,precipitationUnit);
    cMenu = new QMenu(this);
    QPalette myPalette = cMenu->palette();
    myPalette.setColor(QPalette::Window,QColor(0,0,0,100));
    myPalette.setColor(QPalette::WindowText,QColor(255,255,255,255));
    cMenu->setPalette(myPalette);
    _setMainPage = cMenu->addAction("Set MainPage");
    cMenu->addSeparator();
    _deleteAction = cMenu->addAction("Delete");
    cMenu->addSeparator();
    _viewDetail = cMenu->addAction("View detail");

    bool ok;
    if(_city["flag"].toInt(&ok) == 1)
    {
        QImage mainImage(":/images/main.png");
        ui->mainFlagIcon->setPixmap(QPixmap::fromImage(mainImage));
        _setMainPage->setEnabled(false);
        _deleteAction->setEnabled(false);
    }
    connect(_setMainPage,SIGNAL(triggered()),this,SLOT(setMainPage()));
    connect(_deleteAction,SIGNAL(triggered()),this,SLOT(deleteCity()));
    connect(_viewDetail,SIGNAL(triggered()),this,SLOT(viewDetail()));
}

LocationWidget::~LocationWidget()
{
    delete ui;
    delete _manager;
    delete _setMainPage;
    delete _deleteAction;
    delete _viewDetail;
}

void LocationWidget::updateDetail()
{
    if(_manager == NULL)
    {
        _manager = new QNetworkAccessManager(this);
        connect(_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onReply(QNetworkReply*)));
    }
    QString location = "q=" + _city["cityName"].toString();
    QString address = "http://api.openweathermap.org/data/2.5/weather?" + location + "&APPID=255cb28e2c88da079d8c94fbccd17068";
    _manager->get (QNetworkRequest(QUrl(address)));
}

void LocationWidget::onReply(QNetworkReply *reply)
{
    if(reply->error () != QNetworkReply::NoError){
        reply->deleteLater ();
        return;
    }
    QTextCodec *codec = QTextCodec::codecForName ("utf-8");
    QString all = codec->toUnicode (reply->readAll ());
//    qDebug() << all;
    QJson::Parser parser;
    bool ok;
    QVariant result = parser.parse (all.toAscii (),&ok);
    if(ok)
    {
        _currentDetail->updateDetail(result);
        refreshDetail();
    }
    reply->deleteLater();
}

void LocationWidget::refreshDetail()
{
    bool ok;
    if(_city["flag"].toInt(&ok) == 1)
    {
        qDebug() << "Maincity:" + _city["cityName"].toString();
        QImage mainImage(":/images/main.png");
        ui->mainFlagIcon->setPixmap(QPixmap::fromImage(mainImage));
        _setMainPage->setEnabled(false);
        _deleteAction->setEnabled(false);
    }
    else
    {
        qDebug() << "city:" + _city["cityName"].toString();
        ui->mainFlagIcon->setText(" ");
        _setMainPage->setEnabled(true);
        _deleteAction->setEnabled(true);
    }
    ui->locationLabel->setText(_city["cityName"].toString());

    QImage iconImage(QString(":/images/%1.png").arg(_currentDetail->getIcon()));
    ui->iconLabel->setPixmap(QPixmap::fromImage(iconImage));


//    ui->iconLabel->setText(_currentDetail->getIcon());
    ui->maxTempLabel->setText(_currentDetail->getMaxTemp());
    ui->minTempLabel->setText(_currentDetail->getminTemp());
}

void LocationWidget::paintEvent(QPaintEvent *ev)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void LocationWidget::setUnits(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit)
{
    _currentDetail->setWindUnit(windUnit);
    _currentDetail->setTempUnit(tempUnit);
    _currentDetail->setPrecipitationUnit(precipitationUnit);
}

void LocationWidget::deleteCity()
{
    emit deleteCity(_city["cityName"].toString());
}

void LocationWidget::viewDetail()
{
    emit viewDetailCity(_city["cityName"].toString());
}

void LocationWidget::setMainPage()
{
    //_city["flag"] = 1;
    emit setMainPage(_city["cityName"].toString());
}


void LocationWidget::contextMenuEvent(QContextMenuEvent *ev)
{
    cMenu->exec(QCursor::pos());
    QWidget::contextMenuEvent(ev);
}


void LocationWidget::toggleFlag()
{
    if(_city["flag"] == 0)
    {
        _city["flag"] = 1;
    }
    else
        _city["flag"] = 0;
}


