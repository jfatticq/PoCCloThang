// Copyright Epic Games, Inc. All Rights Reserved.

#include "Components/OutfitManagerComponent.h"
#include "PoCCloThang.h"

UOutfitManagerComponent::UOutfitManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UOutfitManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Hide all items initially, then equip the first item in each category
	for (FClothingItemEntry& Item : Items)
	{
		if (Item.MeshRootComponent)
		{
			Item.MeshRootComponent->SetVisibility(false, true);
		}
	}

	// Equip the first item found in each populated category
	TSet<EClothingCategory> InitializedCategories;
	for (const FClothingItemEntry& Item : Items)
	{
		if (!InitializedCategories.Contains(Item.Category))
		{
			InitializedCategories.Add(Item.Category);
			EquipItem(Item.ItemName);
		}
	}
}

bool UOutfitManagerComponent::EquipItem(FName ItemName)
{
	FClothingItemEntry* NewItem = FindItem(ItemName);
	if (!NewItem)
	{
		UE_LOG(LogPoCCloThang, Warning, TEXT("OutfitManager: Item '%s' not found."), *ItemName.ToString());
		return false;
	}

	if (!NewItem->MeshRootComponent)
	{
		UE_LOG(LogPoCCloThang, Warning, TEXT("OutfitManager: Item '%s' has no mesh root component assigned."), *ItemName.ToString());
		return false;
	}

	const EClothingCategory Category = NewItem->Category;
	const FName PreviousItemName = GetEquippedItemName(Category);

	// Hide the previously equipped item in this category
	if (!PreviousItemName.IsNone() && PreviousItemName != ItemName)
	{
		SetItemVisibility(PreviousItemName, false);
	}

	// Show the new item
	SetItemVisibility(ItemName, true);
	EquippedItems.Add(Category, ItemName);

	OnClothingItemEquipped.Broadcast(Category, ItemName, PreviousItemName);

	UE_LOG(LogPoCCloThang, Log, TEXT("OutfitManager: Equipped '%s' in %s slot (was '%s')."),
		*ItemName.ToString(),
		*UEnum::GetValueAsString(Category),
		PreviousItemName.IsNone() ? TEXT("none") : *PreviousItemName.ToString());

	return true;
}

FName UOutfitManagerComponent::EquipNextInCategory(EClothingCategory Category)
{
	TArray<FClothingItemEntry> CategoryItems = GetItemsInCategory(Category);
	if (CategoryItems.Num() == 0)
	{
		return NAME_None;
	}

	const int32 CurrentIndex = GetCurrentIndexInCategory(Category);
	const int32 NextIndex = (CurrentIndex + 1) % CategoryItems.Num();

	EquipItem(CategoryItems[NextIndex].ItemName);
	return CategoryItems[NextIndex].ItemName;
}

FName UOutfitManagerComponent::EquipPrevInCategory(EClothingCategory Category)
{
	TArray<FClothingItemEntry> CategoryItems = GetItemsInCategory(Category);
	if (CategoryItems.Num() == 0)
	{
		return NAME_None;
	}

	const int32 CurrentIndex = GetCurrentIndexInCategory(Category);
	const int32 PrevIndex = (CurrentIndex - 1 + CategoryItems.Num()) % CategoryItems.Num();

	EquipItem(CategoryItems[PrevIndex].ItemName);
	return CategoryItems[PrevIndex].ItemName;
}

void UOutfitManagerComponent::UnequipCategory(EClothingCategory Category)
{
	const FName CurrentItem = GetEquippedItemName(Category);
	if (!CurrentItem.IsNone())
	{
		SetItemVisibility(CurrentItem, false);
		EquippedItems.Remove(Category);

		OnClothingItemEquipped.Broadcast(Category, NAME_None, CurrentItem);
	}
}

FName UOutfitManagerComponent::GetEquippedItemName(EClothingCategory Category) const
{
	const FName* Found = EquippedItems.Find(Category);
	return Found ? *Found : NAME_None;
}

TArray<FClothingItemEntry> UOutfitManagerComponent::GetItemsInCategory(EClothingCategory Category) const
{
	TArray<FClothingItemEntry> Result;
	for (const FClothingItemEntry& Item : Items)
	{
		if (Item.Category == Category)
		{
			Result.Add(Item);
		}
	}
	return Result;
}

int32 UOutfitManagerComponent::GetItemCountInCategory(EClothingCategory Category) const
{
	int32 Count = 0;
	for (const FClothingItemEntry& Item : Items)
	{
		if (Item.Category == Category)
		{
			++Count;
		}
	}
	return Count;
}

FClothingItemEntry* UOutfitManagerComponent::FindItem(FName ItemName)
{
	for (FClothingItemEntry& Item : Items)
	{
		if (Item.ItemName == ItemName)
		{
			return &Item;
		}
	}
	return nullptr;
}

const FClothingItemEntry* UOutfitManagerComponent::FindItem(FName ItemName) const
{
	for (const FClothingItemEntry& Item : Items)
	{
		if (Item.ItemName == ItemName)
		{
			return &Item;
		}
	}
	return nullptr;
}

int32 UOutfitManagerComponent::GetCurrentIndexInCategory(EClothingCategory Category) const
{
	const FName CurrentName = GetEquippedItemName(Category);
	TArray<FClothingItemEntry> CategoryItems = GetItemsInCategory(Category);

	for (int32 i = 0; i < CategoryItems.Num(); ++i)
	{
		if (CategoryItems[i].ItemName == CurrentName)
		{
			return i;
		}
	}
	return 0;
}

void UOutfitManagerComponent::SetItemVisibility(FName ItemName, bool bVisible)
{
	FClothingItemEntry* Item = FindItem(ItemName);
	if (Item && Item->MeshRootComponent)
	{
		Item->MeshRootComponent->SetVisibility(bVisible, true);
	}
}
