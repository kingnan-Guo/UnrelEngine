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
	MyBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);// 仅物理 仅物理 碰撞
	MyBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);// 查询和物理 查询和物理 碰撞
	MyBox->SetCollisionEnabled(ECollisionEnabled::ProbeOnly);// 仅探测 仅探测 碰撞
	MyBox->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);// 查询和探测 查询和探测 碰撞


	// 设置碰撞对象
	MyBox->SetCollisionObjectType(ECC_WorldStatic);// 
	MyBox->SetCollisionObjectType(ECC_WorldDynamic);// 设置为动态物体
	MyBox->SetCollisionObjectType(ECC_Pawn);// 


}

// Called when the game starts or when spawned
void AMyPublicActor::BeginPlay()
{
	Super::BeginPlay();
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BeginOverLapFunction"));
}

void AMyPublicActor::EndOverLapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EndOverLapFunction"));
}

void AMyPublicActor::HitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HitFunction"));
}


