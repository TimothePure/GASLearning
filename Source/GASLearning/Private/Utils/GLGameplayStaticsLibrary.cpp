// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/GLGameplayStaticsLibrary.h"

#include "Characters/GLBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LevelInstance/LevelInstanceTypes.h"

EHitDirection UGLGameplayStaticsLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);
	if (Dot < -0.5f)
	{
		return EHitDirection::Back;
	}
	if (Dot < 0.5f)
	{
		// Either left or right
		const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
		if (Cross.Z < 0.f)
		{
			return EHitDirection::Left;
		} 
		return EHitDirection::Right;
	}
	return EHitDirection::Front;
}

FName UGLGameplayStaticsLibrary::GetHitDirectionName(const EHitDirection& HitDirection)
{
	switch (HitDirection)
	{
		case EHitDirection::Back: return FName("Back");
		case EHitDirection::Left: return FName("Left");
		case EHitDirection::Right: return FName("Right");
		case EHitDirection::Front: return FName("Front");
		default: return FName("None");
	}
}

FClosestActorWithTagResult UGLGameplayStaticsLibrary::FindClosestActorWithTag(const UObject* WorldContextObject, const FVector& Origin, const FName& Tag)
{
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(WorldContextObject, Tag, ActorsWithTag);
	
	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr; 

	for (AActor* Actor : ActorsWithTag)
	{
		if (!IsValid(Actor)) continue;
		AGLBaseCharacter* BaseCharacter = Cast<AGLBaseCharacter>(Actor);
		if (!IsValid(BaseCharacter) || !BaseCharacter->IsAlive()) continue;
		
		const float Distance = FVector::Dist(Origin, BaseCharacter->GetActorLocation());
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestActor = Actor;
		}
	}
	
	return FClosestActorWithTagResult { ClosestActor, ClosestDistance };
}