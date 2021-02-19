// Fill out your copyright notice in the Description page of Project Settings.


#include "C_General_Fuction.h"
#include <string>
#include "Kismet/KismetStringLibrary.h"
#include "Kismet\KismetMathLibrary.h"
#include "Kismet\KismetArrayLibrary.h"
#include "Runtime\CoreUObject\Public\UObject\ConstructorHelpers.h"

float UC_General_Fuction::KE_health_cal(float KE, int32 range, float distance, int attack_location,
	int ERA_strengh, TArray<int> self_ERA_list, TArray<int> self_Armor_list, float ERA_revise)
{
	float result = 0;
	result = KE * (1 + range / (5 * distance + 2 * range)) - ERA_strengh * self_ERA_list[attack_location] * ERA_revise - self_Armor_list[attack_location];
	if (result > 0)
	{
		return result;
	}
	else
	{
		return 0;
	}
}

float UC_General_Fuction::CE_health_cal(float CE, int attack_location, int ERA_strengh, TArray<int> self_ERA_list
	, TArray<int> self_Armor_list, float self_armor_conversion_coefficient, float ERA_revise)
{
	float result = 0;
	result = CE - self_ERA_list[attack_location] * ERA_strengh * ERA_revise - self_Armor_list[attack_location] * self_armor_conversion_coefficient;
	if (result > 0)
	{
		return result;
	}
	else
	{
		return 0;
	}
}

float UC_General_Fuction::HE_health_cal(float HE, float HE_self_distance, int attack_location, TArray<int> self_Armor_list)
{
	float result = 0;
	result = HE * float(HE) / (HE_self_distance + 1) / float(self_Armor_list[attack_location] + 1);
	if (result > 0)
	{
		return result;
	}
	else
	{
		return 0;
	}
}

float UC_General_Fuction::KE_ERA_cal(float KE, int ERA_strengh)
{
	if (KE <= float(ERA_strengh) / 2)
	{
		return 0;
	}
	else if (KE >= ERA_strengh)
	{
		return 1;
	}
	else
	{
		return KE / (4 * ERA_strengh);
	}
}

float UC_General_Fuction::CE_ERA_cal(float CE, float ERA_strength)
{
	if (CE < ERA_strength)
	{
		return 1;
	}
	else
	{
		return 1.5;
	}
}

