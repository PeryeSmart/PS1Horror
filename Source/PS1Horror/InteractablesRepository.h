// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "InteractablesRepository.generated.h"

USTRUCT()
struct FInteractables : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
		FString id;

	UPROPERTY()
		FString name;

	UPROPERTY()
		bool choice;

	UPROPERTY()
		TArray<FString> dialog;

	UPROPERTY()
		FString choice_dialog;

	UPROPERTY()
		TArray<FString> choices;

	UPROPERTY()
		FString confirmation_dialog;

};

UCLASS()
class PS1HORROR_API AInteractablesRepository : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractablesRepository();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
