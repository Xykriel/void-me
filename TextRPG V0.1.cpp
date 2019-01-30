#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class Hero {
public:

	int p_base_health;
	int p_base_attack;
	int p_base_defense;
	int p_base_speed;
	int p_total_exp = 0;
	int p_level = 1;
	int p_max_health;
	int p_current_health;
	int p_attack;
	int p_defense;
	int p_speed;
	int p_heal;

	void setClassStats() {

		p_max_health = p_level * p_base_health;
		p_current_health = p_max_health;
		p_attack = p_level * p_base_attack;
		p_defense = p_level * p_base_defense;
		p_speed = p_level * p_base_speed;
	}
	void healPlayer() {

		p_heal = (p_max_health / 3) * 2;
		p_current_health = p_current_health + p_heal;

		if (p_current_health > p_max_health) {

			p_current_health = p_max_health;
		}
		else {}

		std::cout << "You were healed for " << p_heal << " hit points!\nYou now have " << p_current_health << "hit points!" << std::endl;
	}


};
class Enemy {
public:
	std::string m_name;
	int m_base_health = 1;
	int m_base_attack = 1;
	int m_base_defense = 1;
	int m_base_speed = 1;
	int m_base_health_potion_drop;
	int m_base_gold_drop;
	int m_gold_drop;
	int m_max_health;
	int m_current_health;
	int m_attack;
	int m_defense;
	int m_speed;
	int m_base_exp;
	int m_exp;
	
	void setMonsterStats(Hero player) {
		m_max_health = m_base_health * player.p_level;
		m_current_health = m_max_health;
		m_attack = m_base_attack * player.p_level;
		m_defense = m_base_defense * player.p_level;
		m_speed = m_base_speed * player.p_level;
		m_gold_drop = m_base_gold_drop * player.p_level;
		m_exp = m_base_exp * player.p_level;
	}
	
};


void menu(std::string& playername);
void playerClassSelect(Hero& player);
void getMonsterID(int& min_mon_id, int dungeon_floor, int& monster_id, int monster_pool_range[], Hero player, Enemy& monster);
void speedcheck(bool &player_is_fast, Hero player, Enemy monster);
int battle(bool &player_is_fast, Hero &player, Enemy &monster, bool player_attacks);
void exp_gain(Enemy monster, Hero &player);

int main() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	Hero player{
	};
	Enemy monster{
	};

	std::string playername;
	menu(playername);

	std::cout << playername << ", please input the class you would like to play.\n" << std::endl;
	std::cout << "Knight: The defensive class. They are slow to attack but make up for it with their sturdy shield." << std::endl;
	std::cout << "Rogue: The offensive class. They are the strongest and fastest class, but have the lowest vitality." << std::endl;
	std::cout << "Mage: The all rounding class. They do not have any specialties, and therefore have no strengths or weaknesses.\n" << std::endl;


	playerClassSelect(player);
	
	int dungeon_floor = 2;
	int min_mon_id = 1;
	int monster_id;
	int monster_pool_range[5];
	monster_pool_range[0] = 3;
	monster_pool_range[1] = 3;
	monster_pool_range[2] = 6;


	int health_potions = 1;
	int heal = player.p_max_health / 2; 
	int gold = 0;

	

	do { //gameloop
	
		getMonsterID(min_mon_id, dungeon_floor, monster_id, monster_pool_range, player, monster);
		std::cout << "You are attacked by a " << monster.m_name << "!\n" << std::endl;

		do {


			std::cout << monster.m_name << " has " << monster.m_current_health << " hit points!\n" << std::endl;
			std::cout << "Would you like to attack, or use an item?\n" << std::endl;

			std::string player_battle_choice;


			bool battle_choice;
			bool player_attacks;
			bool potion_choice;

			do {


				std::cin >> player_battle_choice;
				std::transform(player_battle_choice.begin(), player_battle_choice.end(), player_battle_choice.begin(), ::tolower);

				if (player_battle_choice == "attack") {

					player_attacks = true;
					battle_choice = true;
				}
				else if (player_battle_choice == "items" || player_battle_choice == "item") {
					player_attacks = false;
					battle_choice = true;
				}
				else {
					battle_choice = false;
					std::cout << "Invalid Input! Please try again.\n" << std::endl;
				}
			} while (battle_choice == false);



			if (player_attacks == false) {


				std::cout << "You look in your bag, and see that you have " << health_potions << " health potions and " << gold << " gold coins.\n" << std::endl;

				if (health_potions == 0)
				{
					std::cout << "You have no potions, so you decide to attack instead." << std::endl;
					player_attacks = true;
				}

				else if (health_potions > 0) {
					std::cout << "Would you like to use a potion?\n" << std::endl;

					std::string item_choice;
					std::cin >> item_choice;
					std::transform(item_choice.begin(), item_choice.end(), item_choice.begin(), ::tolower);

					do {

						if (item_choice == "yes" || item_choice == "y") {
							player.healPlayer();
							potion_choice = true;
							player_attacks = false;
						}
						else if (item_choice == "no" || item_choice == "n") {
							std::cout << "You decide to attack instead.\n" << std::endl;
							potion_choice = true;
							player_attacks = true;
						}
						else {
							potion_choice = false;
							std::cout << "Invalid Input! Please try again.\n" << std::endl;
						}
					} while (potion_choice == false);



				}

			}

			bool player_is_fast;

			if (player_attacks == false) { // battle start if potion used

				battle(player_is_fast, player, monster, player_attacks);

			}
			else if (player_attacks == true) {

				//battle logic here

				
				speedcheck(player_is_fast, player, monster);
				battle(player_is_fast, player, monster, player_attacks);
			}
		}while (monster.m_current_health > 0 && player.p_current_health > 0);

		if (monster.m_current_health < 1) {

			health_potions = health_potions + monster.m_base_health_potion_drop;
			gold = gold + monster.m_gold_drop;
			std::cout << "You found " << monster.m_base_health_potion_drop << " health potion and " << monster.m_gold_drop << " gold coins!" << std::endl;
			std::cout << "You now have " << health_potions << " health potions and " << gold << " gold coins." << std::endl;
			exp_gain(monster, player);
			
		}

	} while (player.p_current_health > 1);

		
	std::cout << "\nGAME OVER\n" << std::endl;
	std::cout << "Press enter to exit" << std::endl;		
	std::cin.get();
	std::cin.get();
}

