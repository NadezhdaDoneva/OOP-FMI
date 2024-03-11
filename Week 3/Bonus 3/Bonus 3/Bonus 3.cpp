// Bonus 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

const int MAX_NAME_SIZE = 50;

enum class Type {
    NORMAL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC, 
    GHOST,
    FLYING
};

struct Pokemon {
    char name[50];
    Type type;
    unsigned int strength = 0;
};

//1
Pokemon createPokemon() {
    Pokemon pokemon;

    unsigned int type;
    std::cin >> pokemon.name >> type >> pokemon.strength;
    pokemon.type = Type(type);
    return pokemon;
}

//2
Pokemon createPokemonFromBinaryFile(std::ifstream& ifs) {
    Pokemon pokemon;
    ifs.read((char*)&pokemon, sizeof(pokemon));

    return pokemon;
}

//3
void savePokemonInBinaryFile(const char* fileName, const Pokemon& pokemon, int startIdx) {
    std::ofstream ofs(fileName, std::ios::binary | std::ios::ate);
    if (!ofs.is_open()) {
        std::cout << "The file can not be opened" << std::endl;
        return;
    }

    ofs.seekp(startIdx, std::ios::beg);
    ofs.write((const char*)&pokemon, sizeof(pokemon));
    ofs.close();
}

//4
struct PokemonHandler {
    char* file;
};

PokemonHandler newPokemonHandler(const char* filename) {
    PokemonHandler pokemonHandler;
    strcpy(pokemonHandler.file, filename);
    return pokemonHandler;
}

//5
int size(const PokemonHandler& ph) {
    std::ifstream ifs(ph.file, std::ios::binary);

    if (!ifs.is_open()) {
        return -1;
    }

    int currPosition = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    int fileSize = ifs.tellg();
    
    ifs.seekg(currPosition);
    return fileSize / sizeof(Pokemon);
}

//6
bool isValidIdx(const int i, const PokemonHandler& ph) {
    return (i > 0 && i < size(ph));
}

Pokemon at(const PokemonHandler& ph, int i) {
    Pokemon pokemon;
    if (!isValidIdx(i, ph)) {
        std::cout << "Unvalid index" << std::endl;
        return pokemon;
    }

    std::ifstream ifs(ph.file, std::ios::binary);
    if (!ifs.is_open()) {
        std::cout << "The file can not be opened" << std::endl;
        return pokemon;
    }

    ifs.seekg(i * sizeof(Pokemon), std::ios::beg);
    pokemon = createPokemonFromBinaryFile(ifs);

    ifs.close();
    return pokemon;
}


//7
void swap(const PokemonHandler& ph, int i, int j) {
    if (!isValidIdx(i, ph) || !isValidIdx(j, ph)) {
        std::cout << "Unvalid index" << std::endl;
        return;
    }

    Pokemon pokemon1 = at(ph, i);
    Pokemon pokemon2 = at(ph, j);

    savePokemonInBinaryFile(ph.file, pokemon1, j * sizeof(Pokemon));
    savePokemonInBinaryFile(ph.file, pokemon2, i * sizeof(Pokemon));
}

//8
void swapPokemons(const PokemonHandler& ph, const int i, const int j) {
    if (!isValidIdx(i, ph) || !isValidIdx(j, ph)) {
        break;
    }

    Pokemon p1 = at(ph, i);
    Pokemon p2 = at(ph, j);

    savePokemonInBinaryFile(ph.file, p1, j * sizeof(Pokemon));
    savePokemonInBinaryFile(ph.file, p2, i * sizeof(Pokemon));
}

void insert(const PokemonHandler& ph, const Pokemon& pokemon) {
    size_t idx = size(ph);
    savePokemonInBinaryFile(ph.file, pokemon, idx);
    Pokemon curPokemon = at(ph, idx--);
    
    while (curPokemon.strength > pokemon.strength) {
        swapPokemons(ph, idx, idx - 1);
        curPokemon = at(ph, idx--);
    }
}

//9
void savePokemonInTextFile(std::ofstream& ofs, const Pokemon& pokemon) {
    ofs << pokemon.name << (int)pokemon.type << pokemon.strength;
}

void textify(const PokemonHandler& ph, const char* filename) {
    std::ifstream ifs(ph.file, std::ios::binary);
    std::ofstream ofs(filename);

    if (!ifs.is_open() || !ofs.is_open()) {
        std::cout << "The file can not be opened" << std::endl;
        return;
    }

    while (!ifs.eof()) {
        Pokemon pokemon = createPokemonFromBinaryFile(ifs);
        savePokemonInTextFile(ofs, pokemon);
    }

    ifs.close();
    ofs.close();
}

//10
Pokemon& createPokemonFromTextFile(std::ifstream& ifs, Pokemon& pokemon) {
    unsigned int type;
    ifs.getline(pokemon.name, MAX_NAME_SIZE, '\n');
    ifs >> type;
    ifs >> pokemon.strength;
    pokemon.type = Type(type);
    return pokemon;
}

void untextify(const PokemonHandler& ph, const char* filename) {
    std::ifstream ifs(filename);
    
    if (!ifs.is_open()) {
        std::cout << "The file can not be opened" << std::endl;
        return;
    }

    int idx = 0;
    while (!ifs.eof()) {
        Pokemon pokemon;
        createPokemonFromTextFile(ifs, pokemon);
        savePokemonInBinaryFile(ph.file, pokemon, idx);
        idx += sizeof(pokemon);
    }

    ifs.close();
}

int main()
{
    std::cout << "Hello World!\n";
    PokemonHandler ph;
    ph.file = "savedPokemons.dat";
    untextify(ph, "pokemon.txt");
}

