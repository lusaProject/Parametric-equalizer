#ifndef EQFILTERGROUP_H
#define EQFILTERGROUP_H

#include <QAudioBuffer>
#include <QBuffer>
#include <QByteArray>
#include <QVector>
#include <cmath>
#include <QDebug>

class EQFilterGroup
{
public:
    EQFilterGroup();

    static void filterCoefficient(double Fc01, double Fc02, double b[]);

    static  void updateCoefficient(double Fc01, double Fc02, int coefficientGroup);

    static  void clearFdacoefs();

    void set_FC_HZ_32(float gain, float adaptation)
    {
        _FC_HZ_32 = gain * adaptation;
    }
    void set_FC_HZ_63(float gain, float adaptation)
    {
        _FC_HZ_63 = gain * adaptation;
    }
    void set_FC_HZ_125(float gain, float adaptation)
    {
        _FC_HZ_125 = gain * adaptation;
    }
    void set_FC_HZ_250(float gain, float adaptation)
    {
        _FC_HZ_250 = gain * adaptation;
    }
    void set_FC_HZ_500(float gain, float adaptation)
    {
        _FC_HZ_500 = gain * adaptation;
    }
    void set_FC_HZ_1000(float gain)
    {
        _FC_HZ_1000 = gain;
    }
    void set_FC_HZ_2000(float gain)
    {
        _FC_HZ_2000 = gain;
    }
    void set_FC_HZ_4000(float gain)
    {
        _FC_HZ_4000 = gain;
    }
    void set_FC_HZ_8000(float gain)
    {
        _FC_HZ_8000 = gain;
    }
    void set_FC_HZ_16000(float gain)
    {
        _FC_HZ_16000 = gain;
    }


    template<class T>
    void decode_channel(QVector<float> &channel1, QVector<float> &channel2, QAudioBuffer const &buffer)
    {
        T *data = (T *)(buffer.data());
        size_t len = buffer.sampleCount();

        for (size_t i = 0; i < len; i += 1) {
            T left = data[i];

            left = std::isnan(left) ? 0.0 : left;

            channel1.append(float(left) / std::numeric_limits<T>::max());
        }
    }

    template<class T>
    void encode_channel(QVector<float> const &channel1, QVector<float> const &channel2, QByteArray &bytes)
    {
        for (size_t i = 0; i < channel1.count() ; ++i) {
            float left = channel1[i] > 1.0 ? 1.0 : channel1[i];

            T lpcm = T(std::floor(left * std::numeric_limits<T>::max()));
            bytes.append((char *)&lpcm, sizeof(lpcm));
        }
    }

    QBuffer *filter(QAudioBuffer const &buffer);

    float band_filter_channel(float invar, float initval, int setic);

private:

    float _FC_HZ_32 = 1.0;
    float _FC_HZ_63 = 1.0;
    float _FC_HZ_125 = 1.0;
    float _FC_HZ_250 = 1.0;
    float _FC_HZ_500 = 1.0;
    float _FC_HZ_1000 = 1.0;
    float _FC_HZ_2000 = 1.0;
    float _FC_HZ_4000 = 1.0;
    float _FC_HZ_8000 = 1.0;
    float _FC_HZ_16000 = 1.0;
};

#endif // EQFILTERGROUP_H
