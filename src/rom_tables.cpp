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

const uint8_t maxAbilityId = 0x7C;

const uint8_t excludedAbilities[] = {
    0x00, //No ability
    0x35, //Wonder Guard, possibly gamebreaking
    0x74  //Unknown ability, named "$$$"
};

const uint8_t maxTypeId = 0x12;

const uint8_t excludedTypes[] = {
    0x00, //No type, so excluded
    0x12  //Neutral type, not used for pokemon
};

const uint8_t maxIQId = 0xF;

const uint8_t excludedIQs[] = {
    0x08, //Unused
    0x09, //Unused
    0x0C, //Unused
    0x0D, //Unused
    0x0E, //Unused
    0x0F  //Invalid
};