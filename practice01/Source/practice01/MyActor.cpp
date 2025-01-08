#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	coordinate = FVector2D(0.0f, 0.0f);
	FTransform t = this->GetActorTransform();
	FVector v = t.GetLocation();
	v.X = coordinate.X;
	v.Y = coordinate.Y;
	t.SetLocation(v);
	this->SetActorTransform(t);

	VectorArray.Add(coordinate);
	iCnt = 0;
	evCnt = 0;
	fDistance = 0.0f;
	totDist = 0.0f;
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (iCnt<10)
	{
		move();
	}
	if (iCnt == 10) //10회 이동후에는 총 이동거리와 총 이벤트 발생횟수를 출력
	{
		UE_LOG(LogTemp, Warning, TEXT("총 이동거리 : %.2f , 총 이벤트 발생횟수 : %d "), totDist, evCnt);
		iCnt++;
	}
}

void AMyActor::move()
{
	coordinate.X += step();//이동
	coordinate.Y += step();
	FTransform t = this->GetActorTransform();
	FVector v = t.GetLocation();
	v.X += coordinate.X;
	v.Y += coordinate.Y;
	t.SetLocation(v);
	this->SetActorTransform(t);
	VectorArray.Add(coordinate);//이동 후 좌표 저장
	iCnt++; //이동 카운트 증가

	UE_LOG(LogTemp, Warning, TEXT("%d 회 이동 , 좌표 x : %.f, y : %.f "), iCnt, coordinate.X, coordinate.Y);
	
	

	if (VectorArray.IsValidIndex(iCnt - 1)) //인덱스가 유효하면 
	{
		//각 스텝마다 이전 좌표기준 이동 거리를 계산해서 출력

		//fDistance = FMath::Sqrt(FMath::Square(VectorArray[iCnt].X- VectorArray[iCnt-1].X) + FMath::Square(VectorArray[iCnt].Y - VectorArray[iCnt - 1].Y));
		//distance = FVector2D::Distance(VectorArray[iCnt], VectorArray[iCnt-1]);

		fDistance = Mydistance(VectorArray[iCnt], VectorArray[iCnt-1]);
		totDist += fDistance;
		UE_LOG(LogTemp, Warning, TEXT("이동거리 : %.2f"), fDistance);
	}

	bool bEvent = FMath::RandRange(0, 1) == 1;
	if (bEvent) //각 스텝마다, 50% 확률로 랜덤하게 , 
	{
		{
			//이벤트가 발생
		}
		evCnt++;
		UE_LOG(LogTemp, Warning, TEXT("이벤트 발생")); //각  스텝마다 이벤트 발생여부를 출력
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("이벤트 미발생"), bEvent);
	
}

int32_t AMyActor::step()
{
	return FMath::RandRange(0, 1);
}

float AMyActor::Mydistance(FVector2D first, FVector2D second)
{
	float dx = first.X - second.X;
	float dy = first.Y - second.Y;
	return FMath::Sqrt(dx * dx + dy * dy);
}