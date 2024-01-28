#include "SElixirEventSimulator.h"
#include "ElixirEditor.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Styling/CoreStyle.h"
#include "SlateOptMacros.h"
#include "Framework/Application/SlateApplication.h"
#include "EngineGlobals.h"
#include "IDetailsView.h"
#include "Kismet/KismetStringLibrary.h"

using namespace elixir::overlay::message;


#define LOCTEXT_NAMESPACE "ElixirEventSimulator"


class STableItemWidget : public SMultiColumnTableRow<TSharedPtr<FElixirEventItem>>
{
public:
	SLATE_BEGIN_ARGS(STableItemWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedPtr<FElixirEventItem> InItem)
	{
		ItemWeakPtr = InItem;
		SMultiColumnTableRow::Construct(FSuperRowType::FArguments(), InOwnerTableView);
	}
	
	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override
	{
		if (TSharedPtr<FElixirEventItem> Item = ItemWeakPtr.Pin())
		{
			if (ColumnName == "Direction")
			{
				return SNew(STextBlock).Text(FText::FromString(Item->Direction));
			}
			else if (ColumnName == "Name")
			{
				return SNew(STextBlock).Text(FText::FromString(Item->Name));
			}
			else if (ColumnName == "Payload")
			{
				return SNew(STextBlock).Text(FText::FromString(Item->Payload));
			}			
		}

		return SNullWidget::NullWidget;
	}

private:
	TWeakPtr<FElixirEventItem> ItemWeakPtr;	
};

SElixirEventSimulator::SElixirEventSimulator()
{
	bSimulating = false;
	EventBufferGameSdk = nullptr;
	EventBufferOverlayUi = nullptr;
}

SElixirEventSimulator::~SElixirEventSimulator()
{
	ReleaseResources();
}

