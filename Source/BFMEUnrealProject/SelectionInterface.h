// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BFMEUNREALPROJECT_API ISelectionInterface
{
	GENERATED_BODY()

	void StartSelection();
	void StopSelection();

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
