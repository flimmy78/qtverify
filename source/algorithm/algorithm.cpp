/***********************************************
**  �ļ���:     algorithm.cpp
**  ����:       �춨�㷨����ȡ�����ļ���
**  ����ϵͳ:   ����Trolltech Qt4.8.5�Ŀ�ƽ̨ϵͳ
**  ����ʱ��:   2014/6/26
**  רҵ��:     ��³���������
**  ���������: YS
**  ����Ա:     YS
**  �汾��ʷ:   2014/06 ��һ��
**  ���ݰ���:
**  ˵��:		
**  ���¼�¼:   
***********************************************/

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QProcessEnvironment>
#include <QCoreApplication>
#include <QTime>
#include <qmath.h>

#include "algorithm.h"
#include "commondefine.h"
#include "qtexdb.h"

QDateTime getProbationStartDate()
{
	QString filename = getFullIniFileName("verifyparaset.ini");//�����ļ����ļ���
	QSettings settings(filename, QSettings::IniFormat);
	settings.setIniCodec("GB2312");//�����ini�ļ���д��������
	QString probation = settings.value("Other/probation").toString();
	QDateTime regDate = QDateTime::fromString(probation, "yyyyMMddhhmmss");
	return regDate;
}

void setProbationStartDate()
{
	QString filename = getFullIniFileName("verifyparaset.ini");//�����ļ����ļ���
	QSettings settings(filename, QSettings::IniFormat);
	settings.setIniCodec("GB2312");//�����ini�ļ���д��������
	QString probation = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
	settings.setValue("Other/probation", probation);
}

void sleep(unsigned int msec)
{
	QTime n = QTime::currentTime();
	QTime now;
	do
	{
		now = QTime::currentTime();
	} while(n.msecsTo(now) <= msec); 
}

void wait(unsigned int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while( QTime::currentTime() < dieTime )
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//��ȡ���ư�Ķ˿ں�������Ϣ
int getPortSetIni(PortSet_Ini_PTR info)
{
	QString filename = getFullIniFileName("portset.ini");
	QSettings settings(filename, QSettings::IniFormat);

	info->waterInNo = settings.value("Relay/waterInNo").toInt();
	info->bigNo = settings.value("Relay/bigNo").toInt();
	info->middle1No = settings.value("Relay/middle1No").toInt();
	info->middle2No = settings.value("Relay/middle2No").toInt();
	info->smallNo = settings.value("Relay/smallNo").toInt();
	info->waterOutNo = settings.value("Relay/waterOutNo").toInt();
	info->bigWaterInNo = settings.value("Relay/bigWaterInNo").toInt();
	info->bigWaterOutNo = settings.value("Relay/bigWaterOutNo").toInt();
	info->smallWaterInNo = settings.value("Relay/smallWaterInNo").toInt();
	info->smallWaterOutNo = settings.value("Relay/smallWaterOutNo").toInt();
	
	info->regSmallNo = settings.value("Regulate/regSmallNo").toInt();
	info->regMid1No = settings.value("Regulate/regMid1No").toInt();
	info->regMid2No = settings.value("Regulate/regMid2No").toInt();
	info->regBigNo = settings.value("Regulate/regBigNo").toInt();
	info->pumpNo = settings.value("Regulate/pumpNo").toInt();

	info->version = settings.value("CtrlBoard/version").toInt();
	return true;
}

//��ȡ����-�ӻ�������Ϣ
int getMasterSlaveIni(MasterSlave_Ini_PTR info)
{
	QString filename = getFullIniFileName("masterslaveset.ini");
	QSettings settings(filename, QSettings::IniFormat);

	info->netmode = settings.value("localhost/netmode").toInt();
	info->hostflag = settings.value("localhost/hostflag").toInt();
	strcpy_s(info->mastername, settings.value("master/hostname").toString().toAscii());
	strcpy_s(info->masterIP, settings.value("master/ip").toString().toAscii());
	strcpy_s(info->slave1name, settings.value("slave1/hostname").toString().toAscii());
	strcpy_s(info->slave1IP, settings.value("slave1/ip").toString().toAscii());
	strcpy_s(info->slave2name, settings.value("slave2/hostname").toString().toAscii());
	strcpy_s(info->slave2IP, settings.value("slave2/ip").toString().toAscii());
	strcpy_s(info->slave3name, settings.value("slave3/hostname").toString().toAscii());
	strcpy_s(info->slave3IP, settings.value("slave3/ip").toString().toAscii());
	strcpy_s(info->slave4name, settings.value("slave4/hostname").toString().toAscii());
	strcpy_s(info->slave4IP, settings.value("slave4/ip").toString().toAscii());

	return true;
}

QString getFullIniFileName(QString filename)
{
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	if (adehome.isEmpty())
	{
		qWarning()<<"Get $(ADEHOME) Failed! Please set up this system variable.";
		return "";
	}
	QString fullname;
#ifdef __unix
	fullname = adehome + "\/ini\/" + filename;
#else
	fullname = adehome + "\\ini\\" + filename;
#endif
	return fullname;
}

//��ȡ���вɼ������Ӧ����������
QStringList getPickCodeStringList()
{
	QString filename = getFullIniFileName("pickcode.ini");
	QString str;
	QStringList strlist;
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream stream(&file);
		while (!stream.atEnd())
		{
			str = stream.readLine().simplified(); //ȥ����β�ո�
			if (str.isEmpty() || str.startsWith("#"))
			{
				continue;
			}
			strlist += str.section("=", 1);
		}
	}
	return strlist;
}

