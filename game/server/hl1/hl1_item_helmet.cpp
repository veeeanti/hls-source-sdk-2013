//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Handling for the helmet item.
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "player.h"
#include "basecombatweapon.h"
#include "gamerules.h"
#include "items.h"
#include "engine/IEngineSound.h"
#include "hl1_items.h"


#define HELMET_MODEL "models/w_helmet.mdl"

ConVar	sk_helmet( "sk_helmet","10" );	

class CItemHelmet : public CHL1Item
{
public:
	DECLARE_CLASS( CItemHelmet, CHL1Item );

	void Spawn( void )
	{ 
		Precache( );
		BaseClass::SetModel( HELMET_MODEL );
		BaseClass::Spawn( );
	}
	void Precache( void )
	{
		BaseClass::PrecacheModel( HELMET_MODEL );

		BaseClass::PrecacheScriptSound( "Item.Pickup" );
	}

	bool MyTouch( CBasePlayer *pPlayer )
	{
		if (pPlayer->ArmorValue() < MAX_NORMAL_BATTERY)
		{
			CPASAttenuationFilter filter( pPlayer, "Item.Pickup" );
			BaseClass::EmitSound( filter, BaseClass::entindex(), "Item.Pickup" );

			pPlayer->IncrementArmorValue( sk_helmet.GetFloat(), MAX_NORMAL_BATTERY );
			return true;		
		}
		return false;
	}
};

LINK_ENTITY_TO_CLASS(item_helmet, CItemHelmet);
PRECACHE_REGISTER(item_helmet);
