---------------------------------
--流量检定结果记录表（包括质量法和标准表法）
---------------------------------
drop table if exists "T_Flow_Verify_Record"
;
create table T_Flow_Verify_Record
(
F_ID integer not null primary key autoincrement,
F_TimeStamp timestamp not null,     --时间戳（'yyyy-MM-dd HH:mm:ss.zzz')
F_MeterNo varchar(16) not null,     --表号(14位数字: 6 + 8)
F_FlowPointIdx smallint not null,   --流量点索引，例如1,2,3,4...
F_FlowPoint float,                  --流量点数值，单位m3/h
F_MethodFlag smallint,							--方法标志：0(质量法)；1(标准表法)
F_MeterValue0 float,                --热量表初值（体积），单位L
F_MeterValue1 float,                --热量表终值（体积），单位L
F_BalWeight0 float,                 --天平初值（重量），单位kg（质量法使用）
F_BalWeight1 float,                 --天平终值（重量），单位kg（质量法使用）
F_StdMeterV0 float,                 --标准表初值（体积），单位L（标准表法使用）
F_StdMeterV1 float,                 --标准表终值（体积），单位L（标准表法使用）
F_PipeTemper float,                 --分配到每个表位的温度，单位℃
F_Density float,                    --分配到每个表位的密度，单位kg/L
F_StandValue float,                 --经过修正的标准值，单位L
F_DispError float,                  --示值误差，单位%
F_StdError float,                   --要求误差(合格标准),单位%
F_Result smallint,               	  --检定结果(1：合格，0：不合格)
F_MeterPosNo smallint,              --表位号
F_Model integer,                    --表型号，外键(T_Meter_Model.F_ID)
F_Standard integer,                 --表规格(DN15/DN20/DN25)，外键(T_Meter_Standard.F_ID)
F_MeterType integer,                --表类型()，外键(T_Meter_Type.F_ID)
F_ManufactDept integer,             --制造单位，外键(T_Manufacture_Dept.F_ID)
F_VerifyDept integer,               --送检单位，外键(T_Verify_Dept.F_ID)
F_Grade smallint,                   --计量等级（1,2,3）
F_VerifyPerson integer,             --检定员，外键(T_User_Def_Tab.F_ID)
F_CheckPerson integer,              --核验员，外键(T_User_Def_Tab.F_ID)
F_DeviceInfoID integer,						--检定装置设备信息ID，外键(T_Verify_Device_Info.F_ID)
F_VerifyDate date,             	    --检定日期('2014-05-22')
F_ValidDate date,                   --检表结果有效期(生产型不需要)('2014-08-07')
F_EnvTemper float,                  --环境温度，单位℃
F_EnvHumidity float,                --环境湿度
F_AirPressure float,                --大气压力
F_CertNO varchar(16),               --检定证书编号(检表过程不写编号，留给用户以后填写)
F_FlowCoe float,								    --流量系数
F_Bak2 varchar(24),                 --备用域2
F_Bak3 varchar(24),                 --备用域3
F_Bak4 varchar(24),                 --备用域4
constraint F_Model_fk foreign key(F_Model) references T_Meter_Model(F_ID),
constraint F_Standard_fk foreign key(F_Standard) references T_Meter_Standard(F_ID),
constraint F_MeterType_fk foreign key(F_MeterType) references T_Meter_Type(F_ID),
constraint F_ManufactDept_fk foreign key(F_ManufactDept) references T_Manufacture_Dept(F_ID),
constraint F_VerifyDept_fk foreign key(F_VerifyDept) references T_Verify_Dept(F_ID),
constraint F_VerifyPerson_fk foreign key(F_VerifyPerson) references T_User_Def_Tab(F_ID),
constraint F_CheckPerson_fk foreign key(F_CheckPerson) references T_User_Def_Tab(F_ID),
constraint F_DeviceInfoID_fk foreign key(F_DeviceInfoID) references T_Verify_Device_Info(F_ID)
);
create unique index uk_T_Flow_Verify_Record on T_Flow_Verify_Record (F_MeterNo, F_TimeStamp, F_FlowPointIdx);


---------------------------------
--检定装置信息表
---------------------------------
drop table if exists "T_Verify_Device_Info"
;
create table T_Verify_Device_Info
(
F_ID integer not null primary key autoincrement,
F_DeviceName varchar(24) not null,     --标准装置名称（热量表检定装置）
F_DeviceNo varchar(24) not null,       --标准装置编号（SDM201280037)
F_DeviceModel varchar(20),						 --装置型号("RJZ32/80Z/B")
F_Manufact varchar(24),								 --制造厂商("德鲁计量")
F_DeviceGrade varchar(24),						 --装置的准确度等级("0.1% k=2")
F_MeasureRange varchar(24),						 --装置的测量范围("0.12-40.0(m3/h)")
F_CertNo smallint not null,     			 --标准装置证书编号
F_VerifyRule	varchar(20),						 --检定规程("JJG225-2001")
F_DeviceValidDate date,                --标准装置有效期('2014-08-07')
F_CertValidDate date,                  --证书有效期('2014-08-07')
F_RuleValidDate date,									 --计量标准考核证书有效期('2014-08-07')
F_Bak1 varchar(24),										 --备用域1
F_Bak2 varchar(24),                    --备用域2
F_Bak3 varchar(24),                    --备用域3
F_Bak4 varchar(24)                     --备用域4
);
create unique index uk_T_Verify_Device_Info on T_Verify_Device_Info (F_DeviceNo);

