#!/usr/bin/env python3
def actor_scale(level: int):
	base_hp_ = 15
	base_str_ = 5
	base_def_ = 3
	bonus_str_ = 0
	bonus_hp_ = 0
	bonus_def_ = 0
	dif = level
	base_hp_ += round((bonus_hp_ + 1.0) * 13.0 * dif)
	base_str_ += round((bonus_str_ + 1.0) * 4.0 * dif)
	base_def_ += round((bonus_def_ + 1.0) * 3.0 * dif)


def player_scale(level: int) -> tuple[int, int, int]:
	base_hp_ = 25
	base_str_ = 5
	base_def_ = 4
	bonus_hp_ = 0.05
	bonus_str_ = 0.05
	bonus_def_ = 0.0125
	dif = level
	base_hp_ += round((bonus_hp_ + 1.05) * 14.5 * dif)
	base_str_ += round((bonus_str_ + 1.00) * 4.0 * dif)
	# increase hardiness against mobs
	base_def_ += round((bonus_def_ + 1.00) * 2.5 * dif)

	return base_hp_, base_str_, base_def_


def mob_scale(level: int, tier: int) -> tuple[int, int, int]:
	base_hp_ = 16
	base_str_ = 6
	base_def_ = 3
	modifier = 1
	divider = 26
	tier_scale = 0.35
	if level < 10:
		tier_scale = 0
	elif level < 20:
		tier_scale = 0.125
	elif level < 40:
		tier_scale = 0.25
	elif level < 60:
		tier_scale = 0.30

	bonus_hp_ = 0.125
	bonus_str_ = 0.25
	bonus_def_ = 0.125

	if tier == 0:
		modifier += (-1 / divider)
	elif tier == 1:
		modifier = 1
	elif tier < 5:
		modifier += ((tier - tier_scale) / (divider + 0.25))
	else:
		modifier += ((tier - tier_scale) / (divider - 0.10))

	if tier < 1:
		dif = level - 0.25

	elif tier == 1:
		dif = level
	else:
		dif = level + ((tier + 0.0) / 1.50)
		bonus_hp_ += ((tier * 1.25) / 10)
		bonus_str_ += ((tier * 1.01) / 30)
		bonus_def_ += ((tier * 1.25) / 40)

	base_hp_ += round(((bonus_hp_ + 1.0) * 15 * modifier * dif) + (tier - 0.5))
	base_str_ += round(((bonus_str_ + 1.0) * 3.95 * modifier * dif))
	base_def_ += round(((bonus_def_ + 1.0) * 2.50 * modifier * dif))
	return base_hp_, base_str_, base_def_


def weapon_scale(level: int, tier: int) -> int:
	add_str = 0
	if tier == 0:
		modifier = 0.95
		add_str = 1.5
	elif tier == 1:
		modifier = 1
		level += 0.5
		add_str = 1.5
	else:
		modifier = 1 + ((tier - 1) / 4)
		level += ((tier - 1) / 2)
		add_str = 1 + ((tier + 1) / 5)

	dmg = round((level * 1.45 * modifier) + add_str) + 1
	return dmg


def armor_scale(level: int, tier: int) -> int:
	level += (tier - 1)
	if tier == 0:
		modifier = 0.85
	elif tier == 1:
		modifier = 1.05
	else:
		modifier = 1 + ((tier - 1) / 5)
	def_ = round((level * 1.55 * modifier) + (tier / 3)) + 1
	return def_

def potion_scale(level: int, tier: int) -> int:
	return round( ((level*3.5*(1+((tier-1)/3.125))) + (tier-1) ) )


for i in range(0, 2):
	player_hp, player_str, player_def = player_scale(i)
	print(f"Player HP:{player_hp} STR:{player_str} DEF:{player_def}")
	for j in range(6,7):
		print("Potion HP:{}".format(potion_scale(i,j)))
		mob_hp, mob_str_, mob_def_ = mob_scale(i, j)
		print("Mob Lvl:{} Tier:{}".format(i, j))
		print("HP:{} STR:{} DEF:{}".format(mob_hp, mob_str_, mob_def_))
		for k in range(6,7):
			weapon_dmg = weapon_scale(i, k) + player_str
			armor_def = armor_scale(i, k) + player_def
			print("Player->Mob Dmg:{} Weapon Tier:{} Weapon Dmg:{}".format(weapon_dmg - mob_def_, k,weapon_dmg-player_str))
			print("Mob->Player Dmg:{}, Armor Tier:{} Armor Def:{}".format(mob_str_ - armor_def, k, armor_def-player_def))
		print("================================================================")
	print("---------------------------------------------------------------")
