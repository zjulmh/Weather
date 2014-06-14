#include "weather.h"
#include "ui_weather.h"
#include <QLabel>
#include <QLinearGradient>
#include <QDebug>
Weather::Weather(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Weather),
    _tempUnit(CELSIUS),
    _windUnit(KILOMETERSPERHOUR),
    _precipitationUnit(MILLIMETERS),
    _mainPage(NULL),
    _dailyWidget(NULL),
    _hourlyWidget(NULL),
    _settingWidget(NULL),
    _collectWidget(NULL),
    _receiveCount(0),
    _settings("data.ini")
{
    ui->setupUi(this);
    createMap();
    QPalette myPalette = this->palette();
    QLinearGradient linearGradient(0,0,this->width(),this->height());
    linearGradient.setColorAt(0.0,QColor(255,39,10,255));
    linearGradient.setColorAt(1.0,QColor(224, 65, 19));
    QBrush brush(linearGradient);
    myPalette.setBrush(QPalette::Window,brush);
    this->setPalette(myPalette);

    _titleWidget = new TitleWIdget(this);
    _titleWidget->setGeometry(0,0,this->width(),ui->frame->geometry().y());
    QStringList titles;
    titles << "Main" << "Daily" << "Hourly" << "Locations" << "Settings";
    _titleWidget->setTitles(titles);
    _cityList.clear();

    readSettings();
    /*
    QVariantMap city;
    city["cityName"] = "Shanghai,CN";
    city["flag"] = 1;
    QVariantList cityList;
    cityList.append(city);
    city["cityName"] = "Beijing,CN";
    city["flag"] = 0;
    cityList.append(city);
    city["cityName"] = "Shenzhen,CN";
    city["flag"] = 0;
    cityList.append(city);
    city["cityName"] = "Shantou,CN";
    city["flag"] = 0;
    cityList.append(city);
    city["cityName"] = "Hangzhou,CN";
    city["flag"] = 0;
    cityList.append(city);
    city["cityName"] = "Guangzhou,CN";
    city["flag"] = 0;
    cityList.append(city);
    _collectWidget = new CollectWidget(this,cityList,CELSIUS,KILOMETERSPERHOUR,MILLIMETERS);
    _collectWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());

    QLabel *testLabel = new QLabel("test");
    testLabel->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());
    _dailyWidget = new DailyWidget(this,10,"Shanghai,CN");
    _dailyWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());

    _mainPage = new MainPage(this,QString("Shanghai,CN"),CELSIUS,KILOMETERSPERHOUR,MILLIMETERS);
    _mainPage->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());

    _settingWidget = new SettingWidget(this);
    _settingWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());

    _hourlyWidget = new HourlyWidget(this,7,"Shanghai,CN");
    _hourlyWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());

    _contentWidget = new ContentWidget(this);
    _contentWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());

    _widgetList << _mainPage << _dailyWidget << _hourlyWidget << _collectWidget << _settingWidget;
    _contentWidget->setWidget(_widgetList);
//    //    _addLocationDialog = new AddLocationDialog(this);
//    //    _addLocationDialog->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());

    connect(_titleWidget,SIGNAL(prevTitleSignal()),_contentWidget,SLOT(prevWidget()));
    connect(_titleWidget,SIGNAL(nextTitleSignal()),_contentWidget,SLOT(nextWidget()));
    connect(_titleWidget,SIGNAL(firstTitleSignal()),_contentWidget,SLOT(firstWidget()));
    _addLocationDialog = new AddLocationDialog(this);
    _addLocationDialog->setGeometry(0,0,this->width(),this->height());
    _addLocationDialog->hide();

    connect(_settingWidget,SIGNAL(updateUnits(TEMPUNIT,WINDUNIT,PRECIPITATIONUNIT)),this,SLOT(onSetUnits(TEMPUNIT,WINDUNIT,PRECIPITATIONUNIT)));
    */
}

Weather::~Weather()
{
    writeSettings();
    delete ui;
}

