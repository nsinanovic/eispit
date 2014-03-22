#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionExit_triggered();

    void on_actionNew_triggered();

    void on_actionBrightness_triggered();

    void on_menuGrupa_Testova_2_triggered();

    void on_actionNovi_Test_triggered();

    void on_actionGrupa_Testova_triggered();

    void on_pushButton_5_clicked();

    void on_actionSave_triggered();

    void on_pushButton_6_clicked();

    void on_actionCrop_triggered();

    void on_pushButton_7_clicked();

    void on_actionRotiraj_Lijevo_triggered();

    void on_actionVerzija_triggered();

    void on_actionUputstvo_triggered();

public slots:
    QVector<int> read(QString path);
    void prikazi(QVector<int> bars);
    void rotiraj(double stepen);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
