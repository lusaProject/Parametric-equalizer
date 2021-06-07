#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QAudioFormat>
#include <QAudioBuffer>
#include <QMediaContent>
#include <QAudioDecoder>
#include <QAudioOutput>
#include "AudioBufferDevice.h"
#include <QMediaResource>

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = nullptr);

    void setSourceFilename(const QString &fileName);

    void play();
    void suspend();
    void reset();

public:
    void set_FC_HZ_32(float gain, float adaptation) {_buffer->set_FC_HZ_32(gain, adaptation);}
    void set_FC_HZ_63(float gain, float adaptation) {_buffer->set_FC_HZ_63(gain, adaptation);}
    void set_FC_HZ_125(float gain, float adaptation) {_buffer->set_FC_HZ_125(gain, adaptation);}
    void set_FC_HZ_250(float gain, float adaptation) {_buffer->set_FC_HZ_250(gain, adaptation);}
    void set_FC_HZ_500(float gain, float adaptation) {_buffer->set_FC_HZ_500(gain, adaptation);}
    void set_FC_HZ_1000(float gain) {_buffer->set_FC_HZ_1000(gain);}
    void set_FC_HZ_2000(float gain) {_buffer->set_FC_HZ_2000(gain);}
    void set_FC_HZ_4000(float gain) {_buffer->set_FC_HZ_4000(gain);}
    void set_FC_HZ_8000(float gain) {_buffer->set_FC_HZ_8000(gain);}
    void set_FC_HZ_16000(float gain) {_buffer->set_FC_HZ_16000(gain);}

signals:

public slots:

public:
    QAudioOutput *_output       = nullptr;
    AudioBufferDevice *_buffer  = nullptr;
    QAudioDecoder *decoder      = nullptr;
};

#endif // AUDIOPLAYER_H
