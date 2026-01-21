//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Blue Shift player entity
//
// $NoKeywords: $
//=============================================================================//

#ifndef BLUESHIFT_PLAYER_H
#define BLUESHIFT_PLAYER_H
#pragma once

#include "hl1_player.h"

//-----------------------------------------------------------------------------
// Purpose: Blue Shift player class
//-----------------------------------------------------------------------------
class CBlueShift_Player : public CHL1_Player
{
public:
	DECLARE_CLASS( CBlueShift_Player, CHL1_Player );
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

	CBlueShift_Player();
	~CBlueShift_Player();

	virtual void Precache( void );
	virtual void Spawn( void );

	// Blue Shift specific functionality
	virtual void SetupPlayerSounds( void );
	virtual void PlayerDeathThink( void );

	// Barney-specific interactions
	virtual bool HandleInteraction(int interactionType, void *data, CBaseCombatCharacter* sourceEnt);

private:
	// Barney-specific variables
	bool m_bSecurityGuardMode;
};

#endif // BLUESHIFT_PLAYER_H