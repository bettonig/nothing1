#include "neuron.cpp"
#include <iostream>
#include <climits>
#include <fstream>
#include <string>
//#include <iomanip>
//using namespace std;

//void write_membrane_pot (string file_out_, double membrane_pot);

int main()
{
	
	/*string file_out_;
	cout << "How would thee calleth thy file? " << endl;
	cin >> file_out_;*/	

	
	//int start_time(0);
	/*const*/int stop_time(200);
	int start_step(0);
	int stop_step(0);
	int nb_step(0);
	const double h(0.2);											// interval
	//double time(start_time);
	
	double Iext(0.0);
	double Iext2(0.0);												// Current 

	
	while (start_step <= 0) {											// This loop is to make sure the person using this program
		std::cout << "Please inserteth the beginnig step (>0) :" << std::endl;				// enters a number above 0.
		std::cin >> start_step;
		if (std::cin.fail()) {
			std::cout << "I'm afraid i can't do that Dave!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	};
	
	while (stop_step <= 0) {											// This loop is to make sure the person using this program
		std::cout << "Please inserteth the stopping step (>0 & >beginning stop) :" << std::endl;				// enters a number above 0.
		std::cin >> stop_step;
		if (std::cin.fail() or stop_step < start_step) {
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
	
	
	std::vector<Neuron> neurons_;
	Neuron unique;
	neurons_.push_back(unique);
	
	std::ofstream Neuron_mem_pot;
	Neuron_mem_pot.open("potentials.txt");
	
	//for (int i(time), i < stop_time, i + h) {
	while (nb_step < stop_time) {
		if (nb_step < start_step or nb_step > stop_step) 
		{
			Iext2 = 0.0;
			//std::cout << "WADDDDUUUUUUUUUUUUUUUUUPPPPPPPPPPPP" << std::endl;
		} else 
		{ 
			Iext2 = Iext; 
		}
		for (size_t i(0); i < neurons_.size(); ++i) {								/* At first i used a for(auto x : y) loop but it reseted   
			//write_membrane_pot(file_out_, neuron.Get_membrane_potential());			The membrane_potential to 0 for unknown reasons */
			neurons_[i].Update_state( nb_step * h, h, Iext2);
			Neuron_mem_pot << neurons_[i].Get_membrane_potential() << std::endl;
			std::cout << neurons_[i].Get_membrane_potential() << std::endl;
		};
		++nb_step;
	};
	//};
	
	Neuron_mem_pot.close();
	
	
	return 0;
}






/*
void write_membrane_pot (string file_out_, double membrane_pot)
{
	ofstream output(file_out_.c_str);
	
	output << membrane_pot << " , ";
	
	output.close();
}
*/
