#ifndef CSCEINFO_H
#define CSCEINFO_H

#include <QObject>
#include "ScePersonInfo.h"

class CSceInfo : public QObject
{
    Q_OBJECT
public:
    explicit CSceInfo(QObject *parent = nullptr);
    Q_PROPERTY(QString sceName READ getSceName WRITE setSceName NOTIFY sceNameChanged)
    Q_PROPERTY(QList<QObject*> listPerson MEMBER m_listPerson NOTIFY personChanged)

    /**
      * @brief 设置方案名称
      * @param sName
      */
    Q_INVOKABLE void setSceName(const QString &sName);
    Q_INVOKABLE QString getSceName(){ return(m_sSceName);}

    /**
     * @brief 增加人员
     * @param nID
     * @attention 如果成员ID存在则返回空
     * @return
     */
    Q_INVOKABLE ScePersonInfo* addPerson(int nID);
    Q_INVOKABLE ScePersonInfo* addPerson1(int nID,ScePersonInfo* pScePersonInfo);

    /**
     * @brief 根据id修改人员信息
     * @param nID
     * @return
     */
    Q_INVOKABLE ScePersonInfo* modifyPerson(int nID);

    /**
     * @brief 根据id查找人员
     * @param nID
     * @return
     */
    Q_INVOKABLE QObject *findPerson(int nID);

    /**
     * @brief 获取所有的人员信息
     * @return
     */
    Q_INVOKABLE QList<QObject*> getAll();

    /**
     * @brief 得到人员数量
     * @return
     */
    Q_INVOKABLE int getCount(){return m_mapId2Person.size();}

    /**
     * @brief 删除人员信息
     * @param nID
     * @return
     */
    Q_INVOKABLE bool deletePerson(int nID);

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
    void sceNameChanged(QString);
    void personChanged();
protected:
    void ClearMap();
private:
    QString m_sSceName;     ///方案名称
    QList<QObject*> m_listPerson;
    QMap<int,ScePersonInfo*> m_mapId2Person;
};

#endif // CSCEINFO_H
