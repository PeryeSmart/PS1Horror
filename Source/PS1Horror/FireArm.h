// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInterface.h"
#include "GameFramework/Actor.h"
#include "FireArm.generated.h"

UCLASS()
class PS1HORROR_API AFireArm : public AActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireArm();
	virtual void FireWeapon(UAnimInstance* AnimInstance) override;
	virtual FName GetWeaponSocket() override { return WeaponSocketName; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Root Component")
		USceneComponent* WeaponRoot;
	UPROPERTY(EditAnywhere, Category = "Weapon Data")
		FName WeaponSocketName;
	UPROPERTY(EditAnywhere, Category = "Mesh")
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, Category = "Weapon Data")
		USoundBase* FireSound;
	UPROPERTY(EditAnywhere, Category = "Weapon Data")
		UAnimMontage* FireAnimation;
};
