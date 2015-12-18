#include <QFileDialog>
#include <QDesktopServices>
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include "algorithm.h"
#include "qexcel.h"
#include "pseudo.h"

CPseudoDlg::CPseudoDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui = NULL;
	m_config = NULL;
	m_prameterPtr = NULL;
	m_book = NULL;
	m_sheet = NULL;
	m_format = NULL;
	m_font = NULL;
}

CPseudoDlg::~CPseudoDlg()
{

}

void CPseudoDlg::showEvent(QShowEvent *event)
{
	ui = new Ui::PseudoDlgClass;
	ui->setupUi(this);
	m_prameterPtr = new ReportConfigStr;
	memset(m_prameterPtr, 0, sizeof(ReportConfigStr));
	m_config = new QSettings("config.ini", QSettings::IniFormat);
	installConfig();
}

void CPseudoDlg::closeEvent(QCloseEvent * event)
{
	saveConfig();
	if (ui)
	{
		delete ui;
		ui = NULL;
	}

	if(m_config)
	{
		delete m_config;
		m_config = NULL;
	}

	if (m_prameterPtr)
	{
		delete m_prameterPtr;
		m_prameterPtr = NULL;
	}

	if (m_book)
	{
		m_book->release();//release all resources including sheet, format and font
		m_book = NULL;
	}
	if (m_sheet)
	{
		m_sheet = NULL;
	}
	if (m_format)
	{
		m_format = NULL;
	}
	if (m_font)
	{
		m_font = NULL;
	}
}

void CPseudoDlg::installConfig()
{
	ui->lineEdit_MeterCount->setText(m_config->value("meterCount").toString());
	ui->lineEdit_StartRow->setText(m_config->value("dataStartRow").toString());
	ui->lineEdit_NormalFlowRate->setText(m_config->value("NormalFlowRate").toString());
	ui->lineEdit_MinDiffTemp->setText(m_config->value("MinDiffTemp").toString());

	ui->lineEditHTemp_BRate->setText(m_config->value("HTemp_BRate").toString());
	ui->lineEditLTemp_BRate->setText(m_config->value("LTemp_BRate").toString());
	ui->lineEditPTemp_BRate->setText(m_config->value("PTemp_BRate").toString());
	ui->lineEditQuantity_BRate->setText(m_config->value("Quantity_BRate").toString());
	ui->lineEditFlowPoint_BRate->setText(m_config->value("FlowPoint_BRate").toString());

	ui->lineEditHTemp_MRate->setText(m_config->value("HTemp_MRate").toString());
	ui->lineEditLTemp_MRate->setText(m_config->value("LTemp_MRate").toString());
	ui->lineEditPTemp_MRate->setText(m_config->value("PTemp_MRate").toString());
	ui->lineEditQuantity_MRate->setText(m_config->value("Quantity_MRate").toString());
	ui->lineEditFlowPoint_MRate->setText(m_config->value("FlowPoint_MRate").toString());

	ui->lineEditHTemp_SRate->setText(m_config->value("HTemp_SRate").toString());
	ui->lineEditLTemp_SRate->setText(m_config->value("LTemp_SRate").toString());
	ui->lineEditPTemp_SRate->setText(m_config->value("PTemp_SRate").toString());
	ui->lineEditQuantity_SRate->setText(m_config->value("Quantity_SRate").toString());
	ui->lineEditFlowPoint_SRate->setText(m_config->value("FlowPoint_SRate").toString());

	ui->lineEdit_Seq->setText(m_config->value("col_Seq").toString());
	ui->lineEdit_RecNo->setText(m_config->value("col_RecNo").toString());
	ui->lineEdit_MeterNo->setText(m_config->value("col_MeterNo").toString());
	ui->lineEdit_FLowPoint->setText(m_config->value("col_FLowPoint").toString());
	ui->lineEdit_InTemp->setText(m_config->value("col_InTemp").toString());
	ui->lineEdit_OutTemp->setText(m_config->value("col_OutTemp").toString());
	ui->lineEdit_DiffTemp->setText(m_config->value("col_DiffTemp").toString());
	ui->lineEdit_MeterE0->setText(m_config->value("col_MeterE0").toString());
	ui->lineEdit_MeterE1->setText(m_config->value("col_MeterE1").toString());
	ui->lineEdit_MeterE->setText(m_config->value("col_MeterE").toString());
	ui->lineEdit_BalMass->setText(m_config->value("col_BalMass").toString());
	ui->lineEdit_PipeTemp->setText(m_config->value("col_PipeTemp").toString());
	ui->lineEdit_Density->setText(m_config->value("col_Density").toString());
	ui->lineEdit_StandE->setText(m_config->value("col_StandE").toString());
	ui->lineEdit_Err->setText(m_config->value("col_Err").toString());
	ui->lineEdit_ErrLmt->setText(m_config->value("col_ErrLmt").toString());
	ui->lineEdit_Result->setText(m_config->value("col_Result").toString());
	ui->gBox_BRate->setChecked(m_config->value("inuse_BRate").toBool());
	ui->gBox_MRate->setChecked(m_config->value("inuse_MRate").toBool());
	ui->gBox_SRate->setChecked(m_config->value("inuse_SRate").toBool());

	freshConfig();
}

