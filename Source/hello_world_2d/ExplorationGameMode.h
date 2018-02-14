// Copyright David Lovi, 2018.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
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

public:
    UPROPERTY(EditAnywhere)
    TSubclassOf<ASpritePawn> HeroPawnClass;

    AExplorationGameMode(const FObjectInitializer & initializer)
    : AGameModeBase(initializer)
    {
        static ConstructorHelpers::FClassFinder<ASpritePawn> finder(
            TEXT("Blueprint'/Game/Blueprints/HeroPawn.HeroPawn_C'"));
        if (finder.Class) {
            DefaultPawnClass = finder.Class;
        }
    }
};
