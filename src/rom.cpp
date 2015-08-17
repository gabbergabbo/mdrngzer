#include "rom.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <QDebug>

ROM::ROM(unsigned seed) : rand(seed) {
}

void ROM::open(const std::string &filePath) {
    std::ifstream file(filePath, std::ios::binary);
    file.seekg(0, std::ios::end);
    memory.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    
    file.read((char*)memory.data(), memory.size());
    if (std::strcmp("POKEDUN SORAC2SE01", (char*)memory.data())) {
        throw std::string("ROM: ROM must be Pokemon Mystery Dungeon - Explorers of Sky");
    }
}

void ROM::save(const std::string &filePath) {
    std::ofstream file(filePath, std::ios::binary);
    file.write((char*)memory.data(), memory.size());
}

void ROM::randPokemon() {
    const uint16_t maxPokemonId = 0x217;
    
    const uint16_t excludedPokemon[] = {
        0x0000, //No pokemon/end of list
        0x0090, //Articuno
        0x0091, //Zapdos
        0x0092, //Moltres
        0x0096, //Mewtwo
        0x0097, //Mew
        0x00C9, //Unown A
        0x00CA, //Unown B
        0x00CB, //Unown C
        0x00CC, //Unown D
        0x00CD, //Unown E
        0x00CE, //Unown F
        0x00CF, //Unown G
        0x00D0, //Unown H
        0x00D1, //Unown I
        0x00D2, //Unown J
        0x00D3, //Unown K
        0x00D4, //Unown L
        0x00D5, //Unown M
        0x00D6, //Unown N
        0x00D7, //Unown O
        0x00D8, //Unown P
        0x00D9, //Unown Q
        0x00DA, //Unown R
        0x00DB, //Unown S
        0x00DC, //Unown T
        0x00DD, //Unown U
        0x00DE, //Unown V
        0x00DF, //Unown W
        0x00E0, //Unown X
        0x00E1, //Unown Y
        0x00E2, //Unown Z
        0x00E3, //Unown !
        0x00E4, //Unown ?
        0x010E, //Raikou
        0x010F, //Entei
        0x0110, //Suicune
        0x0114, //Lugia
        0x0115, //Ho-oh
        0x0116, //Celebi
        0x0117, //Celebi(shiny)
        0x017B, //Castform(form a)
        0x017C, //Castform(form b)
        0x017D, //Castform(form c)
        0x017E, //Castform(form d)
        0x017F, //Kecleon
        0x0180, //Kecleon(shiny)
        0x0199, //Regirock
        0x019A, //Regice
        0x019B, //Registeel
        0x019C, //Latias
        0x019D, //Latios
        0x019E, //Kyogre
        0x019F, //Groudon
        0x01A0, //Rayquaza
        0x01A1, //Jirachi
        0x01A2, //Deoxys(form a)
        0x01A3, //Deoxys(form b)
        0x01A4, //Deoxys(form c)
        0x01A5, //Deoxys(form d)
        0x0207, //Dusknoir
        0x0208, //Froslass
        0x0209, //Rotom
        0x020A, //Uxie
        0x020B, //Mesprit
        0x020C, //Azelf
        0x020D, //Dialga
        0x020E, //Palkia
        0x020F, //Heatran
        0x0210, //Regigigas
        0x0211, //Girarina
        0x0212, //Cresselia
        0x0213, //Phione
        0x0214, //Manaphy
        0x0215, //Darkrai
        0x0216, //Shaymin
        0x0229  //Decoy
    };
    
    std::vector<uint16_t> choosables;
    
    for (uint16_t i = 0; i != maxPokemonId; i++)
        if (std::find(std::begin(excludedPokemon), std::end(excludedPokemon), i) == std::end(excludedPokemon))
            choosables.push_back(i);
    
    for (unsigned i = 0; i != 14229; i++) {
        uint8_t *entry = memory.data() + 0x003EB1D0 + i * 8;
        //Check for every unchoosable pokemon type
        bool finish = false;
        for (uint16_t excludable : excludedPokemon) {
            //If it matches
            if (!std::memcmp(entry + 6, &excludable, 2)) {
                //Dont randomize this pokemon
                finish = true;
                break;
            }
        }
        //If this is an unreplacable, finish here
        if (finish)
            continue;
        
        //Choose the pokemon to use
        unsigned choice = rand() % choosables.size();
        
        memcpy(entry + 6, &choosables[choice], 2);
    }
}

