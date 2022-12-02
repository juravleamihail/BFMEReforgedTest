// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_PlayerController.h"
#include "UnitBase.h"
#include "HUDCanvas.h"

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

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ARTS_PlayerController::OnLeftClick_Pressed);
	InputComponent->BindAction("LeftClick", IE_Released, this, &ARTS_PlayerController::OnLeftClicked_Released);
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