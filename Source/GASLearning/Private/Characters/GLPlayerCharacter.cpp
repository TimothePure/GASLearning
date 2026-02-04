// Fill out your copyright notice in the Description page of Project Settings.


#include "GASLearning/Public/Characters/GLPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/GLPlayerState.h"

AGLPlayerCharacter::AGLPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 600.f;
	SpringArm->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	Tags.Add(GLTags::Player);
}

UAbilitySystemComponent* AGLPlayerCharacter::GetAbilitySystemComponent() const
{
	AGLPlayerState* GLPlayerState = Cast<AGLPlayerState>(GetPlayerState());
	if (!IsValid(GLPlayerState)) return nullptr;
	
	return GLPlayerState->GetAbilitySystemComponent();
}

UAttributeSet* AGLPlayerCharacter::GetAttributeSet() const
{
	AGLPlayerState* GLPlayerState = Cast<AGLPlayerState>(GetPlayerState());
	if (!IsValid(GLPlayerState)) return nullptr;
	
	return GLPlayerState->GetAttributeSet();
}

void AGLPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!IsValid(GetAbilitySystemComponent()) || !HasAuthority()) return;
	
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	GiveStartupAbilities();
	InitializeAttributes();
	
	UGLAttributeSet* GLAttributeSet = Cast<UGLAttributeSet>(GetAttributeSet());
	if (IsValid(GLAttributeSet))
	{
		GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GLAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
	}
}

void AGLPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	UGLAttributeSet* GLAttributeSet = Cast<UGLAttributeSet>(GetAttributeSet());
	if (IsValid(GLAttributeSet))
	{
		GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GLAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
	}
}

