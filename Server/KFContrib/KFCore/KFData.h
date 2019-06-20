﻿#ifndef __KF_DATA_H__
#define __KF_DATA_H__

#include "KFrame.h"
#include "KFDataSetting.h"
#include "KFMath3D/Math3D.h"

namespace KFrame
{
    class KFData
    {
    public:
        KFData() = default;
        virtual ~KFData() = default;

        template< class T > T InvalidValue();
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< class T = uint64 > T GetValue();
        template< class T = uint64 > T GetValue( const std::string& dataname );
        template< class T = uint64 > T GetValue( const std::string& parentname, const std::string& dataname );
        template< class T = uint64 > T GetValue( uint64 key, const std::string& dataname );
        template< class T = uint64 > T GetValue( const std::string& parentname, uint64 key, const std::string& dataname );
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< class T = uint64 > T SetValue( T value );
        template< class T = uint64 > T SetValue( const std::string& dataname, T value );
        template< class T = uint64 > T SetValue( const std::string& parentname, const std::string& dataname, T value );
        template< class T = uint64 > T SetValue( uint64 key, const std::string& dataname, T value );
        template< class T = uint64 > T SetValue( const std::string& parentname, uint64 key, const std::string& dataname, T value );
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< class T = uint64 > T OperateValue( uint32 operate, T value );
        template< class T = uint64 > T OperateValue( const std::string& dataname, uint32 operate, T value );
        template< class T = uint64 > T OperateValue( const std::string& parentname, const std::string& dataname, uint32 operate, T value );
        template< class T = uint64 > T OperateValue( uint64 key, const std::string& dataname, uint32 operate, T value );
        template< class T = uint64 > T OperateValue( const std::string& dataname, uint64 key, uint32 operate, T value );
        template< class T = uint64 > T OperateValue( const std::string& parentname, uint64 key, const std::string& dataname, uint32 operate, T value );
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 重置
        virtual void Reset() = 0;

        // 是否有效
        virtual bool IsValid() = 0;

        // 数量
        virtual uint32 Size();

        // 是否达到了最大值
        virtual bool IsFull();

        // 名字
        virtual const std::string& GetName() const;

        // 类型
        virtual uint32 GetType() const;

        // keyid
        virtual uint64 GetKeyID();
        virtual void SetKeyID( uint64 id );
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // 属性配置
        const KFClassSetting* GetClassSetting() const;
        const KFDataSetting* GetDataSetting() const;

        // 属性标识
        bool HaveFlagMask( uint32 mask );

        // 初始化
        virtual void Initialize( const KFClassSetting* classsetting, const KFDataSetting* datasetting );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 父属性
        KFData* GetParent();
        void SetParent( KFData* data );

        // 遍历节点
        virtual KFData* FirstData();
        virtual KFData* NextData();

        // 赋值/保存
        virtual void CopyFrom( KFData* kfother ) = 0;
        virtual void SaveTo( KFData* kfother ) = 0;

        // 格式化成字串
        virtual std::string ToString() = 0;
        virtual void FromString( const std::string& value ) = 0;

        // Map的特殊操作
        virtual void ToMap( MapString& values );
        virtual void FromMap( const MapString& values );
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // object

        // 如:money
        virtual KFData* FindData( const std::string& dataname );

        // 如:hero->1
        virtual KFData* FindData( const std::string& dataname, uint64 key );

        // 如: basic->id
        virtual KFData* FindData( const std::string& parentname, const std::string& childname );

        // 如: hero->1->level
        virtual KFData* FindData( const std::string& parentname, uint64 key, const std::string& childname );

        // 如: sign->day->1
        virtual KFData* FindData( const std::string& parentname, const std::string& childname, uint64 key );

        // 如: sign->day->value
        virtual KFData* FindData( const std::string& parentname, const std::string& childname, const std::string& dataname );

        virtual bool AddData( const std::string& dataname, KFData* data );
        virtual bool AddData( const std::string& dataname, uint64 key, KFData* data );
        virtual bool AddData( const std::string& parentname, const std::string& childname, KFData* data );

        virtual KFData* MoveData( const std::string& dataname );
        virtual bool RemoveData( const std::string& dataname );
        virtual bool RemoveData( const std::string& dataname, uint64 key );
        virtual bool RemoveData( const std::string& parentname, const std::string& childname );
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // record
        virtual KFData* FindData( uint64 key );
        virtual KFData* FindData( uint64 key, const std::string& dataname );
        virtual KFData* FindData( uint64 parentkey, uint64 childkey );
        virtual KFData* FindData( uint64 parentkey, uint64 childkey, const std::string& dataname );
        virtual KFData* FindData( uint64 parentkey, const std::string& dataname, uint64 childkey );

        virtual bool AddData( uint64 key, KFData* data );
        virtual bool AddData( uint64 parentkey, uint64 childkey, KFData* data );
        virtual bool AddData( uint64 key, const std::string& dataname, KFData* data );

        virtual KFData* MoveData( uint64 key );
        virtual bool RemoveData( uint64 key );
        virtual bool RemoveData( uint64 key, const std::string& dataname );

        virtual void FindData( const std::string& dataname, uint64 value, std::list< KFData* >& findlist );
        virtual bool CheckData( const std::string& dataname, uint64 value, const std::string& checkname, uint64 checkvalue );
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:
        virtual int32 GetInt32();
        virtual int32 SetInt32( int32 );

        virtual uint32 GetUInt32();
        virtual uint32 SetUInt32( uint32 );

        virtual int64 GetInt64();
        virtual int64 SetInt64( int64 );

        virtual uint64 GetUInt64();
        virtual uint64 SetUInt64( uint64 );

        virtual double GetDouble();
        virtual double SetDouble( double );

        virtual const std::string& GetString();
        virtual const std::string& SetString( const std::string& );

        virtual const Math3D::Vector3D& GetVector3D();
        virtual const Math3D::Vector3D& SetVector3D( const Math3D::Vector3D& );

    public:
        // 属性配置
        const KFDataSetting* _data_setting = nullptr;

        // 类配置
        const KFClassSetting* _class_setting = nullptr;

    protected:
        // 类型
        uint32 _type = 0u;

        // 父属性
        KFData* _parent = nullptr;
    };
}

#include "KFData.inl"

#endif
