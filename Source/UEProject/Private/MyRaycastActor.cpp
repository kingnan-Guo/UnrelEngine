// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRaycastActor.h"

// Sets default values
AMyRaycastActor::AMyRaycastActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyRaycastActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyRaycastActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PerformRaycast();
}


void AMyRaycastActor::PerformRaycast(){
	// 获取玩家控制器
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();// 
	if(!PlayerController){
		return;
	}

	float MouseX; // 获取鼠标位置
	float MouseY; // 获取鼠标位置

	//  MouseX = PlayerController->InputComponent->GetAxisValue("YawAxis");
	//  MouseY = PlayerController->InputComponent->GetAxisValue("PitchAxis");


    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        // 1. 启用光标显示
        PC->bShowMouseCursor = true;

        // 2. 设置输入模式为"游戏+UI"
        // FInputModeGameAndUI InputMode;
        // InputMode.SetHideCursorDuringCapture(false);  // 防止点击时隐藏光标
        // InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 不锁定鼠标到视口
        // PC->SetInputMode(InputMode);
    }


	if (!PlayerController->GetMousePosition(MouseX, MouseY)) {// 获取鼠标光标在游戏视口
		// 若鼠标未在窗口内，用视口中心替代
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		MouseX = ViewportSize.X * 0.5f;
		MouseY = ViewportSize.Y * 0.5f;
	}
	//  打印
	// UE_LOG(LogTemp, Warning, TEXT("MouseX: %f, MouseY: %f"), MouseX, MouseY);
 
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
            // HitLocation = HitResult.Location;
            
            // 处理击中物体
			AActor* HitActor = HitResult.GetActor();
			if(HitActor){
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,  FString::Printf(TEXT("Hit Actor: %s"), *HitActor->GetName()));
			}

        }


		// DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1, 0, 0.1f);

	
	}


}
