
#define     COMSET_1		0
#define		COMSET_2		1
#define		COMSET_3		2    
#define     COMSET_4        3   
#define     COMSET_5        4
#define     COMSET_6        5			
#define     COMSET_7        6

//�ȼ������Э��֧�֣�ͨ����gMETER_Table�����ֲ�ͬЭ��汾�ȼ��������ü�������
//Table ��ʽΪ���������ú���ָ���� + ��ȡ�ȼ��������ݱ�ʶ�� + ǰ��������+ͨѶ����(0:MBUS  1:485)
uint16 gMETER_Table[][4] = {
		COMSET_1, 0x901F, 4,    0,						//��³MBUS�����ȱ�----- ------ 0       
		COMSET_2, 0x52C3, 4,    0,						//�����------   1	Ӳ��Э�鲻���ݺ����� -������
		COMSET_1, 0x1F90, 0,	0,					    //����ɭ---------  2
		COMSET_1, 0x1F90, 4,	0,					    //����Э��1--------3	  ��������1��,�ؼ��Ǳ�ĳ��Ҵ���һ�� ����γ��Ϣ���� ,ע�����������ֱ����ݽ�����ʱ��С����δ֪��ͬ
		COMSET_3, 0x1F90, 4,	1,					    //��ҵ485--------- 4    
        COMSET_4, 0x901F, 4,    0,                      //����� ���--- 5���򻪵�С��Ҳ��
               
};

//����ָ�����飬����gMETER_Table�С��������ú���ָ���š���ȡ��Ӧ����ִ�С�
void (*METER_ComParaSetArray[])(void) = {METER_ComSet1, METER_ComSet2, METER_ComSet3, METER_ComSet4,METER_ComSet5,METER_ComSet6,METER_ComSet7};

//(*METER_ComParaSetArray[gMETER_Table[COMSET_1][0]])()  ִ�е����ݣ����ô��ڲ�������Ӧ��COMSET_2��COMSET_3�ȵȶ�����Ӧ��ָ�뺯�����˴�ʡ�ԡ�
void METER_ComSet1(void) 
{
	USART_InitTypeDef uart_init;

	/* ����USART2����
	    - BaudRate = 2400 baud
	    - Word Length = 8 Bits
	    - One Stop Bit
	    - MBUS_CHECK
	    - Hardware flow control disabled (RTS and CTS signals)
	    - Receive and transmit enabled
	*/
	uart_init.USART_BaudRate = 2400;
	uart_init.USART_WordLength = USART_WordLength_9b;
	uart_init.USART_StopBits = USART_StopBits_1;
	uart_init.USART_Parity = USART_Parity_Even;
	uart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &uart_init);
}


#define 	METER_FRAME_LEN_MAX		128
//�ȱ���Э��ṹ�嶨��
typedef struct{
	uint8   PreSmybolNum;			/*ǰ���ַ�����*/
	uint8   MeterType;				/*�Ǳ�����*/
	uint8 	MeterAddr[7];			/*�ȼ������ַ*/
	uint8 	ControlCode;			/*������*/
	uint8 	Length;					/*�����򳤶�*/
	uint16	DataIdentifier;			/*���ݱ�ʶ��*/
	uint8 	SER;					/*���к�*/
    uint8   DataBuf[METER_FRAME_LEN_MAX];

	}DELU_Protocol;
	
//�������Ϣ���ݸ�ʽ(�ṹ��)
typedef struct{
		uint16 MeterID;						//�ȱ��ţ�Ψһ�������ܲ�������
		uint8 MeterAddr[7];					//�ȼ������ַ
		uint8 Manufacturer;					//���̴���
		uint8 ProtocolVer;					//Э��汾
		uint8 EquipmentType;				//�豸����
		uint8 ChannelIndex;					//ͨ����
		uint8 ValveProtocal;				//������Э��ţ����ڼ��ݶ೧�Ҳ�ͬ��������
		uint8 ValveAddr[7];					//���ŵ�ַ
		uint8 ControlPanelAddr[7];			//��������ַ
		uint8 BulidID;						//¥��
		uint8 UnitID;						//��Ԫ��
		uint16 RoomID;						//�����
		uint16 Reserved1;					//һ��Ԥ��8�ֽڡ�
		uint16 Reserved2;
		uint16 Reserved3;
		uint16 Reserved4;
	}MeterFileType;							//��25���ֽ�
	
