#include "Task05_Character.h"

ATask05_Character::ATask05_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

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

void ATask05_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATask05_Character::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATask05_Character::Look);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATask05_Character::StartFocuse);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &ATask05_Character::EndFocuse);
	}
}
//====================================================================================================================================================================
void ATask05_Character::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = { 0,Rotation.Yaw,0 };

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void ATask05_Character::Look(const FInputActionValue& Value)
{

	const FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(-LookVector.Y);
}
//====================================================================================================================================================================
void ATask05_Character::StartFocuse()
{
	if (!bIsFocusing) bIsFocusing = true;
	if (!GetWorld()) return;
	if (!bIsPlatformSpawned) {
		FActorSpawnParameters SpawnParams;
	//	AActor* SpawnedPlatform = GetWorld()->SpawnActor<AActor>(Platform,SpawnLocation,SpawnRotation,SpawnParams);
	}



	APlayerController* PlayerController = GetController<APlayerController>();
	if (!PlayerController) return;

	FVector  ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	FVector TraceStart = ViewLocation;
	FVector ShootDirection = ViewRotation.Vector();
	FVector TraceEnd = TraceStart + ShootDirection * MaxDistanceToShoot;

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue,1.0f,0,3.0f);
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	if (!HitResult.bBlockingHit) return;
	LocationToSpawnPlatform = HitResult.Location;


	FVector CharacterTraceStart = GetActorForwardVector();
	FVector CharacterTraceEnd = TraceEnd;

}

void ATask05_Character::EndFocuse()
{
	bIsFocusing = false;
	//MakeShot();
}

void ATask05_Character::MakeShot(FVector ShootVector)
{

}

