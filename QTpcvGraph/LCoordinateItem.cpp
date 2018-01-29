#include "LCoordinateItem.h"

using namespace LTPCV;

LCoordinateItem::LCoordinateItem(QObject *parent) :
    QObject(parent),
    m_bDrawLine(true),
    m_bFromZero(false)
{
    m_font.setPixelSize(14);
    // 坐标区域
    m_rBoundingSize.setRect(0, 0, 400, 200);
    // 文本框大小
    m_sizeTextX.setHeight(QFontMetrics(m_font).height());
    m_sizeTextY.setHeight(QFontMetrics(m_font).height());
    m_sizeTextX.setWidth(QFontMetrics(m_font).height()*2);
    m_sizeTextY.setWidth(QFontMetrics(m_font).height()*2);
}

LCoordinateItem::~LCoordinateItem()
{

}

void LCoordinateItem::ReSize(QSize boundingSize)
{
    m_rBoundingSize.setWidth(boundingSize.width());
    m_rBoundingSize.setHeight(boundingSize.height());

    ReSetXYScale();
}

void LCoordinateItem::SetBoundingRect(QRect rect)
{
    m_rBoundingSize = rect;

    ReSetXYScale();
}

void LCoordinateItem::SetXYScale(const QStringList &strLstX, const QStringList &strLstY)
{
    m_strLstX = strLstX;
    m_strLstY = strLstY;

    ReSetXYScale();
}

void LCoordinateItem::SetXScale(const QStringList &strLstX)
{
    m_strLstX = strLstX;

    ReSetXYScale();
}

void LCoordinateItem::SetYScale(const QStringList &strLstY)
{
    m_strLstY = strLstY;

    ReSetXYScale();
}

void LCoordinateItem::SetXTitle(const QString &strXTitle)
{
    m_strXTitle = strXTitle;
}

void LCoordinateItem::SetYTitle(const QString &strYTitle)
{
    m_strYTitle = strYTitle;
}

void LCoordinateItem::SetData(QList<CVF_DATA> cvfDataLst, int iMax)
{
    m_cvfDataLst = cvfDataLst;
    m_iMax = iMax;
}

void LCoordinateItem::DrawXAxis(QPainter *painter, QPoint pLeft, QPoint pRight)
{
    painter->save();
    painter->setPen(m_pen);
    painter->setPen(QColor(62, 92, 149));
    painter->drawLine(pLeft, pRight);
}

void LCoordinateItem::DrawYAxis(QPainter *painter, QPoint pTop, QPoint pBottom)
{
    painter->drawLine(pTop, pBottom);
    painter->setBrush(QColor(62, 92, 149));
    // Y轴箭头
    QPoint topTrigon[3] = {
        QPoint(pTop.x(), pTop.y() - 8),
        QPoint(pTop.x() - 4, pTop.y()),
        QPoint(pTop.x() + 4, pTop.y())
    };
    painter->drawPolygon(topTrigon, 3);
}

void LCoordinateItem::DrawXArrow(QPainter *painter, QPoint pRight)
{
    painter->setBrush(QColor(62, 92, 149));
    // X轴箭头
    QPoint rightTrigon[3] = {
        QPoint(pRight.x() + 8, pRight.y()),
        QPoint(pRight.x(), pRight.y() + 4),
        QPoint(pRight.x(), pRight.y() - 4)
    };
    painter->drawPolygon(rightTrigon, 3);
}

void LCoordinateItem::DrawXTitle(QPainter *painter, QPoint pRight, QString &strTitle)
{
    QRect textXRect(pRight.x() + m_sizeTextX.width()/4, pRight.y() + 5, m_sizeTextX.width(), m_sizeTextX.height());
    painter->drawText(textXRect, Qt::AlignRight | Qt::AlignVCenter | Qt::TextDontClip, strTitle);
}

void LCoordinateItem::DrawYScale(QPainter *painter, QPoint pLeft, QString &strTitle)
{
    QRect textYRect(0, pLeft.y() - 5, m_sizeTextY.width(), m_sizeTextY.height());
    painter->drawText(textYRect, Qt::AlignCenter | Qt::TextDontClip, strTitle);
}

void LCoordinateItem::DrawGraph(QPainter *painter, QPoint pLeft, float fA, float fT, int iMax)
{
    // 幅度
    float A_1 = fA;
    // 周期
    float T_1 = fT;

    QPoint p(pLeft.x(), pLeft.y());
    QPoint p1(0, 0);
    for(int x = 0; x < iMax; x += 1)
    {
        double angle = (double) x / (T_1 * 2) * 2 * PI;
        double y = A_1 * sin(angle);
        QPoint p2(x, y);

        painter->drawLine(CoordinateFlip(p, p1), CoordinateFlip(p, p2));
        p1 = p2;
    }
}

void LCoordinateItem::SetPenColor(QColor penColor)
{
    m_pen.setColor(penColor);
}

QPoint LCoordinateItem::GetOrigin()
{
    return m_pointOrigin;
}

int LCoordinateItem::GetXScaleSpacing()
{
    return m_iXScaleLen;
}

int LCoordinateItem::GetYScaleSpacing()
{
    return m_iYScaleLen;
}

