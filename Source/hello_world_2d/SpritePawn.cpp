// Copyright David Lovi, 2018.

#include "SpritePawn.h"
#include "Components/SceneComponent.h"


// Sets default values
ASpritePawn::ASpritePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    AutoPossessPlayer = EAutoReceiveInput::Player0;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    animation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Render Sprite"));

    camera->SetupAttachment(RootComponent);
    camera->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
    camera->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));
    camera->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
    camera->bConstrainAspectRatio = true;
    camera->bUsePawnControlRotation = false;
    camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    camera->SetOrthoWidth(200.0f);

    animation->SetupAttachment(RootComponent);
    animation->SetLooping(true);
}

// Called when the game starts or when spawned
void ASpritePawn::BeginPlay()
{
	Super::BeginPlay();
    direction = EDirection::SOUTH;
    animation->SetFlipbook(idleDownSpriteAnim);
}

// Called every frame
void ASpritePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpritePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    InputComponent->BindAction("A", IE_Pressed, this, &ASpritePawn::Interact);
    InputComponent->BindAction("B", IE_Pressed, this, &ASpritePawn::Cancel);

    InputComponent->BindAxis("MoveRight", this, &ASpritePawn::MoveRight);
    InputComponent->BindAxis("MoveUp", this, &ASpritePawn::MoveUp);
}

void ASpritePawn::Interact() {
    // TODO: Stub.  Interaction button pressed
}

void ASpritePawn::Cancel() {
    // TODO: Stub.  Cancel button pressed
}

void ASpritePawn::MoveRight(float AxisValue) {
    auto newDirection = direction;
    if (AxisValue > 0.0f) {
        newDirection = EDirection::EAST;
    } else if (AxisValue < 0.0f) {
        newDirection = EDirection::WEST;
    }

    updateDirection(newDirection);
}

void ASpritePawn::MoveUp(float AxisValue) {
    auto newDirection = direction;
    if (AxisValue > 0.0f) {
        newDirection = EDirection::NORTH;
    } else if (AxisValue < 0.0f) {
        newDirection = EDirection::SOUTH;
    }

    updateDirection(newDirection);
}

void ASpritePawn::updateDirection(EDirection newDirection) {
    if (newDirection == direction)
        return;
    direction = newDirection;

    if (direction == EDirection::NORTH) {
        animation->SetFlipbook(walkUpSpriteAnim);
    } else if (direction == EDirection::SOUTH) {
        animation->SetFlipbook(walkDownSpriteAnim);
    } else if (direction == EDirection::EAST) {
        animation->SetFlipbook(walkRightSpriteAnim);
    } else if (direction == EDirection::WEST) {
        animation->SetFlipbook(walkLeftSpriteAnim);
    }
}
