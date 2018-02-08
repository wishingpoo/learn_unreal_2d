// Copyright David Lovi, 2018.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpritePawn.h"
#include "ExplorationGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HELLO_WORLD_2D_API AExplorationGameMode : public AGameModeBase
{
	GENERATED_BODY()

    AExplorationGameMode(const FObjectInitializer & initializer)
    : AGameModeBase(initializer)
    {
        DefaultPawnClass = ASpritePawn::StaticClass();
    }
};
