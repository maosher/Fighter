﻿#include "KFMatchClientPlugin.hpp"
#include "KFMatchClientModule.hpp"

//////////////////////////////////////////////////////////////////////////

namespace KFrame
{
    void KFMatchClientPlugin::Install()
    {
        __REGISTER_MODULE__( KFMatchClient );
    }

    void KFMatchClientPlugin::UnInstall()
    {
        __UNREGISTER_MODULE__( KFMatchClient );
    }

    void KFMatchClientPlugin::LoadModule()
    {
        __FIND_MODULE__( _kf_option, KFOptionInterface );
        __FIND_MODULE__( _kf_config, KFConfigInterface );
        __FIND_MODULE__( _kf_kernel, KFKernelInterface );
        __FIND_MODULE__( _kf_player, KFPlayerInterface );
        __FIND_MODULE__( _kf_message, KFMessageInterface );
        __FIND_MODULE__( _kf_display, KFDisplayInterface );
        __FIND_MODULE__( _kf_route, KFRouteClientInterface );
    }
}