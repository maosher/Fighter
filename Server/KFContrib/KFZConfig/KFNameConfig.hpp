﻿#ifndef __KF_NAME_CONFIG_H__
#define __KF_NAME_CONFIG_H__

#include "KFrame.h"
#include "KFZConfig/KFConfig.h"

namespace KFrame
{
    class KFNameSetting : public KFIntSetting
    {
    public:
        // 名字列表
        StringVector _name_list;
    };
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    class KFNameConfig : public KFConfigT< KFNameSetting >, public KFInstance< KFNameConfig >
    {
    public:
        KFNameConfig()
        {
            _file_name = "name";
        }

        // 随机名字
        const std::string& RandName() const;

    protected:
        // 读取配置
        void ReadSetting( KFNode& xmlnode, KFNameSetting* kfsetting );
    };
}

#endif