float UC_General_Fuction::HE_ERA_cal(float HE, float ERA_strength, float HE_self_distance)
{
	if (HE <= ERA_strength / 5)
	{
		return 0;
	}
	else if (HE_self_distance > HE)
	{
		return 0;
	}
	else if (HE_self_distance < HE / 2)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

float UC_General_Fuction::ERA_revise_cal(float ERA_health, float const_ERA_health)
{
	if (ERA_health >= const_ERA_health / 2)
	{
		return 1;
	}
	else
	{
		return 1 / ((const_ERA_health / 2 - ERA_health) * (const_ERA_health / 2 - ERA_health));
	}
}

void UC_General_Fuction::vehicle_module_health_cal(TArray<float>& out_vehicle_module_health, TArray<float> vehicle_module_health, int vehicle_module_attacked_enum, float damage)
{
	out_vehicle_module_health = vehicle_module_health;

	if (vehicle_module_attacked_enum % 10 == vehicle_module_attacked_enum)
	{
		out_vehicle_module_health[vehicle_module_attacked_enum] -= damage;
		return;
	}

	int* enum_list = new int[5];
	int len = 0;
	int tp = vehicle_module_attacked_enum;
	for (int i = 0; i < 5; i++)
	{
		enum_list[i] = tp % 10;
		tp /= 10;
		if (tp == 0)
		{
			len = i + 1;
			break;
		}
	}

	int main_module = enum_list[0];
	for (int i = 1; i < len; i++)
	{
		if (enum_list[i] == main_module)
		{
			out_vehicle_module_health[i] -= damage;
		}
		else
		{
			out_vehicle_module_health[i] -= (damage / 3);
		}
	}
}

int UC_General_Fuction::vehicle_attack_location_to_module_attacked_enum(int attack_location, float module_hurt)
{
	if (module_hurt <= 1)
	{
		return attack_location;
	}
	else if (module_hurt <= 2)
	{
		switch (attack_location)
		{
		case 0:
			return 100;
		case 1:
			return 101;
		case 2:
			return 212;
		case 3:
			return 313;
		case 4:
			return 404;
		default:
			return attack_location;
		}
	}
	else
	{
		switch (attack_location)
		{
		case 0:
			return 4100;
		case 1:
			return 32101;
		case 2:
			return 2102;
		case 3:
			return 313;
		case 4:
			return 404;
		default:
			return attack_location;
		}
	}
}

void UC_General_Fuction::attacked_cal(TArray<float>& out_vehicle_module_health, float& out_health, float& out_ERA_health, float& out_ERA_revise, bool& is_morale_cal, float health, float ERA_health, float const_ERA_health,
	float KE, float CE, float HE, float HE_self_distance, int ERA_strength, int32 range, int32 distance, int attack_location, TArray<int> self_ERA_list, TArray<float> vehicle_module_health,
	TArray<int> self_Armor_list, float self_armor_conversion_coefficient, float ERA_revise)
{
	float module_hurt = 0;

	if (KE != 0)
	{
		module_hurt = KE_health_cal(KE, range, distance, attack_location, ERA_strength, self_ERA_list, self_Armor_list, ERA_revise);
		out_health = health - module_hurt;
		out_ERA_health = ERA_health - KE_ERA_cal(KE, ERA_strength);
	}
	else if (CE != 0)
	{
		module_hurt = CE_health_cal(CE, attack_location, ERA_strength, self_ERA_list, self_Armor_list, self_armor_conversion_coefficient, ERA_revise);
		out_health = health - module_hurt;
		out_ERA_health = ERA_health - CE_ERA_cal(CE, ERA_strength);
	}
	else
	{
		module_hurt = HE_health_cal(HE, HE_self_distance, attack_location, self_Armor_list);
		out_health = health - module_hurt;
		out_ERA_health = ERA_health - HE_ERA_cal(HE, ERA_strength, HE_self_distance);
	}

	vehicle_module_health_cal(out_vehicle_module_health, vehicle_module_health, vehicle_attack_location_to_module_attacked_enum(attack_location, module_hurt), module_hurt);
	out_ERA_revise = ERA_revise_cal(ERA_health, const_ERA_health);
	if (out_health != health || out_ERA_health != ERA_health) { is_morale_cal = true; }
	else { is_morale_cal = false; }
}

float UC_General_Fuction::Vector_distance_cal(FVector a, FVector b)
{
	return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y) + (a.Z - b.Z) * (a.Z - b.Z));
}

