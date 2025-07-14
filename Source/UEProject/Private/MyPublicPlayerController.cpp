// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPublicPlayerController.h"

AMyPublicPlayerController::AMyPublicPlayerController(){

    PrimaryActorTick.bCanEverTick = true;// 每帧调用Tick()函数




    // UE_LOG(LogTemp, Warning, TEXT("MyPublicPlayerController"));
}


//加载 Widget class
void AMyPublicPlayerController::BeginPlay() {
	Super::BeginPlay();
    // UE_LOG(LogTemp, Warning, TEXT("MyPublicPlayerController BeginPlay"));

    bShowMouseCursor = true;// show mouse cursor
    DefaultMouseCursor = EMouseCursor::Crosshairs;//  设置鼠标光标为十字



	// 这是使用 MyDelegateManager 来注册
	// UMyDelegateManager* DelegateManager = UMyDelegateManager::GetInstance(GetWorld());
    // if (DelegateManager)
    // {
    //     DelegateManager->RegisterMultiDelegate(this, FName("OnDataReceived"));
    //     GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("RegisterMultiDelegate successful"));
    // }
    // else
    // {
    //     GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to get DelegateManager"));
    // }
	
	//  这个是 使用 MyPublicGameInstance 来注册
	if (UMyPublicGameInstance* GameInstance = Cast<UMyPublicGameInstance>(GetWorld()->GetGameInstance()))
    {
        UMyDelegateManagerOfInstance* DelegateManager = GameInstance->GetDelegateManager();
        if (DelegateManager)
        {
            DelegateManager->RegisterMultiDelegate(this, FName("OnDataReceived"));
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("MyPublicPlayerController Registered Delegate"));
        }
    }





}



void AMyPublicPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // UE_LOG(LogTemp, Warning, TEXT("MyPublicPlayerController Tick"));
    PerformRaycast();
}






void AMyPublicPlayerController::PerformRaycast(){
	// 获取玩家控制器
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();// 
	if(!PlayerController){
		return;
	}

	float MouseX; // 获取鼠标位置
	float MouseY; // 获取鼠标位置

	//  MouseX = PlayerController->InputComponent->GetAxisValue("YawAxis");
	//  MouseY = PlayerController->InputComponent->GetAxisValue("PitchAxis");


	if (!PlayerController->GetMousePosition(MouseX, MouseY)) {// 获取鼠标光标在游戏视口
		// 若鼠标未在窗口内，用视口中心替代
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		MouseX = ViewportSize.X * 0.5f;
		MouseY = ViewportSize.Y * 0.5f;
	}
 
	FVector WordLocation;// 将2D屏幕坐标转换为3D世界空间的射线
	FVector WorldDirection; // 从视点发射的射线方向向量（已标准化为单位向量）
	// 将屏幕坐标转换成世界空间射线
	if(PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WordLocation, WorldDirection)){// 将2D屏幕坐标转换为3D世界空间的射线
		// 射线长度
		FVector Start = WordLocation;// 射线起点
		FVector End = Start + WorldDirection * 10000.f;// 射线终点

		// 射线参数
		FHitResult HitResult; // 射线参数
		FCollisionQueryParams QueryParams; // 射线参数
		// 设置碰撞检测参数
		QueryParams.bTraceComplex = true; // 设置碰撞检测参数 ; bTraceComplex : 是否检测复杂碰撞体
		QueryParams.AddIgnoredActor(this); // 设置碰撞检测参数 ; AddIgnoredActor : 忽略检测的Actor
		

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility,// 设置碰撞检测参数 ; ECC_Visibility : 可见性通道
			QueryParams // 设置碰撞检测参数 ; QueryParams : 碰撞检测参数
		);

 		if (bHit)
        {
            // 处理击中物体
			AActor* HitActor = HitResult.GetActor();
			if(HitActor){
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,  FString::Printf(TEXT("Hit Actor: %s"), *HitActor->GetName()));
			
			
			
				// UMyDelegateManager* DelegateManager = UMyDelegateManager::GetInstance();
				// if (DelegateManager)
				// {
				// 	DelegateManager->TriggerMultiData(TEXT("DataFromController"));
				// }
			

			
			
			}

        }
	
	}


}


void AMyPublicPlayerController::OnDataReceived(FString Data)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("OtherModule received or instance: %s"), *Data));
}