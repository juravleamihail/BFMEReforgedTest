// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_PlayerController.h"
#include "UnitBase.h"
#include "HUDCanvas.h"
#include <../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include <AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>

void ARTS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDCanvas = Cast<AHUDCanvas>(GetHUD());
	GetUnitsFromCurrentLevel();
}

void ARTS_PlayerController::GetUnitsFromCurrentLevel()
{
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);
	for (AActor* Actor : AllActors)
	{
		AUnitBase* Unit = Cast<AUnitBase>(Actor);
		if (Unit)
		{
			UnitsAtStart.Add(Unit);
		}
	}
}

void ARTS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARTS_PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ARTS_PlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ARTS_PlayerController::OnLeftClick_Pressed);
	InputComponent->BindAction("LeftClick", IE_Released, this, &ARTS_PlayerController::OnLeftClicked_Released);
}

void ARTS_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bInputPressed)
	{
		FollowTime += DeltaTime;

		// Look for the touch location
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;

		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;

		// Direct the Pawn towards that location
		APawn* const MyPawn = GetPawn();
		if (MyPawn)
		{
			FVector WorldDirection = (HitLocation - MyPawn->GetActorLocation()).GetSafeNormal();
			MyPawn->AddMovementInput(WorldDirection, 1.f, false);
		}
	}
	else
	{
		FollowTime = 0.f;
	}
}

void ARTS_PlayerController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	bInputPressed = true;
	// Just in case the character was moving because of a previous short press we stop it
	StopMovement();
}

AUnitBase* ARTS_PlayerController::GetFarthestUnit(FVector& Location, TArray<AUnitBase*>& Units)
{
	float FarthestDistance = 0;
	AUnitBase* FarthestUnit = nullptr;

	for (AUnitBase* Unit : Units)
	{
		float Distance = FVector::Distance(Unit->GetActorLocation(), Location);
		if (Distance > FarthestDistance)
		{
			FarthestDistance = Distance;
			FarthestUnit = Unit;
		}
	}

	Units.Remove(FarthestUnit);
	return FarthestUnit;
}

void ARTS_PlayerController::AIStopMovement()
{
	for (auto Unit : UnitSelection)
	{
		if (!Unit->Controller)
		{
			return;
		}

		Unit->GetController()->StopMovement();
	}
}

void ARTS_PlayerController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	bInputPressed = false;

	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);

		//TODO: make this a method
		const int NumRows = FMath::CeilToInt(FMath::Sqrt(UnitSelection.Num()));
		const int NumCols = FMath::CeilToInt(UnitSelection.Num() / static_cast<float>(NumRows));

		FVector GridCenter = Hit.Location;
		auto Units = UnitSelection;

		for (int i = 0; i < NumRows; i++)
		{
			for (int j = 0; j < NumCols; j++)
			{
				FVector UnitPosition = FVector(GridCenter.X + (j - NumCols / 2) * UnitSpacing, GridCenter.Y + (i - NumRows / 2) * UnitSpacing, Hit.Location.Z);
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, UnitPosition, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);

				if (Units.IsEmpty())
				{
					return;
				}

				UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetFarthestUnit(UnitPosition, Units)->Controller, UnitPosition);
			}
		}
	}
}

void ARTS_PlayerController::AddUnitToSelection(AUnitBase* UnitBase)
{
	UnitSelection.AddUnique(UnitBase);
	UnitBase->Select(true);
}

void ARTS_PlayerController::ClearUnitSelection()
{
	for (auto UnitSelected : UnitSelection)
	{
		UnitSelected->Select(false);
	}
	UnitSelection.Empty();
}

void ARTS_PlayerController::OnLeftClick_Pressed()
{
	HUDCanvas->StartSelection();
	bShowMouseCursor = false;

	FHitResult HitResult;
	if (GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel11), true, HitResult))
	{
		ClearUnitSelection();
	}
}

void ARTS_PlayerController::OnLeftClicked_Released()
{
	HUDCanvas->StopSelection();
	bShowMouseCursor = true;
}