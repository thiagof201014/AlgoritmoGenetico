#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

string int_to_binary(int num);

class Genetic{
    private:
        vector<int> population;
        int populationSize;
        int lowerBound;
        int upperBound;
        int x; 
        int mutationRate;
        int crossoverRate;
        int n; // Number of individuals for the tournament selection
    public:
        Genetic(int population, int lowerBound, int upperBound, int x, int mutationRate, int crossoverRate, int n);
        void generate_population();
};
Genetic::Genetic(int populationSize, int lowerBound, int upperBound, int x, int mutationRate, int crossoverRate, int n){
    this->populationSize = populationSize;
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;
    this->x = x;
    this->mutationRate = mutationRate;
    this->crossoverRate = crossoverRate;
    this->n = n;

    generate_population();
}

void Genetic::generate_population(){
    srand((unsigned) time(NULL));
    for(int i = 0; i < populationSize; i++){
        int random = rand() % (upperBound+lowerBound) - lowerBound;
        population.push_back(random);
    }
}

string int_to_binary(int num){

}

int main(){


    return 0;
}