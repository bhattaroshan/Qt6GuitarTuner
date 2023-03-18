#ifndef VUMETER_H
#define VUMETER_H

#include<QWidget>
#include<QtGui>
#include<QLabel>

class VuMeter:public QWidget
{
public:
    VuMeter(int width,int height,QWidget *parent=nullptr);
    void setPercentage(int percent);
    void setNote(QString note);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    int m_height;
    int m_width;
    int m_counts;
    int m_singleBarHeight;
    int m_singleBarWidth;
    int m_barGap;
    int m_barHeight;
    int m_percent;
    QLabel *m_noteLabel;
};

#endif // VUMETER_H
