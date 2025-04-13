// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformerChar.h"
#include "King.generated.h"


class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogKing, Log, All);

UCLASS()
class TOWERCLIMBER_API AKing : public APlatformerChar
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

public:
	AKing();

private:
	virtual void SetupPlayerInputComponent(UInputComponent*) override;
	virtual void Tick(float DeltaSeconds) override;

	void UpdateControllerRotation() const;
};
