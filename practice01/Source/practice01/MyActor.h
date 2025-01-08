// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class PRACTICE01_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void move();
	int32_t step();
	float Mydistance(FVector2D first, FVector2D second);

private:
	FVector2D	coordinate = { 0.f, 0.f };
	TArray<FVector2D> VectorArray;
	int32_t iCnt = 0;
	float fDistance = 0.f;
	int32 evCnt =0;
	float totDist =0.f;
};
