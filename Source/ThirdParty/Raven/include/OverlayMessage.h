#ifndef ELIXIR_OVERLAY_MESSAGE_H
#define ELIXIR_OVERLAY_MESSAGE_H

#include "raven_export.h"

namespace elixir::overlay::message
{

#pragma pack(push, 1)

extern "C" enum MessageType : int32_t
{
    MTEmpty = 0,
    MTToken = 1,
    MTOpenStateChange = 2,
    MTCheckout = 3,
    MTCheckoutResult = 4,
    MTFeatureFlags = 5,
    MTLanguage = 6,
    MTSetVisibility = 7
};

extern "C" struct RAVEN_EXPORT MTokenInterop
{
    const char* token;
};

extern "C" struct RAVEN_EXPORT MOpenStateChangeInterop
{
    bool isOpen;
};

extern "C" struct RAVEN_EXPORT MCheckoutInterop
{
    const char* sku;
};

extern "C" struct RAVEN_EXPORT MCheckoutResultInterop
{
    bool        success;
    const char* sku;
};

extern "C" struct RAVEN_EXPORT MFeatureFlagsInterop
{
    const char* featureFlags;
};

extern "C" struct RAVEN_EXPORT MLanguageInterop
{
    const char* language;
};

extern "C" struct RAVEN_EXPORT MSetVisibilityInterop
{
    bool newVisibility;
};

extern "C" struct RAVEN_EXPORT MEmptyInterop
{
};

extern "C" struct RAVEN_EXPORT MessageInterop
{
    MessageType type;
    union
    {
        MTokenInterop           token;
        MOpenStateChangeInterop openStateChange;
        MCheckoutInterop        checkout;
        MCheckoutResultInterop  checkoutResult;
        MFeatureFlagsInterop    featureFlags;
        MLanguageInterop        language;
        MSetVisibilityInterop   setVisibility;
        MEmptyInterop           empty;
    };
};
#pragma pack(pop)

class RAVEN_EXPORT EventBufferInterop
{
public:
    explicit EventBufferInterop(const char* bufferName);
    ~EventBufferInterop();
    size_t write(const MessageInterop& message);

    MessageInterop listenSync();
    const char*    getError();
    void           clearError();
    void           clear();

private:
    class EventBuffer* eventBufferImpl;
};

extern "C" RAVEN_EXPORT EventBufferInterop* CreateEventBuffer(const char* bufferName);
extern "C" RAVEN_EXPORT void                DestroyEventBuffer(EventBufferInterop* eventBuffer);
extern "C" RAVEN_EXPORT MessageInterop      ListenToEventBuffer(EventBufferInterop* eventBuffer);
extern "C" RAVEN_EXPORT const char*         GetEventBufferError(EventBufferInterop* eventBuffer);
extern "C" RAVEN_EXPORT void                ClearEventBufferError(EventBufferInterop* eventBuffer);
extern "C" RAVEN_EXPORT void                ClearEventBuffer(EventBufferInterop* eventBuffer);
extern "C" RAVEN_EXPORT size_t              WriteToEventBuffer(EventBufferInterop* eventBuffer, MessageInterop& message);
extern "C" RAVEN_EXPORT size_t              WriteToEventBufferCheckout(EventBufferInterop* eventBuffer, const char* sku);
extern "C" RAVEN_EXPORT size_t              WriteToEventBufferSetVisibility(EventBufferInterop* eventBuffer, bool newVisibility);
extern "C" RAVEN_EXPORT size_t              WriteToEventBufferCheckoutResult(EventBufferInterop* eventBuffer, bool result, const char* sku);
extern "C" RAVEN_EXPORT size_t              WriteToEventBufferOpenStateChange(EventBufferInterop* eventBuffer, bool openState);
extern "C" RAVEN_EXPORT const char*         GetEventBufferOverlayUi();
extern "C" RAVEN_EXPORT const char*         GetEventBufferGameSdk();

} // namespace elixir::overlay::message

#endif
