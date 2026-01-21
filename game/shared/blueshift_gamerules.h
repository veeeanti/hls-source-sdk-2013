//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Blue Shift game rules
//
// $NoKeywords: $
//=============================================================================//

#ifndef BLUESHIFT_GAMERULES_H
#define BLUESHIFT_GAMERULES_H
#pragma once

#include "hl1_gamerules.h"

#ifdef CLIENT_DLL
	#define CBlueShiftGameRules C_BlueShiftGameRules
	#define CBlueShiftGameRulesProxy C_BlueShiftGameRulesProxy
#endif

class CBlueShiftGameRulesProxy : public CHL1GameRulesProxy
{
public:
	DECLARE_CLASS( CBlueShiftGameRulesProxy, CHL1GameRulesProxy );
	DECLARE_NETWORKCLASS();
};

class CBlueShiftGameRules : public CHL1GameRules
{
public:
	DECLARE_CLASS( CBlueShiftGameRules, CHL1GameRules );

#ifdef CLIENT_DLL
	DECLARE_CLIENTCLASS_NOBASE(); // This makes datatables able to access our private vars.
#else
	DECLARE_SERVERCLASS_NOBASE(); // This makes datatables able to access our private vars.
#endif

	CBlueShiftGameRules();
	virtual ~CBlueShiftGameRules();

#ifdef CLIENT_DLL

	virtual void OnDataChanged( DataUpdateType_t updateType );
	virtual const char *GetGameTypeName( void ) { return "Blue Shift"; }

#else

	virtual void Think( void );
	virtual void PlayerSpawn( CBasePlayer *pPlayer );
	virtual void InitDefaultAIRelationships( void );
	virtual const char *GetGameDescription( void ) { return "Half-Life: Blue Shift"; }

	// Blue Shift specific game rules
	virtual bool ShouldCollide( int collisionGroup0, int collisionGroup1 );
	virtual void PlayerThink( CBasePlayer *pPlayer );

#endif
};

#endif // BLUESHIFT_GAMERULES_H