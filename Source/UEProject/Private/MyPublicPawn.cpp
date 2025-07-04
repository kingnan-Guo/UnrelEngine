// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPublicPawn.h"

// Sets default values
AMyPublicPawn::AMyPublicPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MySceneComponent"));
	MySpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArmComponent"));
	MyCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCameraComponent"));

	MySceneComponent->SetupAttachment(RootComponent);// 将MySceneComponent附加到根组件
	MySpringArmComponent->SetupAttachment(MySceneComponent); // 将MySpringArmComponent附加到MySceneComponent
	MyCameraComponent->SetupAttachment(MySpringArmComponent); // 将MyCameraComponent附加到MySpringArmComponent


	MySpringArmComponent->TargetArmLength = 400.0f; // 设置SpringArm组件的臂长

	MySpringArmComponent->bDoCollisionTest = false; // 设置SpringArm组件不进行碰撞检测

	// 随着 鼠标移动，旋转摄像机
	MySpringArmComponent->bUsePawnControlRotation = true;



}

// Called when the game starts or when spawned
void AMyPublicPawn::BeginPlay()
{
	Super::BeginPlay();


    // APlayerController*  PlayerController = Cast<APlayerController>(GetController());
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if(PlayerController){
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        Subsystem->AddMappingContext(MyInputMappingContext, 0);
    }


	//设置位置
	FVector MyLocation = FVector(0, 0, 0);
 
	//设置旋转
	FRotator MyRotation = FRotator(0, 0, 0);
 
	//设置缩放
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


	//  让增强输入系统代替穿透的输入系统
	UEnhancedInputComponent* ePlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (ePlayerInputComponent){
		ePlayerInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AMyPublicPawn::Move);
		ePlayerInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AMyPublicPawn::Look);
	}

}



void AMyPublicPawn::Move(const FInputActionValue& Value){
	FVector2D MoveValue = Value.Get<FVector2D>();
	FRotator ControllerRotation = GetControlRotation();
	FRotator YawRotation(0, ControllerRotation.Yaw, 0);
	FVector forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // 获取前向向量
	FVector right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 获取右向向量
	AddMovementInput(forward, MoveValue.X);
	AddMovementInput(right, MoveValue.Y);
}

void AMyPublicPawn::Look(const FInputActionValue& Value){
	FVector2D LookValue = Value.Get<FVector2D>();
	AddControllerPitchInput(LookValue.Y);
	AddControllerYawInput(LookValue.X);
}