//����ʱ���²���
	DELU_Protocol	ProtocoalInfo;
	MeterFileType	mf;
	
	//��д��Ӧ�� �ȼ�����ͨ��Э�� �ṹ��
	ProtocoalInfo.PreSmybolNum  = gMETER_Table[mf.ProtocolVer][2];
	ProtocoalInfo.MeterType 	= 0x20;
	memcpy(ProtocoalInfo.MeterAddr, mf.MeterAddr, 7);
	ProtocoalInfo.ControlCode 	= 0x01;
	ProtocoalInfo.Length		= 0x03;
	ProtocoalInfo.DataIdentifier= gMETER_Table[mf.ProtocolVer][1];
	
	//��֡����
	/****************************************************************************************************
**	�� ��  �� ��: METER_CreateFrame
**	�� ��  �� ��: ���������ȼ�����������֡
**	�� ��  �� ��: DELU_Protocol *pReadMeter -- ��ȡ�ȼ���������ݽṹ
**	�� ��  �� ��: uint8  *_sendBuf -- �齨��������֡; 
**                uint16 *plenFrame -- �齨��������֡����
**  ��   ��   ֵ: ��
**	��		  ע: ����֡�����������ȼ���������֡�ṹ������Ϣ������֡
*****************************************************************************************************/
void METER_CreateFrame(DELU_Protocol *pData, uint8 *pSendFrame, uint8 *plenFrame)
{
	uint8 templen	= 0x00;
	uint8 cs		= 0x00;
	uint8 *pTemp, *pTemp1;
    uint16 lenFrame = 0x00;
    uint16 CheckLen = 0x00;
    
    LOG_assert_param(pData == NULL);
    LOG_assert_param(pSendFrame == NULL);
    LOG_assert_param(plenFrame == NULL);
	
	pTemp = pSendFrame;
	
	memset(pTemp, 0xFE, pData->PreSmybolNum);		//����ǰ���ַ�0xFE, �������������
	pTemp += pData->PreSmybolNum;
	lenFrame += pData->PreSmybolNum;
	
	pTemp1 = pTemp;									//Ԥ������У��λ
	*pTemp++ = DELU_FRAME_START;					//�齨 ֡ͷ 0x68
	*pTemp++ = pData->MeterType;					//�Ǳ�����
	memcpy(pTemp, pData->MeterAddr, 7);				//�齨 ��ַ��
	pTemp += 7;
	lenFrame += 9;
	CheckLen += 9;
	
	*pTemp++ = pData->ControlCode;					//�齨 ������
	*pTemp++ = pData->Length;						//�齨 �����򳤶�
	lenFrame += 2;
	CheckLen += 2;
	
	*pTemp++ = pData->DataIdentifier;
	*pTemp++ = (pData->DataIdentifier) >> 8;		//�齨 ���ݱ�ʶ��
	*pTemp++ = gMETER_FrameSer++;
	lenFrame += 3;
	CheckLen += 3;
	
	templen = pData->Length-3;
	memcpy(pTemp, pData->DataBuf, templen);
	pTemp += templen;
	lenFrame += templen;
	CheckLen += templen;
	
	cs = PUBLIC_CountCS(pTemp1, CheckLen);			//���� У���ֽ�
	*pTemp++ = cs;									//�齨 У��λ
	*pTemp++ = 0x16;									//�齨 ����λ
	lenFrame += 2;									//�齨 ����֡����

	*pTemp++ = 0x16;	//��ǿ485����1200bps��,���һ�ֽ����ǲ��ԣ���֡���һ�ֽڡ�
	lenFrame += 1;	
	
	*plenFrame = lenFrame;							//��������֡����
}


