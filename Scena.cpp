#include "Scena.h"


Scena::Scena(QObject *parent) : QGraphicsScene(parent)
{


    QGraphicsPixmapItem *pix = new QGraphicsPixmapItem(QPixmap(":/zdjecia/tlo.png"));
    this->addItem(pix);
    pix->setScale(2.3);
    pix->setPos((QPointF(0,0) - QPointF(pix->boundingRect().width()/2,
                                      pix->boundingRect().height()/2)));

    /*
    QGraphicsPixmapItem *rd1 = new QGraphicsPixmapItem(QPixmap(":/zdjecia/reddark.png"));
    this->addItem(rd1);
    rd1->setScale(0.15);
    rd1->setPos(QPointF(300,100));

    QGraphicsPixmapItem *rd2 = new QGraphicsPixmapItem(QPixmap(":/zdjecia/reddark.png"));
    this->addItem(rd2);
    rd2->setScale(0.15);
    rd2->setPos(QPointF(400,100));

    QGraphicsPixmapItem *gd1 = new QGraphicsPixmapItem(QPixmap(":/zdjecia/greendark.png"));
    this->addItem(gd1);
    gd1->setScale(0.15);
    gd1->setPos(QPointF(500,100));
    */



    this->setSceneRect(0,0,1400,830);
    start = new QPushButton();
    start->setGeometry(1050,520,200,100);
    start->setText("Start");
    this->addWidget(start);

    QStringList naglowki;
    naglowki<< "Kierowca" << "Okrazenie" <<"Postep okrazenia";
    tabela = new QTableWidget();
    tabela->setColumnCount(3);
    tabela->setHorizontalHeaderLabels(naglowki);
    tabela->resizeRowsToContents();
    tabela->resizeColumnsToContents();
    tabela->move(1000,200);
    tabela->setSelectionMode(QAbstractItemView::SingleSelection);
    tabela->setFixedSize(305, 188);
    tabela->setVisible(false);
    this->addWidget(tabela);

    label = new QLabel;
    label->setVisible(false);
    label->move(1050,80);
    label->setFixedSize(200,100);
    label->setAlignment( Qt::AlignCenter);
    label->setStyleSheet(" background-color: rgb(255,255, 255);");
    QFont f("Arial",40);
    label->setFont(f);
    this->addWidget(label);

    QPixmap pixmap("://zdjecia/chessboard.png");
    pixmap =pixmap.scaled(QSize(200,100));
    item = new QGraphicsPixmapItem(pixmap);
    this->addItem(item);
    item->setVisible(false);
    item->setPos(QPoint(1050,80));
    //pix->setTransformOriginPoint(10,7);


}

void Scena::dodajtor(Tor *tor)
{
    torgraf= new Torgraf(tor);
    torgraf->rysujtor(this);
}


void Scena::dodajauto(Auto *car, QString sc, float kierunek)
{
    this->car=car;
    autograf = new Autograf(car,sc,kierunek);
    autograf->dodajauto(this);
    Autagraf.push_back(autograf);
}

void Scena::usunautograf(int i)
{
    delete Autagraf[i];
    Autagraf.erase(Autagraf.begin()+i);
}

void Scena::inicjalizacjatabeli(int t)
{
   tabela->setRowCount(t);

}
void Scena::ustawpozycje(int t, std::string  kierowca, int okrazenie, bool czyukonczyl, bool czypopsuty, int postep)
{
    QString q2;
    QString q3;
    QString q=QString::fromStdString(kierowca);

    if(!czypopsuty&&!czyukonczyl)
    {
        q2=QString::fromStdString(std::to_string(okrazenie));
        q3=QString::fromStdString(std::to_string(postep));
    }
    else if(czypopsuty&&!czyukonczyl)
    {
        q2="DSQ";
        q3="DSQ";
    }
    else if(!czypopsuty&&czyukonczyl)
    {
        q2="Ukonczyl";
        q3="Ukonczyl";

    }
    tabela->setItem(t,0,new QTableWidgetItem(q));
    tabela->setItem(t,1,new QTableWidgetItem(q2));
    tabela->setItem(t,2,new QTableWidgetItem(q3));

}

void Scena::wlacztablicewynikow(float rozmiartab)
{
    tabela->setVisible(true);
    tabela->setFixedHeight(rozmiartab*45);
    label->setVisible(true);
    start->setVisible(false);
}

void Scena::progresokrazen(int t1, int t2, bool czykoniec)
{
    if(!czykoniec)
    {
        std::string Q=std::to_string(t1);
        std::string Q2=std::to_string(t2);
        Q = Q + " / " + Q2;
        QString q=QString::fromStdString(Q);
        label->setText(q);
    }
    else
    {
        label->setVisible(false);
        item->setVisible(true);

    }
}

std::vector<Autograf *> Scena::getvectorautagraf() const
{
    return Autagraf;
}

Autograf *Scena::getautograf(int i) const
{
    return Autagraf[i];
}

QPushButton *Scena::getstartbutton() const
{
    return start;
}






