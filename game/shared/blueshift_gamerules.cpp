//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Blue Shift game rules implementation
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "blueshift_gamerules.h"
#include "ammodef.h"
#include "viewport_panel_names.h"

#ifdef CLIENT_DLL
	#include "c_hl1mp_player.h"
#else
	#include "hl1_player.h"
	#include "blueshift_player.h"
#endif

REGISTER_GAMERULES_CLASS( CBlueShiftGameRules );

BEGIN_NETWORK_TABLE_NOBASE( CBlueShiftGameRules, DT_BlueShiftGameRules )
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( blueshift_gamerules, CBlueShiftGameRulesProxy );
IMPLEMENT_NETWORKCLASS_ALIASED( BlueShiftGameRulesProxy, DT_BlueShiftGameRulesProxy )

#ifdef CLIENT_DLL
	void CBlueShiftGameRules::OnDataChanged( DataUpdateType_t updateType )
	{
		BaseClass::OnDataChanged( updateType );
	}

	IMPLEMENT_CLIENTCLASS_DT( C_BlueShiftGameRules, DT_BlueShiftGameRules, CBlueShiftGameRules )
	END_RECV_TABLE()
#else
	void CBlueShiftGameRules::Think( void )
	{
		BaseClass::Think();
	}

	IMPLEMENT_SERVERCLASS_DT( CBlueShiftGameRules, DT_BlueShiftGameRules, CBlueShiftGameRules )
	END_SEND_TABLE()
#endif

CBlueShiftGameRules::CBlueShiftGameRules()
{
#ifdef CLIENT_DLL
#else
	// Blue Shift specific initialization
#endif
}

CBlueShiftGameRules::~CBlueShiftGameRules()
{
}

#ifndef CLIENT_DLL

void CBlueShiftGameRules::PlayerSpawn( CBasePlayer *pPlayer )
{
	BaseClass::PlayerSpawn( pPlayer );

	// Blue Shift specific player spawn logic
	CBlueShift_Player *pBlueShiftPlayer = dynamic_cast<CBlueShift_Player*>(pPlayer);
	if ( pBlueShiftPlayer )
	{
		// Set up Barney-specific spawn behavior
		pBlueShiftPlayer->SetMaxSpeed( 270 );
	}
}

void CBlueShiftGameRules::InitDefaultAIRelationships( void )
{
	BaseClass::InitDefaultAIRelationships();

	// Blue Shift specific AI relationships
	// Barney has different relationships with certain NPCs
}

bool CBlueShiftGameRules::ShouldCollide( int collisionGroup0, int collisionGroup1 )
{
	// Blue Shift specific collision rules
	return BaseClass::ShouldCollide( collisionGroup0, collisionGroup1 );
}

void CBlueShiftGameRules::PlayerThink( CBasePlayer *pPlayer )
{
	BaseClass::PlayerThink( pPlayer );

	// Blue Shift specific player thinking
	CBlueShift_Player *pBlueShiftPlayer = dynamic_cast<CBlueShift_Player*>(pPlayer);
	if ( pBlueShiftPlayer )
	{
		// Barney-specific thinking logic
	}
}

#endif