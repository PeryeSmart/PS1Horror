// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "CameraCapture.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "CameraTrigger.generated.h"

UENUM(BlueprintType)
enum class AxisEnum : uint8 
{
	X       UMETA(DisplayName = " X (Roll)"),
	Y       UMETA(DisplayName = " Y (Pitch)"),
	Z       UMETA(DisplayName = " Z (Yaw)"),
	XY      UMETA(DisplayName = " X (Roll) And Y (Pitch)"),
	XZ      UMETA(DisplayName = " X (Roll) And Z (Yaw)"),
	YZ      UMETA(DisplayName = " Y (Pitch) And Z (Yaw)"),
	XYZ     UMETA(DisplayName = " X (Roll), Y (Pitch) And Z (Yaw)"),
};

UCLASS()
class PS1HORROR_API ACameraTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraTrigger();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnColliderOverlapBegin(
		UPrimitiveComponent* Comp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherIndex, 
		bool bFromSweep, 
		const FHitResult & SweepResult);

	void ToggleCamera();
	void UpdateCamera();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Actor")
		ACameraCapture * CameraRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Actor")
		bool IsBlendingEnable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Actor")
		float BlendingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Actor")
		TEnumAsByte<EViewTargetBlendFunction> BlendingFunction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Actor")
		float BlendingExponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Actor")
		bool IsCameraActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Actor")
		bool EnableTracking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Actor")
		bool EnableFollowing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Actor")
		AxisEnum FollowingAxisEnum;

private:

	FVector PlayerActorLocation;
	FVector CameraLocation;
	FRotator CameraRotation;
	AActor* HittingActor;

	UPROPERTY(VisibleAnywhere, Category = "Root")
		USceneComponent* CameraTriggerRoot;
	UPROPERTY(VisibleAnywhere, Category = "Camera Trigger")
		UBoxComponent* CameraTrigger;

};
