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
struct FElixirTournament
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString GameId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString CreatedAt;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString StartsAt;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString EndsAt;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString RepeatEvery;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Location;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString EventUrl;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString UserId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString ImageUrl;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString PrizePool;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Visibility;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString PrizeDescription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString SettingsId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Leaderboard;
};

UENUM(BlueprintType)
enum class EElixirTournamentFilterType : uint8
{
	Active,
	All
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

USTRUCT(BlueprintType, Category = "Elixir")
struct FGetWalletResultOverlayMessage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Status;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString EthAddress;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString SolAddress;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString EosAddress;
};

USTRUCT(BlueprintType, Category = "Elixir")
struct FSignTypedDataResultOverlayMessage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Status;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Signature;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString R;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString S;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString V;
};

USTRUCT(BlueprintType, Category = "Elixir")
struct FGetConsentResultEVMOverlayMessage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Status;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString TransactionChainScanUrl;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString TransactionHash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString TransactionId;
};

USTRUCT(BlueprintType, Category = "Elixir")
struct FGetConsentResultSolanaOverlayMessage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Status;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString TransactionId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString TransactionSignature;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString TransactionChainScanUrl;
};