float detA(float a00, float a01, float a10, float a11)
{
	return a00*a11 - a01*a10;
}

/************************************************************************/
/* һ��ֻ�������¶�-��ֵ���ɼ�����˲�������¶�ϵ����0���¶�                 */
/************************************************************************/
plaParam_PTR getPlaParam(pla_T_R_PTR pla_p, int num)
{
	plaParam_PTR p_param;
	p_param = new plaParam_STR;
	float coe[2][3];//����ϵ��, coe[i,j]ǰ���ж�Ӧ�����Է�����ĵ�i�����̵�j��δ֪����ϵ��, �������ǳ�����
	coe[0][0] = detA(pla_p[0].resis, pla_p[0].tmp, pla_p[1].resis, pla_p[1].tmp);
	coe[0][1] = detA(pla_p[0].resis, pla_p[0].tmp*pla_p[0].tmp, pla_p[1].resis, pla_p[1].tmp*pla_p[1].tmp);
	coe[0][2] = pla_p[1].resis - pla_p[0].resis;
	coe[1][0] = detA(pla_p[0].resis, pla_p[0].tmp, pla_p[2].resis, pla_p[2].tmp);
	coe[1][1] = detA(pla_p[0].resis, pla_p[0].tmp*pla_p[0].tmp, pla_p[2].resis, pla_p[2].tmp*pla_p[2].tmp);
	coe[1][2] = pla_p[2].resis - pla_p[0].resis;

	float M;//����ķ����ϵ�����������ʽ��ֵ
	float A;//��һδ֪��a��ֵ
	float B;//�ڶ�δ֪��b��ֵ
	M = detA(coe[0][0], coe[0][1], coe[1][0], coe[1][1]);
	A = detA(coe[0][2], coe[0][1], coe[1][2], coe[1][1]);
	B = detA(coe[0][0], coe[0][2], coe[1][0], coe[1][2]);
	p_param->a = A/M;
	p_param->b = B/M;
	p_param->r0 = pla_p[0].resis/(1 + p_param->a*pla_p[0].tmp + p_param->b*pla_p[0].tmp*pla_p[0].tmp);
	p_param->c;//����cһ�㲻�����㣬ֻ��0�����²��õ�
	return p_param;
}

float getPlaRt(float r0, float a, float b, float tmp)
{
	return r0*(1+a*tmp+b*tmp*tmp);
}

float getPlaTr(float r0, float a, float b, float resis)
{
	if (b==0.0 && a != 0.0)
	{
		return (resis/r0 - 1)/a;
	}
	else if (b==0.0 && a == 0.0)
	{
		return -1;
	}

// 	float ret = (qSqrt(a*a + 4*b*(resis/r0 - 1)) - a)/(2*b);
	float ret = qSqrt(resis/r0/b - 1/b + a*a/(4*b*b)) - (0.5*a/b);
	return ret;
}

