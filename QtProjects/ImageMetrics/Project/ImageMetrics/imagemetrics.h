#ifndef IMAGEMETRICS_H
#define IMAGEMETRICS_H

#include <QMainWindow>
#include <QApplication>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QTreeView>
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QStandardItemModel>

#include <QLibrary>
#include <QLabel>


#include <vector>
#include <Windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageMetrics; }
QT_END_NAMESPACE

class ImageMetrics : public QMainWindow
{
    Q_OBJECT

public:
    ImageMetrics(QWidget *parent = nullptr);
    ~ImageMetrics();


    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;


private slots:
    void onImagesListViewClicked(const QModelIndex& index);
    void on_ClearImageList_clicked();


private:
    Ui::ImageMetrics *ui;
    QFileSystemModel *model;

    QStandardItemModel* m_ImageListModel;

    QMimeData* mimeData;

    void initDirTree();





private: // DLL space
    typedef double(*CalcFunction)(double);
    typedef char*(*NameFunction)(void);
    struct plugin{
        QString name;
        CalcFunction function;
    };

    std::vector<plugin> m_Plugins;
    void loadPlugins();
    void initPluginsText();

};
#endif // IMAGEMETRICS_H