int32 UC_General_Fuction::morale_to_morale_type(float const_morale, float morale_now)
{
	int morale_type_list[4];
	for (int i = 0; i < 4; i++)
	{
		morale_type_list[i] = const_morale * 0.25 * (i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		if (morale_now <= morale_type_list[i])
		{
			return i;
		}
	}

	return -1;
}

void UC_General_Fuction::is_war_zone_caped(bool& is_cap, int& cap_camp, TArray<int>& out, TArray<int> unit_in_war_zone_list)
{
	if (unit_in_war_zone_list[0] == 0 && unit_in_war_zone_list[1] != 0)
	{
		is_cap = true;
		cap_camp = 1;
	}
	else if (unit_in_war_zone_list[1] == 0 && unit_in_war_zone_list[0] != 0)
	{
		is_cap = true;
		cap_camp = 0;
	}
	else
	{
		is_cap = false;
		cap_camp = -1;
	}
	out = unit_in_war_zone_list;
}

void UC_General_Fuction::unit_in_out_war_cone(bool& is_cap, int& cap_camp, TArray<int>& out, bool in, int unit_camp, TArray<int> unit_in_war_zone_list)
{
	if (in)
	{
		unit_in_war_zone_list[unit_camp] += 1;
	}
	else
	{
		unit_in_war_zone_list[unit_camp] -= 1;
	}
	is_war_zone_caped(is_cap, cap_camp, out, unit_in_war_zone_list);
}

void UC_General_Fuction::add_score_list_parse(int& out_camp, int& out_add_score, TArray<int> tp_add_list)
{
	out_camp = tp_add_list[0] > tp_add_list[1] ? 0 : 1;
	out_add_score = tp_add_list[out_camp] - tp_add_list[int(!bool(out_camp))];
}

float UC_General_Fuction::morale_reflex(float morale_now, float morale_reflex, float const_morale)
{
	float tp = morale_now + morale_reflex;
	return tp > const_morale ? const_morale : tp;
}

void UC_General_Fuction::weapon_supply_cal(TArray<float>& out_temp_weapon_sup, TArray<int>& out_weapon_sup_result, TArray<float> temp_weapon_sup, TArray<float> weapon_sup_cost)
{
	/*TArray<float> out_temp_weapon_sup;
	TArray<int> out_weapon_sup_result;*/
	out_temp_weapon_sup.Init(0, 5);
	out_weapon_sup_result.Init(0, 5);
	int len = 0;
	for (int i = 0; i < weapon_sup_cost.Num(); i++)
	{
		if (weapon_sup_cost[i] != -1)
		{
			len++;
		}
		else
		{
			break;
		}
	}
	for (int i = 0; i < len; i++)
	{
		out_temp_weapon_sup[i] = temp_weapon_sup[i] + 1;
		if (out_temp_weapon_sup[i] >= weapon_sup_cost[i])
		{
			out_temp_weapon_sup[i] -= weapon_sup_cost[i];
			out_weapon_sup_result[i] = 1;
		}
		else
		{
			out_weapon_sup_result[i] = 0;
		}
	}
}

void UC_General_Fuction::vehicle_onlyself_supply_cal(bool& is_vehicle_sup_over, float& now_health, float& now_ERA_health, float& now_oil,
	float& now_APS_number, float& now_smoke_number, TArray<float>& out_temp_sup_list_self, float health, float const_health,
	float per_health_sup_time, float ERA_health, float const_ERA_health, float per_ERA_health_sup_time, float oil, float const_oil,
	float per_10_oil_sup_time, float APS_num, float const_APS_num, float per_APS_sup_time, float smoke_num, float const_smoke_num, float per_smoke_sup_time,
	TArray<float> temp_sup_list_self)
{
	TArray<float> property_now = { health,ERA_health,oil,APS_num,smoke_num };
	TArray<float> property_const = { const_health,const_ERA_health,const_oil,const_APS_num,const_smoke_num };
	TArray<float> property_sup_time = { per_health_sup_time,per_ERA_health_sup_time,per_10_oil_sup_time,per_APS_sup_time,per_smoke_sup_time };
	TArray<int> property_sup_multiplier = { 1,1,10,1,1 };
	TArray<float> out_property = { now_health,now_ERA_health,now_oil,now_APS_number,now_smoke_number };
	out_temp_sup_list_self = temp_sup_list_self;

	float tp_sup_incre = 0;
	bool tp_is_sup_over = false;
	is_vehicle_sup_over = true;

	for (int i = 0; i < temp_sup_list_self.Num(); i++)
	{
		vehicle_general_sup(out_property[i], tp_sup_incre, tp_is_sup_over, property_now[i], property_const[i], property_sup_time[i], property_sup_multiplier[i], temp_sup_list_self, i);
		out_temp_sup_list_self[i] += tp_sup_incre;
		is_vehicle_sup_over = is_vehicle_sup_over && tp_sup_incre;
	}

	now_health = out_property[0];
	now_ERA_health = out_property[1];
	now_oil = out_property[2];
	now_APS_number = out_property[3];
	now_smoke_number = out_property[4];
}

void UC_General_Fuction::vehicle_general_sup(float& out_property, float& temp_sup_list_increment, bool& is_property_sup_over, float property,
	float const_property, float per_property_sup_time, int sup_multiplier, TArray<float> temp_sup_list_self, int index)
{
	if (property == const_property)
	{
		out_property = const_property;
		temp_sup_list_increment = 0;
		is_property_sup_over = true;
		return;
	}

	float tp = temp_sup_list_self[index] + 1;
	if (tp >= per_property_sup_time)
	{
		temp_sup_list_increment = tp - per_property_sup_time;
		out_property = (property + sup_multiplier) > const_property ? const_property : (property + sup_multiplier);
		is_property_sup_over = false;
	}
	else
	{
		temp_sup_list_increment = 1;
		out_property = property;
		is_property_sup_over = true;
	}
}

void UC_General_Fuction::helo_onlyself_supply_cal(bool& is_helo_sup_over, float& now_health, float& now_oil,
	float& now_hot_bait_number, TArray<float>& out_temp_sup_list_self, float health, float const_health, float per_health_sup_time, float oil, float const_oil,
	float per_10_oil_sup_time, float hot_bait_num, float const_hot_bait_num, float per_hot_bait_sup_time, TArray<float> temp_sup_list_self)
{
	TArray<float> property_now = { health,oil,hot_bait_num };
	TArray<float> property_const = { const_health,const_oil,const_hot_bait_num };
	TArray<float> property_sup_time = { per_health_sup_time,per_10_oil_sup_time,per_hot_bait_sup_time };
	TArray<int> property_sup_multiplier = { 1,1,1 };
	TArray<float> out_property = { now_health,now_oil,now_hot_bait_number };
	out_temp_sup_list_self = temp_sup_list_self;

	float tp_sup_incre = 0;
	bool tp_is_sup_over = false;
	is_helo_sup_over = true;

	for (int i = 0; i < temp_sup_list_self.Num(); i++)
	{
		vehicle_general_sup(out_property[i], tp_sup_incre, tp_is_sup_over, property_now[i], property_const[i], property_sup_time[i], property_sup_multiplier[i], temp_sup_list_self, i);
		out_temp_sup_list_self[i] += tp_sup_incre;
		is_helo_sup_over = is_helo_sup_over && tp_sup_incre;
	}

	now_health = out_property[0];
	now_oil = out_property[1];
	now_hot_bait_number = out_property[2];
}

void UC_General_Fuction::Boardwalk_radius_cal(FVector& random_boardwalk, float speed, float boardwalk_radius, int range, float X_multi, float Y_multi, float Z_multi)
{
	float max_offset = boardwalk_radius / (range / (speed / 100));
	random_boardwalk.X = max_offset * ((rand() - RAND_MAX / 2) / float(RAND_MAX)) * X_multi;
	random_boardwalk.Y = max_offset * ((rand() - RAND_MAX / 2) / float(RAND_MAX)) * Y_multi;
	random_boardwalk.Z = max_offset * ((rand() - RAND_MAX / 2) / float(RAND_MAX)) * Z_multi;
}

void UC_General_Fuction::high_performance_CROWS_rotate_control(bool& is_over, float& CROWS_rotate, float& CROWS_gun_barrel_rotate, float aiming_z_CROWS, float aiming_x_CROWS_gun_barrel,
	float z_CROWS, float x_CROWS_gun_barrel)
{
	if (abs(z_CROWS - aiming_z_CROWS) < 1 && abs(x_CROWS_gun_barrel - aiming_x_CROWS_gun_barrel) < 1)
	{
		is_over = true;
		CROWS_rotate = 0;
		CROWS_gun_barrel_rotate = 0;
	}
	else
	{
		is_over = false;
	}

	CROWS_rotate = high_performance_CROWS_rotate_cal_function(aiming_z_CROWS, z_CROWS);
	CROWS_gun_barrel_rotate = high_performance_CROWS_rotate_cal_function(aiming_x_CROWS_gun_barrel, x_CROWS_gun_barrel);
}

float UC_General_Fuction::high_performance_CROWS_rotate_cal_function(float aiming_rotation, float now_rotation)
{
	if (abs(aiming_rotation - now_rotation) > 10)
	{
		float tp = (aiming_rotation - now_rotation) / 10;
		return (abs(tp) > 5 ? (5 * abs(tp) / tp) : tp)* (abs(tp) * 10 > 180 ? -1 : 1);
	}
	else
	{
		float tp = (aiming_rotation - now_rotation) / 10;
		return abs(tp) / tp;
	}
}

int UC_General_Fuction::set_now_salvo(bool can_fire_all, int const_bullet_in_magazine, int now_salvo, int salvo)
{
	if (now_salvo < salvo)
	{
		return salvo;
	}
	else
	{
		if (can_fire_all)
		{
			return now_salvo == const_bullet_in_magazine ? 1 : const_bullet_in_magazine;
		}
		else
		{
			return 1;
		}
	}
}

bool UC_General_Fuction::is_in_same_camp(int self_camp, int other_camp)
{
	return self_camp == other_camp;
}

bool UC_General_Fuction::can_vehicle_load_soldier(int vehicle_type)
{
	if (vehicle_type > 21)
	{
		return false;
	}
	switch (vehicle_type)
	{
	case 2:
		return true;
	case 3:
		return true;
	case 4:
		return true;
	case 10:
		return true;
	case 11:
		return false;
	default:
		return false;
	}

}

bool UC_General_Fuction::can_get_on(int vehicle_type, int self_camp, int other_camp)
{
	return can_vehicle_load_soldier(vehicle_type) && is_in_same_camp(self_camp, other_camp);
}

void UC_General_Fuction::attacked_cal_person(TArray<int>& out_body_armor_list, TArray<float>& out_body_health_list, float& out_health, float health, int enemy_anti_person, int attack_location,
	int enemy_range, int enemy_distance, int body_armor_loss_revise, TArray<int> self_body_armor_list, TArray<float> self_body_health_list, TArray<float> damage_multiplier_list)
{
	int real_anti_person = real_anti_person_cal(enemy_anti_person, enemy_range, enemy_distance);
	int tp_health_hurt = 0;
	float tp_total_health_hurt = 0;

	person_armor_cal_and_update(out_body_armor_list, tp_health_hurt, real_anti_person, attack_location, body_armor_loss_revise, self_body_armor_list);
	person_health_cal_and_update(out_body_health_list, tp_total_health_hurt, tp_health_hurt, attack_location, self_body_health_list, damage_multiplier_list);
	out_health = health - tp_total_health_hurt;
}

int UC_General_Fuction::real_anti_person_cal(int enemy_anti_person, int enemy_range, int enemy_distance)
{
	return enemy_anti_person * (1 + (enemy_range - enemy_distance) / float(enemy_range) / 5);
}

void UC_General_Fuction::person_armor_cal_and_update(TArray<int>& out_armor_list, int out_health_hurt, int real_anti_person, int attack_location, int body_armor_loss_revise, TArray<int> self_armor_list)
{
	int armor = self_armor_list[attack_location];
	out_armor_list = self_armor_list;

	if (real_anti_person < armor / 2)
	{
		out_armor_list[attack_location] = armor - 1;
		out_health_hurt = 0;
	}
	else if (real_anti_person < armor)
	{
		int tp = ((real_anti_person - armor / 2) / 2) < (10 - body_armor_loss_revise) ? ((real_anti_person - armor / 2) / 2) : (10 - body_armor_loss_revise);
		out_armor_list[attack_location] = armor - tp;
		out_health_hurt = 1;
	}
	else
	{
		out_armor_list[attack_location] = armor - 10 + body_armor_loss_revise;
		out_health_hurt = real_anti_person - armor;
	}

	if (out_armor_list[attack_location] < 0)
	{
		out_armor_list[attack_location] = 0;
	}
}

void UC_General_Fuction::person_health_cal_and_update(TArray<float>& out_body_health_list, float& total_health_hurt, float health_hurt, int attack_location, TArray<float> body_health_list,
	TArray<float> damage_multiplier_list)
{
	float tp_body_health = body_health_list[attack_location];
	out_body_health_list = body_health_list;

	int tp_hurt = (tp_body_health - health_hurt) > 0 ? health_hurt : tp_body_health;
	out_body_health_list[attack_location] = tp_body_health - tp_hurt;

	total_health_hurt = tp_hurt * damage_multiplier_list[attack_location];
}

bool UC_General_Fuction::ricochet_static_mesh(FVector bullet_vector, FVector hit_normal, float KE, int anti_person)
{
	float angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(bullet_vector.GetSafeNormal(), hit_normal.GetSafeNormal())));
	float ricochet_angle = 0;
	if (KE != 0)
	{
		ricochet_angle = 10 / (KE / 2 + 1);
	}
	else
	{
		ricochet_angle = 20 / (anti_person / 100 + 1);
	}

	return ricochet_general_cal(angle, ricochet_angle);
}

