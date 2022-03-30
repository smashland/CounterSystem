#ifndef BLUR_H
#define BLUR_H

#include <QQuickItem>

class  QSGSimpleTextureNode;
class QmlBlur : public QQuickItem
{
    Q_OBJECT
public:
    QmlBlur(QQuickItem *parent = nullptr);
    ~QmlBlur();
protected:
    QSGNode* updatePaintNode(QSGNode *node, UpdatePaintNodeData *);
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

signals:

public slots:
    void needUpdate();
private:
    void UpdateTexture(QSGSimpleTextureNode *pTextureNode);
private:
    bool m_bNeedUpdate;
    bool m_bNeedTransparent;
    QImage* m_pImage;
};

#endif // BLUR_H
