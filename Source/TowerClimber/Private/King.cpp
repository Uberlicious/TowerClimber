// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

AKing::AKing()
{
   SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
   SpringArmComponent->SetupAttachment(GetCapsuleComponent());
   SpringArmComponent->TargetArmLength = 600.f;
   SpringArmComponent->SetWorldRotation(FRotator(-10, -90, 0));
   
   CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
   CameraComponent->SetupAttachment(SpringArmComponent);
   CameraComponent->PostProcessSettings.bOverride_AutoExposureMethod = true;
   CameraComponent->PostProcessSettings.AutoExposureMethod = AEM_Manual;
   CameraComponent->PostProcessSettings.bOverride_AutoExposureBias = true;
   CameraComponent->PostProcessSettings.AutoExposureBias = 10.2;
}

void AKing::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
   APlayerController* PlayerController = Cast<APlayerController>(GetController());
	 
   UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	    
   Subsystem->ClearAllMappings();
   Subsystem->AddMappingContext(InputMapping, 0);
   
   if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
   {
      EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AKing::Jump);
      EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKing::Move);
      UE_LOG(LogTemp, Warning, TEXT("Enhanced input component found '%s'"), *GetNameSafe(EnhancedInputComponent));
   }
}

void AKing::Tick(float DeltaSeconds)
{
   Super::Tick(DeltaSeconds);
   
   UpdateControllerRotation(); 
}

void AKing::UpdateControllerRotation() const
{
   UCharacterMovementComponent* MovementComponent = GetCharacterMovement();

   if (MovementComponent == nullptr) return;

   FVector Velocity = MovementComponent->Velocity;

   APlayerController* PlayerController = Cast<APlayerController>(GetController());
   if (PlayerController == nullptr) return;
   
   if (Velocity.X > 0)
   {
      PlayerController->SetControlRotation(FRotator(0, 0, 0));
      UE_LOG(LogTemp, Warning, TEXT("Moving more than 0"))
   } else if (Velocity.X < 0)
   {
      PlayerController->SetControlRotation(FRotator(0, 180, 0));
      UE_LOG(LogTemp, Warning, TEXT("Moving less than 0"))
   }
}

void AKing::Move(const FInputActionValue& Value)
{
      const float MoveValue = Value.Get<float>();
      if (Controller != nullptr)
      {
         AddMovementInput(FVector(1, 0, 0), MoveValue);
      }
}
