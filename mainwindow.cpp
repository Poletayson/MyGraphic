#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfile.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer ();

    myGraphic = new Graphic ();
    myGraphic2 = new Graphic ();
    histogram = new Graphic ();
    histogram->setAlignment(Qt::AlignCenter);        //выравнивание по центру
    histogram->setMaximumWidth(260);
    histogram->setMaximumHeight(150);
    //histogram->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //histogram->setsi
    ui->horizontalLayout->addWidget(myGraphic);
    ui->horizontalLayout->addWidget(myGraphic2);
    ui->verticalLayout_4->addWidget(histogram);
    buttGr = new QButtonGroup ();
    buttGr->addButton(ui->radioButton, 0);
    buttGr->addButton(ui->radioButton_2, 1);
    buttGr->addButton(ui->radioButton_3, 2);
    buttGr->addButton(ui->radioButton_4, 3);
    buttGr->addButton(ui->radioButton_5, 4);
    buttNum = 0;
    random = new QRandomGenerator ();

   connect(ui->open, SIGNAL(triggered(bool)), this, SLOT(getFile()));
   connect(ui->ButtonNeg, SIGNAL(clicked()), this, SLOT(Negative ()));
   connect(ui->ButtonGray, SIGNAL(clicked()), this, SLOT(Gray ()));
   connect(ui->ButtonBinary, SIGNAL(clicked()), this, SLOT(Binarization ()));
   connect(ui->ButtonRepair, SIGNAL(clicked()), this, SLOT(Repair ()));
   //connect(ui->ButtonHistBr, SIGNAL(clicked()), this, SLOT(makeHist ()));
   connect(ui->horizontalSlider, SIGNAL(sliderReleased()), this, SLOT(sliderOb())); //valueChanged(int)
   connect(this->buttGr, SIGNAL(buttonClicked(int)), this, SLOT(buttonChange ()));
   connect(ui->ButtonNoise, SIGNAL(clicked()), this, SLOT(setNoise ()));
   connect(ui->ButtonMedian, SIGNAL(clicked()), this, SLOT(Median ()));
   connect(ui->ButtonGauss, SIGNAL(clicked()), this, SLOT(Gauss ()));
   connect(ui->ButtonRezk, SIGNAL(clicked()), this, SLOT(Rezk ()));
   connect(ui->ButtonAquarel, SIGNAL(clicked()), this, SLOT(Aquarel ()));
   connect(ui->ButtonMy, SIGNAL(clicked()), this, SLOT(MyFilter ()));
//    ui->verticalLayout->addWidget(myGraphic);
//    ui->verticalLayout_4->addWidget(myGraphic2);

    //myGraphic->Drawing();
}



MainWindow::~MainWindow()
{

    delete ui;
}



QString MainWindow::getFile()             //выбираем список файлов
{
    #include <QDir>
    QString path = QApplication::applicationDirPath();  //QDir::currentPath();      //текущая директория
    if (QDir(path + "/Input").exists())
         path = path + "/Input";
    else
        QDir(path).mkdir("Input");
    QString fileName = QFileDialog::getOpenFileName(Q_NULLPTR, "Выберите входной файл", path);
    //qDebug() << "Взято " << stl.count() << " файлов";
    //получили файл
    myGraphic->GetFileImage(fileName);      //получаем изображение
    setStart ();
/////
//    buttGr->button(0)->setChecked(true);
//    buttonChange ();
////
    //ui->radioButton->setChecked(true);
    //ui->horizontalSlider->setValue(0);
    return fileName;

}

void MainWindow::Repair ()      //восстановление
{
//    if (myGraphic->image != Q_NULLPTR)
//        delete myGraphic->image;
//    if (myGraphic->reserve != Q_NULLPTR)
//        delete myGraphic->reserve;

    if (myGraphic2->image != Q_NULLPTR)
        delete myGraphic2->image;
    myGraphic2->image = myGraphic2->myScene->addPixmap(myGraphic->image->pixmap());


    if (myGraphic2->reserve != Q_NULLPTR)
        delete myGraphic2->reserve;
    myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic->image->pixmap());
    makeHist ();
}

void MainWindow::Negative ()
{
    if (myGraphic2->image != Q_NULLPTR)
    {
        if (myGraphic2->image != Q_NULLPTR)
            delete myGraphic2->image;
        myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->getNegative());
        if (myGraphic2->reserve  != Q_NULLPTR)
            delete myGraphic2->reserve;
        myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic2->image->pixmap());
        makeHist ();
    }
}

