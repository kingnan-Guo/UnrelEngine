// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFunctionLibraryActor.h"
#include "Kismet/GameplayStatics.h" // 引入GameplayStatics头文件 里面有什么 函数？ 

// Sets default values
AMyFunctionLibraryActor::AMyFunctionLibraryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyFunctionLibraryActor::BeginPlay()
{
	Super::BeginPlay();
	

	UE_LOG(LogTemp, Error, TEXT(" AMyFunctionLibraryActor BeginPlay:   "));
	TArray<AActor*> OuterActors;//
	// 获取当前关卡的所有Actor; 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), OuterActors);// AActor::StaticClass() 是 AActor 的静态类指针

	for (int32 i = 0; i < OuterActors.Num(); i++)
	{
		UE_LOG(LogTemp, Error, TEXT(" Actor Name:   %s"), *OuterActors[i]->GetName());
	}
	


}

// Called every frame
void AMyFunctionLibraryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyFunctionLibraryActor::MyOpenLevel(){
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("ThreeLevelMap"));// 打开一个关卡
	
}
void AMyFunctionLibraryActor::MyCurrentLevelName(){
	 FString CurrentLevelName =UGameplayStatics::GetCurrentLevelName(GetWorld());

	//  GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, CurrentLevelName);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("CurrentLevelName: %s"), *CurrentLevelName));
}
// 函数：退出游戏
void AMyFunctionLibraryActor::MyQuitGame(){

    // TODO: 实现退出游戏的逻辑
	// UGamePlayStatics::QuitGame(GetWorld());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand(TEXT("quit"));
}