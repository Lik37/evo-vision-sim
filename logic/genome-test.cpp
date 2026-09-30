// g++ genome-test.cpp genome.cpp -o genome-test
#include "genome.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// #include <limits>

using namespace std;


Color maxMutate(4);


int main() 
{
    vector<Genome> genomes;
    bool run = true;

    while (run)
    {
        cout << 
R"(
1-all
2-spawn
3-mutate
4-Merge
5-game
0-exit
>>> )";

        int chose;
        cin >> chose;
        cout << "\n";

        switch (chose) 
        {
        case 1:
        {
            cout << "genomes:\n";
            for (size_t i = 0; i < genomes.size(); i++) {
                cout << i << ". " << genomes[i] << "\n";
            }
        }
        break;
        case 2:
        {   
            uint8_t r1;
            uint8_t r2;
            do {
                r1 = rand();
                r2 = rand();
            } while (r1 >= r2);
            Colorset friends({ {r1, r2} });
            do {
                r1 = rand();
                r2 = rand();
            } while (r1 >= r2);
            Colorset enemys({ {r1, r2} });

            genomes.push_back(Genome(Color(rand()), friends, enemys));
            cout << genomes.size() - 1 << ". " << genomes.back() << "\n";
        }
        break;
        case 3:
        {
            cout << "genomes:\n";
            for (size_t i = 0; i < genomes.size(); i++) {
                cout << i << ". " << genomes[i] << "\n";
            } 
            cout << "\ngen: ";
            size_t genId;
            cin >> genId;

            if (genId < genomes.size()) {
                cout << genId << ". " << genomes[genId] << "\n";
                
                genomes.push_back(mutateGenome(genomes[genId]));
                cout << genomes.size() - 1 << ". " << genomes.back() << "\n";
            } else {
                cout << "nothing\n";
            }
        }
        break;
        case 4:
        {
            cout << "genomes:\n";
            for (size_t i = 0; i < genomes.size(); i++) {
                cout << i << ". " << genomes[i] << "\n";
            } 
            cout << "\ng1: ";
            size_t genId1;
            cin >> genId1;
            cout << "g2: ";
            size_t genId2;
            cin >> genId2;

            if (genId1 < genomes.size() && genId2 < genomes.size()) {
                cout << genId1 << ". " << genomes[genId1] << "\n";
                cout << genId2 << ". " << genomes[genId2] << "\n";
                
                genomes.push_back(mergeGenomes(genomes[genId1], genomes[genId2]));
                cout << genomes.size() - 1 << ". " << genomes.back() << "\n";
            } else {
                cout << "nothing\n";
            }
        }
        break;
        case 5:
        {   
            bool run = true;
            while (run)
            {
                cout << 
R"(
GAMES
1-multiplicate
2-mul with enemy
0-exit
>>> )";

                int chose;
                cin >> chose;
                cout << "\n";

                switch (chose)
                {
                case 1:
                {   
                    int startTimeLife = 3;
                    vector<int> timesLife(genomes.size(), startTimeLife);

                    cout << "startTimeLife: " << startTimeLife << " maxMutate: " << maxMutate << "\n";
                    
                    string input = "";
                    
                    while (std::getline(std::cin, input) && input.empty()) 
                    {          
                        if (genomes.size() < 2)
                        {
                            cout << "\nThey all cooked\n";
                            break;
                        }

                        vector<size_t> randIndices;
                        for (size_t i = 0; i < genomes.size(); i++)
                            randIndices.push_back(i);
                        
                        for (size_t i = 0; i < randIndices.size(); i++) {
                            size_t j = i + rand() % (randIndices.size() - i);
                            size_t ri = randIndices[i];
                            randIndices[i] = randIndices[j];
                            randIndices[j] = ri;
                        }

                        cout << "\n";

                        vector<Genome> newGenomes;
                        for (size_t i = 0; i < randIndices.size() - 1; i++)
                        {   
                            size_t ri = randIndices[i];
                            const Genome &parent1 = genomes[ri];
                            
                            for (size_t j = i + 1; j < randIndices.size(); j++) 
                            {
                                size_t rj = randIndices[j];
                                const Genome &parent2 = genomes[rj];
                                
                                if (parent1.getPattern(parent2.color) == Patterns::FRIEND &&
                                    parent2.getPattern(parent1.color) == Patterns::FRIEND)
                                    {
                                        cout << ri << ". " << genomes[ri] << "\n";
                                        cout << rj << ". " << genomes[rj] << "\n";
                                        newGenomes.push_back(mutateGenome(mergeGenomes(genomes[ri], genomes[rj]), maxMutate));
                                        cout << newGenomes.back() << "\n\n";

                                        randIndices.erase(randIndices.begin() + j);
                                        break;
                                    }
                            }
                        }

                        vector<size_t> toErase;
                        for (size_t i = 0; i < timesLife.size(); i++) {
                            timesLife[i] -= 1;
                            if (timesLife[i] <= 0) 
                            {
                                if (newGenomes.empty()) {
                                    toErase.push_back(i);
                                } else {
                                    timesLife[i] = startTimeLife;
                                    genomes[i] = newGenomes.back();
                                    newGenomes.pop_back();
                                }
                            }
                        }
                        for (auto it = toErase.rbegin(); it != toErase.rend(); it++) {
                            timesLife.erase(timesLife.begin() + *it);
                            genomes.erase(genomes.begin() + *it);
                        }
                        for (Genome gen : newGenomes) {
                            genomes.push_back(gen);
                            timesLife.push_back(startTimeLife);
                        }

                        cout << "genomes:\n";
                        for (size_t i = 0; i < genomes.size(); i++) {
                            cout << i << ". " << genomes[i] << "\n";
                        }

                        cout << "(Enter)>>> ";
                    }
                }
                break;
                case 2:
                {   
                    int startTimeLife = 4;
                    vector<int> lifesTime(genomes.size(), startTimeLife);
                    
                    cout << "startTimeLife: " << startTimeLife << " maxMutate: " << maxMutate << "\n";
                    
                    int ec, ed1, ed2;
                    cout << "\ncreate enemy\n";
                    cout << "ec: "; cin >> ec;
                    cout << "ed1: "; cin >> ed1;
                    cout << "ed2: "; cin >> ed2;

                    Genome enemy(Color(ec), Colorset(), Colorset({{Color(ed1), Color(ed2)}}));
                    cout << "enemy: " << enemy << "\n\n";


                    string input = "";
                    
                    while (std::getline(std::cin, input) && input.empty()) 
                    {          
                        if (genomes.size() < 2)
                        {
                            cout << "\nThey all cooked\n";
                            break;
                        }

                        vector<size_t> toErase;


                        // убийства
                        for (size_t i = 0; i < genomes.size(); i++)
                        {
                            bool eated = false;

                            if (enemy.getPattern(genomes[i].color) == Patterns::ENEMY) {
                                switch (genomes[i].getPattern(enemy.color)) {
                                    case Patterns::ENEMY:
                                        if ( !(rand() % 5) ) { // 1 / 5
                                            eated = true;
                                        }
                                        break;
                                    case Patterns::NONE:
                                        if ( !(rand() % 2) ) { // 1 / 2
                                            eated = true;
                                        }
                                        break;
                                    case Patterns::FRIEND:
                                        if ( rand() % 3 ) { // 2 / 3
                                            eated = true;
                                        }
                                        break;
                                }

                                if (eated) {
                                    toErase.push_back(i);
                                    lifesTime[i] = 0;
                                    continue;
                                }
                            }
                        }


                        // случайная очередь
                        vector<size_t> randIndices;
                        for (size_t i = 0; i < genomes.size(); i++) {
                            if (lifesTime[i] <= 0)
                                continue;
                            randIndices.push_back(i);
                        }
                        for (size_t i = 0; i < randIndices.size(); i++) {
                            size_t j = i + rand() % (randIndices.size() - i);
                            size_t ri = randIndices[i];
                            randIndices[i] = randIndices[j];
                            randIndices[j] = ri;
                        }

                        cout << "\n";


                        // взаимодействия
                        vector<Genome> newGenomes;
                        for (size_t i = 0; i < randIndices.size() - 1; i++)
                        {   
                            size_t ri = randIndices[i];
                            const Genome &parent1 = genomes[ri];
                            
                            for (size_t j = i + 1; j < randIndices.size(); j++) 
                            {
                                size_t rj = randIndices[j];
                                const Genome &parent2 = genomes[rj];
                                
                                if (parent1.getPattern(parent2.color) == Patterns::FRIEND &&
                                    parent2.getPattern(parent1.color) == Patterns::FRIEND)
                                    {
                                        cout << ri << ". " << genomes[ri] << "\n";
                                        cout << rj << ". " << genomes[rj] << "\n";
                                        newGenomes.push_back(mutateGenome(mergeGenomes(genomes[ri], genomes[rj]), maxMutate));
                                        cout << newGenomes.back() << "\n\n";

                                        randIndices.erase(randIndices.begin() + j);
                                        break;
                                    }
                            }
                        }

                        // старость
                        for (size_t i = 0; i < lifesTime.size(); i++) {
                            if (lifesTime[i] == 0)
                                continue;
                            lifesTime[i] -= 1;
                            if (lifesTime[i] <= 0) {
                                toErase.push_back(i);
                            }
                        }

                        // очередь на удаление
                        for (auto it = toErase.rbegin(); it != toErase.rend(); it++) {
                            if (newGenomes.empty()) {
                                genomes[*it] = genomes.back(); 
                                genomes.pop_back();
                                lifesTime[*it] = lifesTime.back(); 
                                lifesTime.pop_back();
                            } else {
                                genomes[*it] = newGenomes.back();
                                newGenomes.pop_back();
                                lifesTime[*it] = startTimeLife;
                            }
                        }
                        // добавление остальных новых геномов
                        for (Genome gen : newGenomes) {
                            genomes.push_back(gen);
                            lifesTime.push_back(startTimeLife);
                        }

                        cout << "genomes:\n";
                        for (size_t i = 0; i < genomes.size(); i++) {
                            cout << i << ". " << genomes[i] << "\n";
                        }

                        cout << "\nenemy: " << enemy << "\n\n";

                        cout << "(Enter)>>> ";
                    }
                }
                break;
                case 3:
                {   
                    // int startTimeLife = 4;
                    // vector<int> timesLeft(genomes.size(), startTimeLife);

                    // int eatTimeIncrease = 2;
                    // cout << "eatTimeIncrease: "; cin >> eatTimeIncrease;
                    // cout << "\n";

                    // string input = "";
                    
                //     // while (std::getline(std::cin, input) && input.empty()) 
                //     {          
                //         if (genomes.size() < 2)
                //         {
                //             cout << "\nThey all cooked\n";
                //             break;
                //         }

                //         vector<size_t> randIndices;
                //         for (size_t i = 0; i < genomes.size(); i++)
                //             randIndices.push_back(i);
                        
                //         for (size_t i = 0; i < randIndices.size(); i++) {
                //             size_t j = i + rand() % (randIndices.size() - i);
                //             size_t ri = randIndices[i];
                //             randIndices[i] = randIndices[j];
                //             randIndices[j] = ri;
                //         }

                //         cout << "\n";

                //         // Взаимодействия
                //         vector<Genome> newGenomes;
                //         for (size_t i = 0; i < randIndices.size() - 1; i++)
                //         {   
                //             size_t ri = randIndices[i];
                //             const Genome &parent1 = genomes[ri];
                            
                //             for (size_t j = i + 1; j < randIndices.size(); j++) 
                //             {
                //                 size_t rj = randIndices[j];
                //                 if (timesLeft[rj] == 0)
                //                     continue;
                //                 const Genome &parent2 = genomes[rj];
                                
                //                 bool eated1 = false;
                //                 bool eated2 = false;

                //                 if (parent1.getPattern(parent2.color) == Patterns::ENEMY) {
                //                     switch (parent2.getPattern(parent1.color)) {
                //                         case Patterns::ENEMY:
                //                             if ( !(rand() % 2) ) {
                //                                 eated1 = true;
                //                             } else {
                //                                 eated2 = true;
                //                             }
                //                             break;
                //                         case Patterns::NONE:
                //                             if ( !(rand() % 2) ) {
                //                                 eated2 = true;
                //                             }
                //                             break;
                //                         case Patterns::FRIEND:
                //                             eated2 = true;
                //                             break;
                //                     }
                //                 } else if (parent2.getPattern(parent1.color) == Patterns::ENEMY) {
                //                     switch (parent1.getPattern(parent2.color)) {
                //                         case Patterns::NONE:
                //                             if ( !(rand() % 2) ) {
                //                                 eated1 = true;
                //                             }
                //                             break;
                //                         case Patterns::FRIEND:
                //                             eated1 = true;
                //                             break;
                //                     }
                //                 }
                //                 else if (parent1.getPattern(parent2.color) == Patterns::FRIEND &&
                //                          parent2.getPattern(parent1.color) == Patterns::FRIEND)
                //                 {
                //                     newGenomes.push_back(mutateGenome(mergeGenomes(genomes[ri], genomes[rj])));
                //                     randIndices.erase(randIndices.begin() + j);
                //                     break;
                //                 }

                //                 if (eated1) {
                //                     timesLeft[ri] = 0;
                //                     timesLeft[rj] += eatTimeIncrease;
                //                     break;
                //                 } else if (eated2) {
                //                     timesLeft[ri] += eatTimeIncrease;
                //                     timesLeft[rj] = 0;
                //                     break;
                //                 }
                //             }
                //         }

                //         vector<size_t> toErase;
                //         for (size_t i = 0; i < timesLeft.size(); i++) {
                //             timesLeft[i] -= 1;
                //             if (timesLeft[i] <= 0) 
                //             {
                //                 if (newGenomes.empty()) {
                //                     toErase.push_back(i);
                //                 } else {
                //                     timesLeft[i] = startTimeLife;
                //                     genomes[i] = newGenomes.back();
                //                     newGenomes.pop_back();
                //                 }
                //             }
                //         }
                //         for (auto it = toErase.rbegin(); it != toErase.rend(); it++) {
                //             timesLeft.erase(timesLeft.begin() + *it);
                //             genomes.erase(genomes.begin() + *it);
                //         }
                //         for (Genome gen : newGenomes) {
                //             genomes.push_back(gen);
                //             timesLeft.push_back(startTimeLife);
                //         }

                //         cout << "genomes:\n";
                //         for (size_t i = 0; i < genomes.size(); i++) {
                //             cout << i << ". " << genomes[i] << "\n";
                //         }

                //         cout << "\n(Enter)>>> ";
                //     }
                }
                break;
                case 0:
                    run = false;
                    cout << "<--\n";
                break;
                default:
                {
                    cout << "invalid enter\n";
                }
                break;
                }
            }
        }
        break;
        case 0:
        {
            run = false;
            cout << "EXIT...\n";
        }
        break;
        default:
        {
            cout << "invalid enter\n";
        }
        break;
        }

        // if (genomes.size() > 30) {
        //     genomes.erase(genomes.begin());
        // }
    }
}

