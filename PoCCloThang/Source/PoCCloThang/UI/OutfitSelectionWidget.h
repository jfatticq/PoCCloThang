// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OutfitSelectionWidget.generated.h"

class UButton;
class UTextBlock;
class UOutfitManagerComponent;

/**
 * UMG widget for toggling outfit pieces.
 *
 * Create a Widget Blueprint that derives from this class.
 * Add two UButton widgets named exactly "Blouse01" and "LongSkirt01".
 * Optionally add UTextBlock widgets named "Blouse01Text" and "LongSkirt01Text"
 * to show the current on/off state.
 */
UCLASS()
class POCCLOTHANG_API UOutfitSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	/** Button to toggle the blouse outfit */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Blouse01;

	/** Button to toggle the long skirt outfit */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LongSkirt01;

	/** Optional label showing blouse on/off state */
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Blouse01Text;

	/** Optional label showing long skirt on/off state */
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> LongSkirt01Text;

	virtual void NativeConstruct() override;

private:

	UFUNCTION()
	void OnBlouse01Clicked();

	UFUNCTION()
	void OnLongSkirt01Clicked();

	void ToggleOutfit(FName OutfitName, UTextBlock* StatusText);
	UOutfitManagerComponent* GetOutfitManager() const;
	void CacheOutfitManager();
	void UpdateStatusText(FName OutfitName, UTextBlock* StatusText);

	UPROPERTY()
	TObjectPtr<UOutfitManagerComponent> CachedOutfitManager;

	static const FName Blouse01Name;
	static const FName LongSkirt01Name;
};
