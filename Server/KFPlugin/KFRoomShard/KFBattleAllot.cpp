﻿#include "KFBattleAllot.h"

namespace KFrame
{
    ////////////////////////////////////////////////////////////////////////////////////
    void KFBattleAllot::Initialize( KFRedisDriver* redisdriver )
    {
        _room_redis = redisdriver;
    }

    bool KFBattleAllot::AddBattle( uint64 serverid, const std::string& ip, uint32 port, const std::string& version )
    {
        // 为了避免单点问题, 保存到redis缓存中
        StringMap values;
        values[ __STRING__( ip ) ] = ip;
        values[ __STRING__( version ) ] = version;
        values[ __STRING__( port ) ] = __TO_STRING__( port );

        _room_redis->WriteMulti();
        _room_redis->SAdd( __DATABASE_KEY_2__( __STRING__( battlelist ), version ), serverid );
        _room_redis->HMSet( __DATABASE_KEY_2__( __STRING__( battle ), serverid ), values );
        _room_redis->Expire( __DATABASE_KEY_2__( __STRING__( battle ), serverid ), 300 );
        auto kfresult = _room_redis->WriteExec();
        return kfresult->IsOk();
    }

    void KFBattleAllot::RemoveBattle( uint64 serverid, const std::string& version )
    {
        _room_redis->WriteMulti();
        _room_redis->Del( __DATABASE_KEY_2__( __STRING__( battle ), serverid ) );
        _room_redis->SRem( __DATABASE_KEY_2__( __STRING__( battlelist ), version ), serverid );
        _room_redis->WriteExec();
    }

    std::tuple< uint64, std::string, uint32, bool > KFBattleAllot::AllotBattle( uint64 serverid, const std::string& version )
    {
        if ( serverid != _invalid_int )
        {
            return AllotSpecificBattle( serverid );
        }

        return AllotVersionBattle( version );
    }

    std::tuple< uint64, std::string, uint32, bool > KFBattleAllot::AllotSpecificBattle( uint64 serverid )
    {
        std::string ip = "";
        uint32 port = _invalid_int;
        uint64 allotid = _invalid_int;
        bool isempty = false;

        auto mapresult = _room_redis->HGetAll( __DATABASE_KEY_2__( __STRING__( battle ), serverid ) );
        if ( mapresult->IsOk() )
        {
            if ( !mapresult->_value.empty() )
            {
                allotid = serverid;
                ip = mapresult->_value[ __STRING__( ip ) ];
                port = KFUtility::ToValue< uint32 >( mapresult->_value[ __STRING__( port ) ] );
                if ( ip.empty() || port == _invalid_int )
                {
                    isempty = true;
                    __LOG_ERROR__( "battle[{}] data error!", KFAppId::ToString( serverid ) );
                }

                // 删除列表
                auto version = mapresult->_value[ __STRING__( version ) ];
                _room_redis->SRem( __DATABASE_KEY_2__( __STRING__( battlelist ), version ), allotid );
            }
            else
            {
                isempty = true;
                __LOG_ERROR__( "battle[{}] no data!", KFAppId::ToString( serverid ) );
            }
        }

        return std::make_tuple( allotid, ip, port, isempty );
    }

    std::tuple< uint64, std::string, uint32, bool > KFBattleAllot::AllotVersionBattle( const std::string& version )
    {
        std::string ip = "";
        uint32 port = _invalid_int;
        uint64 allotid = _invalid_int;
        bool isempty = false;

        do
        {
            // 弹出一个可用的服务器
            auto kfquery = _room_redis->SPopUInt64( __DATABASE_KEY_2__( __STRING__( battlelist ), version ) );
            if ( kfquery->_value != _invalid_int )
            {
                std::tie( allotid, ip, port, isempty ) = AllotSpecificBattle( kfquery->_value );
            }
            else
            {
                if ( kfquery->IsOk() )
                {
                    __LOG_ERROR__( "version[{}] battle list empty!", version );
                }
                break;
            }
        } while ( isempty );

        return std::make_tuple( allotid, ip, port, isempty );
    }

    void KFBattleAllot::UpdateBattle( uint64 serverid )
    {
        // 保存10分钟
        _room_redis->Expire( __DATABASE_KEY_2__( __STRING__( battle ), serverid ), 300 );
    }
}