// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <Delegates/Delegate.h>
#include <Components/PrimitiveComponent.h>
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

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<AUnitBase*> UnitSelection;

private:
	AHUDCanvas* HUDCanvas;
};
