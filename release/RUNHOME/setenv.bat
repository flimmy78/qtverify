@echo off

:: 获取ADEHOME环境变量
wmic ENVIRONMENT where "name='ADEHOME'" get UserName,VariableValue

:: 设置环境变量ADEHOME
wmic ENVIRONMENT create name="ADEHOME",username="<system>",VariableValue="%~dp0"
echo %ADEHOME%

:: 更改path环境变量值,新增ADEHOME/bin;ADEHOME/dll
wmic ENVIRONMENT where "name='path' and username='<system>'" set VariableValue="%path%;%~dp0bin;%~dp0dll"


pause