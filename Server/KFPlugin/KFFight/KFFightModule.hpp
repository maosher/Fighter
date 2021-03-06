﻿#ifndef __KF_FIGHT_MODULE_H__
#define __KF_FIGHT_MODULE_H__

/************************************************************************
//    @Module			:    战斗模块
//    @Author           :    __凌_痕__
//    @QQ				:    7969936
//    @Mail			    :    lori227@qq.com
//    @Date             :    2020-8-12
************************************************************************/

#include "KFrameEx.h"
#include "KFFightInterface.h"
#include "KFGame/KFGameInterface.h"
#include "KFPlayer/KFPlayerInterface.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFReset/KFResetInterface.h"

namespace KFrame
{
    class KFFightModule : public KFFightInterface
    {
    public:
        KFFightModule() = default;
        ~KFFightModule() = default;

        virtual void BeforeRun();

        virtual void ShutDown();

    protected:
        // 重置战斗积分
        __KF_RESET_FUNCTION__( OnResetFightScore );

        // 处理积分更新
        __KF_MESSAGE_FUNCTION__( HandleUpdateScoreReq );
    };
}



#endif