void Weather::createMap()
{
    _gradientsMap.clear();
    _gradientsMap.insert(40,"#8c009c");
    _gradientsMap.insert(38,"#76007f");
    _gradientsMap.insert(36,"#65005f");
    _gradientsMap.insert(34,"#600043");
    _gradientsMap.insert(32,"#67002e");
    _gradientsMap.insert(30,"#790023");
    _gradientsMap.insert(28,"#92001d");
    _gradientsMap.insert(26,"#ac0019");
    _gradientsMap.insert(24,"#c30213");
    _gradientsMap.insert(22,"#d8070c");
    _gradientsMap.insert(20,"#e91109");
    _gradientsMap.insert(18,"#E11D07");
    _gradientsMap.insert(16,"#DD2B0C");
    _gradientsMap.insert(14,"#E04414");
    _gradientsMap.insert(12,"#E1581D");
    _gradientsMap.insert(10,"#E17126");
    _gradientsMap.insert(8,"#E18433");
    _gradientsMap.insert(6,"#E1983E");
    _gradientsMap.insert(4,"#E1A84C");
    _gradientsMap.insert(2,"#E1B75B");
    _gradientsMap.insert(0,"#E1C169");
    _gradientsMap.insert(-2,"#E1CB78");
    _gradientsMap.insert(-4,"#DFD78E");
    _gradientsMap.insert(-6,"#D4DFA6");
    _gradientsMap.insert(-8,"#B3D9A4");
    _gradientsMap.insert(-10,"#91D0A1");
    _gradientsMap.insert(-12,"#85e4bd");
    _gradientsMap.insert(-14,"#64d9c9");
    _gradientsMap.insert(-16,"#43c9d3");
    _gradientsMap.insert(-18,"#27b3d9");
    _gradientsMap.insert(-20,"#1497d7");
    _gradientsMap.insert(-22,"#0878cf");
    _gradientsMap.insert(-24,"#055ac3");
    _gradientsMap.insert(-26,"#0641b6");
    _gradientsMap.insert(-28,"#0b2ca8");
    _gradientsMap.insert(-30,"#191f9b");
    _gradientsMap.insert(-32,"#261b97");
    _gradientsMap.insert(-34,"#2b1b97");
    _gradientsMap.insert(-36,"#311c97");
    _gradientsMap.insert(-38,"#381d97");
}

void Weather::onSetUnits(TEMPUNIT tempUnit, WINDUNIT windUnit, PRECIPITATIONUNIT precipitationUnit)
{
    _tempUnit = tempUnit;
    _windUnit = windUnit;
    _precipitationUnit = precipitationUnit;
    _mainPage->setUnits(tempUnit,windUnit,precipitationUnit);
    _dailyWidget->setUnits(tempUnit,windUnit,precipitationUnit);
    _hourlyWidget->setUnits(tempUnit,windUnit,precipitationUnit);
    _collectWidget->setUnits(tempUnit,windUnit,precipitationUnit);
    _titleWidget->firstTitle();
}

void Weather::writeSettings()
{
    _settings.clear();
    _settings.setValue("city",_cityList);
    _settings.setValue("tempunit",_tempUnit);
    _settings.setValue("windunit",_windUnit);
    _settings.setValue("precipitationunit",_precipitationUnit);
}

