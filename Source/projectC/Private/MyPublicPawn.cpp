// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPublicPawn.h"

// Sets default values
AMyPublicPawn::AMyPublicPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComponent"));
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArmComponent"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCameraComponent"));


	RootComponent = MyRoot;
	MySpringArm->SetupAttachment(MyRoot);
	MyCamera->SetupAttachment(MySpringArm);
	MySpringArm->bDoCollisionTest = false; // MySpringArm 的碰撞  设置为 false


}

// Called when the game starts or when spawned
void AMyPublicPawn::BeginPlay()
{
	Super::BeginPlay();
	TestA();
	

	TSubclassOf<UMyPublicObject> MySubClassObject = UMyPublicObject::StaticClass();
	myTestObject = NewObject<UMyPublicObject>(GetWorld(), MySubClassObject);
	if (myTestObject) {
		UE_LOG(LogTemp, Error, TEXT("MyPublicPawn myTestObject %s"), *myTestObject->GetName());
		UE_LOG(LogTemp, Error, TEXT("MyPublicPawn myTestObject %f"), myTestObject->MyDateTableStruct.Health);
		UE_LOG(LogTemp, Error, TEXT("MyPublicPawn myTestObject %s"), *myTestObject->MyDateTableStruct.Name);
		UE_LOG(LogTemp, Error, TEXT("MyPublicPawn myTestObject %d"), myTestObject->MyDateTableStruct.Level);
	}


	myPublicGameInstance = Cast<UMyPublicGameInstance>(GetWorld()->GetFirstPlayerController()->GetGameInstance());

	if (myPublicGameInstance) {
		UE_LOG(LogTemp, Error, TEXT("MyPublicPawn myPublicGameInstance %s"), *myPublicGameInstance->GetName());
		//UE_LOG(LogTemp, Error, TEXT("MyPublicPawn myTestObject %f"), myTestObject->MyDateTableStruct.Health);
		UE_LOG(LogTemp, Error, TEXT("MyPublicPawn myPublicGameInstance %s"), *myPublicGameInstance->myAppId);
		UE_LOG(LogTemp, Error, TEXT("MyPublicPawn myPublicGameInstance %s"), *myPublicGameInstance->myName);
		//UE_LOG(LogTemp, Error, TEXT("MyPublicPawn myTestObject %d"), myTestObject->MyDateTableStruct.Level);
	}




	FVector MyLocation = FVector(0,0,0);
	FRotator MyRotation = FRotator(-50,0,0);
	FVector MyScale = FVector(1, 1, 1);
	SetActorLocation(MyLocation);
	SetActorRotation(MyRotation);
	SetActorScale3D(MyScale);




}

// Called every frame
void AMyPublicPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPublicPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



}

void AMyPublicPawn::myFunctionPrint() {

}

bool AMyPublicPawn::myFunctionPrinttPure() {
	return false;
}





//void AMyPublicPawn::Test1() {
//
//}
//
//
//int AMyPublicPawn::Test2() {
//	return 0;
//}
//
//void AMyPublicPawn::Test11(const FString& MyString)
//{
//}
//
//void AMyPublicPawn::Test22(const FString& MyString)
//{
//}

void AMyPublicPawn::TestA_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TestA_Implementation"));// 在屏幕上显示一条消息
}

int AMyPublicPawn::TestB_Implementation()
{
	return 0;
}

void AMyPublicPawn::TestC_Implementation(const FString &MyString)
{
}

int AMyPublicPawn::TestD_Implementation(const FString &MyString)
{
	return 0;
}

void AMyPublicPawn::PrintTest()
{
}

void AMyPublicPawn::Zoom(bool Direction, float ZoomSpeed)
{
	if (Direction) {
		if (MySpringArm->TargetArmLength >= 300 && MySpringArm->TargetArmLength < 5000) {

			MySpringArm->TargetArmLength += (ZoomSpeed * 2);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MySpringArm Length is %f"), MySpringArm->TargetArmLength));
		}
	}
	else {

		if (MySpringArm->TargetArmLength >= 300 && MySpringArm->TargetArmLength < 5000) {
			MySpringArm->TargetArmLength -= (ZoomSpeed * 2);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MySpringArm Length is %f"), MySpringArm->TargetArmLength));
		}
	}
}
