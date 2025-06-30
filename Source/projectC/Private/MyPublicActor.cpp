// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPublicActor.h"

// Sets default values
AMyPublicActor::AMyPublicActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("MyPublicActor.cpp"));

    // 创建组件
	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyCustomSence"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyCustomMesh"));
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyCustomParticle"));
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyCustomBox"));
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MyCustomAudio"));


	RootComponent = MyScene;     // 设置根组件

    // 将组件附加到场景根组件
	MyMesh->SetupAttachment(MyScene);
	MyParticle->SetupAttachment(MyScene);
	MyBox->SetupAttachment(MyScene);
	MyAudio->SetupAttachment(MyBox);


    // 加载静态网格资源
	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	MyMesh->SetStaticMesh(TempStaticMesh.Object);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>TempParticSystem(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	MyParticle->SetTemplate(TempParticSystem.Object);
   // 加载音效资源
	static ConstructorHelpers::FObjectFinder<USoundWave>TempSound(TEXT("/Script/Engine.SoundWave'/Game/StarterContent/Audio/Collapse01.Collapse01'"));
	MyAudio->SetSound(TempSound.Object);



    // 加载粒子系统资源
	static ConstructorHelpers::FClassFinder<AActor>TempMyActor(TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_WallSconce.Blueprint_WallSconce_C'"));
	myActor = TempMyActor.Class;


    // 绑定碰撞事件
	MyBox->OnComponentBeginOverlap.AddDynamic(this, &AMyPublicActor::BeginOverLapFunction);
	MyBox->OnComponentEndOverlap.AddDynamic(this, &AMyPublicActor::EndOverLapFunction);


	// 绑定碰撞事件
	MyBox->OnComponentHit.AddDynamic(this, &AMyPublicActor::HitFunction);


    // 设置碰撞配置
	MyBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);// ECollisionEnabled::NoCollision û����ײ
	MyBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);// 仅查询 仅查询碰撞
	// MyBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);// 仅物理 仅物理 碰撞
	// MyBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);// 查询和物理 查询和物理 碰撞
	// MyBox->SetCollisionEnabled(ECollisionEnabled::ProbeOnly);// 仅探测 仅探测 碰撞
	// MyBox->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);// 查询和探测 查询和探测 碰撞


	// 设置碰撞对象
	// MyBox->SetCollisionObjectType(ECC_WorldStatic);// 世界静态
	MyBox->SetCollisionObjectType(ECC_WorldDynamic);// 世界动态
	// MyBox->SetCollisionObjectType(ECC_Pawn);// 设置为Pawn ,pawn是 玩家
	// MyBox->SetCollisionObjectType(ECC_PhysicsBody);// 设置为物理体
	// MyBox->SetCollisionObjectType(ECC_Vehicle);// 设置为 模具 载具
	// MyBox->SetCollisionObjectType(ECC_Destructible);// 设置为可破坏的 ，可破碎物体

	// 碰撞榆社 碰撞响应
	// MyBox->SetCollisionResponseToAllChannels(ECR_Block);// 阻止所有碰撞 block
	// MyBox->SetCollisionResponseToAllChannels(ECR_Ignore);// 忽略所有碰撞
	MyBox->SetCollisionResponseToAllChannels(ECR_Overlap);// 碰撞重叠 overlap ,相应为 overLap

	// MyBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);// 对单个通道进行设置  pawn 角色 overLap
	// MyBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	// MyBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);




	// 设置网格大小
	MyBox->SetBoxExtent(FVector(64, 64, 64));// 设置网格大小 生效了不能设置太小
}

// Called when the game starts or when spawned
void AMyPublicActor::BeginPlay()
{
	Super::BeginPlay();

	if(MyParticle){// 初次进来
		MyParticle->Deactivate();// 关闭粒子
	}

	int a = 10;
	UE_LOG(LogTemp, Warning, TEXT("AMyPublicActor BeginPlay %d"), a);

	if (myActor) {
		UE_LOG(LogTemp, Warning, TEXT("AMyPublicActor BeginPlay myActor %s"), *myActor->GetName());

	}



	// 动态加载静态网格资源
	UStaticMesh* MyTempStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MyTempStaticMesh) {
		MyMesh->SetStaticMesh(MyTempStaticMesh);
	}


	// 动态加载蓝图类并生成Actor
	UClass* myTempClass = LoadClass<AActor>(this, TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	if (myTempClass) {
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(myTempClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}


}

// Called every frame
void AMyPublicActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// UE_LOG(LogTemp, Warning, TEXT("AMyPublicActor Tick"));


	//
	FVector myOffset = FVector(1, 0, 0);
	FHitResult myFHitResult;
	//AddActorLocalOffset(myOffset, false, &myFHitResult);//  本地坐标 偏移
	AddActorWorldOffset(myOffset, false, &myFHitResult);

}

void AMyPublicActor::BeginOverLapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MyParticle->Activate();// 开启粒子
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BeginOverLapFunction"));


	// 碰到 角色的时候 进行 伤害
	AMyPublicCharacter * myCharacter = Cast<AMyPublicCharacter>(OtherActor);
	if (myCharacter)
	{
		// UDamageType::StaticClass() 是 伤害类型
		UGameplayStatics::ApplyDamage(myCharacter, 5.0f, nullptr, this, UDamageType::StaticClass());// 伤害
	}
	
}

void AMyPublicActor::EndOverLapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	MyParticle->Deactivate();// 关闭粒子
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EndOverLapFunction"));
}

void AMyPublicActor::HitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HitFunction"));
}


