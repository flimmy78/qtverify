---------------------------------
--���ͺ�
---------------------------------
drop table T_Meter_Model
;
create table T_Meter_Model
(
F_ID integer not null primary key autoincrement,	--�ͺ�ID
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Meter_Model(F_ID, F_Name, F_Desc) values(0, 'E-UWZ', '�ͺ�1');


---------------------------------
--����
---------------------------------
drop table T_Meter_Standard
;
create table T_Meter_Standard
(
F_ID integer not null primary key autoincrement,	--���ID
F_Name varchar(24) not null 											--������
);
insert into T_Meter_Standard(F_ID, F_Name) values(0, 'DN15');
insert into T_Meter_Standard(F_ID, F_Name) values(1, 'DN20');
insert into T_Meter_Standard(F_ID, F_Name) values(2, 'DN25');


---------------------------------
--������
---------------------------------
drop table T_Meter_Type
;
create table T_Meter_Type
(
F_ID integer not null primary key autoincrement,
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Meter_Type(F_ID, F_Name, F_Desc) values(0, 'machine', '��е��');
insert into T_Meter_Type(F_ID, F_Name, F_Desc) values(1, 'supersonic', '��������');


---------------------------------
--���쵥λ
---------------------------------
drop table T_Manufacture_Unit
;
create table T_Manufacture_Unit
(
F_ID integer not null primary key autoincrement,
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Manufacture_Unit(F_ID, F_Name, F_Desc) values(0, 'SDM', 'ɽ����³����');
insert into T_Manufacture_Unit(F_ID, F_Name, F_Desc) values(1, 'SDJG', '��̨�����Ǳ�');
insert into T_Manufacture_Unit(F_ID, F_Name, F_Desc) values(2, 'HYLY', '������ҵ');


---------------------------------
--�ͼ쵥λ
---------------------------------
drop table T_Verify_Unit
;
create table T_Verify_Unit
(
F_ID integer not null primary key autoincrement,
F_Name varchar(24),
F_Desc varchar(60)
);
insert into T_Verify_Unit(F_ID, F_Name, F_Desc) values(0, 'SDJL', 'ɽ������Ժ');
insert into T_Verify_Unit(F_ID, F_Name, F_Desc) values(1, 'QDJL', '�ൺ������');
insert into T_Verify_Unit(F_ID, F_Name, F_Desc) values(2, 'YTJL', '��̨������');


---------------------------------
--�û������
---------------------------------
create table T_User_Def_Tab
(
F_ID integer not null primary key autoincrement,
F_Name varchar(24),
F_Desc varchar(60),
F_Password varchar(24),
F_RoleID interger					--��ɫID�����(T_Role_Def_Tab)
);
insert into T_User_Def_Tab(F_ID, F_Name, F_Desc, F_RoleID) values(0, 'admin', '����Ա', 0);
insert into T_User_Def_Tab(F_ID, F_Name, F_Desc, F_RoleID) values(1, 'oper', '����Ա', 1);


---------------------------------
--��ɫ�����
---------------------------------
create table T_Role_Def_Tab
(
F_ID integer not null primary key autoincrement,
F_Name varchar(24),
F_Desc varchar(60),
F_Func1 interger,
F_Func2 interger,
F_Func3 interger
);
insert into T_Role_Def_Tab(F_ID, F_Name, F_Desc) values(0, 'root', '�����û�');
insert into T_Role_Def_Tab(F_ID, F_Name, F_Desc) values(1, 'common', '��ͨ�û�');



---------------------------------
--�춨�����¼��
---------------------------------
drop table T_Verify_Record
;
create table T_Verify_Record
(
F_ID integer not null primary key autoincrement,
F_TimeStamp interger not null,			--ʱ���������1970��1��1�յ�������10λ����������1406043519��
F_MeterNo interger not null, 				--���
F_FlowPointIdx integer not null,		--����������������1,2,3,4...
F_FlowPoint float,									--��������ֵ����λm3/h
F_BeginVolume float,								--�������ֵ�����������λL
F_EndVolume float,									--��������ֵ�����������λL
F_DeltaVolume float,								--������ʾֵ�����������λL��=(��ֵ-��ֵ)
F_BeginWeight float,								--��ƽ��ֵ������������λkg
F_EndWeight float,									--��ƽ��ֵ������������λkg
F_DeltaWeight float,								--��ƽʾֵ������������λkg��=(��ֵ-��ֵ)
F_Temperature float,								--�¶ȣ���λ��
F_Density float,										--�ܶȣ���λkg/L
F_StandVolume float,								--���������ı�׼�������λL
F_DispError float,									--ʾֵ����λ%
F_StdError float,										--Ҫ�����(�ϸ��׼),��λ%
F_Result	interger,									--�춨�����1���ϸ�0�����ϸ�
F_MeterPosNo interger,							--��λ��
F_Model integer,										--���ͺ�()�����(T_Meter_Model)
F_Standard integer,									--����(DN15/DN20/DN25)�����(T_Meter_Standard)
F_MeterType integer,								--������()�����(T_Meter_Type)
F_Manufacture	integer,							--���쵥λ�����(T_Manufacture_Unit)
F_VerifyUnit integer,							  --�ͼ쵥λ�����(T_Verify_Unit)
F_Grade integer,										--�����ȼ���1,2,3��
F_VerifyPerson integer,						  --�춨Ա�����(T_User_Def_Tab)
F_CheckPerson integer,						  --����Ա�����(T_User_Def_Tab)
F_Verify_Date	date									--�춨����(20140522)
);
create unique index uk_T_Verify_Record on T_Verify_Record (F_MeterNo, F_TimeStamp, F_FlowPointIdx);
