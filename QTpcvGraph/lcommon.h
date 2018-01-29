/************************************************************************
*   文件名称：LCommon.h
*   编写人员：LHH
*   创建日期：2018/01/02
*   功能描述：公共数据
*   备    注：
*   修改描述：
************************************************************************/

#ifndef LCOMMON_H
#define LCOMMON_H

#include <QString>
#include <QMap>

namespace LTPCV
{
    const float PI = 3.1415926;
    const int MAX_SCALE_NUM = 7;
    const int MARGIN_COORDINATE = 20;

    // 绘制图形的类型
    enum LDrawType
    {
        GRAPH,              // 曲线图
        HISTOGRAM,          // 柱状图
        OTHER               // 其他图
    };

    // 幅值、频率数据
    typedef struct CvfData
    {
        float iAmpl;          // 幅值
        float iFreq;          // 频率/周期

    }CVF_DATA;

    // 所有数据
    typedef struct LTpcvData
    {
        QMultiMap<QString, CVF_DATA> mapCvfData;
        int iMax;

    }LTPCV_DATA;




}
#endif // LCOMMON_H
