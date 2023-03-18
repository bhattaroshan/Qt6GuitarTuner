#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "vumeter.h"

struct GuitarNotes{
    QString noteName;
    float frequency;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void updatePercentage();

private:
    Ui::MainWindow *ui;
    VuMeter *m_vuMeter;
    int m_percentage = 0;
    int m_noteCounter = 0;
    QLabel *m_freq;
    int m_frequencyValue = 0;
    QVector<GuitarNotes> m_Notes;
};
#endif // MAINWINDOW_H
