#include "EQFilterGroup.h"
#include "fdacoefs.h"

#include "fir1.h"
#include "fir1_terminate.h"
#include "rt_nonfinite.h"

#include <iostream>
#include <QDebug>

EQFilterGroup::EQFilterGroup()
{

}

void  EQFilterGroup::filterCoefficient(double Fc01, double Fc02, double b[])
{
    /*-------计算滤波器系数---------*/

    double dv[2] = {0};
    dv[0] = Fc01 / (44100 / 2);
    dv[1] = Fc02 / (44100 / 2);

    // "bandpass";
    char b_cv[8] = {'b', 'a', 'n', 'd', 'p', 'a', 's', 's'};

    double dv1[100] = {
        0.0800, 0.0809, 0.0837, 0.0883, 0.0947, 0.1030, 0.1130, 0.1247, 0.1380, 0.1530,
        0.1696, 0.1876, 0.2071, 0.2279, 0.2499, 0.2732, 0.2975, 0.3228, 0.3489, 0.3758,
        0.4034, 0.4316, 0.4601, 0.4890, 0.5181, 0.5473, 0.5765, 0.6055, 0.6342, 0.6626,
        0.6905, 0.7177, 0.7443, 0.7700, 0.7948, 0.8186, 0.8412, 0.8627, 0.8828, 0.9016,
        0.9189, 0.9347, 0.9489, 0.9614, 0.9723, 0.9814, 0.9887, 0.9942, 0.9979, 0.9998,
        0.9998, 0.9979, 0.9942, 0.9887, 0.9814, 0.9723, 0.9614, 0.9489, 0.9347, 0.9189,
        0.9016, 0.8828, 0.8627, 0.8412, 0.8186, 0.7948, 0.7700, 0.7443, 0.7177, 0.6905,
        0.6626, 0.6342, 0.6055, 0.5765, 0.5473, 0.5181, 0.4890, 0.4601, 0.4316, 0.4034,
        0.3758, 0.3489, 0.3228, 0.2975, 0.2732, 0.2499, 0.2279, 0.2071, 0.1876, 0.1696,
        0.1530, 0.1380, 0.1247, 0.1130, 0.1030, 0.0947, 0.0883, 0.0837, 0.0809, 0.0800
    };


    // "scale";
    char cv1[5] = {'s', 'c', 'a', 'l', 'e'};

    // double ba[100];
    double a;

    fir1(99, dv, b_cv, dv1, cv1, b, &a);

    // fir1_terminate();
}

void EQFilterGroup::updateCoefficient(double Fc01, double Fc02, int coefficientGroup)
{
    double ba[100] = {0};

    float *znum = nullptr;

    switch (coefficientGroup) {
    case 1:
        znum  = FC_HZ_32;
        break;
    case 2:
        znum  = FC_HZ_63;
        break;
    case 3:
        znum  = FC_HZ_125;
        break;
    case 4:
        znum  = FC_HZ_250;
        break;
    case 5:
        znum  = FC_HZ_500;
        break;
    case 6:
        znum  = FC_HZ_1000;
        break;
    case 7:
        znum  = FC_HZ_2000;
        break;
    case 8:
        znum  = FC_HZ_4000;
        break;
    case 9:
        znum  = FC_HZ_8000;
        break;
    case 10:
        znum  = FC_HZ_16000;
        break;

    default:
        break;
    }

    memset(ba, 0,  100);
    filterCoefficient(Fc01, Fc02, ba);
    for (int i = 0; i < 100; i++) {
        znum[i] = ba[i];
    }
}

void EQFilterGroup::clearFdacoefs()
{
    for (int i = 0; i < 100; i++) {
        FC_HZ_32[i] = 0.0;
        FC_HZ_63[i] = 0.0;
        FC_HZ_125[i] = 0.0;
        FC_HZ_250[i] = 0.0;
        FC_HZ_500[i] = 0.0;
        FC_HZ_1000[i] = 0.0;
        FC_HZ_2000[i] = 0.0;
        FC_HZ_4000[i] = 0.0;
        FC_HZ_8000[i] = 0.0;
        FC_HZ_16000[i] = 0.0;
    }
}

QBuffer *EQFilterGroup::filter(const QAudioBuffer &buffer)
{
    QVector<float> channel1;
    QVector<float> channel2;
    decode_channel<qint32>(channel1, channel2, buffer);
    QVector<float> filtered_channel1;
    QVector<float> filtered_channel2;

    //    qDebug() << _FC_HZ_32 << " " << _FC_HZ_63 << " " << _FC_HZ_125 << " " << _FC_HZ_250 << " "
    //             << _FC_HZ_500 << " " <<  _FC_HZ_1000 << " " << _FC_HZ_2000 << " " << _FC_HZ_4000 << " "
    //             << _FC_HZ_8000 << " " << _FC_HZ_16000;

    for (auto i = 0; i < channel1.count() ; ++i) {
        float left =    _FC_HZ_32 * band_filter_channel(channel1[i], 0, 1) +
                        _FC_HZ_63 * band_filter_channel(channel1[i], 0, 2) +
                        _FC_HZ_125 * band_filter_channel(channel1[i], 0, 3) +
                        _FC_HZ_250 * band_filter_channel(channel1[i], 0, 4) +
                        _FC_HZ_500 * band_filter_channel(channel1[i], 0, 5) +
                        _FC_HZ_1000 * band_filter_channel(channel1[i], 0, 6) +
                        _FC_HZ_2000 * band_filter_channel(channel1[i], 0, 7) +
                        _FC_HZ_4000 * band_filter_channel(channel1[i], 0, 8) +
                        _FC_HZ_8000 * band_filter_channel(channel1[i], 0, 9) +
                        _FC_HZ_16000 * band_filter_channel(channel1[i], 0, 10);

        filtered_channel1.append(left);
    }

    QByteArray array;
    encode_channel<qint32>(filtered_channel1, filtered_channel2, array);
    auto qb = new QBuffer();
    qb->setData(array);
    return qb;
}



float EQFilterGroup::band_filter_channel(float invar, float initval, int setic)
{
    float sumnum = 0.0;
    static float states[99] = {0};

    float *znum = nullptr;

    switch (setic) {
    case 1:
        znum  = FC_HZ_32;
        break;
    case 2:
        znum  = FC_HZ_63;
        break;
    case 3:
        znum  = FC_HZ_125;
        break;
    case 4:
        znum  = FC_HZ_250;
        break;
    case 5:
        znum  = FC_HZ_500;
        break;
    case 6:
        znum  = FC_HZ_1000;
        break;
    case 7:
        znum  = FC_HZ_2000;
        break;
    case 8:
        znum  = FC_HZ_4000;
        break;
    case 9:
        znum  = FC_HZ_8000;
        break;
    case 10:
        znum  = FC_HZ_16000;
        break;

    default:
        break;
    }


    for (int i = 0; i < 99; i++) {
        sumnum += states[i] * znum[i];
        if (i < 98)
            states[i] = states[i + 1];
    }
    states[98] = invar;
    sumnum += states[98] * znum[0];
    return sumnum  * 0.4;
}




