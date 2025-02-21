#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>
# include <string>

class ClapTrap
{
    private:
        std::string _name;
        int         _hit = 100;
        int         _energy = 50;
        int         _attackDamage = 20;

    public:
        ClapTrap(std::string name);
        ClapTrap(void);
        ClapTrap(ClapTrap const &copy);
        ClapTrap &operator = (ClapTrap const &copy);
        ~ClapTrap(void);
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
};

#endif