#include "ElixirEditor.h"
#include "SElixirEventSimulator.h"
#include "ElixirEventSimulatorStyle.h"

#include "Modules/ModuleManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"
#include "LevelEditor.h"

DEFINE_LOG_CATEGORY(LogEditorElixir);

#define LOCTEXT_NAMESPACE "FElixirEditorModule"

void FElixirEditorModule::StartupModule()
{
	if (IsRunningCommandlet())
	{
		return;
	}

	HElixirEventSimulatorWindow = nullptr;

	FElixirEventSimulatorStyle::Initialize();

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ELIXIR_API_TAB_OVERLAY_SIMULATOR,
	                                                  FOnSpawnTab::CreateRaw(
		                                                  this, &FElixirEditorModule::MakeElixirEventSimulatorTab))
	                        .SetDisplayName(NSLOCTEXT("ElixirEditorModule", "TabTitle", "Elixir Event Simulator"))
	                        .SetTooltipText(NSLOCTEXT("ElixirEditorModule", "TooltipText",
	                                                  "Open the elixir overlay event simulator tool."))
	                        .SetGroup(WorkspaceMenu::GetMenuStructure().GetDeveloperToolsMiscCategory())
	                        .SetIcon(FSlateIcon(FElixirEventSimulatorStyle::Get()->GetStyleSetName(),
	                                            "ElixirEventSimulator.TabIcon"));

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuBarExtension(
		"Help",
		EExtensionHook::After,
		nullptr,
		FMenuBarExtensionDelegate::CreateRaw(this, &FElixirEditorModule::AddMenuEntry)
	);
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FElixirEditorModule::ShutdownModule()
{
	FElixirEventSimulatorStyle::Shutdown();

	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner("ElixirEventSimulator");
	}
}

TSharedRef<SWidget> FElixirEditorModule::CreateElixirEventSimulatorWidget()
{
	SAssignNew(HElixirEventSimulatorWindow, SElixirEventSimulator);
	return HElixirEventSimulatorWindow->AsShared();
}

void FElixirEditorModule::OnTabClosed(TSharedRef<SDockTab> TabBeingClosed)
{
	/*	if (HPixelInspectorWindow.IsValid())
		{
			HPixelInspectorWindow->OnWindowClosed();
		}
		*/
}

void FElixirEditorModule::AddMenuEntry(FMenuBarBuilder& MenuBarBuilder)
{
	MenuBarBuilder.AddPullDownMenu(
		FText::FromString("Elixir"),
		FText::FromString("Elixir SDK"),
		FNewMenuDelegate::CreateRaw(this, &FElixirEditorModule::FillSubmenu),
		"Elixir"
	);
}


void FElixirEditorModule::FillSubmenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString("Overlay Simulator"),
		FText::FromString("Simulate communication with the overlay"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FElixirEditorModule::MenuCallbackOverlaySimulator))
	);

	MenuBuilder.AddMenuEntry(
		FText::FromString("Documentation"),
		FText::FromString("Go to the online Elixir SDK documentation"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FElixirEditorModule::MenuCallbackDocumentation))
	);
}

void FElixirEditorModule::MenuCallbackOverlaySimulator()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FTabId(ELIXIR_API_TAB_OVERLAY_SIMULATOR));
}

void FElixirEditorModule::MenuCallbackDocumentation()
{
	FPlatformProcess::LaunchURL(TEXT("https://docs.elixir.app/sdk/unreal-engine"), nullptr, nullptr);
}

TSharedRef<SDockTab> FElixirEditorModule::MakeElixirEventSimulatorTab(const FSpawnTabArgs&)
{
	TSharedRef<SDockTab> PixelInspectorTab = SNew(SDockTab)
		.Icon(FElixirEventSimulatorStyle::Get()->GetBrush("ElixirEventSimulator.TabIcon"))
		.TabRole(NomadTab);

	PixelInspectorTab->SetContent(CreateElixirEventSimulatorWidget());
	PixelInspectorTab->SetOnTabClosed(
		SDockTab::FOnTabClosedCallback::CreateRaw(this, &FElixirEditorModule::OnTabClosed));

	return PixelInspectorTab;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FElixirEditorModule, ElixirEditor)
