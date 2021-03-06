#include "PlayerQueueManager.hpp"

namespace Eyer {
    AVFrameQueueManager::AVFrameQueueManager()
    {

    }

    AVFrameQueueManager::~AVFrameQueueManager()
    {

    }

    int AVFrameQueueManager::GetQueue(Eyer::EyerString key, AVFrameQueue * * queue)
    {
        return queueManager.GetQueue(key, queue);
    }

    int AVFrameQueueManager::ClearAndDelete()
    {
        return queueManager.ClearAndDelete();
    }


    int AVFrameQueueManager::GetMediaCodecQueueInit(Eyer::EyerAVStream & stream, jobject surface)
    {
        std::lock_guard<std::mutex> lg(mediaCodecQueueMut);
        if(mediaCodecQueue == nullptr){
            mediaCodecQueue = new Eyer::EyerMediaCodec();
        }

        mediaCodecQueue->Init(stream, surface);

        return 0;
    }

    int AVFrameQueueManager::GetMediaCodecQueueUninit()
    {
        std::lock_guard<std::mutex> lg(mediaCodecQueueMut);
        if(mediaCodecQueue != nullptr){
            mediaCodecQueue->Uninit();
            delete mediaCodecQueue;
            mediaCodecQueue = nullptr;
        }
        return 0;
    }

    int AVFrameQueueManager::GetMediaCodecQueue(Eyer::EyerMediaCodec * * _mediaCodecQueue)
    {
        std::lock_guard<std::mutex> lg(mediaCodecQueueMut);
        if(mediaCodecQueue == nullptr){
            return -1;
        }

        *_mediaCodecQueue = mediaCodecQueue;

        return 0;
    }
}