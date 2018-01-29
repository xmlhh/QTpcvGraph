#ifndef LEONWGT_H
#define LEONWGT_H

#include "LCommon.h"
#include "LTpcvView.h"
#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
class LeonWgt;
}

class LeonWgt : public QWidget
{
    Q_OBJECT

public:
    explicit LeonWgt(QWidget *parent = 0);
    ~LeonWgt();

    // 初始化界面
    int InitUI();

    // 初始化数据
    int InitData();

    // 测试数据
    void SetData();

    // 初始化坐标
    void InitCoordinate(LTPCV::LTPCV_DATA tpcvData);

    // 重置窗口大小
    void resizePreViewWgt();

    // 设置X轴标题
    void SetXTitle(const QString &strXTitle);
    // 设置Y轴标题
    void SetYTitle(const QString &strYTitle);
    // 设置X轴坐标
    void SetXScale(const QStringList &strLstX);
    // 设置Y轴坐标
    void SetYScale(const QStringList &strLstY);


private:
    Ui::LeonWgt *ui;

    LTpcvView *m_pLTpcvView;
    // 数据结构
    LTPCV_DATA m_lTpcvData;

};

#endif // LEONWGT_H