void ROM::randAbilities() {
    const uint8_t maxAbilityId = 0x7C;
    
    const uint8_t excludedAbilities[] = {
        0x00, //No ability
        0x35, //Wonder Guard, possibly gamebreaking
        0x74  //Unknown ability, named "$$$"
    };
    
    struct PokemonAbility {
        uint8_t first, second;
    };
    
    std::vector<uint8_t> choosables;
    std::vector<PokemonAbility> pokemonAbilities;
    
    //Make choosable abilitities list
    for (uint8_t i = 0; i != maxAbilityId; i++) {
        if (std::find(std::begin(excludedAbilities), std::end(excludedAbilities), i) == std::end(excludedAbilities))
            choosables.push_back(i);
    }
    
    //Map abilities to every pokemon ID
    for (unsigned i = 0; i != 600; i++) {
        pokemonAbilities.emplace_back();
        PokemonAbility &a = pokemonAbilities.back();
        a.first = choosables[rand() % choosables.size()];
        
        //50% chance for second ability
        if ((rand() % 100) < 50)
            a.second = choosables[rand() % choosables.size()];
        else
            a.second = 0;
    }

    //Iterate through all pokemon entires and assign their abilities based on pokemon ID
    for (unsigned i = 0; i != 1155; i++) {
        uint8_t *entry = memory.data() + 0x00472808 + i * 68;

        //Get pokemon ID from memory
        uint16_t ID = *(entry+4)+*(entry+5)*256;

        memcpy(entry + 0x18, &pokemonAbilities[ID].first, 1);
        memcpy(entry + 0x19, &pokemonAbilities[ID].second, 1);
    }
}

void ROM::randTypes() {
    const uint8_t maxTypeId = 0x12;
    
    const uint8_t excludedTypes[] = {
        0x00, //No type, so excluded
        0x12  //Neutral type, not used for pokemon
    };
    
    struct PokemonType {
        uint8_t first, second;
    };
    
    std::vector<uint8_t> choosables;
    std::vector<PokemonType> pokemonTypes;
    
    //Make choosable Types list
    for (uint8_t i = 0; i != maxTypeId; i++)
        if (std::find(std::begin(excludedTypes), std::end(excludedTypes), i) == std::end(excludedTypes))
            choosables.push_back(i);
    
    //Map types to every pokemon ID
    for (unsigned i = 0; i != 600; i++) {
        pokemonTypes.emplace_back();
        PokemonType &t = pokemonTypes.back();
        t.first = rand() % choosables.size();
        
        //40% chance for second Type
        if ((rand() % 100) < 40)
            t.second = rand() % choosables.size();
        else
            t.second = 0;
    }

    //Assign the values to the pokemon entries
    for (unsigned i = 0; i != 1155; i++) {
        uint8_t *entry = memory.data() + 0x00472808 + i * 68;

        //Get pokemon ID from memory
        uint16_t ID = *(entry+4)+*(entry+5)*256;

        memcpy(entry + 0x14, &pokemonTypes[ID].first, 1);
        memcpy(entry + 0x15, &pokemonTypes[ID].second, 1);
    }
}

void ROM::randIQs() {
    const uint8_t maxIQId = 0xF;
    
    const uint8_t excludedIQs[] = {
        0x08, //Unused
        0x09, //Unused
        0x0C, //Unused
        0x0D, //Unused
        0x0E, //Unused
        0x0F  //Invalid
    };
    
    std::vector<uint8_t> choosables;
    std::vector<uint8_t> pokemonIQs;
    
    //Make choosable IQ's list
    for (uint8_t i = 0; i != maxIQId; i++)
        if (std::find(std::begin(excludedIQs), std::end(excludedIQs), i) == std::end(excludedIQs))
            choosables.push_back(i);
    
    //Map IQ's to every pokemon ID
    for (unsigned i = 0; i != 600; i++)
        pokemonIQs.push_back(choosables[rand() % choosables.size()]);
    
    //Assign the values to the pokemon entries
    for (unsigned i = 0; i != 1155; i++) {
        uint8_t *entry = memory.data() + 0x00472808 + i * 68;

        //Get pokemon ID from memory
        uint16_t ID = *(entry+4)+*(entry+5)*256;

        memcpy(entry + 0x17, &pokemonIQs[ID], 1);
    }
}

void ROM::randMusic() {
    const uint8_t maxMusicId = 0x80;

    const uint8_t excludedMusic[] = {
        0x00, //No music
        0x36, //No music
        0x76, //No music
        0x77, //No music
        0x78, //No music
        0x79, //No music
        0x7A, //No music
        0x7B, //No music
        0x7C, //No music
        0x7D, //No music
        0x7E, //No music
        0x7F  //No music
    };

    std::vector<uint8_t> choosables;
    std::vector<uint8_t> Music;

    for (uint8_t i = 0; i != maxMusicId; i++)
        if (std::find(std::begin(excludedMusic), std::end(excludedMusic), i) == std::end(excludedMusic))
            choosables.push_back(i);

    //generate list for dungeon
    for (unsigned i = 0; i != 200; i++)
        Music.push_back(choosables[rand() % choosables.size()]);

    unsigned count = 0;
    uint8_t last = 0x01;

    //Assign the values to the floor entries
    for (unsigned i = 0; i != 1837; i++) {
        uint8_t *entry = memory.data() + 0x003DC7B0 + i * 32;

        uint8_t current = *(entry + 0x3);

        if (last != current) {
            count++;
        }

        last = *(entry + 0x3);
        memcpy(entry + 0x3, &Music[count], 1);

    }
}
