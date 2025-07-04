// // Fill out your copyright notice in the Description page of Project Settings.


// #include "MyCameraPawn.h"

// // Sets default values
// AMyCameraPawn::AMyCameraPawn()
// {
//  	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
// 	PrimaryActorTick.bCanEverTick = true;

// }

// // Called when the game starts or when spawned
// void AMyCameraPawn::BeginPlay()
// {
// 	Super::BeginPlay();
	
// }

// // Called every frame
// void AMyCameraPawn::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);

// }

// // Called to bind functionality to input
// void AMyCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);

// }


#include "MyCameraPawn.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMyCameraPawn::AMyCameraPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // 使用基类的 RootComponent（AActor 提供的）
    // 不需要重新声明 RootComponent

    // 设置 Spring Arm 组件
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->bDoCollisionTest = false;
    SpringArmComponent->TargetArmLength = 300.0f;

    // 设置相机组件
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    // 初始化注视点
    LookAtPoint = FVector(0.0f, 0.0f, 0.0f);
}

void AMyCameraPawn::BeginPlay()
{
    Super::BeginPlay();

    // 确保运行视口使用 CameraComponent
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->SetViewTargetWithBlend(this, 0.0f);

        // 添加输入映射上下文
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(IMC_CameraControls, 0);
        }
    }

    // 初始化相机朝向 LookAtPoint
    CameraComponent->SetWorldRotation((LookAtPoint - CameraComponent->GetComponentLocation()).Rotation());
}

void AMyCameraPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 保持相机朝向 LookAtPoint
    FVector WorldLookAtPoint = GetActorLocation() + LookAtPoint;
    FVector DirectionToLookAt = WorldLookAtPoint - CameraComponent->GetComponentLocation();
    CameraComponent->SetWorldRotation(DirectionToLookAt.Rotation());

    // 处理平滑过渡
    if (bIsTransitioning)
    {
        ElapsedTime += DeltaTime;
        float Alpha = FMath::Clamp(ElapsedTime / TransitionDuration, 0.0f, 1.0f);
        SetActorLocation(FMath::Lerp(GetActorLocation(), TargetPosition, Alpha));
        SetActorRotation(FMath::Lerp(GetActorRotation(), TargetRotation, Alpha));
        if (Alpha >= 1.0f)
        {
            bIsTransitioning = false;
        }
    }

    // 调试绘制注视点（可选）
    DrawDebugSphere(GetWorld(), GetActorLocation() + LookAtPoint, 10.0f, 12, FColor::Red, false, 0.0f);
}

void AMyCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 使用增强输入组件
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &AMyCameraPawn::Zoom);
        EnhancedInputComponent->BindAction(IA_RotateHorizontal, ETriggerEvent::Triggered, this, &AMyCameraPawn::RotateHorizontal);
        EnhancedInputComponent->BindAction(IA_RotateVertical, ETriggerEvent::Triggered, this, &AMyCameraPawn::RotateVertical);
        EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &AMyCameraPawn::MoveForward);
        EnhancedInputComponent->BindAction(IA_MoveRight, ETriggerEvent::Triggered, this, &AMyCameraPawn::MoveRight);
        EnhancedInputComponent->BindAction(IA_LookAtForward, ETriggerEvent::Triggered, this, &AMyCameraPawn::MoveLookAtForward);
        EnhancedInputComponent->BindAction(IA_LookAtRight, ETriggerEvent::Triggered, this, &AMyCameraPawn::MoveLookAtRight);
        EnhancedInputComponent->BindAction(IA_PanHorizontal, ETriggerEvent::Triggered, this, &AMyCameraPawn::PanHorizontal);
        EnhancedInputComponent->BindAction(IA_PanVertical, ETriggerEvent::Triggered, this, &AMyCameraPawn::PanVertical);
        EnhancedInputComponent->BindAction(IA_RightMouseButton, ETriggerEvent::Started, this, &AMyCameraPawn::StartRotate);
        EnhancedInputComponent->BindAction(IA_RightMouseButton, ETriggerEvent::Completed, this, &AMyCameraPawn::StopRotate);
        EnhancedInputComponent->BindAction(IA_MiddleMouseButton, ETriggerEvent::Started, this, &AMyCameraPawn::StartPan);
        EnhancedInputComponent->BindAction(IA_MiddleMouseButton, ETriggerEvent::Completed, this, &AMyCameraPawn::StopPan);
    }
}

void AMyCameraPawn::Zoom(const FInputActionValue& Value)
{
    float Val = Value.Get<float>();
    if (Val != 0.0f)
    {
        float Distance = FVector::Distance(GetActorLocation(), GetActorLocation() + LookAtPoint);
        if (Distance > 300.0f && Val < 0.0f) return; // 最大距离限制
        if (Distance < 1.0f && Val > 0.0f) return; // 最小距离限制
        SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + Val * -CameraMoveSpeed * 100.0f, 1.0f, 300.0f);
    }
}

void AMyCameraPawn::RotateHorizontal(const FInputActionValue& Value)
{
    if (bIsRotating && Value.Get<float>() != 0.0f)
    {
        float Val = Value.Get<float>();
        SpringArmComponent->AddLocalRotation(FRotator(0.0f, Val * CameraRotateSpeed, 0.0f));
        LookAtPoint = FRotator(0.0f, Val * CameraRotateSpeed, 0.0f).RotateVector(LookAtPoint);
    }
}

