#ifndef ZONEDISPLAYZONE_H
#define ZONEDISPLAYZONE_H

#include <vector>

#include <SDL/SDL.h>

#include "StaticArea.h"
#include "Player.h"
#include "TileDisplayZone.h"

#include <iostream> // debug

class ZoneDisplayZone
{
public:
    ZoneDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop);
    virtual ~ZoneDisplayZone();

    typedef std::vector<std::string> ZoneSetLine;
    typedef std::vector<ZoneSetLoader::ZoneSetLine> ZoneSet;

    void render(SDL_Surface* screen, const StaticArea* area, std::vector<Player> players, SDL_Rect const offset = {0,0,0,0}) const;
protected:
private:
    SDL_Rect m_displayPos;
};

#endif // ZONEDISPLAYZONE_H
