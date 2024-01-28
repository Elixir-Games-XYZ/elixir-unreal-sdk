#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class SElixirEventSimulator;

DECLARE_LOG_CATEGORY_EXTERN(LogEditorElixir, Log, All);

class FElixirEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Creates the HLOD Outliner widget */
	virtual TSharedRef<SWidget> CreateElixirEventSimulatorWidget();

private:
	
	void OnTabClosed(TSharedRef<SDockTab> TabBeingClosed);

private:
	TSharedRef<SDockTab> MakeElixirEventSimulatorTab(const FSpawnTabArgs&);

	TSharedPtr<SElixirEventSimulator> HElixirEventSimulatorWindow;
	TMap<uint32, bool> OriginalViewportStates;
};