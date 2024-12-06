#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include <iostream>
# include <string>
# include "./ClapTrap.hpp"
# include "./ScavTrap.hpp"
# include "./FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap
{
    private:
        std::string _name;

    public:
        DiamondTrap(void);
        DiamondTrap(std::string name);
        DiamondTrap(DiamondTrap const &src);
		DiamondTrap &operator=(DiamondTrap const &src);
        ~DiamondTrap(void);

        // using FragTrap::_hit;
	    // using ScavTrap::_energy;
	    // using FragTrap::_attackDamage;
        using ScavTrap::attack;

        void whoAmI(void);
};

#endif
