#include <QtCore/QDebug>

#include "mythread.h"


MyThread::MyThread(QObject* parent) : QThread(parent)
{
	
}   

void MyThread::slot_main()
{           
	qDebug()<<"from thread slot_main:" <<currentThreadId();       
} 

void MyThread::run()
{           
	qDebug()<<"thread thread:"<<currentThreadId();     
}   



Object::Object() : QObject()
{

}

void Object::slot()
{    
	qDebug()<<"from thread slot:" <<QThread::currentThreadId();       
}   
