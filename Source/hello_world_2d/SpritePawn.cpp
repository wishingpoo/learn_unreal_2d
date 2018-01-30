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

}

