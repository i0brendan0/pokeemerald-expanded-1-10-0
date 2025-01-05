#ifndef GUARD_POKEDEX_H
#define GUARD_POKEDEX_H

extern u8 gUnusedPokedexU8;
extern void (*gPokedexVBlankCB)(void);

void ResetPokedex(void);
u16 GetNationalPokedexCount(u8);
u16 GetHoennPokedexCount(u8);
u8 DisplayCaughtMonDexPage(u16 species, bool32 isShiny, u32 personality);
s8 GetSetPokedexFlag(u16 nationalNum, u8 caseId);
void DrawFootprint(u8 windowId, u16 species);
u16 CreateMonSpriteFromNationalDexNumber(u16, s16, s16, u16);
bool16 HasAllHoennMons(void);
void ResetPokedexScrollPositions(void);
bool16 HasAllMons(void);
void CB2_OpenPokedex(void);
void PrintMonMeasurements(u16 species, u32 owned);
u8* ConvertMonHeightToString(u32 height);
u8* ConvertMonWeightToString(u32 weight);
bool16 HasAllKantoMons(void);
bool16 HasAllJohtoMons(void);
bool16 HasAllSinnohMons(void);
bool16 HasAllMonsIncludingMythicals(void);
bool16 HasSeenAllHoennMons(void);
bool16 HasSeenAllKantoMons(void);
bool16 HasSeenAllJohtoMons(void);
bool16 HasSeenAllSinnohMons(void);
bool16 HasSeenAllMons(void);
bool16 HasSeenAllMonsIncludingMythicals(void);

#endif // GUARD_POKEDEX_H
