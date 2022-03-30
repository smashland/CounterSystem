#ifndef MYRECTAGEITEM_H
#define MYRECTAGEITEM_H

#include <QQuickItem>

class QSGSimpleTextureNode;

class QMyRectageItem : public QQuickItem
{
    Q_OBJECT
public:
    QMyRectageItem(QQuickItem *parent=nullptr);

protected:
    QSGNode* updatePaintNode(QSGNode *node, UpdatePaintNodeData *);
signals:

public slots:
    void updateString(const QString& sCheckInfo);
protected:
    void UpdateTexture(QSGSimpleTextureNode *pTextureNode);
private:
    bool    m_bNeedUpdate;
    QString m_sCheckInfo;
};

#endif // MYRECTAGEITEM_H
