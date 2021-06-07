#ifndef AUDIOBUFFERDEVICE_H
#define AUDIOBUFFERDEVICE_H

#include <QObject>
#include <QIODevice>
#include <QAudioDecoder>
#include <QQueue>
#include <QAudioBuffer>
#include <QBuffer>
#include "EQFilterGroup.h"

class AudioBufferDevice : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioBufferDevice(QAudioDecoder *decoder, QObject *parent = nullptr);
    virtual bool atEnd() const override;
    virtual qint64 bytesAvailable() const override;

protected:
    virtual qint64 readData(char *data, qint64 size) override;

    virtual qint64 writeData(const char *data, qint64 maxSize);
signals:

public slots:
    void onBufferReady();
    void onFinished();
    void clearQAbuffer();
    void onErroe(QAudioDecoder::Error error);

    void set_FC_HZ_32(float gain, float adaptation) {_filter->set_FC_HZ_32(gain, adaptation);}
    void set_FC_HZ_63(float gain, float adaptation) {_filter->set_FC_HZ_63(gain, adaptation);}
    void set_FC_HZ_125(float gain, float adaptation) {_filter->set_FC_HZ_125(gain, adaptation);}
    void set_FC_HZ_250(float gain, float adaptation) {_filter->set_FC_HZ_250(gain, adaptation);}
    void set_FC_HZ_500(float gain, float adaptation) {_filter->set_FC_HZ_500(gain, adaptation);}
    void set_FC_HZ_1000(float gain) {_filter->set_FC_HZ_1000(gain);}
    void set_FC_HZ_2000(float gain) {_filter->set_FC_HZ_2000(gain);}
    void set_FC_HZ_4000(float gain) {_filter->set_FC_HZ_4000(gain);}
    void set_FC_HZ_8000(float gain) {_filter->set_FC_HZ_8000(gain);}
    void set_FC_HZ_16000(float gain) {_filter->set_FC_HZ_16000(gain);}


private:
    QAudioDecoder *_decoder;
    QQueue<QBuffer *> _queue;
    QQueue<QAudioBuffer *> _abuffer_queue;
    EQFilterGroup *_filter;
    bool _isFinished;
};

#endif // AUDIOBUFFERDEVICE_H
