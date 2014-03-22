#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QtCore/QTextStream>


#include <QMessageBox>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<int> MainWindow::read(QString path){

    QByteArray ba = path.toLocal8Bit();
    const char * p = ba.data();

    // read an image and convert image to grayscale
    IplImage * image = cvLoadImage(p, CV_LOAD_IMAGE_GRAYSCALE);


    // image info
    int height = image->height;
    int width = image->width;
    int step = image->widthStep;
    uchar * data = (uchar *)image->imageData;

    //tacni odgovori
    QString tacni = ui->lineEdit_2->text();

      QVector<int> vektor;

    if(tacni != "" && tacni.size()==9){



    //citanje markera
    QList<int> redovi;
    QList<int> kolone;

    for(int i=0;i<height-1;i++) {
         for(int j=0;j<width-1;j++) {
            if(data[i*step+j]<10 && kolone.size()<4){
                kolone.push_back(j);
            }
        }
    }
    kolone.push_back(304);

    for(int j=0;j<width-1;j++) {
         for(int i=0;i<height-1;i++) {
            if(data[i*step+j]<10 && redovi.size()<12){
                redovi.push_back(i);
            }
        }
    }


    //citanje testa

    QString sifra="Šifra kandidata: ";
    QString odgovori="Odgovori kandidata: ";
    QString o="";

    int brojac=0;
    QString str ="";
    for(int i=0; i<redovi.size(); i++){
        int j;
        for(  j=0; j<kolone.size(); j++){
            //provjerava 4 pixela u krugu
             if(data[redovi.at(i)*step+kolone.at(j)]<10 && data[redovi.at(i)*step+kolone.at(j)-1]<10 && data[redovi.at(i)*step+kolone.at(j)+1]<10 && data[(redovi.at(i)-1)*step+kolone.at(j)-1]<10){
                if(i<3){
                    if(j==0) { if(i==2)sifra.push_back("1"); else sifra.push_back("A");}
                     if(j==1) { if(i==2)sifra.push_back("2"); else sifra.push_back("B");}
                      if(j==2) { if(i==2)sifra.push_back("3"); else sifra.push_back("C");}
                       if(j==3) { if(i==2)sifra.push_back("4"); else sifra.push_back("D");}
                        if(j==4) { if(i==2)sifra.push_back("5"); else sifra.push_back("E");}
                }
                else{

                     if(j==1) { brojac++; str="A";}
                      if(j==2) {brojac++;str="B";}
                       if(j==3) {brojac++;str="C";}
                        if(j==4) {brojac++;str="D";}


                }
             }

        }
        if(i>2){
            if(brojac!=1)  {o.push_back("N");}
            else if(str=="A")  {o.push_back("A");}
            else if(str=="B")  {o.push_back("B");}
            else if(str=="C")  {o.push_back("C");}
            else if(str=="D")  {o.push_back("D");}
            brojac=0;
            str="";
        }


    }

    odgovori.push_back(o);
    int bodovi=0;

    for(int i=0; i<tacni.size(); i++){
        if(o.at(i)==tacni.at(i)) {bodovi++; vektor.push_back(1);}
        else {vektor.push_back(0);}

    }
    QString b = QString::number(bodovi);
    QString bodici = "UKUPNO BODOVA: ";
    bodici.push_back(b);

    ui->textEdit->append("________________");
    ui->textEdit->append("");
    ui->textEdit->append(sifra);
    ui->textEdit->append(odgovori);
    ui->textEdit->append(bodici);

}
    else{
        QMessageBox * msgBox = new QMessageBox();
        msgBox->setText("Morate unijeti tačne odgovore!");
        msgBox->exec();

    }
    return vektor;

}