bool UC_General_Fuction::ricochet_vehicle(FVector bullet_vector, FVector hit_normal, float KE, int hit_armor)
{
	float angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(bullet_vector.GetSafeNormal(), hit_normal.GetSafeNormal())));
	float ricochet_angle = 0;

	ricochet_angle = (10 + hit_armor / 5) / (KE / 2 + 1);

	return ricochet_general_cal(angle, ricochet_angle);
}

bool UC_General_Fuction::ricochet_helo(FVector bullet_vector, FVector hit_normal, float KE, int hit_armor)
{
	float angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(bullet_vector.GetSafeNormal(), hit_normal.GetSafeNormal())));
	float ricochet_angle = ricochet_angle = (5 + hit_armor) / (KE / 2 + 1);

	return ricochet_general_cal(angle, ricochet_angle);
}

bool UC_General_Fuction::ricochet_person(FVector bullet_vector, FVector hit_normal, float KE, int anti_person, int hit_body_armor)
{
	if (KE != 0 || anti_person >= 50)
	{
		return false;
	}

	float angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(bullet_vector.GetSafeNormal(), hit_normal.GetSafeNormal())));
	float ricochet_angle = (20 + hit_body_armor / 10) / (anti_person / 100 + 1);

	return ricochet_general_cal(angle, ricochet_angle);
}

