#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Lab_3");
    this->setWindowIcon(QIcon(":/new/prefix1/img/880785.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_conversion_clicked()
{
    int current_koof = ui->comboBox_2->currentText().toInt();

    QString first_number = ui->lineEdit->text();

    if (check_number(first_number, ui->comboBox->currentText().toInt())) {
        int dec_number = to_dec(first_number.toStdString(), ui->comboBox->currentText().toInt());

        QString current_number = to_current(dec_number, current_koof);

        ui->lineEdit_2->setText(current_number);
    }
    else {
        ui->lineEdit_2->setText("Error");
    }
}

bool MainWindow::check_number(QString first_number, int koof)
{
    std::string number = first_number.toStdString();

    bool flag;

    for (int i = 0; i < number.length(); i++)
    {
        if (number[i] - 48 >= koof)
            flag = false;
        else
            flag = true;
        if (koof > 10)
        {
            if (number[i] > 'F') flag = false;
            else {
                if (number[i]  < '0') flag = false;
                else {
                    if (number[i] > '9' && number[i] < 'A') flag = false;
                    else flag = true;
                }
            }

        }
    }

    return flag;
}

int MainWindow::to_dec(std::string number, int koof)
{
    int ans = 0;

    if (ui->comboBox->currentText().toInt() > 10) {
        QString str = QString::fromStdString(number);
        bool t;
        ans = str.toInt(&t, 16);
    } else {

        int serial_number = number.length() - 1;

        for (int i = 0; i < number.length(); i++)
        {
            ans += (number[i] - 48) * pow(koof, serial_number);
            serial_number--;
        }
    }

    return ans;
}

QString MainWindow::to_current(int dec_number, int koof)
{
    QString current_number;

    if (koof > 10) {
        current_number = QString("%1").arg(dec_number, 0, koof).toUpper();
    } else {
        while (dec_number > 0) {
            current_number = QString::number(dec_number % koof) + current_number;
            dec_number /= koof;
        }
    }
    return current_number;
}
