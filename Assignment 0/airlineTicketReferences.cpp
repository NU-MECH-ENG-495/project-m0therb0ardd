#include <string>
#include <iostream>

using namespace std;

//KEY CONCEPTS OF THIS CODE: 
//  - clases and objects : the airlineTicket class represents an airline ticket and its associated data and behavior 
//  - constructor: initialized object state 
//  - getters and setter: these methods are used to get and set the values of an objects private data members
//  - member functions: functions that define the behavior of the object 

//CHANGES TO MAKE: 
// const and & for std::string (references)
// for setter methods like setPassengerName use a reference (const std::str&) for the strign parameter to avoid unnecessary copies
// for getter methods like getPassengerName return const std::string& so that the string isnt copied and caller cannot mopify it  


// const = methods marked as const tell compiler and reader that these methods dont modify the internal state of the object --> important for methods that only "read" data
// references = passing large objects liek std:: string by reference instead of by value avoids copying 


// used chatgpt to walk through the concepts of this --> idea of const was new to me but makes sense 


class AirlineTicket
{
public: // public methods can be accessed from outside the class (like in main)
	AirlineTicket(); // constructor --> special method when object of class is created --> initializes objects data members to default values
	~AirlineTicket(); //destructor --> method called when object goes out of scope 
	

	double calculatePriceInDollars() const; //marked as constant bc it doesnt modify th eobject 
	
	const std::string getPassengerName() const; // return const 

	void setPassengerName(const std::string& name); // pass by reference to avoid copying 

	int getNumberOfMiles() const; // marked as const bc it doenst modify the object 

	void setNumberOfMiles(int miles); //setter method 
	
	bool hasEliteSuperRewardsStatus() const; // doesnt modify obejct 

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

double AirlineTicket::calculatePriceInDollars() const //marked as const
{
	if (hasEliteSuperRewardsStatus()) {
		// Elite Super Rewards customers fly for free!
		return 0;
	}

	// The cost of the ticket is the number of miles times 0.1.
	// Real airlines probably have a more complicated formula!
	return getNumberOfMiles() * 0.1;
}

const std::string AirlineTicket::getPassengerName() const // return const referenc e
{
	return m_passengerName;
}

void AirlineTicket::setPassengerName(const std::string name) // use reference to avoid copying 
{
	m_passengerName = name;
}

int AirlineTicket::getNumberOfMiles() const // doesnt modify object 
{
	return m_numberOfMiles;
}

void AirlineTicket::setNumberOfMiles(int miles)
{
	m_numberOfMiles = miles;
}

bool AirlineTicket::hasEliteSuperRewardsStatus() const
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


