#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>

class Player_Hero{
    public:
        std::string name;
        std::string hero_class;
        int level;
        int current_health;
        int base_health;
        int base_attack;
        int base_defense;
        int base_speed;
        int exp;
        int hero_level;

};

class Monster{
public:
    std::string name;
    int monster_id;
    int level;
    int current_health;
    int base_health;
    int base_attack;
    int base_defense;
    int base_speed;
};

int intro_get_class_id(int class_id);
int intro_get_class_select(int &class_id);
int set_player_class(Player_Hero &player, int class_id);
int enemy_select(int dungeon_floor,int &enemy_id);
int set_enemy_stats(int enemy_id, Monster &placeholder);
int battle_menu(Player_Hero &player, Monster &placeholder);
int battle_menu_player_decide(int player_battle_choice);

int main()
{

    //std::string data;
    //std::cin >> data;
    //std::transform(data.begin(), data.end(), data.begin(), ::tolower); // Lowercase script for commands and string recognition
    //std::cout << data << std::endl;

    //srand((int)time(0));
	//int i = 0;
	//while(i++ < 10) {
	//	int r = (rand() % 100) + 1; // random number script for monster generation
	//	std::cout << r << " ";
	//}

    Player_Hero player;
    player.hero_class   = "hero";
    player.base_health  = 100;
    player.current_health = 100;
    player.base_attack  = 1;
    player.base_defense = 1;
    player.base_speed   = 1;
    player.exp          = 0;
    player.hero_level   = 1;

    Monster placeholder;
    placeholder.name  = "placeholder";
    placeholder.monster_id   = 0;
    placeholder.level        = 1;
    placeholder.base_health  = 1;
    placeholder.current_health = 1;
    placeholder.base_attack  = 1;
    placeholder.base_defense = 1;
    placeholder.base_speed   = 1;

    std::string player_name;
    std::cout << "Welcome! What is your name?" << std::endl;
    std::cin >> player_name;
    std::cout << "Welcome, " << player_name << "!" << std::endl;
    std::cout << player_name << ", please input the class you would like to play." << std::endl;
    std::cout << "Knight: The defensive class. They are slow to attack but make up for it with their sturdy sword." << std::endl;
    std::cout << "Rogue: The offensive class. They are the strongest and fastest class, but have the lowest vitality." << std::endl;
    std::cout << "Mage: The all rounding class. They do not have any specialties, and therefore have no strengths or weaknesses." << std::endl;
    int class_id = 0;
    intro_get_class_select(class_id);
    set_player_class(player, class_id);
    std::cout << "Good luck, " << player_name << " the " << player.hero_class << "!" << std::endl;
    std::cout << "Be warned, at the end of each dungeon a dangerous creature lies in wait." << std::endl;

    std::cout << "\nNow entering the dungeon..." << std::endl;
    int dungeon_floor = 1;
    int enemy_id;
    enemy_select(dungeon_floor, enemy_id);
    std::cout << enemy_id << std::endl;
    set_enemy_stats(enemy_id, placeholder);
    battle_menu(player, placeholder);
    int player_battle_choice;
    battle_menu_player_decide(player_battle_choice);

    return 0;
}

