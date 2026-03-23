// Copyright Epic Games, Inc. All Rights Reserved.

#include "OutfitManagerComponent.h"
#include "PoCCloThang.h"

UOutfitManagerComponent::UOutfitManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UOutfitManagerComponent::ToggleOutfit(FName OutfitName)
{
	FOutfitEntry* Entry = FindOutfitEntry(OutfitName);
	if (!Entry)
	{
		UE_LOG(LogPoCCloThang, Warning, TEXT("OutfitManager: Outfit '%s' not found."), *OutfitName.ToString());
		return false;
	}

	const bool bNewVisibility = !Entry->bIsVisible;
	SetOutfitVisible(OutfitName, bNewVisibility);
	return bNewVisibility;
}

bool UOutfitManagerComponent::SetOutfitVisible(FName OutfitName, bool bVisible)
{
	FOutfitEntry* Entry = FindOutfitEntry(OutfitName);
	if (!Entry)
	{
		UE_LOG(LogPoCCloThang, Warning, TEXT("OutfitManager: Outfit '%s' not found."), *OutfitName.ToString());
		return false;
	}

	if (!Entry->OutfitRootComponent)
	{
		UE_LOG(LogPoCCloThang, Warning, TEXT("OutfitManager: Outfit '%s' has no root component assigned."), *OutfitName.ToString());
		return false;
	}

	Entry->bIsVisible = bVisible;
	Entry->OutfitRootComponent->SetVisibility(bVisible, /*bPropagateToChildren=*/ true);

	OnOutfitVisibilityChanged.Broadcast(OutfitName, bVisible);

	UE_LOG(LogPoCCloThang, Log, TEXT("OutfitManager: Outfit '%s' visibility set to %s."),
		*OutfitName.ToString(), bVisible ? TEXT("ON") : TEXT("OFF"));

	return true;
}

bool UOutfitManagerComponent::IsOutfitVisible(FName OutfitName) const
{
	const FOutfitEntry* Entry = FindOutfitEntry(OutfitName);
	if (!Entry)
	{
		return false;
	}
	return Entry->bIsVisible;
}

FOutfitEntry* UOutfitManagerComponent::FindOutfitEntry(FName OutfitName)
{
	for (FOutfitEntry& Entry : Outfits)
	{
		if (Entry.OutfitName == OutfitName)
		{
			return &Entry;
		}
	}
	return nullptr;
}

const FOutfitEntry* UOutfitManagerComponent::FindOutfitEntry(FName OutfitName) const
{
	for (const FOutfitEntry& Entry : Outfits)
	{
		if (Entry.OutfitName == OutfitName)
		{
			return &Entry;
		}
	}
	return nullptr;
}
