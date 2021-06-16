// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraCapture.h"

// Sets default values
ACameraCapture::ACameraCapture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture Component"));
	RootComponent = CameraComp;
	SceneCapture->SetupAttachment(CameraComp);
}

// Called when the game starts or when spawned
void ACameraCapture::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraCapture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->GetFirstPlayerController()->GetViewTarget() == this)
	{
		SceneCapture->bCaptureEveryFrame = true;
	}
	else
	{
		SceneCapture->bCaptureEveryFrame = false;
	}
}

void ACameraCapture::SetCameraCaptureInUse(bool _IsCameraCaptureInUse) 
{
	IsCameraCaptureInUse = _IsCameraCaptureInUse;
}
