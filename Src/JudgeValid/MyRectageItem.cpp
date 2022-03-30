#include <QSGSimpleTextureNode>
#include <QQuickWindow>
#include <QtDebug>
#include "qrencode.h"
#include "MyRectageItem.h"

QMyRectageItem::QMyRectageItem(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_bNeedUpdate(true)
    ,m_sCheckInfo("Test")
{
    setFlag(ItemHasContents);
}

QSGNode *QMyRectageItem::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *)
{
    QSGSimpleTextureNode *n = static_cast<QSGSimpleTextureNode *>(node);
    if (!n)
    {
        n = new QSGSimpleTextureNode();
        UpdateTexture(n);
    }
    else if (m_bNeedUpdate)
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

void QMyRectageItem::updateString(const QString &sCheckInfo)
{
    m_sCheckInfo = sCheckInfo;
    m_bNeedUpdate = true;
}

/// ¸üÐÂÎÆÀí
void QMyRectageItem::UpdateTexture(QSGSimpleTextureNode* pTextureNode)
{
    QRcode* qrcode = QRcode_encodeString(m_sCheckInfo.toUtf8(), 2, QR_ECLEVEL_H, QR_MODE_8, 1);

    if(qrcode)
    {
        qreal width = this->width();
        qreal height = this->height();
        int qrWidth = qrcode->width > 0 ? qrcode->width : 1 ;
        qreal scaleX = qrWidth / width ;
        qreal scaleY = qrWidth / height ;

        QImage image(width,height,QImage::Format_RGB888);
        image.fill(Qt::white);
        for(int y = 0; y < width; ++y)
        {
            for(int x = 0; x < height; ++x)
            {
                uchar node = qrcode->data[int(int(y*scaleX)*qrWidth) + int(x*scaleY)];
                if(node & 0x01)
                {
                    image.setPixelColor(y,x,Qt::black);
                }
            }
        }

        QSGTexture* pTexture = window()->createTextureFromImage(image);
        pTextureNode->setTexture(pTexture);
        QRcode_free(qrcode);
        m_bNeedUpdate = false;
    }
}
