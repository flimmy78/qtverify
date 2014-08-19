---------------------------------
--检定结果记录表
---------------------------------
drop table if exists "T_Verify_Record"
;
create table T_Verify_Record
(
F_ID integer not null primary key autoincrement,
F_TimeStamp timestamp not null,     --时间戳（'yyyy-MM-dd HH:mm:ss.zzz')
F_MeterNo varchar(16) not null,     --表号(14位数字: 6 + 8)
F_FlowPointIdx smallint not null,   --流量点索引，例如1,2,3,4...
F_FlowPoint float,                  --流量点数值，单位m3/h
F_TotalFlag smallint,               --总量检定标志，0：分量法；1：总量法
F_MeterValue0 float,                --热量表初值（体积或热量），单位L
F_MeterValue1 float,                --热量表终值（体积或热量），单位L
F_MeterDeltaV float,                --热量表示值（体积或热量），单位L，=(终值-初值)
F_BalWeight0 float,                 --天平初值（重量），单位kg
F_BalWeight1 float,                 --天平终值（重量），单位kg
F_BalDeltaW float,                  --天平示值（重量），单位kg，=(终值-初值)
F_InSlotTemper float,              	--恒温槽入口温度，单位℃(总量检定使用)
F_OutSlotTemper float,              --恒温槽出口温度，单位℃(总量检定使用)
F_PipeTemper float,                 --分配到每个表位的管路温度，单位℃(分量检定使用)
F_Density float,                    --密度，单位kg/L
F_StandValue float,                 --经过修正的标准值，体积(L)或热力
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
F_VerifyDate date,             	    --检定日期('2014-05-22')
F_EnvTemper float,                  --环境温度，单位℃
F_EnvHumidity float,                --环境湿度
F_AirPressure float,                --大气压力
F_ValidDate date,                   --检表结果有效期(生产型不需要)('2014-08-07')
F_RecordNumber interger,            --检定记录证书编号(每块表每次检定（多个流量点共用）形成一个编号)
constraint F_Model_fk foreign key(F_Model) references T_Meter_Model(F_ID),
constraint F_Standard_fk foreign key(F_Standard) references T_Meter_Standard(F_ID),
constraint F_MeterType_fk foreign key(F_MeterType) references T_Meter_Type(F_ID),
constraint F_ManufactDept_fk foreign key(F_ManufactDept) references T_Manufacture_Dept(F_ID),
constraint F_VerifyDept_fk foreign key(F_VerifyDept) references T_Verify_Dept(F_ID),
constraint F_VerifyPerson_fk foreign key(F_VerifyPerson) references T_User_Def_Tab(F_ID),
constraint F_CheckPerson_fk foreign key(F_CheckPerson) references T_User_Def_Tab(F_ID)
);
create unique index uk_T_Verify_Record on T_Verify_Record (F_MeterNo, F_TimeStamp, F_FlowPointIdx);


---------------------------------
--热表各规格的默认参数表
---------------------------------
drop table if exists "T_Meter_Default_Params"
;
create table T_Meter_Default_Params
(
	F_ID integer not null primary key autoincrement, 			-- 参数id
	F_StandardID integer,                                 -- 外键,表规格id(T_Meter_Standard.F_ID)
	F_Nflowpoint float,																		-- 常用流量点
	F_Upperflow float,																		-- 上限流量点		
	F_Verifyflow float,																		-- 检定流量点
	F_Flowquantity float,																	-- 检定量
	F_Pumpfrequencey float,																-- 水泵频率
	F_Valve_i smallint,																		-- 阀门编号	
	F_Seq_i smallint,																		  -- 检测序列号
  constraint F_StandardID_fk foreign key(F_StandardID) references T_Meter_Standard(F_ID)
);