void CPseudoDlg::freshConfig()
{
	m_prameterPtr->meterCount      = ui->lineEdit_MeterCount->text().toInt();
	m_prameterPtr->dataStartRow    = ui->lineEdit_StartRow->text().toInt();//因为libxl要插入一行logo, 所以行数要多一个
	m_prameterPtr->normalFlowRate  = ui->lineEdit_NormalFlowRate->text().toFloat();
	m_prameterPtr->minDiffTemp     = ui->lineEdit_MinDiffTemp->text().toFloat();

	m_prameterPtr->HTemp_BRate     = ui->lineEditHTemp_BRate->text().toFloat();
	m_prameterPtr->LTemp_BRate     = ui->lineEditLTemp_BRate->text().toFloat();
	m_prameterPtr->PTemp_BRate	   = ui->lineEditPTemp_BRate->text().toFloat();
	m_prameterPtr->Quantity_BRate  = ui->lineEditQuantity_BRate->text().toFloat();
	m_prameterPtr->FlowPoint_BRate = ui->lineEditFlowPoint_BRate->text().toFloat();

	m_prameterPtr->HTemp_MRate     = ui->lineEditHTemp_MRate->text().toFloat();
	m_prameterPtr->LTemp_MRate     = ui->lineEditLTemp_MRate->text().toFloat();
	m_prameterPtr->PTemp_MRate	   = ui->lineEditPTemp_MRate->text().toFloat();
	m_prameterPtr->Quantity_MRate  = ui->lineEditQuantity_MRate->text().toFloat();
	m_prameterPtr->FlowPoint_MRate = ui->lineEditFlowPoint_MRate->text().toFloat();

	m_prameterPtr->HTemp_SRate     = ui->lineEditHTemp_SRate->text().toFloat();
	m_prameterPtr->LTemp_SRate     = ui->lineEditLTemp_SRate->text().toFloat();
	m_prameterPtr->PTemp_SRate	   = ui->lineEditPTemp_SRate->text().toFloat();
	m_prameterPtr->Quantity_SRate  = ui->lineEditQuantity_SRate->text().toFloat();
	m_prameterPtr->FlowPoint_SRate = ui->lineEditFlowPoint_SRate->text().toFloat();

	m_prameterPtr->col_Seq         = ui->lineEdit_Seq->text().toInt()-1;
	m_prameterPtr->col_RecNo       = ui->lineEdit_RecNo->text().toInt()-1;
	m_prameterPtr->col_MeterNo     = ui->lineEdit_MeterNo->text().toInt()-1;
	m_prameterPtr->col_FLowPoint   = ui->lineEdit_FLowPoint->text().toInt()-1;
	m_prameterPtr->col_InTemp      = ui->lineEdit_InTemp->text().toInt()-1;
	m_prameterPtr->col_OutTemp     = ui->lineEdit_OutTemp->text().toInt()-1;
	m_prameterPtr->col_DiffTemp    = ui->lineEdit_DiffTemp->text().toInt()-1;
	m_prameterPtr->col_MeterE0     = ui->lineEdit_MeterE0->text().toInt()-1;
	m_prameterPtr->col_MeterE1     = ui->lineEdit_MeterE1->text().toInt()-1;
	m_prameterPtr->col_MeterE      = ui->lineEdit_MeterE->text().toInt()-1;
	m_prameterPtr->col_BalMass	   = ui->lineEdit_BalMass->text().toInt()-1;
	m_prameterPtr->col_PipeTemp    = ui->lineEdit_PipeTemp->text().toInt()-1;
	m_prameterPtr->col_Density     = ui->lineEdit_Density->text().toInt()-1;
	m_prameterPtr->col_StandE      = ui->lineEdit_StandE->text().toInt()-1;
	m_prameterPtr->col_Err         = ui->lineEdit_Err->text().toInt()-1;
	m_prameterPtr->col_ErrLmt      = ui->lineEdit_ErrLmt->text().toInt()-1;
	m_prameterPtr->col_Result      = ui->lineEdit_Result->text().toInt()-1;

	mapFlowPoints();
}

