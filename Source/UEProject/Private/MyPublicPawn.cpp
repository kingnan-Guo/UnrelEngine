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
	// MySpringArmComponent->bUsePawnControlRotation = true;


	AutoPossessPlayer = EAutoReceiveInput::Player0;// 设置自动拥有玩家输入


	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");

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
	// FVector MyLocation = FVector(0, 0, 0);
 
	// //设置旋转
	// FRotator MyRotation = FRotator(0, 0, 0);
 
	// //设置缩放
	// FVector MyScale = FVector(1, 1, 1);
 
	// SetActorLocation(MyLocation);
	// SetActorRotation(MyRotation);
	// SetActorScale3D(MyScale);
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
		// ePlayerInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AMyPublicPawn::Move);
		// ePlayerInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AMyPublicPawn::Look);

		ePlayerInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AMyPublicPawn::Move);
		ePlayerInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AMyPublicPawn::Look);
		ePlayerInputComponent->BindAction(ScaleInputAction, ETriggerEvent::Triggered, this, &AMyPublicPawn::Scale);
		

		ePlayerInputComponent->BindAction(MouseButtonRightInputAction, ETriggerEvent::Triggered, this, &AMyPublicPawn::MouseButtonInstance);
		ePlayerInputComponent->BindAction(MouseButtonMiddleInputAction, ETriggerEvent::Triggered, this, &AMyPublicPawn::MouseButtonInstance);
	



	}

}


void AMyPublicPawn::Move(const FInputActionValue& Value){

	if (!MovementComponent || MovementComponent->IsFalling()) 
		return; // 确保移动组件有效

	// 打印信息
	// UE_LOG(LogTemp, Warning, TEXT("Move"));
	FVector2D MoveValue = Value.Get<FVector2D>();
	// UE_LOG(LogTemp, Warning, TEXT("MoveValue: %s"), *MoveValue.ToString());
	FRotator ControllerRotation = GetControlRotation();
	FRotator YawRotation(0, ControllerRotation.Yaw, 0);
	FVector forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // 获取前向向量
	FVector right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 获取右向向量
	AddMovementInput(forward, MoveValue.X);
	AddMovementInput(right, MoveValue.Y);
}

void AMyPublicPawn::Look(const FInputActionValue& Value){
	if (bEnableRightMouseButtonInput) {
		// 打印信息
		UE_LOG(LogTemp, Warning, TEXT("Look"));
		FVector2D LookValue = Value.Get<FVector2D>();
		AddControllerPitchInput(LookValue.Y);
		AddControllerYawInput(LookValue.X);
	};

	if(bEnableMiddleMouseButtonInput){
		FVector2D MoveValue = Value.Get<FVector2D>();
		// UE_LOG(LogTemp, Warning, TEXT("LookValue: %s"), *MoveValue.ToString());

		FRotator ControllerRotation = GetControlRotation();
		FRotator YawRotation(0, ControllerRotation.Yaw, 0);
		FVector forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // 获取前向向量
		FVector right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 获取右向向量
		// UE_LOG(LogTemp, Warning, TEXT("forward: %s"), *forward.ToString());
		// UE_LOG(LogTemp, Warning, TEXT("right: %s"), *right.ToString());
		// UE_LOG(LogTemp, Warning, TEXT("MoveValue: %s"), *MoveValue.ToString());
		// MoveValue.X
		// AddMovementInput(forward, -MoveValue.X );
		// AddMovementInput(right, MoveValue.Y);

		
		// float MoveValueX = MoveValue.X * 1000000.0f;
		// float MoveValueY = MoveValue.Y* 1000000.0f;
		float MoveValueX = MoveValue.X * 1.0f;
		float MoveValueY = MoveValue.Y* 1.0f;
		UE_LOG(LogTemp, Warning, TEXT("MoveValue.X: %s MoveValue.Y: %s"), *FString::SanitizeFloat(MoveValueX), *FString::SanitizeFloat(MoveValueY));
		AddMovementInput(forward, -MoveValueX );
		AddMovementInput(right, MoveValueY);

	}

}