void SElixirEventSimulator::ReleaseResources()
{
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SElixirEventSimulator::Construct(const FArguments& InArgs)
{
	EventTypes.Add(MakeShareable(new FString("CheckoutResult")));
	EventTypes.Add(MakeShareable(new FString("OpenStateChange")));
	SelectedEventType = "CheckoutResult";
	
	EventsListView = SNew(SListView<TSharedPtr<FElixirEventItem>>)
		.ItemHeight(24.0f)
		.ListItemsSource(&Events)
		.OnGenerateRow_Lambda([](TSharedPtr<FElixirEventItem> Item, const TSharedRef<STableViewBase>& OwnerTable)
		{
			return SNew(STableItemWidget, OwnerTable, Item);
		})
		.HeaderRow
		(
			SNew(SHeaderRow)
			+ SHeaderRow::Column("Direction").DefaultLabel(FText::FromString("Direction"))
			.FillWidth(0.2f)
			+ SHeaderRow::Column("Name").DefaultLabel(FText::FromString("Event Name"))
			.FillWidth(0.4f)
			+ SHeaderRow::Column("Payload").DefaultLabel(FText::FromString("Payload"))
			.FillWidth(0.4f)
		);

	EventTypeComboBox = SNew(SComboBox<TSharedPtr<FString>>)
		.OptionsSource(&EventTypes)
		.OnSelectionChanged_Lambda([this](TSharedPtr<FString> Value, ESelectInfo::Type SelectInfo)
		{
			SelectedEventType = *Value;
			if (SelectedEventType == "CheckoutResult")
			{
				SuccessHorizontalBox->SetVisibility(EVisibility::Visible);
				SkuHorizontalBox->SetVisibility(EVisibility::Visible);
				IsOpenHorizontalBox->SetVisibility(EVisibility::Collapsed);
			}
			else if (SelectedEventType == "OpenStateChange")
			{
				SuccessHorizontalBox->SetVisibility(EVisibility::Collapsed);
				SkuHorizontalBox->SetVisibility(EVisibility::Collapsed);
				IsOpenHorizontalBox->SetVisibility(EVisibility::Visible);
			}
		})
		.OnGenerateWidget_Lambda([](TSharedPtr<FString> Value)
		{
			return SNew(STextBlock).Text(FText::FromString(*Value));
		})
		[
			SNew(STextBlock).Text_Lambda([this]
			{
				return FText::FromString(SelectedEventType);
			})
		];

	
	SuccessHorizontalBox = SNew(SHorizontalBox)
	+ SHorizontalBox::Slot()
	.MaxWidth(100)
	[
		SNew(STextBlock).Text(FText::FromString("Success"))
	]
	+ SHorizontalBox::Slot()
	.FillWidth(1.0)
	[
		SAssignNew(SuccessCheckBox, SCheckBox)
	];
	
	SkuHorizontalBox = SNew(SHorizontalBox)
	+ SHorizontalBox::Slot()
	.MaxWidth(100)
	[
		SNew(STextBlock).Text(FText::FromString("Sku"))
	]
	+ SHorizontalBox::Slot()
	.FillWidth(1.0)
	[
		SAssignNew(SkuEditableText, SEditableText)
	];	
	
	IsOpenHorizontalBox = SNew(SHorizontalBox)
	.Visibility(EVisibility::Collapsed)
	+ SHorizontalBox::Slot()
	.MaxWidth(100)
	[
		SNew(STextBlock).Text(FText::FromString("IsOpen"))
	]
	+ SHorizontalBox::Slot()
	.FillWidth(1.0)
	[
		SAssignNew(IsOpenCheckBox, SCheckBox)
	];	
	
	TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox)
	+ SVerticalBox::Slot()
	.AutoHeight()
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		.AutoWidth()
		[
			SNew(SButton)
		   .HAlign(HAlign_Center)
		   .OnClicked(this, &SElixirEventSimulator::OnStartStop)
		   .Content()
		   [
			   SNew(STextBlock)
			   .MinDesiredWidth(100)
			   .Text(this, &SElixirEventSimulator::GetStartStopButtonText)
		   ]
		]
		+ SHorizontalBox::Slot()
		.Padding(10.0f, 3.0f, 0.0f, 3.0f)
		.AutoWidth()
		[
			SNew(SButton)
			.HAlign(HAlign_Center)
			.OnClicked(this, &SElixirEventSimulator::OnClear)
			.Content()
			[
				SNew(STextBlock)
				.MinDesiredWidth(100)
				.Text(FText::FromString("Clear"))
            ]
		]
	]
	+ SVerticalBox::Slot()
	.FillHeight(1.0f)
	[
		SNew(SBorder)
		.Padding(0)
		.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
		[
			EventsListView.ToSharedRef()
		]		
	]
	+ SVerticalBox::Slot()
	.AutoHeight()
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("Event Type"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			EventTypeComboBox.ToSharedRef()
		]
	]
	+ SVerticalBox::Slot()
	.AutoHeight()
	[
		SuccessHorizontalBox.ToSharedRef()
	]
	+ SVerticalBox::Slot()
	.AutoHeight()
	[
		SkuHorizontalBox.ToSharedRef()
	]	
	+ SVerticalBox::Slot()
	.AutoHeight()
	[
		IsOpenHorizontalBox.ToSharedRef()
	]
	+ SVerticalBox::Slot()
	.AutoHeight()
	.Padding(0,10.0f,0,0)
	[
		SNew(SButton)
		.HAlign(HAlign_Center)
		.IsEnabled(this, &SElixirEventSimulator::IsSimulating)
		.OnClicked(this, &SElixirEventSimulator::OnSend)
		.Content()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("ElixirEventSimulator_Send", "Send"))
		]
	];
	
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				VerticalBox.ToSharedRef()
			]
		]
	];
	
}

void SElixirEventSimulator::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	if (!bSimulating)
		return;
	
	MessageInterop Msg = ListenToEventBuffer(EventBufferOverlayUi);
	if (Msg.type != MTEmpty)
	{
		UE_LOG(LogEditorElixir, Verbose, TEXT("Received an overlay message from game (\"type\": %d"), Msg.type);
	}

	if (Msg.type == MTCheckout)
	{
		TSharedPtr<FElixirEventItem> Item = MakeShareable(new FElixirEventItem);
		Item->Direction = "Incoming";
		Item->Name = "Checkout";
		Item->Payload = FString::Printf(TEXT("\"Sku\": \"%hs\""), Msg.checkout.sku); 
		Events.Add(Item);
		EventsListView->RebuildList();
	}
}

