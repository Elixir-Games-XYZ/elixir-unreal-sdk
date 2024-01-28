#include "ElixirEditor.h"
#include "SElixirEventSimulator.h"
#include "ElixirEventSimulatorStyle.h"

#include "Modules/ModuleManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"

DEFINE_LOG_CATEGORY(LogEditorElixir);

#define LOCTEXT_NAMESPACE "FElixirEditorModule"

void FElixirEditorModule::StartupModule()
{
	HElixirEventSimulatorWindow = nullptr;

	FElixirEventSimulatorStyle::Initialize();

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner("ElixirEventSimulator", FOnSpawnTab::CreateRaw(this, &FElixirEditorModule::MakeElixirEventSimulatorTab))
		.SetDisplayName(NSLOCTEXT("ElixirEditorModule", "TabTitle", "Elixir Event Simulator"))
		.SetTooltipText(NSLOCTEXT("ElixirEditorModule", "TooltipText", "Open the elixir overlay event simulator tool."))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetDeveloperToolsMiscCategory())
		.SetIcon(FSlateIcon(FElixirEventSimulatorStyle::Get()->GetStyleSetName(), "ElixirEventSimulator.TabIcon"));	
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

TSharedRef<SDockTab> FElixirEditorModule::MakeElixirEventSimulatorTab(const FSpawnTabArgs&)
{
	TSharedRef<SDockTab> PixelInspectorTab = SNew(SDockTab)
		.Icon(FElixirEventSimulatorStyle::Get()->GetBrush("ElixirEventSimulator.TabIcon"))
		.TabRole(ETabRole::NomadTab);
	
	PixelInspectorTab->SetContent(CreateElixirEventSimulatorWidget());
	PixelInspectorTab->SetOnTabClosed( SDockTab::FOnTabClosedCallback::CreateRaw(this, &FElixirEditorModule::OnTabClosed));
	
	return PixelInspectorTab;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FElixirEditorModule, ElixirEditor)