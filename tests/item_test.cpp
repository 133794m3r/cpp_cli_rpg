/*
* CLI RPG
* Macarthur Inbody
* Created on 5/4/21.
*
*/
#include "../classes/items/potion.hxx"
#include "../classes/items/weapon.hxx"
#include "../classes/items/armor.hxx"
#include "../terminal.hxx"
int main() {
	std::cout << "\x1b[" << BRIGHT_WHITE_TXT << 'm' << "\x1b[" << BLACK_BG << 'm';
	Item junk("Junk", 1, 0);
	Potion basic_pot("Basic", 1, 1);
	Weapon base_weapon();
	Armor base_armor();
	Weapon epic_weapon("Epic Weapon", 1, 6);
	Armor epic_armor("Epic Armor", 1, 6);
	unsigned short total = 0;
	unsigned short failed = 0;

	total++;
	std::cout << "Item id test ";
	if (junk.get_id() == 0)
		std::cout << "passed!";
	else {
		std::cout << "failed: Expected 0 but we got " << junk.get_id();
		failed++;
	}
	std::cout << '\n';
	std::cout << "Item Value Tests\n";
	std::cout << "Junk Test: ";
	total++;
	if(junk.get_value() == 0x1f)
		std::cout << "passed!\n";
	else {
		std::cout << "failed expected " << 0x1f << "but we got " << junk.get_value() << '\n';
		failed++;
	}

	total++;
	std::cout << "Normal test: ";
	if(basic_pot.get_value() == 0x2b)
		std::cout << "passed!\n";
	else {
		failed++;
		std::cout << "failed! Expected: " << 0x2b << " but we got " << basic_pot.get_value() << "\n";
	}

	total++;
	std::cout << "Epic test: ";
	if(epic_weapon.get_value() == 0x20)
		std::cout << "passed!\n";
	else {
		std::cout << "failed! Expected: " << 0x20 << " but we got " << epic_weapon.get_value() << "\n";
		failed++;
	}

	total++;
	std::cout << "Item Unique property tests\n";
	std::cout << "Potion(lvl1) power: ";
	if(basic_pot.get_power() == 4)
		std::cout << "passed!";
	else {
		std::cout << "failed! We expected 4 but we got " << basic_pot.get_power() << "\n";
		failed++;
	}

	total++;
	std::cout << "Epic Weapon Damage: ";
	if(epic_weapon.get_damage() == 3)
		std::cout << "passed!\n";
	else {
		std::cout << "failed! Expected: 3 but we got " << epic_weapon.get_damage() << "\n";
		failed++;
	}

	total++;
	std::cout << "Epic Armor Defense: ";
	if(epic_armor.get_defense() == 22)
		std::cout << "passed!\n";
	else {
		std::cout << "failed! Expected: 9 but we got " << epic_armor.get_defense() << "\n";
		failed++;
	}

	std::cout << "Passed: \x1b[1;" << BRIGHT_GREEN_TXT << 'm'<< total - failed << "\x1b[22;97m/" << total << "  Failed: \x1b[1;" << BRIGHT_RED_TXT << 'm' <<failed << "\x1b[0m\n";
	if(failed != 0)
		return 1;
	return 0;
}

