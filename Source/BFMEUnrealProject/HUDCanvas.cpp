// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDCanvas.h"
#include "RTS_PlayerController.h"
#include "UnitBase.h"

void AHUDCanvas::BeginPlay()
{
	Super::BeginPlay();

	AsRTSPlayerController = Cast<ARTS_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AHUDCanvas::StartSelection()
{
	AsRTSPlayerController->GetMousePosition(PointA.X, PointA.Y);
	IsDrawing = true;
}

void AHUDCanvas::DrawHUD()
{
	Super::DrawHUD();

	if (IsDrawing)
	{
		AsRTSPlayerController->GetMousePosition(PointB.X, PointB.Y);
		DrawRect(FLinearColor(0,1, 0.874), PointA.X, PointA.Y, PointB.X - PointA.X, PointB.Y - PointA.Y);
		IsMarquee = true;
		SelectionOfActors.Empty();
		GetActorsInSelectionRectangle(PointA, PointB, SelectionOfActors);
	}
}

void AHUDCanvas::StopSelection()
{
	IsDrawing = false;

	if (IsMarquee)
	{
		// Clear previous selection of units
		AsRTSPlayerController->ClearUnitSelection();
		SelectUnits();
	}
}

void AHUDCanvas::SelectUnits()
{
	TArray<FName> GroupsSelected;

	for (auto SelectedActor : SelectionOfActors)
	{
		AUnitBase* Unit = Cast<AUnitBase>(SelectedActor);

		if (Unit && Unit->GroupName != "")
		{
			GroupsSelected.Add(Unit->GroupName);
			UE_LOG(LogTemp, Error, TEXT(" ,Group name: %s, "), *Unit->GroupName.ToString());
		}
	}

	if (!GroupsSelected.IsEmpty())
	{
		for (AUnitBase* Unit : AsRTSPlayerController->UnitsAtStart)
		{
			if (GroupsSelected.Contains(Unit->GroupName))
			{
				AsRTSPlayerController->AddUnitToSelection(Unit);
			}
		}
	}
}
