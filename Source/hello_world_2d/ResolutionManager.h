// Copyright David Lovi, 2018.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "UnrealString.h"
#include <vector>
#include <utility>

#include "ResolutionManager.generated.h"


USTRUCT()
struct HELLO_WORLD_2D_API FResolutionManager
{
    GENERATED_USTRUCT_BODY()

public:
    static constexpr double PPU = 3.2;

private:
    UGameUserSettings* GetUserSettings();
    std::vector<std::pair<uint32, uint32> > ComputeSupportedResolutions();
    std::vector<std::pair<uint32, uint32> >& SupportedResolutions();

public:
    void ChangeResolution(uint32 width, uint32 height, bool fullscreen=true);
    void NextResolution(bool fullscreen=true);
    void Persist();
};

