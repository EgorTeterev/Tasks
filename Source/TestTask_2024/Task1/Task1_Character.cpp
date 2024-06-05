#include "Task1_Character.h"

//====================================================================================================================================================================
ATask1_Character::ATask1_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;
		
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

}
//====================================================================================================================================================================
void ATask1_Character::BeginPlay()
{ 
	Super::BeginPlay();
	
	MainCharacterController = Cast<APlayerController>(GetController());
	if (MainCharacterController) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MainCharacterController->GetLocalPlayer())) {
			UE_LOG(LogTemp, Warning, TEXT("Enhanced input subsystem is ok"));
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
//====================================================================================================================================================================
void ATask1_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//====================================================================================================================================================================
void ATask1_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATask1_Character::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATask1_Character::Look);
		EnhancedInputComponent->BindAction(ItteractAction, ETriggerEvent::Triggered, this, &ATask1_Character::Itterack);

	}
}
//====================================================================================================================================================================
void ATask1_Character::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = { 0,Rotation.Yaw,0 };

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//UE_LOG(LogTemp, Warning, TEXT("Forward Direction %s"), *ForwardDirection.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Right Direction %s"), *RightDirection.ToString());

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}
//====================================================================================================================================================================
void ATask1_Character::Look(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Look action"));

	const FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(-LookVector.Y);
}
//====================================================================================================================================================================
void ATask1_Character::Itterack()
{

}

