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
	if level > 1:
		dif = level-1
		base_hp_ += round((bonus_hp_ + 1.05) * 14.5 * dif)
		base_str_ += round((bonus_str_ + 1.00) * 4.0 * dif)
		# increase hardiness against mobs
		base_def_ += round((bonus_def_ + 1.00) * 2.5 * dif)

	return base_hp_, base_str_, base_def_


def mob_scale(level: int, tier: int) -> tuple[int, int, int, int]:
	#tier 0=trash, 1=normal, 2=rare, 3=elite, 4=miniboss, 5=boss
	base_hp_ = 16
	base_str_ = 6
	base_def_ = 3
	if level > 1:
		modifier = 1
		divider = 28
		tier_scale = 0.40
		if level < 5:
			tier_scale = -0.75
		if level < 10:
			tier_scale = 0.20
		elif level < 20:
			tier_scale = 0.25
		elif level < 40:
			tier_scale = 0.30
		elif level < 60:
			tier_scale = 0.35

		bonus_hp_ = 0.25
		bonus_str_ = 0.25
		bonus_def_ = 0.125

		if tier == 0:
			modifier += (-1 / (divider-0.25))
		elif tier == 1:
			modifier = 1
		elif tier < 5:
			modifier += ((tier - tier_scale) / (divider + 0.25))
		else:
			modifier += ((tier - tier_scale) / (divider - 0.15))
	
		if tier < 1:
			dif = level - 0.25

		elif tier == 1:
			dif = level
		else:
			dif = level + ((tier + 0.0) / 1.50)
			bonus_hp_ += ((tier * 1.25) / 7)
			bonus_str_ += ((tier * 1.00) / 95)
			bonus_def_ += ((tier * 1.25) / 45)

		base_hp_ += round(((bonus_hp_ + 1.0) * 18 * modifier * dif) + (tier - 0.5))
		base_str_ += round(((bonus_str_ + 1.0) * 5.55 * modifier * dif))
		base_def_ += round(((bonus_def_ + 1.0) * 2.50 * modifier * dif))
	tmp = level+1
	xp = round(tmp*(tmp*0.79)*(1+(tier-1)/3.25))+2
	return base_hp_, base_str_, base_def_,xp


def weapon_scale(level: int, tier: int) -> int:
	#tiers are 0=junk,1=common, 2= uncommon, 3 = rare, 4=epic, 5= legendary
	add_str = 1.5
	modifier = 1
	if level < 10:
		multiplier = 5.1
	elif level < 20:
		multiplier = 5.08
	elif level < 40:
		multiplier = 5.05
	elif level < 60:
		multiplier = 5.01
	else:
		multiplier = 4.96
	
	if tier == 0:
		modifier = 0.85
		add_str = 1.5
	elif tier > 1:
		modifier += [2/16,5/16,8/16,11/16][tier-2]
		if level < 10:
			multiplier = 5.10 + 0.05
		elif level < 20:
			multiplier = 5.08 + 0.04
		elif level < 40:
			multiplier = 5.05 + 0.03
		elif level < 60:
			multiplier = 5.01 + 0.02
		else:
			multiplier = 4.96 + 0.01

		level += ((tier+1) / 1.00)	
		add_str = 1.5 + ((tier + 1) / 7)

	dmg = round((level * multiplier * modifier) + add_str) + 1
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


mob_tiers = ['junk', 'normal', 'rare', 'elite', 'mini-boss', 'boss']
for i in range(2):
#for i in range(9,11):
#for i in range(19,21):
#for i in range(39,41):
#for i in range(59,61):
#for i in range(111,112):
	player_hp, player_str, player_def = player_scale(i)
	print(f"Player HP:{player_hp} STR:{player_str} DEF:{player_def}")
	for j in range(6):
	#for j in range(1):
		if j < 6:
			potion_power = potion_scale(i,j)
		else:
			potion_power = potion_scale(i,5)
		
		print("Potion HP:{}".format(potion_power))
		mob_hp, mob_str_, mob_def_,xp = mob_scale(i, j)
		print("Mob Lvl:{} Tier:{}/{}".format(i, j, mob_tiers[j]))
		print("HP:{} STR:{} DEF:{} XP:{} ".format(mob_hp, mob_str_, mob_def_,xp))
		#the tiers
		for k in range(6):
			weapon_dmg = weapon_scale(i,k) + player_str
			armor_def = armor_scale(i, k) + player_def
			print("Player->Mob Dmg:{} Weapon Tier:{} Weapon Dmg:{}".format(weapon_dmg - mob_def_, k,weapon_dmg-player_str))
			print("Mob->Player Dmg:{}, Armor Tier:{} Armor Def:{}".format(mob_str_ - armor_def, k, armor_def-player_def))
		print("---------------------------------------------------------------")
	print("================================================================")
