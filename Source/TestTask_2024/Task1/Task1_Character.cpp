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
	
	Test1_Character_Controller = Cast<APlayerController>(GetController());
	if (Test1_Character_Controller) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Test1_Character_Controller->GetLocalPlayer())) {
			UE_LOG(LogTemp, Warning, TEXT("Enhanced input subsystem is ok"));
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
//====================================================================================================================================================================
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
void ATask1_Character::Itteract()
{
	if (!Cast<ATask1_TargetActor>(FocuseActor)) return;
	FocuseActor->Itteract_Implementation();
}
//====================================================================================================================================================================
void ATask1_Character::FocusingItteractable()
{
	Test1_Character_Controller = GetController<APlayerController>();

	if (!Controller) return;
	//get camera location and rotation to trace at the place,camera looking;
	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation,ViewRotation);

	//start tracing from camera location to understand,if we focused on itteractable item.
	FVector TraceStart = ViewLocation;
	FVector TraceDirection = ViewRotation.Vector();
	FVector TraceEnd = TraceStart + TraceDirection * ItteractionDistance;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 3.0f, 0, 3.0f);
	FocuseActor = nullptr;
	if (!HitResult.bBlockingHit) return;
	IItteractInterface* ItteractableActor = Cast<IItteractInterface>(HitResult.GetActor());
	if (!ItteractableActor) return;

	/*
	camera hited itteractable item,can we acces it?
	We should take ItteractableActor location,and trace from character location to ItteractableActor,if there is a wall between them->return false
	*/

	FHitResult CharacterHitResult;
	FVector CharacterTraceStart = GetActorLocation();
	FVector CharacterTraceEnd = HitResult.GetActor()->GetActorLocation();

	GetWorld()->LineTraceSingleByChannel(CharacterHitResult, CharacterTraceStart, CharacterTraceEnd, ECollisionChannel::ECC_Visibility);
	//DrawDebugLine(GetWorld(), CharacterTraceStart, CharacterTraceEnd, FColor::Red,false, 3.0f, 0, 3.0f);

	if (CharacterHitResult.bBlockingHit && CharacterHitResult.GetActor() == HitResult.GetActor())
	{
	//	DrawDebugPoint(GetWorld(), CharacterHitResult.ImpactPoint, 16.0f, FColor::Blue, false, 3.0f, 5);
		ItteractableActor = Cast<IItteractInterface>(CharacterHitResult.GetActor());
	//	UE_LOG(LogTemp, Warning, TEXT("You can interact with %s"), *CharacterHitResult.GetActor()->GetName());
		FocuseActor = Cast<ATask1_TargetActor>(CharacterHitResult.GetActor());
		return;
	}

	

}