float calcTemperByResis(float resis)
{
	QString filename = getFullIniFileName("stdplasensor.ini");
	QSettings settings(filename, QSettings::IniFormat);
	QString pt = settings.value("in_use/pt").toString();
	float rtp = settings.value(pt+"/in_rtp").toFloat();
	float a = settings.value(pt+"/in_a").toFloat();
	float b = settings.value(pt+"/in_b").toFloat();
	float temp = getPlaTr(rtp, a, b, resis);
	return temp;
}

float getDeltaTmpErr(float std_delta_t, float min_delta_t)
{
	return qAbs(0.5 + 3*min_delta_t/std_delta_t);
}

float getSingleTmpErr(float std_delta_t)
{
	return (0.3 + 0.005*qAbs(std_delta_t));
}

/************************************************************************/
/*����JJG-2001 Page4, ��1�����ܱ�����������ޣ�
/*grade, ��ĵȼ�, 1��, 2��, 3����
/*delta_t_min, �����С�²�
/*deta_t, ʵ�ʼ��ʱ���²�
/*dn_flow_rate, ��ĳ���(�)����, ������λ��flow_rate��ͬ
/*flow_rate, ʵ�ʼ��ʱ�������
/************************************************************************/
float calcMeterHeatErrLmt(int grade, float delta_t_min, float delta_t, float dn_flow_rate, float flow_rate)
{
	float ret;
	float coe_a, coe_b, coe_c;
	switch(grade)
	{
		case GRADE_ONE:
			coe_a = 2.0f;
			coe_b = 4.0f;
			coe_c = 0.01f;
			break;
		case GRADE_TWO:
			coe_a = 3.0f;
			coe_b = 4.0f;
			coe_c = 0.02f;
			break;
		case GRADE_THREE:
			coe_a = 4.0f;
			coe_b = 4.0f;
			coe_c = 0.05f;
			break;
		default:
			break;
	}
	ret = qAbs(coe_a + coe_b*(delta_t_min/delta_t) + coe_c*(dn_flow_rate/flow_rate));
	return ret;
}

//�����ȱ�������䳣������
float getNormalFlowByStandard(int standard)
{
	float normalFlow = 0.0;
	switch (standard)
	{
	case DN15:
		normalFlow = 1.5f;
		break;
	case DN20:
		normalFlow = 2.5f;
		break;
	case DN25:
		normalFlow = 3.5f;
		break;
	case DN32:
		normalFlow = 6.0f;
		break;
	case DN40:
		normalFlow = 10.0f;
		break;
	case DN50:
		normalFlow = 15.0f;
		break;
	default:
		break;
	}

	return normalFlow;
}

//����������ͨѶ���ص����ֽ����ݣ��������Ӧ�ĸ�������ֵ
float calcFloatValueOfCoe(QString coe)
{
	bool ok;
	float dec = coe.right(3).toInt(&ok, 16)/4096.0;
	float coeV = coe.left(1).toFloat() + dec; 

	return coeV;
}

//����������ͨѶ���ص����ֽ����ݣ��������Ӧ�����ֵ
float calcErrorValueOfCoe(QString coe)
{
	float coeV = calcFloatValueOfCoe(coe); 
	float errV = 100/coeV - 100;

	return errV;
}

/* ����ModBus-RTU����Э���CRCУ��ֵ
 * ref: http://www.ccontrolsys.com/w/How_to_Compute_the_Modbus_RTU_Message_CRC
 * ���ɶ���ʽΪ x^16+x^15+x^2+x^0, ��ϵ���ִ�Ϊ (1 1000 0000 0000 0101),
 * ����16���ݵ�ϵ����Ϊ (1000 0000 0000 0101, ��0x8005),
 * �ٷ���õ� (1010 0000 0000 0001, ��0xA001)
 * buf, ָ����Ϣͷ��ָ��;
 * len, ��Ϣ��ĳ���
 */
UINT16 calcModRtuCRC(uchar *buf, int len)
{
	UINT16 crc = 0xFFFF;

	for (int pos = 0; pos < len; pos++) {
		crc ^= (UINT16)buf[pos];          // XOR byte into least sig. byte of crc

		for (int i = 8; i > 0; i--) {    // Loop over each bit
			if ((crc & 0x0001) != 0) {      // If the LSB is set, that is the LSB is 1
				crc >>= 1;                  // Shift right, ignore LSB(LSB is the MSB before reverse)
				crc ^= POLY;				// and XOR 0xA001
			}
			else                            // Else LSB is not set, that is the LSB is 0
				crc >>= 1;                  // Just shift right, a XOR 0 = a, so not need to do XOR
		}
	}
	return crc;
}

