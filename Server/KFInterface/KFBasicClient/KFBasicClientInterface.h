﻿#ifndef __KF_BASIC_CLIENT_INTERFACE_H__
#define __KF_BASIC_CLIENT_INTERFACE_H__

#include "KFKernel/KFEntity.h"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class KFBasicClientInterface : public KFModule
    {
    public:
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_INTERFACE__( _kf_basic_client, KFBasicClientInterface );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}



#endif