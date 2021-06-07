#ifndef WIDGET_H
#define WIDGET_H

#include "AudioPlayer.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // 设置音乐风格
    void setMusicStyle(QList<int> &style);

    void clearFdacoefs();

    void setBandpassFrequency(int status);

private slots:
    void on_verticalSlider_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

    void on_verticalSlider_3_valueChanged(int value);

    void on_verticalSlider_4_valueChanged(int value);

    void on_verticalSlider_5_valueChanged(int value);

    void on_verticalSlider_6_valueChanged(int value);

    void on_verticalSlider_7_valueChanged(int value);

    void on_verticalSlider_8_valueChanged(int value);

    void on_verticalSlider_9_valueChanged(int value);

    void on_verticalSlider_10_valueChanged(int value);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_4_editingFinished();

    void on_lineEdit_5_editingFinished();

    void on_lineEdit_6_editingFinished();

    void on_lineEdit_7_editingFinished();

    void on_lineEdit_8_editingFinished();

    void on_lineEdit_9_editingFinished();

    void on_lineEdit_10_editingFinished();

    void on_lineEdit_11_editingFinished();

    void on_lineEdit_12_editingFinished();

    void on_lineEdit_13_editingFinished();

    void on_lineEdit_14_editingFinished();

    void on_lineEdit_15_editingFinished();

    void on_lineEdit_16_editingFinished();

    void on_lineEdit_17_editingFinished();

    void on_lineEdit_18_editingFinished();

    void on_lineEdit_19_editingFinished();

    void on_lineEdit_20_editingFinished();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

    int bandwidthStatus = 0;

    AudioPlayer *_player;

    QList<int> musicStyle;
};
#endif // WIDGET_H
