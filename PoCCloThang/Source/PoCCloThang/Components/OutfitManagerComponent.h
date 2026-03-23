// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ClothingTypes.h"
#include "OutfitManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnClothingItemEquipped,
	EClothingCategory, Category,
	FName, NewItemName,
	FName, PreviousItemName);

/**
 * Manages a wardrobe of clothing items organized by category.
 *
 * Each category (Top, Bottom, Shoes, Jacket) can have one active item
 * at a time. Equipping a new item in a category automatically hides
 * the previous one.
 *
 * Add this component to the MetaHuman actor and populate the Items
 * array with references to clothing mesh root components.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POCCLOTHANG_API UOutfitManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOutfitManagerComponent();

	/** All clothing items available on this character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wardrobe")
	TArray<FClothingItemEntry> Items;

	/** Fired when an item is equipped (including at startup) */
	UPROPERTY(BlueprintAssignable, Category = "Wardrobe")
	FOnClothingItemEquipped OnClothingItemEquipped;

	/** Equip a specific item by name. Hides the previous item in the same category. */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	bool EquipItem(FName ItemName);

	/** Equip the next item in the given category's carousel. Wraps around. */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	FName EquipNextInCategory(EClothingCategory Category);

	/** Equip the previous item in the given category's carousel. Wraps around. */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	FName EquipPrevInCategory(EClothingCategory Category);

	/** Unequip the current item in a category (hide it, nothing shown). */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	void UnequipCategory(EClothingCategory Category);

	/** Get the currently equipped item name for a category. NAME_None if nothing equipped. */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	FName GetEquippedItemName(EClothingCategory Category) const;

	/** Get all items in a given category (for building carousel UI). */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	TArray<FClothingItemEntry> GetItemsInCategory(EClothingCategory Category) const;

	/** Get the number of items in a category. */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	int32 GetItemCountInCategory(EClothingCategory Category) const;

protected:
	virtual void BeginPlay() override;

private:
	/** Maps category to currently equipped item name */
	UPROPERTY()
	TMap<EClothingCategory, FName> EquippedItems;

	FClothingItemEntry* FindItem(FName ItemName);
	const FClothingItemEntry* FindItem(FName ItemName) const;
	int32 GetCurrentIndexInCategory(EClothingCategory Category) const;
	void SetItemVisibility(FName ItemName, bool bVisible);
};
