﻿#ifndef __KF_COMPONENT_H__
#define __KF_COMPONENT_H__

#include "KFEntity.h"
#include "KFElementResult.h"

namespace KFrame
{
    ////////////////////////////////////////////////////////////////////////////////////////////
    typedef std::function< void( KFEntity* ) > KFEntityFunction;
    typedef std::function< void( KFEntity*, uint32 ) > KFSaveEntityFunction;
    typedef std::function< void( KFEntity*, KFMsg::PBObject& ) > KFSyncFunction;
    typedef std::function< void( KFEntity*, KFMsg::PBShowElements& ) > KFShowElementFunction;
    ////////////////////////////////////////////////////////////////////////////////////////////
    typedef std::function< bool( KFEntity*, KFData*, KFElement*, double, const char*, uint32 ) > KFCheckAddElementFunction;
    typedef std::function< bool( KFEntity*, KFData*, KFElementResult*, const char*, uint32 ) > KFAddElementFunction;
    typedef std::function< bool( KFEntity*, KFData*, KFElement*, double, const char*, uint32 ) > KFCheckRemoveElementFunction;
    typedef std::function< bool( KFEntity*, KFData*, KFElementResult*, const char*, uint32 ) > KFRemoveElementFunction;
    ////////////////////////////////////////////////////////////////////////////////////////////
    typedef std::function<void( KFEntity*, KFData*, uint64, KFData* )> KFAddDataFunction;
    typedef std::function<void( KFEntity*, KFData*, uint64, KFData* )> KFRemoveDataFunction;
    typedef std::function<void( KFEntity*, uint64, KFData*, uint32, uint64, uint64, uint64 )> KFUpdateDataFunction;
    typedef std::function<void( KFEntity*, KFData*, const std::string&, const std::string& )> KFUpdateStringFunction;
    ////////////////////////////////////////////////////////////////////////////////////////////
    typedef std::function<uint64( KFEntity*, uint64, uint64 )> KFGetConfigValueFunction;
    ////////////////////////////////////////////////////////////////////////////////////////////
    typedef std::function< void( KFEntity*, const KFElementResult* ) > KFLogElementFunction;
    typedef std::function< bool( KFEntity*, const KFElementResult* ) > KFElementResultFunction;

    // 游戏中的组件, 负责属性回调事件
    class KFComponent : public KFModule
    {
    public:
        KFComponent() = default;
        virtual ~KFComponent() = default;
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 创建实体
        virtual KFEntity* CreateEntity( uint64 key ) = 0;
        virtual KFEntity* CreateEntity( uint64 key, const KFMsg::PBObject* data ) = 0;

        // 添加实体
        virtual void AddEntity( uint64 key, KFEntity* kfentity ) = 0;

        // 查找实体
        virtual KFEntity* FindEntity( uint64 key ) = 0;
        virtual KFEntity* FindEntity( uint64 key, const char* function, uint32 line ) = 0;

        // 删除实体, 保存数据库
        virtual bool RemoveEntity( uint64 key ) = 0;
        virtual bool RemoveEntity( KFEntity* kfentity ) = 0;

        // 实体数量
        virtual uint32 GetEntityCount() = 0;

        // 遍历列表
        virtual KFEntity* FirstEntity() = 0;
        virtual KFEntity* NextEntity() = 0;

        // 获得属性列表
        virtual StringVector& GetDataList( const std::string& dataname ) = 0;

        // 获得类配置
        virtual const KFClassSetting* FindClassSetting() = 0;
        virtual const KFClassSetting* FindClassSetting( const std::string& dataname ) = 0;

        // 获得属性配置
        virtual const KFDataSetting* FindDataSetting() = 0;
        virtual const KFDataSetting* FindDataSetting( const std::string& dataname ) = 0;
        virtual const KFDataSetting* FindDataSetting( const std::string& parentname, const std::string& dataname ) = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void SetMaxValue( const std::string& dataname, uint32 value ) = 0;
        virtual void SetMaxValue( const std::string& parentname, const std::string& dataname, uint32 value ) = 0;
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 注册判断属性函数
        template< class T >
        void RegisterCheckAddElementFunction( const std::string& dataname, T* module, bool ( T::*handle )( KFEntity*, KFData*, KFElement*, double, const char*, uint32 ) )
        {
            KFCheckAddElementFunction function = std::bind( handle, module,
                                                 std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                                                 std::placeholders::_4, std::placeholders::_5, std::placeholders::_6 );
            BindCheckAddElementFunction( dataname, function );
        }
        virtual void UnRegisterCheckAddElementFunction( const std::string& dataname ) = 0;

        // 注册添加属性函数
        template< class T >
        void RegisterAddElementFunction( const std::string& dataname, T* module, bool ( T::*handle )( KFEntity*, KFData*, KFElementResult*, const char*, uint32 ) )
        {
            KFAddElementFunction function = std::bind( handle, module,
                                            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                                            std::placeholders::_4, std::placeholders::_5 );
            BindAddElementFunction( dataname, function );
        }
        virtual void UnRegisterAddElementFunction( const std::string& dataname ) = 0;

        // 注册判断属性函数
        template< class T >
        void RegisterCheckRemoveElementFunction( const std::string& dataname, T* module, bool ( T::*handle )( KFEntity*, KFData*, KFElement*, double, const char*, uint32 ) )
        {
            KFCheckRemoveElementFunction function = std::bind( handle, module,
                                                    std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                                                    std::placeholders::_4, std::placeholders::_5, std::placeholders::_6 );
            BindCheckRemoveElementFunction( dataname, function );
        }
        virtual void UnRegisterCheckRemoveElementFunction( const std::string& dataname ) = 0;

        // 注册删除属性函数
        template< class T >
        void RegisterRemoveElementFunction( const std::string& dataname, T* module, bool ( T::*handle )( KFEntity*, KFData*, KFElementResult*, const char*, uint32 ) )
        {
            KFRemoveElementFunction function = std::bind( handle, module,
                                               std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                                               std::placeholders::_4, std::placeholders::_5 );
            BindRemoveElementFunction( dataname, function );
        }
        virtual void UnRegisterRemoveElementFunction( const std::string& dataname ) = 0;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 注册添加属性逻辑
        template< class T >
        void RegisterAddDataLogic( const std::string& dataname, T* module, void ( T::*handle )( KFEntity*, KFData*, uint64, KFData* ) )
        {
            KFAddDataFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 );
            BindAddDataLogic( module, dataname, function );
        }

        template< class T >
        void UnRegisterAddDataLogic( const std::string& dataname, T* module )
        {
            UnBindAddDataLogic( module, dataname );
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 注册添加属性回调函数
        template< class T >
        void RegisterAddDataModule( T* module, void ( T::*handle )( KFEntity*, KFData*, uint64, KFData* ) )
        {
            KFAddDataFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 );
            BindAddDataModule( module, function );
        }

        template< class T >
        void UnRegisterAddDataModule( T* module )
        {
            UnBindAddDataModule( module );
        }

        template< class T >
        void RegisterAddDataFunction( const std::string& dataname, uint64 key, T* module, void ( T::*handle )( KFEntity*, KFData*, uint64, KFData* ) )
        {
            KFAddDataFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 );
            BindAddDataFunction( module, dataname, key, function );
        }

        template< class T >
        void UnRegisterAddDataFunction( T* module, const std::string& dataname, uint64 key )
        {
            UnBindAddDataFunction( module, dataname, key );
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 注册删除属性逻辑
        template< class T >
        void RegisterRemoveDataLogic( const std::string& dataname, T* module, void ( T::*handle )( KFEntity*, KFData*, uint64, KFData* ) )
        {
            KFRemoveDataFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 );
            BindRemoveDataLogic( module, dataname, function );
        }

        template< class T >
        void UnRegisterRemoveDataLogic( const std::string& dataname, T* module )
        {
            UnBindRemoveDataLogic( module, dataname );
        }

        // 注册删除属性回调函数
        template< class T >
        void RegisterRemoveDataModule( T* module, void ( T::*handle )( KFEntity*, KFData*, uint64, KFData* ) )
        {
            KFRemoveDataFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 );
            BindRemoveDataModule( module, function );
        }

        template< class T >
        void UnRegisterRemoveDataModule( T* module )
        {
            UnBindRemoveDataModule( module );
        }

        template< class T >
        void RegisterRemoveDataFunction( const std::string& dataname, uint64 key, T* module, void ( T::*handle )( KFEntity*, KFData*, uint64, KFData* ) )
        {
            KFRemoveDataFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 );
            BindRemoveDataFunction( module, dataname, key, function );
        }

        template< class T >
        void UnRegisterRemoveDataFunction( T* module, const std::string& dataname, uint64 key )
        {
            UnBindRemoveDataFunction( module, dataname, key );
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 注册更新属性回调函数
        template< class T >
        void RegisterUpdateDataModule( T* module, void ( T::*handle )( KFEntity*, uint64, KFData*, uint32, uint64, uint64, uint64 ) )
        {
            KFUpdateDataFunction function = std::bind( handle, module,
                                            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4,
                                            std::placeholders::_5, std::placeholders::_6, std::placeholders::_7 );
            BindUpdateDataModule( module, function );
        }

        template< class T >
        void UnRegisterUpdateDataModule( T* module )
        {
            UnBindUpdateDataModule( module );
        }

        template< class T >
        void RegisterUpdateDataFunction( const std::string& dataname, T* module, void ( T::*handle )( KFEntity*, uint64, KFData*, uint32, uint64, uint64, uint64 ) )
        {
            KFUpdateDataFunction function = std::bind( handle, module,
                                            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4,
                                            std::placeholders::_5, std::placeholders::_6, std::placeholders::_7 );
            BindUpdateDataFunction( module, _invalid_string, dataname, function );
        }

        template< class T >
        void RegisterUpdateDataFunction( const std::string& parentname, const std::string& dataname, T* module, void ( T::*handle )( KFEntity*, uint64, KFData*, uint32, uint64, uint64, uint64 ) )
        {
            KFUpdateDataFunction function = std::bind( handle, module,
                                            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4,
                                            std::placeholders::_5, std::placeholders::_6, std::placeholders::_7 );
            BindUpdateDataFunction( module, parentname, dataname, function );
        }

        template< class T >
        void UnRegisterUpdateDataFunction( T* module, const std::string& dataname )
        {
            UnBindUpdateDataFunction( module, _invalid_string, dataname );
        }

        template< class T >
        void UnRegisterUpdateDataFunction( T* module, const std::string& parentname, const std::string& dataname )
        {
            UnBindUpdateDataFunction( module, parentname, dataname );
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 注册更新属性回调函数
        template< class T >
        void RegisterUpdateStringModule( T* module, void ( T::*handle )( KFEntity*, KFData*, const std::string&, const std::string& ) )
        {
            KFUpdateStringFunction function = std::bind( handle, module,
                                              std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 );
            BindUpdateStringModule( module, function );
        }

        template< class T >
        void UnRegisterUpdateStringModule( T* module )
        {
            UnBindUpdateStringModule( module );
        }

        template< class T >
        void RegisterUpdateStringFunction( const std::string& dataname, T* module, void ( T::*handle )( KFEntity*, KFData*, const std::string&, const std::string& ) )
        {
            KFUpdateStringFunction function = std::bind( handle, module,
                                              std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 );
            BindUpdateStringFunction( module, _invalid_string, dataname, function );
        }

        template< class T >
        void RegisterUpdateStringFunction( const std::string& parentname, const std::string& dataname, T* module, void ( T::*handle )( KFEntity*, KFData*, const std::string&, const std::string& ) )
        {
            KFUpdateStringFunction function = std::bind( handle, module,
                                              std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 );
            BindUpdateStringFunction( module, parentname, dataname, function );
        }

        template< class T >
        void UnRegisterUpdateStringFunction( T* module, const std::string& dataname )
        {
            UnBindUpdateStringFunction( module, _invalid_string, dataname );
        }

        template< class T >
        void UnRegisterUpdateStringFunction( T* module, const std::string& parentname, const std::string& dataname )
        {
            UnBindUpdateStringFunction( module, parentname, dataname );
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< class T >
        void RegisterEntityInitializeFunction( T* module, void ( T::*handle )( KFEntity* ) )
        {
            KFEntityFunction function = std::bind( handle, module, std::placeholders::_1 );
            BindEntityInitializeFunction( module, function );
        }
        virtual void UnRegisterEntityInitializeFunction() = 0;

        template< class T >
        void RegisterEntityUninitializeFunction( T* module, void ( T::*handle )( KFEntity* ) )
        {
            KFEntityFunction function = std::bind( handle, module, std::placeholders::_1 );
            BindEntityUninitializeFunction( module, function );
        }
        virtual void UnRegisterEntityUninitializeFunction() = 0;

        template< class T >
        void RegisterEntityRunFunction( T* module, void ( T::*handle )( KFEntity* ) )
        {
            KFEntityFunction function = std::bind( handle, module, std::placeholders::_1 );
            BindEntityRunFunction( module, function );
        }
        virtual void UnRegisterEntityRunFunction() = 0;

        template< class T >
        void RegisterEntityAfterRunFunction( T* module, void ( T::*handle )( KFEntity* ) )
        {
            KFEntityFunction function = std::bind( handle, module, std::placeholders::_1 );
            BindEntityAfterRunFunction( module, function );
        }
        virtual void UnRegisterEntityAfterRunFunction() = 0;

        template< class T >
        void RegisterEntitySaveFunction( T* module, void ( T::*handle )( KFEntity*, uint32 ) )
        {
            KFSaveEntityFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2 );
            BindEntitySaveFunction( module, function );
        }
        virtual void UnRegisterEntitySaveFunction() = 0;

        template< class T >
        void RegisterEntityDeleteFunction( T* module, void ( T::*handle )( KFEntity* ) )
        {
            KFEntityFunction function = std::bind( handle, module, std::placeholders::_1 );
            BindEntityDeleteFunction( module, function );
        }
        virtual void UnRegisterEntityDeleteFunction() = 0;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< class T >
        void RegisterSyncUpdateFunction( T* module, void ( T::*handle )( KFEntity*, KFMsg::PBObject& ) )
        {
            KFSyncFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2 );
            BindSyncUpdateFunction( module, function );
        }
        virtual void UnRegisterSyncUpdateFunction() = 0;

        template< class T >
        void RegisterSyncAddFunction( T* module, void ( T::*handle )( KFEntity*, KFMsg::PBObject& ) )
        {
            KFSyncFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2 );
            BindSyncAddFunction( module, function );
        }
        virtual void UnRegisterSyncAddFunction() = 0;

        template< class T >
        void RegisterSyncRemoveFunction( T* module, void ( T::*handle )( KFEntity*, KFMsg::PBObject& ) )
        {
            KFSyncFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2 );
            BindSyncRemoveFunction( module, function );
        }
        virtual void UnRegisterSyncRemoveFunction() = 0;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< class T >
        void RegisterShowElementFunction( T* module, void ( T::*handle )( KFEntity*, KFMsg::PBShowElements& ) )
        {
            KFShowElementFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2 );
            BindShowElementFunction( module, function );
        }
        virtual void UnRegisterShowElementFunction() = 0;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< class T >
        void RegisterGetConfigValueFunction( const std::string& name, T* module, uint64 ( T::*handle )( KFEntity*, uint64, uint64 ) )
        {
            KFGetConfigValueFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 );
            BindGetConfigValueFunction( module, name, function );
        }

        void UnRegisterGetConfigValueFunction( const std::string& name )
        {
            UnBindGetConfigValueFunction( name );
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< class T >
        void RegisterLogElementFunction( const std::string& name, T* module, void( T::*handle )( KFEntity*, const KFElementResult* ) )
        {
            KFLogElementFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2 );
            BindLogElementFunction( module, name, function );
        }

        void UnRegisterLogElementFunction( const std::string& name )
        {
            UnBindLogElementFunction( name );
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< class T >
        void RegisterElementResultFunction( const std::string& name, T* module, bool( T::*handle )( KFEntity*, const KFElementResult* ) )
        {
            KFElementResultFunction function = std::bind( handle, module, std::placeholders::_1, std::placeholders::_2 );
            BindElementResultFunction( module, name, function );
        }

        void UnRegisterElementResultFunction( const std::string& name )
        {
            UnBindElementResultFunction( name );
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:
        virtual void BindCheckAddElementFunction( const std::string& dataname, KFCheckAddElementFunction& function ) = 0;
        virtual void BindAddElementFunction( const std::string& dataname, KFAddElementFunction& function ) = 0;
        virtual void BindCheckRemoveElementFunction( const std::string& dataname, KFCheckRemoveElementFunction& function ) = 0;
        virtual void BindRemoveElementFunction( const std::string& dataname, KFRemoveElementFunction& function ) = 0;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void BindAddDataLogic( KFModule* module, const std::string& dataname, KFAddDataFunction& function ) = 0;
        virtual void UnBindAddDataLogic( KFModule* module, const std::string& dataname ) = 0;

        virtual void BindAddDataModule( KFModule* module, KFAddDataFunction& function ) = 0;
        virtual void UnBindAddDataModule( KFModule* module ) = 0;
        virtual void BindAddDataFunction( KFModule* module, const std::string& dataname, uint64 key, KFAddDataFunction& function ) = 0;
        virtual void UnBindAddDataFunction( KFModule* module, const std::string& dataname, uint64 key ) = 0;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        virtual void BindRemoveDataLogic( KFModule* module, const std::string& dataname, KFRemoveDataFunction& function ) = 0;
        virtual void UnBindRemoveDataLogic( KFModule* module, const std::string& dataname ) = 0;

        virtual void BindRemoveDataModule( KFModule* module, KFRemoveDataFunction& function ) = 0;
        virtual void UnBindRemoveDataModule( KFModule* module ) = 0;
        virtual void BindRemoveDataFunction( KFModule* module, const std::string& dataname, uint64 key, KFRemoveDataFunction& function ) = 0;
        virtual void UnBindRemoveDataFunction( KFModule* module, const std::string& dataname, uint64 key ) = 0;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        virtual void BindUpdateDataModule( KFModule* module, KFUpdateDataFunction& function ) = 0;
        virtual void UnBindUpdateDataModule( KFModule* module ) = 0;
        virtual void BindUpdateDataFunction( KFModule* module, const std::string& parentname, const std::string& dataname, KFUpdateDataFunction& function ) = 0;
        virtual void UnBindUpdateDataFunction( KFModule* module, const std::string& parentname, const std::string& dataname ) = 0;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        virtual void BindUpdateStringModule( KFModule* module, KFUpdateStringFunction& function ) = 0;
        virtual void UnBindUpdateStringModule( KFModule* module ) = 0;
        virtual void BindUpdateStringFunction( KFModule* module, const std::string& parentname, const std::string& dataname, KFUpdateStringFunction& function ) = 0;
        virtual void UnBindUpdateStringFunction( KFModule* module, const std::string& parentname, const std::string& dataname ) = 0;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        virtual void BindEntityInitializeFunction( KFModule* module, KFEntityFunction& function ) = 0;
        virtual void BindEntityUninitializeFunction( KFModule* module, KFEntityFunction& function ) = 0;
        virtual void BindEntityAfterRunFunction( KFModule* module, KFEntityFunction& function ) = 0;
        virtual void BindEntityRunFunction( KFModule* module, KFEntityFunction& function ) = 0;
        virtual void BindEntityDeleteFunction( KFModule* module, KFEntityFunction& function ) = 0;
        virtual void BindSyncUpdateFunction( KFModule* module, KFSyncFunction& function ) = 0;
        virtual void BindSyncAddFunction( KFModule* module, KFSyncFunction& function ) = 0;
        virtual void BindSyncRemoveFunction( KFModule* module, KFSyncFunction& function ) = 0;
        virtual void BindShowElementFunction( KFModule* module, KFShowElementFunction& function ) = 0;
        virtual void BindEntitySaveFunction( KFModule* module, KFSaveEntityFunction& function ) = 0;
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void BindGetConfigValueFunction( KFModule* module, const std::string& dataname, KFGetConfigValueFunction& function ) = 0;
        virtual void UnBindGetConfigValueFunction( const std::string& dataname ) = 0;

        virtual void BindLogElementFunction( KFModule* module, const std::string& dataname, KFLogElementFunction& function ) = 0;
        virtual void UnBindLogElementFunction( const std::string& dataname ) = 0;

        virtual void BindElementResultFunction( KFModule* module, const std::string& dataname, KFElementResultFunction& function ) = 0;
        virtual void UnBindElementResultFunction( const std::string& dataname ) = 0;
    };
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
#define  __KF_CHECK_ADD_ELEMENT_FUNCTION__( checkfunction ) \
    bool checkfunction( KFEntity* player, KFData* kfparent, KFElement* kfelement, double multiple, const char* function, uint32 line )

#define  __REGISTER_CHECK_ADD_ELEMENT__( dataname, function )\
    _kf_component->RegisterCheckAddElementFunction( dataname, this, function )
#define  __UN_CHECK_ADD_ELEMENT__( dataname )\
    _kf_component->UnRegisterCheckAddElementFunction( dataname  )
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
#define __KF_ADD_ELEMENT_FUNCTION__( addfunction ) \
    bool addfunction( KFEntity* player, KFData* kfparent, KFElementResult* kfresult, const char* function, uint32 line )

#define  __REGISTER_ADD_ELEMENT__( dataname, function ) \
    _kf_component->RegisterAddElementFunction( dataname, this, function )
#define  __UN_ADD_ELEMENT__( dataname ) \
    _kf_component->UnRegisterAddElementFunction( dataname  )
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
#define  __KF_CHECK_REMOVE_ELEMENT_FUNCTION__( checkfunction ) \
    bool checkfunction( KFEntity* player, KFData* kfparent, KFElement* kfelement, double multiple, const char* function, uint32 line )

#define  __REGISTER_CHECK_REMOVE_ELEMENT__( dataname, function )\
    _kf_component->RegisterCheckRemoveElementFunction( dataname, this, function )
#define  __UN_CHECK_REMOVE_ELEMENT__( dataname )\
    _kf_component->UnRegisterCheckRemoveElementFunction( dataname )
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
#define  __KF_REMOVE_ELEMENT_FUNCTION__( removefunction ) \
    bool removefunction( KFEntity* player, KFData* kfparent, KFElementResult* kfresult, const char* function, uint32 line )

#define __REGISTER_REMOVE_ELEMENT__( dataname, function ) \
    _kf_component->RegisterRemoveElementFunction( dataname, this, function )
#define __UN_REMOVE_ELEMENT__( dataname ) \
    _kf_component->UnRegisterRemoveElementFunction( dataname )
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
#define __KF_ADD_DATA_FUNCTION__( addfunction ) \
    void addfunction( KFEntity* player, KFData* kfparent, uint64 key, KFData* kfdata )

#define __REGISTER_ADD_LOGIC__( dataname, function )\
    _kf_component->RegisterAddDataLogic( dataname, this, function )
#define __UN_ADD_LOGIC__( dataname )\
    _kf_component->UnRegisterAddDataLogic( dataname, this )

#define __REGISTER_ADD_DATA__( function )\
    _kf_component->RegisterAddDataModule( this, function )
#define __UN_ADD_DATA__()\
    _kf_component->UnRegisterAddDataModule( this )

#define __REGISTER_ADD_DATA_1__( dataname, function )\
    _kf_component->RegisterAddDataFunction( dataname, 0u, this, function )
#define __REGISTER_ADD_DATA_2__( dataname, key, function )\
    _kf_component->RegisterAddDataFunction( dataname, key, this, function )

#define __UN_ADD_DATA_1__( dataname )\
    _kf_component->UnRegisterAddDataFunction( this, dataname, 0u )
#define __UN_ADD_DATA_2__( dataname, key )\
    _kf_component->UnRegisterAddDataFunction( this, dataname, key  )
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
#define __KF_REMOVE_DATA_FUNCTION__( removefunction ) \
    void removefunction( KFEntity* player, KFData* kfparent, uint64 key, KFData* kfdata )

#define __REGISTER_REMOVE_LOGIC__( dataname, function )\
    _kf_component->RegisterRemoveDataLogic( dataname, this, function )
#define __UN_REMOVE_LOGIC__( dataname )\
    _kf_component->UnRegisterRemoveDataLogic( dataname, this )

#define __REGISTER_REMOVE_DATA__( function )\
    _kf_component->RegisterRemoveDataModule( this, function )
#define __UN_REMOVE_DATA__()\
    _kf_component->UnRegisterRemoveDataModule( this  )

#define __REGISTER_REMOVE_DATA_1__( dataname, function )\
    _kf_component->RegisterRemoveDataFunction( dataname, 0u, this, function )
#define __REGISTER_REMOVE_DATA_2__( dataname, key, function )\
    _kf_component->RegisterRemoveDataFunction( dataname, key, this, function )
#define __UN_REMOVE_DATA_1__( dataname )\
    _kf_component->UnRegisterRemoveDataFunction( this, dataname, 0u )
#define __UN_REMOVE_DATA_2__( dataname, key )\
    _kf_component->UnRegisterRemoveDataFunction( this, dataname, key )
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
#define __KF_UPDATE_DATA_FUNCTION__( updatefunction ) \
    void updatefunction( KFEntity* player, uint64 key, KFData* kfdata, uint32 operate, uint64 value, uint64 oldvalue, uint64 newvalue )

#define  __REGISTER_UPDATE_DATA__( function )\
    _kf_component->RegisterUpdateDataModule( this, function )
#define  __REGISTER_UPDATE_DATA_1__( dataname, updatefunction)\
    _kf_component->RegisterUpdateDataFunction( dataname, this, updatefunction )
#define  __REGISTER_UPDATE_DATA_2__( parentname, dataname, updatefunction)\
    _kf_component->RegisterUpdateDataFunction( parentname, dataname, this, updatefunction )

#define  __UN_UPDATE_DATA__()\
    _kf_component->UnRegisterUpdateDataModule( this )
#define  __UN_UPDATE_DATA_1__( dataname )\
    _kf_component->UnRegisterUpdateDataFunction( this, dataname )
#define  __UN_UPDATE_DATA_2__( parentname, dataname )\
    _kf_component->UnRegisterUpdateDataFunction( this, parentname, dataname )
    ///////////////////////////////////////////////////////////////////////////////////////////////////
#define  __KF_UPDATE_STRING_FUNCTION__( updatefunction ) \
    void updatefunction( KFEntity* player, KFData* kfdata, const std::string& oldvalue, const std::string& newvalue )

#define  __REGISTER_UPDATE_STRING__( updatefunction)\
    _kf_component->RegisterUpdateStringModule( this, updatefunction )
#define  __REGISTER_UPDATE_STRING_1__( dataname, updatefunction)\
    _kf_component->RegisterUpdateStringFunction( dataname, this, updatefunction )
#define  __REGISTER_UPDATE_STRING_2__( parentname, dataname, updatefunction)\
    _kf_component->RegisterUpdateStringFunction( parentname, dataname, this, updatefunction )

#define  __UN_UPDATE_STRING__()\
    _kf_component->UnRegisterUpdateStringModule( this )
#define  __UN_UPDATE_STRING_1__( dataname )\
    _kf_component->UnRegisterUpdateStringFunction( this, dataname )
#define  __UN_UPDATE_STRING_2__( parentname, dataname )\
    _kf_component->UnRegisterUpdateStringFunction( this, parentname, dataname )
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
#define  __KF_GET_CONFIG_VALUE_FUNCTION__( function ) \
    uint64 function( KFEntity* player, uint64 id, uint64 maxvalue )

#define __REGISTER_GET_CONFIG_VALUE__( dataname, function ) \
    _kf_component->RegisterGetConfigValueFunction( dataname, this, function )
#define __UN_GET_CONFIG_VALUE__( dataname ) \
    _kf_component->UnRegisterGetConfigValueFunction( dataname )
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
#define  __KF_LOG_ELEMENT_FUNCTION__( function ) \
    void function( KFEntity* player, const KFElementResult* kfresult )

#define __REGISTER_LOG_ELEMENT__( dataname, function ) \
    _kf_component->RegisterLogElementFunction( dataname, this, function )
#define __UN_LOG_ELEMENT__( dataname ) \
    _kf_component->UnRegisterLogElementFunction( dataname )
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
#define  __KF_ELEMENT_RESULT_FUNCTION__( function ) \
    bool function( KFEntity* player, const KFElementResult* kfresult )

#define __REGISTER_ELEMENT_RESULT__( modulename, function ) \
    _kf_component->RegisterElementResultFunction( modulename, this, function )
#define __UN_ELEMENT_RESULT__( modulename ) \
    _kf_component->UnRegisterElementResultFunction( modulename )
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif