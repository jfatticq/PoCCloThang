// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ClothingTypes.generated.h"

/** Categories of clothing that occupy distinct slots on the character. */
UENUM(BlueprintType)
enum class EClothingCategory : uint8
{
	Top      UMETA(DisplayName = "Top"),
	Bottom   UMETA(DisplayName = "Bottom"),
	Shoes    UMETA(DisplayName = "Shoes"),
	Jacket   UMETA(DisplayName = "Jacket")
};

/**
 * A single clothing item that can be equipped on the character.
 * Configure these in the OutfitManagerComponent's Items array.
 */
USTRUCT(BlueprintType)
struct FClothingItemEntry
{
	GENERATED_BODY()

	/** Unique name for this clothing item (e.g. "Blouse01", "LongSkirt01") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clothing")
	FName ItemName;

	/** Which slot this item occupies */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clothing")
	EClothingCategory Category = EClothingCategory::Top;

	/** The root scene component for this clothing item (set in Blueprint) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clothing")
	TObjectPtr<USceneComponent> MeshRootComponent = nullptr;

	/** Optional thumbnail for UI display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clothing")
	TObjectPtr<UTexture2D> Thumbnail = nullptr;
};
