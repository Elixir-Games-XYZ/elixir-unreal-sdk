// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
#ifdef ELIXIR_ElixirController_generated_h
#error "ElixirController.generated.h already included, missing '#pragma once' in ElixirController.h"
#endif
#define ELIXIR_ElixirController_generated_h

#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_SPARSE_DATA
#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execCloseElixir); \
	DECLARE_FUNCTION(execGetCollections); \
	DECLARE_FUNCTION(execGetUserData); \
	DECLARE_FUNCTION(execInitElixir); \
	DECLARE_FUNCTION(execPrepareElixir);


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execCloseElixir); \
	DECLARE_FUNCTION(execGetCollections); \
	DECLARE_FUNCTION(execGetUserData); \
	DECLARE_FUNCTION(execInitElixir); \
	DECLARE_FUNCTION(execPrepareElixir);


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUElixirController(); \
	friend struct Z_Construct_UClass_UElixirController_Statics; \
public: \
	DECLARE_CLASS(UElixirController, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Elixir"), NO_API) \
	DECLARE_SERIALIZER(UElixirController)


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_INCLASS \
private: \
	static void StaticRegisterNativesUElixirController(); \
	friend struct Z_Construct_UClass_UElixirController_Statics; \
public: \
	DECLARE_CLASS(UElixirController, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Elixir"), NO_API) \
	DECLARE_SERIALIZER(UElixirController)


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UElixirController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UElixirController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UElixirController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UElixirController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UElixirController(UElixirController&&); \
	NO_API UElixirController(const UElixirController&); \
public:


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UElixirController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UElixirController(UElixirController&&); \
	NO_API UElixirController(const UElixirController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UElixirController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UElixirController); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UElixirController)


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_8_PROLOG
#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_SPARSE_DATA \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_RPC_WRAPPERS \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_INCLASS \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_SPARSE_DATA \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_INCLASS_NO_PURE_DECLS \
	FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ELIXIR_API UClass* StaticClass<class UElixirController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
