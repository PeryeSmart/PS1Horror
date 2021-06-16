// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "CameraCapture.generated.h"

UCLASS()
class PS1HORROR_API ACameraCapture : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraCapture();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetCameraCaptureInUse(bool _IsCameraCaptureInUse);
	//ACameraActor* GetCameraRef() { return CameraRef; };

private:
	bool IsCameraCaptureInUse = false;
	UPROPERTY(EditAnywhere, Category = "Camera Actor")
		UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, Category = "Camera Actor")
		USceneCaptureComponent2D* SceneCapture;
};
