// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemRepository.generated.h"

UENUM()
enum class EItemType : uint8
{
	Consumable,
	Weapon,
	Ammo,
	KeyItem,
};

UENUM()
enum class EItemCommands : uint8 
{
	Equip,
	Use,
	Combine,
	Examine,
};

USTRUCT(BlueprintType)
struct FItem : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
		FString id;

	UPROPERTY(EditAnywhere)
		FString name;

	UPROPERTY(EditAnywhere)
		FString description;

	UPROPERTY(EditAnywhere)
		EItemType type;

	UPROPERTY(EditAnywhere)
		bool is_stackable;

	UPROPERTY(EditAnywhere)
		int amount;

	UPROPERTY(EditAnywhere)
		class UStaticMesh* mesh;

	UPROPERTY(EditAnywhere)
		TArray<FString> commands;

	UPROPERTY(EditAnywhere)
		TArray<EItemCommands> commands_index;
};

UCLASS()
class PS1HORROR_API AItemRepository : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemRepository();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
