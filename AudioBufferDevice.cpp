#include "AudioBufferDevice.h"
#include <QByteArray>

AudioBufferDevice::AudioBufferDevice(QAudioDecoder *decoder, QObject *parent):
    QIODevice(parent),
    _decoder(decoder),
    _isFinished(false)
{
    connect(_decoder, SIGNAL(bufferReady()), this, SLOT(onBufferReady()));
    connect(_decoder, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(_decoder, SIGNAL(error(QAudioDecoder::Error)), this, SLOT(onErroe(QAudioDecoder::Error)));
    _filter = new EQFilterGroup();
    _decoder->start();
}

bool AudioBufferDevice::atEnd() const
{
    return _isFinished && _queue.empty();
}

qint64 AudioBufferDevice::readData(char *data, qint64 size)
{
    if (_queue.empty() && _abuffer_queue.empty()) {
        return 0;
    }

    if (_queue.empty()) {
        QAudioBuffer *buffer = _abuffer_queue.first();
        QBuffer *qb = _filter->filter(*buffer);
        _queue.push_back(qb);
        _abuffer_queue.removeFirst();
        delete buffer;
    }

    QBuffer *buffer = _queue.first();
    if (!buffer->isOpen()) {
        buffer->open(QIODevice::ReadOnly);
    }

    qint64 n = buffer->read(data, size);
    qDebug() << "-----------------------------------------------------------------------------data" << strlen(data);
    if (buffer->atEnd()) {
        _queue.removeFirst();
        delete buffer;
    }


    return n;
}

qint64 AudioBufferDevice::writeData(const char *data, qint64 maxSize)
{
    return 0;
}

qint64 AudioBufferDevice::bytesAvailable() const
{
    if (_queue.empty()) {
        return 0;
    } else {
        return _queue.first()->bytesAvailable();
    }
}

void AudioBufferDevice::onBufferReady()
{
    QAudioBuffer buffer = _decoder->read();
    if (buffer.isValid()) {
        _abuffer_queue.push_back(new QAudioBuffer(buffer));
    }
}

void AudioBufferDevice::onFinished()
{
    _isFinished = true;
}

void AudioBufferDevice::clearQAbuffer()
{
    _queue.clear();
    _abuffer_queue.clear();
}

void AudioBufferDevice::onErroe(QAudioDecoder::Error error)
{
    qDebug() << error;
}
