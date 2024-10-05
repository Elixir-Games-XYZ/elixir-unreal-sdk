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
	SLATE_BEGIN_ARGS(STableItemWidget)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView,
		TSharedPtr<FElixirEventItem> InItem)
	{
		ItemWeakPtr = InItem;
		SMultiColumnTableRow::Construct(FSuperRowType::FArguments(), InOwnerTableView);
	}

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override
	{
		if (const TSharedPtr<FElixirEventItem> Item = ItemWeakPtr.Pin())
		{
			if (ColumnName == "Direction")
			{
				return SNew(STextBlock).Text(FText::FromString(Item->Direction));
			}
			if (ColumnName == "Name")
			{
				return SNew(STextBlock).Text(FText::FromString(Item->Name));
			}
			if (ColumnName == "Payload")
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
	EventTypes.Add(MakeShareable(new FString("GetWalletResult")));
	EventTypes.Add(MakeShareable(new FString("SignTypedDataResult")));
	EventTypes.Add(MakeShareable(new FString("GetConsentResultEVM")));
	EventTypes.Add(MakeShareable(new FString("GetConsentResultSolana")));
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
			+ SHeaderRow::Column("Direction")
			.DefaultLabel(
				FText::FromString("Direction"))
			.FillWidth(0.2f)
			+ SHeaderRow::Column("Name")
			.DefaultLabel(
				FText::FromString("Event Name"))
			.FillWidth(0.4f)
			+ SHeaderRow::Column("Payload")
			.DefaultLabel(
				FText::FromString("Payload"))
			.FillWidth(0.4f)
		);

	EventTypeComboBox = SNew(SComboBox<TSharedPtr<FString>>)
		.OptionsSource(&EventTypes)
		.OnSelectionChanged_Lambda([this](TSharedPtr<FString> Value, ESelectInfo::Type SelectInfo)
		{
			SelectedEventType = *Value;
			// TODO: This is horrible, refactor it.
			if (SelectedEventType == "CheckoutResult")
			{
				SuccessHorizontalBox->SetVisibility(
					EVisibility::Visible);
				SkuHorizontalBox->SetVisibility(
					EVisibility::Visible);
				IsOpenHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetWalletStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletEthAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletSolAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletEosAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				SignTypedDataStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataSignatureHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataRHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataSHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataVHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetConsentEVMStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionHashHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetConsentSolanaStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionSignatureHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
			}
			else if (SelectedEventType == "OpenStateChange")
			{
				SuccessHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SkuHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				IsOpenHorizontalBox->SetVisibility(
					EVisibility::Visible);

				GetWalletStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletEthAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletSolAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletEosAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				SignTypedDataStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataSignatureHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataRHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataSHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataVHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetConsentEVMStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionHashHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetConsentSolanaStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionSignatureHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
			}
			else if (SelectedEventType == "GetWalletResult")
			{
				SuccessHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SkuHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				IsOpenHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetWalletStatusHorizontalBox->SetVisibility(
					EVisibility::Visible);
				GetWalletEthAddressHorizontalBox->SetVisibility(
					EVisibility::Visible);
				GetWalletSolAddressHorizontalBox->SetVisibility(
					EVisibility::Visible);
				GetWalletEosAddressHorizontalBox->SetVisibility(
					EVisibility::Visible);

				SignTypedDataStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataSignatureHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataRHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataSHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataVHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetConsentEVMStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionHashHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetConsentSolanaStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionSignatureHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
			}
			else if (SelectedEventType == "SignTypedDataResult")
			{
				SuccessHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SkuHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				IsOpenHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetWalletStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletEthAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletSolAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletEosAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				SignTypedDataStatusHorizontalBox->SetVisibility(
					EVisibility::Visible);
				SignTypedDataSignatureHorizontalBox->SetVisibility(
					EVisibility::Visible);
				SignTypedDataRHorizontalBox->SetVisibility(
					EVisibility::Visible);
				SignTypedDataSHorizontalBox->SetVisibility(
					EVisibility::Visible);
				SignTypedDataVHorizontalBox->SetVisibility(
					EVisibility::Visible);

				GetConsentEVMStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionHashHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetConsentSolanaStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionSignatureHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
			}
			else if (SelectedEventType == "GetConsentResultEVM")
			{
				SuccessHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SkuHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				IsOpenHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetWalletStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletEthAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletSolAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletEosAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				SignTypedDataStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataSignatureHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataRHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataSHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataVHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetConsentEVMStatusHorizontalBox->SetVisibility(
					EVisibility::Visible);
				GetConsentEVMTransactionHashHorizontalBox->SetVisibility(
					EVisibility::Visible);
				GetConsentEVMTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Visible);
				GetConsentEVMTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Visible);

				GetConsentSolanaStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionSignatureHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentSolanaTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
			}
			else if (SelectedEventType == "GetConsentResultSolana")
			{
				SuccessHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SkuHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				IsOpenHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetWalletStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletEthAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletSolAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetWalletEosAddressHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				SignTypedDataStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataSignatureHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataRHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataSHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				SignTypedDataVHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetConsentEVMStatusHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionHashHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Collapsed);
				GetConsentEVMTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Collapsed);

				GetConsentSolanaStatusHorizontalBox->SetVisibility(
					EVisibility::Visible);
				GetConsentSolanaTransactionSignatureHorizontalBox->SetVisibility(
					EVisibility::Visible);
				GetConsentSolanaTransactionChainScanUrlHorizontalBox->SetVisibility(
					EVisibility::Visible);
				GetConsentSolanaTransactionIdHorizontalBox->SetVisibility(
					EVisibility::Visible);
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
			SAssignNew(SkuEditableTextBox, SEditableTextBox)
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

	GetWalletStatusHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("Status"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetWalletStatusEditableTextBox, SEditableTextBox)
		];

	GetWalletEthAddressHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("EthAddress"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetWalletEthAddressEditableTextBox, SEditableTextBox)
		];

	GetWalletSolAddressHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("SolAddress"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetWalletSolAddressEditableTextBox, SEditableTextBox)
		];

	GetWalletEosAddressHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("EosAddress"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetWalletEosAddressEditableTextBox, SEditableTextBox)
		];

	SignTypedDataStatusHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("Status"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(SignTypedDataStatusEditableTextBox, SEditableTextBox)
		];

	SignTypedDataSignatureHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("Signature"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(SignTypedDataSignatureEditableTextBox, SEditableTextBox)
		];

	SignTypedDataRHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("R"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(SignTypedDataREditableTextBox, SEditableTextBox)
		];

	SignTypedDataSHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("S"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(SignTypedDataSEditableTextBox, SEditableTextBox)
		];

	SignTypedDataVHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("V"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(SignTypedDataVEditableTextBox, SEditableTextBox)
		];

	GetConsentEVMStatusHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("Status"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetConsentEVMStatusEditableTextBox, SEditableTextBox)
		];

	GetConsentEVMTransactionChainScanUrlHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("TransactionChainScanUrl"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetConsentEVMTransactionChainScanUrlEditableTextBox, SEditableTextBox)
		];

	GetConsentEVMTransactionHashHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("TransactionHash"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetConsentEVMTransactionHashEditableTextBox, SEditableTextBox)
		];

	GetConsentEVMTransactionIdHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("TransactionId"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetConsentEVMTransactionIdEditableTextBox, SEditableTextBox)
		];

	GetConsentSolanaStatusHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("Status"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetConsentSolanaStatusEditableTextBox, SEditableTextBox)
		];

	GetConsentSolanaTransactionChainScanUrlHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("TransactionChainScanUrl"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetConsentSolanaTransactionChainScanUrlEditableTextBox, SEditableTextBox)
		];

	GetConsentSolanaTransactionSignatureHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("TransactionSignature"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetConsentSolanaTransactionSignatureEditableTextBox, SEditableTextBox)
		];

	GetConsentSolanaTransactionIdHorizontalBox = SNew(SHorizontalBox)
		.Visibility(EVisibility::Collapsed)
		+ SHorizontalBox::Slot()
		.MaxWidth(100)
		[
			SNew(STextBlock).Text(FText::FromString("TransactionId"))
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SAssignNew(GetConsentSolanaTransactionIdEditableTextBox, SEditableTextBox)
		];
	const TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox)
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
			.Padding(6.0f, 3.0f, 0.0f, 3.0f)
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
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
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
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
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
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			SuccessHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			SkuHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			IsOpenHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetWalletStatusHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetWalletEthAddressHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetWalletSolAddressHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetWalletEosAddressHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			SignTypedDataStatusHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			SignTypedDataSignatureHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			SignTypedDataRHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			SignTypedDataSHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			SignTypedDataVHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetConsentEVMStatusHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetConsentEVMTransactionChainScanUrlHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetConsentEVMTransactionHashHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetConsentEVMTransactionIdHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetConsentSolanaStatusHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetConsentSolanaTransactionChainScanUrlHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetConsentSolanaTransactionSignatureHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 3.0f, 0.0f, 3.0f)
		[
			GetConsentSolanaTransactionIdHorizontalBox.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0, 10.0f, 0, 3.0f)
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
	{
		return;
	}

	const MessageInterop Msg = ListenToEventBuffer(EventBufferOverlayUi);
	if (Msg.type != MTEmpty)
	{
		UE_LOG(LogEditorElixir, Verbose, TEXT("Received an overlay message from game (\"type\": %d"), Msg.type);
	}

	if (Msg.type == MTCheckout)
	{
		const TSharedPtr<FElixirEventItem> Item = MakeShareable(new FElixirEventItem);
		Item->Direction = "Incoming";
		Item->Name = "Checkout";
		Item->Payload = FString::Printf(TEXT("\"Sku\": \"%hs\""), Msg.checkout.sku);
		Events.Add(Item);
		EventsListView->RebuildList();
	}

	if (Msg.type == MTMKGetConsent)
	{
		const TSharedPtr<FElixirEventItem> Item = MakeShareable(new FElixirEventItem);
		Item->Direction = "Incoming";
		Item->Name = "GetConsent";
		Item->Payload = FString::Printf(TEXT("\"ConsentToken\": \"%hs\""), Msg.metaKeepGetConsent.consentToken);
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
	{
		StartSimulating();
	}
	else
	{
		StopSimulating();
	}

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
	{
		return FReply::Handled();
	}

	if (SelectedEventType == "CheckoutResult")
	{
		SendCheckoutResult(SuccessCheckBox->IsChecked(), SkuEditableTextBox->GetText().ToString());
	}
	else if (SelectedEventType == "OpenStateChange")
	{
		SendOpenStateChange(IsOpenCheckBox->IsChecked());
	}
	else if (SelectedEventType == "GetWalletResult")
	{
		SendGetWalletResult(GetWalletStatusEditableTextBox->GetText().ToString(),
			GetWalletEthAddressEditableTextBox->GetText().ToString(),
			GetWalletSolAddressEditableTextBox->GetText().ToString(),
			GetWalletEosAddressEditableTextBox->GetText().ToString());
	}
	else if (SelectedEventType == "SignTypedDataResult")
	{
		SendSignTypedDataResult(SignTypedDataStatusEditableTextBox->GetText().ToString(),
			SignTypedDataSignatureEditableTextBox->GetText().ToString(),
			SignTypedDataREditableTextBox->GetText().ToString(),
			SignTypedDataSEditableTextBox->GetText().ToString(),
			SignTypedDataVEditableTextBox->GetText().ToString());
	}
	else if (SelectedEventType == "GetConsentResultEVM")
	{
		SendGetConsentResultEVM(GetConsentEVMStatusEditableTextBox->GetText().ToString(),
			GetConsentEVMTransactionChainScanUrlEditableTextBox->GetText().ToString(),
			GetConsentEVMTransactionHashEditableTextBox->GetText().ToString(),
			GetConsentEVMTransactionIdEditableTextBox->GetText().ToString());
	}
	else if (SelectedEventType == "GetConsentResultSolana")
	{
		SendGetConsentResultSolana(GetConsentSolanaStatusEditableTextBox->GetText().ToString(),
			GetConsentSolanaTransactionChainScanUrlEditableTextBox->GetText().ToString(),
			GetConsentSolanaTransactionSignatureEditableTextBox->GetText().ToString(),
			GetConsentSolanaTransactionIdEditableTextBox->GetText().ToString());
	}

	return FReply::Handled();
}