---------------------------------
--表型号
---------------------------------
drop table if exists "T_Meter_Model"
;
create table T_Meter_Model
(
F_ID integer not null primary key autoincrement,  --型号ID
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Meter_Model(F_ID, F_Name, F_Desc) values(0, 'E-UWZ1', '型号1');
insert into T_Meter_Model(F_ID, F_Name, F_Desc) values(1, 'E-UWZ2', '型号2');
insert into T_Meter_Model(F_ID, F_Name, F_Desc) values(2, 'E-UWZ3', '型号3');


---------------------------------
--表规格
---------------------------------
drop table if exists "T_Meter_Standard"
;
create table T_Meter_Standard
(
F_ID integer not null primary key autoincrement, --规格ID
F_Name varchar(24),                     --规格代码
F_Meter_Quantity smallint						  -- 被检表的数量(2014.07.31 修改By Song baoshan)
);
insert into T_Meter_Standard(F_ID, F_Name, F_Meter_Quantity) values(0, 'DN15', 16);
insert into T_Meter_Standard(F_ID, F_Name, F_Meter_Quantity) values(1, 'DN20', 16);
insert into T_Meter_Standard(F_ID, F_Name, F_Meter_Quantity) values(2, 'DN25', 12);


---------------------------------
--表类型
---------------------------------
drop table if exists "T_Meter_Type"
;
create table T_Meter_Type
(
F_ID integer not null primary key autoincrement,
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
F_ID integer not null primary key autoincrement,
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Manufacture_Dept(F_ID, F_Name, F_Desc) values(0, 'SDM', '山东德鲁');
insert into T_Manufacture_Dept(F_ID, F_Name, F_Desc) values(1, 'SDJG', '烟台晶格');
insert into T_Manufacture_Dept(F_ID, F_Name, F_Desc) values(2, 'HYLY', '华仪乐业');


---------------------------------
--送检单位
---------------------------------
drop table if exists "T_Verify_Dept"
;
create table T_Verify_Dept
(
F_ID integer not null primary key autoincrement,
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Verify_Dept(F_ID, F_Name, F_Desc) values(0, 'SDJL', '山东计量院');
insert into T_Verify_Dept(F_ID, F_Name, F_Desc) values(1, 'QDJL', '青岛计量所');
insert into T_Verify_Dept(F_ID, F_Name, F_Desc) values(2, 'YTJL', '烟台计量所');


---------------------------------
--用户定义表
---------------------------------
drop table if exists "T_User_Def_Tab"
;
create table T_User_Def_Tab
(
F_ID integer not null primary key autoincrement,
F_Name varchar(24),
F_Desc varchar(60),
F_Password varchar(24),
F_RoleID smallint          --角色ID，外键(T_Role_Def_Tab)
);
insert into T_User_Def_Tab(F_ID, F_Name, F_Desc, F_Password, F_RoleID) values(0, 'admin', '管理员', 'admin', 0);
insert into T_User_Def_Tab(F_ID, F_Name, F_Desc, F_Password, F_RoleID) values(1, 'oper', '操作员', '1234', 1);


---------------------------------
--角色定义表
---------------------------------
drop table if exists "T_Role_Def_Tab"
;
create table T_Role_Def_Tab
(
F_ID integer not null primary key autoincrement,
F_Name varchar(24),
F_Desc varchar(60),
F_Func1 smallint,
F_Func2 smallint,
F_Func3 smallint
);
insert into T_Role_Def_Tab(F_ID, F_Name, F_Desc) values(0, 'root', '超级用户');
insert into T_Role_Def_Tab(F_ID, F_Name, F_Desc) values(1, 'common', '普通用户');


---------------------------------
--是否表
---------------------------------
drop table if exists "T_Yes_No_Tab"
;
create table T_Yes_No_Tab
(
F_ID integer not null primary key autoincrement,
F_Name varchar(8),
F_Desc varchar(12)
);
insert into T_Yes_No_Tab(F_ID, F_Name, F_Desc) values(0, 'No', '不合格');
insert into T_Yes_No_Tab(F_ID, F_Name, F_Desc) values(1, 'Yes', '合格');


---------------------------------
--热表各规格的默认参数表
---------------------------------
insert into t_meter_default_params values(1, 0, 1.5, 1.6, 1.5, 40, 34, 0, 1);
insert into t_meter_default_params values(2, 0, 1.5, 0.5, 0.45, 20, 33, 1, 2);
insert into t_meter_default_params values(3, 0, 1.5, 0.16, 0.15, 10, 33, 2, 3);
insert into t_meter_default_params values(4, 0, 1.5, 0.035, 0.03, 5, 33, 3, 4);
insert into t_meter_default_params values(5, 1, 2.5, 2.6, 2.5, 50, 34, 0, 1);
insert into t_meter_default_params values(6, 1, 2.5, 0.8, 0.75, 20, 33, 1, 2);
insert into t_meter_default_params values(7, 1, 2.5, 0.3, 0.25, 10, 33, 2, 3);
insert into t_meter_default_params values(8, 1, 2.5, 0.06, 0.05, 5, 33, 3, 4);
insert into t_meter_default_params values(9, 2, 3.5, 3.6, 3.5, 50, 34, 0, 1);
insert into t_meter_default_params values(10, 2, 3.5, 1.1, 1.05, 20, 33, 1, 2);
insert into t_meter_default_params values(11, 2, 3.5, 0.4, 0.35, 10, 33, 2, 3);
insert into t_meter_default_params values(12, 2, 3.5, 0.08, 0.07, 5, 33, 3, 4);

