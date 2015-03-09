
-----------------------------------------------------------------
--                    检定结果视图                           ----
-----------------------------------------------------------------
drop view if exists "V_Flow_Verify_Record"
;
create view V_Flow_Verify_Record as
select 
  r.F_ID,
  r.F_TimeStamp,
  r.F_MeterNo,
  r.F_FlowPointIdx,
  r.F_FlowPoint,
  r.F_MethodFlag,
  r.F_MeterValue0,
  r.F_MeterValue1,                
  r.F_BalWeight0,                 
  r.F_BalWeight1,                 
  r.F_StdMeterV0,                 
  r.F_StdMeterV1,                 
  r.F_PipeTemper,                 
  r.F_Density,                    
  r.F_StandValue,                 
  r.F_DispError,                  
  r.F_StdError,                   
  r.F_Result,                   
  r.F_MeterPosNo,              
  r.F_Model,                    
  r.F_Standard,                 
  r.F_MeterType,                
  r.F_ManufactDept,             
  r.F_VerifyDept,               
  r.F_Grade,                   
  r.F_VerifyPerson,             
  r.F_CheckPerson,              
  r.F_DeviceInfoID,        
  r.F_VerifyDate,                 
  r.F_ValidDate,                   
  r.F_EnvTemper,                  
  r.F_EnvHumidity,                
  r.F_AirPressure,                
  r.F_CertNO,
  m.F_Name model_name,
  s.F_Name stand_name,
  t.F_Name type_name,
  ma.F_Name manu_name,
  vde.F_Name verify_dept,
  u.F_Name user_name,
  dev.F_DeviceName,   
  dev.F_DeviceNo,
  dev.F_DeviceModel,
  dev.F_Manufact,
  dev.F_DeviceGrade,
  dev.F_MeasureRange,
  dev.F_CertNo,
  dev.F_VerifyRule,
  dev.F_DeviceValidDate,
  dev.F_CertValidDate,
  dev.F_RuleValidDate 
from
   T_Flow_Verify_Record r, 
   T_Meter_Model m, 
   T_Meter_Standard s, 
   T_Meter_Type t, 
   T_Manufacture_Dept ma, 
   T_Verify_Dept vde, 
   T_User_Def_Tab u, 
   T_Verify_Device_Info dev 
where
   r.[F_Model]=m.[F_ID] and   
   r.[F_Standard]=s.[F_ID] and   
   r.[F_MeterType]=t.[F_ID] and   
   r.[F_ManufactDept]=ma.[F_ID] and   
   r.[F_VerifyDept]=vde.[F_ID] and   
   r.[F_VerifyPerson]=u.[F_ID] and   
   r.[F_CheckPerson]=u.[F_ID]
 order by r.f_meterno, r.f_timestamp;