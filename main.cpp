//
//  Labo1.cpp
//  Labos ASD1 2018
//
//  Created by Olivier Cuisenaire on 16.12.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//
//	/* NOMS DES ETUDIANTS ICI */
//

#include <stdlib.h>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

enum class Functions {CHERCHER_POSITION, TRIER, CHERCHER_SI_CONTIENT, F, G, RANDOM, RANDOM_2};
unsigned count = 0;

/**
 * Recherche la position d'une valeur dans un vector.
 *
 * Pour la complexité, on considère le nombre d'itérations.
 * Tester pour diverses valeurs de val, présentes ou non dans le vector.
 *
 * @param v vector dans lequel on cherche
 * @param val valeur à chercher
 * @return la position de la valeur dans le vector si trouvé, -1 sinon
 */
size_t chercherPosition(const vector<int> &v, int val) {
    for (size_t i = 0; i < v.size(); ++i) {
        ++count;
        if (v.at(i) == val)
            return i;
    }
    return -1;
}


/**
 * Trie un vector.
 *
 * Pour la complexité, on considère le nombre de comparaisons (>)
 *
 * @param v vector à trier
 */
void trier(vector<int> &v) {
    if (v.empty()) return;

    for (int a : v) {
        auto j = v.begin();
        auto k = j++;
        for (; j != v.end(); k = j++) {
            ++count;
            if (*k > *j) {
                swap(*k, *j);
            }
        }
    }
}

/**
 * Retourne true si la valeur est contenue dans le vector.
 *
 * Pour la complexité, on considère le nombre d'itérations.
 * v doit être trié en entrée !
 * Tester pour diverses valeurs de val, présentes ou non dans le vecteur.
 *
 * @param v vector trié dans lequel on cherche
 * @param val valeur à chercher
 * Retourne true si la valeur est contenue dans le vector, false sinon.
 */
bool chercherSiContient(const vector<int> &v, int val) {
    auto first = v.begin();
    auto last = v.end();

    while (first != last) {
        auto mid = first + (last - first) / 2;
        ++count;
        if (*mid == val) {
            return true;
        } else if (*mid < val) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    return false;
}

/**
 * Pour la complexité, on considère le nombre d'additions
 *
 * @param n
 * @return
 */
unsigned long long f(unsigned n) {

    if (n == 0) return 1;


    // the counter is increased by two because it's asked to take into
    // account the number of addition made for the complexity and their are 2 of them each
    // time the function is called
    count += 2;

    return f(n - 1) + f(n - 1) + f(n - 1);
}

/**
 * Pour la complexité, on considère le nombre d'additions (+=)
 *
 * @param v
 */
void g(vector<int> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = v.size() - 1; j > 0; j /= 2) {
            ++count;
            v.at(i) += v.at(j);
        }
    }
}

/**
 * Pour la complexité, on considère les opérations push_back()
 *
 * Evaluer le temps d'exécution
 *
 * @param N nombre de données à générer
 * @param maxVal valeur maximale des données
 * @return vector rempli de N valeurs aléatoires.
 */
vector<int> random(size_t N, int maxVal) {

    vector<int> v;
    for (size_t i = 0; i < N; ++i) {
        v.push_back(1 + rand() % maxVal);
    }

    return v;
}

/**
 * Pour la complexité, on considère les opérations insert()
 *
 * Evaluer le temps d'exécution
 *
 * @param N nombre de données à générer
 * @param maxVal valeur maximale des données
 * @return vector rempli de N valeurs aléatoires.
 */
vector<int> random2(size_t N, int maxVal) {

    vector<int> v;
    for (size_t i = 0; i < N; ++i) {
        v.insert(v.begin(), 1 + rand() % maxVal);
    }

    return v;
}

