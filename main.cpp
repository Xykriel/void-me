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
        int health_turn;
        int base_health;
        double base_attack;
        double base_defense;
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
    int health_turn;
    int base_health;
    double base_attack;
    double base_defense;
    int base_speed;
};

int introGetClassSelect(int &class_id);
int setPlayerClass(Player_Hero &player, int class_id);
int getMonsterID(int min_mon_id, int dungeon_floor, int &monster_id);
int enemySelect(int monster_id, Monster &placeholder);
int battleStart(Monster &placeholder, Player_Hero &player);
int battlePlayerSelect(int &attack_choice, int &item_choice);
int check_items(Player_Hero &player, int &player_chose_attack, int gold, int &health_potions, int attack_active);
int battleAttackPhaseOne(int player_chose_attack, Player_Hero &player, Monster &placeholder,int &turn_order, int &damage);
int battleAttackPhaseTwo();

int main()
{
    std::srand(static_cast<unsigned int>(std::time(0)));

    Player_Hero player;
    player.hero_class   = "hero";
    player.base_health  = 100;
    player.current_health = 100;
    player.health_turn = 100;
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
    placeholder.health_turn = 1;
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
    introGetClassSelect(class_id);
    setPlayerClass(player, class_id);
    std::cout << "Good luck, " << player_name << " the " << player.hero_class << "!" << std::endl;
    std::cout << "Be warned, at the end of each dungeon a dangerous creature lies in wait." << std::endl;
    srand((int)time(0));
    std::cout << "\nNow entering the dungeon..." << std::endl;

    int dungeon_floor = 1;
    int min_mon_id;
    int monster_id;

    getMonsterID(min_mon_id, dungeon_floor, monster_id);
    enemySelect(monster_id, placeholder);
    battleStart(placeholder, player);
    int attack_choice = 0;
    int item_choice = 0;
    battlePlayerSelect(attack_choice, item_choice);
    int health_potions = 0;
    int gold = 0;
    int player_chose_attack = 0;
    int attack_active = 0;
    int turn_order;
    int damage;
        if (attack_choice == 1){
        player_chose_attack = 1;
        battleAttackPhaseOne(player_chose_attack, player, placeholder, turn_order, damage);

    }
    else if (item_choice == 1){
        check_items(player, player_chose_attack, gold, health_potions,attack_active);
        battleAttackPhaseTwo();
    }

    return 0;

}

int introGetClassSelect(int &class_id){

    do{
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
            class_id = 4;
             std::cout << "Invalid Input! Please try again." << std::endl;
            }
        }
        while (class_id == 4);{}

return class_id;
}

int setPlayerClass(Player_Hero &player, int class_id){ // IF a function gets called with multiple parameters, it must return at least one parameter...??
    if (class_id == 1){ // Knight Stats --- input class id, output knight stats
        player.hero_class = "Knight";
        player.base_health = 100;
        player.current_health = player.base_health;
        player.health_turn = player.base_health;
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
        player.health_turn = player.base_health;
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
            player.health_turn = player.base_health;
            player.base_attack = 11;
            player.base_defense = 8;
            player.base_speed = 11;
            player.exp = 0;
            player.hero_level = 1;
            }
    return 0;
}

int getMonsterID(int min_mon_id, int dungeon_floor, int &monster_id){
    do {
        int max_mon_id;
        int temp_min_mon_id;
        int temp_max_mon_id;
        int monster_pool_range = 3;

        max_mon_id - min_mon_id <= RAND_MAX;
        temp_max_mon_id = dungeon_floor * monster_pool_range;
        max_mon_id = temp_max_mon_id;
        temp_min_mon_id = max_mon_id - monster_pool_range + 1;
        min_mon_id = temp_min_mon_id;

        static const double fraction = 1.0 / (RAND_MAX + 1.0);
        monster_id = min_mon_id + static_cast<int>((max_mon_id - min_mon_id + 1) * (std::rand() * fraction));}

        while (monster_id < 0);
        return 0;

}

