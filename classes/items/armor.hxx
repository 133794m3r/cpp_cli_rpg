/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
* Created on 5/3/21.
*
*/

#ifndef CPP_CLI_RPG_ARMOR_HXX
#define CPP_CLI_RPG_ARMOR_HXX
#include <utility>

#include "item.hxx"
class Armor:public Item {
  private:
	unsigned short defense_;
  public:
	explicit Armor(std::string name="Armor", unsigned short level=1, unsigned short tier=1):Item(std::move(name),level,tier,2){
		this->defense_ = std::lround((level*1.95*(1+((tier-1.00)/4.00))));
	}
	unsigned short get_defense() const{
		return this->defense_;
	}
};


#endif //CPP_CLI_RPG_ARMOR_HXX