bool UC_General_Fuction::ricochet_general_cal(float angle, float ricochet_angle)
{
	int tp = (rand() / float(RAND_MAX)) * ricochet_angle;
	return ((90 - angle) < ricochet_angle) && (tp > (90 - angle));//the expression is equivalent to (tp > (90 - angle))
}

void UC_General_Fuction::abnormal_status_cal(FString& out_status_string, TArray<float> vehicle_module_health, TArray<float> const_vehicle_module_health, TArray<FString> vehicle_abnormal_status_rate_list)
{
	int index_list[] = { 0,6,20,27,31,35 };
	out_status_string = "";

	for (int i = 0; i < vehicle_module_health.Num(); i++)
	{
		if (vehicle_module_health[i] < const_vehicle_module_health[i] / 2)
		{
			for (int j = index_list[i]; j < index_list[i + 1]; j++)
			{
				if (FCString::Atof(*(vehicle_abnormal_status_rate_list[j])) == 0)
				{
					break;
				}

				float ftp = FCString::Atof(*(vehicle_abnormal_status_rate_list[j]));
				float ftp1 = (rand() / float(RAND_MAX));
				bool tp = ftp > ftp1;
				if (tp)
				{
					out_status_string.Append(enum_index_to_fstring(j));
				}
			}
		}
	}
}

