#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QShortcut>
#include <Qt>

double calcValue = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcValue));
    QPushButton *numButtons[10] = { nullptr };
    for(int i = 0 ; i < 10; ++i){
        QString buttonName = "Button"+QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(buttonName);

        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->ButtonAdd,       SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonSubstract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonMultiply,  SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonDivide,    SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->ButtonEquals,    SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->ButtonSign,    SIGNAL(released()), this, SLOT(ChangeNumberSign()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed()
{
    QPushButton *button = static_cast<QPushButton*>(sender());
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();

    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0)
        ui->Display->setText(buttonVal);
    else{
        QString newValue = displayVal + buttonVal;
        double dNewValue = newValue.toDouble();
        ui->Display->setText(QString::number(dNewValue, 'g', 16));
    }
}

void MainWindow::MathButtonPressed()
{
    divTrigger = false;    mulTrigger = false;    addTrigger = false;    subTrigger = false;

    QString displayValue = ui->Display->text();
    calcValue = displayValue.toDouble();
    QPushButton *button = static_cast<QPushButton*>(sender());
    QString buttonValue = button->text();

    if(QString::compare(buttonValue, "/", Qt::CaseInsensitive) == 0)
        divTrigger = true;
    else if(QString::compare(buttonValue, "*", Qt::CaseInsensitive) == 0)
        mulTrigger = true;
    else if(QString::compare(buttonValue, "+", Qt::CaseInsensitive) == 0)
        addTrigger = true;
    else if(QString::compare(buttonValue, "-", Qt::CaseInsensitive) == 0)
        subTrigger = true;

    ui->Display->setText("");

}

void MainWindow::EqualButton()
{
    double solution = 0.0;
    QString displayValue = ui->Display->text();
    double dDisplayValue = displayValue.toDouble();

    if(addTrigger || subTrigger || mulTrigger || divTrigger){
        if (addTrigger)
            solution =  calcValue + dDisplayValue;
        else if (subTrigger)
            solution =  calcValue - dDisplayValue;
        else if (mulTrigger)
            solution =  calcValue * dDisplayValue;
        else if (divTrigger)
            solution =  calcValue / dDisplayValue;
    }

    ui->Display->setText(QString::number(solution));
}

void MainWindow::ChangeNumberSign()
{
    QString displayValue = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    if(reg.match(displayValue).hasMatch()){
        double dDisplayValue = displayValue.toDouble();
        double dDisplayValueSign = -1 * dDisplayValue;
        ui->Display->setText(QString::number(dDisplayValueSign));
    }
}




























