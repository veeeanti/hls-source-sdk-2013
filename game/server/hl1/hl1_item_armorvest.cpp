//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Handling for the armor vest item.
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


#define ARMORVEST_MODEL "models/w_armorvest.mdl"

ConVar	sk_armorvest( "sk_armorvest","20" );	

class CItemArmorVest : public CHL1Item
{
public:
	DECLARE_CLASS( CItemArmorVest, CHL1Item );

	void Spawn( void )
	{ 
		Precache( );
		BaseClass::SetModel( ARMORVEST_MODEL );
		BaseClass::Spawn( );
	}
	void Precache( void )
	{
		BaseClass::PrecacheModel( ARMORVEST_MODEL );

		BaseClass::PrecacheScriptSound( "Item.Pickup" );
	}

	bool MyTouch( CBasePlayer *pPlayer )
	{
		if (pPlayer->ArmorValue() < MAX_NORMAL_BATTERY)
		{
			CPASAttenuationFilter filter( pPlayer, "Item.Pickup" );
			BaseClass::EmitSound( filter, BaseClass::entindex(), "Item.Pickup" );

			pPlayer->IncrementArmorValue( sk_armorvest.GetFloat(), MAX_NORMAL_BATTERY );
			return true;		
		}
		return false;
	}
};

LINK_ENTITY_TO_CLASS(item_armorvest, CItemArmorVest);
PRECACHE_REGISTER(item_armorvest);
