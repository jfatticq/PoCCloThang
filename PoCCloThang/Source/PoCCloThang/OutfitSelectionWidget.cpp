// Copyright Epic Games, Inc. All Rights Reserved.

#include "OutfitSelectionWidget.h"
#include "OutfitManagerComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "PoCCloThang.h"

const FName UOutfitSelectionWidget::Blouse01Name = FName(TEXT("Blouse01"));
const FName UOutfitSelectionWidget::LongSkirt01Name = FName(TEXT("LongSkirt01"));

void UOutfitSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
		UE_LOG(LogPoCCloThang, Warning, TEXT("OutfitSelectionWidget: No OutfitManagerComponent found on the player pawn."));
		return;
	}

	Manager->ToggleOutfit(OutfitName);
	UpdateStatusText(OutfitName, StatusText);
}

UOutfitManagerComponent* UOutfitSelectionWidget::GetOutfitManager() const
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC)
	{
		return nullptr;
	}

	APawn* Pawn = PC->GetPawn();
	if (!Pawn)
	{
		return nullptr;
	}

	return Pawn->FindComponentByClass<UOutfitManagerComponent>();
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
