// Fill out your copyright notice in the Description page of Project Settings.


#include "Super_unit.h"

// Sets default values
ASuper_unit::ASuper_unit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ASuper_unit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuper_unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASuper_unit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASuper_unit::set_tp_distance_for_sort(FVector location)
{
	set_my_location();
	tp_distance_for_sort = sqrt((my_location.X - location.X)* (my_location.X - location.X)+ (my_location.Y - location.Y)* 
		(my_location.Y - location.Y)+ (my_location.Z - location.Z)* (my_location.Z - location.Z));
}

void ASuper_unit::set_my_location()
{
	my_location = this->GetActorLocation();
}

void ASuper_unit::distance_sort_unit_list(TArray<ASuper_unit*>& out_sorted_array, TArray<ASuper_unit*> unit_list, FVector self_location)
{
	int len = unit_list.Num();
	int* tp_remove = new int[len];
	for (int i = 0; i < len; i++)
	{
		tp_remove[i] = 0;
		if (IsValid(unit_list[i]))
		{
			(unit_list)[i]->set_tp_distance_for_sort(self_location);
		}
		else
		{
			tp_remove[i] = 1;
		}
	}
	
	for (int i = 0; i < len; i++)
	{
		if (tp_remove[i])
		{
			unit_list.RemoveAt(i);
		}
	}
	
	if (len > 1)
	{
		(unit_list).Sort([](const ASuper_unit& a, const ASuper_unit& b) {return a.tp_distance_for_sort < b.tp_distance_for_sort; });
	}

	out_sorted_array = (unit_list);
}

FVector ASuper_unit::get_next_nav_point(ASuper_unit* target_enemy_unit, FVector target_location, bool is_target_unit)
{
	set_my_location();
	const FVector location_now = my_location;
	UNavigationPath* Navpath;

	if (is_target_unit)
	{
		Navpath = UNavigationSystemV1::FindPathToActorSynchronously(this, my_location, target_enemy_unit);
	}
	else
	{
		Navpath = UNavigationSystemV1::FindPathToLocationSynchronously(this, my_location, target_location);
	}

	if (Navpath->PathPoints.Num() > 1)
	{
		return Navpath->PathPoints[1];
	}
	else
	{
		return my_location;
	}
}