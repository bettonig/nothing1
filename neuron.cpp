#include "neuron.h"
#include <vector>
//#include <cmath>
//using namespace std;



//Constructor & Destructor::

Neuron::Neuron ()
:membrane_potential_(0.0), nb_spks_(0), time_spks_()
{
	time_spks_.push_back(0);
	for (size_t i(0); i <= delay + 1; ++i) 
	{
		delay_buffer.push_back(0);
	}
}

Neuron::Neuron (double membrane_potential, unsigned int nb_spks)
:membrane_potential_(membrane_potential), nb_spks_(nb_spks), time_spks_()
{
	time_spks_.push_back(0);
	for (size_t i(0); i <= delay + 1; ++i)
	{
		delay_buffer.push_back(0);
	}
}

/*Neuron::Neuron (const Neuron& another)
:
{}*/

Neuron::~Neuron ()
{/*std::cout << "NEURON TERMINATED" << std::endl;*/}



//----------------------------------------------------------------------



// Getters::

double Neuron::Get_membrane_potential () const
{return membrane_potential_;}

unsigned int Neuron::Get_nb_spks () const
{return nb_spks_;}

int_vector Neuron::Get_time_spks () const
{return time_spks_;}



//----------------------------------------------------------------------



//Setters::

void Neuron::Set_membrane_potential (double membrane_potential)
{membrane_potential_ = membrane_potential;}

void Neuron::Set_nb_spks (unsigned int nb_spks)
{nb_spks_ = nb_spks;}

void Neuron::Set_time_spks (int_vector time_spks)
{time_spks_ = time_spks;}



//----------------------------------------------------------------------



//Methods::

bool Neuron::Is_refractory(/*double dT*/)
{
	if (steps_intern_ >= 20 and steps_intern_ - time_spks_.back() < refractory_time_)
	{
		return true;
	}
	return false;
}


bool Neuron::Has_now_spiked (/*double dT*/)
{
	if (time_spks_.size() < 2)
	{
		return false;
	} 
	else 
	{
		if (steps_intern_ == time_spks_.back())
		{
			//std::cout << "WOLOLO" << std::endl;
			return true;
		} else {
			return false;
		};
	};
}


void Neuron::Update_state(double Iext2, int poisson)
{
	if (Is_refractory(/*dT*/))
	{
		membrane_potential_ = 0.0;
	} else {
		membrane_potential_ = Exp_ * membrane_potential_ + Iext2 * c2 * (1 - Exp_) + ((delay_buffer[(steps_intern_ + delay) % (delay + 1)] + poisson) * J_) ;
		delay_buffer[(steps_intern_ + delay) % (delay + 1)] = 0;
		if (membrane_potential_ >= threshold_)
		{
			//std::cout << nb_spks_ << std::endl;
			time_spks_.push_back(steps_intern_ + 1);
			nb_spks_ = nb_spks_ + 1;								
		};
	};
	steps_intern_ += 1;
	//std::cout << nb_spks_ << std::endl;
}


void Neuron::Send_spike(Neuron& neuron, int step, bool is_Inhib)
{
	neuron.Store_spike(step, is_Inhib);
	//std::cout<<"spike send"<<std::endl;
}


void Neuron::Store_spike(int step, bool is_Inhib)
{
	int modulo = (step + delay) % (delay + 1);
	if (is_Inhib) {
		delay_buffer[modulo] -= 5;
		//std::cout<<"  inhib"<<std::endl;
	} else {
		delay_buffer[modulo] += 1;
		//std::cout<<"excit"<<std::endl;
	};
}


