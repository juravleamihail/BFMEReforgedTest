// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Kismet/GameplayStatics.h>
#include "SelectionInterface.h"
#include "HUDCanvas.generated.h"

class ARTS_PlayerController;

/**
 * 
 */
UCLASS()
class BFMEUNREALPROJECT_API AHUDCanvas : public AHUD
{
	GENERATED_BODY()
	
public:
	void StartSelection();
	void StopSelection();

protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

public:
	ARTS_PlayerController* AsRTSPlayerController;
	FVector2D PointA, PointB;
	bool IsDrawing = false;
	TArray<AActor*> SelectionOfActors;
	bool IsMarquee = false;
};
