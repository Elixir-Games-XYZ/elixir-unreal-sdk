#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class SElixirEventSimulator;

DECLARE_LOG_CATEGORY_EXTERN(LogEditorElixir, Log, All);

#define ELIXIR_API_TAB_OVERLAY_SIMULATOR "ElixirEventSimulator"

class FElixirEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Creates the HLOD Outliner widget */
	virtual TSharedRef<SWidget> CreateElixirEventSimulatorWidget();

private:
	void OnTabClosed(TSharedRef<SDockTab> TabBeingClosed);
	void AddMenuEntry(FMenuBarBuilder& MenuBuilder);
	void FillSubmenu(FMenuBuilder& MenuBuilder);
	void MenuCallbackOverlaySimulator();
	void MenuCallbackDocumentation();

private:
	TSharedRef<SDockTab> MakeElixirEventSimulatorTab(const FSpawnTabArgs&);

	TSharedPtr<SElixirEventSimulator> HElixirEventSimulatorWindow;
	TMap<uint32, bool> OriginalViewportStates;
};