void test(const Functions& FUNCTION_TO_TEST){

    vector<unsigned> vector_sizes;
    unsigned replication;// Search replication in each vector

    switch(FUNCTION_TO_TEST){

        // First function : "Chercher Position"
        case Functions::CHERCHER_POSITION:

            vector_sizes = {500, 2500, 4500, 6500, 8500, 10500};
            replication = 100000;

            // Loop through all vector sizes and search (REPLICATION times) a random number
            for (auto i = vector_sizes.begin(); i < vector_sizes.end(); ++i) {
                // Create a new vector contains : 1 ... currentSize)
                vector<int> vector(*i);
                for (unsigned j = 1; j <= *i; ++j) {
                    vector.at(j - 1) = j;
                }

                unsigned average = 0;
                // Search 1'000'000x a random number between -currentSize ... currentSize
                for (unsigned k = 0; k < replication; ++k) {
                    count = 0;
                    int randomNb = rand() % *i;
                    chercherPosition(vector, randomNb);
                    average += count;
                }

                average = average / replication;

                cout << "Pour un vecteur contenant " << *i << " éléments" << ", la moyenne des itération est : " << average << endl;
            }

            break;

        case Functions::TRIER:
            vector_sizes = {5, 25, 125, 625, 3125, 15625};
            for(auto i = vector_sizes.begin(); i < vector_sizes.end(); ++i) {
                // Create vector contains random number to sort
                unsigned currentVectorSize = *i;
                vector<int> vectorToSort(currentVectorSize);
                for(unsigned currentPos = 0; currentPos < currentVectorSize; ++currentPos) {
                    vectorToSort.at(currentPos) = rand();
                }

                // Count each comparison in the target function
                count = 0;
                trier(vectorToSort);

                cout << "Pour un vecteur contenant " << currentVectorSize << " éléments" << ", la moyenne des comparaison est : " << count << endl;
            }

            break;
        case Functions::CHERCHER_SI_CONTIENT:
            vector_sizes = {1000, 5000, 10000, 50000, 100000, 1000000};
            replication = 100000;

            // Loop through all vector sizes and search (REPLICATION times) a random number
            for (auto i = vector_sizes.begin(); i < vector_sizes.end(); ++i) {
                // Create a new vector contains : 1 ... currentSize)
                vector<int> vector(*i);
                for (unsigned j = 1; j <= *i; ++j) {
                    vector.at(j - 1) = j;
                }

            unsigned average = 0;

            for (unsigned k = 0; k < replication; ++k) {
              count = 0;
              int randomNb = rand();
              chercherSiContient(vector, randomNb);
              average += count;
            }

            average = average / replication;

            cout << "Pour un vecteur contenant " << *i << " elements" << ", la moyenne des iteration est : " << average << endl;
          }
            break;

        case Functions::F:

            vector_sizes = {5, 6, 7, 8, 9, 10};

            for (auto i = vector_sizes.begin(); i < vector_sizes.end() ; ++i) {
                count = 0;
                f(*i);
                cout << "Pour un N de " << *i << ", le nombre d'addiction est : " << count << endl;
            }

            break;

            break;

        case Functions::G:
            vector_sizes = {16, 64, 128, 512, 1000, 5000 };
            replication = 1000;

            // Loop through all vector sizes and search (REPLICATION times) a random number
            for (auto i = vector_sizes.begin(); i < vector_sizes.end(); ++i) {
              unsigned average = 0;
              vector<int> v(*i, 1);

              for ( unsigned k = 0; k < replication; ++k) {
                count = 0;
                // for ( auto a : v) {
                //   cout << a << ", ";
                // }
                g(v);
                average += count;
                // for ( auto a : v) {
                //   cout << a << ", ";
                // }
              }

              average = average / replication;
              
              cout << "Pour un vecteur contenant " << *i << " éléments"
                   << ", la moyenne des additions est : " << average << endl;
            }

            break;

        case Functions::RANDOM:

            // TODO

            break;

        case Functions::RANDOM_2:
            
            // TODO

            break;
    }
}

int main() {
    //initialisation du générateur aléatoire
    srand(time(NULL));

    test(Functions::F);
}
