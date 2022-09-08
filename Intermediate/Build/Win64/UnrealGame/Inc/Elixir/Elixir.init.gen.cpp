// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeElixir_init() {}
	ELIXIR_API UFunction* Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature();
	ELIXIR_API UFunction* Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature();
	ELIXIR_API UFunction* Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Elixir;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Elixir()
	{
		if (!Z_Registration_Info_UPackage__Script_Elixir.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_Elixir_Callback__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_Elixir_CollectionsCallback__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_Elixir_UserDataCallback__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Elixir",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x490415FF,
				0x4E5C7A16,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Elixir.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Elixir.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Elixir(Z_Construct_UPackage__Script_Elixir, TEXT("/Script/Elixir"), Z_Registration_Info_UPackage__Script_Elixir, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x490415FF, 0x4E5C7A16));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
