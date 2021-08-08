#include "widget.h"
#include "ui_widget.h"

#include "EQFilterGroup.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setBandpassFrequency(1);

    _player = new AudioPlayer(this);

    on_verticalSlider_valueChanged(100);
    on_verticalSlider_2_valueChanged(100);
    on_verticalSlider_3_valueChanged(100);
    on_verticalSlider_4_valueChanged(100);
    on_verticalSlider_5_valueChanged(100);
    on_verticalSlider_6_valueChanged(100);
    on_verticalSlider_7_valueChanged(100);
    on_verticalSlider_8_valueChanged(100);
    on_verticalSlider_9_valueChanged(100);
    on_verticalSlider_10_valueChanged(100);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setMusicStyle(QList<int> &style)
{
    if (!style.isEmpty()) {

        ui->verticalSlider->setValue(style[0]);

        ui->verticalSlider_2->setValue(style[1]);

        ui->verticalSlider_3->setValue(style[2]);

        ui->verticalSlider_4->setValue(style[3]);

        ui->verticalSlider_5->setValue(style[4]);

        ui->verticalSlider_6->setValue(style[5]);

        ui->verticalSlider_7->setValue(style[6]);

        ui->verticalSlider_8->setValue(style[7]);

        ui->verticalSlider_9->setValue(style[8]);

        ui->verticalSlider_10->setValue(style[9]);
    }
}

void Widget::clearFdacoefs()
{
    _player->reset();

    EQFilterGroup::clearFdacoefs();
}

void Widget::setBandpassFrequency(int status)
{
    if (status == 1) {
        EQFilterGroup::updateCoefficient(21,    42,   1);
        EQFilterGroup::updateCoefficient(42,    85,   2);
        EQFilterGroup::updateCoefficient(85,    170,  3);
        EQFilterGroup::updateCoefficient(170,   339,  4);
        EQFilterGroup::updateCoefficient(339,   679,  5);
        EQFilterGroup::updateCoefficient(679,   1385, 6);
        EQFilterGroup::updateCoefficient(1385,  2715, 7);
        EQFilterGroup::updateCoefficient(2715,  5431, 8);
        EQFilterGroup::updateCoefficient(5431,  10861, 9);
        EQFilterGroup::updateCoefficient(10861, 21722, 10);

        bandwidthStatus = 1;

    } else if (status == 2) {

        EQFilterGroup::updateCoefficient(60,    100,   1);
        EQFilterGroup::updateCoefficient(100,   200,   2);
        EQFilterGroup::updateCoefficient(200,   500,   3);
        EQFilterGroup::updateCoefficient(500,   1000,  4);
        EQFilterGroup::updateCoefficient(1000,  2000,  5);
        EQFilterGroup::updateCoefficient(2000,  4000,  6);
        EQFilterGroup::updateCoefficient(4000,  8000,  7);
        EQFilterGroup::updateCoefficient(8000,  12000, 8);
        EQFilterGroup::updateCoefficient(12000, 16000, 9);
        EQFilterGroup::updateCoefficient(16000, 20000, 10);

        bandwidthStatus = 2;
    }
}


void Widget::on_verticalSlider_valueChanged(int value)
{
    float gain = float(value) / 100;

    float coeff = 1.0;
    if (bandwidthStatus == 1) {
        coeff = 0.1;
    } else if (bandwidthStatus == 2) {
        coeff = 0.5;
    }

    _player->set_FC_HZ_32(gain, coeff);
}

void Widget::on_verticalSlider_2_valueChanged(int value)
{
    float gain = float(value) / 100;

    float coeff = 1.0;
    if (bandwidthStatus == 1) {
        coeff = 0.2;
    } else if (bandwidthStatus == 2) {
        coeff = 0.6;
    }

    _player->set_FC_HZ_63(gain, coeff);
}

void Widget::on_verticalSlider_3_valueChanged(int value)
{
    float gain = float(value) / 100;

    float coeff = 1.0;
    if (bandwidthStatus == 1) {
        coeff = 0.4;
    } else if (bandwidthStatus == 2) {
        coeff = 0.7;
    }

    _player->set_FC_HZ_125(gain, coeff);
}

void Widget::on_verticalSlider_4_valueChanged(int value)
{
    float gain = float(value) / 100;

    float coeff = 0.8;

    _player->set_FC_HZ_250(gain, coeff);
}

