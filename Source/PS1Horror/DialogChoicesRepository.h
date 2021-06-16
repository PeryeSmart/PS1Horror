// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DialogChoicesRepository.generated.h"

USTRUCT()
struct FDialogChoices : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		FString id;

	UPROPERTY(EditAnywhere)
		FString name;

	UPROPERTY(EditAnywhere)
		FString dialog;

	UPROPERTY(EditAnywhere)
		FString confirmation;

	UPROPERTY(EditAnywhere)
		TArray<FString> choices;
};

USTRUCT()
struct FDialogs : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		FString id;

	UPROPERTY(EditAnywhere)
		FString name;

	UPROPERTY(EditAnywhere)
		bool choice;

	UPROPERTY(EditAnywhere)
		TArray<FString> dialog;

	UPROPERTY(EditAnywhere)
		FString choice_dialog;

	UPROPERTY(EditAnywhere)
		TArray<FString> choices;

	UPROPERTY(EditAnywhere)
		FString confirmation_dialog;
};

UCLASS()
class PS1HORROR_API ADialogChoicesRepository : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogChoicesRepository();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
