/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later

*
*/
#ifndef CPP_CLI_RPG_MOB_HXX
#define CPP_CLI_RPG_MOB_HXX

//have a custom structure for the rewards themselves.
struct MobRewards{
	unsigned int gold = 0;
	unsigned int xp = 0;
	std::vector<std::pair<Item *,unsigned char>> items;
};

#include "actor.hxx"
#include "../containers/loot_table.hxx"
class Mob : public Actor {
  private:
	//the xp to be awarded and gold be awarded upon death.
	unsigned int xp_;
	unsigned int gold_;
	//the tier strings a total of 6 tiers exist.
	const static std::string tier_str[6];

	/*
	 * type is based upon the following list.
	 * 0 = trash-tier, 1 = normal, 2 = rare, 3 = elite, 4 = mini-boss, 5 = boss
	 * they get a bonus to all stats based upon their tier(or reduced for trash).
	 * The stat bonus makes it as if they are of a higher level than they really are like so.
	 * Bosses use get way more bonuses than everyone else and hence are harder than the rest.
	 */

	//a short to make C++ not try to make it be a string when doing stream operations.
	unsigned short tier_;
	//loot table
	LootTable loot_table_;

	/**
	 * Sets the amount of gold that this mob should reward upon it's death.
	 */
	void set_gold(){
		unsigned int dl = this->lvl_ + 1;
		double gm = 1.90;
		double glm;
		double bvm;
		if(dl < 10){
			gm = 5.90;
			glm = 1.90;
			bvm = 6.80;
		}
		else if(dl < 40){
			gm = 6.00;
			glm = 1.85;
			bvm = 7.00;
		}
		else if(dl < 91){
			gm = 1.95;
			glm = 2.0;
			bvm = 50.00;
		}
		else if(dl < 151){
			glm = 2.20;
			bvm = 70.00;
		}
		else if(dl < 199){
			glm = 2.40;
			bvm = 100.00;
		}
		else{
			glm = 4.00;
			bvm = 120.00;
		}
		this->gold_ = static_cast<unsigned int>((this->xp_ * glm - ((dl / gm) * bvm)) * 0.50);
	}
  public:

	//initialize the Mob class. Explicit since it can be called with just 1 parameter. Also initialize properties with parent class' constructor.
	explicit Mob(std::string name="Mob",unsigned short tier=1, unsigned short level=1,
			  double bonus_hp=0.125, double bonus_str=0.25, double bonus_def=0.125)
			  :Actor(std::move(name),level,bonus_hp,
			bonus_str,bonus_def,16,6,3,1) {
		unsigned int tmp = this->lvl_ + 1;

		//don't allow them to have a tier higher than we actually have support for.
		this->tier_ = (tier>5)?5:tier;
		this->xp_ = std::lround((tmp * (tmp * 0.79) *(1+ (tier - 1.00 / 3.25) ))+ 2.00);
		//based on other formulas this should make the curve OK.
		//tier will modify the two formulas below eventually
		this->set_gold();
		if(tier > 1){
			this->bonus_hp_ += ((tier*1.25)/7);
			this->bonus_str_ += (tier/95);
			this->bonus_def_ += ((tier*1.25)/45);
		}

		if(level > 0) {
			double tier_scale;
			double modifier = 1.00;
			double dif = level;
			if(level < 5)
				tier_scale = -0.75;
			else if (level < 10)
				tier_scale = 0.20;
			else if (level < 20)
				tier_scale = 0.25;
			else if (level < 40)
				tier_scale = 0.30;
			else if (level < 60)
				tier_scale = 0.35;
			else
				tier_scale = 0.40;

			if (tier == 0) {
				modifier += (-1/27.75);
				dif -= 0.25;
			}
			else if(tier > 1){

				dif += (tier / 1.50);
				if (tier < 5) {
					modifier += (tier - tier_scale) / 28.25;
				}
				else {
					modifier += (tier - tier_scale) / 27.85;
				}
			}

			this->base_hp_ += std::lround((this->bonus_hp_ + 1) * 15 * modifier * dif + (tier - 0.5));
			this->base_str_ += std::lround((this->bonus_str_ + 1) * 3.95 * modifier * dif);
			this->base_def_ += std::lround((this->bonus_def_ + 1) * 2.50 * modifier * dif);
		}
		//then set the current stats from the base.
		this->hp_ = this->base_hp_;
		this->str_ = this->base_str_;
		this->def_ = this->base_def_;
	}