void Widget::on_verticalSlider_5_valueChanged(int value)
{
    float gain = float(value) / 100;

    float coeff = 0.9;

    _player->set_FC_HZ_500(gain, coeff);
}

void Widget::on_verticalSlider_6_valueChanged(int value)
{
    float gain = float(value) / 100;
    _player->set_FC_HZ_1000(gain);
}

void Widget::on_verticalSlider_7_valueChanged(int value)
{
    float gain = float(value) / 100;
    _player->set_FC_HZ_2000(gain);
}

void Widget::on_verticalSlider_8_valueChanged(int value)
{
    float gain = float(value) / 100;
    _player->set_FC_HZ_4000(gain);
}

void Widget::on_verticalSlider_9_valueChanged(int value)
{
    float gain = float(value) / 100;
    _player->set_FC_HZ_8000(gain);
}

void Widget::on_verticalSlider_10_valueChanged(int value)
{
    float gain = float(value) / 100;
    _player->set_FC_HZ_16000(gain);
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    musicStyle.clear();

    ui->comboBox_2->blockSignals(true);
    ui->comboBox_2->setCurrentIndex(-1);
    ui->comboBox_2->blockSignals(false);

    if (bandwidthStatus == 2) {
        setBandpassFrequency(1);
    }

    switch (index) {

    case 0:
        // 0,0,0, 0,0,0,0,0,0,0
        musicStyle << 100 << 100 << 100 << 100 << 100
                   << 100 << 100 << 100 << 100 << 100;
        break;

    case 1:
        // 0,0,0, 1,2, 3,3,2, 1,0
        musicStyle << 100 << 100 << 100 << 110 << 120
                   << 130 << 130 << 120 << 110 << 100;
        break;

    case 2:
        // 9,8,5,2, 1,0,-3,-4,-3, 0
        musicStyle << 190 << 180 << 150 << 120 << 110
                   << 100 << 70 << 60 << 70 << 100;
        break;
    case 3:
        // 8,8,8, 7,4,0,-3,-5,-7,-9
        musicStyle << 180 << 180 << 180 << 170 << 140
                   << 100 << 70 << 50 << 30 << 10;
        break;

    case 4:
        // -9,-8,-7,-6,-3,1,5,8,10, 12
        musicStyle << 10 << 20 << 30 << 40 << 70
                   << 110 << 150 << 180 << 200 << 220;
        break;

    case 5:
        // -2,-1, 0,2,3, 2,0,-2,-2,-1
        musicStyle << 80 << 90 << 100 << 120 << 130
                   << 120 << 100 << 80 << 80 << 90;
        break;

    case 6:
        // 6,5,2,-2,-5,-2,0,3,5, 6
        musicStyle << 160 << 150 << 120 << 80 << 50
                   << 80 << 100 << 130 << 150 << 160;
        break;

    case 7:
        // 2,1,0,0,-1,0,1,2,3,4
        musicStyle << 120 << 110 << 100 << 100 << 90
                   << 100 << 110 << 120 << 130 << 140;
        break;

    case 8:
        // 8,7,6,3,2, 0,-1,-2,-1,0
        musicStyle << 180 << 170 << 160 << 130 << 120
                   << 100 << 90 << 80 << 90 << 100;
        break;

    case 9:
        //4,4,3,2, 0,0,0,0,0,4
        musicStyle << 140 << 140 << 130 << 120 << 100
                   << 100 << 100 << 100 << 100 << 140;
        break;

    case 10:
        //4 2 0 -3 -6 -6 -3 0 1 3
        musicStyle << 140 << 120 << 100 << 70 << 40
                   << 40 << 70 << 100 << 110 << 130;
        break;

    case 11:
        //7 6 3 0 0 -4 -6 -6 0 0
        musicStyle << 170 << 160 << 130 << 100 << 100
                   << 60 << 40 << 40 << 100 << 100;
        break;
    case 12:
        //3 6 8 3 -2 0 4 7 9 10
        musicStyle << 130 << 160 << 180 << 130 << 80
                   << 100 << 140 << 170 << 190 << 200;
        break;
    case 13:
        //0 0 0 0 0 0 -6 -6 -6 -8
        musicStyle << 100 << 100 << 100 << 100 << 100
                   << 100 << 40 << 40 << 40 << 20;
        break;
    case 14:
        //0 0 1 4 4 4 0 1 3 3
        musicStyle << 100 << 100 << 110 << 140 << 140
                   << 140 << 100 << 110 << 130 << 130;
        break;
    case 15:
        //5 4 2 0 -2 0 3 6 7 8
        musicStyle << 150 << 140 << 120 << 100 << 80
                   << 100 << 130 << 160 << 170 << 180;
        break;
    case 16:
        //6 5 0 -5 -4 0 6 8 8 7
        musicStyle << 160 << 150 << 100 << 50 << 60
                   << 100 << 160 << 180 << 180 << 170;
        break;
    case 17:
        //7 4 -4 7 -2 1 5 7 9 9
        musicStyle << 170 << 140 << 60 << 170 << 80
                   << 100 << 150 << 170 << 190 << 190;
        break;
    case 18:
        //5 6 2 -5 1 1 -5 3 8 5
        musicStyle << 150 << 160 << 120 << 50 << 100
                   << 100 << 50 << 130 << 180 << 150;
        break;
    case 19:
        //-2 -1 -1 0 3 4 3 0 0 1
        musicStyle << 80 << 90 << 90 << 100 << 130
                   << 140 << 130 << 100 << 100 << 110;
        break;

    default:
        break;
    }

    setMusicStyle(musicStyle);
}