void SElixirEventSimulator::StartSimulating()
{
	if (bSimulating)
	{
		return;
	}

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

	const size_t BytesWritten = WriteToEventBufferCheckoutResult(EventBufferGameSdk, Result, TCHAR_TO_ANSI(*Sku));
	if (BytesWritten == 0)
	{
		return false;
	}

	const TSharedPtr<FElixirEventItem> Item = MakeShareable(new FElixirEventItem);
	Item->Direction = "Outgoing";
	Item->Name = "CheckoutResult";
	Item->Payload = FString::Printf(
		TEXT("\"Result\": %s, \"Sku\": \"%s\""), *UKismetStringLibrary::Conv_BoolToString(Result), *Sku);
	Events.Add(Item);
	EventsListView->RebuildList();

	return true;
}

bool SElixirEventSimulator::SendGetWalletResult(const FString& Status, const FString& EthAddress,
	const FString& SolAddress,
	const FString& EosAddress)
{
	if (Status.Len() == 0)
	{
		UE_LOG(LogEditorElixir, Error, TEXT("Invalid empty Status"));
		return false;
	}

	const size_t BytesWritten = WriteToEventBufferGetWalletResult(EventBufferGameSdk, TCHAR_TO_ANSI(*Status),
		TCHAR_TO_ANSI(*EthAddress),TCHAR_TO_ANSI(*SolAddress),
		TCHAR_TO_ANSI(*EosAddress));
	if (BytesWritten == 0)
	{
		return false;
	}

	const TSharedPtr<FElixirEventItem> Item = MakeShareable(new FElixirEventItem);
	Item->Direction = "Outgoing";
	Item->Name = "GetWalletResult";
	Item->Payload = FString::Printf(
		TEXT("\"Status\": %s, \"EthAddress\": \"%s\", \"SolAddress\": \"%s\", \"EosAddress\": \"%s\""), *Status,
		*EthAddress, *SolAddress, *EosAddress);
	Events.Add(Item);
	EventsListView->RebuildList();

	return true;
}

