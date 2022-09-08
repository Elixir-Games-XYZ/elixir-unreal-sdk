// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Elixir/Public/ElixirController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeElixirController() {}
// Cross Module References
	ELIXIR_API UClass* Z_Construct_UClass_UElixirController_NoRegister();
	ELIXIR_API UClass* Z_Construct_UClass_UElixirController();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintAsyncActionBase();
	UPackage* Z_Construct_UPackage__Script_Elixir();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	ELIXIR_API UFunction* Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature();
	ELIXIR_API UFunction* Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature();
	ELIXIR_API UFunction* Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature();
// End Cross Module References
	DEFINE_FUNCTION(UElixirController::execCloseElixir)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_PROPERTY_REF(FDelegateProperty,Z_Param_Out_OnComplete);
		P_FINISH;
		P_NATIVE_BEGIN;
		UElixirController::CloseElixir(Z_Param_WorldContextObject,FCallback(Z_Param_Out_OnComplete));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UElixirController::execGetCollections)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_PROPERTY_REF(FDelegateProperty,Z_Param_Out_OnComplete);
		P_FINISH;
		P_NATIVE_BEGIN;
		UElixirController::GetCollections(Z_Param_WorldContextObject,FCollectionsCallback(Z_Param_Out_OnComplete));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UElixirController::execGetUserData)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_PROPERTY_REF(FDelegateProperty,Z_Param_Out_OnComplete);
		P_FINISH;
		P_NATIVE_BEGIN;
		UElixirController::GetUserData(Z_Param_WorldContextObject,FUserDataCallback(Z_Param_Out_OnComplete));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UElixirController::execInitElixir)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_PROPERTY_REF(FDelegateProperty,Z_Param_Out_OnComplete);
		P_FINISH;
		P_NATIVE_BEGIN;
		UElixirController::InitElixir(Z_Param_WorldContextObject,FCallback(Z_Param_Out_OnComplete));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UElixirController::execPrepareElixir)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_DevAPIKey);
		P_GET_PROPERTY(FStrProperty,Z_Param_DevGameID);
		P_GET_PROPERTY(FStrProperty,Z_Param_ProdAPIKey);
		P_GET_PROPERTY(FStrProperty,Z_Param_ProdGameID);
		P_FINISH;
		P_NATIVE_BEGIN;
		UElixirController::PrepareElixir(Z_Param_DevAPIKey,Z_Param_DevGameID,Z_Param_ProdAPIKey,Z_Param_ProdGameID);
		P_NATIVE_END;
	}
	void UElixirController::StaticRegisterNativesUElixirController()
	{
		UClass* Class = UElixirController::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CloseElixir", &UElixirController::execCloseElixir },
			{ "GetCollections", &UElixirController::execGetCollections },
			{ "GetUserData", &UElixirController::execGetUserData },
			{ "InitElixir", &UElixirController::execInitElixir },
			{ "PrepareElixir", &UElixirController::execPrepareElixir },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UElixirController_CloseElixir_Statics
	{
		struct ElixirController_eventCloseElixir_Parms
		{
			UObject* WorldContextObject;
			FScriptDelegate OnComplete;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnComplete_MetaData[];
#endif
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_OnComplete;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UElixirController_CloseElixir_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventCloseElixir_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UElixirController_CloseElixir_Statics::NewProp_OnComplete_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UElixirController_CloseElixir_Statics::NewProp_OnComplete = { "OnComplete", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventCloseElixir_Parms, OnComplete), Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature, METADATA_PARAMS(Z_Construct_UFunction_UElixirController_CloseElixir_Statics::NewProp_OnComplete_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_CloseElixir_Statics::NewProp_OnComplete_MetaData)) }; // 1255884997
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElixirController_CloseElixir_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_CloseElixir_Statics::NewProp_WorldContextObject,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_CloseElixir_Statics::NewProp_OnComplete,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UElixirController_CloseElixir_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "OnComplete" },
		{ "Category", "Elixir" },
		{ "ModuleRelativePath", "Public/ElixirController.h" },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElixirController_CloseElixir_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UElixirController, nullptr, "CloseElixir", nullptr, nullptr, sizeof(Z_Construct_UFunction_UElixirController_CloseElixir_Statics::ElixirController_eventCloseElixir_Parms), Z_Construct_UFunction_UElixirController_CloseElixir_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_CloseElixir_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UElixirController_CloseElixir_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_CloseElixir_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UElixirController_CloseElixir()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElixirController_CloseElixir_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UElixirController_GetCollections_Statics
	{
		struct ElixirController_eventGetCollections_Parms
		{
			UObject* WorldContextObject;
			FScriptDelegate OnComplete;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnComplete_MetaData[];
#endif
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_OnComplete;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UElixirController_GetCollections_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventGetCollections_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UElixirController_GetCollections_Statics::NewProp_OnComplete_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UElixirController_GetCollections_Statics::NewProp_OnComplete = { "OnComplete", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventGetCollections_Parms, OnComplete), Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature, METADATA_PARAMS(Z_Construct_UFunction_UElixirController_GetCollections_Statics::NewProp_OnComplete_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_GetCollections_Statics::NewProp_OnComplete_MetaData)) }; // 4225519050
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElixirController_GetCollections_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_GetCollections_Statics::NewProp_WorldContextObject,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_GetCollections_Statics::NewProp_OnComplete,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UElixirController_GetCollections_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "OnComplete" },
		{ "Category", "Elixir" },
		{ "ModuleRelativePath", "Public/ElixirController.h" },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElixirController_GetCollections_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UElixirController, nullptr, "GetCollections", nullptr, nullptr, sizeof(Z_Construct_UFunction_UElixirController_GetCollections_Statics::ElixirController_eventGetCollections_Parms), Z_Construct_UFunction_UElixirController_GetCollections_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_GetCollections_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UElixirController_GetCollections_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_GetCollections_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UElixirController_GetCollections()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElixirController_GetCollections_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UElixirController_GetUserData_Statics
	{
		struct ElixirController_eventGetUserData_Parms
		{
			UObject* WorldContextObject;
			FScriptDelegate OnComplete;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnComplete_MetaData[];
#endif
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_OnComplete;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UElixirController_GetUserData_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventGetUserData_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UElixirController_GetUserData_Statics::NewProp_OnComplete_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UElixirController_GetUserData_Statics::NewProp_OnComplete = { "OnComplete", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventGetUserData_Parms, OnComplete), Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature, METADATA_PARAMS(Z_Construct_UFunction_UElixirController_GetUserData_Statics::NewProp_OnComplete_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_GetUserData_Statics::NewProp_OnComplete_MetaData)) }; // 677451729
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElixirController_GetUserData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_GetUserData_Statics::NewProp_WorldContextObject,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_GetUserData_Statics::NewProp_OnComplete,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UElixirController_GetUserData_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "OnComplete" },
		{ "Category", "Elixir" },
		{ "ModuleRelativePath", "Public/ElixirController.h" },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElixirController_GetUserData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UElixirController, nullptr, "GetUserData", nullptr, nullptr, sizeof(Z_Construct_UFunction_UElixirController_GetUserData_Statics::ElixirController_eventGetUserData_Parms), Z_Construct_UFunction_UElixirController_GetUserData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_GetUserData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UElixirController_GetUserData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_GetUserData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UElixirController_GetUserData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElixirController_GetUserData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UElixirController_InitElixir_Statics
	{
		struct ElixirController_eventInitElixir_Parms
		{
			UObject* WorldContextObject;
			FScriptDelegate OnComplete;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnComplete_MetaData[];
#endif
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_OnComplete;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UElixirController_InitElixir_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventInitElixir_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UElixirController_InitElixir_Statics::NewProp_OnComplete_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UElixirController_InitElixir_Statics::NewProp_OnComplete = { "OnComplete", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventInitElixir_Parms, OnComplete), Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature, METADATA_PARAMS(Z_Construct_UFunction_UElixirController_InitElixir_Statics::NewProp_OnComplete_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_InitElixir_Statics::NewProp_OnComplete_MetaData)) }; // 1255884997
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElixirController_InitElixir_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_InitElixir_Statics::NewProp_WorldContextObject,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_InitElixir_Statics::NewProp_OnComplete,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UElixirController_InitElixir_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "OnComplete" },
		{ "Category", "Elixir" },
		{ "ModuleRelativePath", "Public/ElixirController.h" },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElixirController_InitElixir_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UElixirController, nullptr, "InitElixir", nullptr, nullptr, sizeof(Z_Construct_UFunction_UElixirController_InitElixir_Statics::ElixirController_eventInitElixir_Parms), Z_Construct_UFunction_UElixirController_InitElixir_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_InitElixir_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UElixirController_InitElixir_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_InitElixir_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UElixirController_InitElixir()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElixirController_InitElixir_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UElixirController_PrepareElixir_Statics
	{
		struct ElixirController_eventPrepareElixir_Parms
		{
			FString DevAPIKey;
			FString DevGameID;
			FString ProdAPIKey;
			FString ProdGameID;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_DevAPIKey;
		static const UECodeGen_Private::FStrPropertyParams NewProp_DevGameID;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ProdAPIKey;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ProdGameID;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::NewProp_DevAPIKey = { "DevAPIKey", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventPrepareElixir_Parms, DevAPIKey), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::NewProp_DevGameID = { "DevGameID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventPrepareElixir_Parms, DevGameID), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::NewProp_ProdAPIKey = { "ProdAPIKey", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventPrepareElixir_Parms, ProdAPIKey), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::NewProp_ProdGameID = { "ProdGameID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ElixirController_eventPrepareElixir_Parms, ProdGameID), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::NewProp_DevAPIKey,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::NewProp_DevGameID,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::NewProp_ProdAPIKey,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::NewProp_ProdGameID,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::Function_MetaDataParams[] = {
		{ "Category", "Elixir" },
		{ "ModuleRelativePath", "Public/ElixirController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UElixirController, nullptr, "PrepareElixir", nullptr, nullptr, sizeof(Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::ElixirController_eventPrepareElixir_Parms), Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UElixirController_PrepareElixir()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElixirController_PrepareElixir_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UElixirController);
	UClass* Z_Construct_UClass_UElixirController_NoRegister()
	{
		return UElixirController::StaticClass();
	}
	struct Z_Construct_UClass_UElixirController_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UElixirController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintAsyncActionBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Elixir,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UElixirController_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UElixirController_CloseElixir, "CloseElixir" }, // 2856877400
		{ &Z_Construct_UFunction_UElixirController_GetCollections, "GetCollections" }, // 1388787454
		{ &Z_Construct_UFunction_UElixirController_GetUserData, "GetUserData" }, // 2123709903
		{ &Z_Construct_UFunction_UElixirController_InitElixir, "InitElixir" }, // 977987207
		{ &Z_Construct_UFunction_UElixirController_PrepareElixir, "PrepareElixir" }, // 724579541
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UElixirController_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ElixirController.h" },
		{ "ModuleRelativePath", "Public/ElixirController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UElixirController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UElixirController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UElixirController_Statics::ClassParams = {
		&UElixirController::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UElixirController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UElixirController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UElixirController()
	{
		if (!Z_Registration_Info_UClass_UElixirController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UElixirController.OuterSingleton, Z_Construct_UClass_UElixirController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UElixirController.OuterSingleton;
	}
	template<> ELIXIR_API UClass* StaticClass<UElixirController>()
	{
		return UElixirController::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UElixirController);
	struct Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UElixirController, UElixirController::StaticClass, TEXT("UElixirController"), &Z_Registration_Info_UClass_UElixirController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UElixirController), 199788878U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_1054103438(TEXT("/Script/Elixir"),
		Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_ElixirController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
