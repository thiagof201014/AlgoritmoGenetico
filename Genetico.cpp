#include<iostream>
#include<vector>
#include<cstdlib>
#include<math.h>
using namespace std;

struct Individual{
    string binary;
    int fitness;
};

string int_to_binary(int num);
int binary_to_int(string binary);
int bestPos;

class Genetic{
    private:
        // Attributes
        vector<Individual> population;
        int populationSize;
        int lowerBound;
        int upperBound;
        int generations;
        int mutationRate;
        int crossoverRate;
        int n; // Number of individuals for the tournament selection

        // Private methods
        void generate_population();
        Individual tournament();
        void mutation(Individual individual);
        void crossover(Individual individual);
        float calculate_fitness(string binary);

    public:
        Genetic(int populationSize, int lowerBound, int upperBound, int generations, int mutationRate, int crossoverRate, int n);
        Genetic();
        void run();
};
Genetic::Genetic(int populationSize, int lowerBound, int upperBound, int generations, int mutationRate, int crossoverRate, int n){
    this->populationSize = populationSize;
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;
    this->generations = generations;
    this->mutationRate = mutationRate;
    this->crossoverRate = crossoverRate;
    this->n = n;

    generate_population();
}

Genetic::Genetic(){
    this->populationSize = 4;
    this->lowerBound = -10;
    this->upperBound = 10;
    this->generations = 50;
    this->mutationRate = 1;
    this->crossoverRate = 70;
    this->n = 2;

    generate_population();
}

void Genetic::generate_population() {
    srand((unsigned)time(NULL));
    for (int i = 0; i < populationSize; i++) {
        int random = rand() % (upperBound - lowerBound + 1) + lowerBound;
        string binary = int_to_binary(random);
        Individual individual;
        individual.binary = binary;
        individual.fitness = calculate_fitness(binary);
        population.push_back(individual);
    }
}

Individual Genetic::tournament(){
    srand((unsigned) time(NULL));
    bestPos = rand() % populationSize;
    Individual winner = population.at(bestPos);
    for(int i = 0; i < n; i++){
        int random2 = rand() % populationSize;
        if(population.at(random2).fitness > winner.fitness){
            winner = population.at(random2);
        }
    }
    return winner;
}

void Genetic::mutation(Individual individual){
    srand((unsigned) time(NULL));
    int random = rand() % 100;
    if(random < mutationRate){
        int random2 = rand() % individual.binary.size();
        if(individual.binary[random2] == '0'){
            individual.binary[random2] = '1';
        }
        else{
            individual.binary[random2] = '0';
        }
    }
}

void Genetic::crossover(Individual individual){
    srand((unsigned) time(NULL));
    int random = rand() % 100;
    if(random < crossoverRate){
        int random2 = rand() % populationSize;
        string binary1 = individual.binary;
        string binary2 = population.at(random2).binary;
        int random3 = rand() % binary1.size();

        string binaryAux1 = binary1.substr(0, random3);
        string binaryAux2 = binary2.substr(random3, binary2.size());
        string binaryAux3 = binary2.substr(0, random3);
        string binaryAux4 = binary1.substr(random3, binary1.size());
        binary1 = binaryAux1 + binaryAux2;
        binary2 = binaryAux3 + binaryAux4;

        Individual individual1;
        individual1.binary = binary1;
        individual1.fitness = calculate_fitness(binary1);
        Individual individual2;
        individual2.binary = binary2;
        individual2.fitness = calculate_fitness(binary2);

        population.erase(population.begin() + random2);
        population.erase(population.begin() + bestPos);
        population.push_back(individual1);
        population.push_back(individual2);
    }
}

float Genetic::calculate_fitness(string binary){
    int num = binary_to_int(binary);
    return (num*num) + (3*num) + 4;
}

void Genetic::run(){
    for(int i = 0; i < generations; i++){
        Individual winner = tournament();
        mutation(winner);
        crossover(winner);
    }
    float bestFitness = -100000000;
    float bestIndividual = 0;
    for(Individual individual : population){
        if(individual.fitness > bestFitness){
            bestFitness = individual.fitness;
            bestIndividual = binary_to_int(individual.binary);
        }
    }
    cout << "Best individual fitness: " << bestFitness << endl;
    cout << "Best individual x: " << bestIndividual << endl;
}

string int_to_binary(int num) {
    char signal = '0';
    if (num < 0) {
        // The number is negative
        signal = '1';
        num *= -1;
    }

    string binary = "";
    while (num > 0) {
        if (num % 2 == 0) {
            binary = "0" + binary;
        } else {
            binary = "1" + binary;
        }
        num /= 2;
    }

    if (binary.empty()) {
        binary = "0";
    }
    binary = signal + binary;

    return binary;
}

int binary_to_int(string binary){
    int num = 0;
    int power = 0;
    for(int i = binary.size() - 1; i > 0; i--){
        if(binary[i] == '1'){
            num += pow(2, power);
        }
        power++;
    }
    if(binary[0] == '1'){
        num *= -1;
    }
    return num;
}
int main(){
    Genetic genetic;
    genetic.run();

    return 0;
}