FString UC_General_Fuction::enum_index_to_fstring(int m)
{
	if (m < 10)
	{
		return FString::FromInt(m);
	}
	else
	{
		char tp = m - 10 + 65;
		std::string tp1 = std::string(1, tp);
		return FString(tp1.c_str());
	}
}

int UC_General_Fuction::enum_index_fstring_to_int(FString str)
{
	char* tp_str = TCHAR_TO_UTF8(*str);
	int tp_int = *tp_str - '0';
	if (tp_int > 10)
	{
		tp_int -= 7;
	}
	return tp_int;
}

void UC_General_Fuction::abnormal_status_cal_check(FString& out_status, bool& have_new, FString& new_status, FString now_status,
	TArray<float> vehicle_module_health, TArray<float> const_vehicle_module_health, TArray<FString> vehicle_abnormal_status_rate_list)
{
	TArray<FString> tp_now_status_list;
	TArray<FString> tp_append_status_list;
	new_status = "";
	out_status = now_status;
	have_new = false;
	FString append_status;
	abnormal_status_cal(append_status, vehicle_module_health, const_vehicle_module_health, vehicle_abnormal_status_rate_list);

	tp_now_status_list = UKismetStringLibrary::GetCharacterArrayFromString(now_status);
	tp_append_status_list = UKismetStringLibrary::GetCharacterArrayFromString(append_status);

	for (int i = 0; i < tp_append_status_list.Num(); i++)
	{
		int check = 1;
		for (int j = 0; j < tp_now_status_list.Num(); j++)
		{
			if (tp_now_status_list[j] == tp_append_status_list[i])
			{
				check = 0;
				break;
			}
		}

		if (check == 1)
		{
			out_status.Append(tp_append_status_list[i]);
			new_status.Append(tp_append_status_list[i]);
			have_new = true;
		}
	}
}

void UC_General_Fuction::Exp_cal(float& prograss, int& max_exp, int now_exp, int level)
{
	max_exp = level * level * 25 + 100;
	prograss = float(now_exp) / max_exp;
}

void UC_General_Fuction::large_int_normalize_to_string(FString& out_normalize_string, int input)
{
	int tp_int = input;
	while (tp_int != 0)
	{
		int tp = tp_int % 1000;
		out_normalize_string.AppendInt(tp);
		out_normalize_string.AppendChar(' ');
		tp_int /= 1000;
	}

	out_normalize_string = out_normalize_string.Reverse();
}

