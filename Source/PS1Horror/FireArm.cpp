// Fill out your copyright notice in the Description page of Project Settings.


#include "FireArm.h"

// Sets default values
AFireArm::AFireArm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(WeaponRoot);
}

// Called when the game starts or when spawned
void AFireArm::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireArm::FireWeapon(UAnimInstance* AnimInstance)
{
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireAnimation != nullptr)
	{
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

