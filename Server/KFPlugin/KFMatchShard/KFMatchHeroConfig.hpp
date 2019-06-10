﻿#ifndef __KF_MATCH_HERO_CONFIG_H__
#define __KF_MATCH_HERO_CONFIG_H__

#include "KFConfig/KFConfigInterface.h"

namespace KFrame
{
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFMatchHeroConfig : public KFConfig, public KFSingleton< KFMatchHeroConfig >
    {
    public:
        KFMatchHeroConfig()
        {
            _file = "hero.config";
        }

        // 读取配置
        bool LoadConfig( const std::string& file );

        // 随机英雄
        uint32 RandHero() const;

    private:
        // 英雄列表
        std::vector< uint32 > _hero_list;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static auto _kf_match_hero_config = KFMatchHeroConfig::Instance();
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif