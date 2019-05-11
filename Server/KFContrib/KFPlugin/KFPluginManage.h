﻿#ifndef __KF_PLUGIN_MANAGE_H__
#define __KF_PLUGIN_MANAGE_H__

#include "KFrame.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define __KF_PLUGIN_ENRTY__( classname )\
    KFrame::KFPlugin* DllPluginEntry( KFrame::KFPluginManage* pluginmanage, KFrame::KFGlobal* kfglobal, KFrame::KFMalloc* kfmalloc, KFrame::KFLogger* kflogger )\
    {\
        KFrame::KFGlobal::Initialize( kfglobal );\
        KFrame::KFMalloc::Initialize( kfmalloc );\
        KFrame::KFLogger::Initialize( kflogger );\
        return pluginmanage->RegistPlugin< classname >();\
    }\

#define __KF_PLUGIN_LEAVE__( classname ) \
    void DllPluginLeave( KFrame::KFPluginManage* pluginmanage )\
    {\
        pluginmanage->UnRegistPlugin< classname >();\
    }\

#if __KF_SYSTEM__ == __KF_WIN__
#define __CHECK_PLUGIN_FUNCTION__( module, function )\
    std::string basename = typeid( &KFModule::function ).name();\
    std::string childname = typeid( &module::function ).name();\
    if ( basename != childname )\

#else
#define __CHECK_PLUGIN_FUNCTION__( module, function )\
    KFModule kfbase;\
    void ( KFModule::*basemfp )() = &KFModule::function; \
    auto bassaddress = ( void* )( kfbase.*basemfp ); \
    auto kfmodule = static_cast < module* >( _kf_module );\
    void ( module::*childmfp )() = &module::function; \
    auto childaddress = (void*)( kfmodule->*childmfp );\
    if ( bassaddress != childaddress )\

#endif

#define __REGISTER_PLUGIN_FUNCTION__( module, function )\
    {\
        __CHECK_PLUGIN_FUNCTION__( module, function )\
        {   \
            auto ok = _kf_plugin_manage->Register##function##Function< module >( _sort, kfmodule, &module::function );\
            if ( !ok )\
            {\
                __LOG_ERROR__( "module=[{}] sort=[{}] function=[{}] is already register!", #module, _sort, #function );\
            }\
            else\
            {\
                __LOG_INFO__( "module=[{}] sort=[{}] register function=[{}] ok!", #module, _sort, #function );\
            }\
        }\
    }

#define __UNREGISTER_PLUGIN_FUNCTION__( module, function )\
    {\
        __CHECK_PLUGIN_FUNCTION__( module, function )\
        {   \
            _kf_plugin_manage->UnRegister##function##Function( _sort );\
        }\
    }

// 注册模块
#define __REGISTER_MODULE__( name ) \
    auto kfmodule = new name##Module();\
    _kf_plugin_manage->RegistModule< name##Plugin, name##Interface >( kfmodule );\
    __REGISTER_PLUGIN_FUNCTION__( name##Module, Run );\
    __REGISTER_PLUGIN_FUNCTION__( name##Module, AfterRun );\

// 卸载模块
#define __UNREGISTER_MODULE__( name ) \
    __UNREGISTER_PLUGIN_FUNCTION__( name##Module, Run );\
    __UNREGISTER_PLUGIN_FUNCTION__( name##Module, AfterRun );\
    _kf_plugin_manage->UnRegistModule< name##Plugin >();\

#define __FIND_MODULE__( module, classname ) \
    module = _kf_plugin_manage->FindModule< classname >( __FILE__, __LINE__ )

#define __FIND_MODULE_NO_LOG__( module, classname ) \
    module = _kf_plugin_manage->FindModule< classname >()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace KFrame
{
    class KFDebugCommand
    {
    public:
        std::string _command;
        VectorString  _params;
    };

    typedef std::function<void()> KFRunFunction;
    typedef std::function<void( const VectorString& )> KFCmdFunction;
    //////////////////////////////////////////////////////////////////////
    class KFAppSetting;
    class KFPluginManage : public KFSingleton< KFPluginManage >
    {
    public:
        KFPluginManage();
        ~KFPluginManage();

        ///////////////////////////////////////////////////////////////////////////
        // 初始化
        bool InitPlugin();

        // 关闭
        void ShutDown();

        // 逻辑
        void Run();

        // 添加命令
        void AddCommand( std::string command );
        /////////////////////////////////////////////////////////////////////////

        // 注册插件
        template< class T >
        T* RegistPlugin()
        {
            auto plugin = new T ();
            return dynamic_cast<T*>( RegistPlugin( typeid( T ).name(), plugin ) );
        }

        // 卸载插件
        template< class T >
        void UnRegistPlugin()
        {
            std::string name = typeid( T ).name();
            UnRegistPlugin( name );
        }

        // 查找插件
        template< class T >
        T* FindPlugin()
        {
            std::string name = typeid( T ).name();
            return dynamic_cast<T*>( FindPlugin( name ) );
        }

        /////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////
        // 注册模块
        template< class PluginType, class InterfaceType >
        void RegistModule( InterfaceType* module )
        {
            auto plugin = FindPlugin< PluginType >();
            plugin->BindModule( typeid( InterfaceType ).name(), module );
        }

        // 卸载模块
        template< class PluginType >
        void UnRegistModule()
        {
            auto plugin = FindPlugin< PluginType >();
            plugin->UnBindModule();
        }

        // 查找模块
        template< class InterfaceType >
        InterfaceType* FindModule( const char* file, uint32 line )
        {
            std::string name = typeid( InterfaceType ).name();
            return dynamic_cast< InterfaceType*>( FindModule( name, file, line ) );
        }

        template< class InterfaceType >
        InterfaceType* FindModule()
        {
            std::string name = typeid( InterfaceType ).name();
            return dynamic_cast< InterfaceType* >( FindModule( name ) );
        }
        /////////////////////////////////////////////////////////////////
        template< class T >
        void RegisterCommandFunction( const std::string& command, T* object, void ( T::*handle )( const VectorString& ) )
        {
            auto kffunction = _command_functions.Create( command );
            kffunction->_function = std::bind( handle, object, std::placeholders::_1 );
        }

        void UnRegisterCommandFunction( const std::string& command )
        {
            _command_functions.Remove( command );
        }

        /////////////////////////////////////////////////////////////////
        template< class T >
        bool RegisterRunFunction( uint32 sort, T* object, void ( T::*handle )() )
        {
            auto kffunction = _run_functions.Find( sort );
            if ( kffunction != nullptr )
            {
                return false;
            }

            kffunction = _run_functions.Create( sort );
            kffunction->_function = std::bind( handle, object );
            return true;
        }

        void UnRegisterRunFunction( uint32 sort )
        {
            _run_functions.Remove( sort );
        }

        /////////////////////////////////////////////////////////////////
        template< class T >
        bool RegisterAfterRunFunction( uint32 sort, T* object, void ( T::*handle )( ) )
        {
            auto kffunction = _after_run_functions.Find( sort );
            if ( kffunction != nullptr )
            {
                return false;
            }

            kffunction = _after_run_functions.Create( sort );
            kffunction->_function = std::bind( handle, object );
            return true;
        }

        void UnRegisterAfterRunFunction( uint32 sort )
        {
            _after_run_functions.Remove( sort );
        }
        /////////////////////////////////////////////////////////////////

    protected:
        ////////////////////////////////////////////////////////////////////
        // 安装模块
        void InstallPlugin();

        // 加载模块
        void LoadModule();

        // 初始化模块
        void InitModule();

        // 加载配置
        void LoadConfig();

        // 准备执行
        void BeforeRun();

        // 执行一次
        void OnceRun();

        // 执行命令
        void RunCommand();
        ////////////////////////////////////////////////////////////////////

        // 注册插件
        KFPlugin* RegistPlugin( const std::string& name, KFPlugin* plugin );

        // 卸载插件
        void UnRegistPlugin( const std::string& name );

        // 查找插件
        KFPlugin* FindPlugin( const std::string& name );

        // 查找模块
        KFModule* FindModule( const std::string& name, const char* file, uint32 line );
        KFModule* FindModule( const std::string& name );

    protected:
        std::vector< KFPlugin* > _plugins;

        // 命令列表
        KFQueue< KFDebugCommand > _commands;
        KFBind< std::string, const std::string&, KFCmdFunction > _command_functions;

        // 注册的Run函数
        KFBind< uint32, uint32, KFRunFunction > _run_functions;
        KFBind< uint32, uint32, KFRunFunction > _after_run_functions;
    };
}

#endif