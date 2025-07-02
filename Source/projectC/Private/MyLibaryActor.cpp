// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLibaryActor.h"
#include "Kismet/GameplayStatics.h" // 引入GameplayStatics头文件 里面有什么 函数？ 
// Sets default values
AMyLibaryActor::AMyLibaryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyLibaryActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyLibaryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





