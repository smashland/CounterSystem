#ifndef CSCEINFO_H
#define CSCEINFO_H

#include <QObject>
#include "ScePersonInfo.h"

class CSceInfo : public QObject
{
    Q_OBJECT
public:
    explicit CSceInfo(QObject *parent = nullptr);

    /**
     * @brief 增加人员
     * @param nID
     * @attention 如果成员ID存在则返回空
     * @return
     */
    Q_INVOKABLE ScePersonInfo* addPerson(int nID);

    /**
     * @brief 根据id查找人员
     * @param nID
     * @return
     */
    ScePersonInfo* FinPerson(int nID);

    /**
     * @brief 获取所有的人员信息
     * @return
     */
    QList<ScePersonInfo*> GetAll();

    /**
     * @brief 删除人员信息
     * @param nID
     * @return
     */
    bool DeletePerson(int nID);

    /**
     * @brief 通过Json解析人员信息
     * @param rArray
     */
    void Prase(const QJsonArray& rArray)/*(const QJsonArray& rArray)*/;

    /**
     * @brief 将人员信息保存到Json中
     * @param rArray
     */
    void Save(QJsonArray& rArray);
signals:
protected:
    void ClearMap();
private:
    QMap<int,ScePersonInfo*> m_mapId2Person;
};

#endif // CSCEINFO_H