void Weather::readSettings()
{
    bool ok;
    int index = 0;
    index = _settings.value("tempunit").toInt(&ok);
    if(ok)
        _tempUnit = TEMPUNIT(index);
    index = _settings.value("windunit").toInt(&ok);
    if(ok)
        _windUnit = WINDUNIT(index);
    index = _settings.value("precipitationunit").toInt(&ok);
    if(ok)
        _precipitationUnit = PRECIPITATIONUNIT(index);
    _cityList = _settings.value("city").toList();

    bool mainCityExist = false;
    foreach (QVariant item, _cityList) {
        QVariantMap city = item.toMap();
        index = city["flag"].toInt(&ok);
        if(index == 1 && ok)
        {
            mainCityExist = true;
            _mainPage = new MainPage(this,city["cityName"].toString(),_tempUnit,_windUnit,_precipitationUnit);
            _dailyWidget = new DailyWidget(this,7,city["cityName"].toString(),_tempUnit,_windUnit,_precipitationUnit);
            _hourlyWidget = new HourlyWidget(this,8,city["cityName"].toString(),_tempUnit,_windUnit,_precipitationUnit);
            _collectWidget = new CollectWidget(this,_cityList,_tempUnit,_windUnit,_precipitationUnit);
            _settingWidget = new SettingWidget(this,_tempUnit,_windUnit,_precipitationUnit);
            _contentWidget = new ContentWidget(this);
            _addLocationDialog = new AddLocationDialog(this,0);
            _addLocationDialog->setGeometry(0,0,this->width(),this->height());
            _addLocationDialog->hide();
            _loadingWidget = new LoadingWidget(this);
            _loadingWidget->setGeometry(0,0,this->width(),this->height());
            _loadingWidget->raise();
            _updateTimer = new QTimer(this);
            _updateTimer->setInterval(1000 * 60 * 30);
            _updateTimer->start();
            connect(_updateTimer,SIGNAL(timeout()),this,SLOT(onTimer()));
        }
    }

    if(!mainCityExist)
    {
        _mainPage = new MainPage(this,"",_tempUnit,_windUnit,_precipitationUnit);
        _dailyWidget = new DailyWidget(this,7,"",_tempUnit,_windUnit,_precipitationUnit);
        _hourlyWidget = new HourlyWidget(this,8,"",_tempUnit,_windUnit,_precipitationUnit);
        _collectWidget = new CollectWidget(this,_tempUnit,_windUnit,_precipitationUnit);
        _settingWidget = new SettingWidget(this,_tempUnit,_windUnit,_precipitationUnit);
        _contentWidget = new ContentWidget(this);
        _addLocationDialog = new AddLocationDialog(this);
        _addLocationDialog->setGeometry(0,0,this->width(),this->height());
        _addLocationDialog->raise();
        _loadingWidget = new LoadingWidget(this);
        _loadingWidget->setGeometry(0,0,this->width(),this->height());
        _loadingWidget->move(0,-_loadingWidget->height());
    }

    _mainPage->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());
    _dailyWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());
    _hourlyWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());
    _collectWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());
    _contentWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());
    _widgetList << _mainPage << _dailyWidget << _hourlyWidget << _collectWidget << _settingWidget;
    _contentWidget->setWidget(_widgetList);

//    if(_cityList.isEmpty())
//    {
//        _mainPage = new MainPage(this,"",_tempUnit,_windUnit,_precipitationUnit);
//        _dailyWidget = new DailyWidget(this,7,"",_tempUnit,_windUnit,_precipitationUnit);
//        _hourlyWidget = new HourlyWidget(this,8,"",_tempUnit,_windUnit,_precipitationUnit);
//        _collectWidget = new CollectWidget(this,_tempUnit,_windUnit,_precipitationUnit);
//        _settingWidget = new SettingWidget(this,_tempUnit,_windUnit,_precipitationUnit);
//        _contentWidget = new ContentWidget(this);
//        _mainPage->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());
//        _dailyWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());
//        _hourlyWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());
//        _collectWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());
//        _contentWidget->setGeometry(0,ui->frame->y() + ui->frame->height(),this->width(),this->height() - ui->frame->y() - ui->frame->height());
//        _widgetList << _mainPage << _dailyWidget << _hourlyWidget << _collectWidget << _settingWidget;
//        _contentWidget->setWidget(_widgetList);

//        _addLocationDialog = new AddLocationDialog(this);
//        _addLocationDialog->setGeometry(0,0,this->width(),this->height());
//        _addLocationDialog->show();
//    }
    connect(_titleWidget,SIGNAL(prevTitleSignal()),_contentWidget,SLOT(prevWidget()));
    connect(_titleWidget,SIGNAL(nextTitleSignal()),_contentWidget,SLOT(nextWidget()));
    connect(_titleWidget,SIGNAL(firstTitleSignal()),_contentWidget,SLOT(firstWidget()));
    connect(_settingWidget,SIGNAL(updateUnits(TEMPUNIT,WINDUNIT,PRECIPITATIONUNIT)),this,SLOT(onSetUnits(TEMPUNIT,WINDUNIT,PRECIPITATIONUNIT)));
    connect(_addLocationDialog,SIGNAL(addCitySignal(QString,int)),this,SLOT(addCity(QString,int)));
    connect(_collectWidget,SIGNAL(addCitySignal(int)),this,SLOT(receiveAddCitySignal(int)));
    connect(_collectWidget,SIGNAL(setMainPageSignal(QString)),this,SLOT(setMainPage(QString)));
    connect(_collectWidget,SIGNAL(viewDetailSingal(QString)),this,SLOT(viewDetail(QString)));
    connect(_mainPage,SIGNAL(backgroundSignal(int,TEMPUNIT)),this,SLOT(changeBackground(int,TEMPUNIT)));
    connect(_collectWidget,SIGNAL(deleteCitySignal(QString)),this,SLOT(deleteCity(QString)));
    connect(_mainPage,SIGNAL(hideLoadingWidget()),this,SLOT(hideLoadingWidget()));
    connect(_collectWidget,SIGNAL(hideLoadingWidget()),_loadingWidget,SLOT(onHide()));
    connect(_dailyWidget,SIGNAL(hideLoadingWidget()),this,SLOT(hideLoadingWidget()));
    connect(_hourlyWidget,SIGNAL(hideLoadingWidget()),this,SLOT(hideLoadingWidget()));
}


