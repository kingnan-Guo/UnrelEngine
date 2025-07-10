// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// MySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MySceneComponent"));
	MySpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArmComponent"));
	MyCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCameraComponent"));

	// MySceneComponent->SetupAttachment(RootComponent);// 将MySceneComponent附加到根组件
	MySpringArmComponent->SetupAttachment(RootComponent); // 将MySpringArmComponent附加到MySceneComponent
	MyCameraComponent->SetupAttachment(MySpringArmComponent); // 将MyCameraComponent附加到MySpringArmComponent


	MySpringArmComponent->TargetArmLength = 400.0f; // 设置SpringArm组件的臂长

	MySpringArmComponent->bDoCollisionTest = false; // 设置SpringArm组件不进行碰撞检测

	// 随着 鼠标移动，旋转摄像机
	MySpringArmComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
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


	// 动态加载资源

	UStaticMesh* MyTempMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/Shapes/40.40'"));
	UE_LOG(LogTemp, Warning, TEXT("MyTempMesh 1"));
	if (MyTempMesh) {
		UE_LOG(LogTemp, Warning, TEXT("MyTempMesh 2"));
		// 创建静态网格体组件
		UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
		StaticMeshComponent->SetStaticMesh(MyTempMesh);
		StaticMeshComponent->SetupAttachment(RootComponent);


		
		// 关键：注册组件到引擎
		StaticMeshComponent->RegisterComponent();
		
		// 强制更新渲染状态
		StaticMeshComponent->MarkRenderStateDirty();
		
		// 设置有效位置（避免被遮挡）
		StaticMeshComponent->SetRelativeLocation(FVector(100, 0, 0));
		StaticMeshComponent->SetRelativeScale3D(FVector(1.0f));
		UE_LOG(LogTemp, Warning, TEXT("MyTempMesh 3"));
		
	}
	// 动态加载类资源 , 算是动态加载预制体了
	UClass* myTempClass = LoadClass<AActor>(this, TEXT("/Script/Engine.Blueprint'/Game/BP/MyTempActor.MyTempActor_C'"));
	UE_LOG(LogTemp, Warning, TEXT("myTempClass 1"));
	if(myTempClass){
		UE_LOG(LogTemp, Warning, TEXT("myTempClass 2"));
		AActor* SpamActor = GetWorld()->SpawnActor<AActor>(myTempClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//  让增强输入系统代替穿透的输入系统
	UEnhancedInputComponent* ePlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (ePlayerInputComponent){
		ePlayerInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		ePlayerInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		ePlayerInputComponent->BindAction(ScaleInputAction, ETriggerEvent::Triggered, this, &AMyCharacter::Scale);
		
		// ePlayerInputComponent->BindAction(MouseButtonRightInputAction, ETriggerEvent::Triggered, this, &AMyCharacter::MouseButton);
		// ePlayerInputComponent->BindAction(MouseButtonMiddleInputAction, ETriggerEvent::Triggered, this, &AMyCharacter::MouseButton);


		ePlayerInputComponent->BindAction(MouseButtonRightInputAction, ETriggerEvent::Triggered, this, &AMyCharacter::MouseButtonInstance);
		ePlayerInputComponent->BindAction(MouseButtonMiddleInputAction, ETriggerEvent::Triggered, this, &AMyCharacter::MouseButtonInstance);
	}

}




void AMyCharacter::Move(const FInputActionValue& Value){
	// 打印信息
	// UE_LOG(LogTemp, Warning, TEXT("Move"));
	FVector2D MoveValue = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("MoveValue: %s"), *MoveValue.ToString());
	FRotator ControllerRotation = GetControlRotation();
	FRotator YawRotation(0, ControllerRotation.Yaw, 0);
	FVector forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // 获取前向向量
	FVector right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 获取右向向量
	AddMovementInput(forward, MoveValue.X);
	AddMovementInput(right, MoveValue.Y);
}

void AMyCharacter::Look(const FInputActionValue& Value){
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

void AMyCharacter::Scale(const FInputActionValue& Value){
	UE_LOG(LogTemp, Warning, TEXT("Scale"));
	//  打印信息 value
	UE_LOG(LogTemp, Warning, TEXT("Value: %s"), *Value.ToString());
	
	FVector2D ScaleValue = Value.Get<FVector2D>();
	MySpringArmComponent->TargetArmLength += -ScaleValue.X * 10.0f;
	MySpringArmComponent->TargetArmLength = FMath::Clamp(MySpringArmComponent->TargetArmLength, 100.0f, 1000.0f);

}



void AMyCharacter::MouseButtonInstance(const FInputActionInstance& Instance)
{
	UE_LOG(LogTemp, Warning, TEXT("MouseButtonInstance"));
    const UInputAction* SourceAction = Instance.GetSourceAction();
    // if (SourceAction)
    // {
    //     FString ActionName = SourceAction->GetName();
    //     UE_LOG(LogTemp, Warning, TEXT("Action Name: %s"), *ActionName);

	// 	// 获取动作值
    //     FInputActionValue Value = Instance.GetValue();

	// 	 UE_LOG(LogTemp, Warning, TEXT("MouseButton Value: %s"), *Value.ToString());
		

	// 	ETriggerEvent TriggerEvent = Instance.GetTriggerEvent();

  	// 	// 获取触发按键 ??

    // }
	

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
            // UE_LOG(LogTemp, Error, TEXT("Left Mouse Button %s"), *TriggerEventName);
            // if (TriggerEvent == ETriggerEvent::Started)
            // {
            //     // 左键按下时的逻辑
            //     bEnableRightMouseButtonInput = false; // 示例：禁用右键功能
            // }

			// if (Value.Get<bool>()) {
			// 	bEnableRightMouseButtonInput = true;

			// } else {
			// 	bEnableRightMouseButtonInput = false;
			// }

        }
        else if (ActionName.Contains(TEXT("Right")))
        {
            // UE_LOG(LogTemp, Error, TEXT("Right Mouse Button %s"), *TriggerEventName);
            // if (TriggerEvent == ETriggerEvent::Started)
            // {
            //     // 右键按下时的逻辑
            //     bEnableRightMouseButtonInput = true; // 示例：启用右键功能
            //     if (APlayerController* PC = Cast<APlayerController>(GetController()))
            //     {
            //         PC->bShowMouseCursor = false;
            //         PC->SetInputMode(FInputModeGameOnly());
            //     }
            // }
            // else if (TriggerEvent == ETriggerEvent::Completed)
            // {
            //     // 右键释放时的逻辑
            //     bEnableRightMouseButtonInput = false;
            //     if (APlayerController* PC = Cast<APlayerController>(GetController()))
            //     {
            //         PC->bShowMouseCursor = true;
            //         PC->SetInputMode(FInputModeGameAndUI());
            //     }
            // }

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
void AMyCharacter::MouseButton(const FInputActionValue& Value){

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
