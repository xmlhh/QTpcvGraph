/************************************************************************
*   文件名称：LTpcvView.h
*   编写人员：LHH
*   创建日期：2018/01/02
*   功能描述：作为画布展示绘制的图形，数据的加载，动作处理
*   备    注：
*   修改描述：
************************************************************************/

#ifndef LTPCVVIEW_H
#define LTPCVVIEW_H

#include "LCommon.h"
#include "LCoordinateItem.h"

#include <QObject>
#include <QGraphicsView>

using namespace LTPCV;

class LTpcvView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit LTpcvView();
    ~LTpcvView();

    /**
    * @author by lhh
    * @brief X轴标识
    * @param strXTitle箭标
    * @return void
    */
    void SetXTitle(const QString &strXTitle);

    /**
    * @author by lhh
    * @brief Y轴标识
    * @param strXTitle箭标
    * @return void
    */
    void SetYTitle(const QString &strYTitle);

    /**
    * @author by lhh
    * @brief 设置X轴刻度
    * @param X轴所有刻度值
    * @return void
    */
    void SetXScale(const QStringList &strLstX);

    /**
    * @author by lhh
    * @brief 设置Y轴刻度
    * @param Y轴所有刻度值
    * @return void
    */
    void SetYScale(const QStringList &strLstX);

    /**
    * @author by lhh
    * @brief 保存数据
    * @param 公用tpcvData数据结构
    * @return void
    */
    void SetData(LTPCV_DATA tpcvData);
    void SetData_2(LTPCV_DATA tpcvData);

    // 设置字体
    void SetFont(QFont textFont);

    // 设置柱状图形宽度
    void SetSparWidth(int iSparWidth);
    // 默认：曲线图
    void ChangeDrawType(LDrawType drawType = GRAPH);
    // 绘制曲线图
    void DrawGraph(LTPCV_DATA lTpcvData);
    // 绘制柱状图
    void DrawHistogram(LTPCV_DATA lTpcvData);
    // 清除画布
    void ClearScene();

protected:
    // 重置窗口大小
    virtual void resizeEvent(QResizeEvent *event);
    virtual void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    // 标尺/刻度
    LCoordinateItem *m_pCoordinateItem;
    // 图形类型
    LDrawType m_drawType;

    // 柱状图的高度
    int m_iCellHeight;
    // 柱状图的宽度
    int m_iSparWidth;

    // 字体
    QFont m_font;
    // 颜色
    QList<QColor> m_colorLst;

    // 柱形图
    QList<QGraphicsRectItem *> m_rectItemLst;
    // 所有柱形图
    QList<QGraphicsRectItem *> m_sparLst;
    // 曲线图
    QList<QGraphicsPathItem *> m_painterPathLst;
    // X轴刻度线
    QList<QGraphicsLineItem *> m_lineItemLst;

    // 数据
    QList<CVF_DATA> m_cvfDataLst;
    QMultiMap<QString, CVF_DATA> m_mapCvfData;
    LTPCV_DATA m_lTpcvData;

};

#endif // LTPCVVIEW_H
