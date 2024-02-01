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
	virtual ~SElixirEventSimulator();

	/** Release all the resources */
	void ReleaseResources();

	SLATE_BEGIN_ARGS(SElixirEventSimulator){}
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

	TSharedPtr<SHorizontalBox> IsOpenHorizontalBox;
	TSharedPtr<SCheckBox> IsOpenCheckBox;	
	
	TSharedPtr<SListView<TSharedPtr<FElixirEventItem>>> EventsListView;
	TArray<TSharedPtr<FElixirEventItem>> Events;
};


#undef LOCTEXT_NAMESPACE