void AMyCameraPawn::RotateVertical(const FInputActionValue& Value)
{
    if (bIsRotating && Value.Get<float>() != 0.0f)
    {
        float Val = Value.Get<float>();
        float NewPitch = FMath::Clamp(SpringArmComponent->GetComponentRotation().Pitch + Val * CameraRotateSpeed, -80.0f, 80.0f);
        SpringArmComponent->SetRelativeRotation(FRotator(NewPitch, SpringArmComponent->GetComponentRotation().Yaw, 0.0f));
    }
}

void AMyCameraPawn::MoveForward(const FInputActionValue& Value)
{
    if (Value.Get<float>() != 0.0f)
    {
        FVector Forward = GetActorForwardVector();
        Forward.Z = 0.0f; // 限制在水平面
        AddActorWorldOffset(Forward * Value.Get<float>() * CameraMoveSpeed * 100.0f * GetWorld()->GetDeltaSeconds());
        LookAtPoint += Forward * Value.Get<float>() * CameraMoveSpeed * 100.0f * GetWorld()->GetDeltaSeconds();
    }
}

void AMyCameraPawn::MoveRight(const FInputActionValue& Value)
{
    if (Value.Get<float>() != 0.0f)
    {
        FVector Right = GetActorRightVector();
        Right.Z = 0.0f; // 限制在水平面
        AddActorWorldOffset(Right * Value.Get<float>() * CameraMoveSpeed * 100.0f * GetWorld()->GetDeltaSeconds());
        LookAtPoint += Right * Value.Get<float>() * CameraMoveSpeed * 100.0f * GetWorld()->GetDeltaSeconds();
    }
}

void AMyCameraPawn::MoveLookAtForward(const FInputActionValue& Value)
{
    if (Value.Get<float>() != 0.0f)
    {
        FVector Forward = GetActorForwardVector();
        Forward.Z = 0.0f; // 限制在水平面
        AddActorWorldOffset(Forward * Value.Get<float>() * CameraMoveSpeed * 100.0f * GetWorld()->GetDeltaSeconds());
        LookAtPoint += Forward * Value.Get<float>() * CameraMoveSpeed * 100.0f * GetWorld()->GetDeltaSeconds();
    }
}

void AMyCameraPawn::MoveLookAtRight(const FInputActionValue& Value)
{
    if (Value.Get<float>() != 0.0f)
    {
        FVector Right = GetActorRightVector();
        Right.Z = 0.0f; // 限制在水平面
        AddActorWorldOffset(Right * Value.Get<float>() * CameraMoveSpeed * 100.0f * GetWorld()->GetDeltaSeconds());
        LookAtPoint += Right * Value.Get<float>() * CameraMoveSpeed * 100.0f * GetWorld()->GetDeltaSeconds();
    }
}

void AMyCameraPawn::PanHorizontal(const FInputActionValue& Value)
{
    if (bIsPanning && Value.Get<float>() != 0.0f)
    {
        FVector Right = GetActorRightVector();
        Right.Z = 0.0f; // 限制在水平面
        AddActorWorldOffset(Right * -Value.Get<float>() * MoveCameraSidewaysSpeed * GetWorld()->GetDeltaSeconds());
        LookAtPoint += Right * -Value.Get<float>() * MoveCameraSidewaysSpeed * GetWorld()->GetDeltaSeconds();
    }
}

void AMyCameraPawn::PanVertical(const FInputActionValue& Value)
{
    if (bIsPanning && Value.Get<float>() != 0.0f)
    {
        FVector Up = GetActorUpVector();
        AddActorWorldOffset(Up * -Value.Get<float>() * MoveCameraUpwardsSpeed * GetWorld()->GetDeltaSeconds());
        LookAtPoint += GetActorForwardVector() * -Value.Get<float>() * MoveCameraUpwardsSpeed * GetWorld()->GetDeltaSeconds();
    }
}

void AMyCameraPawn::StartRotate(const FInputActionValue& Value)
{
    bIsRotating = true;
}

void AMyCameraPawn::StopRotate(const FInputActionValue& Value)
{
    bIsRotating = false;
}

void AMyCameraPawn::StartPan(const FInputActionValue& Value)
{
    bIsPanning = true;
}

void AMyCameraPawn::StopPan(const FInputActionValue& Value)
{
    bIsPanning = false;
}

void AMyCameraPawn::ChangeLookAtPosition(const FVector& NewPosition, const FRotator& NewRotation, float Distance, float Duration)
{
    // 将世界坐标的 NewPosition 转换为相对于 Pawn 的偏移
    LookAtPoint = NewPosition - GetActorLocation();

    // 计算相机的新位置（保持与注视点的距离）
    FVector Forward = NewRotation.Vector();
    FVector CameraPosition = NewPosition - Forward * (Distance > 0.0f ? Distance : SpringArmComponent->TargetArmLength);

    // 触发平滑过渡
    ChangeCameraPosition(CameraPosition, NewRotation, Distance > 0.0f ? Distance : SpringArmComponent->TargetArmLength, Duration);
}

void AMyCameraPawn::ChangeCameraPosition(const FVector& NewPosition, const FRotator& NewRotation, float Distance, float Duration)
{
    TargetPosition = NewPosition;
    TargetRotation = NewRotation;
    SpringArmComponent->TargetArmLength = Distance;
    TransitionDuration = Duration;
    ElapsedTime = 0.0f;
    bIsTransitioning = true;
}