void AMyPublicPawn::Scale(const FInputActionValue& Value){
	// UE_LOG(LogTemp, Warning, TEXT("Scale"));
	//  打印信息 value
	// UE_LOG(LogTemp, Warning, TEXT("Value: %s"), *Value.ToString());
	
	FVector2D ScaleValue = Value.Get<FVector2D>();
	MySpringArmComponent->TargetArmLength += -ScaleValue.X * 10.0f;
	MySpringArmComponent->TargetArmLength = FMath::Clamp(MySpringArmComponent->TargetArmLength, 100.0f, 1000.0f);

}



void AMyPublicPawn::MouseButtonInstance(const FInputActionInstance& Instance)
{
	UE_LOG(LogTemp, Warning, TEXT("MouseButtonInstance"));
    const UInputAction* SourceAction = Instance.GetSourceAction();
	

	if (SourceAction)
		{
        // 获取动作名称（在输入映射中设置的名称，例如 "IA_MouseLeft" 或 "IA_MouseRight"）
        FString ActionName = SourceAction->GetName();
        UE_LOG(LogTemp, Warning, TEXT("Action Name: %s"), *ActionName);

        // 获取动作值
        FInputActionValue Value = Instance.GetValue();
        UE_LOG(LogTemp, Warning, TEXT("MouseButton Value: %s"), *Value.ToString());

        // 获取触发事件（按下、释放等）
        // ETriggerEvent TriggerEvent = Instance.GetTriggerEvent();
        // FString TriggerEventName;
        // switch (TriggerEvent)
        // {
        // case ETriggerEvent::Triggered:
        //     TriggerEventName = TEXT("Triggered");
        //     break;
        // case ETriggerEvent::Started:
        //     TriggerEventName = TEXT("Started (Pressed)");
        //     break;
        // case ETriggerEvent::Completed:
        //     TriggerEventName = TEXT("Completed (Released)");
        //     break;
        // case ETriggerEvent::Canceled:
        //     TriggerEventName = TEXT("Canceled");
        //     break;
        // default:
        //     TriggerEventName = TEXT("Unknown");
        //     break;
        // }
        // UE_LOG(LogTemp, Error, TEXT("Trigger Event: %s"), *TriggerEventName);



        // 根据动作名称判断具体鼠标按钮
        // 假设你在输入映射中为不同鼠标按钮设置了不同的 UInputAction
        // 例如：IA_MouseLeft、IA_MouseRight、IA_MouseMiddle
        if (ActionName.Contains(TEXT("Left")))
        {


        }
        else if (ActionName.Contains(TEXT("Right")))
        {


			if (Value.Get<bool>()) {
				bEnableRightMouseButtonInput = true;

			} else {
				bEnableRightMouseButtonInput = false;
			}
        }
        else if (ActionName.Contains(TEXT("Middle")))
        {
            // UE_LOG(LogTemp, Error, TEXT("Middle Mouse Button %s"), *TriggerEventName);
            // 中键逻辑

			if (Value.Get<bool>()) {
				bEnableMiddleMouseButtonInput = true;

			} else {
				bEnableMiddleMouseButtonInput = false;
			}
        }
    }


}

// 当鼠标按钮被按下时调用
void AMyPublicPawn::MouseButton(const FInputActionValue& Value){

	// 输出日志信息
	// UE_LOG(LogTemp, Warning, TEXT("MouseButton Value: %s"), *Value.ToString());
	FVector2D MouseValue = Value.Get<FVector2D>();
	// FString ActionName = Value.Get<FString>();
	// UE_LOG(LogTemp, Warning, TEXT("ActionName: %s"), *ActionName);
	//Value 是哪个按钮
	UE_LOG(LogTemp, Warning, TEXT("MouseValue: %s"), *MouseValue.ToString());
	// 检查鼠标按钮是否被按下
	if (Value.Get<bool>()) {
		UE_LOG(LogTemp, Warning, TEXT("Mouse button pressed"));
		bEnableRightMouseButtonInput = true;

	} else {
		UE_LOG(LogTemp, Warning, TEXT("Mouse button released"));
		bEnableRightMouseButtonInput = false;
	}

}



//  这个 重新的目的是 在 AddMovementInput 函数内部是要寻找 MovementComponent 的，
UPawnMovementComponent* AMyPublicPawn::GetMovementComponent() const
{
    return MovementComponent;
}