void LCoordinateItem::ReSetXYScale()
{
    QPoint top = QPoint(m_sizeTextX.width() + MARGIN_COORDINATE, MARGIN_COORDINATE);
    QPoint bottom = QPoint(m_sizeTextX.width() + MARGIN_COORDINATE, m_rBoundingSize.height() - m_sizeTextY.height() + MARGIN_COORDINATE);
    QPoint origin = QPoint(m_sizeTextX.width() + MARGIN_COORDINATE, m_rBoundingSize.height() - m_sizeTextY.height() - MARGIN_COORDINATE);
    QPoint right = QPoint(m_rBoundingSize.width() + MARGIN_COORDINATE * 4, m_rBoundingSize.height() - m_sizeTextY.height() - MARGIN_COORDINATE);
    QPoint left = QPoint(m_sizeTextX.width() - MARGIN_COORDINATE, m_rBoundingSize.height() - m_sizeTextY.height() - MARGIN_COORDINATE);

    m_pointOrigin = origin;

    m_iYScaleLen = (origin.y() - top.y()) / (m_strLstY.size() + 1);
    m_iXScaleLen = (right.x() - origin.x()) / (m_strLstX.size() + 1);
}


QPoint LCoordinateItem::CoordinateFlip(QPoint o, QPoint p)
{
    p.setY(0 - p.y());
    return p + o;
}

QRectF LCoordinateItem::boundingRect() const
{
    return m_rBoundingSize;
}

void LCoordinateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    QPoint top = QPoint(m_sizeTextX.width(), MARGIN_COORDINATE);
    QPoint bottom = QPoint(m_sizeTextX.width(), m_rBoundingSize.height() - m_sizeTextY.height() - MARGIN_COORDINATE);
    QPoint origin = QPoint(m_sizeTextX.width() + MARGIN_COORDINATE, m_rBoundingSize.height() - m_sizeTextY.height() - MARGIN_COORDINATE);
    QPoint right = QPoint(m_rBoundingSize.width() - MARGIN_COORDINATE * 2, MARGIN_COORDINATE * 6);
    QPoint left = QPoint(m_sizeTextX.width(), MARGIN_COORDINATE * 6);

    QPoint right_2 = QPoint(m_rBoundingSize.width() - MARGIN_COORDINATE * 2,
                            (m_rBoundingSize.height() + m_sizeTextY.height() + MARGIN_COORDINATE)/2 - MARGIN_COORDINATE);
    QPoint left_2 = QPoint(m_sizeTextX.width(),
                           (m_rBoundingSize.height() + m_sizeTextY.height() + MARGIN_COORDINATE)/2 - MARGIN_COORDINATE);

    QPoint right_3 = QPoint(m_rBoundingSize.width() - MARGIN_COORDINATE * 2,
                            m_rBoundingSize.height() - m_sizeTextY.height() - MARGIN_COORDINATE * 6);
    QPoint left_3 = QPoint(m_sizeTextX.width(), m_rBoundingSize.height() - m_sizeTextY.height() - MARGIN_COORDINATE * 6);

    m_pointOrigin = origin;

    // X轴
    DrawXAxis(painter, left, right);
    DrawXAxis(painter, left_2, right_2);
    DrawXAxis(painter, left_3, right_3);
    // Y轴
    DrawYAxis(painter, top, bottom);

    // X轴2箭头
    DrawXArrow(painter, right);
    DrawXArrow(painter, right_2);
    DrawXArrow(painter, right_3);

    // X轴文字描述
    DrawXTitle(painter, right, m_strXTitle);
    DrawXTitle(painter, right_2, m_strXTitle);
    DrawXTitle(painter, right_3, m_strXTitle);

    // Y轴文字描述及刻度
    QRect textYRect(70, 10, m_sizeTextY.width(), m_sizeTextY.height());
    painter->drawText(textYRect, Qt::AlignCenter | Qt::TextDontClip, m_strYTitle);
    DrawYScale(painter, left, m_strLstY[0]);
    DrawYScale(painter, left_2, m_strLstY[1]);
    DrawYScale(painter, left_3, m_strLstY[2]);

    // 曲线图
    painter->setRenderHint(QPainter::Antialiasing, true);
    // 1
    QPen pen1(Qt::darkCyan, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen1);
    DrawGraph(painter, left, m_cvfDataLst[0].iFreq, m_cvfDataLst[0].iAmpl, m_iMax);
    // 2
    QPen pen2(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen2);
    DrawGraph(painter, left_2, m_cvfDataLst[1].iFreq, m_cvfDataLst[1].iAmpl, m_iMax);
    // 3
    QPen pen3(Qt::green, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen3);
    DrawGraph(painter, left_3, m_cvfDataLst[2].iFreq, m_cvfDataLst[2].iAmpl, m_iMax);

    // X轴坐标刻度
//    painter->setPen(Qt::white);
//    for (int i = 0; i < m_strLstX.size(); ++i)
//    {
//        QRect yTextRect;
//        yTextRect = QRect(origin.x() + m_iXScaleLen * (i + 1) - m_sizeTextY.width() / 2 - MARGIN_COORDINATE,
//                          origin.y() + 5,
//                          m_sizeTextY.width(),
//                          m_sizeTextY.height());

//        QString strTmp = m_strLstX.at(i);
//        int fontCount = m_iXScaleLen / QFontMetrics(painter->font()).height();

//        if (strTmp.toLocal8Bit().size() > fontCount * 2)
//        {
//            strTmp = strTmp.left(fontCount - 2) + "......";
//        }

//        painter->drawText(yTextRect, Qt::AlignCenter | Qt::TextDontClip, strTmp);
//    }



    painter->restore();

}