UINT16 CRC16ModRTU_Table_Driven (const uchar *nData, UINT16 wLength)
{
	static const UINT16 wCRCTable[] = {
		0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
		0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
		0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
		0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
		0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
		0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
		0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
		0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
		0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
		0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
		0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
		0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
		0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
		0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
		0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
		0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
		0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
		0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
		0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
		0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
		0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
		0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
		0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
		0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
		0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
		0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
		0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
		0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
		0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
		0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
		0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
		0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 
	};

		uchar nTemp;
		UINT16 wCRCWord = 0xFFFF;

		while (wLength--)
		{
			nTemp = *nData++ ^ wCRCWord;
			wCRCWord >>= BYTE_LENGTH;
			wCRCWord  ^= wCRCTable[nTemp];
		}
		return wCRCWord;
}

/* ��CRC������ת��ΪQByteArray
 * ����ֵQByteArray sendbuf;
 * sendbuf.at(0) �ǵ�λ;  sendbuf.at(1) �Ǹ�λ
 * crc, ����õ���У��ֵ, ��λ��ǰ, ��λ�ں�
 */
QByteArray getCRCArray(UINT16 crc)
{
	QByteArray sendbuf;
	sendbuf.append((char)crc);//��λ
	sendbuf.append((char)(crc>>BYTE_LENGTH));//��λ
	return sendbuf;
}

int get9150ARouteI(int i, QByteArray valueArray)
{
	if(valueArray.length() < EDA9150A_ROUTE_BYTES)
		return -1;

	if ( (EDA9150A_ROUTE_BYTES*i) > valueArray.length())//i���ܳ�������ȡ��ͨ������
	{
		return -1;
	}

	QByteArray data;
	for (int k=0;k<EDA9150A_ROUTE_BYTES;k++)
		data.append(valueArray.at(EDA9150A_ROUTE_BYTES*i+k));

	int value = 0;	
	for (int k=0;k<EDA9150A_ROUTE_BYTES;k++)
	{
		value |= ( ((uchar)data.at(k)) << ((EDA9150A_ROUTE_BYTES-1-k)*BYTE_LENGTH) );
	}
	return value;
}

int get9017RouteI(int i, QByteArray valueArray)
{
	if(valueArray.length() < EDA9017_ROUTE_BYTES)
		return -1;

	if ( (EDA9017_ROUTE_BYTES*i) > valueArray.length())//i���ܳ�������ȡ��ͨ������
	{
		return -1;
	}

	QByteArray data;
	for (int k=0;k<EDA9017_ROUTE_BYTES;k++)
		data.append(valueArray.at(EDA9017_ROUTE_BYTES*i+k));

	int value = 0;	
	for (int k=0;k<EDA9017_ROUTE_BYTES;k++)
	{
		value |= ( ((uchar)data.at(k)) << ((EDA9017_ROUTE_BYTES-1-k)*BYTE_LENGTH) );
	}
	return value;
}

float getInstStdValue(float elecValue, float upperValue)
{
	if (ELEC_ZERO<=elecValue && elecValue <= ELEC_UPPER)
	{
		float deltaStd = ELEC_UPPER - ELEC_ZERO;
		float deltaCur = elecValue - ELEC_ZERO;
		return (deltaCur/deltaStd)*upperValue;
	}

	return 0.0f;//���������������ֵ�ķ�Χ, �����쳣����
}