bool SElixirEventSimulator::SendSignTypedDataResult(const FString& Status, const FString& Signature, const FString& R,
	const FString& S, const FString& V)
{
	if (Status.Len() == 0)
	{
		UE_LOG(LogEditorElixir, Error, TEXT("Invalid empty Status"));
		return false;
	}

	const size_t BytesWritten = WriteToEventBufferSignTypedDataResult(EventBufferGameSdk, TCHAR_TO_ANSI(*Status),
		TCHAR_TO_ANSI(*Signature),TCHAR_TO_ANSI(*R),
		TCHAR_TO_ANSI(*S), TCHAR_TO_ANSI(*V));
	if (BytesWritten == 0)
	{
		return false;
	}

	const TSharedPtr<FElixirEventItem> Item = MakeShareable(new FElixirEventItem);
	Item->Direction = "Outgoing";
	Item->Name = "SignTypedDataResult";
	Item->Payload = FString::Printf(
		TEXT("\"Status\": %s, \"Signature\": \"%s\", \"R\": \"%s\", \"S\": \"%s\", \"V\": \"%s\""), *Status,
		*Signature, *R, *S, *V);
	Events.Add(Item);
	EventsListView->RebuildList();

	return true;
}

bool SElixirEventSimulator::SendGetConsentResultEVM(const FString& Status, const FString& TransactionChainScanUrl,
	const FString& TransactionHash,
	const FString& TransactionId)
{
	if (Status.Len() == 0)
	{
		UE_LOG(LogEditorElixir, Error, TEXT("Invalid empty Status"));
		return false;
	}

	const size_t BytesWritten = WriteToEventBufferGetConsentResult(EventBufferGameSdk, TCHAR_TO_ANSI(*Status),
		MMKGetConsentResultResponseInterop{
			MKResponseEVM,
			TCHAR_TO_ANSI(*TransactionChainScanUrl),TCHAR_TO_ANSI(*TransactionHash),
			TCHAR_TO_ANSI(*TransactionId)
		});

	if (BytesWritten == 0)
	{
		return false;
	}

	const TSharedPtr<FElixirEventItem> Item = MakeShareable(new FElixirEventItem);
	Item->Direction = "Outgoing";
	Item->Name = "SendGetConsentResultEVM";
	Item->Payload = FString::Printf(
		TEXT("\"Status\": %s, \"TransactionChainScanUrl\": \"%s\", \"TransactionHash\": \"%s\", \"TransactionId\": \"%s\""), *Status,
		*TransactionChainScanUrl, *TransactionHash, *TransactionId);
	Events.Add(Item);
	EventsListView->RebuildList();

	return true;
}