void Widget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("文件对话框！"),
                                                    "F:",
                                                    tr("音乐文件(*mp3)"));


    qDebug() << "filename : " << fileName;

    setWindowTitle(fileName);

    _player->setSourceFilename(fileName);

    _player->play();
}


void Widget::on_lineEdit_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit->text().toInt();
    int Fc2 = ui->lineEdit_2->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 1);
}

void Widget::on_lineEdit_2_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit->text().toInt();
    int Fc2 = ui->lineEdit_2->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 1);

}

void Widget::on_lineEdit_3_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_3->text().toInt();
    int Fc2 = ui->lineEdit_4->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 2);

}

void Widget::on_lineEdit_4_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_3->text().toInt();
    int Fc2 = ui->lineEdit_4->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 2);

}

void Widget::on_lineEdit_5_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_5->text().toInt();
    int Fc2 = ui->lineEdit_6->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 3);
}

void Widget::on_lineEdit_6_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_5->text().toInt();
    int Fc2 = ui->lineEdit_6->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 3);

}

void Widget::on_lineEdit_7_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_7->text().toInt();
    int Fc2 = ui->lineEdit_8->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 4);
}

void Widget::on_lineEdit_8_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_7->text().toInt();
    int Fc2 = ui->lineEdit_8->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 4);
}

void Widget::on_lineEdit_9_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_9->text().toInt();
    int Fc2 = ui->lineEdit_10->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 5);
}

void Widget::on_lineEdit_10_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_9->text().toInt();
    int Fc2 = ui->lineEdit_10->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 5);
}

void Widget::on_lineEdit_11_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_11->text().toInt();
    int Fc2 = ui->lineEdit_12->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 6);
}

void Widget::on_lineEdit_12_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_11->text().toInt();
    int Fc2 = ui->lineEdit_12->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 6);
}

void Widget::on_lineEdit_13_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_13->text().toInt();
    int Fc2 = ui->lineEdit_14->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 7);
}

void Widget::on_lineEdit_14_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_13->text().toInt();
    int Fc2 = ui->lineEdit_14->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 7);
}

void Widget::on_lineEdit_15_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_15->text().toInt();
    int Fc2 = ui->lineEdit_16->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 8);
}

void Widget::on_lineEdit_16_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_15->text().toInt();
    int Fc2 = ui->lineEdit_16->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 8);
}

void Widget::on_lineEdit_17_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_17->text().toInt();
    int Fc2 = ui->lineEdit_18->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 9);
}

void Widget::on_lineEdit_18_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_17->text().toInt();
    int Fc2 = ui->lineEdit_18->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 9);
}

void Widget::on_lineEdit_19_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_19->text().toInt();
    int Fc2 = ui->lineEdit_20->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 10);
}

void Widget::on_lineEdit_20_editingFinished()
{
    this->setFocus();

    int Fc1 = ui->lineEdit_19->text().toInt();
    int Fc2 = ui->lineEdit_20->text().toInt();

    EQFilterGroup::updateCoefficient(Fc1, Fc2, 10);
}

