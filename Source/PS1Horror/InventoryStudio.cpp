// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryStudio.h"

// Sets default valuesw
AInventoryStudio::AInventoryStudio()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StudioRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Studio Root Component"));
	Floor = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Studio Floor"));
	Top = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Studio Ceiling"));
	Wall_1 = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Studio Wall 1"));
	Wall_2 = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Studio Wall 2"));
	Wall_3 = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Studio Wall 3"));
	Wall_4 = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Studio Wall 4"));
	StudioCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Studio Camera Component"));
	StudioSceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Studio Scene Capture Component"));
	//WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh Component"));

	StudioRoot->SetupAttachment(RootComponent);

	Floor->SetupAttachment(StudioRoot);
	Top->SetupAttachment(StudioRoot);
	Wall_1->SetupAttachment(StudioRoot);
	Wall_2->SetupAttachment(StudioRoot);
	Wall_3->SetupAttachment(StudioRoot);
	Wall_4->SetupAttachment(StudioRoot);
	//WeaponMesh->SetupAttachment(StudioRoot);
	StudioSceneCapture->SetupAttachment(StudioCamera);
	StudioCamera->SetupAttachment(StudioRoot);

}

// Called when the game starts or when spawned
void AInventoryStudio::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryStudio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

