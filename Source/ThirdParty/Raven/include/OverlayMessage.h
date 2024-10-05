#ifndef ELIXIR_OVERLAY_MESSAGE_H
#define ELIXIR_OVERLAY_MESSAGE_H

#include "raven_export.h"

namespace elixir::overlay::message
{

#pragma pack(push, 1)

extern "C" enum MessageType : int
{
    MTEmpty = 0,
    MTToken = 1,
    MTOpenStateChange = 2,
    MTCheckout = 3,
    MTCheckoutResult = 4,
    MTFeatureFlags = 5,
    MTLanguage = 6,
    MTSetVisibility = 7,
    MTMKSignTransaction = 50,
    MTMKSignTransactionResult = 51,
    MTMKGetWallet = 52,
    MTMKGetWalletResult = 53,
    MTMKSignMessage = 54,
    MTMKSignMessageResult = 55,
    MTMKSignTypedData = 56,
    MTMKSignTypedDataResult = 57,
    MTMKGetConsent = 58,
    MTMKGetConsentResult = 59,

    // Warning: Message types over 128 will be glitchy thanks to how msgpack converts integers. See TODO in ShmBuffer.cpp
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

extern "C" struct RAVEN_EXPORT MMKSignTransactionInterop
{
    const char* transactionObjectJsonString;
    const char* reason;
};

extern "C" struct RAVEN_EXPORT MMKGetConsentInterop
{
    const char* consentToken;
};

extern "C" enum MMKResponseType : int
{
    MKResponseNone = 0,
    MKResponseEVM = 1,
    MKResponseSolana = 2,
    MKResponseEOS = 3
};

extern "C" struct RAVEN_EXPORT MMKSignTransactionResultResponseEVMInterop
{
    const char* signedRawTransaction;
    const char* transactionHash;
    const char* signature;
    const char* r;
    const char* s;
    const char* v;
};

extern "C" struct RAVEN_EXPORT MMKSignTransactionResultResponseSolanaInterop
{
    const char* signature;
};

extern "C" struct RAVEN_EXPORT MMKSignTransactionResultResponseEOSInterop
{
    const char* signature;
};

extern "C" struct RAVEN_EXPORT MMKSignTransactionResultResponseInterop
{
    MMKResponseType type;
    union
    {
        MMKSignTransactionResultResponseEVMInterop    responseEVM;
        MMKSignTransactionResultResponseSolanaInterop responseSolana;
        MMKSignTransactionResultResponseEOSInterop    responseEOS;
    };
};

extern "C" struct RAVEN_EXPORT MMKSignTransactionResultInterop
{
    const char*                             status;
    MMKSignTransactionResultResponseInterop response;
};

extern "C" struct RAVEN_EXPORT MMKGetConsentResultResponseEVMInterop
{
    const char* transactionChainScanUrl;
    const char* transactionHash;
    const char* transactionId;
};

extern "C" struct RAVEN_EXPORT MMKGetConsentResultResponseSolanaInterop
{
    const char* transactionId;
    const char* transactionSignature;
    const char* transactionChainScanUrl;
};

extern "C" struct RAVEN_EXPORT MMKGetConsentResultResponseInterop
{
    MMKResponseType type;
    union
    {
        MMKGetConsentResultResponseEVMInterop    responseEVM;
        MMKGetConsentResultResponseSolanaInterop responseSolana;
    };
};

extern "C" struct RAVEN_EXPORT MMKGetConsentResultInterop
{
    const char*                        status;
    MMKGetConsentResultResponseInterop response;
};

extern "C" struct RAVEN_EXPORT MMKSignMessageInterop
{
    const char* message;
    const char* reason;
};

extern "C" struct RAVEN_EXPORT MMKSignMessageResultResponseEVMInterop
{
    const char* signature;
    const char* r;
    const char* s;
    const char* v;
};

extern "C" struct RAVEN_EXPORT MMKSignMessageResultResponseSolanaInterop
{
    const char* signature;
};

extern "C" struct RAVEN_EXPORT MMKSignMessageResultResponseEOSInterop
{
    const char* signature;
};

extern "C" struct RAVEN_EXPORT MMKSignMessageResultResponseInterop
{
    MMKResponseType type;
    union
    {
        MMKSignMessageResultResponseEVMInterop    responseEVM;
        MMKSignMessageResultResponseSolanaInterop responseSolana;
        MMKSignMessageResultResponseEOSInterop    responseEOS;
    };
};

extern "C" struct RAVEN_EXPORT MMKSignMessageResultInterop
{
    const char*                         status;
    MMKSignMessageResultResponseInterop response;
};

extern "C" struct RAVEN_EXPORT MMKSignTypedDataInterop
{
    const char* message;
    const char* reason;
};

extern "C" struct RAVEN_EXPORT MMKSignTypedDataResultInterop
{
    const char* status;
    const char* signature;
    const char* r;
    const char* s;
    const char* v;
};

// The following monstrosity disables the pesky 'extern-c-compat' warning that Unreal elevates to error
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wextern-c-compat"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wextern-c-compat"
#endif
extern "C" struct RAVEN_EXPORT MMKGetWalletInterop
{
};
#ifdef __clang__
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

extern "C" struct RAVEN_EXPORT MMKGetWalletResultInterop
{
    const char* status;
    const char* ethAddress;
    const char* solAddress;
    const char* eosAddress;
};

// The following monstrosity disables the pesky 'extern-c-compat' warning that Unreal elevates to error
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wextern-c-compat"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wextern-c-compat"
#endif
extern "C" struct RAVEN_EXPORT MEmptyInterop
{
};
#ifdef __clang__
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

extern "C" struct RAVEN_EXPORT MessageInterop
{
    MessageType type;
    union
    {
        MTokenInterop                   token;
        MOpenStateChangeInterop         openStateChange;
        MCheckoutInterop                checkout;
        MCheckoutResultInterop          checkoutResult;
        MFeatureFlagsInterop            featureFlags;
        MLanguageInterop                language;
        MSetVisibilityInterop           setVisibility;
        MMKSignTransactionInterop       metaKeepSignTransaction;
        MMKSignTransactionResultInterop metaKeepSignTransactionResult;
        MMKSignMessageInterop           metaKeepSignMessage;
        MMKSignMessageResultInterop     metaKeepSignMessageResult;
        MMKSignTypedDataInterop         metaKeepSignTypedData;
        MMKSignTypedDataResultInterop   metaKeepSignTypedDataResult;
        MMKGetWalletInterop             metaKeepGetWallet;
        MMKGetWalletResultInterop       metaKeepGetWalletResult;
        MMKGetConsentInterop            metaKeepGetConsent;
        MMKGetConsentResultInterop      metaKeepGetConsentResult;
        MEmptyInterop                   empty;
    };
};
#pragma pack(pop)

class RAVEN_EXPORT EventBufferInterop
{
public:
    explicit EventBufferInterop(const char* bufferName);
    ~        EventBufferInterop();
    bool     write(const MessageInterop& message);

    MessageInterop listenSync();
    const char*    getError();
    void           clearError();
    void           clear();

private:
    class ShmBuffer* eventBufferImpl;
};

extern "C" RAVEN_EXPORT EventBufferInterop* CreateEventBuffer(const char* bufferName);
extern "C" RAVEN_EXPORT void                DestroyEventBuffer(EventBufferInterop* eventBuffer);
extern "C" RAVEN_EXPORT MessageInterop      ListenToEventBuffer(EventBufferInterop* eventBuffer);
extern "C" RAVEN_EXPORT const char*         GetEventBufferError(EventBufferInterop* eventBuffer);
extern "C" RAVEN_EXPORT void                ClearEventBufferError(EventBufferInterop* eventBuffer);
extern "C" RAVEN_EXPORT void                ClearEventBuffer(EventBufferInterop* eventBuffer);
extern "C" RAVEN_EXPORT bool                WriteToEventBuffer(EventBufferInterop* eventBuffer, MessageInterop& message);
extern "C" RAVEN_EXPORT bool                WriteToEventBufferCheckout(EventBufferInterop* eventBuffer, const char* sku);
extern "C" RAVEN_EXPORT bool                WriteToEventBufferSetVisibility(EventBufferInterop* eventBuffer, bool newVisibility);
extern "C" RAVEN_EXPORT bool                WriteToEventBufferCheckoutResult(EventBufferInterop* eventBuffer, bool result, const char* sku);
extern "C" RAVEN_EXPORT bool                WriteToEventBufferOpenStateChange(EventBufferInterop* eventBuffer, bool openState);
extern "C" RAVEN_EXPORT bool                WriteToEventBufferGetWallet(EventBufferInterop* eventBuffer);
extern "C" RAVEN_EXPORT bool                WriteToEventBufferGetWalletResult(
                   EventBufferInterop* eventBuffer, const char* status, const char* ethAddress, const char* solAddress, const char* eosAddress);
extern "C" RAVEN_EXPORT bool WriteToEventBufferSignTypedData(EventBufferInterop* eventBuffer, const char* message, const char* reason);
extern "C" RAVEN_EXPORT bool WriteToEventBufferSignTypedDataResult(
    EventBufferInterop* eventBuffer, const char* status, const char* signature, const char* r, const char* s, const char* v);
extern "C" RAVEN_EXPORT bool WriteToEventBufferSignMessage(EventBufferInterop* eventBuffer, const char* message, const char* reason);
extern "C" RAVEN_EXPORT bool WriteToEventBufferSignMessageResult(
    EventBufferInterop* eventBuffer, const char* status, MMKSignMessageResultResponseInterop response);
extern "C" RAVEN_EXPORT bool WriteToEventBufferSignTransaction(EventBufferInterop* eventBuffer, const char* message, const char* reason);
extern "C" RAVEN_EXPORT bool WriteToEventBufferSignTransactionResult(
    EventBufferInterop* eventBuffer, const char* status, MMKSignTransactionResultResponseInterop response);
extern "C" RAVEN_EXPORT bool WriteToEventBufferGetConsent(EventBufferInterop* eventBuffer, const char* consentToken);
extern "C" RAVEN_EXPORT bool WriteToEventBufferGetConsentResult(
    EventBufferInterop* eventBuffer, const char* status, MMKGetConsentResultResponseInterop response);
extern "C" RAVEN_EXPORT const char* GetEventBufferOverlayUi();
extern "C" RAVEN_EXPORT const char* GetEventBufferGameSdk();
extern "C" RAVEN_EXPORT const char* GetShmBufferCefImage();
extern "C" RAVEN_EXPORT const char* GetShmBufferCefImageDimensions();

} // namespace elixir::overlay::message

#endif
