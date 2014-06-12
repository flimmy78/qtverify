#ifndef	MYTHREAD_H
#define MYTHREAD_H

#include <QtCore/QThread>  
#include <QtCore/QObject> 



class MyThread : public QThread 
{      
	Q_OBJECT 

public:       
	MyThread(QObject* parent=0);

public slots:     
	void slot_main();   

protected:     
	void run();     
};  


class Object : public QObject 
{       
	Q_OBJECT  

public: 
	Object();

public slots:
	void slot();
};    

#endif //MYTHREAD_H