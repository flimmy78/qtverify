#ifndef COMMONDEFINE_H
#define COMMONDEFINE_H

/************************************************************************/
/* �ض��򣺸�ʽ����������־��¼                                         */
/************************************************************************/
// #define qDebug() (qDebug()<<"Debug:"<<"file<"<<__FILE__<<">, line<"<<__LINE__<<">:")
#define qWarning() (qWarning()<<"Warning:"<<"file<"<<__FILE__<<">, line<"<<__LINE__<<">:")
#define qCritical() (qCritical()<<"Critical:"<<"file<"<<__FILE__<<">, line<"<<__LINE__<<">:")
// #define qFatal() (qFatal("Fatal: file< %s >, line< %d >:", __FILE__, __LINE__)) //�����ض���ᵼ����Ϣ�޷�д���ļ�


/************************************************************************/
/* ͨ�ú궨��                                                           */
/************************************************************************/
#define FILENAME_LENGTH		100		//�ļ���(ȫ·��)����
#define ASCNAME_LEN			24		//���ݿ���д�����ĳ���
#define DESC_LEN			60		//���ݿ����������ĳ���

#endif //COMMONDEFINE_H