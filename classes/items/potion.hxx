/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
* Created on 4/28/21.
*
*/

#ifndef CPP_CLI_RPG_POTION_HXX
#define CPP_CLI_RPG_POTION_HXX

#include <utility>
#include "../../includes.hxx"
#include "item.hxx"
class Potion:public Item {
  private:
	unsigned short power_;
  public:
	//the name should always convey that it's a potion
	explicit Potion(std::string name="Junk", unsigned short level=1, unsigned short tier=1):Item(std::move(name)+" Pot",3,tier,level){
		this->power_ = std::lround((level*16.00)*((tier+1.00)/4.00));
	}
	unsigned short get_power() const{
		return this->power_;
	}
	explicit operator std::string() const override{
		return this->name_;
	}
};


#endif //CPP_CLI_RPG_POTION_HXX
