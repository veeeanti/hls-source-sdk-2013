//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Blue Shift player entity implementation
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "blueshift_player.h"
#include "gamerules.h"
#include "trains.h"
#include "vcollide_parse.h"
#include "in_buttons.h"
#include "igamemovement.h"
#include "ai_hull.h"
#include "hl2_shareddefs.h"
#include "info_camera_link.h"
#include "Point_Camera.h"
#include "ndebugoverlay.h"
#include "globals.h"
#include "ai_interactions.h"
#include "engine/IEngineSound.h"
#include "vphysics/player_controller.h"
#include "vphysics/constraints.h"
#include "predicted_viewmodel.h"
#include "physics_saverestore.h"
#include "gamestats.h"

LINK_ENTITY_TO_CLASS( player, CBlueShift_Player );
PRECACHE_REGISTER(player);

BEGIN_DATADESC( CBlueShift_Player )
	DEFINE_FIELD( m_bSecurityGuardMode, FIELD_BOOLEAN ),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST( CBlueShift_Player, DT_BlueShiftPlayer )
	SendPropBool( SENDINFO( m_bSecurityGuardMode ) ),
END_SEND_TABLE()

CBlueShift_Player::CBlueShift_Player()
{
	m_bSecurityGuardMode = true;
}

CBlueShift_Player::~CBlueShift_Player()
{
}

void CBlueShift_Player::Precache( void )
{
	BaseClass::Precache();

	// Barney-specific sounds
	PrecacheScriptSound( "Barney.Pain" );
	PrecacheScriptSound( "Barney.Die" );
	PrecacheScriptSound( "Barney.Idle" );
	PrecacheScriptSound( "Barney.Alert" );
	PrecacheScriptSound( "Barney.Follow" );
	PrecacheScriptSound( "Barney.Wait" );
	PrecacheScriptSound( "Barney.Stop" );
	PrecacheScriptSound( "Barney.Yes" );
	PrecacheScriptSound( "Barney.No" );
	PrecacheScriptSound( "Barney.Hello" );
}

void CBlueShift_Player::Spawn(void)
{
	// Set Barney model
	SetModel( "models/barney.mdl" );

	BaseClass::Spawn();

	// Blue Shift specific spawn setup
	SetMaxSpeed( 270 ); // Barney is slightly slower than Gordon

	// Give Barney his starting equipment
	GiveNamedItem( "weapon_crowbar" );
	GiveNamedItem( "weapon_glock" );
	GiveNamedItem( "ammo_9mmclip" );
	GiveNamedItem( "item_suit" );
	GiveNamedItem( "item_battery" );

	// Barney starts with security guard mode
	m_bSecurityGuardMode = true;
}

void CBlueShift_Player::SetupPlayerSounds( void )
{
	// Barney-specific sound replacements
	m_flTimePlayPain = gpGlobals->curtime;
}

void CBlueShift_Player::PlayerDeathThink( void )
{
	BaseClass::PlayerDeathThink();

	// Barney-specific death behavior
	if ( m_lifeState == LIFE_DEAD )
	{
		// Play Barney death sound
		EmitSound( "Barney.Die" );
	}
}

bool CBlueShift_Player::HandleInteraction(int interactionType, void *data, CBaseCombatCharacter* sourceEnt)
{
	// Barney has different interactions than Gordon
	if ( interactionType == g_interactionBarnacleVictimDangle )
	{
		// Barney might react differently to being grabbed by barnacles
		TakeDamage ( CTakeDamageInfo( sourceEnt, sourceEnt, m_iHealth + ArmorValue(), DMG_SLASH | DMG_ALWAYSGIB ) );
		return true;
	}

	return BaseClass::HandleInteraction(interactionType, data, sourceEnt);
}