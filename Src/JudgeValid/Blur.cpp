#include <QSGSimpleTextureNode>
#include <QQuickWindow>
#include <QScreen>
#include "Blur.h"

QmlBlur::QmlBlur(QQuickItem *parent):QQuickItem(parent),m_bNeedUpdate(true)
{
    setFlag(ItemHasContents, true);
    m_pImage = nullptr;
    m_bNeedTransparent = false;
}

QmlBlur::~QmlBlur()
{
    delete m_pImage;
}

QSGNode *QmlBlur::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *)
{

    QSGSimpleTextureNode *n = static_cast<QSGSimpleTextureNode *>(node);
    if (!n)
    {
        n = new QSGSimpleTextureNode();
        UpdateTexture(n);
        connect(window(),&QQuickWindow::xChanged,this,&QmlBlur::needUpdate);
        connect(window(),&QQuickWindow::yChanged,this,&QmlBlur::needUpdate);
    }
    else
    {
        QSGTexture * pTexture = n->texture();
        if(nullptr != pTexture)
        {
            delete pTexture;
        }

        UpdateTexture(n);
    }
    n->setRect(boundingRect());
    return n;
}

void QmlBlur::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry,oldGeometry);

    /// 创建一个透明的图片
    if(nullptr != m_pImage)
    {
        delete m_pImage;
    }
    m_pImage = new QImage(width(),height(),QImage::Format_RGBA8888);
    m_pImage->fill(Qt::transparent);

    needUpdate();
}

void QmlBlur::needUpdate()
{
    m_bNeedUpdate = true;
    m_bNeedTransparent = true;
    update();
}

void QmlBlur::UpdateTexture(QSGSimpleTextureNode *pTextureNode)
{
    QSGTexture* pTexture = nullptr;
    if(m_bNeedTransparent)
    {
        pTexture = window()->createTextureFromImage(*m_pImage);


         m_bNeedTransparent = false;
         update();
    }
    else
    {
        QPixmap tmpMap = window()->screen()->grabWindow(0,window()->x()
                                                        ,window()->y()
                                                        ,window()->width()
                                                        ,window()->height());
         pTexture = window()->createTextureFromImage(tmpMap.toImage());
    }
    pTextureNode->setTexture(pTexture);
    pTextureNode->markDirty(QSGNode::DirtyMaterial);

}