---------------------------------
--总量检定结果记录表（包括质量法和标准表法）
---------------------------------
drop table if exists "T_Total_Verify_Record"
;
create table T_Total_Verify_Record
(
F_ID integer not null primary key autoincrement,
F_TimeStamp timestamp not null,     --时间戳（'yyyy-MM-dd HH:mm:ss.zzz')
F_MeterNo varchar(16) not null,     --表号(14位数字: 6 + 8)
F_FlowPointIdx smallint not null,   --流量点索引，例如1,2,3,4...
F_FlowPoint float,                  --流量点数值，单位m3/h
F_MethodFlag smallint,							--方法标志：0(质量法)；1(标准表法)
F_MeterValue0 float,                --热量表初值（热量），单位kwh
F_MeterValue1 float,                --热量表终值（热量），单位kwh
F_BalWeight0 float,                 --天平初值（重量），单位kg（质量法使用）
F_BalWeight1 float,                 --天平终值（重量），单位kg（质量法使用）
F_StdMeterV0 float,                 --标准表初值（体积），单位L（标准表法使用）
F_StdMeterV1 float,                 --标准表终值（体积），单位L（标准表法使用）
F_InSlotTemper float,              	--恒温槽入口温度，单位℃
F_OutSlotTemper float,              --恒温槽出口温度，单位℃
F_PipeTemper float,                 --分配到每个表位的温度，单位℃
F_Density float,                    --分配到每个表位的密度，单位kg/L
F_StandValue float,                 --经过修正的标准值，单位kwh
F_DispError float,                  --示值误差，单位%
F_StdError float,                   --要求误差(合格标准),单位%
F_Result smallint,               	  --检定结果（1：合格，0：不合格）
F_MeterPosNo smallint,              --表位号
F_Model integer,                    --表型号，外键(T_Meter_Model.F_ID)
F_Standard integer,                 --表规格(DN15/DN20/DN25)，外键(T_Meter_Standard.F_ID)
F_MeterType integer,                --表类型()，外键(T_Meter_Type.F_ID)
F_ManufactDept integer,             --制造单位，外键(T_Manufacture_Dept.F_ID)
F_VerifyDept integer,               --送检单位，外键(T_Verify_Dept.F_ID)
F_Grade smallint,                   --计量等级（1,2,3）
F_VerifyPerson integer,             --检定员，外键(T_User_Def_Tab.F_ID)
F_CheckPerson integer,              --核验员，外键(T_User_Def_Tab.F_ID)
F_DeviceInfoID smallint,						--检定装置设备信息ID，外键(T_Verify_Device_Info.F_ID)
F_VerifyDate date,             	    --检定日期('2014-05-22')
F_ValidDate date,                   --检表结果有效期(生产型不需要)('2014-08-07')
F_EnvTemper float,                  --环境温度，单位℃
F_EnvHumidity float,                --环境湿度
F_AirPressure float,                --大气压力
F_CertNO varchar(16),               --检定证书编号(检表过程不写编号，留给用户以后填写)
F_Bak1 varchar(24),								  --备用域1
F_Bak2 varchar(24),                 --备用域2
F_Bak3 varchar(24),                 --备用域3
F_Bak4 varchar(24),                 --备用域4
constraint F_Model_fk foreign key(F_Model) references T_Meter_Model(F_ID),
constraint F_Standard_fk foreign key(F_Standard) references T_Meter_Standard(F_ID),
constraint F_MeterType_fk foreign key(F_MeterType) references T_Meter_Type(F_ID),
constraint F_ManufactDept_fk foreign key(F_ManufactDept) references T_Manufacture_Dept(F_ID),
constraint F_VerifyDept_fk foreign key(F_VerifyDept) references T_Verify_Dept(F_ID),
constraint F_VerifyPerson_fk foreign key(F_VerifyPerson) references T_User_Def_Tab(F_ID),
constraint F_CheckPerson_fk foreign key(F_CheckPerson) references T_User_Def_Tab(F_ID),
constraint F_DeviceInfoID_fk foreign key(F_DeviceInfoID) references T_Verify_Device_Info(F_ID)
);
create unique index uk_T_Total_Verify_Record on T_Total_Verify_Record (F_MeterNo, F_TimeStamp, F_FlowPointIdx);

