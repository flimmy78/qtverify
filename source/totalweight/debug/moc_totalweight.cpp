/****************************************************************************
** Meta object code from reading C++ file 'totalweight.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/totalweight.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'totalweight.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TotalWeightDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      58,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   16,   15,   15, 0x0a,
      51,   15,   47,   15, 0x0a,
      71,   15,   15,   15, 0x0a,
      94,   15,   15,   15, 0x0a,
     112,   15,   15,   15, 0x0a,
     136,   15,   15,   15, 0x0a,
     158,   15,   15,   15, 0x0a,
     179,   15,   15,   15, 0x0a,
     200,   15,   15,   15, 0x0a,
     221,   15,   47,   15, 0x0a,
     243,   15,   47,   15, 0x0a,
     255,   15,   47,   15, 0x0a,
     278,   15,   47,   15, 0x0a,
     304,   15,   47,   15, 0x0a,
     325,   15,   47,   15, 0x0a,
     345,   15,   47,   15, 0x0a,
     364,   15,   47,   15, 0x0a,
     386,  384,   47,   15, 0x0a,
     423,  415,   47,   15, 0x0a,
     459,   15,   15,   15, 0x0a,
     473,   15,   47,   15, 0x0a,
     497,   15,  492,   15, 0x0a,
     526,  520,   47,   15, 0x0a,
     558,  520,   47,   15, 0x0a,
     586,  520,   47,   15, 0x0a,
     619,  612,   47,   15, 0x0a,
     636,  612,   47,   15, 0x0a,
     654,  612,   47,   15, 0x0a,
     674,   15,   47,   15, 0x0a,
     695,   15,   47,   15, 0x0a,
     714,   15,   15,   15, 0x0a,
     745,   15,   47,   15, 0x0a,
     769,  765,   47,   15, 0x0a,
     798,  789,   15,   15, 0x0a,
     835,  827,   15,   15, 0x0a,
     866,   15,   15,   15, 0x0a,
     900,  886,   15,   15, 0x0a,
     934,   15,   15,   15, 0x0a,
     974,  954,   15,   15, 0x0a,
    1023, 1010,   15,   15, 0x0a,
    1066, 1055,   15,   15, 0x0a,
    1106, 1055,   15,   15, 0x0a,
    1144,   15,   15,   15, 0x0a,
    1168,   15,   15,   15, 0x0a,
    1192,   15,   15,   15, 0x0a,
    1217,   15,   15,   15, 0x0a,
    1242,   15,   15,   15, 0x0a,
    1271,   15,   15,   15, 0x0a,
    1300,   15,   15,   15, 0x0a,
    1327,   15,   15,   15, 0x0a,
    1353,   15,   15,   15, 0x0a,
    1388, 1377,   15,   15, 0x0a,
    1424,   15,   47,   15, 0x0a,
    1447,   15,   15,   15, 0x0a,
    1468,   15,   15,   15, 0x0a,
    1494,   15,   15,   15, 0x0a,
    1519, 1515,   15,   15, 0x0a,
    1542, 1515,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TotalWeightDlg[] = {
    "TotalWeightDlg\0\0event\0closeEvent(QCloseEvent*)\0"
    "int\0readNowParaConfig()\0showNowKeyParaConfig()\0"
    "initTableWidget()\0on_btnExhaust_clicked()\0"
    "on_btnStart_clicked()\0on_btnNext_clicked()\0"
    "on_btnStop_clicked()\0slotExaustFinished()\0"
    "openAllValveAndPump()\0readMeter()\0"
    "setMeterVerifyStatus()\0closeAllFlowPointValves()\0"
    "closeWaterOutValve()\0openWaterOutValve()\0"
    "openBigFlowValve()\0closeBigFlowValve()\0"
    "v\0judgeBalanceInitValue(float)\0targetV\0"
    "judgeBalanceAndCalcAvgTemper(float)\0"
    "startVerify()\0getValidMeterNum()\0bool\0"
    "judgeBalanceCapacity()\0order\0"
    "judgeBalanceCapacitySingle(int)\0"
    "prepareVerifyFlowPoint(int)\0"
    "startVerifyFlowPoint(int)\0portno\0"
    "openValve(UINT8)\0closeValve(UINT8)\0"
    "operateValve(UINT8)\0getMeterStartValue()\0"
    "getMeterEndValue()\0makeStartValueByLastEndValue()\0"
    "calcAllMeterError()\0idx\0calcMeterError(int)\0"
    "balValue\0slotFreshBalanceValue(float)\0"
    "tempStr\0slotFreshComTempValue(QString)\0"
    "slotFreshFlowRate()\0portno,status\0"
    "slotSetValveBtnStatus(UINT8,bool)\0"
    "slotSetRegulateOk()\0comName,meterNumber\0"
    "slotSetMeterNumber(QString,QString)\0"
    "comName,flow\0slotSetMeterFlow(QString,float)\0"
    "btn,status\0setValveBtnBackColor(QToolButton*,bool)\0"
    "setRegBtnBackColor(QPushButton*,bool)\0"
    "on_btnParaSet_clicked()\0on_btnWaterIn_clicked()\0"
    "on_btnWaterOut_clicked()\0"
    "on_btnValveBig_clicked()\0"
    "on_btnValveMiddle1_clicked()\0"
    "on_btnValveMiddle2_clicked()\0"
    "on_btnValveSmall_clicked()\0"
    "on_btnWaterPump_clicked()\0"
    "on_btnSetFreq_clicked()\0row,column\0"
    "on_tableWidget_cellChanged(int,int)\0"
    "saveAllVerifyRecords()\0clearTableContents()\0"
    "on_btnReadMeter_clicked()\0"
    "on_btnExit_clicked()\0row\0"
    "slotModifyMeterNo(int)\0slotAdjustError(int)\0"
};

void TotalWeightDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TotalWeightDlg *_t = static_cast<TotalWeightDlg *>(_o);
        switch (_id) {
        case 0: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: { int _r = _t->readNowParaConfig();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: _t->showNowKeyParaConfig(); break;
        case 3: _t->initTableWidget(); break;
        case 4: _t->on_btnExhaust_clicked(); break;
        case 5: _t->on_btnStart_clicked(); break;
        case 6: _t->on_btnNext_clicked(); break;
        case 7: _t->on_btnStop_clicked(); break;
        case 8: _t->slotExaustFinished(); break;
        case 9: { int _r = _t->openAllValveAndPump();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { int _r = _t->readMeter();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: { int _r = _t->setMeterVerifyStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: { int _r = _t->closeAllFlowPointValves();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 13: { int _r = _t->closeWaterOutValve();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: { int _r = _t->openWaterOutValve();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: { int _r = _t->openBigFlowValve();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 16: { int _r = _t->closeBigFlowValve();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: { int _r = _t->judgeBalanceInitValue((*reinterpret_cast< float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 18: { int _r = _t->judgeBalanceAndCalcAvgTemper((*reinterpret_cast< float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 19: _t->startVerify(); break;
        case 20: { int _r = _t->getValidMeterNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 21: { bool _r = _t->judgeBalanceCapacity();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 22: { int _r = _t->judgeBalanceCapacitySingle((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 23: { int _r = _t->prepareVerifyFlowPoint((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 24: { int _r = _t->startVerifyFlowPoint((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 25: { int _r = _t->openValve((*reinterpret_cast< UINT8(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 26: { int _r = _t->closeValve((*reinterpret_cast< UINT8(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 27: { int _r = _t->operateValve((*reinterpret_cast< UINT8(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 28: { int _r = _t->getMeterStartValue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 29: { int _r = _t->getMeterEndValue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 30: _t->makeStartValueByLastEndValue(); break;
        case 31: { int _r = _t->calcAllMeterError();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 32: { int _r = _t->calcMeterError((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 33: _t->slotFreshBalanceValue((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 34: _t->slotFreshComTempValue((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 35: _t->slotFreshFlowRate(); break;
        case 36: _t->slotSetValveBtnStatus((*reinterpret_cast< const UINT8(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 37: _t->slotSetRegulateOk(); break;
        case 38: _t->slotSetMeterNumber((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 39: _t->slotSetMeterFlow((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const float(*)>(_a[2]))); break;
        case 40: _t->setValveBtnBackColor((*reinterpret_cast< QToolButton*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 41: _t->setRegBtnBackColor((*reinterpret_cast< QPushButton*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 42: _t->on_btnParaSet_clicked(); break;
        case 43: _t->on_btnWaterIn_clicked(); break;
        case 44: _t->on_btnWaterOut_clicked(); break;
        case 45: _t->on_btnValveBig_clicked(); break;
        case 46: _t->on_btnValveMiddle1_clicked(); break;
        case 47: _t->on_btnValveMiddle2_clicked(); break;
        case 48: _t->on_btnValveSmall_clicked(); break;
        case 49: _t->on_btnWaterPump_clicked(); break;
        case 50: _t->on_btnSetFreq_clicked(); break;
        case 51: _t->on_tableWidget_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 52: { int _r = _t->saveAllVerifyRecords();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 53: _t->clearTableContents(); break;
        case 54: _t->on_btnReadMeter_clicked(); break;
        case 55: _t->on_btnExit_clicked(); break;
        case 56: _t->slotModifyMeterNo((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 57: _t->slotAdjustError((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TotalWeightDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TotalWeightDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TotalWeightDlg,
      qt_meta_data_TotalWeightDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TotalWeightDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TotalWeightDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TotalWeightDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TotalWeightDlg))
        return static_cast<void*>(const_cast< TotalWeightDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int TotalWeightDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 58)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 58;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
