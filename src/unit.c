#include "Outil.h"

#define N 11
#define NB_MAX_EFFECT

bool canGetPassed(unit * target)
{
    bool out=true;
    for(int i=0;i<NB_MAX_EFFECT;i++)
    {
        if(target-> effect[i]>2)
        {
            out=false;
        }
    }
    return out;
}

bool canBlock(unit * target)
{
    bool out=true;
        for(int i=0;i<NB_MAX_EFFECT;i++)
    {
        if(target-> effect[i]>4)
        {
            out=false;
        }
    }
    return out;
}
bool canAttack(unit * target)
{
    bool out=true;
        for(int i=0;i<NB_MAX_EFFECT;i++)
    {
        if(target-> effect[i]>3 && target-> effect[i]<6)
        {
            out=false;
        }
    }
    return out;
}

bool canMove(unit * target)
{
    bool out=true;
        for(int i=0;i<NB_MAX_EFFECT;i++)
    {
        if(target-> effect[i]==5)
        {
            out=false;
        }
    }
    return out;
}

int getSideAttacked()
{

}

void heal(unit* source, unit* target)
{//soigne
    target->stat->HP += source->stat->POWER;
}

bool attack(unit* source, unit* target)
{
    if(canAttack(source))
    {
        if(canBlock(target))
        {
            target->stat->HP-=(source->stat->POWER*target->stat->BLOCK[getSideAttacked(source,target)]);
        }
        else
        {
            target->stat->HP-=source->stat->POWER;
        }

    }
}

void move(unit grille[N][N],unit * source)

void moduleAmorcer()
{

}

int main()
{
    moduleAmorcer();
    return 0;
}
