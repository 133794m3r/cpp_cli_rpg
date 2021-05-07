/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
* Created on 4/6/21.
*
*/

#include "../menus/battle.hxx"
int main(){
	Weapon stick("Stick",1,0);
	Armor shirt("Shirt",1,0);
	Weapon sword("sword",1,1);
	Armor cloth("shield",1,1);
	Mob mob("Fish");
	Mob Boss("Giant",6,2);
	Player player("Jimmy");
	battle(player,mob);
	return 0;
}