/*
** ����ˮ��ı�׼���
*/
float getWaterMeterStdError(float Q2, int grade, float temper, float flow)
{
	float stdErr = 0.02;
	switch (grade)
	{
	case 1: //һ��ˮ��
		if (temper>=0.1 && temper<=30)
		{
			if (flow >= Q2) //����
			{
				stdErr = 0.01;
			}
			else //����
			{
				stdErr = 0.03;
			}
		}
		else
		{
			if (flow >= Q2) //����
			{
				stdErr = 0.02;
			}
			else //����
			{
				stdErr = 0.03;
			}
		}
		break;
	case 2: //����ˮ��
		if (temper>=0.1 && temper<=30)
		{
			if (flow >= Q2) //����
			{
				stdErr = 0.02;
			}
			else //����
			{
				stdErr = 0.05;
			}
		}
		else
		{
			if (flow >= Q2) //����
			{
				stdErr = 0.03;
			}
			else //����
			{
				stdErr = 0.05;
			}
		}
		break;
	default:
		break;
	}

	return stdErr*100;
}

/**********************************************************
������CAlgorithm
���ܣ��춨�㷨��
***********************************************************/
CAlgorithm::CAlgorithm()
{

}

CAlgorithm::~CAlgorithm()
{

}

float CAlgorithm::calc(float a, float b)
{
	float sum = a + b;
	qDebug("%.2f + %.2f = %.2f \n", a, b, sum);
	return sum;
}

/*********************************************************************************************
* ����λ�ż������¶�(���������)                                      
* inlet: ��ˮ���¶�ֵ                                                              
* outlet: ��ˮ���¶�ֵ																						   
* num: ��λ��(��1��ʼ�����������), �Դ˼�����ȱ�����ڵľ���        
/********************************************************************************************/
float CAlgorithm::getMeterTempByPos(float inlet, float outlet, int num)
{
	//��ȡ�����Ĺ��
	QSettings ParaSet(getFullIniFileName("verifyparaset.ini"), QSettings::IniFormat);//���������ļ�
	int standard = ParaSet.value("head/standard").toInt();//�������
    int totalCount = getMaxMeterByIdx(standard); //�ù���ȱ��Ӧ�����������
	float delta = (inlet - outlet)/(totalCount + 2); //˫��·��ƣ��������ǰ�����䴦�����ں����һ��������
	float temper = inlet - (num + (int)(2*(num-1)/totalCount))*delta;
	return temper;
}

/************************************************************************
* ����ˮ��-�ܶȱ�(JGG 225-2010 ������춨���)
* ���ж���ʽ���(MATLAB, 9�η�)
* float temp: �¶�ֵ ( 1 �� temp �� 150 , ��λǧ��/��, kg/L)
* f(x) = p1*x^9 + p2*x^8 + p3*x^7 + p4*x^6 + 
* p5*x^5 + p6*x^4 + p7*x^3 + p8*x^2 + p9*x + p10               
/************************************************************************/
double CAlgorithm::getDensityByFit(float temp)
{
	//p1~p10Ϊ����ʽϵ��
	double const p1 =  -3.562e-18;
	double const p2 =   2.303e-15;
	double const p3 =  -5.989e-13;
	double const p4 =   7.617e-11;
	double const p5 =  -3.716e-09;
	double const p6 =  -2.719e-07;
	double const p7 =   6.455e-05;
	double const p8 =   -0.008346;
	double const p9 =     0.05982;
	double const p10 =  1000.12;
	//exp2~exp9Ϊ��������ֵ
	double exp2 = temp * temp;
	double exp3 = exp2 * temp;
	double exp4 = exp3 * temp;
	double exp5 = exp4 * temp;
	double exp6 = exp5 * temp;
	double exp7 = exp6 * temp;
	double exp8 = exp7 * temp;
	double exp9 = exp8 * temp;

	return  (p1*exp9 + p2*exp8 + p3*exp7 + p4*exp6 + p5*exp5 + p6 * exp4 + p7*exp3 +  + p8*exp2 +  + p9*temp + p10) / 1000.0;
}

/*****************************************************************************
* ������Ӧˮ�µ��ܶ�ֵ(��λǧ��/��, kg/L)
* �赱ǰˮ��Ϊtemp
* temp����������Ϊ low, 
* low�¶�ֵ���ɵ�density[low - 1](density��������0��ʼ)
* (��temp��С�����ֲ�Ϊ��, ��ô��Ϊ���¶�low-1��low֮��
* �ܶ�ֵ�����Ա仯��)
/****************************************************************************/
double CAlgorithm::getDensityByQuery(float temp)
{
	if (temp<1 || temp>149)
	{
		return -1;
	}
	int low = getInt(temp);

	return (density[low -1] +  getDecimal(temp) * (density[low] - density[low - 1])) / 1000.0;
}

