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
		this->damage_ = std::lround((level*1.5*(1+((tier-1.00)/4.00))));
	}


	unsigned short get_damage() const{
		return this->damage_;
	}
};


#endif //CPP_CLI_RPG_WEAPON_HXX
