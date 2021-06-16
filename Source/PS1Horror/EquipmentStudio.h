// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "EquipmentStudio.generated.h"

UCLASS()
class PS1HORROR_API AEquipmentStudio : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipmentStudio();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetWeaponMesh(class UStaticMesh* _WeaponMesh);
	void SpinWeapon(bool _IsSpinning);

protected:

	UPROPERTY(EditAnywhere, Category = "Weapon Rotation")
		float WeaponRotationRate;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* StudioRoot;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Floor;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Top;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Wall_1;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Wall_2;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Wall_3;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Wall_4;
	UPROPERTY(EditAnywhere)
		class UCameraComponent* StudioCamera;
	UPROPERTY(EditAnywhere)
		class USceneCaptureComponent2D* StudioSceneCapture;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* WeaponMesh;
};
