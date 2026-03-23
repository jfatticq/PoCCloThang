// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ClothingTypes.h"
#include "WardrobeWidget.generated.h"

class UOutfitManagerComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnWardrobeSelectionChanged,
	EClothingCategory, Category,
	FName, NewItemName);

/**
 * Base widget for the wardrobe carousel UI.
 *
 * Create a Widget Blueprint that derives from this class.
 * Use the BlueprintCallable functions (NavigateNext, NavigatePrev,
 * EquipItemByName) to wire up your carousel buttons. Listen to
 * OnSelectionChanged to update labels, thumbnails, etc.
 *
 * The widget automatically finds the OutfitManagerComponent in the
 * world at construction time.
 */
UCLASS()
class POCCLOTHANG_API UWardrobeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Fired when the equipped item changes in any category */
	UPROPERTY(BlueprintAssignable, Category = "Wardrobe")
	FOnWardrobeSelectionChanged OnSelectionChanged;

	/** Navigate to the next item in a category's carousel */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	void NavigateNext(EClothingCategory Category);

	/** Navigate to the previous item in a category's carousel */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	void NavigatePrev(EClothingCategory Category);

	/** Equip a specific item by name (e.g. when clicking a carousel thumbnail) */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	void EquipItemByName(FName ItemName);

	/** Get the display name of the currently equipped item in a category */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	FName GetEquippedItemName(EClothingCategory Category) const;

	/** Get all available items in a category (useful for populating carousel) */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	TArray<FClothingItemEntry> GetItemsInCategory(EClothingCategory Category) const;

	/** Get the OutfitManagerComponent this widget is controlling */
	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	UOutfitManagerComponent* GetOutfitManager() const;

protected:
	virtual void NativeConstruct() override;

private:
	void CacheOutfitManager();

	UFUNCTION()
	void HandleItemEquipped(EClothingCategory Category, FName NewItemName, FName PreviousItemName);

	UPROPERTY()
	TObjectPtr<UOutfitManagerComponent> CachedOutfitManager;
};