void CPseudoDlg::mapFlowPoints()
{
	m_mapFlowPoint[BIG_RATE_ROW_OFFSET] = m_prameterPtr->FlowPoint_BRate;
	m_mapFlowPoint[MID_RATE_ROW_OFFSET] = m_prameterPtr->FlowPoint_MRate;
	m_mapFlowPoint[SML_RATE_ROW_OFFSET] = m_prameterPtr->FlowPoint_SRate;

	m_mapHTemp[BIG_RATE_ROW_OFFSET] = m_prameterPtr->HTemp_BRate;
	m_mapHTemp[MID_RATE_ROW_OFFSET] = m_prameterPtr->HTemp_MRate;
	m_mapHTemp[SML_RATE_ROW_OFFSET] = m_prameterPtr->HTemp_SRate;	
		
	m_mapLTemp[BIG_RATE_ROW_OFFSET] = m_prameterPtr->LTemp_BRate;
	m_mapLTemp[MID_RATE_ROW_OFFSET] = m_prameterPtr->LTemp_MRate;
	m_mapLTemp[SML_RATE_ROW_OFFSET] = m_prameterPtr->LTemp_SRate;

	m_mapPTemp[BIG_RATE_ROW_OFFSET] = m_prameterPtr->PTemp_BRate;
	m_mapPTemp[MID_RATE_ROW_OFFSET] = m_prameterPtr->PTemp_MRate;
	m_mapPTemp[SML_RATE_ROW_OFFSET] = m_prameterPtr->PTemp_SRate;

	m_mapVerifyMass[BIG_RATE_ROW_OFFSET] = m_prameterPtr->Quantity_BRate;
	m_mapVerifyMass[MID_RATE_ROW_OFFSET] = m_prameterPtr->Quantity_MRate;
	m_mapVerifyMass[SML_RATE_ROW_OFFSET] = m_prameterPtr->Quantity_SRate;
}

