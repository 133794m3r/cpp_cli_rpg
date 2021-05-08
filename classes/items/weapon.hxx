/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
* Created on 5/3/21.
*
*/

#ifndef CPP_CLI_RPG_WEAPON_HXX
#define CPP_CLI_RPG_WEAPON_HXX
#include "item.hxx"
class Weapon:public Item {
  private:
	unsigned short damage_;
  public:
	explicit Weapon(std::string name="Weapon",unsigned short level=1, unsigned short tier=1):Item(std::move(name), level, tier,1){
		double modifier=0;
		double add_str = 1.50;
		double dif = level;
		if(tier == 0)
			modifier = 0.95;
		else if(tier == 1){
			modifier = 1.00;
			dif = level+0.50;
		}
		else{
			modifier = 1.00 + (tier-1.00)/4.00;
			add_str = 1.00 + (tier+1)/5.0;
			dif += ((tier-1.0)/2.0);
		}
		this->damage_ = std::lround( (dif*1.45 * modifier) + add_str)+1	;
	}

	unsigned short get_damage() const{
		return this->damage_;
	}
};


#endif //CPP_CLI_RPG_WEAPON_HXX
