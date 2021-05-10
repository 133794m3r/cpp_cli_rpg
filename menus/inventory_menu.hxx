/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
* Created on 4/27/21.
*
*/

#ifndef CPP_CLI_RPG_INVENTORY_MENU_HXX
#define CPP_CLI_RPG_INVENTORY_MENU_HXX
#include "menu.hxx"
#include "../classes/fighters/player.hxx"
#include "../classes/items/potion.hxx"
class InventoryMenu: public Menu{
  private:
	Player *player_;
	std::vector<menu_item_data> items_;
	std::deque<unsigned short> item_ids_;
	std::string menu_string_;
	unsigned short current_idx_;
	unsigned short max_op_;
	bool prev_;
	bool next_;
	void update_shown_items(bool forward=true){
		this->menu_string_ = "";
		std::string padding_string(53,' ');
		size_t end_idx = std::min(this->items_.size() - this->current_idx_, static_cast<size_t>(3));
		size_t i =this->current_idx_;
		unsigned short item_type;
		for(;i<end_idx;i++){
			std::string tmp = " x" + std::to_string(this->items_[i].item_quantity);
			this->menu_string_ += std::to_string(i + 1) + ')';
			//this is just a hack until I get ANSI wrap enabled.
			item_type = this->player_->player_inventory.get_item(this->item_ids_[i])->get_type();
			if (item_type == 1 || item_type == 2) {
				this->menu_string_ += '+';
			}
			this->menu_string_ += this->items_[i].item_name + tmp + padding_string.substr(0, static_cast<unsigned long>(std::floor(15 - (this->items_[i].item_name.size() + tmp.size())))) + ';';

		}
		i++;
		if(end_idx > 3) {
			this->menu_string_ += std::to_string(i++) + ")Show Next      ;";
			this->next_ = true;
		}
		else
			this->next_ = false;
		if(current_idx_ != 0){
			this->menu_string_ += std::to_string(i++) + ")Show Prev      ;";
			this->prev_ = true;
		}
		else
			this->prev_ = false;

		this->menu_string_ += std::to_string(i) + ")Exit Menu;";
		if(forward)
			this->current_idx_+= end_idx;
		else
			this->current_idx_-=end_idx;
		this->max_op_ = static_cast<unsigned short>(i);
	}

  public:
	explicit InventoryMenu(Player *player):Menu(10,3){
		this->player_ = player;
		this->items_ = this->player_->show_inventory();
		this->item_ids_ = this->player_->player_inventory.get_item_ids();
		this->prev_ = false;
		this->next_ = false;
		this->current_idx_ = 0;
		this->max_op_ = 0;
	}

	void enter(){
		clear_and_move_top();
		this->items_ = this->player_->show_inventory();
		this->item_ids_ = this->player_->player_inventory.get_item_ids();
		bool item_consumed;
		std::cout << "Player Inventory Management\n" << this->player_->get_name() << " HP:"<< this->player_->get_hp() << "/" << this->player_->get_base_hp();
		std::cout << "\nSelect item to use/equip. Total Items:" << this->items_.size() << "\nIf total items is more than the last item then use the next/prev respectively\n";
		std::cout<< "You can only use potions. Armor/Weapons have a + before their name denoting that they are equippable.\n\n\n";
		std::cout << "+------------------------------------------------------+\n|                                                      |\n|                                                      |\n+------------------------------------------------------+" << std::endl;
		this->current_idx_ = 0;
		update_shown_items();
		this->show_menu_message(this->menu_string_);
		unsigned short choice;
		while(true){
			std::cout << "\x1b[1mSelection\x1b[22m: ";
			item_consumed = true;
			choice = valid_option(1,this->max_op_);
			if(choice == this->max_op_)
				break;

			if(this->prev_ && this->next_){
				if(choice == this->max_op_ - 2){
					update_shown_items(true);
				}
				else if(choice == this->max_op_ - 1){
					update_shown_items(false);
				}
			}
			else if(this->prev_ && choice == this->max_op_ - 1){
				update_shown_items(false);
			}
			else if(this->next_ && choice == this->max_op_ - 1){
				update_shown_items(true);
			}
			else{
				choice--;
				choice -= (this->prev_ || this->next_) ? 1 : 0;
				if(this->current_idx_ > 3)
					choice += 3;
				auto *item = this->player_->player_inventory.get_item(this->item_ids_[choice]);
				auto type = item->get_type();
				if(type == 1) {
					auto *weapon = dynamic_cast<Weapon *>(item);
					this->player_->unequip_weapon();
					this->player_->equip_weapon(*weapon);

				}
				else if(type == 2){
					auto *armor = dynamic_cast<Armor *>(item);
					this->player_->unequip_armor();
					this->player_->equip_armor(*armor);
				}
				else if(type == 3){
					if(player_->get_hp() < player_->get_base_hp()){
						auto *potion = dynamic_cast<Potion *>(item);
						move_cursor(7,1);
						std::cout << "Would you like to use " << potion->get_name() << " to restore " << potion->get_power() <<" HP?";
						this->show_menu_message("1) Yes          2) No          ");
						std::cout << "\x1b[1mSelection\x1b[22m: ";
						choice = static_cast<unsigned short>(valid_option(1, 2));
						if(choice == 1){
							this->player_->add_hp(potion->get_power());
							std::cout << "Hp restored!\n";
							pause();
							move_and_clear(12);
							move_cursor(2,1);
							std::cout << player_->get_name() << " HP:" << player_->get_hp();
							std::cout << "\x1b[7H\x1b[2K";
							std::cout << "\x1b[12H\x1b[2K";
						}
						else{
							item_consumed = false;
						}
					}
					else{
						std::cout << "Your HP is full, it wouldn't do any good!\n";
						pause();
						move_and_clear_up(1);
						item_consumed = false;
					}
				}
				if(item_consumed) {
					this->player_->player_inventory.remove_item(*item);
					//need to find a better way to do this but it works for now.
					this->items_ = this->player_->show_inventory();
					this->item_ids_ = this->player_->player_inventory.get_item_ids();
					this->current_idx_ = 0;
					//all of the above needs to be redone eventually
					this->update_shown_items();
				}
			}
			//really hacky way but it works for now.
			this->show_menu_message(menu_string_);
		}
	}
};
#endif //CPP_CLI_RPG_INVENTORY_MENU_HXX
