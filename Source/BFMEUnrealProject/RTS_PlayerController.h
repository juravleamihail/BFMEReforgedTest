// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <Delegates/Delegate.h>
#include <Components/PrimitiveComponent.h>
#include <Kismet/GameplayStatics.h>
#include <../Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h>
#include "RTS_PlayerController.generated.h"

class AUnitBase;
class AHUDCanvas;

/**
 * 
 */
UCLASS()
class BFMEUNREALPROJECT_API ARTS_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void AddUnitToSelection(AUnitBase* UnitBase);
	UFUNCTION(BlueprintCallable)
	void ClearUnitSelection();

	void OnLeftClick_Pressed();
	void OnLeftClicked_Released();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void AIStopMovement();

private:
	void GetUnitsFromCurrentLevel();
	AUnitBase* GetClosestUnit(FVector& Location);

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<AUnitBase*> UnitSelection;
	UPROPERTY(BlueprintReadOnly)
	TArray<AUnitBase*> UnitsAtStart;
	UPROPERTY(EditAnywhere)
	float UnitSpacing = 32.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

private:
	AHUDCanvas* HUDCanvas;
	bool bInputPressed; // Input is bring pressed
};
