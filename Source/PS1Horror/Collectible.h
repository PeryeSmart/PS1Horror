// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Collectible.generated.h"

UCLASS()
class PS1HORROR_API ACollectible : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectible();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;
	virtual bool GetIsFocusEnable() override;
	virtual FString GetInteractableName() override { return ItemName; };
	virtual FText GetInteractableDialog() override { return ItemDialog; };
	virtual FString GetInteractableID() override { return InteractableID; };

	TArray<FString> GetItemDescription() { return DelimitedItemDescription; };
	FString GetItemName() { return ItemName; };
	UStaticMeshComponent* GetItemMeshComponent() { return ItemMeshComponent; };
	void SetItemName(FString _ItemName);
	void SetItemDescription(FText _ItemDescription);
	void DestroyItem();

public : 

	UPROPERTY(EditAnywhere, Category = "Item Description")
		FString InteractableID;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	

private:

	TArray<FString> DelimitedItemDescription;
	int32 InteractCounter = 0;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* ItemRoot;

	UPROPERTY(EditAnywhere, Category = "Item Description")
		bool IsFocusEnable;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ItemMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Item Description")
		FString ItemName;

	UPROPERTY(EditAnywhere, Category = "Item Description")
		FText ItemDescription;

	UPROPERTY(EditAnywhere, Category = "Item Description")
		FText ItemDialog;
};