int enemySelect(int monster_id, Monster &placeholder){
    if (monster_id == 1)
    {
        placeholder.name  = "Cave Spider";
        placeholder.monster_id   = 1;
        placeholder.level        = 1;
        placeholder.base_health  = 15;
        placeholder.health_turn = placeholder.base_health;
        placeholder.current_health = placeholder.base_health;
        placeholder.base_attack  = 5;
        placeholder.base_defense = 2;
        placeholder.base_speed   = 4;
    }
    else if (monster_id == 2){
        placeholder.name  = "Cave Bat";
        placeholder.monster_id   = 2;
        placeholder.level        = 1;
        placeholder.base_health  = 10;
        placeholder.health_turn = placeholder.base_health;
        placeholder.current_health = placeholder.base_health;
        placeholder.base_attack  = 3;
        placeholder.base_defense = 2;
        placeholder.base_speed   = 6;
    }
    else if (monster_id == 3){
        placeholder.name = "Cave Worm";
        placeholder.monster_id   = 3;
        placeholder.level        = 1;
        placeholder.base_health  = 20;
        placeholder.health_turn = placeholder.base_health;
        placeholder.current_health = placeholder.health_turn;
        placeholder.base_attack  = 2;
        placeholder.base_defense = 2;
        placeholder.base_speed   = 2;
    }

}

int battleStart(Monster &placeholder, Player_Hero &player){

    std::cout << "You are attacked by a " << placeholder.name << "!" << std::endl;
    std::cout << "It currently has " << placeholder.current_health << " health remaining." << std::endl;

    std::cout << "\nYou currently have " << player.current_health << " health remaining." << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "Attack\tItems" << std::endl;

return 0;
}

int battlePlayerSelect(int &attack_choice, int &item_choice){
    int invalid_battle_input = 0;
do{
    std::string battle_player_input;
    std::cin >> battle_player_input;
    std::transform(battle_player_input.begin(), battle_player_input.end(), battle_player_input.begin(), ::tolower);
    if (battle_player_input == "attack"){
        attack_choice = 1;
        invalid_battle_input = 0;
        return 0;
    }
    else if(battle_player_input == "item" || battle_player_input == "items" ){
        item_choice = 1;
        invalid_battle_input = 0;
        return 0;
        }
        else{
            invalid_battle_input = 1;
            std::cout << "Invalid Input! Please try again." << std::endl;
        }
}
    while (invalid_battle_input == 1);{}

return 0;
}

int check_items(Player_Hero &player, int &player_chose_attack, int gold, int &health_potions, int attack_active){

 int health_restored = player.hero_level * 15;

    if (health_potions == 0 && gold == 0){
      std::cout << "You don't have any items... so you attack!" << std::endl;
        player_chose_attack = 1;
        attack_active = 1;
    }
    else if (health_potions == 0 && gold > 0){
        std::cout << "You don't have any health potions, but you do have " << gold << "gold coins." << std::endl;
        std::cout << "There aren't any shops down here, so you decide to attack for the moment." << std::endl;
        player_chose_attack = 1;
        attack_active = 1;
    }
    else if (health_potions > 0){
        std::cout << "You have " << health_potions << "health potions remaining." << std::endl;
        std::cout << "If you use a health potion, it will restore " << health_restored << "of your current HP." << std::endl;
        std::cout << "Would you like to use a health potion?" << std::endl;
        std::string player_item_confirm;
        std::cin >> player_item_confirm;
        std::transform(player_item_confirm.begin(), player_item_confirm.end(), player_item_confirm.begin(), ::tolower);
            if (player_item_confirm == "yes" || player_item_confirm == "y"){
                player_chose_attack = 0;
                attack_active = 1;
                health_potions--;
                player.health_turn = player.current_health;
                player.current_health = player.health_turn + health_restored;
                    if (player.current_health > player.base_health){
                        player.current_health = player.base_health;
                        return 0;
                        }
                        else{
                            attack_active = 1;
                            return 0;
                        }
                }
                else if (player_item_confirm == "no" || player_item_confirm == "n")
                    std::cout << "You change your mind and decide to attack instead." << std::endl;
                    player_chose_attack = 1;
                    attack_active = 1;
            }
        else{
            return 0;
        }
    return 0;
}



int battleAttackPhaseOne(int player_chose_attack, Player_Hero &player, Monster &placeholder,int &turn_order, int &damage){



    if (player.base_speed >= placeholder.base_speed){
        int turn_order = 1; //player is faster/ is as fast as opponent. next number is 3

        damage = static_cast<int>(player.base_attack / placeholder.base_defense);
        placeholder.current_health = placeholder.health_turn - damage;
        std::cout << "You attack " << placeholder.name << " for " << damage << " damage!" << std::endl;
        std::cout << placeholder.name << " has " << placeholder.current_health << " HP remaining!" << std::endl;
        }
    else if (player.base_speed < placeholder.base_speed){
        int turn_order = 2; // player is slower. next number is 4
        damage = static_cast<int>(placeholder.base_attack / player.base_defense);
        player.current_health = player.health_turn - placeholder.base_attack;
        std::cout << placeholder.name << " attacks you for " << damage << " damage!" << std::endl;
    }


}


int battleAttackPhaseTwo(){


}












