#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include <iostream>
# include <string>
# include "./ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap
{
    public:
        ScavTrap(std::string name);
        ScavTrap(void);
        ScavTrap(ScavTrap const &src);
		ScavTrap &operator=(ScavTrap const &src);
        ~ScavTrap(void);

        void attack(const std::string& target);
        void guardGate();
};

#endif
