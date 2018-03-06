// Copyright David Lovi, 2018.

#include "ResolutionManager.h"
#include "Engine/Engine.h"
#include "DynamicRHI.h"
#include "Math/IntPoint.h"
#include <algorithm>


UGameUserSettings* FResolutionManager::GetUserSettings() {
    return GEngine->GameUserSettings;
}

std::vector<std::pair<uint32, uint32> > FResolutionManager::ComputeSupportedResolutions() {
    std::vector<std::pair<uint32, uint32> > retVal;
    FScreenResolutionArray resolutions;

    if (RHIGetAvailableResolutions(resolutions, true /* ignore hertz */))
        for (const FScreenResolutionRHI& r : resolutions)
            retVal.push_back(std::make_pair(r.Width, r.Height));
    return retVal;
}

std::vector<std::pair<uint32, uint32> >& FResolutionManager::SupportedResolutions() {
    static std::vector<std::pair<uint32, uint32> > retVal(ComputeSupportedResolutions());
    return retVal;
}

void FResolutionManager::ChangeResolution(uint32 width, uint32 height, bool fullscreen) {
    auto* settings = GetUserSettings();
    auto mode = fullscreen ? EWindowMode::Fullscreen : EWindowMode::Windowed;

    settings->RequestResolutionChange(width, height, mode, false);

    // Record our change in settings for later potential persistence calls
    settings->SetScreenResolution(FIntPoint(width, height));
    settings->SetFullscreenMode(mode);
    // TODO: Make user friendly with confirm / revert
    settings->ConfirmVideoMode();
}

void FResolutionManager::NextResolution(bool fullscreen) {
    auto* settings = GetUserSettings();
    auto& resolutions = SupportedResolutions();

    auto current_res = std::make_pair(
        uint32(settings->GetScreenResolution().X),
        uint32(settings->GetScreenResolution().Y));

    auto result = std::find(resolutions.begin(), resolutions.end(), current_res);
    if (result == resolutions.end())
        return;

    result = ++result;
    if (result == resolutions.end())
        result = resolutions.begin();

    ChangeResolution(result->first, result->second, fullscreen);
}

void FResolutionManager::Persist() {
    auto* settings = GetUserSettings();
    settings->SaveSettings();
}
