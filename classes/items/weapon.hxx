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
		double modifier;
		double add_str = 1.50;
		double dif = level;
		double multiplier;
		tier = (tier > 5)?5:tier;
		if(tier <2) {
			switch (tier) {
				case 0:
					modifier = 0.85;
					break;
				case 1:
					modifier = 1.00;
					break;
			}
			if(level < 10)
				multiplier = 5.10;
			else if(level<20)
				multiplier = 5.08;
			else if(level < 40)
				multiplier = 5.05;
			else if(level < 60)
				multiplier = 5.01;
			else
				multiplier = 4.96;
		}
		else{
			switch(tier-2){
				case 0:
					multiplier = 2.00/16.00;
					break;
				case 1:
					multiplier = 5.00/16.00;
					break;
				case 2:
					multiplier = 0.50;
					break;
				case 3:
					multiplier = 11.00/16.00;
					break;
			}
			dif += tier+1;
			add_str += ((tier+1)/7.00);
			if(level < 10)
				multiplier = 5.15;
			else if(level<20)
				multiplier = 5.12;
			else if(level < 40)
				multiplier = 5.08;
			else if(level < 60)
				multiplier = 5.03;
			else
				multiplier = 4.97;
		}
		this->damage_ = std::lround( (level*multiplier*modifier) + add_str)+1;
	}

	unsigned short get_damage() const{
		return this->damage_;
	}
};


#endif //CPP_CLI_RPG_WEAPON_HXX