/*
** ������Ӧˮ�µ���ֵ(��λ kJ/kg)
*/
double CAlgorithm::getEnthalpyByQuery(float temp)
{
	int low = getInt(temp);
	float ret = enthalpy[low -1] +  getDecimal(temp) * (enthalpy[low] - enthalpy[low - 1]);
	return ret;
}

/*
** ����ŷ��EN1434�����ܱ�����ˮ��Kϵ��
** Ĭ��Kϵ����λMJ/m3��
*/
double CAlgorithm::calcKCoeOfWater(float inTemper, float outTemper, int installPos, float pressure)
{
	float kCoe = 0.0;
	float vIn = 0.0, vOut = 0.0;
	float tao = 0.0;
	float hIn = getEnthalpyByQuery(inTemper);
	float hOut = getEnthalpyByQuery(outTemper);
 	float pai = pressure/16.53;
	float kIn = inTemper + 273.13;
	float kOut = outTemper + 273.13;
	float R = 461.526;
	float lanmuda = 0.0;
	int i = 0;
	float tmp;

	if (installPos==INSTALLPOS_IN) //��װλ�� ���
	{
		tao = 1386/kIn;
		for (i=0; i<34; i++)
		{
			tmp = -n[i]*I[i]*pow(7.1-pai, I[i]-1)*pow(tao-1.222, J[i]);
			lanmuda += tmp;
		}
		vIn = pai*lanmuda*R*kIn/pressure/1000;
		kCoe = (hIn - hOut)/(inTemper - outTemper)/vIn;
	}
	else if (installPos==INSTALLPOS_OUT)	//��װλ�� ����
	{
		tao = 1386/kOut;
		for (i=0; i<34; i++)
		{
			tmp = -n[i]*I[i]*pow(7.1-pai, I[i]-1)*pow(tao-1.222, J[i]);
			lanmuda += tmp;
		}
		vOut = pai*lanmuda*R*kOut/pressure/1000;
		kCoe = (hIn - hOut)/(inTemper - outTemper)/vOut;
	}

	return kCoe;
}

/*
** ����ŷ��EN1434�����ܱ�Part-1 ����ˮ�ı���ֵ
** ��λKJ/kg
** temp �¶�, ��
** pressure ѹǿ, MPa
*/
double CAlgorithm::calcEnthalpyOfWater(float temp, float pressure)
{
	float T = temp + 273.15;//�������¶ȱ�
	float tao = 1386/T;
	float pai = pressure/16.53;
	float gamaTao = getGamaTao(pai, tao);

	float H = tao*gamaTao*ENTHALPY_R*T;

	return H/1000.0;
}

double CAlgorithm::getGamaPai(float pai, float tao)
{
	float gama = 0.0;
	for (int i=0; i<34; i++)
		gama += (-1)*n[i]*I[i]*pow(7.1-pai, I[i]-1)*pow(tao-1.222, J[i]);

	return gama;
}

double CAlgorithm::getGamaTao(float pai, float tao)
{
	float gama = 0.0;
	for (int i=0; i<34; i++)
		gama += n[i]*pow(7.1-pai, I[i])*J[i]*pow(tao - 1.222, J[i] - 1);

	return gama;
}

/*
** ����ŷ��EN1434�����ܱ�Part-1 ����ˮ�ı���ֵ
** ��λ(kWh/MJ)
** inTemper �����¶�, ��
** outTemper �����¶�, ��
** volum ���, L
** installPos ��װλ��, ����/����
** unit ʹ�õ���ֵ��λ, kWh/MJ
** pressure ѹǿ, MPa
*/
double CAlgorithm::calcEnergyByEnthalpy(float inTemper, float outTemper, float volum,  int installPos, int unit, float pressure)
{
	float inEnthalpy, outEnthalpy;
	float density;
	float mass;
	float energy;

	inEnthalpy = calcEnthalpyOfWater(inTemper, pressure);//KJ/kg
	outEnthalpy = calcEnthalpyOfWater(outTemper, pressure);//KJ/kg
	if (installPos == INSTALLPOS_IN)
	{
		density = getDensityByQuery(inTemper);//kg/L
	}
	else if (installPos == INSTALLPOS_OUT)
	{
		density = getDensityByQuery(outTemper);//kg/L
	}
	
	mass = density*volum;//kg
	energy = mass*(inEnthalpy-outEnthalpy);//KJ
	if (unit == UNIT_KWH)
	{
		energy /= 3600.0;
	}
	else if (unit == UNIT_MJ)
	{
		energy /= 1000.0;
	}
	return energy;
}

