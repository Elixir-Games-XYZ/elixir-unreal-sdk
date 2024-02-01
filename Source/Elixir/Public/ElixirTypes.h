#pragma once

#include "CoreMinimal.h"
#include "ElixirTypes.generated.h"


USTRUCT(BlueprintType, Category = "Elixir")
struct FElixirUserData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Sub;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Iss;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	TArray<FString> Wallets;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Nickname;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Picture;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Aud;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Status;
};


USTRUCT(BlueprintType, Category = "Elixir")
struct FElixirNftAttribute
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString TraitType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString DisplayType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Value;
};

USTRUCT(BlueprintType, Category = "Elixir")
struct FElixirNft
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString TokenId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Image;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	TArray<FElixirNftAttribute> Attributes;
};

USTRUCT(BlueprintType, Category = "Elixir")
struct FElixirCollection
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Collection;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString CollectionName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	TArray<FElixirNft> Nfts;
};

USTRUCT(BlueprintType, Category = "Elixir")
struct FOpenStateChangeOverlayMessage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	bool IsOpen;
};

USTRUCT(BlueprintType, Category = "Elixir")
struct FCheckoutResultOverlayMessage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	bool Success;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Sku;	
};