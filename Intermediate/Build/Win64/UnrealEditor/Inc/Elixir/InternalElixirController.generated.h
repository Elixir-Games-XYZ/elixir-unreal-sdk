// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FElixirUserData;
struct FElixirCollection;
#ifdef ELIXIR_InternalElixirController_generated_h
#error "InternalElixirController.generated.h already included, missing '#pragma once' in InternalElixirController.h"
#endif
#define ELIXIR_InternalElixirController_generated_h

#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_11_DELEGATE \
struct _Script_Elixir_eventCallback_Parms \
{ \
	bool bSuccess; \
}; \
static inline void FCallback_DelegateWrapper(const FScriptDelegate& Callback, bool bSuccess) \
{ \
	_Script_Elixir_eventCallback_Parms Parms; \
	Parms.bSuccess=bSuccess ? true : false; \
	Callback.ProcessDelegate<UObject>(&Parms); \
}


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_16_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FElixirUserData_Statics; \
	ELIXIR_API static class UScriptStruct* StaticStruct();


template<> ELIXIR_API UScriptStruct* StaticStruct<struct FElixirUserData>();

#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_29_DELEGATE \
struct _Script_Elixir_eventUserDataCallback_Parms \
{ \
	bool bSuccess; \
	FElixirUserData userData; \
}; \
static inline void FUserDataCallback_DelegateWrapper(const FScriptDelegate& UserDataCallback, bool bSuccess, FElixirUserData userData) \
{ \
	_Script_Elixir_eventUserDataCallback_Parms Parms; \
	Parms.bSuccess=bSuccess ? true : false; \
	Parms.userData=userData; \
	UserDataCallback.ProcessDelegate<UObject>(&Parms); \
}


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_34_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics; \
	ELIXIR_API static class UScriptStruct* StaticStruct();


template<> ELIXIR_API UScriptStruct* StaticStruct<struct FElixirNFTAttribute>();

#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_44_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FElixirNFT_Statics; \
	ELIXIR_API static class UScriptStruct* StaticStruct();


template<> ELIXIR_API UScriptStruct* StaticStruct<struct FElixirNFT>();

#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_58_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FElixirCollection_Statics; \
	ELIXIR_API static class UScriptStruct* StaticStruct();


template<> ELIXIR_API UScriptStruct* StaticStruct<struct FElixirCollection>();

#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_67_DELEGATE \
struct _Script_Elixir_eventCollectionsCallback_Parms \
{ \
	bool bSuccess; \
	TArray<FElixirCollection> collections; \
}; \
static inline void FCollectionsCallback_DelegateWrapper(const FScriptDelegate& CollectionsCallback, bool bSuccess, TArray<FElixirCollection> const& collections) \
{ \
	_Script_Elixir_eventCollectionsCallback_Parms Parms; \
	Parms.bSuccess=bSuccess ? true : false; \
	Parms.collections=collections; \
	CollectionsCallback.ProcessDelegate<UObject>(&Parms); \
}


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_SPARSE_DATA
#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_RPC_WRAPPERS
#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUElixirSaveData(); \
	friend struct Z_Construct_UClass_UElixirSaveData_Statics; \
public: \
	DECLARE_CLASS(UElixirSaveData, USaveGame, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Elixir"), NO_API) \
	DECLARE_SERIALIZER(UElixirSaveData)


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_INCLASS \
private: \
	static void StaticRegisterNativesUElixirSaveData(); \
	friend struct Z_Construct_UClass_UElixirSaveData_Statics; \
public: \
	DECLARE_CLASS(UElixirSaveData, USaveGame, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Elixir"), NO_API) \
	DECLARE_SERIALIZER(UElixirSaveData)


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UElixirSaveData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UElixirSaveData) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UElixirSaveData); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UElixirSaveData); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UElixirSaveData(UElixirSaveData&&); \
	NO_API UElixirSaveData(const UElixirSaveData&); \
public:


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UElixirSaveData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UElixirSaveData(UElixirSaveData&&); \
	NO_API UElixirSaveData(const UElixirSaveData&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UElixirSaveData); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UElixirSaveData); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UElixirSaveData)


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_69_PROLOG
#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_SPARSE_DATA \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_RPC_WRAPPERS \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_INCLASS \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_SPARSE_DATA \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_INCLASS_NO_PURE_DECLS \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_72_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ELIXIR_API UClass* StaticClass<class UElixirSaveData>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
