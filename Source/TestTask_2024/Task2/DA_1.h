#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "DA_1.generated.h"
class UDA_2;
//====================================================================================================================================================================
USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	UDA_2* Data_Asset_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	UTexture2D* Texture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Vector;
};
//====================================================================================================================================================================
UCLASS()
class TESTTASK_2024_API UDA_1 : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Execution")
	FMyStruct Test_Structure;
};
