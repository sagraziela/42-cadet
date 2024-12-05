#include "./DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void) : ClapTrap("null_clap_name"), ScavTrap(), FragTrap()
{
	this->_name = "(null)";
	FragTrap::_hit = 100;
	ScavTrap::_energy = 50;
	FragTrap::_attackDamage = 30;
    std::cout << "Default DiamondTrap was created.\n";
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + std::string("_clap_name")), ScavTrap(name), FragTrap(name)
{
	this->_name = name;
    this->ClapTrap::_name = name + "_clap_name";
	FragTrap::_hit = 100;
	ScavTrap::_energy = 50;
	FragTrap::_attackDamage = 30;
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
        ClapTrap::operator=(src);
		this->_name = src._name;
		// this->FragTrap::_hit = src.FragTrap::_hit;
		// this->ScavTrap::_energy = src.ScavTrap::_energy;
		// this->FragTrap::_attackDamage = src.FragTrap::_attackDamage;
	}
	return *this;
}

DiamondTrap::~DiamondTrap(void)
{
    std::cout << this->_name << " DiamondTrap was destroyed.\n";
}

void DiamondTrap::whoAmI(void)
{
    std::cout << "I am " << this->_name << ", " << this->ClapTrap::_name << std::endl;

    std::cout << "HIT: " << this->_hit << " | ENERGY: " << this->_energy << " | ATTACK: " << this->_attackDamage << std::endl;
}