#ifndef ELIXIR_OVERLAY_MESSAGE_H
#define ELIXIR_OVERLAY_MESSAGE_H

#include <cstdint>
#include <vector>
#include <string>
#include <thread>
#include <functional>
#include <memory>
#include <variant>
#include "raven_export.h"

struct PShmBuffer_;
typedef struct PShmBuffer_ PShmBuffer;

struct PError_;
typedef struct PError_ PError;

struct PShm_;
typedef struct PShm_ PShm;

namespace elixir::overlay::message
{

inline auto EVENT_BUFFER_OVERLAY_UI = "EVENT_BUFFER_OVERLAY_UI";
inline auto EVENT_BUFFER_GAME_SDK = "EVENT_BUFFER_GAME_SDK";

#pragma pack(push, 1)
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

extern "C" enum RAVEN_EXPORT MessageType : int32_t
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

inline char* ToCharPtr(const std::string& str)
{
    char* cstr = new char[str.length() + 1];
    cstr[str.length()] = 0;
    std::memcpy(cstr, str.c_str(), str.length());
    return cstr;
}

struct MToken
{
    MessageType messageType{ MTToken };
    std::string token;

    template <class T> void pack(T& pack) { pack(messageType, token); }
    MTokenInterop           ToInterop() { return { ToCharPtr(token) }; };
    static MToken           FromInterop(const MTokenInterop& message) { return { MTToken, message.token }; }
};

struct MOpenStateChange
{
    MessageType messageType{ MTOpenStateChange };
    bool        isOpen;

    template <class T> void pack(T& pack) { pack(messageType, isOpen); }
    MOpenStateChangeInterop ToInterop() { return { isOpen }; }
    static MOpenStateChange FromInterop(const MOpenStateChangeInterop& message) { return { MTOpenStateChange, message.isOpen }; }
};

struct MCheckout
{
    MessageType messageType{ MTCheckout };
    std::string sku;

    template <class T> void pack(T& pack) { pack(messageType, sku); }
    MCheckoutInterop        ToInterop() const { return { ToCharPtr(sku) }; };
    static MCheckout        FromInterop(const MCheckoutInterop& message) { return { MTCheckout, message.sku }; }
};

struct MCheckoutResult
{
    MessageType messageType{ MTCheckoutResult };
    bool        success;
    std::string sku;

    template <class T> void pack(T& pack) { pack(messageType, success, sku); }
    MCheckoutResultInterop  ToInterop() const { return { success, ToCharPtr(sku) }; };
    static MCheckoutResult  FromInterop(const MCheckoutResultInterop& message)
    {
        return { MTCheckoutResult, message.success, std::string(message.sku) };
    }
};

struct MFeatureFlags
{
    MessageType messageType{ MTFeatureFlags };
    std::string featureFlags;

    template <class T> void pack(T& pack) { pack(messageType, featureFlags); }
    MFeatureFlagsInterop    ToInterop() const { return { ToCharPtr(featureFlags) }; };
    static MFeatureFlags    FromInterop(const MFeatureFlagsInterop& message) { return { MTFeatureFlags, message.featureFlags }; }
};

struct MLanguage
{
    MessageType messageType{ MTLanguage };
    std::string language;

    template <class T> void pack(T& pack) { pack(messageType, language); }
    MLanguageInterop        ToInterop() const { return { ToCharPtr(language) }; };
    static MLanguage        FromInterop(const MLanguageInterop& message) { return { MTLanguage, message.language }; }
};

struct MSetVisibility
{
    MessageType messageType{ MTSetVisibility };
    bool        newVisibility;

    template <class T> void pack(T& pack) { pack(messageType, newVisibility); }
    MSetVisibilityInterop   ToInterop() { return { newVisibility }; }
    static MSetVisibility   FromInterop(const MSetVisibilityInterop& message) { return { MTSetVisibility, message.newVisibility }; }
};

struct MEmpty
{
    MessageType messageType{ MTEmpty };