void CPseudoDlg::saveConfig()
{
	if (!chkFlowPoints())
	{
		QMessageBox::warning(this, tr("Select"), tr("选择的流量点不合理!"));
		return;
	}

	m_config->setValue("meterCount",ui->lineEdit_MeterCount->text());
	m_config->setValue("dataStartRow",ui->lineEdit_StartRow->text());
	m_config->setValue("NormalFlowRate",ui->lineEdit_NormalFlowRate->text());
	m_config->setValue("MinDiffTemp",ui->lineEdit_MinDiffTemp->text());

	m_config->setValue("HTemp_BRate",ui->lineEditHTemp_BRate->text());
	m_config->setValue("LTemp_BRate",ui->lineEditLTemp_BRate->text());
	m_config->setValue("PTemp_BRate",ui->lineEditPTemp_BRate->text());
	m_config->setValue("Quantity_BRate",ui->lineEditQuantity_BRate->text());
	m_config->setValue("FlowPoint_BRate",ui->lineEditFlowPoint_BRate->text());

	m_config->setValue("HTemp_MRate",ui->lineEditHTemp_MRate->text());
	m_config->setValue("LTemp_MRate",ui->lineEditLTemp_MRate->text());
	m_config->setValue("PTemp_MRate",ui->lineEditPTemp_MRate->text());
	m_config->setValue("Quantity_MRate",ui->lineEditQuantity_MRate->text());
	m_config->setValue("FlowPoint_MRate",ui->lineEditFlowPoint_MRate->text());

	m_config->setValue("HTemp_SRate",ui->lineEditHTemp_SRate->text());
	m_config->setValue("LTemp_SRate",ui->lineEditLTemp_SRate->text());
	m_config->setValue("PTemp_SRate",ui->lineEditPTemp_SRate->text());
	m_config->setValue("Quantity_SRate",ui->lineEditQuantity_SRate->text());
	m_config->setValue("FlowPoint_SRate",ui->lineEditFlowPoint_SRate->text());

	m_config->setValue("col_Seq",ui->lineEdit_Seq->text());
	m_config->setValue("col_RecNo",ui->lineEdit_RecNo->text());
	m_config->setValue("col_MeterNo",ui->lineEdit_MeterNo->text());
	m_config->setValue("col_FLowPoint",ui->lineEdit_FLowPoint->text());
	m_config->setValue("col_InTemp",ui->lineEdit_InTemp->text());
	m_config->setValue("col_OutTemp",ui->lineEdit_OutTemp->text());
	m_config->setValue("col_DiffTemp",ui->lineEdit_DiffTemp->text());
	m_config->setValue("col_MeterE0",ui->lineEdit_MeterE0->text());
	m_config->setValue("col_MeterE1",ui->lineEdit_MeterE1->text());
	m_config->setValue("col_MeterE",ui->lineEdit_MeterE->text());
	m_config->setValue("col_BalMass",ui->lineEdit_BalMass->text());
	m_config->setValue("col_PipeTemp",ui->lineEdit_PipeTemp->text());
	m_config->setValue("col_Density",ui->lineEdit_Density->text());
	m_config->setValue("col_StandE",ui->lineEdit_StandE->text());
	m_config->setValue("col_Err",ui->lineEdit_Err->text());
	m_config->setValue("col_ErrLmt",ui->lineEdit_ErrLmt->text());
	m_config->setValue("col_Result",ui->lineEdit_Result->text());
	m_config->setValue("inuse_BRate", ui->gBox_BRate->isChecked());
	m_config->setValue("inuse_MRate", ui->gBox_MRate->isChecked());
	m_config->setValue("inuse_SRate", ui->gBox_SRate->isChecked());
	freshConfig();
}

bool CPseudoDlg::chkFlowPoints()
{
	m_writeFlowPoints = 0;
	if (ui->gBox_BRate->isChecked())
	{
		m_writeFlowPoints++;
	}
	if (ui->gBox_MRate->isChecked())
	{
		m_writeFlowPoints++;
	}
	if (ui->gBox_SRate->isChecked())
	{
		m_writeFlowPoints++;
	}
	return (m_writeFlowPoints == 2);
}

void CPseudoDlg::on_btn_Exit_clicked()
{
	this->close();
}

void CPseudoDlg::on_btn_SaveConfig_clicked()
{
	saveConfig();
}

void CPseudoDlg::on_btn_FileList_clicked()
{
	m_excelFiles.clear();
	m_excelFiles = QFileDialog::getOpenFileNames(this, tr("Select Files"), QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation), tr("Microsoft Excel (*.xls)"));
}

void CPseudoDlg::on_btn_Export_clicked()
{
	freshConfig();
	disableInputs();
	initWriteFp();
	exportReports();
	QMessageBox::about(this, "OK", "done");
}

