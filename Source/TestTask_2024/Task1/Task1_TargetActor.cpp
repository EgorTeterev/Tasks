#include "Task1_TargetActor.h"
//====================================================================================================================================================================
ATask1_TargetActor::ATask1_TargetActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

//====================================================================================================================================================================
void ATask1_TargetActor::BeginPlay()
{
	Super::BeginPlay();
	
	Character = Cast<ACharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	TargetLocation = GetActorLocation();
}

void ATask1_TargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateDistance();
	IsInViewPort();
}
//====================================================================================================================================================================
void ATask1_TargetActor::UpdateDistance()
{
	CharacterLocation = Character->GetActorLocation();
	DistanceToCharacter = floor(FVector::Distance(TargetLocation, CharacterLocation)/100);
}	

void ATask1_TargetActor::IsInViewPort()
{
	//FVector2D ScreenPosition;
	APlayerController* CharacterPlayerController = Cast<APlayerController>(Character->GetController());
	if(!CharacterPlayerController) return;


	CharacterPlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ScreenPosition);


	CharacterPlayerController->GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	bIsInViewPort = ScreenPosition.X >= 0 && ScreenPosition.X <= ViewPortSizeX && ScreenPosition.Y >= 0 && ScreenPosition.Y <= ViewPortSizeY;

	ClampedPosition = ScreenPosition;
	ClampedPosition.X = FMath::Clamp(ClampedPosition.X, 0, ViewPortSizeX);
	ClampedPosition.Y = FMath::Clamp(ClampedPosition.Y, 0, ViewPortSizeY);

}
//====================================================================================================================================================================
void ATask1_TargetActor::Itteract()
{
	Execute_Itteract(this);
}