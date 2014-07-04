drop table t_meter_standard
;
create table t_meter_standard
(
id integer not null primary key autoincrement,
name varchar(8) not null
);
insert into t_meter_standard(id, name) values(0, 'DN15');
insert into t_meter_standard(id, name) values(1, 'DN20');
insert into t_meter_standard(id, name) values(2, 'DN25');


drop table t_meter_type
;
create table t_meter_type
(
id integer not null primary key autoincrement,
desc varchar(24) not null
);
insert into t_meter_type(id, desc) values(0, '机械表');
insert into t_meter_type(id, desc) values(1, '超声波表');


drop table t_manufacture_tab
;
create table t_manufacture_tab
(
id integer not null primary key autoincrement,
desc varchar(60) not null
);
insert into t_manufacture_tab(id, desc) values(0, '山东德鲁计量');
insert into t_manufacture_tab(id, desc) values(1, '烟台晶格仪表');
insert into t_manufacture_tab(id, desc) values(2, '华仪乐业');



drop table t_verify_record
;
create table t_verify_record
(
id integer not null primary key autoincrement,
meterNo interger not null,
flowPointIdx interger not null,
flowPoint float,
beginVolume float,
endVolume float,
dispVolume float,
weight0 float,
weight1 float,
deltaWeight float,
temperature float,
density float,
standVolume float,
dispError float,
stdError float,
result	interger,
meterPosNo interger,
standard varchar(8),
meterType varchar(24),
manufacture	varchar(60)
);
create unique index uk_t_verify_record on t_verify_record (meterNo, flowPointIdx);


drop table t_verify_record
;
create table t_verify_record
(
id integer not null primary key autoincrement,
meterNo interger not null,
flowpoint float,
beginVolume float
);
create unique index uk_t_verify_record on t_verify_record (meterNo, flowpoint);

insert into t_verify_record values(0, 1, 2.5, 50);
insert into t_verify_record values(1, 1, 0.75, 60);
insert into t_verify_record values(2, 1, 0.25, 70);
insert into t_verify_record values(3, 1, 0.05, 90);
insert into t_verify_record values(4, 1, 2.5, 50);
insert into t_verify_record values(5, 1, 2.5, 50);

