// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPublicPlayerController.h"
#include "MyPublicPawn.h"

//#include "Engine/World.h"
//#include "CollisionQueryParams.h"
//#include "DrawDebugHelpers.h" // 调试用


void AMyPublicPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	// 绑定鼠标左键
	//InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AMyPublicPlayerController::HandleMouseClick);

	UE_LOG(LogTemp, Warning, TEXT("AMyPublicPlayerController SetupInputComponent LeftMouseClick "))


	InputComponent->BindAction("WheelUp", IE_Pressed, this, &AMyPublicPlayerController::WheelUpFunction);
	InputComponent->BindAction("WheelDown", IE_Pressed, this, &AMyPublicPlayerController::WheelDownFunction);



}



void AMyPublicPlayerController::WheelUpFunction() {
	if (GetPawn()) {
		AMyPublicPawn* MyCameraPawn = Cast<AMyPublicPawn>(GetPawn());
		if (MyCameraPawn) {
			MyCameraPawn->Zoom(0, 10);
		}
	}
}
 
void AMyPublicPlayerController::WheelDownFunction() {
	if (GetPawn()) {
		AMyPublicPawn* MyCameraPawn = Cast<AMyPublicPawn>(GetPawn());
		if (MyCameraPawn) {
			MyCameraPawn->Zoom(1, 10);
		}
	}
}

