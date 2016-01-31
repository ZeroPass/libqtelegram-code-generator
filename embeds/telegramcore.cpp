// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#include "telegramcore.h"
#include <QDebug>

qint32 TelegramCore::mTimeOut = 30000;

TelegramCore::TelegramCore(QObject *parent) :
    QObject(parent)
{
}

void TelegramCore::setApi(TelegramApi *api)
{
    mApi = api;

/*! === connects === !*/
    connect(api, &TelegramApi::error, this, &TelegramCore::onError);
}

/*! === methods === !*/

void TelegramCore::onError(qint64 id, qint32 errorCode, const QString &errorText, const QString &functionName, const QVariant &attachedData, bool &accepted)
{
    Q_EMIT error(id, errorCode, errorText, functionName);
    Q_UNUSED(accepted)
    Q_UNUSED(attachedData)
}

qint64 TelegramCore::retry(qint64 mid)
{
    qint64 result = 0;
    if(!mRecallArgs.contains(mid))
        return result;
    const QVariantHash &args = mRecallArgs.take(mid);
    const QString &functionName = args.value("").toString();
    if(functionName.isEmpty())
        return result;
/*! === retries === !*/
    return result;
}

void TelegramCore::timerEvent(QTimerEvent *e)
{
    const qint64 msgId = mTimer.key(e->timerId());
    if(msgId)
    {
        mTimer.remove(msgId);
        killTimer(e->timerId());
        qDebug() << "Timed out. Retrying msgId=" << msgId;
        retry(msgId);
    }

    QObject::timerEvent(e);
}

TelegramCore::~TelegramCore()
{
    QHashIterator<qint64, void*> i(mCallbacks);
    while(i.hasNext())
    {
        i.next();
        Callback<int> *ptr = reinterpret_cast<Callback<int>*>(i.value());
        delete ptr;
    }
    mCallbacks.clear();
}

