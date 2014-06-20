#ifndef PLAYERMODE_H
#define PLAYERMODE_H

enum class PlayerMode//used to determine what privileges the player should have
{
    Normal = 0,
    God,
};

enum class PlayerState//used to determine how player commands should be interpreted
{
    Playing = 0,
    Interfacing,
    Editing,
};

#endif // PLAYERMODE_H