/*
* 已检测用户确实选择的是两个流量点后
* 把这两个流量点加入写入队列
*/
void CPseudoDlg::initWriteFp()
{
	m_fpList.clear();
	if (ui->gBox_BRate->isChecked())
	{
		m_fpList.append(BIG_RATE_ROW_OFFSET);
	}
	if (ui->gBox_MRate->isChecked())
	{
		m_fpList.append(MID_RATE_ROW_OFFSET);
	}
	if (ui->gBox_SRate->isChecked())
	{
		m_fpList.append(SML_RATE_ROW_OFFSET);
	}
}

//开始导数据时, 不允许再更改参数
void CPseudoDlg::disableInputs()
{

}

void CPseudoDlg::exportReports()
{
	QString filename;
	for(int i=0; i<m_excelFiles.count(); i++)
	{
		filename = m_excelFiles[i];
		exportReport(filename);
	}
}

void CPseudoDlg::exportReport(QString filename)
{
	insertLogoRow(filename);
	LoadExcel(filename);
	insertRows();
	int RowNum = 0;
	for (int i=1;i<=m_prameterPtr->meterCount;i++)
	{
		RowNum = getStartRowNum(i);
		writeSingleRow(m_fpList[0], RowNum+1);
		writeSingleRow(m_fpList[1], RowNum+2);
		mergeCells(i);
	}
	deleteLog(filename);
	saveExcel(filename.replace(".xls",".result.xls"));
	deleteLog(filename);
}

void CPseudoDlg::insertRows()
{
	for (int i=1;i<=m_prameterPtr->meterCount;i++)
	{
		m_sheet->insertRow(getStartRowNum(i)+1,  getStartRowNum(i)+2);
	}
}

void CPseudoDlg::writeSingleRow(flowPointEnum flowPoint, int RowNum)
{
	float highTemp = getHighTemp(flowPoint);
	float lowTemp  = getLowTemp(flowPoint);
	float pipeTemp = getPipeTemp(flowPoint);
	float flowRate = getFlowPoint(flowPoint);
	float mass	   = getBalanceMass(flowPoint);

	float errLmt = getErrLmt(highTemp-lowTemp, MAP_FP(m_mapFlowPoint));
	float err    = getErr(errLmt);
	float stdEnergy = getStdEnergy(highTemp, lowTemp, mass);
	float dispEnergy = getMeterEnergy(stdEnergy, err);
	float pipeDensity = getPipeDensity(pipeTemp);

	m_sheet->writeStr(RowNum, m_prameterPtr->col_InTemp, FLOAT_TO_CHAR(highTemp), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_OutTemp, FLOAT_TO_CHAR(lowTemp), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_DiffTemp, FLOAT_TO_CHAR(highTemp - lowTemp), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_FLowPoint, FLOAT_TO_CHAR(flowRate), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_MeterE0, FLOAT_TO_CHAR(0), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_MeterE1, FLOAT_TO_CHAR(dispEnergy), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_MeterE, FLOAT_TO_CHAR(dispEnergy), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_BalMass, FLOAT_TO_CHAR(mass), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_PipeTemp, FLOAT_TO_CHAR(pipeTemp), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_Density, FLOAT_TO_CHAR(pipeDensity), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_StandE, FLOAT_TO_CHAR(stdEnergy), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_Err, FLOAT_TO_CHAR(err), m_format);
	m_sheet->writeStr(RowNum, m_prameterPtr->col_ErrLmt, FLOAT_TO_CHAR(errLmt), m_format);
}

void CPseudoDlg::mergeCells(int meterNo)
{
	m_sheet->setMerge(getStartRowNum(meterNo), getEndRowNum(meterNo), m_prameterPtr->col_Seq, m_prameterPtr->col_Seq);
	m_sheet->setMerge(getStartRowNum(meterNo), getEndRowNum(meterNo), m_prameterPtr->col_RecNo, m_prameterPtr->col_RecNo);
	m_sheet->setMerge(getStartRowNum(meterNo), getEndRowNum(meterNo), m_prameterPtr->col_MeterNo, m_prameterPtr->col_MeterNo);
	m_sheet->setMerge(getStartRowNum(meterNo), getEndRowNum(meterNo), m_prameterPtr->col_Result, m_prameterPtr->col_Result);
}

