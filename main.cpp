#include <iostream>
#include "Player.hpp"
#include "SugarPP/all.hpp"

#include <vector>
#include <array>
#include <span>
#include <algorithm>

using namespace std;
using namespace SugarPP;

static const vector<const string> names
{
    "QuantumQuest", "MysticJester", "LunaPhoenix", "CipherSeeker", "NebulaWhisper",
    "ZenPioneer", "VelvetVortex", "EnigmaExplorer", "AstralHarmony", "ThunderMyst",
    "StarlightGlider", "QuantumBard", "NeonNomad", "CelestialCipher", "SapphireEcho",
    "ChronoWanderer", "SereneLabyrinth", "MiragePioneer", "TechnoSculptor", "PhoenixFable",
    "SolarEcho", "ElysianVagrant", "ZephyrOracle", "PixelSorcerer", "NebulaLoom",
    "QuantumQuasar", "EtherealCrafter", "VelvetSpectra", "PrismNomad", "CosmicPulse",
    "LunarMystique", "StellarRogue", "EnchantVoyager", "PinnaclePeregrine", "RogueSpecter",
    "NebulaNomad", "ZenithLoom", "EchoCipher", "AstralSculptor", "CelestialPioneer",
    "QuantumWanderer", "NovaHarmony", "ChronoSorcerer", "SeraphicVoyager", "EonExplorer",
    "MirageNomad", "TechnoSculptor", "RadiantPulse", "EtherealJester", "StellarWhisper"
};

vector<Player> generate_players()
{
    Range score_rng(0, 26);
    vector<Player> players;
    players.reserve(names.size());

    for(const string& name : names)
        players.emplace_back(name, score_rng.rand(), score_rng.rand());
    
    return players;
}

template <class T>
ostream& operator<<(ostream& os, const span<T>& values)
{
    for(const T& value : values)
        os << value << endl;
    
    return os;
}

int main()
{
    cout << endl;

    vector<Player> players = generate_players();

    sort(players.begin(), players.end());

    span<Player> players_span(players.begin(), players.end());
    size_t chunk_size = players_span.size() / 3;
    size_t leftover_size = players_span.size() % 3;

    span<Player> low_players(players_span.begin(), players_span.begin() + chunk_size);
    span<Player> mid_players(low_players.end(), low_players.end() + chunk_size + leftover_size);
    span<Player> high_players(mid_players.end(), players_span.end());

    cout << "\n[[ Low Players ]]\n\n" << low_players << endl;
    cout << "\n[[ Mid Players ]]\n\n" << mid_players << endl;
    cout << "\n[[ High Players ]]\n\n" << high_players << endl;
}