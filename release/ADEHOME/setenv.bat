@echo off

:: ��ȡADEHOME��������
wmic ENVIRONMENT where "name='ADEHOME'" get UserName,VariableValue

:: ���û�������ADEHOME
wmic ENVIRONMENT create name="ADEHOME",username="<system>",VariableValue="%~dp0"
echo %ADEHOME%

:: ����path��������ֵ,����ADEHOME/bin;ADEHOME/dll
wmic ENVIRONMENT where "name='path' and username='<system>'" set VariableValue="%path%;%~dp0bin;%~dp0dll"


pause