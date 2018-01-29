#include "LTpcvView.h"

LTpcvView::LTpcvView() :
    m_drawType(GRAPH),
    m_iSparWidth(10)
{
    // 场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    // 场景在View中展示
    setScene(scene);
    // 坐标
    m_pCoordinateItem = new LCoordinateItem;
    m_pCoordinateItem->setZValue(-1);
    m_pCoordinateItem->SetPenColor(Qt::blue);
    // 坐标添加到场景
    scene->addItem(m_pCoordinateItem);

    // 滚动条不显示
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);

    scene->setSceneRect(50, 50, width(), height() + MARGIN_COORDINATE * 5);
}

LTpcvView::~LTpcvView()
{

}

void LTpcvView::SetXTitle(const QString &strXTitle)
{
    m_pCoordinateItem->SetXTitle(strXTitle);
}

void LTpcvView::SetYTitle(const QString &strYTitle)
{
    m_pCoordinateItem->SetYTitle(strYTitle);
}

void LTpcvView::SetXScale(const QStringList &strLstX)
{
    // 设置X轴刻度
    m_pCoordinateItem->SetXScale(strLstX);
}

void LTpcvView::SetYScale(const QStringList &strLstX)
{
    // 设置Y轴刻度
    m_pCoordinateItem->SetYScale(strLstX);
}

void LTpcvView::SetData(LTPCV_DATA tpcvData)
{
    m_lTpcvData = tpcvData;
    m_mapCvfData = tpcvData.mapCvfData;

    switch (m_drawType)
    {
    // 曲线图
    case GRAPH:
        DrawGraph(m_lTpcvData);
        break;

    // 柱状图
    case HISTOGRAM:
        DrawHistogram(m_lTpcvData);
        break;
    default:
        break;
    }
}

void LTpcvView::SetData_2(LTPCV_DATA tpcvData)
{
    m_lTpcvData = tpcvData;
    m_cvfDataLst.clear(); /*= tpcvData.cvfDataLst*/
    m_colorLst.clear();

    int r, g, b;

    // 随机颜色
    for (int i = 0; i < m_cvfDataLst.size(); ++i)
    {
        switch (i%6)
        {
        case 0:
            r = qrand()%70 + 130;
            g = 130;
            b = 200;
            break;
        case 1:
            r = qrand()%70 + 130;
            g = 130;
            b = 200;
            break;
        case 2:
            r = qrand()%70 + 130;
            g = 130;
            b = 200;
            break;
        case 3:
            r = qrand()%70 + 130;
            g = 130;
            b = 200;
            break;
        case 4:
            r = qrand()%70 + 130;
            g = 130;
            b = 200;
            break;
        case 5:
            r = qrand()%70 + 130;
            g = 130;
            b = 200;
            break;
        }
        m_colorLst.append(QColor(r, g, b));
    }

    switch (m_drawType)
    {
    // 曲线图
    case GRAPH:
        DrawGraph(m_lTpcvData);
        break;

    // 柱状图
    case HISTOGRAM:
        DrawHistogram(m_lTpcvData);
        break;
    default:
        break;
    }
}

void LTpcvView::SetFont(QFont textFont)
{
    m_font = textFont;
}

void LTpcvView::SetSparWidth(int iSparWidth)
{
    m_iSparWidth = iSparWidth;
}

void LTpcvView::ChangeDrawType(LDrawType drawType)
{
    m_drawType = drawType;
}

void LTpcvView::DrawGraph(LTPCV_DATA lTpcvData)
{
    ClearScene();
    // @todo

    m_mapCvfData = lTpcvData.mapCvfData;
    CVF_DATA cvfData;
    QList<CVF_DATA> cvfDataLst;

    QMultiMap<QString, CVF_DATA>::iterator it;
    for (it = m_mapCvfData.begin(); it != m_mapCvfData.end(); ++it)
    {
        cvfData = it.value();
        cvfDataLst.append(cvfData);
    }
    m_pCoordinateItem->SetData(cvfDataLst, lTpcvData.iMax);
}

void LTpcvView::DrawHistogram(LTPCV_DATA lTpcvData)
{
    ClearScene();
    // @todo
}

void LTpcvView::ClearScene()
{
    // 删除场景中的X轴刻度线
    for (int i = 0; i < m_lineItemLst.size(); ++i)
    {
        scene()->removeItem(m_lineItemLst[i]);
    }

    // 删除柱状图形
    for (int i = 0; i < m_rectItemLst.size(); ++i)
    {
        scene()->removeItem(m_rectItemLst[i]);
    }

    for (int i = 0; i < m_sparLst.size(); ++i)
    {
        delete m_sparLst[i];
    }
    m_sparLst.clear();

    // 删除曲线图
    for (int i = 0; i < m_painterPathLst.size(); ++i)
    {
        delete m_painterPathLst[i];
    }
    m_painterPathLst.clear();

}

void LTpcvView::resizeEvent(QResizeEvent */*event*/)
{
    QRect coordinateRect = rect();
    scene()->setSceneRect(rect());

    m_pCoordinateItem->SetBoundingRect(coordinateRect);

    switch (m_drawType)
    {
    // 曲线图
    case GRAPH:
        DrawGraph(m_lTpcvData);
        break;

    // 柱状图
    case HISTOGRAM:
        DrawHistogram(m_lTpcvData);
        break;
    default:
        break;
    }
}

void LTpcvView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
}
