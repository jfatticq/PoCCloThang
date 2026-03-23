// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/WardrobeWidget.h"
#include "Components/OutfitManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PoCCloThang.h"

void UWardrobeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CacheOutfitManager();
}

void UWardrobeWidget::NavigateNext(EClothingCategory Category)
{
	UOutfitManagerComponent* Manager = GetOutfitManager();
	if (Manager)
	{
		Manager->EquipNextInCategory(Category);
	}
}

void UWardrobeWidget::NavigatePrev(EClothingCategory Category)
{
	UOutfitManagerComponent* Manager = GetOutfitManager();
	if (Manager)
	{
		Manager->EquipPrevInCategory(Category);
	}
}

void UWardrobeWidget::EquipItemByName(FName ItemName)
{
	UOutfitManagerComponent* Manager = GetOutfitManager();
	if (Manager)
	{
		Manager->EquipItem(ItemName);
	}
}

FName UWardrobeWidget::GetEquippedItemName(EClothingCategory Category) const
{
	UOutfitManagerComponent* Manager = GetOutfitManager();
	return Manager ? Manager->GetEquippedItemName(Category) : NAME_None;
}

TArray<FClothingItemEntry> UWardrobeWidget::GetItemsInCategory(EClothingCategory Category) const
{
	UOutfitManagerComponent* Manager = GetOutfitManager();
	return Manager ? Manager->GetItemsInCategory(Category) : TArray<FClothingItemEntry>();
}

UOutfitManagerComponent* UWardrobeWidget::GetOutfitManager() const
{
	return CachedOutfitManager;
}

void UWardrobeWidget::CacheOutfitManager()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), AllActors);

	for (AActor* Actor : AllActors)
	{
		UOutfitManagerComponent* Comp = Actor->FindComponentByClass<UOutfitManagerComponent>();
		if (Comp)
		{
			CachedOutfitManager = Comp;

			// Listen for equip changes to relay through our widget delegate
			Comp->OnClothingItemEquipped.AddDynamic(this, &UWardrobeWidget::HandleItemEquipped);

			UE_LOG(LogPoCCloThang, Log, TEXT("WardrobeWidget: Found OutfitManagerComponent on '%s'."), *Actor->GetName());
			return;
		}
	}

	UE_LOG(LogPoCCloThang, Warning, TEXT("WardrobeWidget: No actor with OutfitManagerComponent found in the world."));
}

void UWardrobeWidget::HandleItemEquipped(EClothingCategory Category, FName NewItemName, FName PreviousItemName)
{
	OnSelectionChanged.Broadcast(Category, NewItemName);
}