    template <class T> void pack(T& pack) { pack(messageType); }
    MEmptyInterop           ToInterop() { return {}; }
    static MEmpty           FromInterop(const MEmptyInterop& message) { return { MTEmpty }; }
};

struct Message
{
    MessageType                                                                                                          type;
    std::variant<MToken, MOpenStateChange, MCheckout, MCheckoutResult, MFeatureFlags, MLanguage, MSetVisibility, MEmpty> data;

    MessageInterop ToInterop()
    {
        MessageInterop messageInterop;
        messageInterop.type = type;

        switch (type)
        {
            case MTToken:
                messageInterop.token = std::get<MToken>(data).ToInterop();
                break;
            case MTOpenStateChange:
                messageInterop.openStateChange = std::get<MOpenStateChange>(data).ToInterop();
                break;
            case MTCheckout:
                messageInterop.checkout = std::get<MCheckout>(data).ToInterop();
                break;
            case MTCheckoutResult:
                messageInterop.checkoutResult = std::get<MCheckoutResult>(data).ToInterop();
                break;
            case MTFeatureFlags:
                messageInterop.featureFlags = std::get<MFeatureFlags>(data).ToInterop();
                break;
            case MTLanguage:
                messageInterop.language = std::get<MLanguage>(data).ToInterop();
                break;
            case MTSetVisibility:
                messageInterop.setVisibility = std::get<MSetVisibility>(data).ToInterop();
                break;
            case MTEmpty:
                messageInterop.empty = std::get<MEmpty>(data).ToInterop();
                break;
            default:
                break;
        }

        return messageInterop;
    }
};

class EventBuffer
{
public:
    explicit EventBuffer(const char* bufferName);
    ~EventBuffer();

    std::unique_ptr<std::thread> listen(
        const std::function<bool()>& shouldShutdown, const std::function<void(std::vector<unsigned char>&)>& eventCallback);
    Message     listenSync();
    void        clear();
    size_t      write(const MToken& message);
    size_t      write(const MOpenStateChange& message);
    size_t      write(const MCheckout& message);
    size_t      write(const MCheckoutResult& message);
    size_t      write(const MFeatureFlags& message);
    size_t      write(const MLanguage& message);
    size_t      write(const MSetVisibility& message);
    size_t      write(const MEmpty& message);
    const char* getError();
    void        clearError();

private:
    std::vector<uint8_t> prependSizeToMessage(std::vector<uint8_t> packedMessage);
    void listenImpl(const std::function<bool()>& shouldShutdown, const std::function<void(std::vector<unsigned char>&)>& eventCallback);
    PShmBuffer*            eventBuffer;
    PError*                eventBufferError;
    inline static uint32_t instanceCount = 0;
};

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
    EventBuffer* eventBufferImpl;
};

int32_t readMessageLength(PShmBuffer* eventBuffer, int32_t* outLength);
size_t  getMessageSizeByType(MessageType messageType);

std::vector<unsigned char> packMessage(MToken message);
std::vector<unsigned char> packMessage(MOpenStateChange message);
std::vector<unsigned char> packMessage(MCheckout message);
std::vector<unsigned char> packMessage(MCheckoutResult message);
std::vector<unsigned char> packMessage(MFeatureFlags message);
std::vector<unsigned char> packMessage(MLanguage message);
std::vector<unsigned char> packMessage(MSetVisibility message);
std::vector<unsigned char> packMessage(MEmpty message);

void unpackMessage(const std::vector<unsigned char>& buffer, MToken& value);
void unpackMessage(const std::vector<unsigned char>& buffer, MOpenStateChange& value);
void unpackMessage(const std::vector<unsigned char>& buffer, MCheckout& value);
void unpackMessage(const std::vector<unsigned char>& buffer, MCheckoutResult& value);
void unpackMessage(const std::vector<unsigned char>& buffer, MFeatureFlags& value);
void unpackMessage(const std::vector<unsigned char>& buffer, MLanguage& value);
void unpackMessage(const std::vector<unsigned char>& buffer, MSetVisibility& value);
void unpackMessage(const std::vector<unsigned char>& buffer, MEmpty& value);

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

extern "C" RAVEN_EXPORT const char* GetEventBufferOverlayUi();
extern "C" RAVEN_EXPORT const char* GetEventBufferGameSdk();

} // namespace elixir::overlay::message

#endif
