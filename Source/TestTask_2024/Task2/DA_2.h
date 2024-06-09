#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_1.h"
#include "DA_2.generated.h"
//====================================================================================================================================================================
UENUM(BlueprintType)
enum class EMyEnum : uint8
{
	value_true	UMETA(DisplayName = "true"),
	value_false	UMETA(DisplayName = "false"),	
	value_n	    UMETA(DisplayName = "n")
};
//====================================================================================================================================================================
UCLASS()
class TESTTASK_2024_API UDA_2 : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DA_2")
	EMyEnum Enumiration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DA_2",meta = (EditCondition = "Enumiration == EMyEnum::value_true", EditConditionHides))
	UDA_1* Data_Asset_1;
};
