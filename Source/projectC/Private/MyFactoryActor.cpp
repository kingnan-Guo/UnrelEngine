// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFactoryActor.h"
#include "ProductB.h"
#include "ProductA.h"
// Sets default values
AMyFactoryActor::AMyFactoryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyFactoryActor::BeginPlay()
{
	Super::BeginPlay();

	UProductObject* productA = UFactoryObject::CreateNewProdcutObject(this, UProductA::StaticClass());
	UProductObject* productB = UFactoryObject::CreateNewProdcutObject(this, UProductB::StaticClass());


	productA->ShowInfo();
	productB->ShowInfo();
}

// Called every frame
void AMyFactoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

