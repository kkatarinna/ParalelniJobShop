////
//// Created by Katarina Krstin on 3.6.23..
////

#include "Chromosome.h"
#include <vector>
#include <map>
#include <random>
#include <string>

Chromosome::Chromosome(std::map<std::string, int> jobs, std::map<std::string, std::map<std::string, std::vector<int>>> machines, std::vector<std::vector<std::string>> chromosome)

{
        if (chromosome.size() == 0) {
            this->chromosome = generate_chromosome(jobs, machines);
        } else {
            this->chromosome = chromosome;
        }
    }
std::string Chromosome::to_string() {
    std::string str = "iz klase : ";
    for (int i = 0; i < this->chromosome.size(); i++) {
        for (int j = 0; j < this->chromosome[i].size(); j++) {
            str += this->chromosome[i][j] + " ";
        }
    }
    return str;
}


    std::vector<std::vector<std::string>> Chromosome::generate_chromosome(std::map<std::string, int> jobs_dict, std::map<std::string, std::map<std::string, std::vector<int>>> machines_dict) {
        std::vector<std::string> job_slot;
        std::vector<std::string> machine_slot;

        std::map<std::string, int> all_jobs_occurance_counter;
        for (auto const& job : jobs_dict) {
            all_jobs_occurance_counter.insert({job.first, 0});
        }
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dis(0, jobs_dict.size()-1);

        while (true) {
            int choice = dis(gen);
            auto it = std::next(std::begin(jobs_dict), choice);
            if (all_jobs_occurance_counter[it->first] < it->second) { //!!!!! mozda nece raditi
                all_jobs_occurance_counter[it->first] += 1;
                job_slot.push_back(it->first);
            }
            if (job_slot.size() == jobs_dict.size()) {
                break;
            }
        }

        std::vector<std::vector<std::string>> chromosome;
        chromosome.push_back(job_slot);
        chromosome.push_back(machine_slot);
        return chromosome;
    }



