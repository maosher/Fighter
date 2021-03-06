﻿#ifndef __KF_ITEM_CONFIG_H__
#define __KF_ITEM_CONFIG_H__

#include "KFItemSetting.hpp"
#include "KFZConfig/KFConfig.h"

namespace KFrame
{
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFItemConfig : public KFConfigT< KFItemSetting >, public KFInstance< KFItemConfig >
    {
    public:
        KFItemConfig()
        {
            _file_name = "item";
        }
    protected:
        // 读取配置
        virtual void ReadSetting( KFNode& xmlnode, KFItemSetting* kfsetting );

        // 读取通用道具
        void ReadCommonSetting( KFNode& xmlnode, KFItemSetting* kfsetting );

        // 读取礼包配置
        void ReadGiftSetting( KFNode& xmlnode, KFItemSetting* kfsetting );

        // 读取药品配置
        void ReadDrugSetting( KFNode& xmlnode, KFItemSetting* kfsetting );

        // 读取装备配置
        void ReadEquipSetting( KFNode& xmlnode, KFItemSetting* kfsetting );

        // 读取材料配置
        void ReadMaterialSetting( KFNode& xmlnode, KFItemSetting* kfsetting );

        // 读取其他配置
        void ReadOtherSetting( KFNode& xmlnode, KFItemSetting* kfsetting );
    };
}

#endif