void MainWindow::Gray ()
{
    if (myGraphic2->image  != Q_NULLPTR)
    {
        if (myGraphic2->image)
            delete myGraphic2->image;
        myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->getGray());
        if (myGraphic2->reserve != nullptr)
            delete myGraphic2->reserve;
        myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic2->image->pixmap());
        makeHist ();
    }
}

void MainWindow::Brightness()
{
    if (myGraphic2->reserve != nullptr)
    {
        int brPl = ui->horizontalSlider->value();
        if (myGraphic2->image != nullptr)
            delete myGraphic2->image;
        myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->Brightness(brPl));
    }
}

void MainWindow::Contrast()
{
    if (myGraphic2->reserve != nullptr)
    {
        int brPl = ui->horizontalSlider->value();
        if (myGraphic2->image != nullptr)
            delete myGraphic2->image;
        myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->Brightness(brPl));
    }
}
void MainWindow::Balance()
{
    if (myGraphic2->reserve != nullptr)
    {
        int brPl = ui->horizontalSlider->value();
        if (myGraphic2->image != nullptr)
            delete myGraphic2->image;
        myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->Brightness(brPl));
    }
}

void MainWindow::setStart ()
{
    if (myGraphic2->image != nullptr)
        delete myGraphic2->image;
    myGraphic2->image = myGraphic2->myScene->addPixmap(myGraphic->image->pixmap());
    myGraphic2->myScene->setSceneRect(0, 0, myGraphic2->image->pixmap().width(), myGraphic2->image->pixmap().height());
    if (myGraphic2->reserve != nullptr)
        delete myGraphic2->reserve;
    myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic2->image->pixmap());
    makeHist ();
}

void MainWindow::buttonChange ()            //произошло нажатие на радиокнопку
{
    buttNum = buttGr->checkedId();
    delete myGraphic->reserve;      //удаляем старый резерв и делаем текущее изображение резервным
    myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic2->image->pixmap());//myGraphic2->myScene->addPixmap(myGraphic->image->pixmap());//  new QPixmap (myGraphic2->image->pixmap());
    switch (buttNum) {
        case 0:
        {
            ui->horizontalSlider->setMinimum(-255);     //устанавливаем минимум и максимум
            ui->horizontalSlider->setMaximum(255);
            ui->horizontalSlider->setValue(0);
            break;
        }
        case 1:
        {
            ui->horizontalSlider->setMinimum(0);     //устанавливаем минимум и максимум
            ui->horizontalSlider->setMaximum(200);
            ui->horizontalSlider->setValue(50.0);
            break;
        }
        case 2:
        {
            ui->horizontalSlider->setMinimum(0);     //устанавливаем минимум и максимум
            ui->horizontalSlider->setMaximum(255);
            ui->horizontalSlider->setValue(127);
            break;
        }
        case 3:
        {
            ui->horizontalSlider->setMinimum(0);     //устанавливаем минимум и максимум
            ui->horizontalSlider->setMaximum(5);
            ui->horizontalSlider->setValue(3);
            break;
        }
        case 4:
        {
            ui->horizontalSlider->setMinimum(1);     //устанавливаем минимум и максимум
            ui->horizontalSlider->setMaximum(10);
            ui->horizontalSlider->setValue(2);
            break;
        }
    }
}

void MainWindow::Binarization ()
{
    if (myGraphic2->reserve != nullptr)
    {
        int brPl = ui->horizontalSlider->value();
        if (myGraphic2->image != nullptr)
            delete myGraphic2->image;
        myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->Binarization(brPl));
        makeHist ();
    }
}




void MainWindow::sliderOb ()
{
    if (myGraphic2->reserve != nullptr)
    {
        int brPl = ui->horizontalSlider->value();
        switch (buttNum)
        {
            case 0:
            {
                if (myGraphic2->image != nullptr)
                    delete myGraphic2->image;
                myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->Brightness(brPl));      //яркость
                makeHist ();
                break;
            }
            case 1:
            {
                if (myGraphic2->image != nullptr)
                    delete myGraphic2->image;
                myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->Contrast((float)brPl/50.0)); //контраст
                makeHist ();
                break;
            }
        }
    }
}

void MainWindow::makeHist ()
{
    int brigtLevels [256];
    for (int i = 0; i < 256; i++) {
        brigtLevels [i] = 0;
    }
    QColor* col;
    qreal bright;           //яркость
    QImage *newImage = new QImage (myGraphic2->image->pixmap().toImage());
    for (int i = 0; i < myGraphic2->image->pixmap().width(); i++)
        for (int j = 0; j < myGraphic2->image->pixmap().height(); j++)
        {
            col = new QColor (newImage->pixelColor(i, j));
            bright = 0.289*col->red() + 0.5556*col->green() + 0.112*col->blue();    //яркость
            brigtLevels[(int)bright]++;     //добавляем к яркости
            delete col;
        }
    delete newImage;
//получили массив яркостей
    QPen p (Qt::black);
    int max = brigtLevels[0];
    for (int i = 0; i < 256; i++) {
        if (brigtLevels[i] > max)
            max = brigtLevels[i];
    }
    //int sch = histogram->scene()->height();
//    try {
//        //delete histogram->myScene;
//    } catch (std::exception& ex)
//    {
//        //ex.
//    }

    //histogram->myScene = new QGraphicsScene ();
    histogram->myScene->setSceneRect(0, 0, 256, histogram->height() - 3);   //размер сцены под картинку
    histogram->myScene->clear();
    qreal m = histogram->myScene->height()/max;
    for (int i = 0; i < 256; i++) {
        histogram->scene()->addLine(i, histogram->height() - m*brigtLevels[i], i, histogram->height(), p);
    }
}

void MainWindow::setNoise ()
{
    if (myGraphic2->image != Q_NULLPTR)
    {
        int noisePers = ui->horizontalSlider->value();      //процент шума
        int r, g, b;
        QImage *newImage = new QImage (myGraphic2->image->pixmap().toImage());
        //QColor* col;
        QRgb c;
        for (int i = 0; i < myGraphic2->image->pixmap().width(); i++)
            for (int j = 0; j < myGraphic2->image->pixmap().height(); j++)
            {
                if (random->generate() % 100 < noisePers)
                {
                    r = random->generate() % 256;
                    g = random->generate() % 256;
                    b = random->generate() % 256;
                    c = qRgb(r, g, b);
//                    col = new QColor ();
//                    col->setBlue(b);
//                    col->setGreen(g);
//                    col->setRed(r);
                    newImage->setPixel (i, j, c); //Color(i, j, *col);
                    //delete col;
                }
            }
        delete myGraphic2->image;
        myGraphic2->image = myGraphic2->myScene->addPixmap (*new QPixmap (QPixmap::fromImage(*newImage)));
        delete myGraphic2->reserve;
        myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic2->image->pixmap());
        delete newImage;

    }
}
void MainWindow::Median()
{
    if (myGraphic2->reserve != nullptr)
    {
        if (myGraphic2->image != nullptr)
            delete myGraphic2->image;
        myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->Median());
        delete myGraphic->reserve;      //удаляем старый резерв и делаем текущее изображение резервным
        myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic2->image->pixmap());
        makeHist ();
    }
}

void MainWindow::Gauss()
{
    if (myGraphic2->reserve != nullptr)
    {
        if (myGraphic2->image != nullptr)
            delete myGraphic2->image;
        myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->Gauss());
        delete myGraphic->reserve;      //удаляем старый резерв и делаем текущее изображение резервным
        myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic2->image->pixmap());
        makeHist ();
    }
}

void MainWindow::Rezk()
{
    if (myGraphic2->reserve != nullptr)
    {
        if (myGraphic2->image != nullptr)
            delete myGraphic2->image;
        myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->Rezk());
        delete myGraphic->reserve;      //удаляем старый резерв и делаем текущее изображение резервным
        myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic2->image->pixmap());
        makeHist ();
    }
}

void MainWindow::MyFilter()
{
    if (myGraphic2->reserve != nullptr)
    {
        if (myGraphic2->image != nullptr)
            delete myGraphic2->image;
        myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->MyFilter(ui->horizontalSlider->value()));
        delete myGraphic->reserve;      //удаляем старый резерв и делаем текущее изображение резервным
        myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic2->image->pixmap());
        makeHist ();
    }
}

void MainWindow::Aquarel()
{
    if (myGraphic2->reserve != nullptr)
    {
        if (myGraphic2->image != nullptr)
            delete myGraphic2->image;
        //myGraphic2->SIGMA = 5;
        myGraphic2->reserve = myGraphic2->myScene->addPixmap(*myGraphic2->Median());   //размываем
        myGraphic2->reserve = myGraphic2->myScene->addPixmap(*myGraphic2->Median());   //размываем
        myGraphic2->reserve = myGraphic2->myScene->addPixmap(*myGraphic2->Median());   //размываем
        //myGraphic2->reserve = myGraphic2->myScene->addPixmap(*myGraphic2->Gauss());   //размываем

    myGraphic2->image = myGraphic2->myScene->addPixmap(*myGraphic2->Rezk());   //размываем
    delete myGraphic->reserve;      //удаляем старый резерв и делаем текущее изображение резервным
    myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic2->image->pixmap());
        makeHist ();
    }
}

