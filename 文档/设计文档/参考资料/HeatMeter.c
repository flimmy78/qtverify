
#define     COMSET_1		0
#define		COMSET_2		1
#define		COMSET_3		2    
#define     COMSET_4        3   
#define     COMSET_5        4
#define     COMSET_6        5			
#define     COMSET_7        6

//热计量表多协议支持，通过该gMETER_Table来区分不同协议版本热计量表设置及抄读等
//Table 格式为：串口设置函数指针标号 + 读取热计量表数据标识符 + 前导符个数+通讯类型(0:MBUS  1:485)
uint16 gMETER_Table[][4] = {
		COMSET_1, 0x901F, 4,    0,						//德鲁MBUS总线热表----- ------ 0       
		COMSET_2, 0x52C3, 4,    0,						//天津万华------   1	硬件协议不兼容海威茨 -林晓彬
		COMSET_1, 0x1F90, 0,	0,					    //丹佛森---------  2
		COMSET_1, 0x1F90, 4,	0,					    //立创协议1--------3	  威海震宇1表,关键是表的厂家代码一样 ，经纬不息屏版 ,注：力创有两种表，数据解析的时候小数点未知不同
		COMSET_3, 0x1F90, 4,	1,					    //乐业485--------- 4    
        COMSET_4, 0x901F, 4,    0,                      //天津万华 大表--- 5，万华的小表也用
               
};

//函数指针数组，根据gMETER_Table中“串口设置函数指针表号”调取相应函数执行。
void (*METER_ComParaSetArray[])(void) = {METER_ComSet1, METER_ComSet2, METER_ComSet3, METER_ComSet4,METER_ComSet5,METER_ComSet6,METER_ComSet7};

//(*METER_ComParaSetArray[gMETER_Table[COMSET_1][0]])()  执行的内容，设置串口参数。相应的COMSET_2、COMSET_3等等都有相应的指针函数，此处省略。
void METER_ComSet1(void) 
{
	USART_InitTypeDef uart_init;

	/* 配置USART2参数
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
//热表抄表协议结构体定义
typedef struct{
	uint8   PreSmybolNum;			/*前导字符个数*/
	uint8   MeterType;				/*仪表类型*/
	uint8 	MeterAddr[7];			/*热计量表地址*/
	uint8 	ControlCode;			/*控制码*/
	uint8 	Length;					/*数据域长度*/
	uint16	DataIdentifier;			/*数据标识符*/
	uint8 	SER;					/*序列号*/
    uint8   DataBuf[METER_FRAME_LEN_MAX];

	}DELU_Protocol;
	
//表基础信息内容格式(结构体)
typedef struct{
		uint16 MeterID;						//热表编号，唯一，但可能不连续。
		uint8 MeterAddr[7];					//热计量表地址
		uint8 Manufacturer;					//厂商代码
		uint8 ProtocolVer;					//协议版本
		uint8 EquipmentType;				//设备类型
		uint8 ChannelIndex;					//通道号
		uint8 ValveProtocal;				//阀控器协议号，用于兼容多厂家不同阀控器。
		uint8 ValveAddr[7];					//阀门地址
		uint8 ControlPanelAddr[7];			//控制面板地址
		uint8 BulidID;						//楼号
		uint8 UnitID;						//单元号
		uint16 RoomID;						//房间号
		uint16 Reserved1;					//一下预留8字节。
		uint16 Reserved2;
		uint16 Reserved3;
		uint16 Reserved4;
	}MeterFileType;							//共25个字节
	
