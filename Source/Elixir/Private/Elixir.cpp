#include "Elixir.h"

#define LOCTEXT_NAMESPACE "FElixirModule"

DEFINE_LOG_CATEGORY(LogElixir);

void FElixirModule::StartupModule()
{
}

void FElixirModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FElixirModule, Elixir)
