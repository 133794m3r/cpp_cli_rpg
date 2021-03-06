/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
* Created on 4/25/21.
*
*/

#ifndef CPP_CLI_RPG_LOOT_TABLE_HXX
#define CPP_CLI_RPG_LOOT_TABLE_HXX
#include <utility>
#include <vector>
#include "../../random.h"
#include "inventory.hxx"

class LootTable:public Inventory {
  private:
	std::vector<double> chances;
  public:
	explicit LootTable(const std::vector<Item*>& items={}, std::vector<unsigned char> counts={},const std::vector<double>& probs = {})
	:Inventory(items,std::move(counts)){
		this->chances = probs;
	}

	std::vector <std::pair<Item*,unsigned char>> award_items(){
		//create a temporary vector
		std::vector<std::pair<Item *,unsigned char>> rewards;
		double res;
		unsigned short item_id;
		//see which items we'll give them
		for(unsigned int i=0;i<this->item_indexes.size();i++){
			res = xorshift128(0.00,1.00);
			//if it's less than the probability we award it.
			if(res <= this->chances[i]){
				//first have to get the item's id.
				item_id = this->item_indexes[i];
				//then we add a std::pair to the vector
				rewards.emplace_back(this->items[item_id],this->item_quantity[item_id]);
			}
		}
		return rewards;
	}

	void add_item(Item &item,unsigned char quantity,double probability){
		this->chances.push_back(probability);
		Inventory::add_item(item,quantity);
	}
};


#endif //CPP_CLI_RPG_LOOT_TABLE_HXX