FText SElixirEventSimulator::GetStartStopButtonText() const
{
	return bSimulating ? FText::FromString("Stop") : FText::FromString("Start");
}

bool SElixirEventSimulator::IsSimulating() const
{
	return bSimulating;
}

FReply SElixirEventSimulator::OnStartStop()
{
	if (!bSimulating)
		StartSimulating();
	else
		StopSimulating();
	
	return FReply::Handled();
}

FReply SElixirEventSimulator::OnClear()
{
	Events.Reset();
	EventsListView->RebuildList();
	
	return FReply::Handled();
}

FReply SElixirEventSimulator::OnSend()
{
	if (!bSimulating)
		return FReply::Handled();
	
	if (SelectedEventType == "CheckoutResult")
	{
		SendCheckoutResult(SuccessCheckBox->IsChecked(), SkuEditableText->GetText().ToString());
	}
	else if (SelectedEventType == "OpenStateChange")
	{
		SendOpenStateChange(IsOpenCheckBox->IsChecked());
	}	
	
	return FReply::Handled();
}

void SElixirEventSimulator::StartSimulating()
{
	if (bSimulating)
		return;
	
	EventBufferOverlayUi = CreateEventBuffer(GetEventBufferOverlayUi());
	ClearEventBuffer(EventBufferOverlayUi);

	const char* Error = GetEventBufferError(EventBufferOverlayUi);
	if (Error && Error[0] != 0)
	{
		ClearEventBufferError(EventBufferOverlayUi);
		UE_LOG(LogEditorElixir, Error, TEXT("Failed to creaete an OverlayUi event buffer (error = '%hs')"), Error);
		return;
	}

	EventBufferGameSdk = CreateEventBuffer(GetEventBufferGameSdk());
	ClearEventBuffer(EventBufferGameSdk);

	const char* Error2 = GetEventBufferError(EventBufferGameSdk);
	if (Error2 && Error2[0] != 0)
	{
		ClearEventBufferError(EventBufferGameSdk);
		UE_LOG(LogEditorElixir, Error, TEXT("Failed to creaete a GameSdk event buffer (error = '%hs')"), Error2);
		return;
	}	
	
	bSimulating = true;
}

void SElixirEventSimulator::StopSimulating()
{
	if (bSimulating)
	{
		bSimulating = false;
		DestroyEventBuffer(EventBufferOverlayUi);
		DestroyEventBuffer(EventBufferGameSdk);
	}
}

bool SElixirEventSimulator::SendCheckoutResult(bool Result, const FString& Sku)
{
	if (Sku.Len() == 0)
	{
		UE_LOG(LogEditorElixir, Error, TEXT("Invalid empty Sku"));
		return false;
	}

	const char* SkuChar = TCHAR_TO_ANSI(*Sku);
	size_t BytesWritten = WriteToEventBufferCheckoutResult(EventBufferGameSdk, Result, SkuChar);
	if (BytesWritten == 0)
		return false;

	TSharedPtr<FElixirEventItem> Item = MakeShareable(new FElixirEventItem);
	Item->Direction = "Outgoing";
	Item->Name = "CheckoutResult";
	Item->Payload = FString::Printf(TEXT("\"Result\": %s, \"Sku\": \"%s\""), *UKismetStringLibrary::Conv_BoolToString(Result), *Sku); 
	Events.Add(Item);
	EventsListView->RebuildList();

	return true;	
}

bool SElixirEventSimulator::SendOpenStateChange(bool IsOpen)
{
	size_t BytesWritten = WriteToEventBufferOpenStateChange(EventBufferGameSdk, IsOpen);
	if (BytesWritten == 0)
		return false;
	
	
	TSharedPtr<FElixirEventItem> Item = MakeShareable(new FElixirEventItem);
	Item->Direction = "Outgoing";
	Item->Name = "OpenStateChange";
	Item->Payload = FString::Printf(TEXT("\"IsOpen\": %s"), *UKismetStringLibrary::Conv_BoolToString(IsOpen)); 
	Events.Add(Item);
	EventsListView->RebuildList();

	return true;
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION


#undef LOCTEXT_NAMESPACE
