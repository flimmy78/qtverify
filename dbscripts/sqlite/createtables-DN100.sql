---------------------------------
--表规格
---------------------------------
insert into T_Meter_Standard(F_ID, F_Name, F_Meter_Quantity) values(6, 'DN65', 2);
insert into T_Meter_Standard(F_ID, F_Name, F_Meter_Quantity) values(7, 'DN80', 2);
insert into T_Meter_Standard(F_ID, F_Name, F_Meter_Quantity) values(8, 'DN100', 1);


---------------------------------
--热表各规格的默认参数表
---------------------------------
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
	F_Opening smallint,                     -- 调节阀开度
  constraint F_StandardID_fk foreign key(F_StandardID) references T_Meter_Standard(F_ID)
);

insert into T_Meter_Default_Params values(24, 6, 25,  30,    25,   450, 34, 0, 1, 50); --DN65
insert into T_Meter_Default_Params values(25, 6, 25,  7,     7.5,  150,  33, 1, 2, 50);
insert into T_Meter_Default_Params values(26, 6, 25,  1.05,  2.5,  60,  33, 2, 3, 50);
insert into T_Meter_Default_Params values(27, 6, 25,  0.15,  1,    30,  33, 3, 4, 50);

insert into T_Meter_Default_Params values(28, 7, 40,  30,    40,   1000, 34, 0, 1, 50); --DN80
insert into T_Meter_Default_Params values(29, 7, 40,  7,     12,   350,  33, 1, 2, 50);
insert into T_Meter_Default_Params values(30, 7, 40,  1.05,  4,    70,  33, 2, 3, 50);
insert into T_Meter_Default_Params values(31, 7, 40,  0.15,  1.6,  30,  33, 3, 4, 50);

insert into T_Meter_Default_Params values(32, 8, 60,  30,    60,   1500, 34, 0, 1, 50); --DN100
insert into T_Meter_Default_Params values(33, 8, 60,  7,     18,   400,  33, 1, 2, 50);
insert into T_Meter_Default_Params values(34, 8, 60,  1.05,  6,    100,  33, 2, 3, 50);
insert into T_Meter_Default_Params values(35, 8, 60,  0.15,  2.4,  90,  33, 3, 4, 50);

