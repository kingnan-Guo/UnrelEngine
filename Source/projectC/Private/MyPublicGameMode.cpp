// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPublicGameMode.h"

AMyPublicGameMode::AMyPublicGameMode() {
    DefaultPawnClass = AMyPublicPawn::StaticClass();
    PlayerControllerClass = AMyPublicPlayerController::StaticClass();
    GameStateClass = AMyPublicGameState::StaticClass();
    PlayerStateClass = AMyPublicPlayerState::StaticClass();
    HUDClass = AMyPublicHUD::StaticClass();

    // DefaultPlayerControllerClass = AMyPublicPlayerController::StaticClass();
}



void AMyPublicGameMode::BeginPlay() {
    Super::BeginPlay();// 调用父类方法

    UE_LOG(LogTemp, Warning, TEXT("AMyPublicGameMode.cpp"));

	int a = 10;
	UE_LOG(LogTemp, Display, TEXT("AMyPublicActor BeginPlay %d"), a)

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MyPublicGameMode BeginPlay"));// 在屏幕上显示一条消息


    // String = FString("Hello World");
    // UE_LOG(LogTemp, Warning, TEXT("AMyPublicGameMode.cpp %s"), *String);
    // Name = FName("MyName");
    // UE_LOG(LogTemp, Warning, TEXT("AMyPublicGameMode.cpp %s"), *Name);
    // Text = FText::FromString("Hello World"); 



    fstring = TEXT("Hello World");
    fname = FName(*fstring); // 将FString转换为FName

    FText fts = FText::FromString(fstring);// 将FName转换为FText

    fstring = fname.ToString();

    FText ftsname = FText::FromName(fname);


    FString strFromeText = ftsname.ToString();// 将FText转换为FString

    // FText 不能直接转换成 FName , 需要先转换成 FString 再转换成 FName





    myTArray.Add(20);
    myTArray.Add(30);
    myTArray.Add(50);

    //myTArray.AddUnique(20);// 添加唯一元素，如果元素已经存在，则不会添加
    //myTArray.AddUnique(30);
    //myTArray.Remove(20); // 删除元素


    //myTArray.Sort(); // 排序
    //myTArray.RemoveAt(0);// 删除 0 位置的元素


    PrintF(); // 打印数组

    //myTArray.RemoveSingle(30);// 删除所有 30 的元素
    //myTArray.Empty(); // 清空数组
    //myTArray.Reset(); // 重置数组 所有的元素 都 置为 0

    //myTArray.Insert(0, 10); // 在 0 位置插入 10
    //int32 index = myTArray.Find(30);// 查找 30 的位置
    //int32 temp = myTArray[0]
    //temp = 80;
    //
    //PrintF(); // 打印数组



    //myTMap.Emplace(0, 1);

}

void AMyPublicGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    Super::EndPlay(EndPlayReason);
}

void AMyPublicGameMode::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}


void AMyPublicGameMode::PrintF() {
    for(auto it = myTArray.CreateIterator(); it; it++) {
        UE_LOG(LogTemp, Warning, TEXT("AMyPublicGameMode.cpp %d"), *it);
    }




}