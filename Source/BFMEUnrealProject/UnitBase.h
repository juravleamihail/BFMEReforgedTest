// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/DecalComponent.h"
#include "UnitBase.generated.h"

UCLASS()
class BFMEUNREALPROJECT_API AUnitBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnitBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Select(bool isSelected);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDecalComponent* Decal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSelected;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FName GroupName;

};