void speedcheck(bool &player_is_fast, Hero player, Enemy monster){

	if (player.p_speed >= monster.m_speed){
		player_is_fast = true;
	}
	else if (player.p_speed < monster.m_speed) {
		player_is_fast = false;
	}
}

void exp_gain(Enemy monster, Hero &player) {

	player.p_total_exp = player.p_total_exp + monster.m_exp;

	int exp_needed = player.p_level * 5;

	if (player.p_total_exp >= exp_needed) {

		std::cout << "You have leveled up!" << std::endl;
		++player.p_level;
		std::cout << "You are now level " << player.p_level << "!" << std::endl;
		std::cout << "You have grown in power, and have also been healed." << std::endl;
		player.p_total_exp = player.p_total_exp - exp_needed;
		std::cout << "You currently have " << player.p_total_exp << " experience points." << std::endl;
		exp_needed = (player.p_level * 5) - player.p_total_exp;
		std::cout << "You need " << exp_needed << " experience points to level up." << std::endl;
		player.setClassStats();


	}
	else if (player.p_total_exp < exp_needed) {


		std::cout << "You currently have " << player.p_total_exp << " experience points." << std::endl;
		exp_needed = (player.p_level * 5) - player.p_total_exp;
		std::cout << "You need " << exp_needed << " experience points to level up." << std::endl;

	}
}
int battle(bool &player_is_fast, Hero &player, Enemy &monster, bool player_attacks) {

	int damage;
	bool turn_one_ended = false;

	if (player_attacks == true){
		if (player_is_fast == true) { // player hits first

			damage = player.p_attack - monster.m_defense; // player attacks
			monster.m_current_health = monster.m_current_health - damage;

			if (monster.m_current_health < 0) {

				monster.m_current_health = 0;
			}

			std::cout << "You attack the " << monster.m_name << " for " << damage << " hit points." << std::endl;
			std::cout << "It has " << monster.m_current_health << " remaining.\n" << std::endl;

			turn_one_ended = true;

		}
			else if (player_is_fast == false) {

			damage = monster.m_attack - player.p_defense; // monster attack calc
			player.p_current_health = player.p_current_health - damage;

			if (player.p_current_health < 0) {

				player.p_current_health = 0;
			}

			std::cout << "You are attacked by the " << monster.m_name << " for " << damage << " hit points." << std::endl;
			std::cout << "You have " << player.p_current_health << " remaining!\n" << std::endl;
			turn_one_ended = true;

			}


		if (player.p_current_health < 1){
			
		std::cout << "You were killed by a " << monster.m_name << "!" << std::endl;
		return 0;
		}
			else if (monster.m_current_health < 1) {
				std::cout << "You killed a " << monster.m_name << "!" << std::endl;
				return 0;
			}

		else{}

		if (turn_one_ended == true && player_is_fast == true) {

			damage = monster.m_attack - player.p_defense; // monster attack calc
			player.p_current_health = player.p_current_health - damage;

			if (player.p_current_health < 0) {

				player.p_current_health = 0;
			}

			std::cout << "You are attacked by the " << monster.m_name << " for " << damage << " hit points." << std::endl;
			std::cout << "You have " << player.p_current_health << " remaining!\n" << std::endl;
		}
			else if (turn_one_ended == true && player_is_fast == false)
			{
				damage = player.p_attack - monster.m_defense;
				monster.m_current_health = monster.m_current_health - damage;

				if (monster.m_current_health < 0) {

					monster.m_current_health = 0;
				}

				std::cout << "You attack the " << monster.m_name << " for " << damage << " hit points." << std::endl;
				std::cout << "it has " << monster.m_current_health << " remaining.\n" << std::endl;
			}
	}
		else if (player_attacks == false) {

			damage = monster.m_attack - player.p_defense; // monster attack calc
			player.p_current_health = player.p_current_health - damage;
			std::cout << "You are attacked by the " << monster.m_name << " for " << damage << " hit points." << std::endl;
			std::cout << "You have " << player.p_current_health << " remaining.\n" << std::endl;

		}

		if (player.p_current_health < 1) {

			std::cout << "You were killed by a " << monster.m_name << "!" << std::endl;
			return 0;
		}
			else if (monster.m_current_health < 1) {
				std::cout << "You killed a " << monster.m_name << "!" << std::endl;
				return 0;
			}

	return 0;

}
void menu(std::string& playername) {

	std::cout << "Welcome!" << std::endl;
	std::cout << "Please enter your name.\n" << std::endl;

	std::cin >> playername;
	std::cout << "Welcome, " << playername << "!" << std::endl;

	
	
}

