// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "SMagicProjectile.h"
#include "Math/UnitConversion.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetSimulatePhysics(true);
	BaseMesh->SetNotifyRigidBodyCollision(true);
	BaseMesh->OnComponentHit.AddDynamic(this,&ASExplosiveBarrel::OnHit);
	RootComponent = BaseMesh;
	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForceComp"));
	ForceComp->SetupAttachment(BaseMesh);
	ForceComp->SetAutoActivate(false);
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	ForceComp->bImpulseVelChange = true;
	ForceComp->Radius = 750.0f;
	ForceComp->ImpulseStrength = 2500.0f;
}


// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASExplosiveBarrel::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		   UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		   const FHitResult& Hit)
{
	if (OtherActor->IsA(ASMagicProjectile::StaticClass()))
	{
		Explode();
		UE_LOG(LogTemp,Warning, TEXT("otherActor: %s, at game time: %f"),*GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
		FString CombinedString = FString::Printf(TEXT("Hit at loction: %s"),*Hit.ImpactPoint.ToString());
		DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
	}
}

void ASExplosiveBarrel::Explode()
{
	//BaseMesh->AddImpulse(FVector(1000,1000,1000), NAME_None,true);
	ForceComp->FireImpulse();
	
	UE_LOG(LogTemp, Log, TEXT("Onhit in Explosive Barrel"));
	
}