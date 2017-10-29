#include "neuron.h"
#include <iostream>
#include <climits>
#include <fstream>
#include <string>
#include <array>
#include <random>
//#include <iomanip>
//using namespace std;

//void write_membrane_pot (string file_out_, double membrane_pot);


int main()
{

	/*const*/int stop_time(2000);
	int start_step(0);
	int stop_step(0);
	int nb_step(0);
	const double h(0.1); //ms											// interval
	
	double Iext(0.0);		//pA
	double Iext2(0.0);		//pA										// Current 
	
	/*
	int control(0);
	
	
	while (control <= 0 or control > 25000) {
		std::cout << "Please inserteth the number of neurons to simulate :" << std::endl;
		std::cin >> control;
		if (std::cin.fail()) {
			std::cout << "I'm afraid i can't do that Dave!2" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	}
	*/
	constexpr int nb_neurons(10); //12500
	
	constexpr int nb_exhit(4*nb_neurons/5); //10000							nb of exitatory Neurons
	constexpr int nb_inhib(1*nb_neurons/5); //2500							nb of inhibitory Neurons
	
	constexpr int exhit_conn(nb_exhit/2); //1000							nb 
	constexpr int inhib_conn(nb_inhib/2); //250
	constexpr int conn_tot(exhit_conn + inhib_conn); //1250					each neurons is connected to 1 every 10 neurons
		
		
	std::array<std::array<int, conn_tot>, nb_neurons> neurons_targets;
	std::array<Neuron, nb_neurons> neurons_;


	
	while (start_step <= 0 or start_step >= stop_time) {											// This loop is to make sure the person using this program
		std::cout << "Please inserteth the beginnig step (>0 & <2000) :" << std::endl;				// enters a number above 0.
		std::cin >> start_step;
		if (std::cin.fail() or start_step >= stop_time) {
			std::cout << "I'm afraid i can't do that Dave!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	};
	
	
	while (stop_step <= 0 or stop_step < start_step or stop_step > stop_time) {											// This loop is to make sure the person using this program
		std::cout << "Please inserteth the stopping step (>beginning step & <=200) :" << std::endl;				// enters a number above 0.
		std::cin >> stop_step;
		if (std::cin.fail() or stop_step < start_step or stop_step > stop_time) {
			std::cout << "I'm afraid i can't do that Dave!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	};
		
		
	while (Iext <= 0.0) {
		std::cout << "Please inserteth the current :" << std::endl;
		std::cin >> Iext;
		if (std::cin.fail()) {
			std::cout << "I'm afraid i can't do that Dave!2" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	};
	
	
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> random_exhit(0, nb_exhit-1);
	std::uniform_int_distribution<> random_inhib(nb_exhit, nb_neurons-1);
	
	
	for (size_t i(0); i < nb_neurons; ++i) {
		for(size_t j(0); j < conn_tot; ++j) {
			if (j < exhit_conn) {
				neurons_targets[i][j] = random_exhit(gen);
			} else {
				neurons_targets[i][j] = random_inhib(gen);
			}
		}
	}





	//int spiked_conn(0);
	
	/*std::vector<Neuron> neurons_;
	Neuron unique;
	neurons_.push_back(unique);
	Neuron second(7.0, 0);
	neurons_.push_back(second);*/
	
	std::ofstream Neurons_mem_pot;
	Neurons_mem_pot.open("potentials.txt");
	
	while (nb_step < stop_time) 
	{
		if (nb_step < start_step or nb_step > stop_step) 
		{
			Iext2 = 0.0;
		} 
		else 
		{ 
			Iext2 = Iext; 
		}
		
		for (size_t i(0); i < neurons_.size(); ++i) {								
			
			if (neurons_[i].Has_now_spiked(/*h*/) and i < (neurons_.size() - 1)) 
			{
				for (size_t j(0); j < conn_tot; ++j) {
					
					bool is_Inhib(false);
					
					if (i < nb_exhit) {
						is_Inhib = false;
					} else {
						is_Inhib = true;
					}
					
					neurons_[i].Send_spike(neurons_[neurons_targets[i][j]], nb_step, is_Inhib);
				}
			}
			neurons_[i].Update_state(h, Iext2);
			Neurons_mem_pot << neurons_[i].Get_membrane_potential() << '\t';
			//std::cout << "at step " << nb_step << " : " << neurons_[i].Get_membrane_potential() << " mV" << '\t';
			};
		//std::cout << std::endl;
		Neurons_mem_pot << std::endl;
		//std::cout << std::endl;
		++nb_step;
	};

	Neurons_mem_pot.close();
	
	
	
	
	
	
	
	return 0;
}

