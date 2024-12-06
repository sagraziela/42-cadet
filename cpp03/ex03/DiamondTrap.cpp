#include "./DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void) : ClapTrap(), ScavTrap(), FragTrap()
{
	this->_name = "(null)";
	this->_hit = FragTrap::_hit;
	this->_energy = ScavTrap::_energy;
	this->_attackDamage = FragTrap::_attackDamage;
	this->ClapTrap::_name = "null_clap_name";
    std::cout << "Default DiamondTrap was created.\n";
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(), ScavTrap(), FragTrap()
{
	this->_name = name;
	this->_hit = 100;
	this->_energy = 50;
	this->_attackDamage = 30;
	this->ClapTrap::_name = name + std::string("_clap_name");
    std::cout << this->_name << " DiamondTrap was created.\n";
}

DiamondTrap::DiamondTrap(DiamondTrap const &src) : ClapTrap(src), ScavTrap(src), FragTrap(src)
{
	std::cout << "DiamondTrap copy constructor called.\n";
	*this = src;
}

DiamondTrap &DiamondTrap::operator=(DiamondTrap const &src)
{
	std::cout << "DiamondTrap copy assignment operator called.\n";
	if (this != &src)
	{
		this->_name = src._name;
		this->_name = src._name;
		this->_hit = src._hit;
		this->_energy = src._energy;
		this->_attackDamage = src._attackDamage;
	}
	return *this;
}

DiamondTrap::~DiamondTrap(void)
{
    std::cout << this->_name << " DiamondTrap was destroyed.\n";
}

void DiamondTrap::whoAmI(void)
{
    std::cout << "I am " << this->_name << "; ClapTrap NAME: " << this->ClapTrap::_name << std::endl;

    std::cout << "HIT: " << this->_hit << " | ENERGY: " << this->_energy << " | ATTACK: " << this->_attackDamage << std::endl;
}