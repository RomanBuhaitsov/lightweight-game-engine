#include "component.h"

GameWindow *Component::GAME = NULL;

void Component::update()
{
}

json Component::to_json()
{
    return json();
}

void Component::onNotify(const Message & message)
{
}