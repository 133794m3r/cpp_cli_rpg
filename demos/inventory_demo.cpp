/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
* Created on 4/26/21.
*
*/
#include "../menus/inventory_menu.hxx"
int main(){
	Player player("Jim");
	Armor armor("Shirt");
	Weapon weapon("Sword");
	Potion potion;
	player.add_item(armor);
	player.add_item(weapon);
	player.add_item(potion);
	//player.damage(7);
	InventoryMenu inv_menu(&player);
	inv_menu.enter();
	return 0;
}
