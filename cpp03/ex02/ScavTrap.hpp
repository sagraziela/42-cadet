#ifndef E6CC8B1A_2963_4F42_A637_5595AD651D1E
#define E6CC8B1A_2963_4F42_A637_5595AD651D1E
#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include <iostream>
# include <string>
# include "./ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
    public:
        ScavTrap(std::string name);
        ScavTrap(void);
        ScavTrap(ScavTrap const &src);
		ScavTrap &operator=(ScavTrap const &src);
        ~ScavTrap(void);

        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
        void guardGate();
};

#endif


#endif /* E6CC8B1A_2963_4F42_A637_5595AD651D1E */
