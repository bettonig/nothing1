#include "neuron.h"
#include <cmath>
#include <vector>
//using namespace std;

//Constructor & Destructor::
Neuron::Neuron ()
:membrane_potential_(0.0), nb_spks_(0), time_spks_()
{time_spks_.push_back(0);}

Neuron::Neuron (double membrane_potential, unsigned int nb_spks, time_vector time_spks)
:membrane_potential_(membrane_potential), nb_spks_(nb_spks), time_spks_(time_spks)
{}

/*Neuron::Neuron (const Neuron& another)
:
{}*/

Neuron::~Neuron ()
{}



// Getters::
double Neuron::Get_membrane_potential () const
{return membrane_potential_;}

unsigned int Neuron::Get_nb_spks () const
{return nb_spks_;}

time_vector Neuron::Get_time_spks () const
{return time_spks_;}



//Setters::
void Neuron::Set_membrane_potential (double membrane_potential)
{membrane_potential_ = membrane_potential;}

void Neuron::Set_nb_spks (unsigned int nb_spks)
{nb_spks_ = nb_spks;}

void Neuron::Set_time_spks (time_vector time_spks)
{time_spks_ = time_spks;}



//Methods::
bool Neuron::Is_refractory(double time1)
{
	if(time1 - time_spks_.back() < refractory_time_)
	{
		return true;
	}
	return false;
}

void Neuron::Update_state(double time1, double dT, double Iex)
{
	if (Is_refractory(time1))
	{
		membrane_potential_ = 0.0;
	} else 
	{
		membrane_potential_ = exp(-(dT/tau_)) * membrane_potential_ + Iex * (tau_ / c_) * (1 - exp(-(dT/tau_)));
		if (membrane_potential_ >= threshold_)
		{
			//std::cout << nb_spks_ << std::endl;
			time_spks_.push_back(time1 + dT);
			nb_spks_ = nb_spks_ + 1;					
			//std::cout << "WOLOLO" << std::endl;
			
		};
	};
	//std::cout << nb_spks_ << std::endl;
}