bool SElixirEventSimulator::SendGetConsentResultSolana(const FString& Status, const FString& TransactionChainScanUrl,
	const FString& TransactionSignature,
	const FString& TransactionId)
{
	if (Status.Len() == 0)
	{
		UE_LOG(LogEditorElixir, Error, TEXT("Invalid empty Status"));
		return false;
	}

	const size_t BytesWritten = WriteToEventBufferGetConsentResult(EventBufferGameSdk, TCHAR_TO_ANSI(*Status),
		MMKGetConsentResultResponseInterop{
			MKResponseSolana,
			TCHAR_TO_ANSI(*TransactionChainScanUrl),TCHAR_TO_ANSI(*TransactionSignature),
			TCHAR_TO_ANSI(*TransactionId)
		});

	if (BytesWritten == 0)
	{
		return false;
	}

	const TSharedPtr<FElixirEventItem> Item = MakeShareable(new FElixirEventItem);
	Item->Direction = "Outgoing";
	Item->Name = "SendGetConsentResultEVM";
	Item->Payload = FString::Printf(
		TEXT("\"Status\": %s, \"TransactionChainScanUrl\": \"%s\", \"TransactionSignature\": \"%s\", \"TransactionId\": \"%s\""), *Status,
		*TransactionChainScanUrl, *TransactionSignature, *TransactionId);
	Events.Add(Item);
	EventsListView->RebuildList();

	return true;
}

bool SElixirEventSimulator::SendOpenStateChange(bool IsOpen)
{
	const size_t BytesWritten = WriteToEventBufferOpenStateChange(EventBufferGameSdk, IsOpen);
	if (BytesWritten == 0)
	{
		return false;
	}


	const TSharedPtr<FElixirEventItem> Item = MakeShareable(new FElixirEventItem);
	Item->Direction = "Outgoing";
	Item->Name = "OpenStateChange";
	Item->Payload = FString::Printf(TEXT("\"IsOpen\": %s"), *UKismetStringLibrary::Conv_BoolToString(IsOpen));
	Events.Add(Item);
	EventsListView->RebuildList();

	return true;
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION


#undef LOCTEXT_NAMESPACE
