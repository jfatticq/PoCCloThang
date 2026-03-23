#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ClothingTypes.generated.h"

UENUM(BlueprintType)
enum class EClothingSlot : uint8
{
    Jacket,
    Top,
    Bottom,
    Shoes
};

USTRUCT(BlueprintType)
struct FClothingItem : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EClothingSlot Slot;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSoftObjectPtr<UTexture2D> Thumbnail;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSoftObjectPtr<USkeletalMesh> Mesh;
};