#ifndef COMPLEX_H
#define COMPLEX_H

#include<iostream>
#include<math.h>
using namespace std;

class Complex{
  private:
    float m_real;
    float m_imag;
  public:
    Complex(){
      m_real = 0;
      m_imag = 0;
    }
    Complex(float real,float imag){
      this->m_real = real;
      this->m_imag = imag;
    }
    Complex operator+(Complex other){
        return Complex(this->m_real+other.m_real,this->m_imag+other.m_imag);
    }
    Complex operator-(Complex other){
        return Complex(this->m_real-other.m_real,this->m_imag-other.m_imag);
    }
    Complex operator*(Complex other){
        return Complex(this->m_real*other.m_real-this->m_imag*other.m_imag,this->m_real*other.m_imag+this->m_imag*other.m_real);
    }
    float real(){
        return this->m_real;
    }

    float imag(){
        return this->m_imag;
    }

    friend ostream& operator << (ostream& os,const Complex cls){
        char op = '+';
        if(cls.m_imag<0)    op = '\0';
        return os<<cls.m_real<<op<<cls.m_imag<<"i";
    }
};




#endif // COMPLEX_H
