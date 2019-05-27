﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Headers.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "NetEvent.h"
#include "NetDefine.h"
#include "Runtime/Networking/Public/Networking.h"


DECLARE_LOG_CATEGORY_CLASS( LogNetwork, All, All );

class FSocket;
class UNetSend;
class UNetRecv;
class UNetConnect;
class NetMessage;

class NetSocket
{
public:
    NetSocket();
    ~NetSocket();

public:
    // init
    void Init( const FString& name, ENetType nettype, uint32 sendqueuesize, uint32 recvqueuesize, bool disconnectsend );

    // close
    void Close();

    // shutdown
    void Shutdown();

    // tick
    void Tick( float DeltaTime );

public:
    // event
    void PushNetEvent( uint32 type, int32 code = 0, void* data = nullptr );

    // 弹出一个网络事件
    NetEvent* PopNetEvent();

    // connect
    void StartConnect( const FString& ip, uint32 port );

    // send
    bool SendNetMessage( uint32 msgid, const int8* data, uint32 length );

    // 弹出一个消息
    NetMessage* PopNetMessage();

public:
    // socket
    FSocket* _socket = nullptr;

    // 是否连接
    std::atomic<bool> _is_connect;

    // 是否关闭
    std::atomic<bool> _is_close;

    // 消息头长度
    uint32 _message_head_length = 0u;

    // 断线是否需要加入发送队列
    bool _is_disconnect_send = false;

private:
    // 连接线程
    //UPROPERTY( Transient )
    UNetConnect* _net_connect = nullptr;

    // 发送线程
    UPROPERTY( Transient )
    UNetSend* _net_send = nullptr;

    // 接收线程
    UPROPERTY( Transient )
    UNetRecv* _net_recv = nullptr;

    // 网络事件列表
    std::list< NetEvent* > _event_queue;

    /**< 互斥锁 */
    FCriticalSection _event_lock;
};
