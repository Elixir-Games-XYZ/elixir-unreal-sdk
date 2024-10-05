#pragma once

#include "OverlayMessage.h"
#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "SElixirEventSimulator.generated.h"

#define LOCTEXT_NAMESPACE "ElixirEventSimulator"

USTRUCT()
struct FElixirEventItem
{
	GENERATED_BODY()

	UPROPERTY()
	FString Direction;
	UPROPERTY()
	FString Name;
	UPROPERTY()
	FString Payload;
};

/**
 * Slate widget to allow users to simulate elixir overlay events.
 */
class SElixirEventSimulator : public SCompoundWidget
{
public:
	/** Default constructor. */
	SElixirEventSimulator();

	/** Virtual destructor. */
	virtual ~SElixirEventSimulator() override;

	/** Release all the resources */
	void ReleaseResources();

	SLATE_BEGIN_ARGS(SElixirEventSimulator)
		{
		}

	SLATE_END_ARGS()

	/**
	* Constructs this widget.
	*/
	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	FText GetStartStopButtonText() const;
	bool IsSimulating() const;
	FReply OnStartStop();
	FReply OnClear();
	FReply OnSend();

	void StartSimulating();
	void StopSimulating();
	bool SendCheckoutResult(bool Result, const FString& Sku);
	bool SendGetWalletResult(const FString& Status, const FString& EthAddress, const FString& SolAddress,
		const FString& EosAddress);
	bool SendSignTypedDataResult(const FString& Status, const FString& Signature, const FString& R, const FString& S,
		const FString& V);
	bool SendGetConsentResultEVM(const FString& Status, const FString& TransactionChainScanUrl, const FString& TransactionHash,
		const FString& TransactionId);
	bool SendGetConsentResultSolana(const FString& Status, const FString& TransactionChainScanUrl, const FString& TransactionSignature,
		const FString& TransactionId);
	bool SendOpenStateChange(bool IsOpen);

private:
	bool bSimulating;
	elixir::overlay::message::EventBufferInterop* EventBufferGameSdk;
	elixir::overlay::message::EventBufferInterop* EventBufferOverlayUi;

	TArray<TSharedPtr<FString>> EventTypes;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> EventTypeComboBox;
	FString SelectedEventType;

	TSharedPtr<SHorizontalBox> SuccessHorizontalBox;
	TSharedPtr<SCheckBox> SuccessCheckBox;
	TSharedPtr<SHorizontalBox> SkuHorizontalBox;
	TSharedPtr<SEditableTextBox> SkuEditableTextBox;

	TSharedPtr<SHorizontalBox> GetWalletStatusHorizontalBox;
	TSharedPtr<SEditableTextBox> GetWalletStatusEditableTextBox;
	TSharedPtr<SHorizontalBox> GetWalletEthAddressHorizontalBox;
	TSharedPtr<SEditableTextBox> GetWalletEthAddressEditableTextBox;
	TSharedPtr<SHorizontalBox> GetWalletSolAddressHorizontalBox;
	TSharedPtr<SEditableTextBox> GetWalletSolAddressEditableTextBox;
	TSharedPtr<SHorizontalBox> GetWalletEosAddressHorizontalBox;
	TSharedPtr<SEditableTextBox> GetWalletEosAddressEditableTextBox;

	TSharedPtr<SHorizontalBox> SignTypedDataStatusHorizontalBox;
	TSharedPtr<SEditableTextBox> SignTypedDataStatusEditableTextBox;
	TSharedPtr<SHorizontalBox> SignTypedDataSignatureHorizontalBox;
	TSharedPtr<SEditableTextBox> SignTypedDataSignatureEditableTextBox;
	TSharedPtr<SHorizontalBox> SignTypedDataRHorizontalBox;
	TSharedPtr<SEditableTextBox> SignTypedDataREditableTextBox;
	TSharedPtr<SHorizontalBox> SignTypedDataSHorizontalBox;
	TSharedPtr<SEditableTextBox> SignTypedDataSEditableTextBox;
	TSharedPtr<SHorizontalBox> SignTypedDataVHorizontalBox;
	TSharedPtr<SEditableTextBox> SignTypedDataVEditableTextBox;

	TSharedPtr<SHorizontalBox> GetConsentEVMStatusHorizontalBox;
	TSharedPtr<SEditableTextBox> GetConsentEVMStatusEditableTextBox;
	TSharedPtr<SHorizontalBox> GetConsentEVMTransactionHashHorizontalBox;
	TSharedPtr<SEditableTextBox> GetConsentEVMTransactionHashEditableTextBox;
	TSharedPtr<SHorizontalBox> GetConsentEVMTransactionChainScanUrlHorizontalBox;
	TSharedPtr<SEditableTextBox> GetConsentEVMTransactionChainScanUrlEditableTextBox;
	TSharedPtr<SHorizontalBox> GetConsentEVMTransactionIdHorizontalBox;
	TSharedPtr<SEditableTextBox> GetConsentEVMTransactionIdEditableTextBox;

	TSharedPtr<SHorizontalBox> GetConsentSolanaStatusHorizontalBox;
	TSharedPtr<SEditableTextBox> GetConsentSolanaStatusEditableTextBox;
	TSharedPtr<SHorizontalBox> GetConsentSolanaTransactionSignatureHorizontalBox;
	TSharedPtr<SEditableTextBox> GetConsentSolanaTransactionSignatureEditableTextBox;
	TSharedPtr<SHorizontalBox> GetConsentSolanaTransactionChainScanUrlHorizontalBox;
	TSharedPtr<SEditableTextBox> GetConsentSolanaTransactionChainScanUrlEditableTextBox;
	TSharedPtr<SHorizontalBox> GetConsentSolanaTransactionIdHorizontalBox;
	TSharedPtr<SEditableTextBox> GetConsentSolanaTransactionIdEditableTextBox;


	TSharedPtr<SHorizontalBox> IsOpenHorizontalBox;
	TSharedPtr<SCheckBox> IsOpenCheckBox;

	TSharedPtr<SListView<TSharedPtr<FElixirEventItem>>> EventsListView;
	TArray<TSharedPtr<FElixirEventItem>> Events;
};


#undef LOCTEXT_NAMESPACE