//���곭������֡���·��������ȱ������ݲ��������ɡ�
	
  

/****************************************************************************************************
**	�� ��  �� ��: METER_DELU_AnalDataFrame
**	�� ��  �� ��: ��������ȡ�����ȼ�������
**	�� ��  �� ��: Duint8 *pRecFrame -- ����Ĵ���֡������
**	�� ��  �� ��: DELU_Protocol *pProtoclData -- ��֡������ݽṹ
**  ��   ��   ֵ: NO_ERR
**	��		  ע: 
*****************************************************************************************************/

uint8 METER_DELU_AnalDataFrame(DELU_Protocol *pProtoclData, uint8 *pRecFrame)
{
	uint8 *pTemp 		= pRecFrame;
	
	LOG_assert_param(pProtoclData == NULL);
	LOG_assert_param(pRecFrame == NULL);
	
	if(pProtoclData->MeterType == 0x20)
	{
		if(0x68 != *pTemp++)	return 1;	
		
		pProtoclData->MeterType = *pTemp++;										//�Ǳ�����
		memcpy(pProtoclData->MeterAddr, pTemp, 7);								//�Ǳ��ַ
		pTemp += 7;
		
		pProtoclData->ControlCode	= *pTemp++;									//������
		pProtoclData->Length		= *pTemp++;									//����
		pProtoclData->DataIdentifier= (*pTemp++) | (*pTemp++ << 8);
		pProtoclData->SER			= *pTemp++;
		memcpy(pProtoclData->DataBuf, pTemp, (pProtoclData->Length-3));			//����������
		pTemp += pProtoclData->Length-3;
	}
	else{
		
		return ERR;
	}

	return NO_ERR;
}

//��³�ȱ����ݸ�ʽ�ṹ�塣
typedef struct{
	uint32   DailyHeat;		               /*����������*/	
    uint8     DailyHeatUnit;
	uint32   CurrentHeat;				   /*��ǰ����*/
    uint8     CurrentHeatUnit;
	uint32 	 HeatPower;			      		/*�ȹ���*/
    uint8     HeatPowerUnit;
	uint32 	 Flow;			                /*��������*/
    uint8 	 FlowUnit;
	uint32 	AccumulateFlow;				/*�ۻ�����*/
    uint8 	AccumulateFlowUnit;	
	uint8	WaterInTemp[3];		       	 /*��ˮ�¶�*/	
	uint8 	WaterOutTemp[3];				/*��ˮ�¶�*/
    uint8 	AccumulateWorkTime[3];			/*�ۼƹ���ʱ��*/
	uint8	RealTime[7];		                /*ʵʱʱ��*/	
	uint16 	ST;					                    /*״̬ST*/  
	}CJ188_Format;



CJ188_Data = METER_Data_To_CJ188Format(mf.ProtocolVer,ProtocoalInfo.DataBuf,sizeof(CJ188_Data) ,&err);
//�Ѳ�ͬ�ڵ�³�ȱ����ݸ�ʽ���ȱ����� �����ɺ͵�³��ʽһ��
CJ188_Format  METER_Data_To_CJ188Format(uint8 ProtocolVer,uint8* DataBuf,uint8 len,uint8* err)
{
    CJ188_Format  MeterData={0,0x05,0,0x05,0,0x17,0,0x35,0,0x2c};
   
    
    switch(ProtocolVer)
      {
      case LYRB-USF:  /*��ҵ485 LYRB-USF*/
          {
			//����ҵЭ�����ݵ����ɺ͵�³��ʽһ��
            break;
          }
       case WANHUA:  /*WANHUA ���*/
          {
			//����Э�����ݵ����ɺ͵�³��ʽһ��
            
            break;
          } 
    
		 	//�ȵ�

	
      default:  //��ȫ���ϵ�³Э��Ĵ���
          {
           memcpy(&MeterData,DataBuf,sizeof(MeterData));   /* ��³Э����ȫ����CJ188��׼*/ 
           }
        break;
      }
    
   return MeterData; 
}


	

