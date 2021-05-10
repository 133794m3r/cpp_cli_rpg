#include <utility>

/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
* Created on 5/3/21.
*
*/

#ifndef CPP_CLI_RPG_ITEM_HXX
#define CPP_CLI_RPG_ITEM_HXX


class Item {
  private:
	const unsigned short id_;
	static unsigned short next_id_;
  protected:
	std::string name_;
	unsigned short value_;
	//short b/c cout cats unsigned char to a char.
	unsigned short tier_;
	//same here. it's literally only going up to the number 8 but instead we waste an extra byte of ram.
	unsigned short type_;
	unsigned short level_;
  public:
	explicit Item(std::string name = "Item", unsigned short level=1, unsigned short tier=1,uint_fast8_t type=0):id_(next_id_++){
		this->name_ = std::move(name);
		this->tier_ = tier;
		this->value_ = (level*6)+25+std::lround(level*((tier-1.00)/4.00));
		this->type_ = type;
		this->level_ = level;
	}

	unsigned short get_id() const{
		return this->id_;
	}

	unsigned short get_value() const{
		return this->value_;
	}

	unsigned short get_type() const{
		return this->type_;
	}

	std::string get_name() const{
		return this->name_;
	}

	unsigned short get_tier() const{
		return this->tier_;
	};

	virtual explicit operator std::string() const{
		return this->name_;
	}

};

unsigned short Item::next_id_ = 0;


#endif //CPP_CLI_RPG_ITEM_HXX