	/**
	 * Sets all stats for the object based upon the level we set.
	 * @param level The level that we're going to be basing scaling on.
	 */
	void set_level(unsigned short level) override{
		//TODO: Decide if I'm going to store the base stats from creation and just recalculate the new stats after setting level. Which would make this whole thing a lot easier.
		double dif;
		//if it's the same just do nothing.
		if(level == this->lvl_)
			dif = this->lvl_ - 1;
		else if(level > this->lvl_)
			dif = level - this->lvl_;
		else
			dif = this->lvl_ - level;

		double tier_scale;
		double modifier = 1.00;
		if(dif < 5)
			tier_scale = -0.75;
		else if (dif < 10)
			tier_scale = 0.20;
		else if (dif < 20)
			tier_scale = 0.25;
		else if (dif < 40)
			tier_scale = 0.30;
		else if (dif < 60)
			tier_scale = 0.35;
		else
			tier_scale = 0.40;

		if (this->tier_ == 0) {
			modifier += (-1/27.75);
			dif -= 0.25;
		}
		else if(this->tier_ > 1){
			if(dif > 0)
				dif += (this->tier_ / 1.50);
			else
				dif -= (this->tier_ / 1.50);
			if (this->tier_ < 5) {
				modifier += (this->tier_ - tier_scale) / 28.25;
			}
			else {
				modifier += (this->tier_ - tier_scale) / 27.85;
			}
		}

		this->base_hp_ += std::lround((this->bonus_hp_ + 1) * 15 * modifier * dif + (this->tier_ - 0.5));
		this->base_str_ += std::lround((this->bonus_str_ + 1) * 3.95 * modifier * dif);
		this->base_def_ += std::lround((this->bonus_def_ + 1) * 2.50 * modifier * dif);

		dif = level+1.00;
		this->xp_ = std::lround((dif * (dif * 0.79) *(1.00+ (this->tier_ - 1.00 / 3.25) )))+2;
		this->set_gold();
		//then set the current stats from the base.
		this->hp_ = this->base_hp_;
		this->str_ = this->base_str_;
		this->def_ = this->base_def_;
	}

	/**
	 * Gets the tier of the mob.
	 * @return The tier of the mob.
	 */
	unsigned short get_tier() const{
		return this->tier_;
	}

	/**
	 * Returns the rewards upon death.
	 *
	 * @return A custom struct of the xp, gold, and the items that they can expect.
	 */
	MobRewards rewards(){
		MobRewards rewards;
		rewards.xp = this->xp_;
		rewards.gold = this->gold_;
		if(this->loot_table_.inventory_quantity() != 0)
			rewards.items = this->loot_table_.award_items();
		return rewards;
	}

	/**
	 * Add items to the mob's loot table.
	 * @param items The items to add
	 * @param quantity The number for each
	 * @param chances The chance of each appearing
	 */
	void add_items(std::vector<Item *> items, std::vector<unsigned char> quantity, std::vector<double> chances){
		for(unsigned int i=0;i<chances.size();i++){
			this->loot_table_.add_item(*items[i], quantity[i], chances[i]);
		}
	}

	/**
	 * Add a single item
	 * @param item Item to add
	 * @param quantity The number to add
	 * @param chance The chance of rewarding it
	 */
	void add_item(Item &item, unsigned char quantity=1, double chance = 1.0){
		this->loot_table_.add_item(item, quantity, chance);
	}

	/**
	 * Converts the object into a string.
	 *
	 * @return The object stringified.
	 */
	explicit operator std::string(){
		std::stringstream ss;
		ss << "id: " << this->id << " " << this->name_ << " hp:" <<this->hp_ << "/" << this->base_hp_ <<
		   " str:" << this->str_ << "/" << this->base_str_ << " def:" << this->def_ << "/"
		   << this->base_def_ << " xp:" << this->xp_ << " g:" << this->gold_ << " tier: " << this->tier_
		   << " / " << tier_str[this->tier_];
		return ss.str();
	}
};
//the tiers but in string form.
const std::string Mob::tier_str[6] =  {"trash", "normal", "rare", "elite", "mini-boss", "boss"};

#endif //CPP_CLI_RPG_MOB_HXX
