#include "stdafx.h"
#include "windmill.h"
#include "player.h"

void windmill::EnterState()
{
    _pl->getIndex() = 0;
    _pl->getAttack()->Attack(_pl->getGroundRc().right, _pl->getGroundRc().top - 50);
    _pl->getAttack()->Attack(_pl->getGroundRc().left - 150, _pl->getGroundRc().top - 50);
}

void windmill::updateState()
{
}

void windmill::ExitState()
{
}