void UC_General_Fuction::helo_close_engine_decline_buoyancy(float& out_buoyancy, int in_index)
{
	out_buoyancy = (1000 - in_index) * 980;
}

void UC_General_Fuction::set_camera_FOV(float& out_FOV, int& aiming_multipiler, float now_FOV, TArray<float> FOV_list, bool is_add)
{
	for (int i = 0; i < FOV_list.Num(); i++)
	{
		if (FOV_list[i] == now_FOV)
		{
			if (is_add)
			{
				out_FOV = FOV_list[i == FOV_list.Num() - 1 ? i : i + 1];
				break;
			}
			else
			{
				out_FOV = FOV_list[i == 0 ? i : i - 1];
				break;
			}
		}
	}

	aiming_multipiler = 90 / out_FOV;
}

void UC_General_Fuction::get_now_aiming_multipiler(int& out_multipiler, float now_FOV)
{
	out_multipiler = 90 / now_FOV;
}

void UC_General_Fuction::attacked_comp_to_location(int& attack_loaction, FString comp_name)
{
	FString tp_str = comp_name.Right(2);
	TArray<FString> tp_array = UKismetStringLibrary::GetCharacterArrayFromString(tp_str);
	attack_loaction = FCString::Atoi(*(tp_array[0]));
}

void UC_General_Fuction::is_ATGM_FoF(bool& out_bool, FString ATGM_property)
{
	TArray<FString> tp_array = UKismetStringLibrary::GetCharacterArrayFromString(ATGM_property);
	out_bool = false;

	for (int i = 0; i < tp_array.Num(); i++)
	{
		if (tp_array[i] == FString::FromInt(3))
		{
			out_bool = true;
			break;
		}
	}
}

float UC_General_Fuction::high_performance_AI_standby_CROWS_rotate(int total_index, int now_index, int stop_duration, float rotate_speed)
{
	int tp_division = (total_index - stop_duration * 2) / 4;
	if (now_index < tp_division)
	{
		return rotate_speed;
	}
	else if (now_index < tp_division + stop_duration)
	{
		return 0;
	}
	else if (now_index < total_index - tp_division - stop_duration)
	{
		return -rotate_speed;
	}
	else if (now_index < total_index - tp_division)
	{
		return 0;
	}
	else
	{
		return rotate_speed;
	}
}

void UC_General_Fuction::magazine_array_parse(int& out_magazine_number, bool& is_rewrite_bullet_number, int& rewrite_per_magazine_bullet_number, TArray<int> origin_data)
{
	out_magazine_number = origin_data[1];
	is_rewrite_bullet_number = bool(origin_data[0]);
	rewrite_per_magazine_bullet_number = origin_data[0];
}

void UC_General_Fuction::unit_type_to_unit_status_enum(int& out_status_enum, FString unit_type)
{
	int tp_index = enum_index_fstring_to_int(unit_type);
	if (tp_index < 10)
	{
		out_status_enum = 0;
	}
	else if (tp_index < 22)
	{
		out_status_enum = 1;
	}
	else
	{
		out_status_enum = 2;
	}
}

void UC_General_Fuction::high_performance_turret_rotate_to_degrees(float& out_axis, bool& is_turret_rotate_rdy, FVector enemy_location, FVector my_location, float now_turret_degrees,
	float pre_aim_turret_rotate)
{
	FVector* tp_vector_degrees = new FVector(0);
	*tp_vector_degrees += (enemy_location - my_location).GetSafeNormal();
	float tp_location_rotate_degrees = (*tp_vector_degrees).Rotation().Yaw;
	tp_location_rotate_degrees += pre_aim_turret_rotate;
	tp_location_rotate_degrees -= now_turret_degrees;
	if (UKismetMathLibrary::NearlyEqual_FloatFloat(abs(tp_location_rotate_degrees), 0, 0.1))
	{
		out_axis = tp_location_rotate_degrees;
		is_turret_rotate_rdy = true;
	}
	else if (UKismetMathLibrary::NearlyEqual_FloatFloat(abs(tp_location_rotate_degrees), 0, 10))
	{
		out_axis = tp_location_rotate_degrees / 10;
		is_turret_rotate_rdy = false;
	}
	else
	{
		out_axis = tp_location_rotate_degrees / abs(tp_location_rotate_degrees);
		is_turret_rotate_rdy = false;
	}
}

