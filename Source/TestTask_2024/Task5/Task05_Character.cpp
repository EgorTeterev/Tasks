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
	
	SpawnLocation = GetActorLocation()+GetControlRotation().Vector()*100.0f;
	LaunchVelocity = GetControlRotation().Vector() * 1000.0f;

	FPredictProjectilePathParams PredictParams;
	PredictParams.StartLocation = SpawnLocation;
	PredictParams.LaunchVelocity = LaunchVelocity;
	PredictParams.bTraceWithCollision = true; // Включает трассировку с учётом столкновений
	PredictParams.ProjectileRadius = 5.0f; // Радиус снаряда
	PredictParams.MaxSimTime = 3.0f; // Максимальное время симуляции
	PredictParams.SimFrequency = 15.0f; // Частота симуляции
	PredictParams.OverrideGravityZ = -980.f; // Гравитация

	FPredictProjectilePathResult PredictResult;

	bool bHit = UGameplayStatics::PredictProjectilePath(this, PredictParams, PredictResult);

	if (bHit)
	{
		
		// Если был хит, то можно обработать результаты, например, нарисовать траекторию
		int temp = 0;
		for (const FPredictProjectilePathPointData& PointData : PredictResult.PathData)
		{
			if (!(temp % 3)) {
				DrawDebugSphere(GetWorld(), PointData.Location, 15.0f, 12, FColor::Red, false, 0.1f);
			}
			temp++;
		}
		if (!bIsPlatformSpawned) {
			FActorSpawnParameters SpawnParams;
			FVector PlatformSpawnLocation =  PredictResult.HitResult.Location;
			FRotator PlatformSpawnRotation = GetControlRotation();
			SpawnedPlatform = GetWorld()->SpawnActor<AActor>(Platform, PlatformSpawnLocation, PlatformSpawnRotation, SpawnParams);
			SpawnedPlatform->SetActorEnableCollision(false);
			bIsPlatformSpawned = true;
		}
		else {
			SpawnedPlatform->SetActorLocation(PredictResult.HitResult.Location);
		}
	}
}

void ATask05_Character::EndFocuse()
{
	bIsFocusing = false;
	bIsPlatformSpawned = false;
	MakeShot(SpawnLocation, LaunchVelocity);
}

void ATask05_Character::MakeShot(FVector ShootVector, FVector ShootVelocity)
{
	FActorSpawnParameters SpawnParams;
	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(Projectile, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

}