void CPseudoDlg::LoadExcel(QString filename)
{
	filename.replace('\\',"\\\\");
	m_book = xlCreateBook();
	m_book->load(filename.toStdString().data());
	m_sheet = m_book->getSheet(0);
	m_format = m_book->addFormat();
	m_font = m_book->addFont();

	//set cell format
	m_format->setBorder(BORDERSTYLE_THIN);
	m_format->setAlignH(ALIGNH_CENTER);
	m_format->setAlignV(ALIGNV_CENTER);
	m_font->setColor(COLOR_BLACK);
	m_font->setName("宋体");
	m_font->setSize(10);
	m_format->setFont(m_font);
}

void CPseudoDlg::saveExcel(QString filename)
{
	m_book->save(filename.toStdString().data());

	if (m_book)
	{
		m_book->release();//release all resources including sheet, format and font
		m_book = NULL;
	}
	if (m_sheet)
	{
		m_sheet = NULL;
	}
	if (m_format)
	{
		m_format = NULL;
	}
	if (m_font)
	{
		m_font = NULL;
	}
}

int CPseudoDlg::getStartRowNum(int MeterNo)
{
	return m_prameterPtr->dataStartRow + (MeterNo-1)*FLOW_POINTS;
}

int CPseudoDlg::getEndRowNum(int MeterNo)
{
	return (getStartRowNum(MeterNo)+2);
}

float CPseudoDlg::getHighTemp(flowPointEnum flowPoint)
{
	GET_RAND(1000)
	return MAP_FP(m_mapHTemp) + SIGN*RATIONAL_RAND(2000.0);
}

float CPseudoDlg::getLowTemp(flowPointEnum flowPoint)
{
	GET_RAND(1000)
	return MAP_FP(m_mapLTemp) + SIGN*RATIONAL_RAND(2000.0);
}

float CPseudoDlg::getPipeTemp(flowPointEnum flowPoint)
{
	GET_RAND(1000)
	return MAP_FP(m_mapPTemp) + SIGN*RATIONAL_RAND(2000.0);
}

float CPseudoDlg::getPipeDensity(float temp)
{
	CAlgorithm al;
	return al.getDensityByQuery(temp);
}

float CPseudoDlg::getBalanceMass(flowPointEnum flowPoint)
{
	GET_RAND(1000)
	return MAP_FP(m_mapVerifyMass) + rand/800.0;
}

float CPseudoDlg::getFlowPoint(flowPointEnum flowPoint)
{
	GET_RAND(500)
	return MAP_FP(m_mapFlowPoint)*(1+ SIGN*RATIONAL_RAND(10000.0));
}

float CPseudoDlg::getErrLmt(float delta_t, float flow_rate)
{
	CAlgorithm al;
	return getMeterGradeErrLmt(2, m_prameterPtr->minDiffTemp, delta_t, m_prameterPtr->normalFlowRate, flow_rate);
}

float CPseudoDlg::getErr(float errLmt)
{
	GET_RAND(1000)
	return SIGN*(errLmt - RATIONAL_RAND(1000.0));
}

float CPseudoDlg::getStdEnergy(float hTemp, float lTemp, float mass)
{
	CAlgorithm al;
	return al.calcStdEnergyByEnthalpy(hTemp, lTemp, mass, UNIT_KWH);
}

float CPseudoDlg::getMeterEnergy(float stdEnergy, float err)
{
	return stdEnergy*(1+err/100.0);
}

void CPseudoDlg::insertLogoRow(QString filename)
{
	QExcel j(filename);
	j.selectSheet(1);
	j.insertRow(1,1);
	j.save();
	j.close();
}

void CPseudoDlg::deleteLog(QString filename)
{
	QExcel j(filename);
	j.selectSheet(1);
	j.deleteRow(1,1);
	j.save();
	j.close();
}