void UC_General_Fuction::high_performance_barrel_rotate_to_degrees(float& out_axis, bool& is_barrel_rotate_rdy, float pre_aim_turret_rotate, float now_barrel_degrees)
{
	float tp_will_rotate_pitch = pre_aim_turret_rotate - now_barrel_degrees;
	if (UKismetMathLibrary::NearlyEqual_FloatFloat(abs(tp_will_rotate_pitch), 0, 0.1))
	{
		out_axis = tp_will_rotate_pitch;
		is_barrel_rotate_rdy = true;
	}
	else if (UKismetMathLibrary::NearlyEqual_FloatFloat(abs(tp_will_rotate_pitch), 0, 10))
	{
		out_axis = tp_will_rotate_pitch / 10;
		is_barrel_rotate_rdy = false;
	}
	else
	{
		out_axis = tp_will_rotate_pitch / abs(tp_will_rotate_pitch);
		is_barrel_rotate_rdy = false;
	}
}

void UC_General_Fuction::auto_advance_cal_after_rotate(float& turret_advance_rotate_z, float& barrel_advance_rotate_y, FVector enemy_location
	, FVector enemy_speed, FVector my_location, float my_pitch, float bullet_speed)
{
	float distance = Vector_distance_cal(enemy_location, my_location);
	float TADV = 0;
	time_advance_cal(TADV, distance, enemy_speed, bullet_speed);
	FVector* tp_vector = new FVector(0);
	*tp_vector += enemy_location + enemy_speed * TADV;
	float adv_distance = Vector_distance_cal(*tp_vector, my_location);

	turret_advance_rotate_z = FMath::RadiansToDegrees(acosf(FVector::DotProduct((enemy_location - my_location).GetSafeNormal(), (*tp_vector - my_location).GetSafeNormal())));
	barrel_pitch_cal(barrel_advance_rotate_y, *tp_vector, my_location, my_pitch, bullet_speed, TADV);
}

void UC_General_Fuction::time_advance_cal(float& tadv, float distance, FVector enemy_speed, int bullet_speed)
{
	float enemy_speed_num = enemy_speed.Size();
	#define G 980
	#define BULLET_SPEED_CM (bullet_speed*100)
	#define VA_VB (enemy_speed_num-BULLET_SPEED_CM)
	/*
	#define TADV_CAL(va,vb,s) \
		VAR_VALID \
		( ((va)-(vb)+sqrt(((vb)-(va))*((vb)-(va))-4*G*s))/(-2*G), \
		((va)-(vb)-sqrt(((vb)-(va))*((vb)-(va))-4*G*s))/(-2*G) )
		*/

	tadv = (VA_VB + sqrt(VA_VB * VA_VB - 4 * G * distance)) / (-2 * G);
}

void UC_General_Fuction::barrel_pitch_cal(float& out_pitch, FVector enemy_adv_location, FVector my_location, float my_pitch, float bullet_speed, float TADV)
{
	#define G 980
	#define VECTOR2_SUB(a) (enemy_adv_location.a-my_location.a)
	#define VECTOR2_DIS(a,b) (sqrt((a)*(a)+(b)*(b)))

	float tp_adv_2d_distance = VECTOR2_DIS(VECTOR2_SUB(X), VECTOR2_SUB(Y));
	UE_LOG(LogTemp, Log, TEXT("tp_adv_2d_distance %f"), tp_adv_2d_distance);
	float location_pitch = acosf(tp_adv_2d_distance / (enemy_adv_location-my_location).Size());//radian
	UE_LOG(LogTemp, Log, TEXT("location_pitch %f"), location_pitch);
	UE_LOG(LogTemp, Log, TEXT("(enemy_adv_location-my_location).Size() %f"), (enemy_adv_location - my_location).Size());
	UE_LOG(LogTemp, Log, TEXT("tp_adv_2d_distance %f"), tp_adv_2d_distance);
	out_pitch = FMath::RadiansToDegrees(asinf(cosf(location_pitch) * G * TADV / 2 / (bullet_speed * 100)) + location_pitch - my_pitch);
	UE_LOG(LogTemp, Log, TEXT("out_pitch %f"), out_pitch);
}