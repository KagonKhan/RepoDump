#include "imagedelegate.h"

ImageDelegate::ImageDelegate(QStandardItemModel *model, QObject *parent) :
    QStyledItemDelegate(parent),
    m_model(model)
{

}

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPixmap pix(m_model->data(index).toString());
    QRect optionRect = option.rect;
    painter->drawPixmap(optionRect.x() + 5,
                        optionRect.y() + 5,
                        optionRect.width() - 10,
                        optionRect.height() - 10 ,
                        pix);
}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    result.setHeight(140);
    result.setWidth(140);
    return QSize(140, 140);
}
