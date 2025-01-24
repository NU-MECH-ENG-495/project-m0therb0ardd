#include <string>
#include <iostream>

using namespace std;

//KEY CONCEPTS OF THIS CODE: 
//  - clases and objects : the airlineTicket class represents an airline ticket and its associated data and behavior 
//  - constructor: initialized object state 
//  - getters and setter: these methods are used to get and set the values of an objects private data members
//  - member functions: functions that define the behavior of the object 


class AirlineTicket
{
public: // public methods can be accessed from outside the class (like in main)
	AirlineTicket(); // constructor --> special method when object of class is created --> initializes objects data members to default values
	~AirlineTicket(); //destructor --> method called when object goes out of scope 
	

	double calculatePriceInDollars(); //method
	
	std::string getPassengerName(); // getter method 
	void setPassengerName(std::string name); // setter method 

	int getNumberOfMiles(); //getter method 
	void setNumberOfMiles(int miles); //setter method 
	
	bool hasEliteSuperRewardsStatus(); // getter method
	void setHasEliteSuperRewardsStatus(bool status); //setter netgid 

private: // data members of the class the can only be seen in the class 
 
	std::string m_passengerName{ "Unknown Passenger" }; // string variable
	int m_numberOfMiles{ 0 }; // int variable
	bool m_hasEliteSuperRewardsStatus{ false }; // boolean variable 
};


// member function defintions --> define behavior of airline ticket class 
AirlineTicket::AirlineTicket()
	: m_passengerName{ "Unknown Passenger" }
	, m_numberOfMiles{ 0 }
	, m_hasEliteSuperRewardsStatus{ false }
{
}

AirlineTicket::~AirlineTicket()
{
	// Nothing to do in terms of cleanup
}

// :: scope resolution operator used to define function outside the class 
// this means calculatePriceInDollars is a member function of the airlineTicket class

double AirlineTicket::calculatePriceInDollars() 
{
	if (hasEliteSuperRewardsStatus()) {
		// Elite Super Rewards customers fly for free!
		return 0;
	}

	// The cost of the ticket is the number of miles times 0.1.
	// Real airlines probably have a more complicated formula!
	return getNumberOfMiles() * 0.1;
}

std::string AirlineTicket::getPassengerName()
{
	return m_passengerName;
}

void AirlineTicket::setPassengerName(std::string name)
{
	m_passengerName = name;
}

int AirlineTicket::getNumberOfMiles()
{
	return m_numberOfMiles;
}

void AirlineTicket::setNumberOfMiles(int miles)
{
	m_numberOfMiles = miles;
}

bool AirlineTicket::hasEliteSuperRewardsStatus()
{
	return m_hasEliteSuperRewardsStatus;
}

void AirlineTicket::setHasEliteSuperRewardsStatus(bool status)
{
	m_hasEliteSuperRewardsStatus = status;
}




int main()
{
	AirlineTicket myTicket;  // Stack-based AirlineTicket
	myTicket.setPassengerName("Sherman T. Socketwrench");
	myTicket.setNumberOfMiles(700);
	double cost{ myTicket.calculatePriceInDollars() };
	cout << "This ticket will cost $" << cost << endl;
} 


