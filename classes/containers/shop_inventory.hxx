/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
* Created on 4/19/21.
*
*/

#ifndef CPP_CLI_RPG_SHOP_INVENTORY_HXX
#define CPP_CLI_RPG_SHOP_INVENTORY_HXX
#include "inventory.hxx"
#include "../../includes.hxx"
class ShopInventory: public Inventory {
  public:
	explicit ShopInventory(const std::vector<Item*> &items = {},
						   const std::vector<unsigned char> &quantity = {}):Inventory(items,quantity){

	}

	/**
	 * The cost to buy amount of the items.
	 * @param item_id The item we're going to be using.
	 * @param amount The amount to attempt to purchase
	 * @return The amount of gold it'd cost to buy it.
	 */
	unsigned int purchase_cost(unsigned short item_id, unsigned int amount=1) const{
		return this->items.at(item_id)->get_value() * amount;
	}


};


#endif //CPP_CLI_RPG_SHOP_INVENTORY_HXX
