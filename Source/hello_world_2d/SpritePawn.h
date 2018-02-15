// Copyright David Lovi, 2018.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Camera/CameraComponent.h"

#include <map>

#include "SpritePawn.generated.h"


UENUM(BlueprintType)
enum class EBearing : uint8 {
    NORTH,
    EAST,
    SOUTH,
    WEST
};


UCLASS()
class HELLO_WORLD_2D_API ASpritePawn : public APawn
{
	GENERATED_BODY()

private:
    std::map<EBearing, UPaperFlipbook *> bearingToWalkAnim;
    std::map<EBearing, UPaperFlipbook *> bearingToIdleAnim;

    FVector bearingToVector();

protected:
    EBearing direction;
    EBearing inputDirection;

    float walkSpeed;
    bool bIsWalking;
    bool bInputIsWalking;

    UPROPERTY(EditAnywhere)
    float fastWalkSpeed;
    UPROPERTY(EditAnywhere)
    float slowWalkSpeed;

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

    UPaperFlipbook* selectFlipBook();

public:
	// Sets default values for this pawn's properties
	ASpritePawn();

protected:
    virtual void PostInitProperties() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Input bindings:
    // TODO: Think about firing blueprint-implementable events for some of these
    void Interact();
    void Cancel();
    void MoveRight(float axisValue);
    void MoveUp(float axisValue);
    void Move(float axisValue, EBearing forward, EBearing backward);
};
