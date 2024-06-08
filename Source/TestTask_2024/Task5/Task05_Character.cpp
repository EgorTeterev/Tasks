#include "Task05_Character.h"

ATask05_Character::ATask05_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	ShootComponent = CreateDefaultSubobject<UTask05_ShootActorComponent>(TEXT("Shoot component"));

}

void ATask05_Character::BeginPlay()
{
	Super::BeginPlay();
//Input	
	Test05_Character_Controller = Cast<APlayerController>(GetController());
	if (Test05_Character_Controller) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Test05_Character_Controller->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ATask05_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//====================================================================================================================================================================
void ATask05_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATask05_Character::Look);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, ShootComponent, &UTask05_ShootActorComponent::StartFocuse);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, ShootComponent, &UTask05_ShootActorComponent::EndFocuse);
	}
}
//====================================================================================================================================================================
void ATask05_Character::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(-LookVector.Y);
}
//====================================================================================================================================================================





