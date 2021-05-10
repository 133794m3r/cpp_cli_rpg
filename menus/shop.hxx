/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
*
*/

#ifndef CPP_CLI_RPG_SHOP_HXX
#define CPP_CLI_RPG_SHOP_HXX

#include <algorithm>
#include "../classes/shop_keeper.hxx"
#include "inputs.hxx"
#include "menu.hxx"
class ShopMenu:public Menu {
//class ShopMenu{
  private:
	//have a copy of the shop keeper
	ShopKeeper *shop_keeper_;
	//same with player
	Player *player_;
	//some basic properties
	bool menu_ = true;
	static const std::string padding_string_;
	std::string buy_menu_string_;
	std::string sell_menu_string_;

	std::vector<menu_item_data> shop_items_;
	std::vector<menu_item_data> player_items_;
	std::deque<unsigned short> shop_item_ids_;
	std::deque<unsigned short> player_item_ids_;
	/**
	 * Updates the buy strings menu
	 */
	void update_buy_menu(){
		this->buy_menu_string_ = "";
		for(unsigned int i = 0; i < this->shop_items_.size(); i++){
			this->buy_menu_string_ += std::to_string(i + 1) + ")" + this->shop_items_[i].item_name +
									  ShopMenu::padding_string_.substr(0, 14 - this->shop_items_[i].item_name.size()) + ';';
		}
		this->buy_menu_string_ +=
				std::to_string(this->shop_items_.size() + 1) + ")Sell Items    ;" + std::to_string(this->shop_items_.size() + 2) +
				")Exit Shop   ;";
	}

	//updates the shop text for when you're buying items
	void update_shop_text(){
		move_cursor(2,1);
		clear_lines(2,2);
		std::cout << "Shop Inventory";
		move_cursor(2,30);
		std::cout << "Current Money:" << this->player_->get_gold() << "g\n";
		for(unsigned int i = 0; i < this->shop_items_.size(); i++){
			std::cout << this->shop_items_[i].item_name << " x " <<
					  this->shop_items_[i].item_quantity << ' ' << this->shop_items_[i].item_value <<
					  "g";

			if (i < this->shop_items_.size() - 1)
				std::cout << "; ";
		}
		std::cout << "\n\nPurchase Options\n";
	}

	//update the selling text screen
	void update_player_text(){
		move_cursor(2,1);
		clear_lines(2,2);
		std::cout << this->player_->get_name() << "'s Inventory";
		move_cursor(2,30);
		std::cout << "Current Money:" << this->player_->get_gold() << "g\n";
		for(unsigned int i = 0; i < this->player_items_.size(); i++){
			std::cout << this->player_items_[i].item_name << " x " <<
					  this->player_items_[i].item_quantity << ' ' << this->player_items_[i].item_value <<
					  "g";

			if (i < this->player_items_.size() - 1)
				std::cout << "; ";
		}
		std::cout << "\n\nSell Options    \n";
	}

	//updates the items to be sold menu.
	void update_sell_menu(){
		this->sell_menu_string_ = "";
		for(unsigned short i=0;i<this->player_items_.size(); i++){
			this->sell_menu_string_ += std::to_string(i + 1) + ")" + this->player_items_[i].item_name +
									   ShopMenu::padding_string_.substr(0, 14 - this->player_items_[i].item_name.size()) + ';';
		}
		this->sell_menu_string_ += std::to_string(player_items_.size() + 1) + ")Buy Items;     " +
								   std::to_string(this->player_items_.size() + 2) + ")Exit Shop   ;";
	}

  public:
	//constructor
	ShopMenu(ShopKeeper &shop_keeper, Player &player)
	:Menu(7,4)
	{
		this->shop_keeper_ = &shop_keeper;
		this->player_ = &player;
		shop_keeper.enter_shop(player);
		this->shop_items_ = shop_keeper.show_inventory();
		this->shop_item_ids_ = shop_keeper.list_inventory();
		this->update_buy_menu();
		this->player_items_ = player.show_inventory();
		this->update_sell_menu();
		this->player_item_ids_ = player.list_inventory();
	}

	explicit ShopMenu(ShopKeeper &shop_keeper)
	:Menu(7,4){
		this->shop_keeper_ = &shop_keeper;
		this->player_ = nullptr;
		this->shop_items_ = shop_keeper.show_inventory();
		this->update_buy_menu();
		this->shop_item_ids_ = shop_keeper.list_inventory();
	}

	void enter_shop(Player &p){
		this->player_ = &p;
		shop_keeper_->enter_shop(p);
		this->player_items_ = p.show_inventory();
		this->update_sell_menu();
		this->player_item_ids_ = p.list_inventory();
	}

