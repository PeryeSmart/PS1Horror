// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "WeaponRepository.generated.h"

USTRUCT()
struct FWeapon : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		FString id;

	UPROPERTY(EditAnywhere)
		class USkeletalMesh* skeletal_mesh;

	UPROPERTY(EditAnywhere)
		class UStaticMesh* mesh;

	UPROPERTY(EditAnywhere)
		class USoundBase* fire_sound;

	UPROPERTY(EditAnywhere)
		class USoundBase* empty_sound;

	UPROPERTY(EditAnywhere)
		class UAnimSequence* fire_anim;

	UPROPERTY(EditAnywhere)
		class UAnimSequence* char_fire_anim;

	UPROPERTY(EditAnywhere)
		int mag_capacity;

	UPROPERTY(EditAnywhere)
		int mag_ammo_count;

	UPROPERTY(EditAnywhere)
		FName socket_name;

	UPROPERTY(EditAnywhere)
		FName name;
};

UCLASS()
class PS1HORROR_API AWeaponRepository : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponRepository();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
