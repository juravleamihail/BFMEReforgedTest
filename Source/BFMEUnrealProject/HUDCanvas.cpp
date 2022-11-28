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
		AsRTSPlayerController->ClearUnitSelection();

		for (auto SelectedActor : SelectionOfActors)
		{
			AUnitBase* Unit = Cast<AUnitBase>(SelectedActor);

			if (Unit)
			{
				AsRTSPlayerController->AddUnitToSelection(Unit);
			}
		}
	}
}