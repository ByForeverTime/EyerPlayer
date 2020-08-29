#include "EyerGLRenderTask/YUVRenderTask.hpp"
#include "EyerPlayerThread.hpp"
#include "EventTag.hpp"
#include "EyerOpenSL/EyerOpenSL.hpp"
#include "EyerPlayerEventManager.hpp"
#include "PlayerEvent.hpp"

namespace Eyer {
    AVPlayCtrThread::AVPlayCtrThread(AVFrameQueueManager * _frameQueueManager, EyerEventQueue * _eventQueue, MediaInfo & _mediaInfo, double _videoTime)
    {
        mediaInfo = _mediaInfo;
        frameQueueManager = _frameQueueManager;
        eventQueue = _eventQueue;

        opensl = new EyerOpenSL();
    }

    AVPlayCtrThread::~AVPlayCtrThread()
    {
        if(opensl != nullptr){
            delete opensl;
            opensl = nullptr;
        }
    }

    void AVPlayCtrThread::Run()
    {
        JNIEnv * env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        EyerLog("PlayCtr Thread Start\n");

        AVFrameQueue * videoFrameQueue = nullptr;
        AVFrameQueue * audioFrameQueue = nullptr;

        frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_VIDEO, &videoFrameQueue);
        frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_AUDIO, &audioFrameQueue);

        startTime = Eyer::EyerTime::GetTime();

        Eyer::EyerAVFrame * videoFrame = nullptr;
        Eyer::EyerAVFrame * audioFrame = nullptr;

        Eyer::EyerMediaCodec * mediaCodec = nullptr;

        long long videoFrameTime = 0;

        long long lastProcessTime = Eyer::EyerTime::GetTime();
        while(!stopFlag){

            Eyer::EyerTime::EyerSleepMilliseconds(1);

            EventLoop();

            long long nowTime = Eyer::EyerTime::GetTime();


            double dTime = (nowTime - startTime) / 1000.0;
            dTime += seekTime;

            double progress = dTime / mediaInfo.GetDuration();
            if(progress >= 1.0){
                dTime = mediaInfo.GetDuration();
            }

            long long processNowTime = Eyer::EyerTime::GetTime();
            if(processNowTime - lastProcessTime >= 1000){
                long long requestId = 1;
                EventProgressRequest * progressRequest = new EventProgressRequest();
                progressRequest->SetFrom(EventTag::EVENT_PLAYER_CTR);
                progressRequest->SetTo(EventTag::EVENT_MANAGER);
                progressRequest->SetRequestId(requestId);
                progressRequest->progress = progress;
                eventQueue->Push(progressRequest);
                lastProcessTime = processNowTime;
            }





            if(mediaCodec == nullptr){  
                frameQueueManager->GetMediaCodecQueue(&mediaCodec);
            }

            // EyerLog("DTime: %f\n", dTime);
            if(mediaCodec != nullptr){
                if(outindex < 0){
                    outindex = mediaCodec->dequeueOutputBuffer(1000 * 1);
                    if(outindex >= 0){
                        videoFrameTime = mediaCodec->getOutTime();
                    }
                }

                if(outindex >= 0){
                    double timePts = videoFrameTime / 1000.0;
                    // EyerLog("dTime: %f\n", dTime);
                    // EyerLog("timePts: %f\n", timePts);

                    if(dTime - timePts >= 0.1){
                        mediaCodec->releaseOutputBuffer(outindex, false);
                        outindex = -1;
                    }
                    else if (timePts <= dTime) {
                        mediaCodec->releaseOutputBuffer(outindex, true);
                        outindex = -1;
                    }
                }
            }


            /*
            if(videoFrame == nullptr){
                if(videoFrameQueue != nullptr){
                    videoFrameQueue->FrontPop(&videoFrame);
                }
            }
            if(videoFrame != nullptr){
                // 判断视频是否应该播放
                if(videoFrame->timePts <= dTime){
                    mut.lock();
                    if(glCtx != nullptr){
                        YUVRenderTask * yuvRenderTask = new YUVRenderTask();
                        yuvRenderTask->SetFrame(videoFrame);
                        glCtx->AddRenderTask(yuvRenderTask);
                        videoFrame = nullptr;
                    }
                    mut.unlock();

                    if(videoFrame != nullptr){
                        delete videoFrame;
                        videoFrame = nullptr;
                    }
                }
            }
            */





            if(audioFrame == nullptr){
                if(audioFrameQueue != nullptr){
                    audioFrameQueue->FrontPop(&audioFrame);
                }
            }
            if(audioFrame != nullptr){
                // 判断音频是否应该播放
                if(audioFrame->timePts <= dTime){
                    // Play !!!
                    if(audioFrame != nullptr){
                        // opensl->PutFrame(audioFrame);
                        delete audioFrame;
                        audioFrame = nullptr;
                    }
                }
            }
        }


        Eyer::EyerJNIEnvManager::jvm->DetachCurrentThread();

        EyerLog("PlayCtr Thread End\n");
    }

    int AVPlayCtrThread::SetStatus(AVPlayCtrStatus _status)
    {
        statusMut.lock();
        status = _status;
        statusMut.unlock();
        return 0;
    }

    int AVPlayCtrThread::SetGLCtx(Eyer::EyerGLContextThread * _glCtx)
    {
        mut.lock();
        glCtx = _glCtx;
        mut.unlock();
        return 0;
    }

    int AVPlayCtrThread::Seek(double time)
    {
        startTime = Eyer::EyerTime::GetTime();
        seekTime = time;
        outindex = -1;
        return 0;
    }
}