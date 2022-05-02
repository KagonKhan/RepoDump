#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QPixmap>
#include <QDebug>

#include <QStyledItemDelegate>

class ImageDelegate : public QStyledItemDelegate
{
public:
    explicit ImageDelegate(QStandardItemModel *model, QObject *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QStandardItemModel* m_model;
};

#endif // IMAGEDELEGATE_H