int intro_get_class_select(int &class_id){
    std::string player_class_input;
    std::cin >> player_class_input;
    std::transform(player_class_input.begin(), player_class_input.end(), player_class_input.begin(), ::tolower);
        if (player_class_input == "knight"){
        class_id = 1;
        return class_id;}
                else if (player_class_input == "rogue"){
                class_id = 2;
                return class_id;}
                    else if (player_class_input == "mage"){
                    class_id = 3;
                    return class_id;}
                        else{
                        std::cout << "Invalid Input! Please try again." << std::endl;
                        intro_get_class_select(class_id);}
}
int set_player_class(Player_Hero &player, int class_id){ // IF a function gets called with multiple parameters, it must return at least one parameter...??
    if (class_id == 1){ // Knight Stats --- input class id, output knight stats
        player.hero_class = "Knight";
        player.base_health = 100;
        player.current_health = player.base_health;
        player.base_attack = 8;
        player.base_defense = 18;
        player.base_speed = 4;
        player.exp = 0;
        player.hero_level = 1;
        }
        else if (class_id == 2){ // Rogue Stats

        player.hero_class = "Rogue";
        player.base_health = 50;
        player.current_health = player.base_health;
        player.base_attack = 13;
        player.base_defense = 4;
        player.base_speed = 13;
        player.exp = 0;
        player.hero_level = 1;
        }
            else if (class_id == 3){ // Mage Stats

            player.hero_class = "Mage";
            player.base_health = 100;
            player.current_health = player.base_health;
            player.base_attack = 11;
            player.base_defense = 8;
            player.base_speed = 11;
            player.exp = 0;
            player.hero_level = 1;
            }
    return 0;
}
int enemy_select(int dungeon_floor,int &enemy_id){
    if (dungeon_floor == 1){
        srand((int)time(0));
        int i = 0; // last id used in the chain ( in terms of this program)
        while(i++ < 1) { // amount of numbers generated
        enemy_id = (rand() % 3) + 1; /* max number used */
        return enemy_id;
    }
	}
    else if (dungeon_floor == 2){
        srand((int)time(0));
        int i = 3; // last id used in the chain ( in terms of this program)
        while(i++ < 1) { // amount of numbers generated
        enemy_id = (rand() % 6) + 1; /* max number used */}
        return enemy_id;
	}
	return 0;
}
int set_enemy_stats(int enemy_id, Monster &placeholder){

    if (enemy_id == 1){
    placeholder.name  = "Cave Spider";
    placeholder.monster_id   = 1;
    placeholder.level        = 1;
    placeholder.base_health  = 15;
    placeholder.current_health = placeholder.base_health;
    placeholder.base_attack  = 5;
    placeholder.base_defense = 2;
    placeholder.base_speed   = 4;
    }
    else if (enemy_id == 2){
    placeholder.name  = "Cave Bat";
    placeholder.monster_id   = 2;
    placeholder.level        = 1;
    placeholder.base_health  = 10;
    placeholder.current_health = placeholder.base_health;
    placeholder.base_attack  = 3;
    placeholder.base_defense = 2;
    placeholder.base_speed   = 6;
    }
    else if (enemy_id == 3){
    placeholder.name  = "Cave Worm";
    placeholder.monster_id   = 3;
    placeholder.level        = 1;
    placeholder.base_health  = 20;
    placeholder.current_health = placeholder.base_health;
    placeholder.base_attack  = 2;
    placeholder.base_defense = 2;
    placeholder.base_speed   = 2;
    }
   return 0;
}
int battle_menu(Player_Hero &player, Monster &placeholder){

std::cout << "You are attacked by a " << placeholder.name << "!" << std::endl;
std::cout << "It has " << placeholder.current_health << " HP remaining." << std::endl;

std::cout << "\nYou have " << player.current_health << "HP remaining.\nWhat would you like to do?\nAttack\tUse Items" << std::endl;
return 0;
}
int battle_menu_player_decide(int player_battle_choice){
    std::string player_battle_input;
    std::cin >> player_battle_input;
    std::transform(player_battle_input.begin(), player_battle_input.end(), player_battle_input.begin(), ::tolower);
        if (player_battle_input == "attack"){
            player_battle_choice = 1;
            return player_battle_choice;}
        else if (player_battle_input == "use item" || player_battle_input == "item" || player_battle_input == "items"){
            player_battle_choice = 2;
            return player_battle_choice;}
            else{
                std::cout << "Invalid input! Please try again." << std::endl;
                battle_menu_player_decide(player_battle_choice);
                }
}

//how will the battle functions work?
// the battle function will be the one that calls the functions? (no)?
// before a battle starts, the game first needs to tell what enemy is attacking
// to tell what is attacking, the game needs the floor number.
// the floor number will have to be used to call the random number
// HOWEVER, these functionS will have to be made for several floors. this functionality must be kept in mind.

// in short, main will call the random number generator which will determine the enemy pool.
// the generator will then call another function to set the stats of the enemy generated, which will be specific to the pool.
// the enemy stats will have been writen to the placeholder, which will also state enemy name and call the menu function.
// the menu function will call either the battle or the item function.
// item will call the item phase function, which will then call the damage_phase_two function
// damage phase will pull both class data, and calculate speed, damage dealt by the fastest entity on the first turn, then move to death_check_one
// death check one will check if either entity has died in the first turn, and deal accordingly. else, move on to phase two
// phase two will let the slowest party deal their damage. after this, it will then call death check two.
// once a monster has died the reward function will be called. IF the player levels up, they will automatically be healed.
// the reward function gives exp, determines level up, and warns the player of the next enemy. the monster_defeated counter is &referenced here
// If the monster killed counter reaches <= 10, the player is asked if they want to challenge the boss.
// this calls the boss function, which also references dungeon floor, and holds all boss stats.
// boss() will then call the battle function.













