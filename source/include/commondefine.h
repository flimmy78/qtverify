#ifndef COMMONDEFINE_H
#define COMMONDEFINE_H


/************************************************************************/
/* 重定向：格式化，便于日志记录                                         */
/************************************************************************/
// #define qDebug() (qDebug()<<"Debug:"<<"file<"<<__FILE__<<">, line<"<<__LINE__<<">:")
#define qWarning() (qWarning()<<"Warning:"<<"file<"<<__FILE__<<">, line<"<<__LINE__<<">:")
#define qCritical() (qCritical()<<"Critical:"<<"file<"<<__FILE__<<">, line<"<<__LINE__<<">:")
// #define qFatal() (qFatal("Fatal: file< %s >, line< %d >:", __FILE__, __LINE__)) //这种重定向会导致信息无法写入文件


#endif //COMMONDEFINE_H