void MainWindow::on_pushButton_2_clicked()
{
    //tacni odgovori

    QString tacni = ui->lineEdit_2->text();

    if(tacni.size()!=9){
        QMessageBox * msgBox = new QMessageBox();
        msgBox->setText("Morate unijeti tačne odgovore!");
        msgBox->exec();
    }
    else{
        QString tacniOdgovori = "Tačni odgovori su: ";
        tacniOdgovori.push_back(tacni);
        ui->textEdit->append(tacniOdgovori);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    //choose file
    QString fileName = QFileDialog::getOpenFileName(this,tr("Odaberite test"), "", tr("Slike (*.jpg)"));
    ui->lineEdit->setText(fileName);

    //show image on form
    QPixmap image(fileName);
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(image);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    if(fileName != "") ui->textEdit->append("Test uspješno učitan.");
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit->text() != ""){
        read( ui->lineEdit->text());
    }
    else{
        QMessageBox * msgBox = new QMessageBox();
        msgBox->setText("Morate odabrati test!");
        msgBox->exec();
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    close();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionBrightness_triggered()
{

}

void MainWindow::on_menuGrupa_Testova_2_triggered()
{
    close();
}

void MainWindow::on_actionNovi_Test_triggered()
{
    ui->pushButton->show();
    ui->pushButton_6->show();
    ui->groupBox->show();
    ui->label->show();
    ui->lineEdit_3->show();

    ui->textEdit->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    QGraphicsScene * scene = new QGraphicsScene();
        ui->graphicsView->setScene(scene);
    ui->lineEdit_3->clear();

}

void MainWindow::on_actionGrupa_Testova_triggered()
{

    QString tacni = ui->lineEdit_2->text();
    if(tacni != "" && tacni.size()==9){
    //grupa testova
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(dir != ""){
        ui->pushButton->hide();
        ui->pushButton_6->hide();
        ui->groupBox->hide();
        ui->label->hide();
        ui->lineEdit_3->hide();

        QString folder = dir;
        QDir pathd(dir);
        QStringList files = pathd.entryList(QDir::Files);
        QVector< QVector<int> > vektor;

        for(int i=0; i<files.size();i++){

            //read file path
            folder.push_back("/");
            folder.push_back(files.at(i));
            vektor.push_back(read(folder));
            folder=dir;
        }

        QVector <int> bars;

        for(int i=0; i<9; i++){
            int brojac=0;
            for(int j=0; j<vektor.size(); j++){
                brojac=brojac+vektor.at(j).at(i);
            }
            bars.push_back(brojac);
        }


        prikazi(bars);
    }
    }
    else{
        QMessageBox * msgBox = new QMessageBox();
        msgBox->setText("Morate unijeti tačne odgovore!");
        msgBox->exec();
    }
}

void MainWindow::on_pushButton_5_clicked()
{    QString outputFilename = "C:/Users/Nusreta/Desktop/Rezultati.txt";
     QFile outputFile(outputFilename);
      outputFile.open(QIODevice::Append);

     /* Point a QTextStream object at the file */
     QTextStream outStream(&outputFile);

     /* Write the line to the file */
     outStream << ui->textEdit->toPlainText();


     outputFile.close();
      QMessageBox * msgBox = new QMessageBox();
      msgBox->setText("Rezultati uspješno sačuvani u datoteci Rezultati.txt!");
      msgBox->exec();
}

void MainWindow::on_actionSave_triggered()
{
    QString outputFilename = "C:/Users/Nusreta/Desktop/Results.txt";
        QFile outputFile(outputFilename);
         outputFile.open(QIODevice::Append);

        /* Point a QTextStream object at the file */
        QTextStream outStream(&outputFile);

        /* Write the line to the file */
        outStream << ui->textEdit->toPlainText();


        outputFile.close();
        QMessageBox * msgBox = new QMessageBox();
        msgBox->setText("Rezultati uspješno sačuvani u datoteci Rezultati.txt!");
        msgBox->exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    QString t = ui->lineEdit_3->text();
    if(t==""){
        QMessageBox * msgBox = new QMessageBox();
        msgBox->setText("Unesite broj stepeni za rotaciju");
        msgBox->exec();
    }
    else{
        double stepen = t.toDouble();
     rotiraj(stepen);
    }
}
void MainWindow::prikazi(QVector<int> bars){
    QGraphicsScene * scene = new QGraphicsScene();
        ui->graphicsView->setScene(scene);

        scene->addLine(0,0,0,-200);
         scene->addLine(0,0,300,0);

        for(int i = 0; i< bars.size(); i++){
           scene->addRect(15+30*i,-(20*bars.at(i)),20,20*bars.at(i));

           QGraphicsTextItem * pitanja = new QGraphicsTextItem(QString::number(i+1)+".");
           pitanja->setPos((20+30*i),5);
           scene->addItem(pitanja);

           QGraphicsTextItem * broj = new QGraphicsTextItem(QString::number(bars.at(i)));
           broj->setPos(-20,-(20*bars.at(i)+10));
           scene->addItem(broj);
           scene->addLine(-2,-(20*bars.at(i)), 2,-(20*bars.at(i)));

        }

        QGraphicsTextItem * y = new QGraphicsTextItem("Broj kandidata koji su tačno odgovorili na pitanje");
        y->setPos(20,-200);
        scene->addItem(y);
        QGraphicsTextItem * x = new QGraphicsTextItem("Redni broj pitanja");
        x->setPos(200,40);
        scene->addItem(x);

        // Show the view
        ui->graphicsView->show();
}

void MainWindow::on_actionCrop_triggered()
{
    QString fileName = ui->lineEdit->text();

    if(fileName != ""){
        QPixmap image(fileName);
        QMatrix rm;
        rm.rotate(90);
        image = image.transformed(rm);
        QGraphicsScene* scene = new QGraphicsScene();
        scene->addPixmap(image);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
    }



}

void MainWindow::rotiraj(double stepen){
    QString fileName = ui->lineEdit->text();

    if(fileName == ""){

            QMessageBox * msgBox = new QMessageBox();
            msgBox->setText("Unesite putanju do testa!");
            msgBox->exec();
    }
    else{
        QPixmap image(fileName);
        QMatrix rm;
        rm.rotate(stepen);
        image = image.transformed(rm);
        QGraphicsScene* scene = new QGraphicsScene();
        scene->addPixmap(image);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();


    }
}

void MainWindow::on_pushButton_7_clicked()
{

}

void MainWindow::on_actionRotiraj_Lijevo_triggered()
{
    QString fileName = ui->lineEdit->text();

    if(fileName != ""){
        QPixmap image(fileName);
        QMatrix rm;
        rm.rotate(-90);
        image = image.transformed(rm);
        QGraphicsScene* scene = new QGraphicsScene();
        scene->addPixmap(image);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
    }

}

void MainWindow::on_actionVerzija_triggered()
{
    QMessageBox * msgBox = new QMessageBox();
    msgBox->setText("eIspit verzija 2.1.1");
    msgBox->exec();

}

void MainWindow::on_actionUputstvo_triggered()
{
    QGraphicsScene * scene = new QGraphicsScene();
        ui->graphicsView->setScene(scene);

        QGraphicsTextItem * upute = new QGraphicsTextItem("UPUTSTVO");
        upute->setPos(0,0);
        scene->addItem(upute);

        QGraphicsTextItem * upute1 = new QGraphicsTextItem("1. Namjena aplikacije i osnovne funkcije:");
        upute1->setPos(20,20);
        scene->addItem(upute1);

        QGraphicsTextItem * upute11 = new QGraphicsTextItem("Aplikacija služi za elektronsko pregledanje ispita. Bazira se na Optical Mark Recognition.");
        upute11->setPos(40,40);
        scene->addItem(upute11);

        ui->graphicsView->show();
}