void Weather::addCity(QString cityName, int flag)
{

    _addLocationDialog->move(0,-_addLocationDialog->height());
    _loadingWidget->move(0,0);
    _loadingWidget->raise();
    QVariantMap city;
    city["cityName"] = cityName;
    city["flag"] = flag;
    _cityList.append(city);
    if(flag == 1)
    {
        _mainPage->refreshCity(cityName);
        _dailyWidget->refreshCity(cityName);
        _hourlyWidget->refreshCity(cityName);
        _collectWidget->addCity(city);
        _titleWidget->firstTitle();
        _updateTimer = new QTimer(this);
        _updateTimer->setInterval(1000 * 60 * 30);
        connect(_updateTimer,SIGNAL(timeout()),this,SLOT(onTimer()));
        _updateTimer->start();
    }
    else
    {
        _collectWidget->addCity(city);
    }
}


void Weather::viewDetail(QString cityName)
{
    _mainPage->refreshCity(cityName);
    _hourlyWidget->refreshCity(cityName);
    _dailyWidget->refreshCity(cityName);
    _titleWidget->firstTitle();
}

void Weather::setMainPage(QString cityName)
{
    _mainPage->refreshCity(cityName);
    _hourlyWidget->refreshCity(cityName);
    _dailyWidget->refreshCity(cityName);
    _titleWidget->firstTitle();
    bool ok;
    for(int index = 0;index < _cityList.size();index++)
    {
        QVariantMap city = _cityList[index].toMap();
        if(city["cityName"].toString() != cityName && city["flag"].toInt(&ok) == 1)
        {
            city["flag"] = 0;
            _cityList[index] = city;
        }
        else if(city["cityName"].toString() == cityName && city["flag"].toInt(&ok) == 0)
        {
            city["flag"] = 1;
            _cityList[index] = city;
        }
    }
}

void Weather::receiveAddCitySignal(int flag)
{
    _addLocationDialog->move(0,0);
    _addLocationDialog->show();
}

void Weather::changeBackground(int temp, TEMPUNIT tempUnit)
{
    int celsius;
    if(tempUnit == FAHRENHEIT)
        celsius = BaseDetail::FahrenheitToCelius(temp);
    else
        celsius = temp;
    celsius -= 8;
    // stay in range
    if(celsius < -30) celsius = -30;
    else if(celsius > 40) celsius = 40;
    // get anchor value
    celsius = (celsius % 2 == 1 || celsius % 2 == -1) ? celsius +1 : celsius;
    QPalette myPalette = this->palette();
    QLinearGradient linearGradient(0,0,this->width(),this->height());
    linearGradient.setColorAt(0.0,QColor(_gradientsMap[celsius]));
    linearGradient.setColorAt(1.0,QColor(_gradientsMap[celsius - 8]));
    QBrush brush(linearGradient);
    myPalette.setBrush(QPalette::Window,brush);
    this->setPalette(myPalette);
}


void Weather::deleteCity(QString cityName)
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
    }
}


void Weather::hideLoadingWidget()
{
    _receiveCount++;
    qDebug() << _receiveCount;
    if(_receiveCount == 3)
    {
        _receiveCount = 0;
        _loadingWidget->move(0,_loadingWidget->height());
    }
}

void Weather::onTimer()
{
    qDebug() << "ontimer";
    _mainPage->updateDetail();
    _hourlyWidget->updateDetail();
    _dailyWidget->updateDetail();
    _collectWidget->updateDetail();
    _titleWidget->firstTitle();
}
