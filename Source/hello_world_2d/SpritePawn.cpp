// Copyright David Lovi, 2018.

#include "SpritePawn.h"
#include "Components/SceneComponent.h"


FVector ASpritePawn::bearingToVector() {
    switch (direction) {
        case EBearing::NORTH:
            return FVector(0.0f, 0.0f, 1.0f);
            break;
        case EBearing::EAST:
            return FVector(1.0f, 0.0f, 0.0f);
            break;
        case EBearing::SOUTH:
            return FVector(0.0f, 0.0f, -1.0f);
            break;
        case EBearing::WEST:
            return FVector(-1.0f, 0.0f, 0.0f);
            break;
        default:
            return FVector(0.0f, 0.0f, 0.0f);
            break;
    }
}

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

    direction = EBearing::SOUTH;
    bIsWalking = false;
    inputDirection = direction;
    bInputIsWalking = bIsWalking;

    fastWalkSpeed = 90.0f;
    slowWalkSpeed = 30.0f;
}

void ASpritePawn::PostInitProperties() {
    Super::PostInitProperties();

    walkSpeed = slowWalkSpeed;

    bearingToWalkAnim[EBearing::NORTH] = walkUpSpriteAnim;
    bearingToWalkAnim[EBearing::EAST] = walkRightSpriteAnim;
    bearingToWalkAnim[EBearing::SOUTH] = walkDownSpriteAnim;
    bearingToWalkAnim[EBearing::WEST] = walkLeftSpriteAnim;

    bearingToIdleAnim[EBearing::NORTH] = idleUpSpriteAnim;
    bearingToIdleAnim[EBearing::EAST] = idleRightSpriteAnim;
    bearingToIdleAnim[EBearing::SOUTH] = idleDownSpriteAnim;
    bearingToIdleAnim[EBearing::WEST] = idleLeftSpriteAnim;
}

// Called when the game starts or when spawned
void ASpritePawn::BeginPlay()
{
	Super::BeginPlay();
    animation->SetFlipbook(selectFlipBook());
}

// Called every frame
void ASpritePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (inputDirection != direction || bInputIsWalking != bIsWalking) {
        direction = inputDirection;
        bIsWalking = bInputIsWalking;
        animation->SetFlipbook(selectFlipBook());
    }

    if (bIsWalking) {
        FVector loc = GetActorLocation() + walkSpeed * DeltaTime * bearingToVector();
        SetActorLocation(loc, false);  // TODO: Collision
    }
}

// Called to bind functionality to input
void ASpritePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    InputComponent->BindAction("A", IE_Pressed, this, &ASpritePawn::Interact);
    InputComponent->BindAction("B", IE_Pressed, this, &ASpritePawn::Cancel);
    InputComponent->BindAction("Y", IE_Pressed, this, &ASpritePawn::Run);
    InputComponent->BindAction("Y", IE_Released, this, &ASpritePawn::Walk);

    InputComponent->BindAxis("MoveRight", this, &ASpritePawn::MoveRight);
    InputComponent->BindAxis("MoveUp", this, &ASpritePawn::MoveUp);
}

void ASpritePawn::Interact() {
    // TODO: Stub.  Interaction button pressed
}

void ASpritePawn::Cancel() {
    // TODO: Stub.  Cancel button pressed
}

void ASpritePawn::Run() {
    walkSpeed = fastWalkSpeed;
}

void ASpritePawn::Walk() {
    walkSpeed = slowWalkSpeed;
}

void ASpritePawn::MoveRight(float axisValue) {
    Move(axisValue, EBearing::EAST, EBearing::WEST);
}

void ASpritePawn::MoveUp(float axisValue) {
    Move(axisValue, EBearing::NORTH, EBearing::SOUTH);
}

void ASpritePawn::Move(float axisValue, EBearing forward, EBearing backward) {
    if (axisValue > 0.0f) {
        inputDirection = forward;
        bInputIsWalking = true;
    } else if (axisValue < 0.0f) {
        inputDirection = backward;
        bInputIsWalking = true;
    } else if (direction == forward || direction == backward) {
        bInputIsWalking = false;
    }
}

UPaperFlipbook* ASpritePawn::selectFlipBook() {
    if (bIsWalking)
        return bearingToWalkAnim[direction];
    return bearingToIdleAnim[direction];
}
