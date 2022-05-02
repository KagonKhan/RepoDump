#include "imagemetrics.h"
#include "ui_imagemetrics.h"

#include "imagedelegate.h"


ImageMetrics::ImageMetrics(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageMetrics)
    , model(new QFileSystemModel(this))
{
    ui->setupUi(this);

    initDirTree();
    loadPlugins();
    initPluginsText();
}

ImageMetrics::~ImageMetrics()
{
    delete ui;
}


void ImageMetrics::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "DRAG EVENT";
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void ImageMetrics::dropEvent(QDropEvent *event)
{
    qDebug() << "DROP EVENTT";
    QStringList accepted_types;
    accepted_types << "jpeg" << "jpg" << "png";

    foreach(const QUrl & url, event->mimeData()->urls()) {
        QString fname = url.toLocalFile();
        QFileInfo info(fname);

        if (info.exists()) {
            if (accepted_types.contains(info.suffix().trimmed(), Qt::CaseInsensitive)){
                QPixmap pixmap(fname);
                ui->RefImage->setPixmap(pixmap);


                m_ImageListModel->appendRow(new QStandardItem(QIcon(pixmap), fname));

            }
        }
    }
}



void ImageMetrics::initDirTree()
{

    model->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
    model->setNameFilters(QStringList() << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp");
    model->setNameFilterDisables(false);
    model->setRootPath(QString(""));




    QModelIndex index = model->index(QDir::cleanPath(QDir::currentPath()));

    ui->DirectoryTree->setModel(model);
    ui->DirectoryTree->scrollTo(index);



    ui->treeView_3->setModel(model);
    ui->treeView_3->scrollTo(index);

    ui->DirectoryTree->hideColumn(1);
    ui->DirectoryTree->hideColumn(2);
    ui->DirectoryTree->hideColumn(3);


    m_ImageListModel = new QStandardItemModel();
    ui->ImageList->setModel(m_ImageListModel);
    ui->ImageList->setItemDelegate(new ImageDelegate(m_ImageListModel, ui->ImageList));
    connect(ui->ImageList, &QListView::clicked, this, &ImageMetrics::onImagesListViewClicked);

}



void ImageMetrics::loadPlugins()
{
    m_Plugins.clear();

    QDir directory(QDir::currentPath());
    directory.cd(QString("Plugins"));

    auto path = QDir::cleanPath(directory.path());
    SetDllDirectoryA(path.toStdString().c_str());

    QStringList plugins = directory.entryList(QStringList() << "*.dll", QDir::Files);
    foreach(QString plugin, plugins) {
        QLibrary lib(plugin);

        NameFunction name = (NameFunction)lib.resolve("name");
        CalcFunction calc = (CalcFunction)lib.resolve("calc");

        if (calc && name){
            struct plugin temp;
             temp.name = name();
             temp.function = calc;
            m_Plugins.push_back(temp);
        }
        else
           qDebug() << lib.errorString();
    }
}

void ImageMetrics::initPluginsText()
{
    ui->MetricLayout->setAlignment(Qt::AlignTop);
    for(auto&& plugin : m_Plugins){
        QString text = "<H3>";
        text += plugin.name;
        text += "</H3>";
        text += "\n" + QString::number(plugin.function(5));
        ui->MetricLayout->addWidget(new QLabel(text, ui->ResultsPanel),Qt::AlignJustify | Qt::AlignTop);

    }
}


void ImageMetrics::on_ClearImageList_clicked()
{
    m_ImageListModel->clear();
}



void ImageMetrics::onImagesListViewClicked(const QModelIndex &index)
{
    QPixmap pixmap(m_ImageListModel->data(index).toString());

    ui->RefImage->setPixmap(pixmap);
    ui->RefImage->resize(pixmap.size());
}

