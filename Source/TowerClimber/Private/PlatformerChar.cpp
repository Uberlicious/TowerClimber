// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerChar.h"
#include "GameFramework/CharacterMovementComponent.h"

APlatformerChar::APlatformerChar()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();

	Movement->GravityScale = 3.f;
	Movement->JumpZVelocity = 1100.f;
	Movement->AirControl = 1.f;
	Movement->bUseFlatBaseForFloorChecks = true;
}
