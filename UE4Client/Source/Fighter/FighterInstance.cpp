﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterInstance.h"
#include "Public/Network/NetClient.h"
#include "Public/Protocol/Protocol.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Fighter, "Fighter" );
DECLARE_LOG_CATEGORY_CLASS( LogInstance, All, All );

UFighterInstance* UFighterInstance::_this = nullptr;
UFighterInstance::UFighterInstance( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    _this = this;
}

UFighterInstance::~UFighterInstance()
{
    _this = nullptr;
    __SAFE_DELETE__( _net_client );
}

void UFighterInstance::StartGameInstance()
{
    Super::StartGameInstance();
}

inline bool UFighterInstance::IsTickable() const
{
    return true;
}

inline TStatId UFighterInstance::GetStatId() const
{
    return m_TStatId;
}

void UFighterInstance::Init()
{
    Super::Init();
    __LOG_INFO__( LogInstance, "UFighterInstance::Init..." );

    _net_client = new NetClient();
    _net_client->Init( TEXT( "client" ), ENetType::Client, 200, 200, false );
    _net_client->RegisterMessageFunction( this, &UFighterInstance::HandleNetMessage );
    _net_client->RegisterNetEventFunction( NetDefine::ConnectEvent, this, &UFighterInstance::OnNetClientConnectOk );
    _net_client->RegisterNetEventFunction( NetDefine::FailedEvent, this, &UFighterInstance::OnNetClientConnectFailed );
    _net_client->RegisterNetEventFunction( NetDefine::DisconnectEvent, this, &UFighterInstance::OnNetClientDisconnect );

    FString ip = TEXT( "192.168.1.155" );
    uint32 port = 12006;
    _net_client->Connect( ip, port );
}

void UFighterInstance::Shutdown()
{
    if ( _net_client != nullptr )
    {
        _net_client->Close();
        _net_client = nullptr;
    }

    Super::Shutdown();
}

void UFighterInstance::Tick( float DeltaTime )
{
    if ( _net_client != nullptr )
    {
        _net_client->Tick( DeltaTime );
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void UFighterInstance::OnNetClientConnectOk( const NetEvent* event )
{
    __LOG_INFO__( LogInstance, "network connect ok!" );

    KFMsg::MsgLoginReq req;
    req.set_accountid( 111111 );
    req.set_token( "sss" );
    req.set_version( "0.0.0.0" );
    _net_client->SendNetMessage( KFMsg::MSG_LOGIN_REQ, &req );
}

void UFighterInstance::OnNetClientConnectFailed( const NetEvent* event )
{
    __LOG_INFO__( LogInstance, "network connect failed!" );

    FString ip = TEXT( "192.168.1.155" );
    uint32 port = 12006;
    //_net_client->Connect( ip, port );
}

void UFighterInstance::OnNetClientDisconnect( const NetEvent* event )
{
    __LOG_ERROR__( LogInstance, "network disconnect!" );
}

void UFighterInstance::HandleNetMessage( uint32 msgid, const int8* data, uint32 length )
{
    if ( msgid == KFMsg::MSG_RESULT_DISPLAY )
    {
        __PROTO_PARSE__( KFMsg::MsgResultDisplay );
        __LOG_INFO__( LogInstance, "result=[{}]", msg.result() );
    }
    else
    {
        __LOG_INFO__( LogInstance, "msgid=[{}], length=[{}]", msgid, length );
    }

}
/////////////////////////////////////////////////////////////////////////////////////
