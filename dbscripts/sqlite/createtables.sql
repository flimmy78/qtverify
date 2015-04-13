---------------------------------
--表规格
---------------------------------
drop table if exists "T_Meter_Standard"
;
create table T_Meter_Standard
(
F_ID integer not null primary key,  --规格ID
F_Name varchar(24),                 --规格代码
F_Meter_Quantity smallint           -- 被检表的数量(2014.07.31 修改By Song baoshan)
);
insert into T_Meter_Standard(F_ID, F_Name, F_Meter_Quantity) values(0, 'DN15', 16);
insert into T_Meter_Standard(F_ID, F_Name, F_Meter_Quantity) values(1, 'DN20', 16);
insert into T_Meter_Standard(F_ID, F_Name, F_Meter_Quantity) values(2, 'DN25', 12);


---------------------------------
--表型号
---------------------------------
drop table if exists "T_Meter_Model"
;
create table T_Meter_Model
(
F_ID integer not null primary key,  --型号ID
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Meter_Model(F_ID, F_Name, F_Desc) values(0, 'E-UWZ1', '型号1');
insert into T_Meter_Model(F_ID, F_Name, F_Desc) values(1, 'E-UWZ2', '型号2');
insert into T_Meter_Model(F_ID, F_Name, F_Desc) values(2, 'E-UWZ3', '型号3');


---------------------------------
--表类型
---------------------------------
drop table if exists "T_Meter_Type"
;
create table T_Meter_Type
(
F_ID integer not null primary key,
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Meter_Type(F_ID, F_Name, F_Desc) values(0, 'machine', '机械表');
insert into T_Meter_Type(F_ID, F_Name, F_Desc) values(1, 'supersonic', '超声波表');


---------------------------------
--制造单位
---------------------------------
drop table if exists "T_Manufacture_Dept"
;
create table T_Manufacture_Dept
(
F_ID integer not null primary key,
F_Name varchar(24),
F_Desc varchar(60),
F_NumPrefix varchar(6)
);
insert into T_Manufacture_Dept(F_ID, F_Name, F_Desc,F_NumPrefix) values(0, 'SDM', '山东德鲁','111100');
insert into T_Manufacture_Dept(F_ID, F_Name, F_Desc,F_NumPrefix) values(1, 'SDJG', '烟台晶格','111111');
insert into T_Manufacture_Dept(F_ID, F_Name, F_Desc,F_NumPrefix) values(2, 'HYLY', '华仪乐业','222222');


---------------------------------
--送检单位
---------------------------------
drop table if exists "T_Verify_Dept"
;
create table T_Verify_Dept
(
F_ID integer not null primary key,
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Verify_Dept(F_ID, F_Name, F_Desc) values(0, 'SDJL', '山东计量院');
insert into T_Verify_Dept(F_ID, F_Name, F_Desc) values(1, 'QDJL', '青岛计量所');
insert into T_Verify_Dept(F_ID, F_Name, F_Desc) values(2, 'YTJL', '烟台计量所');


---------------------------------
--角色定义表
---------------------------------
drop table if exists "T_Role_Def_Tab"
;
create table T_Role_Def_Tab
(
F_ID integer not null primary key,
F_Name varchar(24),
F_Desc varchar(60),
F_Func1 smallint,
F_Func2 smallint,
F_Func3 smallint
);
insert into T_Role_Def_Tab(F_ID, F_Name, F_Desc) values(0, 'root', '超级用户');
insert into T_Role_Def_Tab(F_ID, F_Name, F_Desc) values(1, 'common', '普通用户');


---------------------------------
--用户定义表
---------------------------------
drop table if exists "T_User_Def_Tab"
;
create table T_User_Def_Tab
(
F_ID integer not null primary key,
F_Name varchar(24),
F_Desc varchar(60),
F_Password varchar(24),
F_RoleID smallint          --角色ID，外键(T_Role_Def_Tab)
);
insert into T_User_Def_Tab(F_ID, F_Name, F_Desc, F_Password, F_RoleID) values(0, 'admin', '管理员', 'admin', 1);
insert into T_User_Def_Tab(F_ID, F_Name, F_Desc, F_Password, F_RoleID) values(1, 'oper', '操作员', '1234', 2);


---------------------------------
--是否表
---------------------------------
drop table if exists "T_Yes_No_Tab"
;
create table T_Yes_No_Tab
(
F_ID integer not null primary key,
F_Name varchar(8),
F_Desc varchar(12)
);
insert into T_Yes_No_Tab(F_ID, F_Name, F_Desc) values(0, 'No', '不合格');
insert into T_Yes_No_Tab(F_ID, F_Name, F_Desc) values(1, 'Yes', '合格');


---------------------------------
--热表各规格的默认参数表
---------------------------------
drop table if exists "T_Meter_Default_Params"
;
create table T_Meter_Default_Params
(
	F_ID integer not null primary key,      -- 参数id
	F_StandardID integer,                   -- 外键,表规格id(T_Meter_Standard.F_ID)
	F_NormalFlow float,                     -- 常用流量点
	F_UpperFlow float,                      -- 上限流量点		
	F_VerifyFlow float,                     -- 检定流量点
	F_FlowQuantity float,                   -- 检定量
	F_PumpFrequencey float,                 -- 水泵频率
	F_Valve_i smallint,                     -- 阀门编号	
	F_Seq_i smallint,                       -- 检测序列号
  constraint F_StandardID_fk foreign key(F_StandardID) references T_Meter_Standard(F_ID)
);
---------------------------------
--热表各规格的默认参数表
---------------------------------
insert into T_Meter_Default_Params values(0, 0, 1.5, 1.6, 1.5, 40, 34, 0, 1);
insert into T_Meter_Default_Params values(1, 0, 1.5, 0.5, 0.45, 20, 33, 1, 2);
insert into T_Meter_Default_Params values(2, 0, 1.5, 0.16, 0.15, 10, 33, 2, 3);
insert into T_Meter_Default_Params values(3, 0, 1.5, 0.035, 0.03, 5, 33, 3, 4);
insert into T_Meter_Default_Params values(4, 1, 2.5, 2.6, 2.5, 50, 34, 0, 1);
insert into T_Meter_Default_Params values(5, 1, 2.5, 0.8, 0.75, 20, 33, 1, 2);
insert into T_Meter_Default_Params values(6, 1, 2.5, 0.3, 0.25, 10, 33, 2, 3);
insert into T_Meter_Default_Params values(7, 1, 2.5, 0.06, 0.05, 5, 33, 3, 4);
insert into T_Meter_Default_Params values(8, 2, 3.5, 3.6, 3.5, 50, 34, 0, 1);
insert into T_Meter_Default_Params values(9, 2, 3.5, 1.1, 1.05, 20, 33, 1, 2);
insert into T_Meter_Default_Params values(10, 2, 3.5, 0.4, 0.35, 10, 33, 2, 3);
insert into T_Meter_Default_Params values(11, 2, 3.5, 0.08, 0.07, 5, 33, 3, 4);


---------------------------------
--检定装置信息表
---------------------------------
drop table if exists "T_Verify_Device_Info"
;
create table T_Verify_Device_Info
(
F_ID integer not null primary key,
F_DeviceName varchar(24) not null,     --标准装置名称（热量表检定装置）
F_DeviceNo varchar(24) not null,       --标准装置编号（SDM201280037)
F_DeviceModel varchar(20),             --装置型号("RJZ32/80Z/B")
F_Manufact varchar(24),                --制造厂商("德鲁计量")
F_DeviceGrade varchar(24),             --装置的准确度等级("0.1% k=2")
F_MeasureRange varchar(24),            --装置的测量范围("0.12-40.0(m3/h)")
F_CertNo smallint not null,            --标准装置证书编号
F_VerifyRule varchar(20),              --检定规程("JJG225-2001")
F_DeviceValidDate date,                --标准装置有效期('2014-08-07')
F_CertValidDate date,                  --证书有效期('2014-08-07')
F_RuleValidDate date,                  --计量标准考核证书有效期('2014-08-07')
F_Bak1 varchar(24),                    --备用域1
F_Bak2 varchar(24),                    --备用域2
F_Bak3 varchar(24),                    --备用域3
F_Bak4 varchar(24)                     --备用域4
);
create unique index uk_T_Verify_Device_Info on T_Verify_Device_Info (F_DeviceNo);


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
F_MethodFlag smallint,              --方法标志：0(质量法)；1(标准表法)
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
F_Result smallint,                  --检定结果(1：合格，0：不合格)
F_MeterPosNo smallint,              --表位号
F_Model integer,                    --表型号，外键(T_Meter_Model.F_ID)
F_Standard integer,                 --表规格(DN15/DN20/DN25)，外键(T_Meter_Standard.F_ID)
F_MeterType integer,                --表类型()，外键(T_Meter_Type.F_ID)
F_ManufactDept integer,             --制造单位，外键(T_Manufacture_Dept.F_ID)
F_VerifyDept integer,               --送检单位，外键(T_Verify_Dept.F_ID)
F_Grade smallint,                   --计量等级（1,2,3）
F_VerifyPerson integer,             --检定员，外键(T_User_Def_Tab.F_ID)
F_CheckPerson integer,              --核验员，外键(T_User_Def_Tab.F_ID)
F_DeviceInfoID integer,             --检定装置设备信息ID，外键(T_Verify_Device_Info.F_ID)
F_VerifyDate date,             	    --检定日期('2014-05-22')
F_ValidDate date,                   --检表结果有效期(生产型不需要)('2014-08-07')
F_EnvTemper float,                  --环境温度，单位℃
F_EnvHumidity float,                --环境湿度
F_AirPressure float,                --大气压力
F_CertNO varchar(16),               --检定证书编号(检表过程不写编号，留给用户以后填写)
F_FlowCoe float,                    --流量系数
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
F_MethodFlag smallint,              --方法标志：0(质量法)；1(标准表法)
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
F_Result smallint,                  --检定结果（1：合格，0：不合格）
F_MeterPosNo smallint,              --表位号
F_Model integer,                    --表型号，外键(T_Meter_Model.F_ID)
F_Standard integer,                 --表规格(DN15/DN20/DN25)，外键(T_Meter_Standard.F_ID)
F_MeterType integer,                --表类型()，外键(T_Meter_Type.F_ID)
F_ManufactDept integer,             --制造单位，外键(T_Manufacture_Dept.F_ID)
F_VerifyDept integer,               --送检单位，外键(T_Verify_Dept.F_ID)
F_Grade smallint,                   --计量等级（1,2,3）
F_VerifyPerson integer,             --检定员，外键(T_User_Def_Tab.F_ID)
F_CheckPerson integer,              --核验员，外键(T_User_Def_Tab.F_ID)
F_DeviceInfoID integer,             --检定装置设备信息ID，外键(T_Verify_Device_Info.F_ID)
F_VerifyDate date,             	    --检定日期('2014-05-22')
F_ValidDate date,                   --检表结果有效期(生产型不需要)('2014-08-07')
F_EnvTemper float,                  --环境温度，单位℃
F_EnvHumidity float,                --环境湿度
F_AirPressure float,                --大气压力
F_CertNO varchar(16),               --检定证书编号(检表过程不写编号，留给用户以后填写)
F_Bak1 varchar(24),                 --备用域1
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


---------------------------------
--铂电阻检定结果记录表
---------------------------------
drop table if exists "T_Platinium_Verify_Record"
;
create table T_Platinium_Verify_Record
(
	F_ID	integer not null primary key autoincrement,
	F_TimeStamp timestamp not null,     --时间戳（'yyyy-MM-dd HH:mm:ss.zzz')
	F_CompOrParam						--比较法或参数法, 0-比较法, 1-参数法
	F_PlaManufactDept integer,          --被检铂电阻制造单位，外键(T_Manufacture_Dept.F_ID)
	F_Standard integer,                 --表规格(DN15/DN20/DN25)，外键(T_Meter_Standard.F_ID)
	F_Model integer,                    --表型号，外键(T_Meter_Model.F_ID)
	F_ManufactDept integer,             --热量表制造单位，外键(T_Manufacture_Dept.F_ID)
	F_VerifyDept integer,               --送检单位，外键(T_Verify_Dept.F_ID)
	F_VerifyPerson integer,             --检定员，外键(T_User_Def_Tab.F_ID)
	F_CheckPerson integer,              --核验员，外键(T_User_Def_Tab.F_ID)
	F_MinTmpDiff float,					--最小温差, 参数
	F_TmpDiff float,					--检测温差
	F_StdInRresis float,				--标准温度计进口电阻值
	F_StdOutRresis float,				--标准温度计出口电阻值
	F_StdInTmp float,					--标准温度计进口电温度
	F_StdOutTmp float,					--标准温度计出口电温度
	F_PlaSerial integer,				--被检铂电阻序列号
	F_PlaInRresis float,				--被检铂电阻进口电阻值
	F_PlaOutRresis float,				--被检铂电阻出口电阻值
	F_PlaParamR0 float,					--被检铂电阻0℃电阻值
	F_PlaCoeA float,					--被检铂电阻系数A
	F_PlaCoeB float,					--被检铂电阻系数B
	F_PlaCoeC float,					--被检铂电阻系数C
	F_InErr	float,						--被检铂电阻进口误差限(℃ %)
	F_OutErr	float,					--被检铂电阻进口误差限(℃ %)
	F_MaxErrPoint float,				--最大误差点
	constraint F_Model_fk foreign key(F_Model) references T_Meter_Model(F_ID),
	constraint F_Standard_fk foreign key(F_Standard) references T_Meter_Standard(F_ID),
	constraint F_ManufactDept_fk foreign key(F_ManufactDept) references T_Manufacture_Dept(F_ID),
	constraint F_VerifyDept_fk foreign key(F_VerifyDept) references T_Verify_Dept(F_ID),
	constraint F_VerifyPerson_fk foreign key(F_VerifyPerson) references T_User_Def_Tab(F_ID),
	constraint F_CheckPerson_fk foreign key(F_CheckPerson) references T_User_Def_Tab(F_ID)
);