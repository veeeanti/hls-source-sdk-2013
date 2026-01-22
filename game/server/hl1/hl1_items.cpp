//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//


#include "cbase.h"
#include "player.h"
#include "items.h"
#include "gamerules.h"
#include "hl1_items.h"


void CHL1Item::Spawn( void )
{
	// Call base class spawn first to get all the CItem setup (physics, collision, etc.)
	BaseClass::Spawn();

	// Now apply HL1 specific overrides
	CBaseEntity* pBase = static_cast<CBaseEntity*>(this);
	pBase->SetMoveType( MOVETYPE_FLYGRAVITY );
	pBase->SetSolid( SOLID_BBOX );
	pBase->AddSolidFlags( FSOLID_NOT_STANDABLE | FSOLID_TRIGGER );
	pBase->CollisionProp()->UseTriggerBounds( true, 24.0f );
	
	pBase->SetCollisionGroup( COLLISION_GROUP_DEBRIS );

	pBase->SetTouch( static_cast<void (CBaseEntity::*)(CBaseEntity *)>(&CItem::ItemTouch) );

#ifdef HL1_DLL
    if ( g_pGameRules->IsMultiplayer() )
        pBase->AddEffects( EF_NOSHADOW );
#endif
}


void CHL1Item::Activate( void )
{
	BaseClass::Activate();

	if ( UTIL_DropToFloor( this, MASK_SOLID ) == 0 )
	{
		Warning( "Item %s fell out of level at %f,%f,%f\n", GetClassname(), GetAbsOrigin().x, GetAbsOrigin().y, GetAbsOrigin().z);
		UTIL_Remove( this );
		return;
	}
}