void Widget::on_comboBox_2_currentIndexChanged(int index)
{
    musicStyle.clear();

    // blockSignals
    ui->comboBox->blockSignals(true);
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox->blockSignals(false);

    if (bandwidthStatus == 1) {
        setBandpassFrequency(2);
    }

    switch (index) {
    case 0:
        // 0,0,0, 0,0,0,0,0,0,0
        musicStyle << 100 << 100 << 100 << 100 << 100
                   << 100 << 100 << 100 << 100 << 100;
        break;

    case 1:
        //0, 0, 0, 0, 0, 0, -7, -7, -7, -9
        musicStyle << 100 << 100 << 100 << 100 << 100
                   << 100 << 30 << 30 << 30 << 10;
        break;

    case 2:
        //0, 0, 8, 5, 5, 5, 3, 0, 0, 0
        musicStyle << 100 << 100 << 180 << 150 << 150
                   << 150 << 130 << 100 << 100 << 100;
        break;
    case 3:
        //9, 7, 2, 0, 0, -5, -7, -7, 0, 0
        musicStyle << 190 << 170 << 120 << 100 << 100
                   << 50 << 30 << 30 << 100 << 100;
        break;

    case 4:
        //-8, 9, 9, 5, 1, -4, -8, -10, -11, -11
        musicStyle << 20 << 190 << 190 << 150 << 110
                   << 60 << 20 << 8 << 6 << 6;
        break;

    case 5:
        //-9, -9, -9, -4, 2, 11, 16, 16, 16, 16
        musicStyle << 10 << 10 << 10 << 60 << 120
                   << 200 << 200 << 200 << 200 << 200;
        break;

    case 6:
        //4, 11, 5, -3, -2, 1, 4, 9, 12, 14
        musicStyle << 140 << 200 << 150 << 70 << 80
                   << 110 << 140 << 190 << 200 << 200;
        break;

    case 7:
        //10, 10, 5, 5, 0, -4, -4, -4, 0, 0
        musicStyle << 200 << 200 << 150 << 150 << 100
                   << 60 << 60 << 60 << 100 << 100;
        break;

    case 8:
        //-4, 0, 4, 5, 5, 5, 4, 2, 2, 2
        musicStyle << 60 << 100 << 140 << 150 << 150
                   << 150 << 140 << 120 << 120 << 120;
        break;

    case 9:
        //7, 7, 0, 0, 0, 0, 0, 0, 7, 7
        musicStyle << 170 << 170 << 100 << 100 << 100
                   << 100 << 100 << 100 << 170 << 170;
        break;

    case 10:
        //-1, 4, 7, 8, 5, 0, -2, -2, -1, -1
        musicStyle << 90 << 140 << 170 << 180 << 150
                   << 100 << 80 << 80 << 90 << 90;
        break;

    case 11:
        //0, 0, 0, -5, 0, 6, 6, 0, 0, 0
        musicStyle << 100 << 100 << 100 << 50 << 100
                   << 160 << 160 << 100 << 100 << 100;
        break;

    case 12:
        //8, 4, -5, -8, -3, 4, 8, 11, 11, 11
        musicStyle << 180 << 140 << 50 << 20 << 70
                   << 140 << 180 << 200 << 200 << 200;
        break;

    case 13:
        //-2, -4, -4, 0, 4, 5, 8, 9, 11, 9
        musicStyle << 80 << 60 << 60 << 100 << 140
                   << 150 << 180 << 190 << 200 << 190;
        break;

    case 14:
        //4, 1, 0, -2, 0, 4, 8, 9, 11, 12
        musicStyle << 140 << 110 << 100 << 80 << 100
                   << 140 << 180 << 190 << 200 << 200;
        break;

    case 15:
        //4, 4, 2, 0, -4, -5, -3, 0, 2, 8
        musicStyle << 140 << 140 << 120 << 100 << 60
                   << 50 << 70 << 100 << 120 << 180;
        break;

    case 16:
        //8, 5, 0, -5, -4, 0, 8, 9, 9, 8
        musicStyle << 180 << 150 << 100 << 50 << 60
                   << 100 << 180 << 190 << 190 << 180;
        break;

    default:
        break;
    }

    setMusicStyle(musicStyle);
}

void Widget::on_pushButton_2_clicked()
{
    clearFdacoefs();
}
