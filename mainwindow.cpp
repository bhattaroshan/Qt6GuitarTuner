#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<portaudio.h>
#include <QTimer>
#include <QThread>
#include <algorithm>
#include <complex>

using namespace std;

void fft(QVector<complex<qreal>> &x){
    int N = x.size();
    if(N<=1) return;

    QVector<complex<qreal>> even(N/2),odd(N/2);

    for(int i=0;i<N/2;++i){
        even[i] = x[i*2];
        odd[i] = x[i*2+1];
    }

    fft(even);
    fft(odd);

    for(int k=0;k<N/2;++k){
        complex<qreal> w = {cos(2.0*M_PI*k/N),-sin(2.0*M_PI*k/N)};
        w = w*odd[k];
        x[k] = even[k]+w;
        x[k+N/2] = even[k]-w;
    }

    even.clear();
    odd.clear();
}


int audioCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData){
    float *in = (float*)inputBuffer;
    QVector<complex<qreal>> out(framesPerBuffer);

    int* freq = (int*)userData;

    for(int i=0;i<framesPerBuffer;++i){
        out[i]={in[i],0};
    }

    fft(out);

    float m_max = 0;
    float m_dF = 0;
    for(int i=0;i<1024;++i){
       float mag = qSqrt(out[i].real()*out[i].real()+out[i].imag()*out[i].imag());
       if(mag>m_max) {
           m_max = mag;
           m_dF = i;
       }
    }

    *freq = (m_dF*8000)/1024;

    return paContinue;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Guitar Tuner");
    setFixedSize(400,600);

    m_vuMeter = new VuMeter(this->width(),this->height(),this);
    QTimer *timer = new QTimer();
    timer->start(100);

    connect(timer,SIGNAL(timeout()),this,SLOT(updatePercentage()));

    m_Notes = {
        {"E4",329.63},
        {"B3",246.94},
        {"G3",196.00},
        {"D3",146.83},
        {"A2",110.00},
        {"E2",82.41}
      };

    m_freq = new QLabel(this);
    m_freq->setText("test");

    Pa_Initialize();
    PaStream *stream;

    Pa_OpenDefaultStream(&stream,1,0,paFloat32,8000,1024,audioCallback,&m_frequencyValue);
    Pa_StartStream(stream);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_vuMeter;
}


void MainWindow::updatePercentage(){

    m_freq->setText(QString::number(m_frequencyValue));

    struct KNN{
        qreal dist;
        int index;
    };

    QVector<KNN> distance;

    for(int i=0;i<m_Notes.size();++i){
        qreal dist = qAbs(m_frequencyValue-m_Notes[i].frequency);
        distance.push_back({dist,i});
    }

    sort(distance.begin(),distance.end(),[](KNN a,KNN b){
        return a.dist<b.dist;
    });

    for(auto d:distance){
        qDebug()<<d.dist<<" ---- "<<d.index;
    }
    qDebug()<<"----------------";

    QString noteName = m_Notes[distance[0].index].noteName;
    float freqName = m_Notes[distance[0].index].frequency;

    int percent = (m_frequencyValue*50)/freqName;
    percent = percent>100?100:percent;
    m_vuMeter->setNote(noteName);
    m_vuMeter->setPercentage(percent);
}