/************************************************************************
* ���㸡��������������           
/************************************************************************/
int CAlgorithm::getInt(float p)
{
	if (p > 0)
	{
		return int(p);
	}
	else if (p == 0)
	{
		return 0;
	}
	else
	{
		return (int(p) - 1);
	}
}
/************************************************************************
* ���㸡������С������           
/************************************************************************/
float CAlgorithm::getDecimal(float p)
{
	return (p - getInt(p));
}

/************************************************************************
* ����λ�Ż�ȡ��Ӧ��λ�ı�׼������� (��λ��, L)                       
* mass:  ����(��λǧ��, kg����ƽ�������׼������������),δ����
* inlet: ��ˮ���¶�
* outlet: ��ˮ���¶�
* num: ��λ��(��1��ʼ�����������)
* method���춨���� ��0����������1����׼����
* balCap:��ƽ��������Ӧ��ͬ��ϵ����0��150kg��ƽ��ϵ��0.9971�� 1��600kg��ƽ��ϵ��0.9939
************************************************************************/
double CAlgorithm::getStdVolByPos(float mass, float inlet, float outlet, int num, int method, int balCap)
{	
	float temp = getMeterTempByPos(inlet, outlet, num);//��ȡ�¶�
#ifdef FIT
	float den = getDensityByFit(temp);//��ȡ�ܶ�
#else
	float den = getDensityByQuery(temp);//��ȡ�ܶ�
#endif

	float stdVol = 0.0;
	if (method == WEIGHT_METHOD)
	{
		if (balCap == BALANCE_CAP150)
		{
			stdVol = mass*0.9971 / den; //��׼���(��������Ҫ������ƽ��ˮ�ܵĸ���������150kg��ƽ����ϵ��0.9971)
		}
		else //BALANCE_CAP600
		{
			stdVol = mass*0.9939 / den; //��׼���(��������Ҫ������ƽ��ˮ�ܵĸ���������600kg��ƽ����ϵ��0.9939��
		}
	}
	else //STANDARD_METHOD
	{
		stdVol = mass / den;
	}
	return stdVol;
}

/*
** �����ʲ�����׼������JJG-2001)
** ��λ(kWh��MJ)
** inTemper ���ڱ�׼�¶�, ��
** outTemper ���ڱ�׼�¶�, ��
** mass ����, kg
** unit ʹ�õ���ֵ��λ, 0:MJ ; 1:kWh
** method �춨������0:��������1:��׼��
** balCap:��ƽ��������Ӧ��ͬ��ϵ����0��150kg��ƽ��ϵ��0.9971�� 1��600kg��ƽ��ϵ��0.9939
** pressure:��ѹ
*/
double CAlgorithm::calcStdEnergyByEnthalpy(float inTemper, float outTemper, float mass, int unit, int method, int balCap, float pressure)
{
	float inEnthalpy, outEnthalpy, energy;

// 	inEnthalpy = calcEnthalpyOfWater(inTemper, pressure);//KJ/kg
// 	outEnthalpy = calcEnthalpyOfWater(outTemper, pressure);//KJ/kg
	inEnthalpy = getEnthalpyByQuery(inTemper);//KJ/kg
	outEnthalpy = getEnthalpyByQuery(outTemper);//KJ/kg

	float massA = 0.0;
	if (method == WEIGHT_METHOD)
	{
		if (balCap == BALANCE_CAP150)
		{
			massA = mass * 0.9971;
		}
		else //BALANCE_CAP600
		{
			massA = mass * 0.9939;
		}
	}
	else //STANDARD_METHOD
	{
		massA = mass;
	}
	energy = massA*(inEnthalpy-outEnthalpy);//KJ
	if (unit == UNIT_KWH)
	{
		energy /= 3600.0;
	}
	else if (unit == UNIT_MJ)
	{
		energy /= 1000.0;
	}
	return energy;
}

