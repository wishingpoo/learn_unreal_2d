// Copyright David Lovi, 2018.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Camera/CameraComponent.h"
#include "SpritePawn.generated.h"

UCLASS()
class HELLO_WORLD_2D_API ASpritePawn : public APawn
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly)
    UPaperFlipbookComponent* animation;

    UPROPERTY(EditDefaultsOnly)
    UPaperFlipbook* idleUpSpriteAnim;
    UPROPERTY(EditDefaultsOnly)
    UPaperFlipbook* idleDownSpriteAnim;
    UPROPERTY(EditDefaultsOnly)
    UPaperFlipbook* idleLeftSpriteAnim;
    UPROPERTY(EditDefaultsOnly)
    UPaperFlipbook* idleRightSpriteAnim;

    UPROPERTY(EditDefaultsOnly)
    UPaperFlipbook* walkUpSpriteAnim;
    UPROPERTY(EditDefaultsOnly)
    UPaperFlipbook* walkDownSpriteAnim;
    UPROPERTY(EditDefaultsOnly)
    UPaperFlipbook* walkLeftSpriteAnim;
    UPROPERTY(EditDefaultsOnly)
    UPaperFlipbook* walkRightSpriteAnim;

    UPROPERTY(EditAnywhere)
    UCameraComponent *camera;

public:
	// Sets default values for this pawn's properties
	ASpritePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
