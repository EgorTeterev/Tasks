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
//Input	
	Test1_Character_Controller = Cast<APlayerController>(GetController());
	if (Test1_Character_Controller) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Test1_Character_Controller->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ATask1_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FocusingItteractable();

}
//====================================================================================================================================================================
void ATask1_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATask1_Character::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATask1_Character::Look);
		EnhancedInputComponent->BindAction(ItteractAction, ETriggerEvent::Started, this, &ATask1_Character::Itteract);
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

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}
//====================================================================================================================================================================
void ATask1_Character::Look(const FInputActionValue& Value)
{

	const FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(-LookVector.Y);
}
void ATask1_Character::Itteract()
{
	if (!Cast<ATask1_TargetActor>(FocuseActor)) return;
	FocuseActor->Itteract();
}
//====================================================================================================================================================================
void ATask1_Character::FocusingItteractable()
{
	Test1_Character_Controller = GetController<APlayerController>();

	if (!Controller) return;
	FocuseActor = nullptr;
	//get camera location and rotation to trace at the place,camera looking;
	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation,ViewRotation);

	//start tracing from camera location to understand,if we are focused on itteractable item.
	FVector TraceStart = ViewLocation;
	FVector TraceDirection = ViewRotation.Vector();
	FVector TraceEnd = TraceStart + TraceDirection * ItteractionDistance;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	if (!HitResult.bBlockingHit) return;
	IItteractInterface* ItteractableActor = Cast<IItteractInterface>(HitResult.GetActor());
	if (!ItteractableActor) return;

	/*
	camera hited itteractable item,can we acces it?
	trace from character location to ItteractableActor,if there is a wall between them
	*/

	FHitResult CharacterHitResult;
	FVector CharacterTraceStart = GetActorLocation();
	FVector CharacterTraceEnd = HitResult.GetActor()->GetActorLocation();

	GetWorld()->LineTraceSingleByChannel(CharacterHitResult, CharacterTraceStart, CharacterTraceEnd, ECollisionChannel::ECC_Visibility);
	if (CharacterHitResult.bBlockingHit && CharacterHitResult.GetActor() == HitResult.GetActor())
	{
		ItteractableActor = Cast<IItteractInterface>(CharacterHitResult.GetActor());
		FocuseActor = Cast<ATask1_TargetActor>(CharacterHitResult.GetActor());
		return;
	}

}

