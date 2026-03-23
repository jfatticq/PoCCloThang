// Copyright Epic Games, Inc. All Rights Reserved.

#include "OutfitSelectionWidget.h"
#include "OutfitManagerComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "PoCCloThang.h"

const FName UOutfitSelectionWidget::Blouse01Name = FName(TEXT("Blouse01"));
const FName UOutfitSelectionWidget::LongSkirt01Name = FName(TEXT("LongSkirt01"));

void UOutfitSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Find the OutfitManagerComponent in the world (on Tandy or any actor that has one)
	CacheOutfitManager();

	if (Blouse01)
	{
		Blouse01->OnClicked.AddDynamic(this, &UOutfitSelectionWidget::OnBlouse01Clicked);
	}

	if (LongSkirt01)
	{
		LongSkirt01->OnClicked.AddDynamic(this, &UOutfitSelectionWidget::OnLongSkirt01Clicked);
	}

	// Set initial status text
	UpdateStatusText(Blouse01Name, Blouse01Text);
	UpdateStatusText(LongSkirt01Name, LongSkirt01Text);
}

void UOutfitSelectionWidget::OnBlouse01Clicked()
{
	ToggleOutfit(Blouse01Name, Blouse01Text);
}

void UOutfitSelectionWidget::OnLongSkirt01Clicked()
{
	ToggleOutfit(LongSkirt01Name, LongSkirt01Text);
}

void UOutfitSelectionWidget::ToggleOutfit(FName OutfitName, UTextBlock* StatusText)
{
	UOutfitManagerComponent* Manager = GetOutfitManager();
	if (!Manager)
	{
		UE_LOG(LogPoCCloThang, Warning, TEXT("OutfitSelectionWidget: No OutfitManagerComponent found in the world."));
		return;
	}

	Manager->ToggleOutfit(OutfitName);
	UpdateStatusText(OutfitName, StatusText);
}

void UOutfitSelectionWidget::CacheOutfitManager()
{
	// Search all actors in the world for one with an OutfitManagerComponent
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
			UE_LOG(LogPoCCloThang, Log, TEXT("OutfitSelectionWidget: Found OutfitManagerComponent on '%s'."), *Actor->GetName());
			return;
		}
	}

	UE_LOG(LogPoCCloThang, Warning, TEXT("OutfitSelectionWidget: No actor with OutfitManagerComponent found in the world."));
}

UOutfitManagerComponent* UOutfitSelectionWidget::GetOutfitManager() const
{
	return CachedOutfitManager;
}

void UOutfitSelectionWidget::UpdateStatusText(FName OutfitName, UTextBlock* StatusText)
{
	if (!StatusText)
	{
		return;
	}

	UOutfitManagerComponent* Manager = GetOutfitManager();
	if (!Manager)
	{
		StatusText->SetText(FText::FromString(TEXT("--")));
		return;
	}

	const bool bVisible = Manager->IsOutfitVisible(OutfitName);
	StatusText->SetText(FText::FromString(bVisible ? TEXT("ON") : TEXT("OFF")));
}
