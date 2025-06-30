// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPublicCharacter.h"

// Sets default values
AMyPublicCharacter::AMyPublicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	mySpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("mySpringArmComponent"));// 创建一个SpringArm组件
	// RootComponent = mySpringArmComponent;// 将SpringArm组件作为根组件
	mySpringArmComponent->SetupAttachment(RootComponent);// 将SpringArm组件附加到根组件上
	mySpringArmComponent->TargetArmLength = 400.0f;// 设置SpringArm的长度
	// 设置相机控制器的 旋转
	mySpringArmComponent->bUsePawnControlRotation = true;// 这是使用pawn 控制器的旋转


	myCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("myCameraComponent"));// 创建一个Camera组件


	myCameraComponent->SetupAttachment(mySpringArmComponent);// 将Camera组件附加到SpringArm组件上

	// 控制器的旋转不影响 角色转动

	bUseControllerRotationPitch = false;//  bUseControllerRotationPitch 是 USpringArmComponent 的一个属性，用于控制是否使用控制器的旋转来影响 SpringArm 的旋转。
	bUseControllerRotationYaw = false;// 
	bUseControllerRotationRoll = false;// 


	// 让角色面朝 加速度方向
	GetCharacterMovement()->bOrientRotationToMovement = true;// bOrientRotationToMovement 是 UCharacterMovementComponent 的一个属性，用于控制是否让角色面朝移动方向。



	// mySpringArmComponent->bUsePawnControlRotation = true;



	//创建默认对象
	myWidgetHealth = CreateDefaultSubobject<UWidgetComponent>(TEXT("UWidgetComponent"));

	myWidgetHealth->SetupAttachment(RootComponent);// 将Widget组件附加到根组件上
	//加载类
	static ConstructorHelpers::FClassFinder<UUserWidget>WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG_Health.UMG_Health_C'"));

	if (WidgetClass.Succeeded()) {
	    myWidgetHealth->SetWidgetClass(WidgetClass.Class);// 设置Widget组件的类
		myWidgetHealth->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));// 设置Widget组件的位置
		//  渲染方式
		myWidgetHealth->SetWidgetSpace(EWidgetSpace::Screen);// 设置Widget组件的渲染方式为屏幕空间

		// 渲染大小
		myWidgetHealth->SetDrawSize(FVector2D(400.0f, 20.0f));// 设置Widget组件的渲染大小
	}
}

// Called when the game starts or when spawned
void AMyPublicCharacter::BeginPlay()
{
	Super::BeginPlay();
	


	// 
	if(APlayerController* PlayerConroller = Cast<APlayerController>(Controller)){
		// 获取增强输入的 本地玩家子系统，并设置输入模式
		// 将本地控制器设置为 增强控制器 子系统 的模式
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerConroller->GetLocalPlayer())){// 获取本地玩家子系统
			// 转换成功之后 
			Subsystem->AddMappingContext(DefaultInputMappingContext, 0);

		}
	}


	Attack();
	CaclulateHealth();

	// 、、设置定时
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AMyPublicCharacter::MyTimerFunction, 1.0f, true);

	if(MyTimerHandle.IsValid()&&false){// 如果定时器有效
		UE_LOG(LogTemp, Log, TEXT("Timer is valid"));
		GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);// 清除定时器

	}
}

// Called every frame
void AMyPublicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPublicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// 绑定 映射
	// 将玩家 输入映射 转换为 玩家增强 输入 映射
	// 当有输入映射的时候会执行这个函数
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){
		// EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPublicCharacter::Move);
		// EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPublicCharacter::Look);
		  
		if (MoveAction)
        {
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPublicCharacter::Move);
            UE_LOG(LogTemp, Log, TEXT("MoveAction bound successfully"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("MoveAction is null!"));
        }
		
        if (LookAction)
        {
            EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPublicCharacter::Look);
            UE_LOG(LogTemp, Log, TEXT("LookAction bound successfully"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("LookAction is null!"));
        }

	}


}



void AMyPublicCharacter::Move(const FInputActionValue& Value){

	FVector2D MoveValueVector = Value.Get<FVector2D>();// 获取 2D 向量
	if(Controller != nullptr){
		const FRotator Rotation = Controller->GetControlRotation();// 获取控制器的旋转

		// 获得 Yaw 轴的旋转,Yaw 是 	水平旋转，也就是左右旋转，也就是绕 Z 轴旋转
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// 获得 前向向量
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);// 获取 X 轴的单位向量
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);// 获取 Y 轴的单位向量

		AddMovementInput(ForwardDirection, MoveValueVector.Y);// 添加移动输入 这个是 前后移动
		AddMovementInput(RightDirection, MoveValueVector.X);// 添加移动输入 这个是 左右移动





	}
}


// / 旋转
void AMyPublicCharacter::Look(const FInputActionValue& Value){
	//  获取鼠标坐标轴的 位置
	FVector2D LookAxisValueVector = Value.Get<FVector2D>();// 获取 2D 向量
	UE_LOG(LogTemp, Warning, TEXT("Look Input: X=%f, Y=%f"), LookAxisValueVector.X, LookAxisValueVector.Y);
	if(Controller != nullptr){
		AddControllerYawInput(LookAxisValueVector.X);// 添加控制器的 Yaw 轴的输入
		AddControllerPitchInput(LookAxisValueVector.Y);// 添加控制器的 Pitch 轴的输入, Y方向的值


	}

}



void AMyPublicCharacter::Attack(){
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack"));
}
void AMyPublicCharacter::CaclulateHealth(){
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CaclulateHealth"));
}



// 
void AMyPublicCharacter::MyTimerFunction(){
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("MyTimerFunction"));
}