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
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void AIStopMovement();

private:
	void GetUnitsFromCurrentLevel();
	AUnitBase* GetFarthestUnit(FVector& Location, TArray<AUnitBase*>& Units);
	AUnitBase* GetNextUnitByPrioritization(TArray<AUnitBase*>& Units);

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<AUnitBase*> UnitSelection;
	UPROPERTY(BlueprintReadOnly)
	TArray<AUnitBase*> UnitsAtStart;
	UPROPERTY(EditAnywhere)
	float UnitSpacing = 32.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

private:
	AHUDCanvas* HUDCanvas;
	bool bInputPressed; // Input is bring pressed
	float FollowTime; // For how long it has been pressed
	const int32 MAX_PRIORITY_NUMBER = 1;
};
