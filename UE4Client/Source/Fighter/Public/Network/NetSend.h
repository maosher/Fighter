﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Headers.h"
#include "NetDefine.h"
#include "NetMessage.h"
#include "NetSend.generated.h"

class NetSocket;

UCLASS()
class UNetSend : public UThread
{
    GENERATED_UCLASS_BODY()

public:
    ~UNetSend();

    // init
    void InitData( NetSocket* socket, uint32 queuesize );

    // start
    void StartService();

    // stop
    void StopService();

    // send
    bool SendNetMessage( uint32 msgid, const int8* data, uint32 length );

protected:
    // body
    virtual void ThreadBody();

    // 发送单个消息
    bool SendSingleMessage( uint32 msgid, const int8* data, uint32 length );

    // 发送拆分消息
    bool SendMultiMessage( uint32 msgid, const int8* data, uint32 length );

    // 判断发送buff
    bool CheckBuffLength( uint32 totallength, uint32 messagelength );

    // 发送数据
    void SendNetBuff();

private:
    // socket
    NetSocket* _net_socket = nullptr;

    // 是否开启了发送
    bool _is_send_start = false;

    // 发消息队列
    TCircle< UNetMessage > _send_queue;

    // 发送消息buff
    uint32 _send_length = 0u;
    uint8 _send_buff[ NetDefine::MaxReqBuffLength ];
};