//抄表时如下操作
	DELU_Protocol	ProtocoalInfo;
	MeterFileType	mf;
	
	//填写相应的 热计量表通信协议 结构体
	ProtocoalInfo.PreSmybolNum  = gMETER_Table[mf.ProtocolVer][2];
	ProtocoalInfo.MeterType 	= 0x20;
	memcpy(ProtocoalInfo.MeterAddr, mf.MeterAddr, 7);
	ProtocoalInfo.ControlCode 	= 0x01;
	ProtocoalInfo.Length		= 0x03;
	ProtocoalInfo.DataIdentifier= gMETER_Table[mf.ProtocolVer][1];
	
	//组帧函数
	/****************************************************************************************************
**	函 数  名 称: METER_CreateFrame
**	函 数  功 能: 集中器对热计量表数据组帧
**	输 入  参 数: DELU_Protocol *pReadMeter -- 读取热计量表的数据结构
**	输 出  参 数: uint8  *_sendBuf -- 组建出的数据帧; 
**                uint16 *plenFrame -- 组建出的数据帧长度
**  返   回   值: 无
**	备		  注: 本组帧函数，根据热计量表数据帧结构体内信息进行组帧
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
	
	memset(pTemp, 0xFE, pData->PreSmybolNum);		//填入前导字符0xFE, 个数视情况而定
	pTemp += pData->PreSmybolNum;
	lenFrame += pData->PreSmybolNum;
	
	pTemp1 = pTemp;									//预留计算校验位
	*pTemp++ = DELU_FRAME_START;					//组建 帧头 0x68
	*pTemp++ = pData->MeterType;					//仪表类型
	memcpy(pTemp, pData->MeterAddr, 7);				//组建 地址域
	pTemp += 7;
	lenFrame += 9;
	CheckLen += 9;
	
	*pTemp++ = pData->ControlCode;					//组建 控制码
	*pTemp++ = pData->Length;						//组建 数据域长度
	lenFrame += 2;
	CheckLen += 2;
	
	*pTemp++ = pData->DataIdentifier;
	*pTemp++ = (pData->DataIdentifier) >> 8;		//组建 数据标识符
	*pTemp++ = gMETER_FrameSer++;
	lenFrame += 3;
	CheckLen += 3;
	
	templen = pData->Length-3;
	memcpy(pTemp, pData->DataBuf, templen);
	pTemp += templen;
	lenFrame += templen;
	CheckLen += templen;
	
	cs = PUBLIC_CountCS(pTemp1, CheckLen);			//计算 校验字节
	*pTemp++ = cs;									//组建 校验位
	*pTemp++ = 0x16;									//组建 结束位
	lenFrame += 2;									//组建 数据帧长度

	*pTemp++ = 0x16;	//联强485总线1200bps调,最后一字节总是不对，组帧多放一字节。
	lenFrame += 1;	
	
	*plenFrame = lenFrame;							//返回数据帧长度
}


//组完抄表数据帧后下发，接收热表返回数据并处理，即可。
	
  

/****************************************************************************************************
**	函 数  名 称: METER_DELU_AnalDataFrame
**	函 数  功 能: 集解析读取来的热计量数据
**	输 入  参 数: Duint8 *pRecFrame -- 输入的待解帧的数据
**	输 出  参 数: DELU_Protocol *pProtoclData -- 解帧后的数据结构
**  返   回   值: NO_ERR
**	备		  注: 
*****************************************************************************************************/

uint8 METER_DELU_AnalDataFrame(DELU_Protocol *pProtoclData, uint8 *pRecFrame)
{
	uint8 *pTemp 		= pRecFrame;
	
	LOG_assert_param(pProtoclData == NULL);
	LOG_assert_param(pRecFrame == NULL);
	
	if(pProtoclData->MeterType == 0x20)
	{
		if(0x68 != *pTemp++)	return 1;	
		
		pProtoclData->MeterType = *pTemp++;										//仪表类型
		memcpy(pProtoclData->MeterAddr, pTemp, 7);								//仪表地址
		pTemp += 7;
		
		pProtoclData->ControlCode	= *pTemp++;									//控制码
		pProtoclData->Length		= *pTemp++;									//长度
		pProtoclData->DataIdentifier= (*pTemp++) | (*pTemp++ << 8);
		pProtoclData->SER			= *pTemp++;
		memcpy(pProtoclData->DataBuf, pTemp, (pProtoclData->Length-3));			//数据域数据
		pTemp += pProtoclData->Length-3;
	}
	else{
		
		return ERR;
	}

	return NO_ERR;
}

//德鲁热表数据格式结构体。
typedef struct{
	uint32   DailyHeat;		               /*结算日热量*/	
    uint8     DailyHeatUnit;
	uint32   CurrentHeat;				   /*当前热量*/
    uint8     CurrentHeatUnit;
	uint32 	 HeatPower;			      		/*热功率*/
    uint8     HeatPowerUnit;
	uint32 	 Flow;			                /*流量流速*/
    uint8 	 FlowUnit;
	uint32 	AccumulateFlow;				/*累积流量*/
    uint8 	AccumulateFlowUnit;	
	uint8	WaterInTemp[3];		       	 /*供水温度*/	
	uint8 	WaterOutTemp[3];				/*回水温度*/
    uint8 	AccumulateWorkTime[3];			/*累计工作时间*/
	uint8	RealTime[7];		                /*实时时间*/	
	uint16 	ST;					                    /*状态ST*/  
	}CJ188_Format;



CJ188_Data = METER_Data_To_CJ188Format(mf.ProtocolVer,ProtocoalInfo.DataBuf,sizeof(CJ188_Data) ,&err);
//把不同于德鲁热表数据格式的热表数据 调整成和德鲁格式一致
CJ188_Format  METER_Data_To_CJ188Format(uint8 ProtocolVer,uint8* DataBuf,uint8 len,uint8* err)
{
    CJ188_Format  MeterData={0,0x05,0,0x05,0,0x17,0,0x35,0,0x2c};
   
    
    switch(ProtocolVer)
      {
      case LYRB-USF:  /*乐业485 LYRB-USF*/
          {
			//把乐业协议数据调整成和德鲁格式一致
            break;
          }
       case WANHUA:  /*WANHUA 大表*/
          {
			//把万华协议数据调整成和德鲁格式一致
            
            break;
          } 
    
		 	//等等

	
      default:  //完全符合德鲁协议的处理。
          {
           memcpy(&MeterData,DataBuf,sizeof(MeterData));   /* 德鲁协议完全符合CJ188标准*/ 
           }
        break;
      }
    
   return MeterData; 
}


	

