#include "ZoneDisplayZone.h"

ZoneDisplayZone::ZoneDisplayZone(Sint16 const displayZoneLeft, Sint16 const displayZoneTop)
{
    m_displayPos = {displayZoneLeft, displayZoneTop};
}

ZoneDisplayZone::~ZoneDisplayZone()
{
    //dtor
}

void ZoneDisplayZone::render(SDL_Surface* screen, const StaticArea* area, std::vector<Player> players, SDL_Rect const offset) const
{
    SDL_Rect refDisplayPos = m_displayPos;
    refDisplayPos.x += offset.x;
    refDisplayPos.y += offset.y;
    SDL_Rect displayPos = refDisplayPos;
    SDL_Rect tileSetSize;
    Uint16 maxHeight = 0;

    for (ZoneSetLoader::ZoneSet::const_iterator zYit = area->getZoneSet().cbegin(); area->getZoneSet().cend() != zYit; ++zYit)
    {
        for (ZoneSetLoader::ZoneSetLine::const_iterator zXit = zYit->cbegin(); zYit->cend() != zXit; ++zXit)
        {
            TileDisplayZone tileDisplayZone(displayPos.x, displayPos.y);
            tileSetSize = tileDisplayZone.render(screen, area->getZone(*zXit));

            for (std::vector<Player>::const_iterator player = players.cbegin(); players.cend() != player; ++player)
            {
                if ((player->m_area == area->getKey()) && (area->getZoneSet()[player->m_zone.y][player->m_zone.x] == *zXit))
                {
                    /** @todo Temporary */
                    tileDisplayZone.render(screen, player->m_tile, TileSetLoader::TILE_PARTY);
                }
            }

            displayPos.x += tileSetSize.w;
            (tileSetSize.h <= maxHeight) || (maxHeight = tileSetSize.h);
        }
        displayPos.x = refDisplayPos.x;
        displayPos.y += maxHeight;
        maxHeight = 0;
    }
}
