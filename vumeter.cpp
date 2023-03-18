#include "vumeter.h"
#include <QDebug>


VuMeter::VuMeter(int width, int height, QWidget *parent):
    QWidget(parent)
{
    m_height = height;
    m_width = width;
    m_percent = 0;

    m_counts = 21;
    m_singleBarHeight = 10;
    m_singleBarWidth = 40;
    m_barGap = 5;
    m_barHeight = (m_singleBarHeight*m_counts+m_barGap*(m_counts-1));

    setFixedSize(400,500);
    m_noteLabel = new QLabel(parent);
    m_noteLabel->setFixedSize(80,50);
    m_noteLabel->setFont(QFont("Times",50));
    m_noteLabel->move(m_width/2+20+m_singleBarWidth,m_height/2-20);

}

void VuMeter::setPercentage(int percent)
{
    m_percent = percent;
    update();
}

void VuMeter::setNote(QString note)
{
    m_noteLabel->setText(note);
}

void VuMeter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter;

    painter.begin(this);

    int startX = m_width/2-m_singleBarWidth/2;
    int startY = m_height/2-m_barHeight/2;

    int progressCount = qCeil((m_percent*m_counts)/100);


    int redTone = 255;
    int greenTone = 255;
    for(int i=m_counts-1;i>=0;--i){
        if(m_counts-progressCount<=i){
            if(m_percent<50){
               redTone = (100-2*m_percent)*255/100;
            }else{
                redTone = ((m_percent-50)*2)*255/100;
            }

            if(m_percent<=50){
                greenTone = 255;
            }else{
                greenTone = (100-(m_percent-50))*255/100;
            }
            painter.setBrush(QBrush(QColor(redTone,greenTone,0)));
        }else{
            painter.setBrush(Qt::NoBrush);
        }
        painter.setPen(QPen(QColor(redTone,greenTone,0),1));
        painter.drawRoundedRect(startX,startY+i*(m_singleBarHeight+m_barGap),m_singleBarWidth,m_singleBarHeight,5,5);

        int arrowX = startX+m_singleBarWidth+10/5+10;
        int arrowY = startY+m_barHeight/2;

        QPoint p1(arrowX,arrowY);
        QPoint p2(arrowX+10,arrowY-10);
        QPoint p3(arrowX+10, arrowY+10);
        QPolygonF triangle;

        triangle<<p1<<p2<<p3;
        painter.setPen(QPen(QColor(redTone,greenTone,0),2));
        painter.drawPolygon(triangle);
    }

    painter.end();


}

