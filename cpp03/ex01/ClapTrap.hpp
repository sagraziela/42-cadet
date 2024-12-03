#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>
# include <string>

class ClapTrap
{
    protected:
        std::string _name;
        int         _hit = 100;
        int         _energy = 50;
        int         _attackDamage = 50;

    public:
        ClapTrap(std::string name);
        ClapTrap(void);
        ClapTrap(ClapTrap const &src);
		ClapTrap &operator=(ClapTrap const &src);
        ~ClapTrap(void);

        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
};

#endif