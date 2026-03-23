// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OutfitManagerComponent.generated.h"

USTRUCT(BlueprintType)
struct FOutfitEntry
{
	GENERATED_BODY()

	/** Display name used to identify this outfit piece (e.g. "Blouse01") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outfit")
	FName OutfitName;

	/** The root scene component for this outfit piece (set in Blueprint) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outfit")
	TObjectPtr<USceneComponent> OutfitRootComponent = nullptr;

	/** Whether the outfit piece is currently visible */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Outfit")
	bool bIsVisible = true;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOutfitVisibilityChanged, FName, OutfitName, bool, bIsVisible);

/**
 * Manages toggling outfit pieces on/off.
 * Add to your character Blueprint and configure the Outfits array
 * with references to your outfit scene components.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POCCLOTHANG_API UOutfitManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOutfitManagerComponent();

	/** Outfit pieces managed by this component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outfit")
	TArray<FOutfitEntry> Outfits;

	/** Fired when any outfit's visibility changes */
	UPROPERTY(BlueprintAssignable, Category = "Outfit")
	FOnOutfitVisibilityChanged OnOutfitVisibilityChanged;

	/** Toggle an outfit on/off. Returns the new visibility state. */
	UFUNCTION(BlueprintCallable, Category = "Outfit")
	bool ToggleOutfit(FName OutfitName);

	/** Set an outfit's visibility explicitly. Returns true if the outfit was found. */
	UFUNCTION(BlueprintCallable, Category = "Outfit")
	bool SetOutfitVisible(FName OutfitName, bool bVisible);

	/** Check if an outfit is currently visible. Returns false if not found. */
	UFUNCTION(BlueprintCallable, Category = "Outfit")
	bool IsOutfitVisible(FName OutfitName) const;

private:
	FOutfitEntry* FindOutfitEntry(FName OutfitName);
	const FOutfitEntry* FindOutfitEntry(FName OutfitName) const;
};
