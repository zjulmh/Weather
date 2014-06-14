#include "collectwidget.h"
#include <QDebug>

CollectWidget::CollectWidget(QWidget *parent, TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit):
    QWidget(parent),
    _tempUnit(tempUnit),
    _windUnit(windUnit),
    _precipitationUnit(precipitationUnit)
{
//    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    resize(400,400);
    _cityList.clear();
    _locationWidgetList.clear();
    _collectArea = new QScrollArea(this);
    _collectArea->setGeometry(0,0,this->width(),350);
    _collectArea->setAlignment(Qt::AlignHCenter);
    _collectArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _collectArea->setStyleSheet("background-color:rgba(255,255,255,0)");
    _contentWidget = new QWidget(_collectArea);
    _contentWidget->resize(300,_collectArea->height());
    _Vlayout = new QVBoxLayout(_contentWidget);
    _Vlayout->setSpacing(10);
    _Vlayout->setMargin(0);
    _contentWidget->setLayout(_Vlayout);
    _collectArea->setWidget(_contentWidget);
    _contentWidget->show();
    _addCityButton = new QToolButton(this);
    QIcon icon(":/images/add.png");
    _addCityButton->setIcon(icon);
    _addCityButton->setGeometry(0,_collectArea->height(),this->width(),this->height() - _collectArea->height());
    _addCityButton->setStyleSheet("border-width:0px;background-color:transparent");
    connect(_addCityButton,SIGNAL(clicked()),this,SLOT(onButtonClicked()));

}

CollectWidget::CollectWidget( QWidget *parent, QVariantList cityList , TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit) :
    QWidget(parent),
    _cityList(cityList),
    _tempUnit(tempUnit),
    _windUnit(windUnit),
    _precipitationUnit(precipitationUnit)
{
    resize(400,400);
    _collectArea = new QScrollArea(this);
    _collectArea->setStyleSheet("background-color:rgba(255,255,255,0);border-width:0px;color:white");
    _collectArea->setGeometry(0,0,this->width(),350);
    _collectArea->setAlignment(Qt::AlignHCenter);
    _collectArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _collectArea->setStyleSheet("background-color:rgba(255,255,255,0);border:none");
    _contentWidget = new QWidget(_collectArea);
    _contentWidget->resize(300,70 * _cityList.size() > _collectArea->height() ? 70 * _cityList.size() : _collectArea->height());
    _Vlayout = new QVBoxLayout(_contentWidget);
    _Vlayout->setSpacing(10);
    _Vlayout->setMargin(0);
    foreach (QVariant city, _cityList) {
        QVariantMap cityDetail = city.toMap();
        LocationWidget *locationWidget = new LocationWidget(_contentWidget,cityDetail,_tempUnit,_windUnit,_precipitationUnit);
        _Vlayout->addWidget(locationWidget);
        _locationWidgetList.append(locationWidget);
        connect(locationWidget,SIGNAL(setMainPage(QString)),this,SLOT(setMainpage(QString)));
        connect(locationWidget,SIGNAL(viewDetailCity(QString)),this,SLOT(viewDetail(QString)));
        connect(locationWidget,SIGNAL(deleteCity(QString)),this,SLOT(deleteCity(QString)));
    }
    _contentWidget->setLayout(_Vlayout);
    _collectArea->setWidget(_contentWidget);
    _contentWidget->show();
    _addCityButton = new QToolButton(this);
    QIcon icon(":/images/add.png");
    _addCityButton->setIcon(icon);
    _addCityButton->setGeometry(0,_collectArea->height(),this->width(),this->height() - _collectArea->height());
    _addCityButton->setStyleSheet("border-width:0px;border-top-width:3px;border-top-style:solid;border-top-color:white;background-color:transparent");
    connect(_addCityButton,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    updateDetail();
}

void CollectWidget::onButtonClicked()
{
    if(_cityList.isEmpty())
        emit addCitySignal(1);
    else
        emit addCitySignal(0);
}

void CollectWidget::updateDetail()
{

    emit hideLoadingWidget();
    foreach (LocationWidget *tempwidget, _locationWidgetList) {
        tempwidget->updateDetail();
    }

}

void CollectWidget::refreshDetail()
{
    foreach (LocationWidget *tempWidget, _locationWidgetList) {
        tempWidget->refreshDetail();
    }
}

void CollectWidget::setUnits(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit)
{
    foreach (LocationWidget *tempWidget, _locationWidgetList) {
        tempWidget->setUnits(tempUnit,windUnit,precipitationUnit);
    }
    _tempUnit = tempUnit;
    _windUnit = windUnit;
    _precipitationUnit = precipitationUnit;
    refreshDetail();
}

void CollectWidget::addCity(QVariantMap city)
{
    LocationWidget *locationWidget = new LocationWidget(_contentWidget,city,_tempUnit,_windUnit,_precipitationUnit);
    _Vlayout->addWidget(locationWidget);
    _locationWidgetList.append(locationWidget);
    _cityList.append(city);
    connect(locationWidget,SIGNAL(setMainPage(QString)),this,SLOT(setMainpage(QString)));
    connect(locationWidget,SIGNAL(viewDetailCity(QString)),this,SLOT(viewDetail(QString)));
    connect(locationWidget,SIGNAL(deleteCity(QString)),this,SLOT(deleteCity(QString)));
    _contentWidget->resize(300,70 * _cityList.size() > _collectArea->height() ? 70 * _cityList.size() : _collectArea->height());
    updateDetail();
}

void CollectWidget::deleteCity(QString cityName)
{
   int index = 0;
   int cityCount = _cityList.size();
   for(index = 0;index < cityCount;index++)
   {
       QVariantMap tempCity = _cityList[index].toMap();
       if(tempCity["cityName"].toString() == cityName)
           break;
   }
   if(index < cityCount)
   {
       _cityList.removeAt(index);
       LocationWidget *tempWidget = _locationWidgetList[index];
       _locationWidgetList.removeAt(index);
       tempWidget->deleteLater();

       _contentWidget->resize(300,70 * _cityList.size() > _collectArea->height() ? 70 * _cityList.size() : _collectArea->height());
       updateDetail();
       emit deleteCitySignal(cityName);
   }

}


void CollectWidget::setMainpage(QString cityName)
{
    int index = 0;
    for(;index < _cityList.size();index++)
    {
        QVariantMap tempCity = _cityList[index].toMap();
        if(tempCity["cityName"] != cityName && tempCity["flag"] == 1)
        {
            tempCity["flag"] = 0;
            _cityList[index] = tempCity;
            _locationWidgetList[index]->toggleFlag();
        }
        else if(tempCity["cityName"] == cityName && tempCity["flag"] != 1)
        {
            tempCity["flag"] = 1;
            _cityList[index] = tempCity;
            _locationWidgetList[index]->toggleFlag();
        }
    }
    updateDetail();
    emit setMainPageSignal(cityName);
}

void CollectWidget::viewDetail(QString cityName)
{
    emit viewDetailSingal(cityName);
}



