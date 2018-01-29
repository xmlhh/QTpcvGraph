#include "LeonWgt.h"
#include "ui_LeonWgt.h"

#define WIN_WIDTH 700
#define WIN_HEIGHT 500

LeonWgt::LeonWgt(QWidget *parent) :
    QWidget(parent),
    m_pLTpcvView(NULL),
    ui(new Ui::LeonWgt)
{
    InitUI();
    InitData();
}

LeonWgt::~LeonWgt()
{
    delete ui;
}

int LeonWgt::InitUI()
{
    ui->setupUi(this);

    resize(WIN_WIDTH, WIN_HEIGHT);

    setWindowTitle("三相电压电流曲线图");

    if (NULL == m_pLTpcvView)
    {
        m_pLTpcvView = new LTpcvView;
    }

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(m_pLTpcvView);
    vLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(vLayout);

    return 0;
}

int LeonWgt::InitData()
{
    QStringList strULst;
    strULst << "Ua" << "Ub" << "Uz";

    QString strXTitle = "频率(t)";
    QString strYTitle = "电压(U)/电流(I)";
    SetXTitle(strXTitle);
    SetYTitle(strYTitle);

    SetYScale(strULst);

    // 测试数据
    SetData();

    return 0;
}

void LeonWgt::SetData()
{
    // 测试数据
    LTPCV_DATA ltpcvData;
    QMultiMap<QString, CVF_DATA> mapCvfData;

    CVF_DATA cvfData1, cvfData2, cvfData3;
    cvfData1.iAmpl = 50;
    cvfData1.iFreq = 35;

    cvfData2.iAmpl = 50;
    cvfData2.iFreq = 45;

    cvfData3.iAmpl = 50;
    cvfData3.iFreq = 65;

    mapCvfData.insert("Ua", cvfData1);
    mapCvfData.insert("Ub", cvfData2);
    mapCvfData.insert("Uz", cvfData3);

    ltpcvData.iMax = 550;
    ltpcvData.mapCvfData = mapCvfData;

    m_pLTpcvView->SetData(ltpcvData);
}

void LeonWgt::InitCoordinate(LTPCV_DATA tpcvData)
{

}

void LeonWgt::resizePreViewWgt()
{
    resize(WIN_WIDTH, WIN_HEIGHT);
}

void LeonWgt::SetXTitle(const QString &strXTitle)
{
    m_pLTpcvView->SetXTitle(strXTitle);
}

void LeonWgt::SetYTitle(const QString &strYTitle)
{
    m_pLTpcvView->SetYTitle(strYTitle);
}

void LeonWgt::SetXScale(const QStringList &strLstX)
{

}

void LeonWgt::SetYScale(const QStringList &strLstY)
{
    m_pLTpcvView->SetYScale(strLstY);
}
