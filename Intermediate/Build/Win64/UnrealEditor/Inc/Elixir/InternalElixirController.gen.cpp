// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Elixir/Public/InternalElixirController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInternalElixirController() {}
// Cross Module References
	ELIXIR_API UFunction* Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_Elixir();
	ELIXIR_API UScriptStruct* Z_Construct_UScriptStruct_FElixirUserData();
	ELIXIR_API UFunction* Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature();
	ELIXIR_API UScriptStruct* Z_Construct_UScriptStruct_FElixirNFTAttribute();
	ELIXIR_API UScriptStruct* Z_Construct_UScriptStruct_FElixirNFT();
	ELIXIR_API UScriptStruct* Z_Construct_UScriptStruct_FElixirCollection();
	ELIXIR_API UFunction* Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature();
	ELIXIR_API UClass* Z_Construct_UClass_UElixirSaveData_NoRegister();
	ELIXIR_API UClass* Z_Construct_UClass_UElixirSaveData();
	ENGINE_API UClass* Z_Construct_UClass_USaveGame();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics
	{
		struct _Script_Elixir_eventCallback_Parms
		{
			bool bSuccess;
		};
		static void NewProp_bSuccess_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::NewProp_bSuccess_SetBit(void* Obj)
	{
		((_Script_Elixir_eventCallback_Parms*)Obj)->bSuccess = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(_Script_Elixir_eventCallback_Parms), &Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::NewProp_bSuccess,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_Elixir, nullptr, "Callback__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::_Script_Elixir_eventCallback_Parms), Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ElixirUserData;
class UScriptStruct* FElixirUserData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ElixirUserData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ElixirUserData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FElixirUserData, Z_Construct_UPackage__Script_Elixir(), TEXT("ElixirUserData"));
	}
	return Z_Registration_Info_UScriptStruct_ElixirUserData.OuterSingleton;
}
template<> ELIXIR_API UScriptStruct* StaticStruct<FElixirUserData>()
{
	return FElixirUserData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FElixirUserData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_elixirId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_elixirId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_nickname_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_nickname;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_avatar_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_avatar;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_wallet_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_wallet;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirUserData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "Elixir" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FElixirUserData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FElixirUserData>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_elixirId_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_elixirId = { "elixirId", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirUserData, elixirId), METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_elixirId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_elixirId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_nickname_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_nickname = { "nickname", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirUserData, nickname), METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_nickname_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_nickname_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_avatar_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_avatar = { "avatar", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirUserData, avatar), METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_avatar_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_avatar_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_wallet_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_wallet = { "wallet", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirUserData, wallet), METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_wallet_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_wallet_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FElixirUserData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_elixirId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_nickname,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_avatar,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirUserData_Statics::NewProp_wallet,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FElixirUserData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Elixir,
		nullptr,
		&NewStructOps,
		"ElixirUserData",
		sizeof(FElixirUserData),
		alignof(FElixirUserData),
		Z_Construct_UScriptStruct_FElixirUserData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirUserData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirUserData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirUserData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FElixirUserData()
	{
		if (!Z_Registration_Info_UScriptStruct_ElixirUserData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ElixirUserData.InnerSingleton, Z_Construct_UScriptStruct_FElixirUserData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_ElixirUserData.InnerSingleton;
	}
	struct Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics
	{
		struct _Script_Elixir_eventUserDataCallback_Parms
		{
			bool bSuccess;
			FElixirUserData userData;
		};
		static void NewProp_bSuccess_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
		static const UECodeGen_Private::FStructPropertyParams NewProp_userData;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::NewProp_bSuccess_SetBit(void* Obj)
	{
		((_Script_Elixir_eventUserDataCallback_Parms*)Obj)->bSuccess = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(_Script_Elixir_eventUserDataCallback_Parms), &Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::NewProp_userData = { "userData", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_Elixir_eventUserDataCallback_Parms, userData), Z_Construct_UScriptStruct_FElixirUserData, METADATA_PARAMS(nullptr, 0) }; // 4158433215
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::NewProp_bSuccess,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::NewProp_userData,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_Elixir, nullptr, "UserDataCallback__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::_Script_Elixir_eventUserDataCallback_Parms), Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ElixirNFTAttribute;
class UScriptStruct* FElixirNFTAttribute::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ElixirNFTAttribute.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ElixirNFTAttribute.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FElixirNFTAttribute, Z_Construct_UPackage__Script_Elixir(), TEXT("ElixirNFTAttribute"));
	}
	return Z_Registration_Info_UScriptStruct_ElixirNFTAttribute.OuterSingleton;
}
template<> ELIXIR_API UScriptStruct* StaticStruct<FElixirNFTAttribute>()
{
	return FElixirNFTAttribute::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_trait_type_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_trait_type;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_value_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "Elixir" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FElixirNFTAttribute>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewProp_trait_type_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewProp_trait_type = { "trait_type", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirNFTAttribute, trait_type), METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewProp_trait_type_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewProp_trait_type_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewProp_value_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirNFTAttribute, value), METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewProp_value_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewProp_value_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewProp_trait_type,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewProp_value,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Elixir,
		nullptr,
		&NewStructOps,
		"ElixirNFTAttribute",
		sizeof(FElixirNFTAttribute),
		alignof(FElixirNFTAttribute),
		Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FElixirNFTAttribute()
	{
		if (!Z_Registration_Info_UScriptStruct_ElixirNFTAttribute.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ElixirNFTAttribute.InnerSingleton, Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_ElixirNFTAttribute.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ElixirNFT;
class UScriptStruct* FElixirNFT::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ElixirNFT.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ElixirNFT.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FElixirNFT, Z_Construct_UPackage__Script_Elixir(), TEXT("ElixirNFT"));
	}
	return Z_Registration_Info_UScriptStruct_ElixirNFT.OuterSingleton;
}
template<> ELIXIR_API UScriptStruct* StaticStruct<FElixirNFT>()
{
	return FElixirNFT::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FElixirNFT_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_tokenId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_tokenId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_name_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_name;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_image_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_image;
		static const UECodeGen_Private::FStructPropertyParams NewProp_attributes_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_attributes_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_attributes;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirNFT_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "Elixir" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FElixirNFT_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FElixirNFT>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_tokenId_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_tokenId = { "tokenId", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirNFT, tokenId), METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_tokenId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_tokenId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_name_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_name = { "name", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirNFT, name), METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_image_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_image = { "image", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirNFT, image), METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_image_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_image_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_attributes_Inner = { "attributes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FElixirNFTAttribute, METADATA_PARAMS(nullptr, 0) }; // 1654969126
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_attributes_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_attributes = { "attributes", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirNFT, attributes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_attributes_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_attributes_MetaData)) }; // 1654969126
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FElixirNFT_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_tokenId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_image,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_attributes_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirNFT_Statics::NewProp_attributes,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FElixirNFT_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Elixir,
		nullptr,
		&NewStructOps,
		"ElixirNFT",
		sizeof(FElixirNFT),
		alignof(FElixirNFT),
		Z_Construct_UScriptStruct_FElixirNFT_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirNFT_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirNFT_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirNFT_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FElixirNFT()
	{
		if (!Z_Registration_Info_UScriptStruct_ElixirNFT.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ElixirNFT.InnerSingleton, Z_Construct_UScriptStruct_FElixirNFT_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_ElixirNFT.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ElixirCollection;
class UScriptStruct* FElixirCollection::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ElixirCollection.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ElixirCollection.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FElixirCollection, Z_Construct_UPackage__Script_Elixir(), TEXT("ElixirCollection"));
	}
	return Z_Registration_Info_UScriptStruct_ElixirCollection.OuterSingleton;
}
template<> ELIXIR_API UScriptStruct* StaticStruct<FElixirCollection>()
{
	return FElixirCollection::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FElixirCollection_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_collection_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_collection;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_collectionName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_collectionName;
		static const UECodeGen_Private::FStructPropertyParams NewProp_nfts_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_nfts_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_nfts;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirCollection_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "Elixir" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FElixirCollection_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FElixirCollection>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_collection_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_collection = { "collection", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirCollection, collection), METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_collection_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_collection_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_collectionName_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_collectionName = { "collectionName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirCollection, collectionName), METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_collectionName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_collectionName_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_nfts_Inner = { "nfts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FElixirNFT, METADATA_PARAMS(nullptr, 0) }; // 4184271733
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_nfts_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_nfts = { "nfts", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FElixirCollection, nfts), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_nfts_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_nfts_MetaData)) }; // 4184271733
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FElixirCollection_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_collection,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_collectionName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_nfts_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FElixirCollection_Statics::NewProp_nfts,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FElixirCollection_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Elixir,
		nullptr,
		&NewStructOps,
		"ElixirCollection",
		sizeof(FElixirCollection),
		alignof(FElixirCollection),
		Z_Construct_UScriptStruct_FElixirCollection_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirCollection_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FElixirCollection_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FElixirCollection_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FElixirCollection()
	{
		if (!Z_Registration_Info_UScriptStruct_ElixirCollection.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ElixirCollection.InnerSingleton, Z_Construct_UScriptStruct_FElixirCollection_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_ElixirCollection.InnerSingleton;
	}
	struct Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics
	{
		struct _Script_Elixir_eventCollectionsCallback_Parms
		{
			bool bSuccess;
			TArray<FElixirCollection> collections;
		};
		static void NewProp_bSuccess_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
		static const UECodeGen_Private::FStructPropertyParams NewProp_collections_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_collections_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_collections;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::NewProp_bSuccess_SetBit(void* Obj)
	{
		((_Script_Elixir_eventCollectionsCallback_Parms*)Obj)->bSuccess = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(_Script_Elixir_eventCollectionsCallback_Parms), &Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::NewProp_collections_Inner = { "collections", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FElixirCollection, METADATA_PARAMS(nullptr, 0) }; // 3461099612
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::NewProp_collections_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::NewProp_collections = { "collections", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_Elixir_eventCollectionsCallback_Parms, collections), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::NewProp_collections_MetaData, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::NewProp_collections_MetaData)) }; // 3461099612
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::NewProp_bSuccess,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::NewProp_collections_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::NewProp_collections,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_Elixir, nullptr, "CollectionsCallback__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::_Script_Elixir_eventCollectionsCallback_Parms), Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	void UElixirSaveData::StaticRegisterNativesUElixirSaveData()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UElixirSaveData);
	UClass* Z_Construct_UClass_UElixirSaveData_NoRegister()
	{
		return UElixirSaveData::StaticClass();
	}
	struct Z_Construct_UClass_UElixirSaveData_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RefreshToken_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_RefreshToken;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UElixirSaveData_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USaveGame,
		(UObject* (*)())Z_Construct_UPackage__Script_Elixir,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UElixirSaveData_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "InternalElixirController.h" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UElixirSaveData_Statics::NewProp_RefreshToken_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "Public/InternalElixirController.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UElixirSaveData_Statics::NewProp_RefreshToken = { "RefreshToken", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UElixirSaveData, RefreshToken), METADATA_PARAMS(Z_Construct_UClass_UElixirSaveData_Statics::NewProp_RefreshToken_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UElixirSaveData_Statics::NewProp_RefreshToken_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UElixirSaveData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElixirSaveData_Statics::NewProp_RefreshToken,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UElixirSaveData_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UElixirSaveData>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UElixirSaveData_Statics::ClassParams = {
		&UElixirSaveData::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UElixirSaveData_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UElixirSaveData_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UElixirSaveData_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UElixirSaveData_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UElixirSaveData()
	{
		if (!Z_Registration_Info_UClass_UElixirSaveData.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UElixirSaveData.OuterSingleton, Z_Construct_UClass_UElixirSaveData_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UElixirSaveData.OuterSingleton;
	}
	template<> ELIXIR_API UClass* StaticClass<UElixirSaveData>()
	{
		return UElixirSaveData::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UElixirSaveData);
	struct Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_Statics::ScriptStructInfo[] = {
		{ FElixirUserData::StaticStruct, Z_Construct_UScriptStruct_FElixirUserData_Statics::NewStructOps, TEXT("ElixirUserData"), &Z_Registration_Info_UScriptStruct_ElixirUserData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FElixirUserData), 4158433215U) },
		{ FElixirNFTAttribute::StaticStruct, Z_Construct_UScriptStruct_FElixirNFTAttribute_Statics::NewStructOps, TEXT("ElixirNFTAttribute"), &Z_Registration_Info_UScriptStruct_ElixirNFTAttribute, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FElixirNFTAttribute), 1654969126U) },
		{ FElixirNFT::StaticStruct, Z_Construct_UScriptStruct_FElixirNFT_Statics::NewStructOps, TEXT("ElixirNFT"), &Z_Registration_Info_UScriptStruct_ElixirNFT, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FElixirNFT), 4184271733U) },
		{ FElixirCollection::StaticStruct, Z_Construct_UScriptStruct_FElixirCollection_Statics::NewStructOps, TEXT("ElixirCollection"), &Z_Registration_Info_UScriptStruct_ElixirCollection, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FElixirCollection), 3461099612U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UElixirSaveData, UElixirSaveData::StaticClass, TEXT("UElixirSaveData"), &Z_Registration_Info_UClass_UElixirSaveData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UElixirSaveData), 3810280536U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_1409563879(TEXT("/Script/Elixir"),
		Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_HostProject_Plugins_Elixir_Source_Elixir_Public_InternalElixirController_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
