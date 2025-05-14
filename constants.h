#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace Constants
{
    constexpr int height{32};
    constexpr int width{64};
    constexpr int scale{10};
    constexpr int kScreenWidth{width * scale};
    constexpr int kScreenHeight{height * scale};
    constexpr int kDebugPanelWidth{200};
    constexpr int kDebugPanelHeight{height * scale};
    constexpr int kFps{30};
}
#endif