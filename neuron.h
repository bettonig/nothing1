#include <iostream>
#include <vector>
//using namespace std;

#ifndef NEURON_H
#define NEURON_H

//typedef std::vector<int> time_vector;
typedef std::vector<int> int_vector;


class Neuron {
	
	private:
		
		double membrane_potential_;
		unsigned int nb_spks_;											//spks is short for "spikes" of a neuron
		int_vector time_spks_;	
		//bool exhib;
		
		int steps_intern_;
		int_vector delay_buffer;
		
		
		unsigned int const delay = 15;									// !!!ask
		static constexpr double tau_ = 20;
		static constexpr double threshold_ = 20;
		static constexpr double c_ = 1.0;
		static constexpr double J_ = 1.0; //0.1
		const int refractory_time_ = 20;
		
		
	public:
		
		//Constructor & Destructor
		Neuron ();
		Neuron (double membrane_potential, unsigned int nb_spks);
		/*Neuron (const Neuron& another);*/
		~Neuron ();

	//----------------------------------------------------------------------
		
		//Getters
		double Get_membrane_potential () const;
		unsigned int Get_nb_spks () const;
		int_vector Get_time_spks () const;
		
	//----------------------------------------------------------------------		
		
		//Setters
		void Set_membrane_potential (double membrane_potential);
		void Set_nb_spks (unsigned int nb_spks);
		void Set_time_spks (int_vector time_spks);
		
	//----------------------------------------------------------------------
		
		//Methods
		bool Is_refractory (/*double dT*/);
		bool Has_now_spiked (/*double dT*/);
		
		void Update_state (double dT, double Iext2);								// dT = n * h
		void Send_spike(Neuron& neuron, int step, bool Is_inhib);
		void Store_spike(int step, bool is_Inhib);
		
};

#endif
