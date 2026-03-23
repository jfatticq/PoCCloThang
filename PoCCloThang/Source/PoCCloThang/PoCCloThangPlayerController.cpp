// Copyright Epic Games, Inc. All Rights Reserved.


#include "PoCCloThangPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "PoCCloThang.h"
#include "Widgets/Input/SVirtualJoystick.h"

void APoCCloThangPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// spawn outfit selection widget on local player controllers
	if (IsLocalPlayerController() && OutfitSelectionWidgetClass)
	{
		OutfitSelectionWidget = CreateWidget<UUserWidget>(this, OutfitSelectionWidgetClass);
		if (OutfitSelectionWidget)
		{
			OutfitSelectionWidget->AddToPlayerScreen(1);
		}
		else
		{
			UE_LOG(LogPoCCloThang, Error, TEXT("Could not spawn outfit selection widget."));
		}
	}

	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogPoCCloThang, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void APoCCloThangPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

bool APoCCloThangPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}
