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


---------------------------------
--表规格
---------------------------------
drop table if exists "T_Meter_Standard"
;
create table T_Meter_Standard
(
F_ID integer not null primary key autoincrement,  --规格ID
F_Name varchar(24) not null                       --规格代码
);
insert into T_Meter_Standard(F_ID, F_Name) values(0, 'DN15');
insert into T_Meter_Standard(F_ID, F_Name) values(1, 'DN20');
insert into T_Meter_Standard(F_ID, F_Name) values(2, 'DN25');


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
drop table if exists "T_Manufacture_Unit"
;
create table T_Manufacture_Unit
(
F_ID integer not null primary key autoincrement,
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Manufacture_Unit(F_ID, F_Name, F_Desc) values(0, 'SDM', '山东德鲁');
insert into T_Manufacture_Unit(F_ID, F_Name, F_Desc) values(1, 'SDJG', '烟台晶格');
insert into T_Manufacture_Unit(F_ID, F_Name, F_Desc) values(2, 'HYLY', '华仪乐业');


---------------------------------
--送检单位
---------------------------------
drop table if exists "T_Verify_Unit"
;
create table T_Verify_Unit
(
F_ID integer not null primary key autoincrement,
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Verify_Unit(F_ID, F_Name, F_Desc) values(0, 'SDJL', '山东计量院');
insert into T_Verify_Unit(F_ID, F_Name, F_Desc) values(1, 'QDJL', '青岛计量所');
insert into T_Verify_Unit(F_ID, F_Name, F_Desc) values(2, 'YTJL', '烟台计量所');


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
F_RoleID interger          --角色ID，外键(T_Role_Def_Tab)
);
insert into T_User_Def_Tab(F_ID, F_Name, F_Desc, F_RoleID) values(0, 'admin', '管理员', 0);
insert into T_User_Def_Tab(F_ID, F_Name, F_Desc, F_RoleID) values(1, 'oper', '操作员', 1);


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
F_Func1 interger,
F_Func2 interger,
F_Func3 interger
);
insert into T_Role_Def_Tab(F_ID, F_Name, F_Desc) values(0, 'root', '超级用户');
insert into T_Role_Def_Tab(F_ID, F_Name, F_Desc) values(1, 'common', '普通用户');



---------------------------------
--检定结果记录表
---------------------------------
drop table if exists "T_Verify_Record"
;
create table T_Verify_Record
(
F_ID integer not null primary key autoincrement,
F_TimeStamp interger not null,      --时间戳（距离1970年1月1日的秒数，10位整数，例如1406043519）
F_MeterNo interger not null,        --表号
F_FlowPointIdx integer not null,    --流量点索引，例如1,2,3,4...
F_FlowPoint float,                  --流量点数值，单位m3/h
F_BeginVolume float,                --热量表初值（体积），单位L
F_EndVolume float,                  --热量表终值（体积），单位L
F_DeltaVolume float,                --热量表示值（体积），单位L，=(终值-初值)
F_BeginWeight float,                --天平初值（重量），单位kg
F_EndWeight float,                  --天平终值（重量），单位kg
F_DeltaWeight float,                --天平示值（重量），单位kg，=(终值-初值)
F_Temperature float,                --温度，单位℃
F_Density float,                    --密度，单位kg/L
F_StandVolume float,                --经过修正的标准体积，单位L
F_DispError float,                  --示值误差，单位%
F_StdError float,                   --要求误差(合格标准),单位%
F_Result	interger,                 --检定结果（1：合格，0：不合格）
F_MeterPosNo interger,              --表位号
F_Model integer,                    --表型号()，外键(T_Meter_Model)
F_Standard integer,                 --表规格(DN15/DN20/DN25)，外键(T_Meter_Standard)
F_MeterType integer,                --表类型()，外键(T_Meter_Type)
F_Manufacture	integer,              --制造单位，外键(T_Manufacture_Unit)
F_VerifyUnit integer,               --送检单位，外键(T_Verify_Unit)
F_Grade integer,                    --计量等级（1,2,3）
F_VerifyPerson integer,             --检定员，外键(T_User_Def_Tab)
F_CheckPerson integer,              --核验员，外键(T_User_Def_Tab)
F_Verify_Date	date                  --检定日期(20140522)
);
create unique index uk_T_Verify_Record on T_Verify_Record (F_MeterNo, F_TimeStamp, F_FlowPointIdx);