	/**
	 * The menu portion o be shown when buying items.
	 * @return The choice(1-2) saying if we're switching menus or leaving the shop
	 */
	unsigned short purchase_menu() {
		this->update_shop_text();
		//show the menu string
		this->show_menu_message(this->buy_menu_string_);
		//infinite loop
		while(true) {
			//show prefix
			std::cout << "\x1b[1mWhat'll it be?\x1b[22m: ";
			unsigned int choice = valid_option(1, this->shop_items_.size() + 2, "What'll it be?");
			//see if it's an item they chose
			if(choice <= this->shop_items_.size()){
				unsigned char amount;
				//decrease by 1
				choice--;
				//move terminal
				move_and_clear_up(1);
				//figure out max they can buy
				unsigned int max_amt = std::min(this->player_->get_gold() / this->shop_items_[choice].item_value, this->shop_items_[choice].item_quantity);
				std::cout << "You can purchase " << max_amt << " " << this->shop_items_[choice].item_name << "(s)\nHow many? ";
				//make sure they don't try to get more than that.
				amount = valid_option(0, max_amt);
				//if it's 0 then they didn't meant to try to buy any.
				if(amount != 0){
					clear_textbox(7, 3);
					move_cursor(7, 3);
					//menu options
					std::cout << "1) Yes        2) No" << ShopMenu::padding_string_.substr(0, 32);
					move_and_clear(11);
					//telling info
					std::cout << "Are you sure you want to buy " << amount << " " << this->shop_items_[choice].item_name
							  << " for "
							  <<
							  this->shop_items_[choice].item_value * amount << "g?\n\x1b[1mSelection:\x1b[22m";
					//check for validity
					max_amt = valid_option(1, 2);
					//they did want to buy it
					if (max_amt == 1) {
						//see if they can
						bool status = this->shop_keeper_->purchase_item(this->shop_item_ids_[choice], amount);
						clear_textbox(7, 3);
						move_cursor(7, 3);
						//they can
						if (status){
							std::cout << this->player_->get_name() << " purchased " << (short) amount << " " << this->shop_items_[choice].item_name
									  << " for " << this->shop_items_[choice].item_value * amount << "g";
							this->player_items_ = this->player_->show_inventory();
							this->player_item_ids_ = this->player_->list_inventory();
							this->update_sell_menu();
							if(this->shop_items_[choice].item_quantity == amount) {
								this->shop_items_.erase(this->shop_items_.begin() + choice);
								this->shop_item_ids_.erase(this->shop_item_ids_.begin() + choice);
								this->update_buy_menu();
							}
							this->update_shop_text();
						}
						else {
							//they can't
							std::cout << "You didn't have enough gold or you tried to purchase more than it had!";
						}
						move_and_clear(11);
						pause();
					}
				}
				else {
					move_and_clear_up(1);
				}
				show_menu_message(this->buy_menu_string_);
			}
				//exit loop
			else {
				return static_cast<unsigned short>(choice - this->shop_items_.size());
			}
		}
	}

	/**
	 * This is the menu when they're selling their own things.
	 * @return
	 */
	unsigned short sell_menu() {
		//show the player side of things
		this->update_player_text();
		show_menu_message(this->sell_menu_string_);
		//all of this code is similar to above but using other properties
		while (true) {
			std::cout << "\x1b[1mSelection\x1b[22m:";
			unsigned int choice = valid_option(1, this->player_items_.size() + 2, "Selection");
			if (choice <= this->player_items_.size()) {
				choice--;
				std::cout << "You can sell " << this->player_items_[choice].item_quantity << "\nHow many?";
				unsigned int amount = valid_option(0, this->player_items_[choice].item_quantity);
				if (amount != 0) {
					clear_textbox(7, 3);
					move_cursor(7, 3);
					std::cout << "1) Yes        2) No" << ShopMenu::padding_string_.substr(0, 32);
					clear_lines(11, 3);
					std::cout << "Are you sure you want to sell " << amount << " "
							  << this->player_items_[choice].item_name << " for " <<
							  std::lround(this->player_items_[choice].item_value * amount * 0.75)
							  << "g?\n\x1b[1mSelection:\x1b[22m";

					if(valid_option(1,2) == 1){
						bool status = this->shop_keeper_->sell_item(this->player_item_ids_[choice], amount);
						this->shop_items_ = this->shop_keeper_->show_inventory();
						this->shop_item_ids_ = this->shop_keeper_->list_inventory();
						clear_textbox(7, 3);
						move_cursor(7, 3);
						if (status) {
							std::cout << this->player_->get_name() << " sold " << amount
									  << this->player_items_[choice].item_name << " for " <<
									  std::lround(this->player_items_[choice].item_value * amount * 0.75) << "g";

							if (this->player_items_[choice].item_quantity == amount) {
								this->update_sell_menu();
								this->player_items_.erase(this->player_items_.begin() + choice);
								this->player_item_ids_.erase(this->player_item_ids_.begin() + choice);
								show_menu_message(this->sell_menu_string_);
							}
							this->update_player_text();
						}
						else {
							std::cout << "You didn't have enough items to sell!";
						}
						move_and_clear(11);
						pause();
					}
				}
				else{
					move_and_clear(11);
				}
			}
			else{
				return static_cast<unsigned short>(choice - this->player_items_.size());
			}
		}
	}

	/**
	 * The main menu method.
	 */
	void shop_menu() {
		//clear the whole screen
		clear_and_move_top();
		std::cout << "Welcome to " << this->shop_keeper_->get_name() << "'s shop. What'll you have?" << std::endl;
		move_cursor(6,1);
		//draw the text-box.
		std::cout << "+------------------------------------------------------+"
				  << '\n' << "|" << ShopMenu::padding_string_ << "|" << '\n'
				  << "|" << ShopMenu::padding_string_ << "|" << '\n'
				  << "|" << ShopMenu::padding_string_ << "|"
				  << '\n' << "+------------------------------------------------------+" << std::endl;

		unsigned short cur_choice;
		//infinite loop
		while(true){
			if(this->menu_)
				cur_choice = purchase_menu();
			else
				cur_choice = sell_menu();

			if(cur_choice == 1) {
				//redraw the menu text options.
				if(this->menu_)
					this->update_shop_text();
				else
					this->update_player_text();
				//swap the current menu we're on
				this->menu_ = !this->menu_;
			}
			//they said to leave it
			else{
				break;
			}
		}
	}
	//make sure to remove player from teh shop
	~ShopMenu(){
		this->shop_keeper_->exit_shop();
	}
};
//teh padding string
const std::string ShopMenu::padding_string_ = "                                                      ";
#endif //CPP_CLI_RPG_SHOP_HXX
