
-----------------------------------------------------------------
--                    检定结果视图                           ----
-----------------------------------------------------------------
drop VIEW if exists "V_Flow_Verify_Record";
CREATE VIEW V_Flow_Verify_Record as
select 
  rid.[rowid],
  rec.F_ID,
  rec.F_TimeStamp,
  rec.F_MeterNo,
  rec.F_FlowPointIdx,
  rec.F_FlowPoint,
  rec.F_MethodFlag,
  rec.F_MeterValue0,
  rec.F_MeterValue1,                
  rec.F_BalWeight0,                 
  rec.F_BalWeight1,                 
  rec.F_StdMeterV0,                 
  rec.F_StdMeterV1,                 
  rec.F_PipeTemper,                 
  rec.F_Density,                    
  rec.F_StandValue,                 
  rec.F_DispError,                  
  rec.F_StdError,
  (case when (F_DispError<F_StdError and F_DispError>-F_StdError) then '合格'
        else '不合格'
   end) valid,                   
  rec.F_Result,                   
  rec.F_MeterPosNo,              
  rec.F_Model,
  mod.[F_Name] F_Model_en,
  mod.[F_Desc] F_Model_zh,                    
  std.f_name F_Standard,                  
  tp.[F_Name] F_MeterType_en,
  tp.[F_Desc] F_MeterType_zh,                
  manu.[F_Name] F_ManufactDept_en,
  manu.[F_Desc] F_ManufactDept_zh,              
  vdpt.[F_Name] F_VerifyDept_en,
  vdpt.[F_Desc] F_VerifyDept_zh,               
  rec.F_Grade,                   
  (select F_Desc from T_User_Def_Tab u where u.F_id = rec.[F_VerifyPerson])  F_VerifyPerson,           
  (select F_Desc from T_User_Def_Tab u where u.F_id = rec.[F_CheckPerson])  F_CheckPerson,            
  rec.F_DeviceInfoID,        
  rec.F_VerifyDate,                 
  rec.F_ValidDate,                   
  rec.F_EnvTemper,                  
  rec.F_EnvHumidity,                
  rec.F_AirPressure,                
  rec.F_CertNO,
  rec.F_FlowCoe,
  rec.F_DeviceName,   
  rec.F_DeviceNo,
  rec.F_DeviceModel,
  rec.F_Manufact,
  rec.F_DeviceGrade,
  rec.F_MeasureRange,
  rec.F_CertNo,
  rec.F_VerifyRule,
  rec.F_DeviceValidDate,
  rec.F_CertValidDate,
  rec.F_RuleValidDate   
from
   (
		select 
		  recj.*, 
		  d.[F_CertNo], 
		  d.[F_CertValidDate], 
		  d.[F_DeviceGrade], 
		  d.[F_DeviceModel], 
		  d.[F_DeviceName], 
		  d.[F_DeviceNo],
		  d.[F_DeviceValidDate],
		  d.[F_Manufact],
		  d.[F_MeasureRange],
		  d.[F_RuleValidDate],
		  d.[F_VerifyRule]
		from 
			T_Flow_Verify_Record recj 
		 left join 
			T_Verify_Device_Info d 
		 on   
			recj.F_DeviceInfoID=d.[F_ID]
    ) rec, 
   T_Meter_Model mod,
   T_meter_standard std,   
   T_Meter_Type tp,   
   T_manufacture_dept manu,   
   T_verify_dept vdpt,   
   v_flow_verify_meterno_rowid rid
where
   rec.[F_Standard]=std.[F_ID] and
   rec.[F_MeterType]=tp.[F_ID] and
   rec.[F_ManufactDept]=manu.[F_ID] and
   rec.[F_VerifyDept]=vdpt.[F_ID] and   
   rec.[F_Model]=mod.[F_ID] and   
   rec.[f_meterno]=rid.[F_MeterNo]
 order by rec.f_meterno, rec.f_timestamp
 ;
 
 -----------------------------------------------------------------
--                    检定结果视图中的rowID                   ----
------------------------------------------------------------------
drop view if exists "v_flow_verify_meterno_rowid";
create view v_flow_verify_meterno_rowid as
select 
distinct (
           select 
                  count(distinct f_meterno) + 1
           from v_flow_verify_record v1 
           where v1.[f_meterno] < v2.[F_MeterNo] 
         ) rowid, 
           v2.f_meterno  
from 
v_flow_verify_record v2