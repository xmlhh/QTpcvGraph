/************************************************************************
*   文件名称：LCoordinateItem.h
*   编写人员：LHH
*   创建日期：2018/01/02
*   功能描述：绘制X轴、Y轴坐标及可刻度，绘制曲线图、柱状图
*   备    注：
*   修改描述：
************************************************************************/

#ifndef LCOORDINATEITEM_H
#define LCOORDINATEITEM_H

#include "LCommon.h"

#include <QObject>

#include <QGraphicsItem>
#include <QPoint>
#include <QPainter>
#include <QPen>
#include <QFont>

using namespace LTPCV;

class LCoordinateItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit LCoordinateItem(QObject *parent = 0);
    ~LCoordinateItem();

    /**
    * @author by lhh
    * @brief 重置大小
    * @param 区域大小
    * @return void
    */
    void ReSize(QSize boundingSize);

    /**
    * @author by lhh
    * @brief 重置边界大小
    * @param 区域大小
    * @return void
    */
    void SetBoundingRect(QRect rect);

    /**
    * @author by lhh
    * @brief 设置X轴、Y轴的刻度
    * @param X刻度列表
    * @param Y刻度列表
    * @return void
    */
    void SetXYScale(const QStringList &strLstX, const QStringList &strLstY);

    /**
    * @author by lhh
    * @brief 设置X轴刻度
    * @param X刻度列表
    * @return void
    */
    void SetXScale(const QStringList &strLstX);

    /**
    * @author by lhh
    * @brief 设置Y轴刻度
    * @param Y刻度列表
    * @return void
    */
    void SetYScale(const QStringList &strLstY);

    /**
    * @author by lhh
    * @brief 设置X轴标题
    * @param X标题
    * @return void
    */
    void SetXTitle(const QString &strXTitle);

    /**
    * @author by lhh
    * @brief 设置Y轴标题
    * @param Y标题
    * @return void
    */
    void SetYTitle(const QString &strYTitle);

    /**
    * @author by lhh
    * @brief 设置幅值、频率、周期最大值
    * @param 幅值、频率的数据结构
    * @param 周期最大值
    * @return void
    */
    void SetData(QList<CVF_DATA> cvfDataLst, int iMax);

    /**
    * @author by lhh
    * @brief 绘制X轴
    * @param pLeft左边的位置点
    * @param pRight右边的位置点
    * @return void
    */
    void DrawXAxis(QPainter *painter, QPoint pLeft, QPoint pRight);

    /**
    * @author by lhh
    * @brief 绘制Y轴
    * @param pTop上边的位置点
    * @param pBottom下边的位置点
    * @return void
    */
    void DrawYAxis(QPainter *painter, QPoint pTop, QPoint pBottom);

    /**
    * @author by lhh
    * @brief 绘制X轴箭头
    * @param pRight右边的位置点
    * @return void
    */
    void DrawXArrow(QPainter *painter, QPoint pRight);

    /**
    * @author by lhh
    * @brief 绘制X轴文字描述
    * @param pRight右边的位置点
    * @param strTitle箭标
    * @return void
    */
    void DrawXTitle(QPainter *painter, QPoint pRight, QString &strTitle);

    /**
    * @author by lhh
    * @brief 绘制Y轴刻度
    * @param pLeft左边的位置点
    * @param strTitle箭标
    * @return void
    */
    void DrawYScale(QPainter *painter, QPoint pLeft, QString &strTitle);

    /**
    * @author by lhh
    * @brief 绘制曲线图
    * @param pLeft左边的位置点
    * @param fA幅值
    * @param fT频率
    * @param iMax周期最大值
    * @return void
    */
    void DrawGraph(QPainter *painter, QPoint pLeft, float fA, float fT, int iMax);


    /**
    * @author by lhh
    * @brief 设置画笔颜色
    * @param penColor画笔颜色
    * @return void
    */
    void SetPenColor(QColor penColor);

    // 获取坐标原点
    QPoint GetOrigin();

    // 获取X轴刻度间宽度
    int GetXScaleSpacing();

    // 获取Y轴刻度间宽度
    int GetYScaleSpacing();

    // 重置X轴、Y轴的刻度
    void ReSetXYScale();

    /**
    * @author by lhh
    * @brief 坐标翻转
    * @param o原点
    * @param p翻转点
    * @return void
    */
    QPoint CoordinateFlip(QPoint o, QPoint p);

protected:
    // 区域
    virtual QRectF boundingRect() const;
    // 重写paint虚函数
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/);

signals:

public slots:

private:
    // 是否画X轴横线
    bool m_bDrawLine;
    // 是否显示提示
    bool m_bFromZero;

    // 坐标原点
    QPoint m_pointOrigin;
    // X轴单位长度
    int m_iXScaleLen;
    // Y轴单位长度
    int m_iYScaleLen;

    // X轴坐标头文本
    QString m_strXTitle;
    // Y轴坐标头文本
    QString m_strYTitle;

    // X轴刻度文本
    QStringList m_strLstX;
    // Y轴刻度文本
    QStringList m_strLstY;

    // X轴文本框大小
    QSize m_sizeTextX;
    // Y轴文本框大小
    QSize m_sizeTextY;

    // 区域大小
    QRect m_rBoundingSize;

    // 画笔
    QPen m_pen;
    QFont m_font;

private:
    // 数据
    float m_fA;
    float m_fT;
    int m_iMax;
    QList<CVF_DATA> m_cvfDataLst;


};

#endif // LCOORDINATEITEM_H