void playerClassSelect(Hero &player) {

	
	bool class_chosen;

	do {
		std::string player_class_input;
		std::cin >> player_class_input; // Gets player class choice
		std::transform(player_class_input.begin(), player_class_input.end(), player_class_input.begin(), ::tolower); // changes class choice to lowercase
			if (player_class_input == "knight") {

				player.p_base_health = 20;
				player.p_base_attack = 10;
				player.p_base_defense = 15;
				player.p_base_speed = 5;
				player.setClassStats();
				std::cout << "You are now a Knight!" << std::endl;
				class_chosen = true;
			}
			else if (player_class_input == "rogue") {
			
				player.p_base_health = 10;
				player.p_base_attack = 13;
				player.p_base_defense = 4;
				player.p_base_speed = 13;
				player.setClassStats();
				std::cout << "You are now a Rogue!" << std::endl;
				class_chosen = true;
			}
			else if (player_class_input == "mage") {
				player.p_base_health = 15;
				player.p_base_attack = 10;
				player.p_base_defense = 10;
				player.p_base_speed = 10;
				player.setClassStats();
				std::cout << "You are now a Mage!" << std::endl;
				class_chosen = true;
			}
			else {
				class_chosen = false;
				std::cout << "Invalid Input! Please try again.\n" << std::endl;
			}
	} while (class_chosen == false); {}

	std::cout << "Now entering the dungeon..." << std::endl;



}

void getMonsterID(int& min_mon_id, int dungeon_floor, int& monster_id, int monster_pool_range[], Hero player, Enemy& monster) {
	
	int max_mon_id;

	do {
		

		max_mon_id = monster_pool_range[(dungeon_floor - 1)];
		min_mon_id = (max_mon_id - monster_pool_range[(dungeon_floor - 1)] + 1);
		max_mon_id - min_mon_id <= RAND_MAX;

		static const double fraction = 1.0 / (RAND_MAX + 1.0);
		monster_id = min_mon_id + static_cast<int>((max_mon_id - min_mon_id + 1) * (std::rand() * fraction));

		
	}
		while (monster_id <= 0);

	switch (monster_id)
	{
	case 1:	
		monster.m_name = "Cave Bat";
		monster.m_base_health = 10;
		monster.m_base_attack = 7;
		monster.m_base_defense = 6;
		monster.m_base_speed = 9;
		monster.m_base_health_potion_drop = 0;
		monster.m_base_gold_drop = 5;
		monster.m_base_exp = 2;
		monster.setMonsterStats(player);
		break;
	case 2:
		monster.m_name = "Cave Rat Pack";
		monster.m_base_health = 15;
		monster.m_base_attack = 8;
		monster.m_base_defense = 8;
		monster.m_base_speed = 7;
		monster.m_base_health_potion_drop = 1;
		monster.m_base_gold_drop = 2;
		monster.m_base_exp = 4;
		monster.setMonsterStats(player);
		break;
	case 3:
		monster.m_name = "Cave Worm";
		monster.m_base_health = 10;
		monster.m_base_attack = 8;
		monster.m_base_defense = 6;
		monster.m_base_speed = 10;
		monster.m_base_health_potion_drop = 1;
		monster.m_base_gold_drop = 4;
		monster.m_base_exp = 5;
		monster.setMonsterStats(player);
		break;
	}
}