// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"

// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMeshComponent->SetupAttachment(ItemRoot);

}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	if (!ItemDescription.IsEmpty()) 
	{
		ItemDescription.ToString().ParseIntoArray(DelimitedItemDescription, TEXT(";"), true);
	}
}

// Called every frame
void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollectible::Interact()
{
	if (InteractCounter == GetItemDescription().Num()) 
	{
		InteractCounter = 0;
	}
	else 
	{
		InteractCounter++;
	}
}

bool ACollectible::GetIsFocusEnable()
{
	return IsFocusEnable;
}

void ACollectible::DestroyItem() 
{
	Destroy();
}

void ACollectible::SetItemName(FString _ItemName)
{
	if (!_ItemName.IsEmpty()) 
	{
		ItemName = _ItemName;
	}
}

void ACollectible::SetItemDescription(FText _ItemDescription)
{
	if (!_ItemDescription.IsEmpty())
	{
		ItemDescription = _ItemDescription;
	}
}

