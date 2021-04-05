/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "main.h"

#define ID_NONE					- 1

#define ID_MENU_MAIN			0
#define ID_MENU_CHEATS			1
#define ID_MENU_CHEATS_INVULN	1
#define ID_MENU_CHEATS_MONEY	2
#define ID_MENU_CHEATS_MODS		135
#define ID_MENU_CHEATS_WEATHER	5
#define ID_MENU_CHEATS_TIME		6
#define ID_MENU_CHEATS_HANDLING 111
#define ID_MENU_PATCHES			7
#define ID_MENU_WEAPONS			8
#define ID_MENU_VEHICLES		9
#define ID_MENU_TELEPORTS		11
#define ID_MENU_MISC			12
#define ID_MENU_DEBUG			13
#define ID_MENU_PLAYERS			14
#define ID_MENU_PLAYERS_WARP	100
#define ID_MENU_PLAYERS_VEHWARP 101
#define ID_MENU_PLAYERS_SPEC	102
#define ID_MENU_PLAYERS_INFO	113
#define ID_MENU_PLAYERS_MUTE	114
#define ID_MENU_PLAYERS_VMUTE	115
#define ID_MENU_SAMPPATCHES		20
#define ID_MENU_SERVER_LIST		21
#define ID_MENU_HUDINDICATORS	22
#define ID_MENU_INTERIORS		23
// RapidFire's Attack Project defineleri //
#define ID_MENU_HILELER         24
#define ID_MENU_ARACHILELERI    25
#define	ID_MENU_WALLHACKLAR     26
#define ID_MENU_GORSEL_HILELER  27
#define ID_MENU_FLOODERLER		28
#define ID_MENU_TROLL_HILELER   29
#define ID_MENU_RAKNET_HILELERI 31
#define ID_HILE_GECIKME_SURELERI 32
#define ID_MENU_ANTI_CRASHERLER 33
#define ID_MENU_SILAH_HILELERI  34
#define ID_MENU_B0TZ			35
#define ID_MENU_AIM_HILELERI	36

#ifdef __CHEAT_VEHRECORDING_H__
#define ID_MENU_ROUTES			26
#define ID_MENU_ROUTES_LOAD		27
#define ID_MENU_ROUTES_DROP		28
#endif

#define ID_CHEAT_INVULN						10
#define ID_CHEAT_WEAPONS					20
#define ID_CHEAT_MONEY						30
#define ID_CHEAT_MODS						40
#define ID_CHEAT_PROT						50
#define ID_CHEAT_WARP_NEAR					60
#define ID_CHEAT_JETPACK					70
#define ID_CHEAT_UNLOCK						80
#define ID_CHEAT_WEATHER					90
#define ID_CHEAT_TIME						100
#define ID_CHEAT_HP							110
#define ID_CHEAT_ARMOR						120
#define ID_CHEAT_GRAVITY					130
#define ID_CHEAT_MAP						140
#define ID_CHEAT_TELETEXTS					150
#define ID_CHEAT_GAME_SPEED					160
#define ID_CHEAT_HANDLING					170
#define ID_CHEAT_KEEP_TRAILER				180
#define ID_CHEAT_NOCOLS						190
#define ID_CHEAT_CHAMS						200
#define ID_CHEAT_CUSTOM_RUNSTYLE			210
#define ID_CHEAT_FLY_SPEED					220
#define ID_CHEAT_DISABLE_WAVES				230
#define ID_CHEAT_MAP_DRAW_LINES				231
#define ID_CHEAT_SURF						232
#define ID_CHEAT_FREEZEROT					233

#define ID_CHEAT_INVULN_ACTOR				0
#define ID_CHEAT_INVULN_VEHICLE				1
#define ID_CHEAT_INVULN_TIRES				2
#define ID_CHEAT_INVULN_MIN_HP				3
#define ID_CHEAT_INVULN_REGEN				5
#define ID_CHEAT_INVULN_REGEN_ONFOOT		6
#define ID_CHEAT_INVULN_DISABLE_EXTRA_INV	7
#define ID_CHEAT_INVULN_ACT_EXPL_INV		8
#define ID_CHEAT_INVULN_ACT_FALL_INV		9
#define ID_CHEAT_INVULN_ACT_FIRE_INV		10

#define ID_CHEAT_MONEY_GIVE_500				0
#define ID_CHEAT_MONEY_GIVE_1000			1
#define ID_CHEAT_MONEY_GIVE_5000			2
#define ID_CHEAT_MONEY_GIVE_10000			3
#define ID_CHEAT_MONEY_GIVE_20000			4
#define ID_CHEAT_MONEY_GIVE_99999999		5
#define ID_CHEAT_MONEY_GIVE_CUSTOM			6
#define ID_CHEAT_MONEY_MAX					7
#define ID_CHEAT_MONEY_RAND_MIN				8
#define ID_CHEAT_MONEY_RAND_MAX				9
#define ID_CHEAT_MONEY_IVAL_MIN				10
#define ID_CHEAT_MONEY_IVAL_MAX				11

#define ID_CHEAT_MODS_COLOR1				10
#define ID_CHEAT_MODS_COLOR2				20
#define ID_CHEAT_MODS_PAINTJOB				30

#define ID_CHEAT_HANDLING_MASS				0
#define ID_CHEAT_HANDLING_TURNMASS			1
#define ID_CHEAT_HANDLING_DRAGCOEFF			2
#define ID_CHEAT_HANDLING_TRACMULT			3
#define ID_CHEAT_HANDLING_ENGNACCEL			4
#define ID_CHEAT_HANDLING_MAXVEL			5
#define ID_CHEAT_HANDLING_BRAKEDECEL		6
#define ID_CHEAT_HANDLING_SUSPFORCELVL		7
#define ID_CHEAT_HANDLING_COLDMGMULT		8
#define ID_CHEAT_HANDLING_MULTIPLIER		9
#define ID_CHEAT_HANDLING_TRACTIONLOSS		10
#define ID_CHEAT_HANDLING_TRACTIONBIAS		11
#define ID_CHEAT_HANDLING_SUSPANTIDIVEMULT	12


#define ID_WEAPON_ENABLE					0
#define ID_WEAPON_RANDOM					1
#define ID_WEAPON_ITEM						2

#define ID_VEHICLES_IWARP					0
#define ID_VEHICLES_FREEZE					1
#define ID_MENU_VEHICLES_SUB				106

#define ID_MISC_COORDS						0
#define ID_MISC_RELOAD						1
#define ID_MISC_HUDTEXT						2
#define ID_MISC_BAD_WEAPONS					3
#define ID_MISC_TRAILERS					4
#define ID_MISC_FPSLIMIT					5
#define ID_MISC_TOGGLEWINDOWED				6

#define ID_DEBUG_ENABLE						0
#define ID_DEBUG_SELF_ACTOR					1
#define ID_DEBUG_SAMP_DLL					2
#define ID_DEBUG_SELF_VEHICLE				3
#define ID_DEBUG_SAMP_INFO					4
#define ID_DEBUG_SAMP_PLAYER_LIST			5
#define ID_DEBUG_SAMP_LOCAL_INFO			6
#define ID_DEBUG_SAMP_CHAT_INFO				7
#define ID_DEBUG_SAMP_CHAT_IPT_INFO			8
#define ID_DEBUG_SAMP_KILL_INFO				9
#define ID_DEBUG_SAMP_VEHICLE_LIST			10
#define ID_DEBUG_SAMP_LOCAL_SAMPPED			11

#ifdef __CHEAT_VEHRECORDING_H__
#define ID_ROUTES_ACTIVATED					0
#define ID_ROUTES_WRITE						1
#define ID_ROUTES_OPTIMIZE					2
#endif

#define ID_HUDIND_BAR						0
#define ID_HUDIND_TSHADOWS					1
#define ID_HUDIND_INV						2
#define ID_HUDIND_WEAPON					3
#define ID_HUDIND_MONEY						4
#define ID_HUDIND_FREEZE					5
#define ID_HUDIND_INVEH_AIRBRK				6
#define ID_HUDIND_INVEH_STICK				7
#define ID_HUDIND_INVEH_BRKDANCE			8
#define ID_HUDIND_ONFOOT_AIRBRK				9
#define ID_HUDIND_ONFOOT_STICK				10
#define ID_HUDIND_ONFOOT_AIM				11
#define ID_HUDIND_POS						12
#define ID_HUDIND_FPS						13
#define ID_HUDIND_LB_BARS					14
#define ID_HUDIND_INVEH_SPIDER				15
#define ID_HUDIND_INVEH_FLY					16
#define ID_HUDIND_ONFOOT_FLY				17
#define ID_HUDIND_SURF						18
#define ID_HUDIND_FREEZEROT					19



#define ID_MENU_SAMPMISC					0
#define ID_MENU_SAMPMISC_VEHICLES_INSTANT	108
#define ID_MENU_SAMPMISC_FAKE_KILL			105
#define ID_MENU_SAMPMISC_SPOOF_WEAPON		3
#define ID_MENU_SAMPMISC_SAMP_INFO_LIST		4
#define ID_MENU_SAMPMISC_CHAT_TEXT			6
#define ID_MENU_SAMPMISC_CHAT_TEXTLINES		7
#define ID_MENU_SAMPMISC_GAMESTATE			9
#define ID_MENU_SAMPMISC_SPECIALACTION		12
#define ID_MENU_SAMPMISC_SAMP_DRUNK			13
#define ID_MENU_SAMPMISC_TELEOBJECT			109
#define ID_MENU_SAMPMISC_TELEPICKUP			110
#define ID_MENU_SAMPMISC_RENDEROBJTXT		15
#define ID_MENU_SAMPMISC_RENDERPCKTXT		16
#define ID_MENU_SAMPMISC_M0DCOMMANDS		17
#define ID_MENU_SAMPMISC_EXTRAGM			18

#define ID_MENU_SPECIAL_ACTION_NONE				0
#define ID_MENU_SPECIAL_ACTION_USEJETPACK		2
#define ID_MENU_SPECIAL_ACTION_DANCE1			5
#define ID_MENU_SPECIAL_ACTION_DANCE2			6
#define ID_MENU_SPECIAL_ACTION_DANCE3			7
#define ID_MENU_SPECIAL_ACTION_DANCE4			8
#define ID_MENU_SPECIAL_ACTION_HANDSUP			10
#define ID_MENU_SPECIAL_ACTION_USECELLPHONE		11
#define ID_MENU_SPECIAL_ACTION_STOPUSECELLPHONE 13
#define ID_MENU_SPECIAL_ACTION_DRINK_BEER		20
#define ID_MENU_SPECIAL_ACTION_SMOKE_CIGGY		21
#define ID_MENU_SPECIAL_ACTION_DRINK_WINE		22
#define ID_MENU_SPECIAL_ACTION_DRINK_SPRUNK		23
#define ID_MENU_SPECIAL_ACTION_CUFFED			24
#define ID_MENU_SPECIAL_ACTION_CARRY			25
#define ID_MENU_SPECIAL_ACTION_URINATE			68

#define ID_MENU_NETPATCHES_INRPC				10024
#define ID_MENU_NETPATCHES_OUTRPC				10025
#define ID_MENU_NETPATCHES_INPACKET				10026
#define ID_MENU_NETPATCHES_OUTPACKET			10027
#define ID_MENU_NETPATCHES_TOGGLE_ALL			INI_NETPATCHES_MAX


//#define ID_CARS_TORNADO						209
//#define ID_CARS_MAGNET						210
//#define ID_CARS_FUCKER2						211
//#define ID_CARS_LINE						212
//#define ID_SHAKING_CARS						213
//#define ID_CARS_TOWER						214
//#define ID_CARS_FLYING						215
//#define ID_CARS_FALLING						216
//#define ID_CARS_SINKER						217
//#define ID_CARS_TORNADO2					218



struct menu *menu_active = NULL;
int	menu_init = 0, menu_mouseover = -1;
extern int	iGTAPatchesCount, iSAMPPatchesCount, iNetPatchesCount, iServersCount;

static struct menu *menu_new ( struct menu *parent, int id, menu_callback callback )
{
	struct menu *menu = (struct menu *)calloc( 1, sizeof(struct menu) );

	if ( menu == NULL )
		return NULL;

	menu->id = id;
	menu->parent = parent;
	menu->callback = callback;

	return menu;
}

static struct menu_item *menu_item_add ( struct menu *menu, struct menu *submenu, const char *name, int id,
										 D3DCOLOR color, void *data, const char* description = "")
{
	struct menu_item	*item;
	int					i;

	i = menu->count++;
	menu->item = (struct menu_item *)realloc( menu->item, sizeof(struct menu_item) * menu->count );
	item = &menu->item[i];

	memset( item, 0, sizeof(menu_item) );
	item->submenu = submenu;
	item->menu = menu;
	item->name = _strdup( name );
	item->id = id;
	item->color = color;
	item->data = data;
	item->description = description;
	return item;
}

static void menu_item_name_set ( struct menu_item *item, const char *fmt, ... )
{
	const char	*name_new;
	char		name[64];
	va_list		ap;

	memset( name, 0, sizeof(name) );
	va_start( ap, fmt );
	vsnprintf( name, sizeof(name)-1, fmt, ap );
	va_end( ap );

	if ( (name_new = _strdup(name)) != NULL )
	{
		free( (void *)item->name );
		item->name = name_new;
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//menu_callback_cheats_mods
static void menu_cheats_mods_populate ( struct menu *menu )
{
	// clear menu
	menu_items_free( menu );

	// get vehicle_info
	struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
	if ( vinfo == NULL )
		return;

	struct actor_info	*ainfo = actor_info_get( ACTOR_SELF, 0 );
	if ( vinfo->passengers[0] != ainfo )
		return;

	// some variables
	int		iModelID = vinfo->base.model_alt_id;
	char	name[64];

	/* i... like... colors & paint
	#define ID_CHEAT_MODS_COLOR1	10
	#define ID_CHEAT_MODS_COLOR2	20
	#define ID_CHEAT_MODS_PAINTJOB	30
	*/
	snprintf( name, sizeof(name), "Color 1: %d", vinfo->color[0] );
	menu_item_add( menu, NULL, name, ID_CHEAT_MODS_COLOR1, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Color 2: %d", vinfo->color[1] );
	menu_item_add( menu, NULL, name, ID_CHEAT_MODS_COLOR2, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Paintjob: %d", vehicle_getPaintJob(vinfo) );
	menu_item_add( menu, NULL, name, ID_CHEAT_MODS_PAINTJOB, MENU_COLOR_DEFAULT, NULL );

	// No upgrades for these types
	eClientVehicleType	vehicleType = GetVehicleType( iModelID );
	if ( vehicleType == CLIENTVEHICLE_BOAT
	 ||	 vehicleType == CLIENTVEHICLE_TRAIN
	 ||	 vehicleType == CLIENTVEHICLE_HELI
	 ||	 vehicleType == CLIENTVEHICLE_PLANE
	 ||	 vehicleType == CLIENTVEHICLE_BIKE
	 ||	 vehicleType == CLIENTVEHICLE_BMX ) return;

	for ( int iUpgradeInfo = 0; iUpgradeInfo < VEHICLE_UPGRADES_COUNT; iUpgradeInfo++ )
	{
		if ( isUpgradeCompatible(cveh_upgrade_info[iUpgradeInfo].iModelID, vinfo) )
		{
			snprintf( name, sizeof(name), "%s %s", cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName,
					  cveh_upgrade_info[iUpgradeInfo].upgradeName );
			menu_item_add( menu, NULL, name, cveh_upgrade_info[iUpgradeInfo].iModelID, MENU_COLOR_DEFAULT, NULL );

			// skip matching sideskirt
			if ( cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName == "Sideskirt"
			 ||	 cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName == "Vents" ) iUpgradeInfo++;
		}
	}
}

static void menu_cheats_spoof_kill_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_Players == NULL )
		return;

	char	text[64];
	int		i;

	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		D3DCOLOR	color = MENU_COLOR_DEFAULT;

		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL )
			continue;

		if ( g_Players->pRemotePlayer[i] != NULL )
			color = samp_color_get( i );

		snprintf( text, sizeof(text), "Fake killed by %s (ID: %d)", getPlayerName(i), i );

		menu_item_add( menu, NULL, text, ID_MENU_SAMPMISC_FAKE_KILL, color, (void *)(UINT_PTR) i );
	}
}

static void menu_vehicles_populate ( struct menu *menu, int class_id )
{
	const struct actor_info *actor_self = actor_info_get( ACTOR_SELF, 0 );
	char					name[64];
	int						i;

	menu_items_free( menu );

	if ( pool_vehicle != NULL )
	{
		for ( i = 0; i < pool_vehicle->size; i++ )
		{
			static const struct vehicle_entry	unknown = { 0, VEHICLE_CLASS_CAR, "[Unknown vehicle]" };
			const struct vehicle_info			*info = vehicle_info_get( i, VEHICLE_ALIVE );
			const struct vehicle_entry			*vehicle;
			float								dist[3] = { 0.0f, 0.0f, 0.0f };

			if ( info == NULL )
				continue;

			vehicle = gta_vehicle_get_by_id( info->base.model_alt_id );
			if ( vehicle == NULL )
				vehicle = &unknown;

			if ( vehicle->class_id != class_id )
				continue;

			if ( actor_self != NULL )
				vect3_vect3_sub( &info->base.matrix[4 * 3], &actor_self->base.matrix[4 * 3], dist );

			if ( vect3_near_zero( &info->base.matrix[4 * 3] ) )
				continue;

			snprintf( name, sizeof(name), "%s (%.2fm%s)", vehicle->name, vect3_length(dist),
					  (info->passengers[0] == NULL) ? "" : ", Occupied" );

			menu_item_add( menu, NULL, name, i, MENU_COLOR_DEFAULT, NULL );
		}
	}
}

static void menu_players_warp_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_Players == NULL )
		return;

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		D3DCOLOR	color = MENU_COLOR_DEFAULT;

		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if(g_Players->pRemotePlayer[i] == NULL)
			continue;

		// can obtain position data?
		if(	vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[i]) 
			&& (g_Players->pRemotePlayer[i]->pPlayerData == NULL || 
			g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL) ) 
			continue;

		color = samp_color_get( i );
		snprintf( text, sizeof(text), "%s (ID: %d)", getPlayerName(i), i );
		menu_item_add( menu, NULL, text, i, color, NULL );
	}
}

static void menu_players_vehwarp_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_Players == NULL )
		return;

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		D3DCOLOR	color = MENU_COLOR_DEFAULT;

		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if ( g_Players->pRemotePlayer[i] == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL )
			continue;

		//if(vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[i])) continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData->bytePlayerState != PLAYER_STATE_DRIVER
		 &&	 g_Players->pRemotePlayer[i]->pPlayerData->bytePlayerState != PLAYER_STATE_PASSENGER ) continue;

		if ( g_Players->pRemotePlayer[i] != NULL )
			color = samp_color_get( i );

		snprintf( text, sizeof(text), "%s (ID: %d)", getPlayerName(i), i );
		menu_item_add( menu, NULL, text, i, color, NULL );
	}
}

static void menu_vehicles_instant_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_Players == NULL && g_Vehicles == NULL )
		return;

	const struct vehicle_entry	*vehicle;
	char						text[64];
	int							v;
	for ( v = 0; v < SAMP_MAX_VEHICLES; v++ )
	{
		if ( g_Vehicles->iIsListed[v] != 1 )
			continue;
		if ( g_Vehicles->pSAMP_Vehicle[v] == NULL )
			continue;
		if ( g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL )
			continue;

		vehicle = gta_vehicle_get_by_id( g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle->base.model_alt_id );
		snprintf( text, sizeof(text), "%s (ID: %d)", vehicle->name, v );
		menu_item_add( menu, NULL, text, v, D3DCOLOR_XRGB(150, 150, 150), NULL );
	}
}

static void menu_players_spectator_mode_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_Players == NULL )
		return;

	menu_item_add( menu, NULL, "Disable", ID_NONE, MENU_COLOR_DEFAULT, NULL );

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		D3DCOLOR	color = MENU_COLOR_DEFAULT;

		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if ( g_Players->pRemotePlayer[i] == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL )
			continue;

		color = samp_color_get( (int)g_Players->pRemotePlayer[i]->pPlayerData->sPlayerID );

		snprintf( text, sizeof(text), "Spectate %s (ID: %d)", getPlayerName(i), i );
		menu_item_add( menu, NULL, text, i, color, (void *)(UINT_PTR) i );
	}
}

static void menu_telepickup_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_SAMP->pPools->pPickup == NULL )
		return;

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PICKUPS; i++ )
	{
		if ( g_SAMP->pPools->pPickup->pickup[i].iModelID == 0 )
			continue;
		if ( g_SAMP->pPools->pPickup->pickup[i].iType == 0 )
			continue;

		D3DCOLOR	color = MENU_COLOR_DEFAULT;
		snprintf( text, sizeof(text), "Pickup (%d, ModelID: %d)", i, g_SAMP->pPools->pPickup->pickup[i].iModelID );
		menu_item_add( menu, NULL, text, i, color, NULL );
	}
}

static int menu_callback_telepickup ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		int id = item->id;

		if ( g_SAMP->pPools->pPickup == NULL )
			return 0;
		if ( g_SAMP->pPools->pPickup->pickup[id].iType == 0 )
			return 0;
		if ( g_SAMP->pPools->pPickup->pickup[id].iModelID == 0 )
			return 0;
		if ( item->id == ID_NONE )
			return 0;

		float	pos[3];

		vect3_copy( g_SAMP->pPools->pPickup->pickup[id].fPosition, pos );
		pos[1] += 2.0f;
		cheat_teleport( pos, 0 );

		return 1;
	}

	return 0;
}

static void menu_teleobject_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_SAMP->pPools->pObject == NULL )
		return;

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_OBJECTS; i++ )
	{
		D3DCOLOR	color = MENU_COLOR_DEFAULT;

		if ( g_SAMP->pPools->pObject->iIsListed[i] != 1 )
			continue;
		if ( g_SAMP->pPools->pObject->object[i] == NULL )
			continue;
		if ( g_SAMP->pPools->pObject->object[i]->pGTAEntity == NULL )
			continue;

		float	pos[3];
		vect3_copy( &g_SAMP->pPools->pObject->object[i]->pGTAEntity->base.matrix[4 * 3], pos );
		if ( vect3_near_zero(pos) )
			continue;

		snprintf( text, sizeof(text), "Object (%d, ModelID %d)", i,
				  g_SAMP->pPools->pObject->object[i]->pGTAEntity->base.model_alt_id );
		menu_item_add( menu, NULL, text, i, color, NULL );
	}
}

static int menu_callback_teleobject ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		if ( g_SAMP->pPools->pObject == NULL )
			return 0;
		if ( item->id == ID_NONE )
			return 0;

		int		id = item->id;
		float	pos[3];

		if ( g_SAMP->pPools->pObject->iIsListed[id] != 1 )
		{
			addMessageToChatWindow( "Object does not exist." );
			return 0;
		}

		if ( g_SAMP->pPools->pObject->object[id]->pGTAEntity == NULL )
		{
			addMessageToChatWindow( "Invalid object info." );
			return 0;
		}

		vect3_copy( &g_SAMP->pPools->pObject->object[id]->pGTAEntity->base.matrix[4 * 3], pos );
		pos[2] += 2.0f;
		cheat_teleport( pos, 0 );

		return 1;
	}

	return 0;
}

static void menu_handling_populate ( struct menu *menu )
{
	CVehicle	*cveh = getSelfCVehicle();
	if ( cveh == NULL )
		return;
	if ( cveh->GetHandlingData() == NULL )
		return;

	traceLastFunc( "menu_handling_populate()" );

	char	text[64];

	menu_items_free( menu );

	snprintf( text, sizeof(text), "Multiplier: %0.2f", set.handling_multiplier );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_MULTIPLIER, MENU_COLOR_DEFAULT, NULL );

	menu_item_add( menu, NULL, "\tHandling", ID_NONE, MENU_COLOR_SEPARATOR, NULL );

	snprintf( text, sizeof(text), "Engine acceleration: %0.2f", cveh->GetHandlingData()->GetEngineAccelleration() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_ENGNACCEL, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Brake decelleration: %0.2f", cveh->GetHandlingData()->GetBrakeDecelleration() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_BRAKEDECEL, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Drag coefficient: %0.2f", cveh->GetHandlingData()->GetDragCoeff() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_DRAGCOEFF, MENU_COLOR_DEFAULT, NULL );

	snprintf( text, sizeof(text), "Max velocity: %0.2f", cveh->GetHandlingData()->GetMaxVelocity() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_MAXVEL, MENU_COLOR_DEFAULT, NULL );

	// these can't be used because they don't always show up right etc... possibly mapped wrong
	snprintf( text, sizeof(text), "Traction multiplier: %0.2f", cveh->GetHandlingData()->GetTractionMultiplier() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_TRACMULT, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Traction loss: %0.2f", cveh->GetHandlingData()->GetTractionLoss() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_TRACTIONLOSS, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Traction bias: %0.2f", cveh->GetHandlingData()->GetTractionBias() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_TRACTIONBIAS, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Suspension force level: %0.2f", cveh->GetHandlingData()->GetSuspensionForceLevel() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_SUSPFORCELVL, MENU_COLOR_DEFAULT, NULL );

	//snprintf( text, sizeof(text), "Suspension anti-dive multiplier: %0.2f", cveh->GetHandlingData()->GetSuspensionAntidiveMultiplier() );
	//menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_SUSPANTIDIVEMULT, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Mass: %0.2f", cveh->GetHandlingData()->GetMass() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_MASS, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Turn mass: %0.2f", cveh->GetHandlingData()->GetTurnMass() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_TURNMASS, MENU_COLOR_DEFAULT, NULL );

	//snprintf( text, sizeof(text), "Collision damage multiplier: %0.2f",
	//		  cveh->GetHandlingData()->GetCollisionDamageMultiplier() );
	//menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_COLDMGMULT, MENU_COLOR_DEFAULT, NULL );
}

static void menu_playerinfo_populate ( struct menu *menu )
{
	menu_items_free( menu );
	if ( g_Players == NULL )
		return;

	menu_item_add( menu, NULL, "Disable", SAMP_MAX_PLAYERS + 1, MENU_COLOR_DEFAULT, NULL );

	menu_item_add( menu, NULL, "Local Player", -2, MENU_COLOR_DEFAULT, (void *)(UINT_PTR) - 2 );

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if ( g_Players->pRemotePlayer[i] == NULL )
			continue;

		snprintf( text, sizeof(text), "View %s (ID: %d)", getPlayerName(i), i );
		menu_item_add( menu, NULL, text, i, MENU_COLOR_DEFAULT, (void *)(UINT_PTR) i );
	}
}

static void menu_playermute_populate ( struct menu *menu )
{
	menu_items_free( menu );
	if ( g_Players == NULL )
		return;

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		if ( g_Players->iIsListed[i] != 1 || g_Players->pRemotePlayer[i] == NULL )
		{
			g_bPlayerMuted[i] = false;
			continue;
		}

		snprintf( text, sizeof(text), "Mute %s (ID: %d)", getPlayerName(i), i );
		menu_item_add( menu, NULL, text, i, MENU_COLOR_DEFAULT, (void *)(UINT_PTR) i );
	}
}

#ifdef __CHEAT_VEHRECORDING_H__
static void menu_routes_drop_populate ( struct menu *menu )
{
	menu_items_free( menu );

	// now get me some data from the database
	char table_name_[64];
	char *table_name;
	int num_tables = rec_sqlite_getNumTables();

	if ( num_tables <= 0 )
	{
		menu_item_add( menu, NULL, (num_tables < 0) ? "Error Reading Database" : "No Saved Routes", ID_NONE, 
			MENU_COLOR_DEFAULT, NULL );
		return;
	}

	for ( int i = 0; i < num_tables; i++ )
	{
		table_name = rec_sqlite_getTableName(i);
		if ( table_name == NULL )
			continue;

		// remember to change menu_callback_routes_drop, if you change the "Delete" text
		_snprintf_s( table_name_, sizeof(table_name_)-1, "Delete '%s'", table_name );
		menu_item_add( menu, NULL, table_name_, i, MENU_COLOR_DEFAULT, NULL );
	}
}

static void menu_routes_load_populate ( struct menu *menu )
{
	menu_items_free( menu );

	// now get me some data from the database
	int num_tables = rec_sqlite_getNumTables();
	char *table_name;

	if ( num_tables <= 0 )
	{
		menu_item_add( menu, NULL, (num_tables < 0) ? "Error Reading Database" : "No Saved Routes", ID_NONE, 
			MENU_COLOR_DEFAULT, NULL );
		return;
	}

	for ( int i = 0; i < num_tables; i++ )
	{
		table_name = rec_sqlite_getTableName(i);
		if ( table_name == NULL )
			continue;
		menu_item_add( menu, NULL, table_name, i, MENU_COLOR_DEFAULT, NULL );
	}
}
#endif

// called when a menu is going to be displayed
static void menu_event_activate ( struct menu *menu )
{
	if ( menu == NULL )
		return;

	switch ( menu->id )
	{
	case ID_MENU_CHEATS_MODS:
		menu_cheats_mods_populate( menu );
		break;

	case ID_MENU_PLAYERS_WARP:
		menu_players_warp_populate( menu );
		break;

	case ID_MENU_PLAYERS_VEHWARP:
		menu_players_vehwarp_populate( menu );
		break;

	case ID_MENU_PLAYERS_SPEC:
		menu_players_spectator_mode_populate( menu );
		break;

	case ID_MENU_SAMPMISC_FAKE_KILL:
		menu_cheats_spoof_kill_populate( menu );
		break;

	case ID_MENU_VEHICLES_SUB:
		menu_vehicles_populate( menu, (int)(UINT_PTR) menu->parent->item[menu->parent->pos].data );
		break;

	case ID_MENU_SAMPMISC_VEHICLES_INSTANT:
		menu_vehicles_instant_populate( menu );
		break;

	case ID_MENU_SAMPMISC_TELEOBJECT:
		menu_teleobject_populate( menu );
		break;

	case ID_MENU_SAMPMISC_TELEPICKUP:
		menu_telepickup_populate( menu );
		break;

	case ID_MENU_CHEATS_HANDLING:
		menu_handling_populate( menu );
		break;

	case ID_MENU_PLAYERS_INFO:
		menu_playerinfo_populate( menu );
		break;

	case ID_MENU_PLAYERS_MUTE:
		menu_playermute_populate( menu );
		break;

#ifdef __CHEAT_VEHRECORDING_H__
	case ID_MENU_ROUTES_DROP:
		menu_routes_drop_populate( menu );
		break;

	case ID_MENU_ROUTES_LOAD:
		menu_routes_load_populate( menu );
		break;
#endif
	}
}

/* run every frame */
void menu_run ( void )
{
	struct menu_item	*item;
	static uint32_t		key_time_updown, key_time_incdec;

	if ( menu_active == NULL )
		return;

	if ( KEYCOMBO_PRESSED(set.key_menu) )
	{
		menu_toggle((cheat_state->_generic.menu ^= 1) != 0);
	}

	if ( cheat_state->_generic.menu )
	{
		if ( KEY_PRESSED(set.key_menu_up) || KEY_PRESSED(set.key_menu_down) )
		{
			menu_active->pos += KEY_PRESSED( set.key_menu_up ) ? -1 : 1;
			key_time_updown = time_get() + MSEC_TO_TIME( MENU_SCROLL_DELAY );
		}

		if ( KEY_DOWN(set.key_menu_up) || KEY_DOWN(set.key_menu_down) )
		{
			if ( time_get() > key_time_updown )
			{
				int diff = time_get() - key_time_updown;
				int overruns = diff / MENU_SCROLL_TIME;
				int dir = KEY_DOWN( set.key_menu_up ) ? -1 : 1;

				menu_active->pos += dir * ( overruns + 1 );

				key_time_updown = time_get() + MENU_SCROLL_TIME - ( diff % MENU_SCROLL_TIME );
			}
		}

		if ( menu_active->pos < 0 )
			menu_active->pos = menu_active->count - 1;
		if ( menu_active->pos >= menu_active->count )
			menu_active->pos = 0;

		if ( menu_active->count <= 0 )
			item = NULL;
		else
			item = &menu_active->item[menu_active->pos];

		if ( KEY_PRESSED(set.key_menu_left) )
		{
			/* pressing left in the main menu, exits the menu */
			if ( menu_active->parent == NULL )
			{
				menu_toggle(false);
				return;
			}

			menu_active = menu_active->parent;
			menu_event_activate( menu_active );
		}

		if ( KEY_PRESSED(set.key_menu_right) || KEY_PRESSED(set.key_menu_select) )
		{
			int was_selected = 0;

			if ( KEY_PRESSED(set.key_menu_select) && menu_active->callback != NULL && item != NULL )
			{
				if ( menu_active->callback(MENU_OP_SELECT, item) )
					was_selected = 1;
			}

			if ( !was_selected && item != NULL && item->submenu != NULL )
			{
				menu_active = item->submenu;
				menu_event_activate( menu_active );
			}
		}

		if ( KEY_PRESSED(set.key_menu_dec) || KEY_PRESSED(set.key_menu_inc) )
		{
			int op = KEY_PRESSED( set.key_menu_dec ) ? MENU_OP_DEC : MENU_OP_INC;
			if ( item != NULL )
				menu_active->callback( op, item );
			key_time_incdec = time_get() + MSEC_TO_TIME( MENU_SCROLL_DELAY );
		}

		if ( KEY_DOWN(set.key_menu_dec) || KEY_DOWN(set.key_menu_inc) )
		{
			if ( time_get() > key_time_incdec )
			{
				int diff = time_get() - key_time_incdec;
				int overruns = diff / MENU_SCROLL_TIME;

				int op = KEY_DOWN( set.key_menu_dec ) ? MENU_OP_DEC : MENU_OP_INC;
				menu_active->callback( op, item );

				key_time_incdec = time_get() + MENU_SCROLL_TIME - ( diff % MENU_SCROLL_TIME );
			}
		}

		KEY_CONSUME( set.key_menu_up );
		KEY_CONSUME( set.key_menu_right );
		KEY_CONSUME( set.key_menu_down );
		KEY_CONSUME( set.key_menu_left );
		KEY_CONSUME( set.key_menu_select );
		KEY_CONSUME( set.key_menu_dec );
		KEY_CONSUME( set.key_menu_inc );
	}
}

bool menu_wndproc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MOUSEWHEEL:
		{
			if (menu_active == NULL || !cheat_state->_generic.menu || !cheat_state->_generic.menu_mousecontrol)
				break;
			
			POINT				point = { LOWORD(lParam), HIWORD(lParam) };
			const int			ROW_HEIGHT = (int)ceilf(pD3DFont->DrawHeight());
			const int			MENU_HEIGHT = (int)ceilf(pD3DFont->DrawHeight() * (float)MENU_ROWS) + 2;
			int					left = pPresentParam.BackBufferWidth / 2 - MENU_WIDTH / 2;
			int					top = pPresentParam.BackBufferHeight - MENU_HEIGHT - 20;
			int					pos = 0;

			if (uMsg == WM_MOUSEWHEEL)
			{
				// WM_MOUSEWHEEL has global cursor coords
				ScreenToClient(pPresentParam.hDeviceWindow, &point);

				if (LOWORD(wParam) == MK_SHIFT)
				{
					menu_item *item = nullptr;
					if (menu_active->count > 0)
						item = &menu_active->item[menu_active->pos];

					int op = short(HIWORD(wParam)) > 0 ? MENU_OP_INC : MENU_OP_DEC;
					menu_active->callback(op, item);
				}
				else
				{
					int dir = short(HIWORD(wParam)) > 0 ? -1 : 1;
					menu_active->pos += dir;
				}
			}

			if (point.x > left && point.x < left + MENU_WIDTH && point.y > top && point.y < top + MENU_HEIGHT)
			{
				pos = (point.y - top) / ROW_HEIGHT;
				if (pos > menu_active->count - 1) pos = menu_active->count - 1;
				if (pos > MENU_ROWS - 1) pos = MENU_ROWS - 1;
				menu_mouseover = menu_active->top_pos + pos;

				if (uMsg == WM_LBUTTONDOWN)
				{
					if (menu_mouseover != -1)
						menu_active->pos = menu_mouseover;
					menu_item *item = nullptr;
					if (menu_active->count > 0)
						item = &menu_active->item[menu_active->pos];

					if (item != nullptr && item->submenu != nullptr)
					{
						menu_active = item->submenu;
						menu_event_activate(menu_active);
					}
					else if (menu_active->callback != nullptr && item != nullptr)
					{
						menu_active->callback(MENU_OP_SELECT, item);
					}
				}
			}
			else
			{
				menu_mouseover = -1;
			}
			if (uMsg == WM_RBUTTONDOWN)
			{
				if (menu_active->parent == NULL)
				{
					menu_toggle(false);
					break;
				}
				menu_active = menu_active->parent;
				menu_event_activate(menu_active);
			}
			break;
		}
	}
	return false;
}

void menu_toggle(bool toggle)
{
	cheat_state->_generic.menu = toggle;
	//cheat_state->_generic.NewMenu = toggle;
	menu_mouseover = -1;
	if (toggle)
	{
		menu_event_activate(menu_active);
		if (g_SAMP)
		{
			if (cheat_state->_generic.menu_mousecontrol = KEYCOMBO_DOWN(set.key_menu_mousecontrol))
				toggleSAMPCursor(true);
		}
	}
	else if (cheat_state->_generic.menu_mousecontrol && g_SAMP)
	{
		toggleSAMPCursor(false);
	}
}

static int menu_callback_main ( int op, struct menu_item *item )
{
	return 0;
}

static int menu_callback_cheats_mods ( int op, struct menu_item *item )
{
	struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
	if ( vinfo == NULL )
		return 0;
	switch ( op )
	{
	case MENU_OP_DEC:
	case MENU_OP_INC:
		int mod, color_temp, paintjob_temp;
		switch ( item->id )
		{
		case ID_CHEAT_MODS_COLOR1:
			color_temp = vehicle_getColor0( vinfo );
			mod = ( op == MENU_OP_DEC ) ? -1 : 1;
			if ( mod > 0 )
				color_temp++;
			if ( mod < 0 )
				color_temp--;
			if ( color_temp < 0 )
				color_temp = 0;
			vehicle_setColor0( vinfo, color_temp );
			menu_item_name_set( item, "Color 1: %d", color_temp );
			return 1;

		case ID_CHEAT_MODS_COLOR2:
			color_temp = vehicle_getColor1( vinfo );
			mod = ( op == MENU_OP_DEC ) ? -1 : 1;
			if ( mod > 0 )
				color_temp++;
			if ( mod < 0 )
				color_temp--;
			if ( color_temp < 0 )
				color_temp = 0;
			vehicle_setColor1( vinfo, color_temp );
			menu_item_name_set( item, "Color 2: %d", color_temp );
			return 1;

		case ID_CHEAT_MODS_PAINTJOB:
			paintjob_temp = vehicle_getPaintJob( vinfo );
			mod = ( op == MENU_OP_DEC ) ? -1 : 1;
			if ( mod > 0 )
				paintjob_temp++;
			if ( mod < 0 )
				paintjob_temp--;
			if ( paintjob_temp < 0 )
				paintjob_temp = 0;
			if ( paintjob_temp > 4 )
				paintjob_temp = 4;
			vehicle_setPaintJob( vinfo, paintjob_temp );
			menu_item_name_set( item, "Paintjob: %d", paintjob_temp );
			return 1;
		}

	case MENU_OP_SELECT:
		if ( item->id >= 1000 && item->id <= 1193 )
		{
			struct actor_info	*ainfo = actor_info_get( ACTOR_SELF, 0 );
			if ( vinfo->passengers[0] != ainfo )
				return 0;

			int						iModelID = item->id;
			int						iUpgradeInfoID;
			vehicle_upgrade_info	upgrade_info = get_cveh_upgrade_info( iModelID, iUpgradeInfoID );
			int						iModelIDplusOne = cveh_upgrade_info[iUpgradeInfoID + 1].iModelID;
			if ( upgrade_info.upgradeCategoryName == "Sideskirt" || upgrade_info.upgradeCategoryName == "Vents" )
			{
				loadSpecificModel( iModelID );
				loadSpecificModel( iModelIDplusOne );
				vehicle_addUpgrade( vinfo, iModelID );
				vehicle_addUpgrade( vinfo, iModelIDplusOne );
			}
			else
			{
				loadSpecificModel( iModelID );
				vehicle_addUpgrade( vinfo, iModelID );
			}

			return 1;
		}
	}

	return 0;
}

static int menu_callback_cheats ( int op, struct menu_item *item )
{
	struct actor_info	*info;
	int					mod;

	switch ( op )
	{
	case MENU_OP_ENABLED:
		switch ( item->id )
		{
		case ID_CHEAT_INVULN:
			return cheat_state->_generic.hp_cheat;

		case ID_CHEAT_WEAPONS:
			return 0;

		case ID_CHEAT_MONEY:
			return cheat_state->_generic.money;

		case ID_CHEAT_MODS:
			return 0;

		case ID_CHEAT_PROT:
			return cheat_state->vehicle.protection;

		case ID_CHEAT_WARP_NEAR:
			return 0;

		case ID_CHEAT_JETPACK:
			return 0;

		case ID_CHEAT_UNLOCK:
			return cheat_state->_generic.vehicles_unlock;

		case ID_CHEAT_WEATHER:
			return set.force_weather == (int)( UINT_PTR ) item->data;

		case ID_CHEAT_TIME:
			return set.force_hour == (int)( UINT_PTR ) item->data;

		case ID_CHEAT_HP:
			return 0;

		case ID_CHEAT_ARMOR:
			return 0;

		case ID_CHEAT_GRAVITY:
			return 0;

		case ID_CHEAT_MAP:
			return cheat_state->_generic.map;

		case ID_CHEAT_TELETEXTS:
			return cheat_state->_generic.teletext;

		case ID_CHEAT_GAME_SPEED:
			return 0;

		case ID_CHEAT_KEEP_TRAILER:
			return cheat_state->vehicle.keep_trailer_attached;

		case ID_CHEAT_NOCOLS:
			return cheat_state->_generic.nocols_enabled;

		case ID_CHEAT_CHAMS:
			return set.chams_on;

		case ID_CHEAT_CUSTOM_RUNSTYLE:
			return set.custom_runanimation_enabled;

		case ID_CHEAT_FLY_SPEED:
			return cheat_state->actor.fly_on;

		case ID_CHEAT_DISABLE_WAVES:
			return pGameInterface->GetWaterManager()->GetWaveLevel() == 0.0f;

		case ID_CHEAT_MAP_DRAW_LINES:
			return set.map_draw_lines;

		case ID_CHEAT_SURF:
			return cheat_state->actor.surf;

		case ID_CHEAT_FREEZEROT:
			return cheat_state->vehicle.freezerot;
		}
		break;

	case MENU_OP_SELECT:
		switch ( item->id )
		{
		case ID_CHEAT_INVULN:
			cheat_state->_generic.hp_cheat ^= 1;
			if( !cheat_state->_generic.hp_cheat )
			{
				struct actor_info *self = actor_info_get( ACTOR_SELF, 0 );
				self->flags &= ~ACTOR_FLAGS_INVULNERABLE;
			}
			break;

		case ID_CHEAT_MONEY:
			cheat_state->_generic.money ^= 1;
			break;

		case ID_CHEAT_PROT:
			cheat_state->vehicle.protection ^= 1;
			break;

		case ID_CHEAT_WARP_NEAR:
			cheat_teleport_nearest_car();
			break;

		case ID_CHEAT_JETPACK:
			gta_jetpack_give();
			break;

		case ID_CHEAT_UNLOCK:
			cheat_state->_generic.vehicles_unlock ^= 1;
			break;

		case ID_CHEAT_WEATHER:
			if ( set.force_weather == (int)(UINT_PTR) item->data )
				set.force_weather = -1;
			else
				set.force_weather = (int)( UINT_PTR ) item->data;
			break;

		case ID_CHEAT_TIME:
			if ( set.force_hour == (int)(UINT_PTR) item->data )
				set.force_hour = -1;
			else
				set.force_hour = (int)( UINT_PTR ) item->data;
			break;

		case ID_CHEAT_MAP:
			cheat_state->_generic.map ^= 1;
			break;

		case ID_CHEAT_TELETEXTS:
			cheat_state->_generic.teletext ^= 1;
			break;

		case ID_CHEAT_HP:
		case ID_CHEAT_ARMOR:
			if ( (info = actor_info_get(ACTOR_SELF, ACTOR_ALIVE)) != NULL )
			{
				if ( item->id == ID_CHEAT_HP )
					info->hitpoints = 100.0f;
				else
					info->armor = 100.0f;
			}
			break;

		case ID_CHEAT_KEEP_TRAILER:
			cheat_state->vehicle.keep_trailer_attached ^= 1;
			break;

		case ID_CHEAT_NOCOLS:
			cheat_state->_generic.nocols_enabled ^= 1;
			break;

		case ID_CHEAT_CHAMS:
			set.chams_on ^= 1;
			break;

		case ID_CHEAT_CUSTOM_RUNSTYLE:
			set.custom_runanimation_enabled ^= 1;
			break;

		case ID_CHEAT_FLY_SPEED:
			cheat_state->actor.fly_on ^= 1;
			break;

		case ID_CHEAT_DISABLE_WAVES:
			if ( pGameInterface->GetWaterManager()->GetWaveLevel() == 0.0f )
				pGameInterface->GetWaterManager()->SetWaveLevel( -1.0f );
			else
				pGameInterface->GetWaterManager()->SetWaveLevel( 0.0f );
			break;

		case ID_CHEAT_MAP_DRAW_LINES:
			set.map_draw_lines ^= 1;
			break;

		case ID_CHEAT_SURF:
			cheat_state->actor.surf ^= 1;
			break;

		case ID_CHEAT_FREEZEROT:
			cheat_state->vehicle.freezerot ^= 1;
			break;

		default:
			return 0;
		}

		return 1;

	case MENU_OP_DEC:
	case MENU_OP_INC:
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;
		switch ( item->id )
		{
		case ID_CHEAT_GRAVITY:
			if ( mod > 0 && gta_gravity_get() < 0.1f )
				gta_gravity_set( gta_gravity_get() + 0.001f );
			if ( mod < 0 && gta_gravity_get() > -0.1f )
				gta_gravity_set( gta_gravity_get() - 0.001f );
			menu_item_name_set( item, "Gravity: %.04f", gta_gravity_get() );
			return 1;

		case ID_CHEAT_GAME_SPEED:
			cheat_state->game_speed += (float)mod * 0.05f;
			menu_item_name_set( item, "Game speed: %d%%", (int)roundf(cheat_state->game_speed * 100.0f) );
			return 1;

		case ID_CHEAT_CUSTOM_RUNSTYLE:
			set.custom_runanimation_id += mod;
			if ( set.custom_runanimation_id >= MOVE_ANIMATIONS_COUNT )
				set.custom_runanimation_id = 0;
			else if ( set.custom_runanimation_id < 0 )
				set.custom_runanimation_id = (MOVE_ANIMATIONS_COUNT-1);
			menu_item_name_set( item, "Custom running style: %i, %s", set.custom_runanimation_id,
										move_animations[set.custom_runanimation_id].moveStyleName );
			return 1;

		case ID_CHEAT_FLY_SPEED:
			if ( set.fly_player_speed <= 4.95f )
			{
				set.fly_player_speed += mod * 0.1f;
			}
			else if ( set.fly_player_speed <= 5.05f
				&& mod < 0 )
			{
				set.fly_player_speed += mod * 0.1f;
			}
			else
			{
				set.fly_player_speed += mod * 1.0f;
			}
			// don't allow it to go under 0.1f
			if ( set.fly_player_speed < 0.1f )
			{
				set.fly_player_speed = 0.1f;
			}

			menu_item_name_set( item, "Player Fly Speed: %0.01f", set.fly_player_speed );
			return 1;

		} // end of INC/DEC
	}

	return 0;
}

static int menu_callback_handling ( int op, struct menu_item *item )
{
	CVehicle	*cveh = getSelfCVehicle();
	if ( cveh == NULL )
		return NULL;

	int		mod;
	float	hlng;

	switch ( op )
	{
	case MENU_OP_DEC:
	case MENU_OP_INC:
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;

		switch ( item->id )
		{
		case ID_CHEAT_HANDLING_MULTIPLIER:
			if ( mod > 0 )
				set.handling_multiplier += 0.050f;
			if ( mod < 0 )
				set.handling_multiplier -= 0.050f;
			menu_item_name_set( item, "Multiplier: %0.2f", set.handling_multiplier );
			return 1;

		case ID_CHEAT_HANDLING_ENGNACCEL:
			hlng = cveh->GetHandlingData()->GetEngineAccelleration();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetEngineAccelleration( hlng );

			//cveh->GetHandlingData()->Recalculate();
			menu_item_name_set( item, "Engine acceleration: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_BRAKEDECEL:
			hlng = cveh->GetHandlingData()->GetBrakeDecelleration();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetBrakeDecelleration( hlng );

			//cveh->GetHandlingData()->Recalculate();
			menu_item_name_set( item, "Brake decelleration: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_MAXVEL:
			hlng = cveh->GetHandlingData()->GetMaxVelocity();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetMaxVelocity( hlng );

			//cveh->GetHandlingData()->Recalculate();
			menu_item_name_set( item, "Max velocity: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_TRACMULT:
			hlng = cveh->GetHandlingData()->GetTractionMultiplier();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetTractionMultiplier( hlng );
			menu_item_name_set( item, "Traction multiplier: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_TRACTIONLOSS:
			hlng = cveh->GetHandlingData()->GetTractionLoss();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetTractionLoss( hlng );
			menu_item_name_set( item, "Traction loss: %0.2f", hlng );
			return 1;

		/*case ID_CHEAT_HANDLING_TRACTIONBIAS:
			if(mod > 0) info->pHandlingData->fTractionBias += set.handling_multiplier;
			if(mod < 0) info->pHandlingData->fTractionBias -= set.handling_multiplier;
			menu_item_name_set(item, "Traction bias: %0.2f", info->pHandlingData->fTractionBias);
			return 1;*/
		case ID_CHEAT_HANDLING_TRACTIONBIAS:
			hlng = cveh->GetHandlingData()->GetTractionBias();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetTractionBias( hlng );
			menu_item_name_set( item, "Traction bias: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_SUSPFORCELVL:
			hlng = cveh->GetHandlingData()->GetSuspensionForceLevel();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetSuspensionForceLevel( hlng );
			menu_item_name_set( item, "Suspension force level: %0.2f", hlng );
			return 1;

		// this one really makes the vehicle go nuttahs with tilt
		// you might lose the wheels using it, lol
		/*case ID_CHEAT_HANDLING_SUSPANTIDIVEMULT:
			if(mod > 0) info->pHandlingData->fSuspensionAntidiveMultiplier += set.handling_multiplier;
			if(mod < 0) info->pHandlingData->fSuspensionAntidiveMultiplier -= set.handling_multiplier;
			menu_item_name_set(item, "Suspension anti-dive multiplier: %0.2f", info->pHandlingData->fSuspensionAntidiveMultiplier);
			return 1;*/
		case ID_CHEAT_HANDLING_MASS:
			hlng = cveh->GetHandlingData()->GetMass();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetMass( hlng );
			menu_item_name_set( item, "Mass: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_TURNMASS:
			hlng = cveh->GetHandlingData()->GetTurnMass();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetTurnMass( hlng );
			menu_item_name_set( item, "Turn mass: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_DRAGCOEFF:
			hlng = cveh->GetHandlingData()->GetDragCoeff();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetDragCoeff( hlng );
			menu_item_name_set( item, "Drag coeffiecient: %0.2f", hlng );
			return 1;

			/*case ID_CHEAT_HANDLING_COLDMGMULT:
			if(mod > 0) info->pHandlingData->fCollisionDamageMultiplier += set.handling_multiplier;
			if(mod < 0) info->pHandlingData->fCollisionDamageMultiplier -= set.handling_multiplier;
			menu_item_name_set(item, "Collision damage multiplier: %0.2f", info->pHandlingData->fCollisionDamageMultiplier);
			return 1;*/
		}
	}

	return 0;
}

static int menu_callback_cheats_invuln ( int op, struct menu_item *item )
{
	int mod;

	switch ( op )
	{
	case MENU_OP_ENABLED:
		switch ( item->id )
		{
		case ID_CHEAT_INVULN_ACTOR:
			return cheat_state->actor.invulnerable;

		case ID_CHEAT_INVULN_VEHICLE:
			return cheat_state->vehicle.invulnerable;

		case ID_CHEAT_INVULN_TIRES:
			return cheat_state->vehicle.hp_tire_support;

		case ID_CHEAT_INVULN_MIN_HP:
			return cheat_state->vehicle.hp_minimum_on;

		case ID_CHEAT_INVULN_REGEN:
			return cheat_state->vehicle.hp_regen_on;

		case ID_CHEAT_INVULN_REGEN_ONFOOT:
			return cheat_state->actor.hp_regen_on;

		case ID_CHEAT_INVULN_DISABLE_EXTRA_INV:
			return set.hp_disable_inv_sp_enemies;

		case ID_CHEAT_INVULN_ACT_EXPL_INV:
			return set.hp_actor_explosion_inv;

		case ID_CHEAT_INVULN_ACT_FALL_INV:
			return set.hp_actor_fall_inv;

		case ID_CHEAT_INVULN_ACT_FIRE_INV:
			return set.hp_actor_fire_inv;
		}
		break;

	case MENU_OP_SELECT:
		switch ( item->id )
		{
		case ID_CHEAT_INVULN_ACTOR:
			cheat_state->actor.invulnerable ^= 1;
			break;

		case ID_CHEAT_INVULN_VEHICLE:
			cheat_state->vehicle.invulnerable ^= 1;
			break;

		case ID_CHEAT_INVULN_TIRES:
			cheat_state->vehicle.hp_tire_support ^= 1;
			break;

		case ID_CHEAT_INVULN_MIN_HP:
			cheat_state->vehicle.hp_minimum_on ^= 1;
			break;

		case ID_CHEAT_INVULN_REGEN:
			cheat_state->vehicle.hp_regen_on ^= 1;
			break;

		case ID_CHEAT_INVULN_REGEN_ONFOOT:
			cheat_state->actor.hp_regen_on ^= 1;
			break;

		case ID_CHEAT_INVULN_DISABLE_EXTRA_INV:
			set.hp_disable_inv_sp_enemies ^= 1;
			break;

		case ID_CHEAT_INVULN_ACT_EXPL_INV:
			set.hp_actor_explosion_inv ^= 1;
			break;

		case ID_CHEAT_INVULN_ACT_FALL_INV:
			set.hp_actor_fall_inv ^= 1;
			break;

		case ID_CHEAT_INVULN_ACT_FIRE_INV:
			set.hp_actor_fire_inv ^= 1;
			break;

		default:
			return 0;
		}

		return 1;
		break;

	case MENU_OP_DEC:
	case MENU_OP_INC:
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;
		switch ( item->id )
		{
		case ID_CHEAT_INVULN_MIN_HP:
			if ( set.hp_minimum > 1000.0f )
			{
				set.hp_minimum = ( mod == 1 ) ? ( set.hp_minimum * 2.0f ) : ( set.hp_minimum / 2.0f );
				if ( set.hp_minimum < 1000.0f )
					set.hp_minimum = 1000.0f;
			}
			else if ( set.hp_minimum > 250.0f )
			{
				set.hp_minimum += (float)mod * 50.0f;
			}
			else
			{
				set.hp_minimum += (float)mod * 10.0f;
			}

			if ( set.hp_minimum <= 0.0f )
				set.hp_minimum = 0.0f;
			else if ( set.hp_minimum > 1000000.0f )
				set.hp_minimum = 1000000.0f;
			else
				set.hp_minimum = roundf( set.hp_minimum );

			menu_item_name_set( item, "Vehicle minimum HP: %d", (int)set.hp_minimum );
			break;

		case ID_CHEAT_INVULN_REGEN:
			set.hp_regen += (float)mod;
			menu_item_name_set( item, "Vehicle HP regeneration: %dhp/sec", (int)set.hp_regen );
			break;

		case ID_CHEAT_INVULN_REGEN_ONFOOT:
			set.hp_regen_onfoot += (float)mod;
			menu_item_name_set( item, "Onfoot HP regeneration: %dhp/sec", (int)set.hp_regen_onfoot );
			break;
		}
		break;
	}

	return 0;
}

static int menu_callback_cheats_money ( int op, struct menu_item *item )
{
	uint32_t	money;
	int			mod;

	switch ( op )
	{
	case MENU_OP_SELECT:
		money = gta_money_get();
		switch ( item->id )
		{
		case ID_CHEAT_MONEY_GIVE_500:
			money += 500;
			break;

		case ID_CHEAT_MONEY_GIVE_1000:
			money += 1000;
			break;

		case ID_CHEAT_MONEY_GIVE_5000:
			money += 5000;
			break;

		case ID_CHEAT_MONEY_GIVE_10000:
			money += 10000;
			break;

		case ID_CHEAT_MONEY_GIVE_20000:
			money += 20000;
			break;

		case ID_CHEAT_MONEY_GIVE_99999999:
			money += 99999999;
			break;

		case ID_CHEAT_MONEY_GIVE_CUSTOM:
			money += set.money_value;
			break;
		}

		gta_money_set( money );
		break;

	case MENU_OP_DEC:
	case MENU_OP_INC:
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;
		switch ( item->id )
		{
		case ID_CHEAT_MONEY_MAX:
			set.money_amount_max += 50000 * mod;
			break;

		case ID_CHEAT_MONEY_RAND_MIN:
			set.money_amount_rand_min += 500 * mod;
			break;

		case ID_CHEAT_MONEY_RAND_MAX:
			set.money_amount_rand_max += 500 * mod;
			break;

		case ID_CHEAT_MONEY_IVAL_MIN:
			set.money_interval_rand_min += 1 * mod;
			break;

		case ID_CHEAT_MONEY_IVAL_MAX:
			set.money_interval_rand_max += 1 * mod;
			break;
		}

		switch ( item->id )
		{
		case ID_CHEAT_MONEY_MAX:
			menu_item_name_set( item, "Max money: %d", (int)set.money_amount_max );
			break;

		case ID_CHEAT_MONEY_RAND_MIN:
			menu_item_name_set( item, "Random min: %d", (int)set.money_amount_rand_min );
			break;

		case ID_CHEAT_MONEY_RAND_MAX:
			menu_item_name_set( item, "Random max: %d", (int)set.money_amount_rand_max );
			break;

		case ID_CHEAT_MONEY_IVAL_MIN:
			menu_item_name_set( item, "Interval min: %dsec", (int)set.money_interval_rand_min );
			break;

		case ID_CHEAT_MONEY_IVAL_MAX:
			menu_item_name_set( item, "Interval max: %dsec", (int)set.money_interval_rand_max );
			break;

		default:
			return 0;
		}
	}

	return 0;
}

int randammo, randammoclip;
static int menu_callback_weapons ( int op, struct menu_item *item )
{
	struct weapon_entry *weapon = (struct weapon_entry *)item->data;
	struct actor_info	*actor_info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	if ( actor_info == NULL )
		return 0;

	if ( op == MENU_OP_ENABLED )
	{
		switch ( item->id )
		{
		case ID_NONE:
			return 0;

		case ID_WEAPON_ENABLE:
			return cheat_state->_generic.weapon;

		case ID_WEAPON_RANDOM:
			return set.ammo_random;
		}

		if ( weapon == NULL )
			return 0;

		if ( set.weapon[weapon->slot] == weapon )
			return 1;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( item->id == ID_WEAPON_ENABLE )
		{
			cheat_state->_generic.weapon ^= 1;
			return 1;
		}

		if ( item->id == ID_WEAPON_RANDOM )
		{
			set.ammo_random ^= 1;
			return 1;
		}

		if ( weapon == NULL )
			return 0;

		if ( set.weapon[weapon->slot] == weapon )
		{
			set.weapon[weapon->slot] = NULL;
			return 1;
		}

		set.weapon[weapon->slot] = weapon;

		if ( !cheat_state->_generic.weapon )
			return 1;

		randammo = ( rand() % set.ammo ) + 1;
		randammoclip = ( rand() % set.ammo_clip ) + 1;
		gta_weapon_set( actor_info, set.weapon[weapon->slot]->slot, set.weapon[weapon->slot]->id, randammo, randammoclip );
		return 1;
	}

	return 0;
}

static int menu_callback_patches ( int op, struct menu_item *item )
{
	struct patch_set	*patch = &set.patch[item->id];

	if ( op == MENU_OP_ENABLED )
	{
		return patch->installed;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( patch->installed || patch->failed )
			patcher_remove( patch );
		else
			patcher_install( patch );

		return 1;
	}

	return 0;
}

static int menu_callback_samppatches ( int op, struct menu_item *item )
{
	if (item->id == ID_MENU_NETPATCHES_INPACKET || item->id == ID_MENU_NETPATCHES_INRPC ||
		item->id == ID_MENU_NETPATCHES_OUTPACKET || item->id == ID_MENU_NETPATCHES_OUTRPC)
		return 0;

	struct patch_set	*patch = &set.sampPatch[item->id];
	if ( op == MENU_OP_ENABLED )
	{
		return patch->installed;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( patch->installed || patch->failed )
			patcher_remove( patch );
		else
			patcher_install( patch );

		return 1;
	}

	return 0;
}

static int menu_callback_vehicles ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_ENABLED )
	{
		switch ( item->id )
		{
		case ID_VEHICLES_IWARP:
			return cheat_state->_generic.vehicles_warp_invert;

		case ID_VEHICLES_FREEZE:
			return cheat_state->_generic.vehicles_freeze;
		}
	}
	else if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case ID_VEHICLES_IWARP:
			cheat_state->_generic.vehicles_warp_invert ^= 1;
			break;

		case ID_VEHICLES_FREEZE:
			cheat_state->_generic.vehicles_freeze ^= 1;
			break;

		default:
			return 0;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_vehicles_sub ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT && item->id != ID_NONE )
	{
		struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
		struct vehicle_info *info = vehicle_info_get( item->id, VEHICLE_ALIVE | ((cheat_state->_generic.vehicles_freeze || !cheat_state->_generic.vehicles_warp_invert) ? 0 : VEHICLE_EMPTY) );
		float				pos[3];

		if ( vect3_near_zero( &info->base.matrix[4 * 3]) )
		{
			cheat_state_text( "Vehicle does not exist." );
			return 1;
		}


		if ( info != NULL && self != NULL )
		{
			if ( cheat_state->_generic.vehicles_warp_invert )
			{
				vect3_copy( &self->base.matrix[4 * 3], pos );
				pos[0] += sinf( -self->fCurrentRotation ) * 5.0f;
				pos[1] += cosf( -self->fCurrentRotation ) * 5.0f;
				pos[2] += 0.5f;
				cheat_vehicle_teleport( info, pos, gta_interior_id_get() );

				matrix_identity( info->base.matrix );
				vect3_copy( pos, &info->base.matrix[4 * 3] );
				vect3_mult( info->speed, 0.0f, info->speed );
				info->speed[2] = 0.05f;
				vect3_mult( info->spin, 0.0f, info->spin );
			}
			else
			{
				vect3_copy( &info->base.matrix[4 * 3], pos );
				pos[2] += 1.5f;
				cheat_teleport( pos, info->base.interior_id );
			}
		}
		else
		{
			if ( self == NULL )
			{
				cheat_state_text( "You are dead." );
			}
			else
			{
				if ( vehicle_info_get(item->id, 0) == NULL )
					cheat_state_text( "Vehicle not found." );
				else if ( vehicle_info_get(item->id, VEHICLE_ALIVE) == NULL )
					cheat_state_text( "Vehicle is destroyed." );
			}
		}

		return 1;
	}

	return 0;
}

static int menu_callback_misc ( int op, struct menu_item *item )
{
	int mod;

	if ( op == MENU_OP_ENABLED )
	{
		switch ( item->id )
		{
		case ID_MISC_HUDTEXT:
			return set.d3dtext_hud;

		case ID_MISC_BAD_WEAPONS:
			return cheat_state->_generic.weapon_disable;

		case ID_MISC_TRAILERS:
			return set.trailer_support;

		case ID_MISC_FPSLIMIT:
			return 0;

		case ID_MISC_TOGGLEWINDOWED:
			return set.window_mode;
		}
	}
	else if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case ID_MISC_COORDS:
			{
				float	*pos =
					( cheat_state->state == CHEAT_STATE_VEHICLE )
						? cheat_state->vehicle.coords : cheat_state->actor.coords;
				Log( "static_teleport_name[] = \"\"" );
				Log( "static_teleport_pos[] = %.2f %.2f %.2f   %d", pos[0], pos[1], pos[2], gta_interior_id_get() );
				cheat_state_text( "Current coordinates written to log file." );
			}
			break;

		case ID_MISC_RELOAD:
			ini_reload();
			break;

		case ID_MISC_HUDTEXT:
			set.d3dtext_hud ^= 1;
			break;

		case ID_MISC_BAD_WEAPONS:
			cheat_state->_generic.weapon_disable ^= 1;
			break;

		case ID_MISC_TRAILERS:
			set.trailer_support ^= 1;
			break;

		case ID_MISC_TOGGLEWINDOWED:
			toggleWindowedMode();
			break;

		default:
			return 0;
		}

		return 1;
	}
	else if ( op == MENU_OP_DEC || MENU_OP_INC )
	{
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;
		if ( item->id == ID_MISC_FPSLIMIT )
		{
			set.fps_limit += (int)mod;
			menu_item_name_set( item, "FPS Limit: %d", set.fps_limit );
		}
	}

	return 0;
}

#ifdef __CHEAT_VEHRECORDING_H__
static int menu_callback_routes_drop ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		if ( item->id == ID_NONE )
			return 1;

		// > 9, because "Delete '.'"
		if ( item->name != NULL && strlen(item->name) > 9 )
		{
			// Remove "Delete '%s'"
			char tableName[64];
			_snprintf_s( tableName, sizeof(tableName)-1, "%s", (item->name+8) );
			tableName[ (strlen(item->name)-9) ] = NULL; // remove the last '
			rec_sqlite_dropTable( tableName );

			// reload menu
			if ( item->menu != NULL )
				menu_routes_drop_populate( item->menu );
			return 1;
		}
	}
	return 0;
}

static int menu_callback_routes_load ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		if ( item->id == ID_NONE )
			return 1;

		if ( item->name != NULL && strlen(item->name) > 0 )
		{
			rec_sqlite_loadTable( (char*)item->name );
			return 1;
		}
	}
	return 0;
}

static int menu_callback_routes ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_ENABLED )
	{
		if ( item->id == ID_ROUTES_ACTIVATED )
			return set.recording_activated;
		return 0;
	}
	if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case ID_ROUTES_ACTIVATED:
			set.recording_activated ^= 1;
			break;
		case ID_ROUTES_WRITE:
			rec_sqlite_writeTable();
			break;
		case ID_ROUTES_OPTIMIZE:
			rec_sqlite_optimizeDatabase();
			break;
		default:
			return 0;
		}
		return 1;
	}
	return 0;
}
#endif

static int menu_callback_sampmisc ( int op, struct menu_item *item )
{
	if ( g_SAMP == NULL )
		return 0;

	int mod;

	switch ( op )
	{
	case MENU_OP_ENABLED:
		{
			switch ( item->id )
			{
			case ID_MENU_SAMPMISC_FAKE_KILL:
				return 0;

			case ID_MENU_SAMPMISC_SPOOF_WEAPON:
				return cheat_state->_generic.spoof_weapon == (int)( UINT_PTR ) item->data;

			case ID_MENU_SAMPMISC_SAMP_INFO_LIST:
				return cheat_state->player_info_list;

			case ID_MENU_SAMPMISC_CHAT_TEXT:
				return ( g_Chat == NULL ) ? 0 : !g_Chat->iChatWindowMode;

			case ID_MENU_SAMPMISC_CHAT_TEXTLINES:
				return 0;

			case ID_MENU_SAMPMISC_SAMP_DRUNK:
				return ( g_Players != NULL && g_Players->pLocalPlayer != NULL && 
					g_Players->pLocalPlayer->pSAMP_Actor != NULL && 
					g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel > 2300 ) ? 1 : 0;

			case ID_MENU_SAMPMISC_RENDEROBJTXT:
				return cheat_state->_generic.objecttexts;

			case ID_MENU_SAMPMISC_RENDERPCKTXT:
				return cheat_state->_generic.pickuptexts;

			case ID_MENU_SAMPMISC_M0DCOMMANDS:
				return g_m0dCommands;

			case ID_MENU_SAMPMISC_EXTRAGM:
				return set.enable_extra_godmode;
			}
		}

	case MENU_OP_SELECT:
		{
			switch ( item->id )
			{
			case ID_MENU_SAMPMISC_SAMP_INFO_LIST:
				cheat_state->player_info_list ^= 1;
				break;

			case ID_MENU_SAMPMISC_CHAT_TEXT:
				if ( g_Chat != NULL )
					g_Chat->iChatWindowMode ^= 1;
				break;

			case ID_MENU_SAMPMISC_SAMP_DRUNK:
				if ( g_Players != NULL && g_Players->pLocalPlayer != NULL && 
					g_Players->pLocalPlayer->pSAMP_Actor != NULL )
				{
					if ( g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel > 0 )
						g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel = 0;
					else
						g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel = 30000 + (rand()%2000);
				}
				break;

			case ID_MENU_SAMPMISC_SPOOF_WEAPON:
				if ( cheat_state->_generic.spoof_weapon == (int)(UINT_PTR) item->data )
					cheat_state->_generic.spoof_weapon = -1;
				else
					cheat_state->_generic.spoof_weapon = (int)( UINT_PTR ) item->data;
				break;

			case ID_MENU_SAMPMISC_FAKE_KILL:
				{
					struct actor_info	*info = getGTAPedFromSAMPPlayerID( (int)(UINT_PTR) item->data );
					struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
					const char			*errmsg = NULL;

					if ( g_Players == NULL )
						return 0;
					if ( g_Players->pRemotePlayer[(int)(UINT_PTR) item->data] == NULL )
						return 0;

					if ( info == NULL )
						errmsg = "Player does not exist.";
					else if ( ACTOR_IS_DEAD(info) )
						errmsg = "The player is dead.";
					if ( self == NULL )
						errmsg = "You are dead.";
					if ( g_iSpectateEnabled == 1 )
						errmsg = "You are spectating";

					if ( errmsg == NULL )
					{
						if ( cheat_state->_generic.spoof_weapon == -1 )
						{
							self->weapon_hit_type = info->weapon[info->weapon_slot].id;
						}
						else
						{
							self->weapon_hit_type = cheat_state->_generic.spoof_weapon;
						}
						self->weapon_hit_by = info;
						// self->hitpoints = 0.0f;
						sendDeath();
					}
					else
					{
						addMessageToChatWindow( errmsg );
					}
				}
				break;

			case ID_MENU_SAMPMISC_RENDEROBJTXT:
				cheat_state->_generic.objecttexts ^= 1;
				break;

			case ID_MENU_SAMPMISC_RENDERPCKTXT:
				cheat_state->_generic.pickuptexts ^= 1;
				break;

			case ID_MENU_SAMPMISC_M0DCOMMANDS:
				initChatCmds();
				break;

			case ID_MENU_SAMPMISC_EXTRAGM:
				set.enable_extra_godmode ^= 1;
				break;
			}
		}

	case MENU_OP_DEC:
	case MENU_OP_INC:
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;
		switch ( item->id )
		{
		case ID_MENU_SAMPMISC_CHAT_TEXTLINES:
			set.d3dtext_chat_lines += mod;
			menu_item_name_set( item, "Display chat lines: %d", set.d3dtext_chat_lines );
			break;
		}
		break;
	}

	/*
	return 1;
}*/
	return 0;
}

static int menu_callback_players ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_ENABLED )
	{
		if ( item->id == ID_MENU_PLAYERS_MUTE )
			return set.anti_spam;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( item->id == ID_MENU_PLAYERS_MUTE )
		{
			set.anti_spam ^= 1;
			// don't open submenu via select button
			return 1;
		}
	}
	return 0;
}

static int menu_callback_players_warp ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		struct actor_info	*actor = NULL;
		int					id = item->id;
		float				pos[3];

		if ( g_Players == NULL )
			return 0;

		if ( id == ID_NONE )
			return 0;

		if ( g_Players->iIsListed[id] != 1 )
		{
			addMessageToChatWindow( "Player does not exist." );
			return 0;
		}

		if ( g_Players->pRemotePlayer[id]->pPlayerData == NULL
		 ||	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor == NULL )
		{
			if ( vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[id]) )
			{
				addMessageToChatWindow( "Player is not streamed in." );
				return 0;
			}

			g_stStreamedOutInfo.fPlayerPos[id][1] += 1.0f;
			cheat_teleport( g_stStreamedOutInfo.fPlayerPos[id], 0 );
			return 0;
		}

		if ( !getPlayerPos(id, pos) )
		{
			addMessageToChatWindow( "Bad player info." );
			return 0;
		}

		if ( g_Players->pRemotePlayer[id]->pPlayerData != NULL
		 &&	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor != NULL )
			actor = g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor->pGTA_Ped;

		if ( actor != NULL && ACTOR_IS_DEAD(actor) )
		{
			addMessageToChatWindow( "Player is dead." );
			return 0;
		}

		pos[1] += 1.0f;
		cheat_teleport( pos, actor->base.interior_id );

		return 1;
	}

	return 0;
}

static int menu_callback_players_vehwarp ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		struct actor_info	*actor = NULL;
		int					id = item->id;

		// safety checking
		if ( g_Players == NULL )
			return 0;
		if ( id == ID_NONE )
			return 0;

		if ( g_Players->pRemotePlayer[id]->pPlayerData != NULL
		 &&	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor != NULL )
			actor = g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor->pGTA_Ped;
		if ( actor == NULL )
			return 0;
		if ( actor->vehicle == NULL )
			return 0;

		if ( g_Players->iIsListed[id] != 1 )
		{
			addMessageToChatWindow( "Player does not exist." );
			return 0;
		}

		if ( g_Players->pRemotePlayer[id]->pPlayerData == NULL
		 ||	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor == NULL )
		{
			addMessageToChatWindow( "Player is not streamed in." );
			return 0;
		}

		if ( actor->vehicle->hitpoints == 0.0f )
		{
			addMessageToChatWindow( "Vehicle is destroyed" );
			return 0;
		}

		if ( cheat_state->actor.air_brake )
		{
			addMessageToChatWindow( "On foot airbrake must be disabled" );
			return 0;
		}

		// if they are in a vehicle, let's GOOOO
		if ( g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_DRIVER
		 ||	 g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_PASSENGER )
		{
			//need car id in memory for vehicleJumper
			if ( g_Players->pRemotePlayer[id] != NULL
			 &&	 g_Players->pRemotePlayer[id]->pPlayerData != NULL
			 &&	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Vehicle != NULL
			 &&	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle != NULL )
			{
				vehicleJumper( (int)(((DWORD) g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle) -
							   (DWORD) pool_vehicle->start) / 2584 );
			}
		}
		else
		{
			addMessageToChatWindow( "The player is not in a vehicle" );
			return 0;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_vehicles_instant ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		int id = item->id;

		if ( g_Vehicles == NULL )
			return 0;

		if ( id == ID_NONE )
			return 0;

		if ( g_Vehicles->iIsListed[id] != 1 )
		{
			addMessageToChatWindow( "Vehicle does not exist." );
			return 0;
		}

		if ( g_Vehicles->pGTA_Vehicle[id] == NULL )
		{
			addMessageToChatWindow( "Vehicle is unstreamed" );
			return 0;
		}

		if ( g_Vehicles->pGTA_Vehicle[id]->hitpoints == 0.0f )
		{
			addMessageToChatWindow( "Vehicle is destroyed" );
			return 0;
		}

		if ( cheat_state->actor.stick )
		{
			addMessageToChatWindow( "On foot stick must be disabled" );
			return 0;
		}

		if ( cheat_state->actor.air_brake )
		{
			addMessageToChatWindow( "On foot airbrake must be disabled" );
			return 0;
		}

		int jump_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[id]) - (DWORD) pool_vehicle->start ) / 2584;
		vehicleJumper( jump_id );

		return 1;
	}

	return 0;
}

static int menu_callback_teleports ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		cheat_teleport_history_save();
		cheat_state_text( "Teleported to: %s.", set.static_teleport_name[item->id] );
		cheat_teleport( set.static_teleport[item->id].pos, set.static_teleport[item->id].interior_id );
		return 1;
	}

	return 0;
}

static int menu_callback_interiors ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		if ( g_SAMP != NULL )
		{
			sampPatchDisableInteriorUpdate( 1 );
			sendSetInterior( interiors_list[item->id].interior_id );
		}

		cheat_state_text( "Teleported to: %s.", interiors_list[item->id].interior_name );
		cheat_teleport( interiors_list[item->id].pos, interiors_list[item->id].interior_id );
		if ( g_SAMP != NULL )
			sampPatchDisableInteriorUpdate( 0 );
		return 1;
	}

	return 0;
}

static int menu_callback_specialaction ( int op, struct menu_item *item )
{
	if ( g_Players->pLocalPlayer == NULL )
		return 0;

	int		id = item->id;
	uint8_t specialaction = g_Players->pLocalPlayer->onFootData.byteSpecialAction;

	if ( op == MENU_OP_ENABLED )
	{
		switch ( id )
		{
		case ID_MENU_SPECIAL_ACTION_NONE:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_NONE )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_USEJETPACK:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_USEJETPACK )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DANCE1:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DANCE1 )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DANCE2:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DANCE2 )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DANCE3:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DANCE3 )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DANCE4:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DANCE4 )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_HANDSUP:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_HANDSUP )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_USECELLPHONE:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_USECELLPHONE )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_STOPUSECELLPHONE:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_STOPUSECELLPHONE )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DRINK_BEER:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DRINK_BEER )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_SMOKE_CIGGY:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_SMOKE_CIGGY )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DRINK_WINE:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DRINK_WINE )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DRINK_SPRUNK:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DRINK_SPRUNK )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_CUFFED:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_CUFFED )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_CARRY:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_CARRY )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_URINATE:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_URINATE )
				return 1;
			break;
		}

		return 0;
	}

	if ( op == MENU_OP_SELECT )
	{
		setSpecialAction( id );
		return 1;
	}

	return 0;
}

static int menu_callback_debug ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_ENABLED )
	{
		if ( item->id == ID_DEBUG_ENABLE )
			return cheat_state->debug_enabled;
		return 0;
	}

	if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case ID_DEBUG_ENABLE:
			cheat_state->debug_enabled ^= 1;
			break;

		case ID_DEBUG_SELF_ACTOR:
			setDebugPointer( (void *)actor_info_get(ACTOR_SELF, 0) );
			break;

		case ID_DEBUG_SELF_VEHICLE:
			setDebugPointer( (void *)vehicle_info_get(VEHICLE_SELF, 0) );
			break;

		case ID_DEBUG_SAMP_DLL:
			setDebugPointer( (void *)g_dwSAMP_Addr );
			break;

		case ID_DEBUG_SAMP_INFO:
			setDebugPointer( (void *)g_SAMP );
			break;

		case ID_DEBUG_SAMP_PLAYER_LIST:
			setDebugPointer( (void *)g_Players );
			break;

		case ID_DEBUG_SAMP_LOCAL_INFO:
			setDebugPointer( (void *)g_Players->pLocalPlayer );
			break;

		case ID_DEBUG_SAMP_CHAT_INFO:
			setDebugPointer( (void *)g_Chat );
			break;

		case ID_DEBUG_SAMP_CHAT_IPT_INFO:
			setDebugPointer( (void *)g_Input );
			break;

		case ID_DEBUG_SAMP_KILL_INFO:
			setDebugPointer( (void *)g_DeathList );
			break;

		case ID_DEBUG_SAMP_VEHICLE_LIST:
			setDebugPointer( (void *)g_Vehicles );
			break;

		case ID_DEBUG_SAMP_LOCAL_SAMPPED:
			setDebugPointer( (void *)g_Players->pLocalPlayer->pSAMP_Actor );
			break;

		default:
			return 0;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_hudindicators ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_ENABLED )
	{
		switch ( item->id )
		{
		case ID_HUDIND_BAR:
			return set.hud_draw_bar;

		case ID_HUDIND_TSHADOWS:
			return set.render_text_shadows;

		case ID_HUDIND_INV:
			return set.hud_indicator_inv;

		case ID_HUDIND_WEAPON:
			return set.hud_indicator_weapon;

		case ID_HUDIND_MONEY:
			return set.hud_indicator_money;

		case ID_HUDIND_FREEZE:
			return set.hud_indicator_freeze;

		case ID_HUDIND_INVEH_AIRBRK:
			return set.hud_indicator_inveh_airbrk;

		case ID_HUDIND_INVEH_STICK:
			return set.hud_indicator_inveh_stick;

		case ID_HUDIND_INVEH_BRKDANCE:
			return set.hud_indicator_inveh_brkdance;

		case ID_HUDIND_INVEH_SPIDER:
			return set.hud_indicator_inveh_spider;

		case ID_HUDIND_ONFOOT_FLY:
			return set.hud_indicator_onfoot_fly;

		case ID_HUDIND_INVEH_FLY:
			return set.hud_indicator_inveh_fly;

		case ID_HUDIND_ONFOOT_AIRBRK:
			return set.hud_indicator_onfoot_airbrk;

		case ID_HUDIND_ONFOOT_STICK:
			return set.hud_indicator_onfoot_stick;

		case ID_HUDIND_ONFOOT_AIM:
			return set.hud_indicator_onfoot_aim;

		case ID_HUDIND_POS:
			return set.hud_indicator_pos;

		case ID_HUDIND_FPS:
			return set.hud_fps_draw;

		case ID_HUDIND_LB_BARS:
			return set.left_bottom_bars_enable;

		case ID_HUDIND_SURF:
			return set.hud_indicator_surf;

		case ID_HUDIND_FREEZEROT:
			return set.hud_indicator_freezerot;
		//case cID_HUDIND_GHOSTMODE: // sec let me fix it..
		//	return set.new_hud_indicator_onfoot_modes;
		}
		return 0;
	}

	if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case ID_HUDIND_BAR:
			set.hud_draw_bar ^= 1;
			break;

		case ID_HUDIND_TSHADOWS:
			set.render_text_shadows ^= 1;
			break;

		case ID_HUDIND_INV:
			set.hud_indicator_inv ^= 1;
			break;

		case ID_HUDIND_WEAPON:
			set.hud_indicator_weapon ^= 1;
			break;

		case ID_HUDIND_MONEY:
			set.hud_indicator_money ^= 1;
			break;

		case ID_HUDIND_FREEZE:
			set.hud_indicator_freeze ^= 1;
			break;

		case ID_HUDIND_INVEH_AIRBRK:
			set.hud_indicator_inveh_airbrk ^= 1;
			break;

		case ID_HUDIND_INVEH_STICK:
			set.hud_indicator_inveh_stick ^= 1;
			break;

		case ID_HUDIND_INVEH_BRKDANCE:
			set.hud_indicator_inveh_brkdance ^= 1;
			break;

		case ID_HUDIND_INVEH_SPIDER:
			set.hud_indicator_inveh_spider ^= 1;
			break;

		case ID_HUDIND_ONFOOT_FLY:
			set.hud_indicator_onfoot_fly ^= 1;
			break;

		case ID_HUDIND_INVEH_FLY:
			set.hud_indicator_inveh_fly ^= 1;
			break;

		case ID_HUDIND_ONFOOT_AIRBRK:
			set.hud_indicator_onfoot_airbrk ^= 1;
			break;

		case ID_HUDIND_ONFOOT_STICK:
			set.hud_indicator_onfoot_stick ^= 1;
			break;

		case ID_HUDIND_ONFOOT_AIM:
			set.hud_indicator_onfoot_aim ^= 1;
			break;

		case ID_HUDIND_POS:
			set.hud_indicator_pos ^= 1;
			break;

		case ID_HUDIND_FPS:
			set.hud_fps_draw ^= 1;
			break;

		case ID_HUDIND_LB_BARS:
			set.left_bottom_bars_enable ^= 1;
			break;

		case ID_HUDIND_SURF:
			set.hud_indicator_surf ^= 1;
			break;

		case ID_HUDIND_FREEZEROT:
			set.hud_indicator_freezerot ^= 1;
			break;

		default:
			return 0;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_hileler(int op, struct menu_item *item)
{
	if (g_SAMP == NULL)
		return 0;

	int mod;

	switch (op)
	{
	case MENU_OP_ENABLED:
	{
		switch (item->id)
		{
		case ID_GOD_FLY:
			return cheat_state->genel.iGoDFly;
		case ID_GHOST_MODE:
			return cheat_state->genel.iGhostMode;
		case ID_TWIST_MODE:
			return cheat_state->genel.iTwistMode;
		case ID_TWIST_MODE_2:
			return cheat_state->genel.iTwistMode2;
		case ID_CAMERA_MODE:
			return cheat_state->genel.iCameraMode;
		case ID_RAND_QUATS:
			return cheat_state->genel.iRandomQuaternions;
		case ID_RAND_QUATS_FIX:
			return cheat_state->genel.iRandomQuaternionsFix;
		case ID_UPSIDE_DOWN:
			return cheat_state->genel.iUpsideDown;
		case ID_UPSIDE_DOWN_FIX:
			return cheat_state->genel.iUpsideDownFix;
		case ID_WALK_THROUGH_WALLS:
			return cheat_state->genel.iWalkThroughWalls;
		case ID_SPEED_WALK:
			return cheat_state->genel.iSpeedWalk;
		case ID_DO_NOT_SEND_KILL:
			return cheat_state->genel.iDo_Not_Send_Kill;
		case ID_SPAWN_AT_DEATH_POS:
			return cheat_state->genel.iSpawnAtDeathPos;
		case ID_MAPRUN:
			return cheat_state->genel.iMapRun;
		case ID_HP_PULSATOR:
			return cheat_state->genel.iCanPulsator;
		case ID_ARMOR_PULSATOR:
			return cheat_state->genel.iZirhPulsator;
		case ID_PLAYER_DEFORMER:
			return cheat_state->genel.iPlayerDeformer;
		case ID_FAST_RESPAWN:
			return cheat_state->genel.iFastRespawn;
		case ID_NO_FALL_ANIMATION:
			return cheat_state->genel.iNoFall;
		case ID_ANTI_STUN:
			return cheat_state->genel.iAntiStun;
		default: return 0;
		}
	}
	case MENU_OP_SELECT:
		switch (item->id)
		{
		case ID_GOD_FLY:
			return cheat_state->genel.iGoDFly ^= 1;
			break;
		case ID_GHOST_MODE:
			cheat_state->genel.iGhostMode ^= 1;
			break;
		case ID_TWIST_MODE:
			cheat_state->genel.iTwistMode ^= 1;
			break;
		case ID_TWIST_MODE_2:
			cheat_state->genel.iTwistMode2 ^= 1;
			break;
		case ID_CAMERA_MODE:
			cheat_state->genel.iCameraMode ^= 1;
			break;
		case ID_RAND_QUATS:
			cheat_state->genel.iRandomQuaternions ^= 1;
			break;
		case ID_RAND_QUATS_FIX:
			cheat_state->genel.iRandomQuaternionsFix ^= 1;
			break;
		case ID_UPSIDE_DOWN:
			cheat_state->genel.iUpsideDown ^= 1;
			break;
		case ID_UPSIDE_DOWN_FIX:
			cheat_state->genel.iUpsideDownFix ^= 1;
			break;
		case ID_WALK_THROUGH_WALLS:
			cheat_state->genel.iWalkThroughWalls ^= 1;
			break;
		case ID_SPEED_WALK:
			cheat_state->genel.iSpeedWalk ^= 1;
			break;
		case ID_DO_NOT_SEND_KILL:
			cheat_state->genel.iDo_Not_Send_Kill ^= 1;
			break;
		case ID_SPAWN_AT_DEATH_POS:
			cheat_state->genel.iSpawnAtDeathPos ^= 1;
			break;
		case ID_MAPRUN:
			cheat_state->genel.iMapRun ^= 1;
			break;
		case ID_HP_PULSATOR:
			cheat_state->genel.iCanPulsator ^= 1;
			break;
		case ID_ARMOR_PULSATOR:
			cheat_state->genel.iZirhPulsator ^= 1;
			break;
		case ID_PLAYER_DEFORMER:
			cheat_state->genel.iPlayerDeformer ^= 1;
			break;
		case ID_FAST_RESPAWN:
			cheat_state->genel.iFastRespawn ^= 1;
			break;
		case ID_NO_FALL_ANIMATION:
			cheat_state->genel.iNoFall ^= 1;
			break;
		case ID_ANTI_STUN:
			cheat_state->genel.iAntiStun ^= 1;
			break;
		}
	}
}
static int menu_callback_arachileleri(int op, struct menu_item *item)
{
	if (g_SAMP == NULL)
		return 0;

	int mod;

	switch (op)
	{
	case MENU_OP_ENABLED:
	{
		switch (item->id)
		{
		case ID_MAKE_ZERO_HP_FOR_CARS:
			return set.MakeZeroHPforCars;
		case ID_CAR_SHOOTER:
			return cheat_state->Arac.iCarShooter;
		case ID_CAR_SHOOTER2:
			return cheat_state->Arac.iCarShooter2;
		case ID_CAR_SHOOTER3:
			return cheat_state->Arac.iCarShooter3;
		case ID_CAR_SHOOTER4:
			return cheat_state->Arac.iCarShooter4;
		case ID_CAR_CIRCLE:
			return cheat_state->Arac.iCarCircle;
		case ID_CAR_CIRCLE2:
			return cheat_state->Arac.iCarCircle2;
		case ID_CAR_FOLLOWS:
			return cheat_state->Arac.iCarFollows;
		case ID_CAR_FOLLOWS2:
			return cheat_state->Arac.iCarFollows2;
		case ID_CAR_FOLLOWS3:
			return cheat_state->Arac.iCarFollows3;
		case ID_CAR_SMOKING:
			return cheat_state->Arac.iCarSmoking;
		case ID_CAR_SUN:
			return cheat_state->Arac.iCarSun;
		case ID_CAR_POSITION_LAGGER:
			return cheat_state->Arac.iCarPosLagger;
		case ID_CRAZY_CAR:
			return cheat_state->Arac.CrazyCar1;
		case ID_CRAZY_CAR2:
			return cheat_state->Arac.CrazyCar2;
		case ID_CRAZY_CAR3:
			return cheat_state->Arac.CrazyCar3;
		case ID_CRAZY_CAR4:
			return cheat_state->Arac.CrazyCar4;
		case ID_VEHICLE_COMPONENT_FLOODER:
			return cheat_state->Arac.iCarFlooder;
		case ID_DELETE_CARS:
			return cheat_state->Arac.DeleteCars;
		case ID_REMOVE_CARS:
			return cheat_state->Arac.RemoveCars;
		case ID_PICK_CAR:
			return cheat_state->Arac.CarPick;
		case ID_EX_ATTACKER:
			return cheat_state->Arac.iExAttacker;
		case ID_CAR_COLORIZE:
			return cheat_state->Arac.CarColorize;
		case ID_CAR_WHEELIZE:
			return cheat_state->Arac.iCarWheelize;
		case ID_CAR_BLACK_WHITE:
			return cheat_state->Arac.BlackWhiteCars;
		case ID_CAR_PINK:
			return cheat_state->Arac.PinkCars;
		case ID_CAR_FUCKER:
			return cheat_state->Arac.iCarFucker;
		case ID_FOLLOW_TROLL:
			return cheat_state->Arac.iCarFollowTroll;
		case ID_ZFOLLOW_TROLL:
			return cheat_state->Arac.iCarZTroll;
		case ID_CAR_UNNAMED_TROLL:
			return cheat_state->Arac.iCarUnnamedTroll;
		case ID_EXPLODE_CARS:
			return cheat_state->Arac.iExplodeCars;
		case ID_HOP_CARS:
			return cheat_state->Arac.iHopCars;
		case ID_RESPAWN_CARS:
			return cheat_state->Arac.iRespawnCars;
		case ID_CAR_FLOATING:
			return cheat_state->Arac.iCarFloating;
		case ID_CAR_FLOATING2:
			return cheat_state->Arac.iCarFloating2;
		case ID_CAR_FLOATING3:
			return cheat_state->Arac.iCarFloating3;
		case ID_CAR_TORNADO:
			return cheat_state->Arac.iCarsTornado;
		case ID_CAR_TORNADO2:
			return cheat_state->Arac.iCarsTornado2;
		case ID_CARS_MAGNET:
			return cheat_state->Arac.iCarsMagnet;
		case ID_CAR_FUCKER2:
			return cheat_state->Arac.iCarsFucker2;
		case ID_CAR_FUCKER3:
			return cheat_state->Arac.iCarsFucker3;
		case ID_CAR_LINE:
			return cheat_state->Arac.iCarsLine;
		case ID_SHAKING_CARS:
			return cheat_state->Arac.iShakingCars;
		case ID_CAR_SPINNING:
			return cheat_state->Arac.iSpinningCars;
		case ID_CARS_TOWER:
			return cheat_state->Arac.iCarsTower;
		case ID_CARS_FLYING:
			return cheat_state->Arac.iFlyingCars;
		case ID_CARS_FALLING:
			return cheat_state->Arac.iFallingCars;
		default: return 0;
		}
	}
	case MENU_OP_SELECT:
		switch (item->id)
		{
		case ID_MAKE_ZERO_HP_FOR_CARS:
			set.MakeZeroHPforCars ^= 1;
			break;
		case ID_CAR_SHOOTER:
			cheat_state->Arac.iCarShooter ^= 1;
			break;
		case ID_CAR_SHOOTER2:
			cheat_state->Arac.iCarShooter2 ^= 1;
			break;
		case ID_CAR_SHOOTER3:
			cheat_state->Arac.iCarShooter3 ^= 1;
			break;
		case ID_CAR_SHOOTER4:
			cheat_state->Arac.iCarShooter4 ^= 1;
			break;
		case ID_CAR_FOLLOWS:
			cheat_state->Arac.iCarFollows ^= 1;
			break;
		case ID_CAR_FOLLOWS2:
			cheat_state->Arac.iCarFollows2 ^= 1;
			break;
		case ID_CAR_FOLLOWS3:
			cheat_state->Arac.iCarFollows3 ^= 1;
			break;
		case ID_CAR_CIRCLE:
			cheat_state->Arac.iCarCircle ^= 1;
			break;
		case ID_CAR_CIRCLE2:
			cheat_state->Arac.iCarCircle2 ^= 1;
			break;
		case ID_CAR_SMOKING:
			cheat_state->Arac.iCarSmoking ^= 1;
			break;
		case ID_CAR_SUN:
			cheat_state->Arac.iCarSun ^= 1;
			break;
		case ID_CAR_POSITION_LAGGER:
			cheat_state->Arac.iCarPosLagger ^= 1;
			break;
		case ID_CRAZY_CAR:
			cheat_state->Arac.CrazyCar1 ^= 1;
			break;
		case ID_CRAZY_CAR2:
			cheat_state->Arac.CrazyCar2 ^= 1;
			break;
		case ID_CRAZY_CAR3:
			cheat_state->Arac.CrazyCar3 ^= 1;
			break;
		case ID_CRAZY_CAR4:
			cheat_state->Arac.CrazyCar4 ^= 1;
			break;
		case ID_VEHICLE_COMPONENT_FLOODER:
			cheat_state->Arac.iCarFlooder ^= 1;
			break;
		case ID_DELETE_CARS:
			cheat_state->Arac.DeleteCars ^= 1;
			break;
		case ID_REMOVE_CARS:
			cheat_state->Arac.RemoveCars ^= 1;
			break;
		case ID_PICK_CAR:
			cheat_state->Arac.CarPick ^= 1;
			break;
		case ID_EX_ATTACKER:
			cheat_state->Arac.iExAttacker ^= 1;
			break;
		case ID_CAR_COLORIZE:
			cheat_state->Arac.CarColorize ^= 1;
			break;
		case ID_CAR_WHEELIZE:
			cheat_state->Arac.iCarWheelize ^= 1;
			break;
		case ID_CAR_BLACK_WHITE:
			cheat_state->Arac.BlackWhiteCars ^= 1;
			break;
		case ID_CAR_PINK:
			cheat_state->Arac.PinkCars ^= 1;
			break;
		case ID_CAR_FUCKER:
			cheat_state->Arac.iCarFucker ^= 1;
			break;
		case ID_FOLLOW_TROLL:
			cheat_state->Arac.iCarFollowTroll ^= 1;
			break;
		case ID_ZFOLLOW_TROLL:
			cheat_state->Arac.iCarZTroll ^= 1;
			break;
		case ID_CAR_UNNAMED_TROLL:
			cheat_state->Arac.iCarUnnamedTroll ^= 1;
			break;
		case ID_EXPLODE_CARS:
			cheat_state->Arac.iExplodeCars ^= 1;
			break;
		case ID_HOP_CARS:
			cheat_state->Arac.iHopCars ^= 1;
			break;
		case ID_RESPAWN_CARS:
			cheat_state->Arac.iRespawnCars ^= 1;
			break;
		case ID_CAR_FLOATING:
			cheat_state->Arac.iCarFloating ^= 1;
			break;
		case ID_CAR_FLOATING2:
			cheat_state->Arac.iCarFloating2 ^= 1;
			break; 
		case ID_CAR_FLOATING3:
			cheat_state->Arac.iCarFloating3 ^= 1;
			break;
		case ID_CAR_TORNADO:
			cheat_state->Arac.iCarsTornado ^= 1;
			break;
		case ID_CAR_TORNADO2:
			cheat_state->Arac.iCarsTornado2 ^= 1;
			break;
		case ID_CARS_MAGNET:
			cheat_state->Arac.iCarsMagnet ^= 1;
			break;
		case ID_CAR_FUCKER2:
			cheat_state->Arac.iCarsFucker2 ^= 1;
			break;
		case ID_CAR_FUCKER3:
			cheat_state->Arac.iCarsFucker3 ^= 1;
			break;
		case ID_CAR_LINE:
			cheat_state->Arac.iCarsLine ^= 1;
			break;
		case ID_CAR_SPINNING:
			cheat_state->Arac.iSpinningCars ^= 1;
			break;
		case ID_SHAKING_CARS:
			cheat_state->Arac.iShakingCars ^= 1;
			break;
		case ID_CARS_TOWER:
			cheat_state->Arac.iCarsTower ^= 1;
			break;
		case ID_CARS_FLYING:
			cheat_state->Arac.iFlyingCars ^= 1;
			break;
		case ID_CARS_FALLING:
			cheat_state->Arac.iFallingCars ^= 1;
			break;
		}
	}
}
static int menu_callback_silah_hileleri(int op, struct menu_item *item)
{
	if (g_SAMP == NULL)
		return 0;

	int mod;

	switch (op)
	{
	case MENU_OP_ENABLED:
	{
		switch (item->id)
		{
		case ID_AUTO2_2:
			return cheat_state->Silah.iAuto2_2;
		case ID_AUTO_SAWN_DEAGLE:
			return cheat_state->Silah.iSawnDeagle;
		case ID_DOUBLE_GUN:
			return cheat_state->Silah.iDoubleGun1;
		case ID_DOUBLE_GUN_2:
			return cheat_state->Silah.iDoubleGun2;
		case ID_AUTO_CBUG:
			return cheat_state->Silah.iAutoCbug1;
		case ID_AUTO_CBUG2:
			return cheat_state->Silah.iAutoCbug2;
		case ID_RAPID_FIRE:
			return cheat_state->Silah.iRapidFire;
		case ID_NO_RECOIL:
			return cheat_state->Silah.iNoRecoil;
		case ID_NO_RELOAD_BUG:
			return cheat_state->Silah.iNoReloadBug;
		case ID_RETURN_THE_DAMAGE:
			return cheat_state->Silah.iReturnTheDamage;
		case ID_BYPASS_WEAPON_CHEAT:
			return cheat_state->Silah.iBypassWeapon;
		case ID_WEAPON_DAMAGE:
			return set.WeaponCheats.Weapon_Damage;
		default: return 0;
		}
	}
	case MENU_OP_SELECT:
		switch (item->id)
		{
		case ID_AUTO2_2:
			cheat_state->Silah.iAuto2_2 ^= 1;
			break;
		case ID_AUTO_SAWN_DEAGLE:
			cheat_state->Silah.iSawnDeagle ^= 1;
			break;
		case ID_DOUBLE_GUN:
			cheat_state->Silah.iDoubleGun1 ^= 1;
			break;
		case ID_DOUBLE_GUN_2:
			cheat_state->Silah.iDoubleGun2 ^= 1;
			break;
		case ID_AUTO_CBUG:
			cheat_state->Silah.iAutoCbug1 ^= 1;
			break;
		case ID_AUTO_CBUG2:
			cheat_state->Silah.iAutoCbug2 ^= 1;
			break;
		case ID_RAPID_FIRE:
			cheat_state->Silah.iRapidFire ^= 1;
			break;
		case ID_NO_RECOIL:
			cheat_state->Silah.iNoRecoil ^= 1;
			break;
		case ID_NO_RELOAD_BUG:
			cheat_state->Silah.iNoReloadBug ^= 1;
			break;
		case ID_RETURN_THE_DAMAGE:
			cheat_state->Silah.iReturnTheDamage ^= 1;
			break;
		case ID_BYPASS_WEAPON_CHEAT:
			cheat_state->Silah.iBypassWeapon ^= 1;
			break;
		case ID_WEAPON_DAMAGE:
			set.WeaponCheats.Weapon_Damage ^= 1;
			break;

		}
	case MENU_OP_DEC:
	case MENU_OP_INC:
		mod = (op == MENU_OP_DEC) ? -1 : 1;
		switch (item->id)
		{
 
		case ID_WEAPON_DAMAGE:
			set.WeaponCheats.Weapon_Damage += mod;
			if (set.WeaponCheats.Weapon_Damage < 0)
			{
				set.WeaponCheats.Weapon_Damage = 0;
			}
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
			menu_item_name_set(item, "Weapon Damage: %d /Per Shot", (int)set.WeaponCheats.Weapon_Damage);
			if (set.WeaponCheats.Weapon_Damage > 5)
				menu_item_name_set(item, "Weapon Damage: %d / Server can detect you!", (int)set.WeaponCheats.Weapon_Damage);
#else
			menu_item_name_set(item, "Silah Hasarý Katlayýcý: %d kat hasar/Atýþ baþý", (int)set.WeaponCheats.Weapon_Damage);
			if (set.WeaponCheats.Weapon_Damage > 5)
				menu_item_name_set(item, "Hasar Katý: %d | Sunucu tarafýndan fark edilebilirsin.", (int)set.WeaponCheats.Weapon_Damage);
#endif
			break;
		}
		break;
	}

}

static int menu_callback_wallhacklar(int op, struct menu_item *item)
{
	if (g_SAMP == NULL)
		return 0;

	int mod;

	switch (op)
	{
	case MENU_OP_ENABLED:
	{
		switch (item->id)
		{
		case ID_BLACK_CHAMS:
			return cheat_state->Wallhack.iBlackChams;

		case ID_BLACK_CHAMS_WIREFRAME:
			return cheat_state->Wallhack.iBlackChamsWireFrame;

		case ID_BLACK_CHAMS_WEAPONS:
			return cheat_state->Wallhack.iBlackChams_Weapons;

		case ID_BLACK_CHAMS_WEAPONS_WIREFRAME:
			return cheat_state->Wallhack.iBlackChams_Weapons_WireFrame;
			///////////////////////////////////////////////////////////////////////////////
		case ID_RED_CHAMS:
			return cheat_state->Wallhack.iRedChams;

		case ID_RED_CHAMS_WIREFRAME:
			return cheat_state->Wallhack.iRedChams_WireFrame;

		case ID_RED_CHAMS_WEAPONS:
			return cheat_state->Wallhack.iRedChams_Weapons;

		case ID_RED_CHAMS_WEAPONS_WIREFRAME:
			return cheat_state->Wallhack.iRedChams_Weapons_WireFrame;
			///////////////////////////////////////////////////////////////////////////////
		case ID_GREEN_CHAMS:
			return cheat_state->Wallhack.iGreenChams;

		case ID_GREEN_CHAMS_WIREFRAME:
			return cheat_state->Wallhack.iGreenChamsWireFrame;

		case ID_GREEN_CHAMS_WEAPONS:
			return cheat_state->Wallhack.iGreenChams_Weapons;

		case ID_GREEN_CHAMS_WEAPONS_WIREFRAME:
			return cheat_state->Wallhack.iGreenChams_Weapons_WireFrame;
			///////////////////////////////////////////////////////////////////////////////
		case ID_BLUE_CHAMS:
			return cheat_state->Wallhack.iBlueChams;

		case ID_BLUE_CHAMS_WIREFRAME:
			return cheat_state->Wallhack.iBlueChams_WireFrame;

		case ID_BLUE_CHAMS_WEAPONS:
			return cheat_state->Wallhack.iBlueChams_Weapons;

		case ID_BLUE_CHAMS_WEAPONS_WIREFRAME:
			return cheat_state->Wallhack.iBlueChams_Weapons_WireFrame;
			///////////////////////////////////////////////////////////////////////////////
		case ID_ORIGINAL_CHAMS:
			return cheat_state->Wallhack.iOrijinalChams;
		case ID_ORIGINAL_CHAMS_WIREFRAME:
			return cheat_state->Wallhack.iOrijinal_Chams_WireFrame;
		case ID_ORIGINAL_WEAPONS_CHAMS:
			return cheat_state->Wallhack.iOrijinal_Weapons;
		case ID_ORIGINAL_WEAPONS_WIREFRAME:
			return cheat_state->Wallhack.iOrijinal_Weapons_WireFrame;
			///////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////
		case ID_GOLD_CHAMS:
			return cheat_state->Wallhack.iGoldChams;
		case ID_GOLD_CHAMS_WIREFRAME:
			return cheat_state->Wallhack.iGoldChams_WireFrame;
		case ID_GOLD_CHAMS_WEAPONS:
			return cheat_state->Wallhack.iGoldChams_Weapons;
		case ID_GOLD_CHAMS_WEAPONS_WIREFRAME:
			return cheat_state->Wallhack.iGoldChams_Weapons_WireFrame;
			///////////////////////////////////////////////////////////////////////////////
		/*case ID_LAGSHOT_POINT:
			return cheat_state->genel.iLagShootPoint;*/
		case ID_DRAW_ADMINS:
			return set.iDraw_Admins;
		case ID_DRAW_FRIENDS:
			return set.D3DFeatures.bDrawFriendTag;
		case ID_BONE_ESP:
			return cheat_state->Wallhack.iBoneESP;
		case ID_TRACER_ESP:
			return cheat_state->Wallhack.iTracerESP;
		case ID_PLAYER_BOX_ESP:
			return cheat_state->Wallhack.iPlayerBoxESP;
		case ID_ADMINS_LIST:
			return cheat_state->Wallhack.iAdminListesi;
		case ID_FRIENDS_LIST:
			return cheat_state->Wallhack.iArkadasListesi;
		case ID_3D_INFORMER:
			return cheat_state->Wallhack.iD3DInformer;
		case ID_WEAPON_INFO:
			return set.seeWeaponTags;
	/*	case ID_STATUS_INFO:
			return set.statusTag;*/
		case ID_RENDER_NEW_HUD:
			return set.D3DFeatures.bDrawHUDLikeLiquid;
			/////////////////////////////////////////////////////////////////////////////
		default: return 0;
		}
	}
	case MENU_OP_SELECT:
		switch (item->id)
		{
		case ID_BLACK_CHAMS:
			cheat_state->Wallhack.iBlackChams ^= 1;
			break;
		case ID_BLACK_CHAMS_WIREFRAME:
			cheat_state->Wallhack.iBlackChamsWireFrame ^= 1;
			break;
		case ID_BLACK_CHAMS_WEAPONS:
			cheat_state->Wallhack.iBlackChams_Weapons ^= 1;
			break;
		case ID_BLACK_CHAMS_WEAPONS_WIREFRAME:
			cheat_state->Wallhack.iBlackChams_Weapons_WireFrame ^= 1;
			break;
			//////////////////////////////////////
		case ID_RED_CHAMS:
			cheat_state->Wallhack.iRedChams ^= 1;
			break;
		case ID_RED_CHAMS_WIREFRAME:
			cheat_state->Wallhack.iRedChams_WireFrame ^= 1;
			break;
		case ID_RED_CHAMS_WEAPONS:
			cheat_state->Wallhack.iRedChams_Weapons ^= 1;
			break;
		case ID_RED_CHAMS_WEAPONS_WIREFRAME:
			cheat_state->Wallhack.iRedChams_Weapons_WireFrame ^= 1;
			break;
			//////////////////////////////////////
		case ID_GREEN_CHAMS:
			cheat_state->Wallhack.iGreenChams ^= 1;
			break;
		case ID_GREEN_CHAMS_WIREFRAME:
			cheat_state->Wallhack.iGreenChamsWireFrame ^= 1;
			break;
		case ID_GREEN_CHAMS_WEAPONS:
			cheat_state->Wallhack.iGreenChams_Weapons ^= 1;
			break;
		case ID_GREEN_CHAMS_WEAPONS_WIREFRAME:
			cheat_state->Wallhack.iGreenChams_Weapons_WireFrame ^= 1;
			break;
			//////////////////////////////////////
		case ID_BLUE_CHAMS:
			cheat_state->Wallhack.iBlueChams ^= 1;
			break;
		case ID_BLUE_CHAMS_WIREFRAME:
			cheat_state->Wallhack.iBlueChams_WireFrame ^= 1;
			break;
		case ID_BLUE_CHAMS_WEAPONS:
			cheat_state->Wallhack.iBlueChams_Weapons ^= 1;
			break;
		case ID_BLUE_CHAMS_WEAPONS_WIREFRAME:
			cheat_state->Wallhack.iBlueChams_Weapons_WireFrame ^= 1;
			break;
			//////////////////////////////////////
			//////////////////////////////////////
		case ID_GOLD_CHAMS:
			cheat_state->Wallhack.iGoldChams ^= 1;
			break;
		case ID_GOLD_CHAMS_WIREFRAME:
			cheat_state->Wallhack.iGoldChams_WireFrame ^= 1;
			break;
		case ID_GOLD_CHAMS_WEAPONS:
			cheat_state->Wallhack.iGoldChams_Weapons ^= 1;
			break;
		case ID_GOLD_CHAMS_WEAPONS_WIREFRAME:
			cheat_state->Wallhack.iGoldChams_Weapons_WireFrame ^= 1;
			break;
			//////////////////////////////////////
		case ID_ORIGINAL_CHAMS:
			cheat_state->Wallhack.iOrijinalChams ^= 1;
			break;
		case ID_ORIGINAL_CHAMS_WIREFRAME:
			cheat_state->Wallhack.iOrijinal_Chams_WireFrame ^= 1;
			break;
		case ID_ORIGINAL_WEAPONS_CHAMS:
			cheat_state->Wallhack.iOrijinal_Weapons ^= 1;
			break;
		case ID_ORIGINAL_WEAPONS_WIREFRAME:
			cheat_state->Wallhack.iOrijinal_Weapons_WireFrame ^= 1;
			break;
			//////////////////////////////////////
		/*case ID_LAGSHOT_POINT:
			return cheat_state->genel.iLagShootPoint ^= 1;
			break;*/
		case ID_DRAW_ADMINS:
			return set.iDraw_Admins ^= 1;
			break;
		case ID_DRAW_FRIENDS:
			return set.D3DFeatures.bDrawFriendTag ^= 1;
			break;
		case ID_BONE_ESP:
			cheat_state->Wallhack.iBoneESP ^= 1;
			break;
		case ID_TRACER_ESP:
			cheat_state->Wallhack.iTracerESP ^= 1;
			break;
		case ID_PLAYER_BOX_ESP:
			cheat_state->Wallhack.iPlayerBoxESP ^= 1;
			break;
		case ID_ADMINS_LIST:
			cheat_state->Wallhack.iAdminListesi ^= 1;
			break;
		case ID_FRIENDS_LIST:
			cheat_state->Wallhack.iArkadasListesi ^= 1;
			break;
		case ID_3D_INFORMER:
			cheat_state->Wallhack.iD3DInformer ^= 1;
			break;
		case ID_WEAPON_INFO:
			set.seeWeaponTags ^= 1;
			break;
	/*	case ID_STATUS_INFO:
			set.statusTag ^= 1;
			break;*/
		case ID_RENDER_NEW_HUD:
			set.D3DFeatures.bDrawHUDLikeLiquid ^= 1;
			break;
		}
	}
}
static int menu_callback_aim_hileleri(int op, struct menu_item* item)
{
	if (g_SAMP == NULL)
		return 0;

	int mod;

	switch (op)
	{
	case MENU_OP_ENABLED:
	{
		switch (item->id)
		{
		case ID_SILENT_AIMBOT:
			return cheat_state->Silent.bSilent;
		case ID_SHOOT_THROUGH_WALLS:
			return cheat_state->Silah.iShooting_Through_Walls;
		case ID_AUTO_AIM_RAGE:
			return cheat_state->actor.autoaim;
		case ID_AUTO_AIM_LEGIT:
			return cheat_state->Silah.iLegitAimBot;
			return 0;
		default: return 0;
		}
	}
	case MENU_OP_SELECT:
		switch (item->id)
		{
		case ID_SILENT_AIMBOT:
			cheat_state->Silent.bSilent ^= 1;
			break;
		case ID_SHOOT_THROUGH_WALLS:
			cheat_state->Silah.iShooting_Through_Walls ^= 1;
			break;
		case ID_AUTO_AIM_RAGE:
			cheat_state->actor.autoaim ^= 1;
			break;
		case ID_AUTO_AIM_LEGIT:
			cheat_state->Silah.iLegitAimBot ^= 1;
			break;
		}
		return 0;
	}
}


static int menu_callback_gorsel_hileler(int op, struct menu_item *item)
{
	if (g_SAMP == NULL)
		return 0;

	int mod;

	switch (op)
	{
	case MENU_OP_ENABLED:
	{
		switch (item->id)
		{
		default: return 0;
		}
	}
	case MENU_OP_SELECT:
		switch (item->id)
		{

		}
	}
}


static int menu_callback_flooderler(int op, struct menu_item *item)
{
	if (g_SAMP == NULL)
		return 0;

	int mod;

	switch (op)
	{
	case MENU_OP_ENABLED:
	{
		switch (item->id)
		{
		case ID_PROJECT_FLOODER:
			return cheat_state->Flooderler.iRandomFlooder;
		case ID_PM_LAGGER_FLOODER:
			return cheat_state->Flooderler.iPMCrashFlooder;
		case ID_MATRIX_FLOODER:
			return cheat_state->Flooderler.iMatrixSpammer;
		default: return 0;
		}
	}
	case MENU_OP_SELECT:
		switch (item->id)
		{

		case ID_PROJECT_FLOODER:
			cheat_state->Flooderler.iRandomFlooder ^= 1;
			break;
		case ID_PM_LAGGER_FLOODER:
			cheat_state->Flooderler.iPMCrashFlooder ^= 1;
			break;
		case ID_MATRIX_FLOODER:
			cheat_state->Flooderler.iMatrixSpammer ^= 1;
			break;
		}
	}

}


static int menu_callback_troll_hileler(int op, struct menu_item *item)
{
	if (g_SAMP == NULL)
		return 0;

	int mod;

	switch (op)
	{
	case MENU_OP_ENABLED:
	{
		switch (item->id)
		{
		case ID_ACTOR_SHOOTER:
			return cheat_state->Troll.iActorShooter;
		case ID_PLAYER_ELEVATOR:
			return cheat_state->Troll.iElevator;
		case ID_PLAYER_JETPACK_ELEVATOR:
			return cheat_state->Troll.iJetpackElevator;
		case ID_PLAYER_SHOOTER:
			return cheat_state->Troll.iPlayerShooter;
		case ID_INVISIBLE:
			return cheat_state->Troll.iInvisible1;
		case ID_INVISIBLE2:
			return cheat_state->Troll.iInvisible2;
		case ID_INVISIBLE3:
			return cheat_state->Troll.iInvisible3;
		case ID_INVISIBLE4:
			return cheat_state->Troll.iInvisible4;
		case ID_INVISIBLE5:
			return cheat_state->Troll.iInvisible5;
		case ID_INVISIBLE6:
			return cheat_state->Troll.iInvisible6;
		case ID_INVISIBLE7:
			return cheat_state->Troll.iInvisible7;
		case ID_INVISIBLE8:
			return cheat_state->Troll.iInvisible8;
		case ID_INVALID_AIM_Z:
			return cheat_state->genel.iInvalidAimZ;
		case ID_SHAKING_CAMERA:
			return cheat_state->genel.iShakingCamera;
		case ID_SHAKING_CAMERA2:
			return cheat_state->genel.iShakingCamera2;
		case ID_DISCO_MODE:
			return cheat_state->genel.iDiscoMode;
		case ID_UNSYNCH:
			return cheat_state->Troll.iUnSynch;
		case ID_N3X_TROLL_CAR_2:
			return cheat_state->Troll.iTrollCar2;
		case ID_PLAYER_SLAPPER:
			return cheat_state->Troll.iSpeedKicker;
		default: return 0;
		}
	}
	case MENU_OP_SELECT:
		switch (item->id)
		{
		case ID_ACTOR_SHOOTER:
			cheat_state->Troll.iActorShooter ^= 1;
			break;
		case ID_PLAYER_JETPACK_ELEVATOR:
			cheat_state->Troll.iJetpackElevator ^= 1;
			break;
		case ID_PLAYER_ELEVATOR:
			cheat_state->Troll.iElevator ^= 1;
			break;
		case ID_PLAYER_SHOOTER:
			cheat_state->Troll.iPlayerShooter ^= 1;
			break;
		case ID_INVISIBLE:
			cheat_state->Troll.iInvisible1 ^= 1;
			break;
		case ID_INVISIBLE2:
			cheat_state->Troll.iInvisible2 ^= 1;
			break;
		case ID_INVISIBLE3:
			cheat_state->Troll.iInvisible3 ^= 1;
			break;
		case ID_INVISIBLE4:
			cheat_state->Troll.iInvisible4 ^= 1;
			break;
		case ID_INVISIBLE5:
			cheat_state->Troll.iInvisible5 ^= 1;
			break;
		case ID_INVISIBLE6:
			cheat_state->Troll.iInvisible6 ^= 1;
			break;
		case ID_INVISIBLE7:
			cheat_state->Troll.iInvisible7 ^= 1;
			break;
		case ID_INVISIBLE8:
			cheat_state->Troll.iInvisible8 ^= 1;
			break;
		case ID_INVALID_AIM_Z:
			cheat_state->genel.iInvalidAimZ ^= 1;
			break;
		case ID_SHAKING_CAMERA:
			cheat_state->genel.iShakingCamera ^= 1;
			break;
		case ID_SHAKING_CAMERA2:
			cheat_state->genel.iShakingCamera2 ^= 1;
			break;
		case ID_DISCO_MODE:
			cheat_state->genel.iDiscoMode ^= 1;
			break;
		case ID_UNSYNCH:
			cheat_state->Troll.iUnSynch ^= 1;
			break;
		case ID_N3X_TROLL_CAR_2:
			cheat_state->Troll.iTrollCar2 ^= 1;
			break;
		case ID_PLAYER_SLAPPER:
			cheat_state->Troll.iSpeedKicker ^= 1;
			break;
		}
	}
}
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
static int menu_callback_b0tz(int op, struct menu_item *item)
{
	if (g_SAMP == NULL)
		return 0;
	int increase = 0;
	short TargetID = g_BotFuncs->BotSettings.sTargetID;
	switch (op)
	{
	case MENU_OP_SELECT:
		switch (item->id)
		{
		case ID_ADD_B0T:
			g_BotFuncs->Client_in_Queue++;
			break;
		case ID_ADD_NUMBER_B0T:
			g_BotFuncs->Client_in_Queue += g_BotFuncs->N_Client_to_Add_In_Queue;
			break;
		//case ID_B0T_FAKE_PING:
		//	g_BotFuncs->BotSettings.FakePing ^= true;
		//	break;
		case ID_DELETE_B0T:
			g_BotFuncs->OL_Delete_Bot();
			break;
		case ID_DELETE_ALL_B0TZ:
			for (int i = g_BotFuncs->BotSettings.ClientCount; i > 0; i--)
				g_BotFuncs->OL_Delete_Bot();
			break;
			//---- BoTz için Bot Timeout all ve Bot Kick All eklenecek.
		case ID_DELETE_ALL_B0TS_TIMEOUT:
			g_BotFuncs->BotSettings.bKickBotsByTimeout ^= true;
			for (int x = g_BotFuncs->BotSettings.ClientCount; x > 0; x--)
				g_BotFuncs->OL_Delete_Bot();
			break;
		case ID_DELETE_ALL_B0TS_KICKED:
			g_BotFuncs->BotSettings.bDeleteBotsByKick ^= true;
			for (int x = g_BotFuncs->BotSettings.ClientCount; x > 0; x--)
				g_BotFuncs->OL_Delete_Bot();
			break;
		case ID_B0T_SPAWN:
			for (int i = g_BotFuncs->BotSettings.ClientCount - 1; i >= 0; i--)
			g_BotFuncs->OL_Spawn_Bot(i);
			break;
		case ID_B0T_SPAWN_ALL:
			for (int j = 0; j < 2; j++)
				for (int i = g_BotFuncs->BotSettings.ClientCount - 1; i >= 0; i--)
					g_BotFuncs->OL_Random_Spawn_Bot(i);
			break;
		case ID_B0T_FOLLOW_ME:
			g_BotFuncs->BotSettings.bFollow ^= true;
			break;
		case ID_B0T_SH00TER:
			g_BotFuncs->BotSettings.bShooter ^= true;
			break;
		case ID_B0T_CIRCLE:
			g_BotFuncs->BotSettings.bBotCircle ^= true;
			break;
		case ID_B0T_ATTACKER:
			g_BotFuncs->BotSettings.bBotAttacker ^= true;
			break;
		case ID_B0T_ELEVATOR:
			g_BotFuncs->BotSettings.bBotElevator ^= true;
			break;
		case ID_B0T_JETPACK_ELEVATOR:
			g_BotFuncs->BotSettings.bBotJetpackElevator ^= true;
			break;
		case ID_B0T_PICK:
			g_BotFuncs->BotSettings.bBotPick ^= true;
			break;
		case ID_B0T_SLAPPER:
			g_BotFuncs->BotSettings.bBotSlapper ^= true;
			break;
		case ID_B0T_FUCK:
			g_BotFuncs->BotSettings.bBotFuck ^= true;
			break;
		case ID_B0T_SUN:
			g_BotFuncs->BotSettings.bBotSun ^= true;
			break;
		/*case ID_BOT_FOLLOW_ANIM:
			g_BotFuncs->BotSettings.bBotFollowAnim ^= true;
			break;*/
		case ID_USE_FRIEND_TARGET3:
			BotCheats->bUseFriendTarget ^= true;
			break;
		case ID_B0T_SILENT:
			g_BotFuncs->BotSettings.bBotSilent ^= true;
			break;
		case ID_B0T_USE_NEAREST_TARGET:
			g_BotFuncs->BotSettings.bUseNearestTarget ^= true;
			break;
		}
		break;
	case MENU_OP_ENABLED:
		switch (item->id)
		{
			char name[128];
		case ID_ADD_NUMBER_B0T:
			snprintf(name, sizeof(name), "\aAdd %d bot", g_BotFuncs->N_Client_to_Add_In_Queue);
			menu_item_name_set(item, name);
			break;
		/*case ID_B0T_FAKE_PING:
			return g_BotFuncs->BotSettings.FakePing;
			break;*/
		case ID_B0T_SH00TER:
			return g_BotFuncs->BotSettings.bShooter;
			break;
		case ID_B0T_CIRCLE:
			return g_BotFuncs->BotSettings.bBotCircle;
			break;
	/*	case ID_INCREASE_PING:
			snprintf(name, sizeof(name), "\aIncrease Ping: %d", g_BotFuncs->BotSettings.incrasePing);
			menu_item_name_set(item, name);
			break;*/
		case ID_B0T_SILENT:
			return g_BotFuncs->BotSettings.bBotSilent;
			break;
		case ID_B0T_FOLLOW_ME:
			return g_BotFuncs->BotSettings.bFollow;
			break;
		case ID_B0T_DISTANCE_BETWEEN_PLAYER:
		{
			snprintf(name, sizeof(name), "\aBot Distance from player: %.2f", g_BotFuncs->BotSettings.fDistanceFollow);
			menu_item_name_set(item, name);

			return g_BotFuncs->BotSettings.bFollow;
			break;
		}
		break;
		case ID_B0T_DISTANCE_BETWEEN_B0TS:
		{
			snprintf(name, sizeof(name), "\aBot Distance from other bots: %.2f", g_BotFuncs->BotSettings.fDistanceFollowBetweenBots);
			menu_item_name_set(item, name);

			return g_BotFuncs->BotSettings.bFollow;
			break;
		}
		case ID_B0T_ATTACKER_WEAPON:
		{
			if (g_BotFuncs->BotSettings.uiAttackWeaponID > 38)
			{
				set.WeaponCheats.Weapon_Damage = 0;
			}
			snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if(g_BotFuncs->BotSettings.uiAttackWeaponID == 0)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [Fist]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if(g_BotFuncs->BotSettings.uiAttackWeaponID == 22)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [Colt45]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 23)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [Colt45-Silenced]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 24)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [DesertEagle]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 25)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [Shotgun]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 26)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [SawnOff]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 27)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [CombatShotgun]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 28)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [UZI]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 29)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [MP5]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 30)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [AK-47]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 31)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [M4]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 32)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [TEC9]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 33)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [Rifle]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 34)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [Sniper]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 35)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [Rocket]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 36)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [HeatSeeker-Rocket]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 37)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [Flamethrower]", g_BotFuncs->BotSettings.uiAttackWeaponID);
			if (g_BotFuncs->BotSettings.uiAttackWeaponID == 38)
				snprintf(name, sizeof(name), "\aBot Att.Weapon ID: %d [Minigun]", g_BotFuncs->BotSettings.uiAttackWeaponID);

			menu_item_name_set(item, name);
			break;
		}
		case ID_B0T_DELAY:
		{
			snprintf(name, sizeof(name), "\aBot Network/Cheat Delay: %d MS", g_BotFuncs->BotSettings.UpdateSendRate);
			menu_item_name_set(item, name);
			return true;
		}
		case ID_B0T_SELECT_TARGET:
			if (TargetID >= 0)
			{
				char name[128];
				if (IsPlayerStreamed(TargetID))
				{
					snprintf(name, sizeof(name), "\aTarget ID: %s <%d>", getPlayerName(TargetID), TargetID);
					menu_item_name_set(item, name);
				}
				else
				{
					snprintf(name, sizeof(name), "\aTarget ID: <%d> [Unstreamed]", TargetID);
					menu_item_name_set(item, name);
				}
			}
			else
			{
				//snprintf(name, sizeof(name), "\aTroll: <%d> [Unstreamed]", TargetID);
				//menu_item_name_set(item, "\aTarget ID: Nearest Player");
				g_BotFuncs->BotSettings.sTargetID = NearestPlayer();
			}
			break;
		case ID_B0T_USE_NEAREST_TARGET:
			return g_BotFuncs->BotSettings.bUseNearestTarget;
			break;
		case ID_B0T_ATTACKER:
			return g_BotFuncs->BotSettings.bBotAttacker;
			break;
		case ID_B0T_ELEVATOR:
			return g_BotFuncs->BotSettings.bBotElevator;
			break;
		case ID_B0T_SUN:
			return g_BotFuncs->BotSettings.bBotSun;
			break;
		case ID_B0T_JETPACK_ELEVATOR:
			return g_BotFuncs->BotSettings.bBotJetpackElevator;
			break;
		case ID_B0T_PICK:
			return g_BotFuncs->BotSettings.bBotPick;
			break;
		case ID_B0T_SLAPPER:
			return g_BotFuncs->BotSettings.bBotSlapper;
			break;
		case ID_B0T_FUCK:
			return g_BotFuncs->BotSettings.bBotFuck;
			break;
		case ID_B0T_FOLLOW_ANIM:
			return g_BotFuncs->BotSettings.bBotFollowAnim;
			break;
		/*case ID_B0T_FOLLOW_SEL_ANIM:
		{
			snprintf(name, sizeof(name), "\aBot Foll. Anim: %d", g_BotFuncs->BotSettings.sBotFollowAnimID);
			menu_item_name_set(item, name);
			break;
		}*/
		case ID_USE_FRIEND_TARGET3:
			return BotCheats->bUseFriendTarget;
		}
		break;
	case MENU_OP_DEC:
	case MENU_OP_INC:
		increase = (op == MENU_OP_DEC) ? -1 : 1;
		switch (item->id)
		{
		case ID_ADD_NUMBER_B0T:
			g_BotFuncs->N_Client_to_Add_In_Queue += increase;
			break;
	/*	case ID_INCREASE_PING:
			g_BotFuncs->BotSettings.incrasePing += increase;
			break;*/
		case ID_B0T_DISTANCE_BETWEEN_PLAYER:
			g_BotFuncs->BotSettings.fDistanceFollow += (float)increase / 10.0f;
			break;
		case ID_B0T_DISTANCE_BETWEEN_B0TS:
			g_BotFuncs->BotSettings.fDistanceFollowBetweenBots += (float)increase / 10.0f;
			break;
		case ID_B0T_ATTACKER_WEAPON:
			g_BotFuncs->BotSettings.uiAttackWeaponID += increase;
			break;
		case ID_B0T_SELECT_TARGET:
			g_BotFuncs->BotSettings.sTargetID = NextPlayer(g_BotFuncs->BotSettings.sTargetID, increase);
			break;

		case ID_B0T_DELAY:
			g_BotFuncs->BotSettings.UpdateSendRate += increase * 5;
			break;
		}
		break;

	}
	return 0;
}
#endif
static int menu_callback_raknet_hileleri(int op, struct menu_item *item)
{
	if (g_SAMP == NULL)
		return 0;

	int mod;

	switch (op)
	{
	case MENU_OP_ENABLED:
	{
		switch (item->id)
		{
		default: return 0;
		}
	}
	case MENU_OP_SELECT:
		switch (item->id)
		{
		
		}
	}
}

static int menu_callback_korumalar(int op, struct menu_item *item)
{
	if (g_SAMP == NULL)
		return 0;

	int mod;

	switch (op)
	{
	case MENU_OP_ENABLED:
	{
		switch (item->id)
		{
		case ID_ANTI_BULLET_CRASHER:
			return cheat_state->Korumalar.iAntiBulletCrasher;
		case ID_ANTI_INVALIDBULLETS_CRASHER:
			return cheat_state->Korumalar.iAntiInvalidBulletsCrasher;
		case ID_ANTI_PASSENGER_CRASHER:
			return cheat_state->Korumalar.iAntiPassengerCrasher;
		case ID_ANTI_ROLL_CRASHER:
			return cheat_state->Korumalar.iAntiRollCrasher;
		case ID_ANTI_CAR_TROLLER:
			return cheat_state->Korumalar.iAntiCarTroll;
		case ID_ANTI_LOADING_CRASHER:
			return cheat_state->Korumalar.iAntiLoadingCrasher;
		case ID_NO_COLLISION_ACTORS:
			return set.bNoCollisionPlayers;
		case ID_NO_COLLISION_VEHICLES:
			return set.bNoCollisionVehicles;
		case ID_ANTI_SHAKING_CAMERA:
			return cheat_state->Korumalar.iAntiShakingCamera;
		case ID_ANTI_INVALID_AIM_Z:
			return cheat_state->Korumalar.iAntiInvalidAimZ;
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH || COMPILE_TYPE != COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
		case ID_ANTI_TRAILERSYNC_POS_CRASHER:
			return cheat_state->AntiTrailer.iAntifPositionCrasher;
		case ID_ANTI_TRAILERSYNC_FSPIN_CRASHER:
			return cheat_state->AntiTrailer.iAntifSpinCrasher;
		case ID_ANTI_TRAILERSYNC_FSPEED_CRASHER:
			return cheat_state->AntiTrailer.iAntifSpeedCrasher;
#endif
		case ID_ANTI_WARNINGS_CRASHER:
			return cheat_state->Korumalar.iAntiWarningCrasher;
		case ID_FPS_UNLOCKER:
			return set.General.Use_FPS_Unlocker;
		default: return 0;
		}
	}
	case MENU_OP_SELECT:
		switch (item->id)
		{
		case ID_ANTI_BULLET_CRASHER:
			cheat_state->Korumalar.iAntiBulletCrasher ^= 1;
			break;
		case ID_ANTI_INVALIDBULLETS_CRASHER:
			cheat_state->Korumalar.iAntiInvalidBulletsCrasher ^= 1;
			break;
		case ID_ANTI_PASSENGER_CRASHER:
			cheat_state->Korumalar.iAntiPassengerCrasher ^= 1;
			break;
		case ID_ANTI_ROLL_CRASHER:
			cheat_state->Korumalar.iAntiRollCrasher ^= 1;
			break;	
		case ID_ANTI_CAR_TROLLER:
			cheat_state->Korumalar.iAntiCarTroll ^= 1;
			break;
		case ID_ANTI_LOADING_CRASHER:
			cheat_state->Korumalar.iAntiLoadingCrasher ^= 1;
			break;
		case ID_NO_COLLISION_ACTORS:
			set.bNoCollisionPlayers ^= 1;
			break;
		case ID_NO_COLLISION_VEHICLES:
			set.bNoCollisionVehicles ^= 1;
			break;
		case ID_ANTI_SHAKING_CAMERA:
			cheat_state->Korumalar.iAntiShakingCamera ^= 1;
			break;
		case ID_ANTI_INVALID_AIM_Z:
			cheat_state->Korumalar.iAntiInvalidAimZ ^= 1;
			break;
		case ID_ANTI_TRAILERSYNC_POS_CRASHER:
			cheat_state->AntiTrailer.iAntifPositionCrasher ^= 1;
			break;
		case ID_ANTI_TRAILERSYNC_FSPIN_CRASHER:
			cheat_state->AntiTrailer.iAntifSpinCrasher ^= 1;
			break;
		case ID_ANTI_TRAILERSYNC_FSPEED_CRASHER:
			cheat_state->AntiTrailer.iAntifSpeedCrasher ^= 1;
			break;
		case ID_ANTI_WARNINGS_CRASHER:
			cheat_state->Korumalar.iAntiWarningCrasher ^= 1;
			break;
		case ID_FPS_UNLOCKER:
			set.General.Use_FPS_Unlocker ^= 1;
			break;
		}
	}
}
static int menu_callback_gecikme_sureleri(int op, struct menu_item *item)
{
	if (g_SAMP == NULL)
		return 0;
	int mod;

	switch (op)
	{
	case MENU_OP_ENABLED:
	{
		switch (item->id)
		{
		
		default: return 0;
		}
	}
	case MENU_OP_SELECT:
		switch (item->id)
		{
		
		}
	}
}


static int menu_callback_spec ( int op, struct menu_item *item )
{
	struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	if ( g_Players == NULL )
		return 0;
	if ( self == NULL )
		return 0;

	if ( op == MENU_OP_SELECT )
	{
		int id = item->id;
		if ( self == NULL )
		{
			addMessageToChatWindow( "You are dead." );
			return 1;
		}
		if ( id == -1 )
		{
			spectatePlayer( id );
			return 1;
		}

		if ( g_Players->pRemotePlayer[id] == NULL )
		{
			addMessageToChatWindow( "Player doesn't exist." );
			return 1;
		}

		if ( g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_WASTED
			|| ( g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_NONE ) )
		{
			addMessageToChatWindow( "Could not spectate player" );
			return 1;
		}

		spectatePlayer( id );

		return 1;
	}

	return 0;
}

void	renderPlayerPoolStructure ( int iPlayerID );
int		iViewingInfoPlayer = -1;
static int menu_callback_playerinfo ( int op, struct menu_item *item )
{
	if ( g_Players == NULL )
		return 0;

	int id = item->id;
	if ( op == MENU_OP_SELECT )
	{
		if ( id == SAMP_MAX_PLAYERS + 1 )
		{
			iViewingInfoPlayer = -1;
			return 1;
		}

		iViewingInfoPlayer = id;

		return 1;
	}

	return 0;
}

static int menu_callback_playermute ( int op, struct menu_item *item )
{
	if ( g_Players == NULL )
		return 0;

	int id = item->id;
	if ( op == MENU_OP_ENABLED )
	{
		if ( id < SAMP_MAX_PLAYERS && id >= 0 )
			return g_bPlayerMuted[id];
		return 0;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( id < SAMP_MAX_PLAYERS && id >= 0 )
		{
			if ( g_bPlayerMuted[id] )
				g_iNumPlayersMuted--;
			else
				g_iNumPlayersMuted++;
			
			g_bPlayerMuted[id] ^= 1;
			return 1;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_server_list ( int op, struct menu_item *item )
{
	if ( g_SAMP == NULL && g_Players == NULL )
		return 0;

	struct fav_server	*server = &set.server[item->id];

	if ( op == MENU_OP_ENABLED )
	{
		if ( item->id == INI_SERVERS_MAX + 1 )
			return set.use_current_name;
		return 0;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( item->id == ID_NONE )
			return 1;

		if ( item->id == INI_SERVERS_MAX + 1 )
		{
			set.use_current_name ^= 1;
			return 1;
		}
		else
		{
			if ( !set.use_current_name )
				setLocalPlayerName( server->nickname );
			changeServer( server->ip, server->port, server->password );

			return 1;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_gamestate ( int op, struct menu_item *item )
{
	if ( g_SAMP == NULL )
		return 0;

	if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case GAMESTATE_CONNECTING:
			g_SAMP->iGameState = GAMESTATE_CONNECTING;
			break;

		case GAMESTATE_CONNECTED:
			g_SAMP->iGameState = GAMESTATE_CONNECTED;
			break;

		case GAMESTATE_AWAIT_JOIN:
			g_SAMP->iGameState = GAMESTATE_AWAIT_JOIN;
			break;

		case GAMESTATE_RESTARTING:
			g_SAMP->iGameState = GAMESTATE_RESTARTING;
			break;

		case GAMESTATE_WAIT_CONNECT:
			g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
			break;
		}

		return 1;
	}

	if ( op == MENU_OP_ENABLED )
	{
		switch ( item->id )
		{
		case GAMESTATE_CONNECTING:
			return g_SAMP->iGameState == GAMESTATE_CONNECTING;

		case GAMESTATE_CONNECTED:
			return g_SAMP->iGameState == GAMESTATE_CONNECTED;

		case GAMESTATE_AWAIT_JOIN:
			return g_SAMP->iGameState == GAMESTATE_AWAIT_JOIN;

		case GAMESTATE_RESTARTING:
			return g_SAMP->iGameState == GAMESTATE_RESTARTING;

		case GAMESTATE_WAIT_CONNECT:
			return g_SAMP->iGameState == GAMESTATE_WAIT_CONNECT;
		}
	}

	return 0;
}

static int menu_callback_netpatches(int op, struct menu_item *item)
{
	if ( g_SAMP == NULL )
		return 0;

	if (op == MENU_OP_SELECT)
	{
		if (item->id == ID_MENU_NETPATCHES_TOGGLE_ALL)
		{
			if (item->menu->count > 1)
			{
				// hacky method to get patch type of this menu
				NetPatchType type = set.netPatch[item->menu->item[1].id].type; // omg omg omg
				
				// count enabled and disabled patches
				int enabled = 0, disabled = 0;
				for (int i = 0; i < iNetPatchesCount; ++i)
				{
					if (set.netPatch[i].type != type) continue;
					if (set.netPatch[i].enabled) ++enabled;
					else ++disabled;
				}

				for (int i = 0; i < iNetPatchesCount; ++i)
				{
					if (set.netPatch[i].type != type) continue;
					set.netPatch[i].enabled = disabled > enabled ? true : false;
				}
			}
		}
		else
		{
			set.netPatch[item->id].enabled ^= true;
		}
	}
	if (op == MENU_OP_ENABLED)
	{
		if (item->id != ID_MENU_NETPATCHES_TOGGLE_ALL)
		{
			return set.netPatch[item->id].enabled;
		}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
////////////////////////////// FUNCTIONS DONE ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////////////////// START MENU LAYOUT /////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void menu_maybe_init(void)
{
	traceLastFunc("menu_maybe_init()");
	if (menu_init)
		return;

	struct menu *menu_main, *menu_cheats, *menu_cheats_mods, *menu_cheats_inv, *menu_cheats_money, *
		menu_cheats_weather, *menu_cheats_time, *menu_weapons, *menu_vehicles, *menu_teleports, *menu_interiors, *
		menu_misc, *menu_debug, *menu_hudindicators, *menu_patches, *menu_players, *menu_servers, *
		menu_players_warp, *menu_players_vehwarp, *menu_players_spec, *menu_hileler, *menu_arac_hileleri, *menu_wallhacklar,
		*menu_gorsel_hileler, *menu_flooderler, *menu_raknet_hileleri, *menu_troll_hileler, *menu_gecikme_sureleri, *menu_korumalar, *menu_silah_hileleri, *menu_aim_hileleri, 
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
		*menu_b0tz,
#endif
#ifdef __CHEAT_VEHRECORDING_H__
		*menu_routes, *menu_routes_load, *menu_routes_drop,
#endif

		//*menu_cheats_handling,
		*menu_player_info, *menu_players_mute, *menu_sampmisc, *menu_spoof_weapon, *menu_fake_kill, *menu_vehicles_instant,
		*menu_gamestate, *menu_specialaction, *menu_teleobject, *menu_telepickup, *menu_samppatches,
		*menu_netpatches_inrpc, *menu_netpatches_outrpc, *menu_netpatches_inpacket, *menu_netpatches_outpacket;



	char		name[128];
	int			i, slot;

	menu_init = 1;

	/* main menu */
	menu_main = menu_new(NULL, ID_MENU_MAIN, menu_callback_main);
	menu_cheats = menu_new(menu_main, ID_MENU_CHEATS, menu_callback_cheats);
	menu_patches = menu_new(menu_main, ID_MENU_PATCHES, menu_callback_patches);
	menu_weapons = menu_new(menu_main, ID_MENU_WEAPONS, menu_callback_weapons);
	menu_vehicles = menu_new(menu_main, ID_MENU_VEHICLES, menu_callback_vehicles);
	menu_teleports = menu_new(menu_main, ID_MENU_TELEPORTS, menu_callback_teleports);
	menu_misc = menu_new(menu_main, ID_MENU_MISC, menu_callback_misc);

	/* main menu -> cheats */
	menu_cheats_inv = menu_new(menu_cheats, ID_MENU_CHEATS_INVULN, menu_callback_cheats_invuln);
	menu_cheats_money = menu_new(menu_cheats, ID_MENU_CHEATS_MONEY, menu_callback_cheats_money);
	menu_cheats_mods = menu_new(menu_cheats, ID_MENU_CHEATS_MODS, menu_callback_cheats_mods);
	menu_cheats_weather = menu_new(menu_cheats, ID_MENU_CHEATS_WEATHER, menu_callback_cheats);
	// disabled for now until we/mta rework CHandlingEntrySA
	//menu_cheats_handling = menu_new( menu_cheats, ID_MENU_CHEATS_HANDLING, menu_callback_handling );
	menu_cheats_time = menu_new(menu_cheats, ID_MENU_CHEATS_TIME, menu_callback_cheats);

	/* main menu -> teleports */
	menu_interiors = menu_new(menu_teleports, ID_MENU_INTERIORS, menu_callback_interiors);

	/* main menu -> misc */
	menu_debug = menu_new(menu_misc, ID_MENU_DEBUG, menu_callback_debug);
	menu_hudindicators = menu_new(menu_misc, ID_MENU_HUDINDICATORS, menu_callback_hudindicators);
#ifdef __CHEAT_VEHRECORDING_H__
	menu_routes = menu_new(menu_misc, ID_MENU_ROUTES, menu_callback_routes);

	/* main menu -> misc -> routes */
	menu_routes_load = menu_new(menu_routes, ID_MENU_ROUTES_LOAD, menu_callback_routes_load);
	menu_routes_drop = menu_new(menu_routes, ID_MENU_ROUTES_DROP, menu_callback_routes_drop);
#endif

	/* samp specific */
	if (g_dwSAMP_Addr != NULL)
	{
		// main menu
		menu_players = menu_new(menu_main, ID_MENU_PLAYERS, menu_callback_players);
		menu_servers = menu_new(menu_main, ID_MENU_SERVER_LIST, menu_callback_server_list);
		menu_sampmisc = menu_new(menu_main, ID_MENU_SAMPMISC, menu_callback_sampmisc);
		menu_samppatches = menu_new(menu_main, ID_MENU_SAMPPATCHES, menu_callback_samppatches);
		menu_hileler = menu_new(menu_main, ID_MENU_HILELER, menu_callback_hileler);

		menu_arac_hileleri = menu_new(menu_main, ID_MENU_ARACHILELERI, menu_callback_arachileleri);

		menu_aim_hileleri = menu_new(menu_main, ID_MENU_AIM_HILELERI, menu_callback_aim_hileleri);

		menu_silah_hileleri = menu_new(menu_main, ID_MENU_SILAH_HILELERI, menu_callback_silah_hileleri);

		menu_wallhacklar = menu_new(menu_main, ID_MENU_WALLHACKLAR, menu_callback_wallhacklar);

		menu_gorsel_hileler = menu_new(menu_main, ID_MENU_GORSEL_HILELER, menu_callback_gorsel_hileler);

		menu_flooderler = menu_new(menu_main, ID_MENU_FLOODERLER, menu_callback_flooderler);

		menu_troll_hileler = menu_new(menu_main, ID_MENU_TROLL_HILELER, menu_callback_troll_hileler);

		menu_raknet_hileleri = menu_new(menu_main, ID_MENU_RAKNET_HILELERI, menu_callback_raknet_hileleri);

		menu_korumalar = menu_new(menu_main, ID_MENU_ANTI_CRASHERLER, menu_callback_korumalar);
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
		menu_b0tz = menu_new(menu_main, ID_MENU_B0TZ, menu_callback_b0tz);
#endif
		menu_gecikme_sureleri = menu_new(menu_main, ID_HILE_GECIKME_SURELERI, menu_callback_gecikme_sureleri);

		// main menu -> players
		menu_players_warp = menu_new(menu_players, ID_MENU_PLAYERS_WARP, menu_callback_players_warp);
		menu_players_vehwarp = menu_new(menu_players, ID_MENU_PLAYERS_VEHWARP, menu_callback_players_vehwarp);
		menu_players_spec = menu_new(menu_players, ID_MENU_PLAYERS_SPEC, menu_callback_spec);
		menu_player_info = menu_new(menu_players, ID_MENU_PLAYERS_INFO, menu_callback_playerinfo);
		menu_players_mute = menu_new(menu_players, ID_MENU_PLAYERS_MUTE, menu_callback_playermute);
		// main menu -> sampmisc
		menu_spoof_weapon = menu_new(menu_sampmisc, ID_MENU_SAMPMISC_SPOOF_WEAPON, menu_callback_sampmisc);
		menu_fake_kill = menu_new(menu_sampmisc, ID_MENU_SAMPMISC_FAKE_KILL, menu_callback_sampmisc);
		menu_vehicles_instant = menu_new(menu_sampmisc, ID_MENU_SAMPMISC_VEHICLES_INSTANT, menu_callback_vehicles_instant);
		menu_gamestate = menu_new(menu_sampmisc, ID_MENU_SAMPMISC_GAMESTATE, menu_callback_gamestate);
		menu_specialaction = menu_new(menu_sampmisc, ID_MENU_SAMPMISC_SPECIALACTION, menu_callback_specialaction);
		menu_teleobject = menu_new(menu_sampmisc, ID_MENU_SAMPMISC_TELEOBJECT, menu_callback_teleobject);
		menu_telepickup = menu_new(menu_sampmisc, ID_MENU_SAMPMISC_TELEPICKUP, menu_callback_telepickup);
		// main menu -> samp patches
		menu_netpatches_inrpc = menu_new(menu_samppatches, ID_MENU_NETPATCHES_INRPC, menu_callback_netpatches);
		menu_netpatches_outrpc = menu_new(menu_samppatches, ID_MENU_NETPATCHES_OUTRPC, menu_callback_netpatches);
		menu_netpatches_inpacket = menu_new(menu_samppatches, ID_MENU_NETPATCHES_INPACKET, menu_callback_netpatches);
		menu_netpatches_outpacket = menu_new(menu_samppatches, ID_MENU_NETPATCHES_OUTPACKET, menu_callback_netpatches);
	}

	/** Menu Items **/
	/* main menu */

// Eðer Compile Type(Projenin çalýþma þekli benim içinse, Projenin Türkçe menülü kýsmýný çalýþtýracak.	
 
	menu_item_add(menu_main, NULL, M0D_VERSION, ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	menu_item_add(menu_main, menu_hileler, "» Cheats", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_aim_hileleri, "» Aim Cheats", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_wallhacklar, "» Visual Cheats", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_silah_hileleri, "» Weapon Cheats", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_troll_hileler, "» Trolling Features", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_flooderler, "» Chat Hacks", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_arac_hileleri, "» Car Cheats", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_korumalar, "» Game Protections", ID_NONE, MENU_COLOR_DEFAULT, NULL);
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
	menu_item_add(menu_main, menu_b0tz, "» RAKNET Bots", ID_NONE, MENU_COLOR_DEFAULT, NULL);
#endif
	//menu_item_add(menu_main, menu_raknet_hileleri, "» RakNet Fonksiyonlarý", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_gecikme_sureleri, "» Proje Lisansý", ID_NONE, MENU_COLOR_DEFAULT, NULL);
#else
	menu_item_add(menu_main, menu_hileler, "» Hileler", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_aim_hileleri, "» Niþan Hileleri", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_wallhacklar, "» Görüþ Hileleri", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_silah_hileleri, "» Silah Hileleri", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_troll_hileler, "» Troll Hileleri", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_flooderler, "» Chat Hileleri", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_arac_hileleri, "» Araç Hileleri", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_korumalar, "» Oyun Korumalarý", ID_NONE, MENU_COLOR_DEFAULT, NULL);
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
	menu_item_add(menu_main, menu_b0tz, "» RakNet Botlarý", ID_NONE, MENU_COLOR_DEFAULT, NULL);
#endif
	//menu_item_add(menu_main, menu_raknet_hileleri, "» RakNet Fonksiyonlarý", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_gecikme_sureleri, "» Proje Lisansý", ID_NONE, MENU_COLOR_DEFAULT, NULL);

#endif

#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH

	menu_item_add(menu_main, NULL, "\t› GTA Cheats", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_main, menu_cheats, "› Cheats", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_weapons, "› Weapons", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_vehicles, "› Cars", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_teleports, "› Teleports", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_misc, "› Misc", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	snprintf(name, sizeof(name), "› GTA Modifications (%d/%d)", iGTAPatchesCount, INI_PATCHES_MAX);
	menu_item_add(menu_main, menu_patches, name, ID_NONE, MENU_COLOR_DEFAULT, NULL);

	/* main menu (samp specific) */
	if (g_dwSAMP_Addr != NULL)
	{
		menu_item_add(menu_main, NULL, "\t› SA-MP Cheats", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
		menu_item_add(menu_main, menu_players, "› Players", ID_NONE, MENU_COLOR_DEFAULT, NULL);
		snprintf(name, sizeof(name), "› Fav. Servers (%d/%d)", iServersCount, INI_SERVERS_MAX);
		menu_item_add(menu_main, menu_servers, name, ID_NONE, MENU_COLOR_DEFAULT, NULL);
		menu_item_add(menu_main, menu_sampmisc, "› SA:MP Miscs.", ID_NONE, MENU_COLOR_DEFAULT, NULL);
		snprintf(name, sizeof(name), "› SA:MP Packets (%d/%d)", iSAMPPatchesCount, INI_SAMPPATCHES_MAX);
		menu_item_add(menu_main, menu_samppatches, name, ID_NONE, MENU_COLOR_DEFAULT, NULL);
	}


	menu_item_add(menu_hileler, menu_hileler, "\t | Cheats |", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL,"Genel hileler burada yer alýr.");
	menu_item_add(menu_hileler, menu_hileler, "God Fly", ID_GOD_FLY, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "You can set speed on AntTweakBar menu.");
	menu_item_add(menu_hileler, menu_hileler, "Map Run", ID_MAPRUN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "You can set speed on AntTweakBar menu.");
	menu_item_add(menu_hileler, menu_hileler, "\t | Invisible Mods |", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL,"You can not see these funcs, but other players can.");
	menu_item_add(menu_hileler, menu_hileler, "Ghost Mode", ID_GHOST_MODE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Ghost Mode");
	menu_item_add(menu_hileler, menu_hileler, "Twist Mode #1", ID_TWIST_MODE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Spins you 360 Degree!");
	menu_item_add(menu_hileler, menu_hileler, "Twist Mode #2", ID_TWIST_MODE_2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Spins you 360 Degree!");
	menu_item_add(menu_hileler, menu_hileler, "Rotation Mode", ID_CAMERA_MODE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"Rotation Mode, you can rotate ur character with mouse");
	menu_item_add(menu_hileler, menu_hileler, "Random Quaternions #1", ID_RAND_QUATS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Randomizes your quaternion");
	menu_item_add(menu_hileler, menu_hileler, "Random Quaternions #2", ID_RAND_QUATS_FIX, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Randomizes your quaternion");
	menu_item_add(menu_hileler, menu_hileler, "Invert Walk #1", ID_UPSIDE_DOWN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Upside Down");
	menu_item_add(menu_hileler, menu_hileler, "Invert Walk #2", ID_UPSIDE_DOWN_FIX, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Upside Down 2");
	menu_item_add(menu_hileler, menu_hileler, "\t | Invisible Mods |", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_hileler, menu_hileler, "Walk Through Walls", ID_WALK_THROUGH_WALLS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"Bugged");
	menu_item_add(menu_hileler, menu_hileler, "Speed Walk", ID_SPEED_WALK, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "You can find settings in AntTweakBar menu");
	menu_item_add(menu_hileler, menu_hileler, "Spawn me under 30HP", ID_DO_NOT_SEND_KILL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Works on some servers");
	menu_item_add(menu_hileler, menu_hileler, "Spawn at Death Position", ID_SPAWN_AT_DEATH_POS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"Works on some servers");
	menu_item_add(menu_hileler, menu_hileler, "HP Pulsator", ID_HP_PULSATOR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"UPs/DOWNs Your HP.");
	menu_item_add(menu_hileler, menu_hileler, "AP Pulsator", ID_ARMOR_PULSATOR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"UPs/DOWNs Your AP.");
	menu_item_add(menu_hileler, menu_hileler, "Player Deformer[Keys:7-8-9-0]", ID_PLAYER_DEFORMER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"You can set keys on .ini file");
	menu_item_add(menu_hileler, menu_hileler, "Fast Respawn", ID_FAST_RESPAWN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"Spawns you faster after die.");
	menu_item_add(menu_hileler, menu_hileler, "Disable Fall Animation", ID_NO_FALL_ANIMATION, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"Disables fall anims");
	menu_item_add(menu_hileler, menu_hileler, "Disable Stun Animation", ID_ANTI_STUN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"Hits doesnt stuns you");


	menu_item_add(menu_troll_hileler, menu_troll_hileler, "\t | Troll Cheats | ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL, "You need to be incar for use most of functions in this section");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Player Shooter #1", ID_PLAYER_SHOOTER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "You need to be incar for use this function");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Player Shooter #2", ID_ACTOR_SHOOTER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "You need to be incar for use this function");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Burning Cars", ID_N3X_TROLL_CAR_2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "You need to be incar for use this function");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "\t Non-Vehicle Cheats ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL, "No need to be in incar");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Googles Disco", ID_DISCO_MODE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "You should not be incar for use.");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "\tAiming Cheats", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Invalid Aim Z", ID_INVALID_AIM_Z, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Makes your body half.");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Ekran Titreþimi #1", ID_SHAKING_CAMERA,  D3DCOLOR_ARGB(255, 255, 0, 0),  NULL, "While shooting, their screen gonna shake!");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Ekran Titreþimi #2", ID_SHAKING_CAMERA2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "While shooting, their screen gonna shake!");

	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "\t Weapon Cheats ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Auto 2-2", ID_AUTO2_2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Auto 2-2");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Oto Sawn-Deagle", ID_AUTO_SAWN_DEAGLE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"Sawn & Deagle");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Double Gun #1", ID_DOUBLE_GUN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Your can set settings on AntTweakBar menu");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Double Gun #2", ID_DOUBLE_GUN_2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Your can set settings on AntTweakBar menu");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Auto C BUG #1", ID_AUTO_CBUG, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"Works with deagle");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Auto C BUG #2", ID_AUTO_CBUG2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Works with deagle");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Rapid Fire", ID_RAPID_FIRE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "You need to press SPACE for send bullets.");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "No spread", ID_NO_RECOIL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "No spread");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "No Reload", ID_NO_RELOAD_BUG, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "No Reload");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Return the Damage", ID_RETURN_THE_DAMAGE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "It returns the damage to sender, you need to have a weapon in hand.");
	snprintf(name, sizeof(name), "Weapon Damage: %d/Per Shot", (int)set.WeaponCheats.Weapon_Damage);
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, name, ID_WEAPON_DAMAGE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	/*	Ýngilizce Sürüm. Rapid en az 200 MS.
		Türkçe Low level. Rapid 150 MS
		Türkçe High Sürüm. Rapid Delay en az 50-100MS*/

	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, "\t Aim Cheats ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, "Auto Aim | Rage[Shortcut: Z]", ID_AUTO_AIM_RAGE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Spins 180 Degree | You can set body part on AntTweakBar menu");
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, "Auto Aim | Legit[Shortcut L]", ID_AUTO_AIM_LEGIT, D3DCOLOR_ARGB(255, 255, 0, 0), NULL,"Smooth Aim | Not useful.");
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, "Silent Aim", ID_SILENT_AIMBOT, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Shortcut key is 'X', but you can change it on .ini");
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, "Wall Shot", ID_SHOOT_THROUGH_WALLS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "To able use wall shot, you need to enable silent aim");
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, " | FOR MORE GO TO ANTTWEAKBAR MENU! ~ RapidFire | ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	//menu_item_add(menu_aim_hileleri, menu_aim_hileleri, " | Bu menüden kaldýrýlmýþtýr. | ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	//menu_item_add(menu_aim_hileleri, menu_aim_hileleri, " | Ayarlara F2 menü üzerinden {00FF00}ulaþabilirsin. | ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "\t | InCar Cheats |", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Crazy Car #1", ID_CRAZY_CAR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Crazy Car #2", ID_CRAZY_CAR2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Crazy Car #3", ID_CRAZY_CAR3, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Crazy Car #4", ID_CRAZY_CAR4, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Pick Cars", ID_PICK_CAR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Ex Attacker", ID_EX_ATTACKER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Vehicle Component Flooder", ID_VEHICLE_COMPONENT_FLOODER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "\t | Araç Fonksiyonlarý | ", ID_NONE, D3DCOLOR_ARGB(255,255,255,0),"Bu kategorideki çoðu hile, %100 Belirgindir. | BAN yiyebilirsin.");
	//menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Yüksek FPS ile araç hileler kullanmak = BAN sebebi", NULL, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	//menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Bu kategorideki çoðu hile, %100 Bellidir | BAN yiyebilirsin.", NULL, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	//menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Hilelerini kullanýrken otomatik olarak araçlar patlasýn mý?", ID_MAKE_ZERO_HP_FOR_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Car Shooter #1", ID_CAR_SHOOTER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Car Shooter #2", ID_CAR_SHOOTER2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);//Çalýþmýyor.
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Car Shooter #3", ID_CAR_SHOOTER3, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Follow #1", ID_CAR_FOLLOWS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Follow #2", ID_CAR_FOLLOWS2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Follow #3", ID_CAR_FOLLOWS3, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Car Circle #1", ID_CAR_CIRCLE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Car Circle #2", ID_CAR_CIRCLE2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Floating #1", ID_CAR_FLOATING, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Floating #2", ID_CAR_FLOATING2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Floating #3", ID_CAR_FLOATING3, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Fucker #1", ID_CAR_FUCKER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Fucker #2", ID_CAR_FUCKER2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Fucker #3", ID_CAR_FUCKER3, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);//Bi bak
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Tornado #1", ID_CAR_TORNADO, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Tornado #2", ID_CAR_TORNADO2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Hop Cars", ID_HOP_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Remove Cars", ID_REMOVE_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Falling Cars", ID_CARS_FALLING, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Tower", ID_CARS_TOWER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Fly Cars", ID_CARS_FLYING, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Magnet", ID_CARS_MAGNET, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Cars Line", ID_CAR_LINE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Shaking Cars", ID_SHAKING_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Car Sun", ID_CAR_SUN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Car Lagger", ID_CAR_POSITION_LAGGER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Dönen Araçlar", ID_CAR_SPINNING, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Pozisyon deðerlerini diðer menüden ayarlayabilirsin.");
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Smoking Cars", ID_CAR_SMOKING, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Remove Cars", ID_REMOVE_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Explode Cars", ID_EXPLODE_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Delete Cars", ID_DELETE_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Colorize Cars", ID_CAR_COLORIZE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);//Crash.
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Black & White Cars", ID_CAR_BLACK_WHITE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL); // ?
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Pink Cars", ID_CAR_PINK, D3DCOLOR_ARGB(255, 255, 0, 0), NULL); // ?
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Car Troller #1", ID_FOLLOW_TROLL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Car Troller #2", ID_ZFOLLOW_TROLL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Car Troller #3", ID_CAR_UNNAMED_TROLL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_flooderler, menu_flooderler, "\t Chat Hacks ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_flooderler, menu_flooderler, "Flooder #1", ID_PROJECT_FLOODER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_flooderler, menu_flooderler, "PM Flooder", ID_PM_LAGGER_FLOODER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "PM Flooder Settings in AntTweakBar");
	menu_item_add(menu_flooderler, menu_flooderler, "Matrix Flooderi #1", ID_MATRIX_FLOODER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
 
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "\t Visual Cheats ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Black Chams | Peds", ID_BLACK_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Black Chams | Peds & WireFrame", ID_BLACK_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Black Chams | Weapons", ID_BLACK_CHAMS_WEAPONS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Black Chams | Weapons & WireFrame", ID_BLACK_CHAMS_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Red Chams | Peds", ID_RED_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Red Chams | Peds & WireFrame", ID_RED_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Red Chams | Weapons", ID_RED_CHAMS_WEAPONS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Red Chams | Weapons & WireFrame", ID_RED_CHAMS_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Green Chams | Peds", ID_GREEN_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Green Chams | Peds & WireFrame", ID_GREEN_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Green Chams | Weapons", ID_GREEN_CHAMS_WEAPONS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Green Chams | Weapons & WireFrame", ID_GREEN_CHAMS_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Blue Chams | Peds", ID_BLUE_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Blue Chams | Peds & WireFrame", ID_BLUE_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Blue Chams | Weapons", ID_BLUE_CHAMS_WEAPONS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Blue Chams | Weapons & WireFrame", ID_BLUE_CHAMS_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Golden Chams | Peds", ID_GOLD_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Golden Chams | Peds + WireFrame", ID_GOLD_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Golden Chams | Silahlar", ID_GOLD_CHAMS_WEAPONS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Golden Chams | Peds + WireFrame", ID_GOLD_CHAMS_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Original Chams | Peds", ID_ORIGINAL_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Original Chams | Peds & WireFrame", ID_ORIGINAL_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Original Chams | Weapons", ID_ORIGINAL_WEAPONS_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Original Chams | Weapons & WireFrame", ID_ORIGINAL_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "\t Visual Cheats #2 ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Tag Admin Peds", ID_DRAW_ADMINS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Tag Friend Peds", ID_DRAW_FRIENDS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "Oyuncularýn HitBoXunu Gör[Lag-Shot Sunucularý]", ID_LAGSHOT_POINT, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Bone ESP", ID_BONE_ESP, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Tracer ESP", ID_TRACER_ESP, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Box ESP", ID_PLAYER_BOX_ESP, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "3D Informer", ID_3D_INFORMER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Weapon Information", ID_WEAPON_INFO, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "Oyuncularýn Etiketlerinde Durum Bilgisi", ID_STATUS_INFO, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "\t Visual Cheats #3 ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Render New HUD", ID_RENDER_NEW_HUD, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "See Admins List", ID_ADMINS_LIST, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "See Friends List", ID_FRIENDS_LIST, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, " Other Vision Assistances ", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "Draw Admins[TEXT ON SKIN]", ID_DRAW_ADMINS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "See Players HitBoX[for Lag-Comp Off]", ID_LAGSHOOT_POINT, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "See Players HitBoX[RainBow]", ID_LAGSHOOT_RAINBOW_POINT, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "Bone ESP Players", ID_BONE_ESP, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "Tracer ESP Players", ID_TRACER_ESP, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "Box ESP Players", ID_PLAYER_BOX_ESP, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "3D Information", ID_3D_INFORMER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "Draw New HUD", ID_RENDER_NEW_HUD_MENU, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "See a list of Admins", ID_SEE_ADMINS_LIST, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "See a list of Your Friends", ID_SEE_FRIENDS_LIST, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_korumalar, menu_korumalar, "\t Game Protections ", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Bullet Crasher", ID_ANTI_BULLET_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Invalid Bullets Crasher", ID_ANTI_INVALIDBULLETS_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Passenger Crasher", ID_ANTI_PASSENGER_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Roll Crasher", ID_ANTI_ROLL_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Car Trollers", ID_ANTI_CAR_TROLLER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_korumalar, menu_korumalar, "Anti Warning Crasher", ID_ANTI_WARNINGS_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Sohbet ekranýndaki warningleri sýnýrsýzlaþtýrýr.");
	//menu_item_add(menu_korumalar, menu_korumalar, "Anti Loading", ID_ANTI_LOADING_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Beyaz & Sarý Ekran hatasýný önler.");
	menu_item_add(menu_korumalar, menu_korumalar, "No Collision Actors", ID_NO_COLLISION_ACTORS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "No Collision Vehicles", ID_NO_COLLISION_VEHICLES, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Shaking Camera", ID_ANTI_SHAKING_CAMERA, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "\t Anti Trailer Crashers ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Trailer Crasher #1", ID_ANTI_TRAILERSYNC_POS_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Trailer Crasher #2", ID_ANTI_TRAILERSYNC_FSPIN_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Trailer Crasher #3", ID_ANTI_TRAILERSYNC_FSPEED_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);


	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, M0D_VERSION, ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "Project Developers:", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "RapidFire", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "Special Thanks to:", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "DarkNeX, FYP, Gigant, dark, RcK, MasterZero and Stickey", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "https://discord.gg/ZTn7DVN33W", ID_NONE, MENU_COLOR_SEPARATOR, NULL);

#else

	menu_item_add(menu_main, NULL, "\t› GTA Hileleri", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_main, menu_cheats, "› Hileler", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_weapons, "› Silahlar", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_vehicles, "› Araçlar", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_teleports, "› Teleportlar", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_main, menu_misc, "› Çeþitli", ID_NONE, MENU_COLOR_DEFAULT, NULL);
	snprintf(name, sizeof(name), "› GTA Modifikasyonlarý (%d/%d)", iGTAPatchesCount, INI_PATCHES_MAX);
	menu_item_add(menu_main, menu_patches, name, ID_NONE, MENU_COLOR_DEFAULT, NULL);

	/* main menu (samp specific) */
	if (g_dwSAMP_Addr != NULL)
	{
		menu_item_add(menu_main, NULL, "\t› SA-MP Hileleri", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
		menu_item_add(menu_main, menu_players, "› Oyuncular", ID_NONE, MENU_COLOR_DEFAULT, NULL);
		snprintf(name, sizeof(name), "› Favori Sunucu Listesi (%d/%d)", iServersCount, INI_SERVERS_MAX);
		menu_item_add(menu_main, menu_servers, name, ID_NONE, MENU_COLOR_DEFAULT, NULL);
		menu_item_add(menu_main, menu_sampmisc, "› SA:MP Çeþitli.", ID_NONE, MENU_COLOR_DEFAULT, NULL);
		snprintf(name, sizeof(name), "› SA:MP Paketleri (%d/%d)", iSAMPPatchesCount, INI_SAMPPATCHES_MAX);
		menu_item_add(menu_main, menu_samppatches, name, ID_NONE, MENU_COLOR_DEFAULT, NULL);
	}


	menu_item_add(menu_hileler, menu_hileler, "\t | Hileler |", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL, "Genel hileler burada yer alýr.");
	menu_item_add(menu_hileler, menu_hileler, "Uçma Hilesi", ID_GOD_FLY, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Diðer menüden ayarlayabilirsin hýz deðerini.");
	menu_item_add(menu_hileler, menu_hileler, "Harita-Hýz Hilesi", ID_MAPRUN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Diðer menüden ayarlayabilirsin hýz deðerini.");
	menu_item_add(menu_hileler, menu_hileler, "\t | Görünmez Modlar |", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL, "Bu kategorideki modlarý sadece diðerleri görebilir.");
	menu_item_add(menu_hileler, menu_hileler, "Hayalet Modu[Oyuncularýn içinden geçebilme]", ID_GHOST_MODE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "GhostMode, Oyuncularýn içinden geçebilirsin.");
	menu_item_add(menu_hileler, menu_hileler, "Dönüþ Modu #1[Paraþütle 360 derece dön]", ID_TWIST_MODE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Paraþütle 360 derece dönersin, fakat bunu göremezsin.");
	menu_item_add(menu_hileler, menu_hileler, "Dönüþ Modu #2[Elindeki silah ile 360 derece dön]", ID_TWIST_MODE_2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "360 Derece dönersin, fakat bunu göremezsin.");
	menu_item_add(menu_hileler, menu_hileler, "Rota Modu", ID_CAMERA_MODE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Rotasyon modu, GTA-VC'deki gibi dönebilirsin.");
	menu_item_add(menu_hileler, menu_hileler, "Random Dördeyler #1", ID_RAND_QUATS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Karakterin sürekli þekil deðiþtirir, fakat bunu göremezsin.");
	menu_item_add(menu_hileler, menu_hileler, "Random Dördeyler #2", ID_RAND_QUATS_FIX, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Eðer Random Dördeyler #1 anti hileye yakalanýyorsa, bunu kullan.");
	menu_item_add(menu_hileler, menu_hileler, "Ters Yürüyüþ", ID_UPSIDE_DOWN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Ters dönersin, fakat bunu göremezsin.");
	menu_item_add(menu_hileler, menu_hileler, "Ters Yürüyüþ #2", ID_UPSIDE_DOWN_FIX, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Eðer Ters Yürüyüþ #1 anti hileye yakalanýyorsa, bunu kullan.");
	menu_item_add(menu_hileler, menu_hileler, "\t | Görünmez Modlar |", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_hileler, menu_hileler, "Duvarlardan Geç", ID_WALK_THROUGH_WALLS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Not:Hatalý olabilir.");
	menu_item_add(menu_hileler, menu_hileler, "Hýz Hilesi[Ayarlarý ATB menüde bulabilirsin]", ID_SPEED_WALK, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Ayarlar diðer menüde.");
	menu_item_add(menu_hileler, menu_hileler, "Can 30'un altýnda olunca Oto Spawn ol", ID_DO_NOT_SEND_KILL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Bazý sunucularda çalýþmayabilir.");
	menu_item_add(menu_hileler, menu_hileler, "Öldüðün yerde doð", ID_SPAWN_AT_DEATH_POS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Bazý sunucularda çalýþmayabilir.");
	menu_item_add(menu_hileler, menu_hileler, "Can Pulsator", ID_HP_PULSATOR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "HUD'da, can deðerin sürekli deðiþir.");
	menu_item_add(menu_hileler, menu_hileler, "Zýrh Pulsator", ID_ARMOR_PULSATOR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "HUD'da, zýrh deðerin sürekli deðiþir.");
	menu_item_add(menu_hileler, menu_hileler, "Karakterini Deforme Et[Tuþlarý: 7-8-9-0]", ID_PLAYER_DEFORMER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Karakter deformasyonu, tuþlarý .ini'den ayarlayabilirsin.");
	menu_item_add(menu_hileler, menu_hileler, "Ölünce Hemen Spawn Ol", ID_FAST_RESPAWN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Öldüðün an spawn olursun, bazý sunucularda çalýþmayabilir.");
	menu_item_add(menu_hileler, menu_hileler, "Çakýlma Animasyonunu Kapat", ID_NO_FALL_ANIMATION, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Düþerken çakýlmazsýn.");
	menu_item_add(menu_hileler, menu_hileler, "Sarsýlma Animasyonunu Kapat", ID_ANTI_STUN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Ýsabet aldýðýn an sarsýlmazsýn.");


	menu_item_add(menu_troll_hileler, menu_troll_hileler, "\t | Troll Hileler | ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL, "Bir kýsmý F2 menüsünde olmak üzere, Troll hileler burada yer alýr.");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Oyuncu Fýrlatýcý #1", ID_PLAYER_SHOOTER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Kullanabilmek için bir aracýn içinde olmalýsýn.");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Oyuncu Fýrlatýcý #2", ID_ACTOR_SHOOTER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Kullanabilmek için bir aracýn içinde olmalýsýn.");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Alev Alan Araç", ID_N3X_TROLL_CAR_2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Kullanabilmek için bir aracýn içinde olmalýsýn.");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "\t Araçsýz Troll Hileleri ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL, "Araç içinde olmaný gerektirmez.");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Gözlük Diskosu", ID_DISCO_MODE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Çalýþmasý için araçta olmaman gerek, diðer oyuncularýn ekranýný bozar...");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "\tNiþan Modifikasyonlarý ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Geçersiz Aim Z Ekseni", ID_INVALID_AIM_Z, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Niþan aldýðýn zaman bedenin yarým olur, menüden senkronize edebilirsin.");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Ekran Titreþimi #1", ID_SHAKING_CAMERA, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Silahla ateþ ettiðin zaman diðer oyuncularýn ekraný titrer.");
	menu_item_add(menu_troll_hileler, menu_troll_hileler, "Ekran Titreþimi #2", ID_SHAKING_CAMERA2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Silahla ateþ ettiðin zaman diðer oyuncularýn ekraný titrer.");

	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "\t Silah Hileleri ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Oto Sawn-Off", ID_AUTO2_2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Sawn-Off ile 2-2 Bug yapabilirsin.");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Oto Sawn-Deagle", ID_AUTO_SAWN_DEAGLE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Çifte Silah #1", ID_DOUBLE_GUN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Bir Deagle, bir shotgun sýkarsýn, ayarlarýný diðer menüde bulabilirsin.");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Çifte Silah #2", ID_DOUBLE_GUN_2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Ayarlarýný diðer menüde bulabilirsin.");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Oto CBug #1", ID_AUTO_CBUG, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Deagle ile oto c bug yapmaný saðlar.");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Oto CBug #2", ID_AUTO_CBUG2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Süper Tarama", ID_RAPID_FIRE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Space tuþu ile çalýþýr | RapidFire, çok güçlü bir fonksiyon.");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Sekmeyen Mermiler", ID_NO_RECOIL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Ateþ ederken silahýn geri tepmez.");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Sýnýrsýz Mermi", ID_NO_RELOAD_BUG, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Sýnýrsýz Mermi | Bazý sunucularda fark edilebilirsin.");
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, "Alýnan hasarý döndür", ID_RETURN_THE_DAMAGE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Sana ateþ eden birine otomatik ateþ edersin | Elinde silah olmalý.");
	snprintf(name, sizeof(name), "Silah Hasarý: %d/Atýþ baþý", (int)set.WeaponCheats.Weapon_Damage);
	menu_item_add(menu_silah_hileleri, menu_silah_hileleri, name, ID_WEAPON_DAMAGE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	/*	Ýngilizce Sürüm. Rapid en az 200 MS.
		Türkçe Low level. Rapid 150 MS
		Türkçe High Sürüm. Rapid Delay en az 50-100MS*/

	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, "\t Niþan Desteði ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, "Auto Aim | Rage[Kýsayol: Z Tuþu]", ID_AUTO_AIM_RAGE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "180 Derece dönüþlü | Niþan alýnan bölgeyi Aim bölümünden ayarlayabilirsin.");
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, "Auto Aim | Legit[Kýsayol: L Tuþu]", ID_AUTO_AIM_LEGIT, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Akýcý hareketler | Kýsayolu 'L' tuþu, pek kullanýþlý deðil.");
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, "Silent Aim", ID_SILENT_AIMBOT, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Kýsayolu 'X' tuþu, fakat .ini'den deðiþtirebilirsin.");
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, "Wall Shot", ID_SHOOT_THROUGH_WALLS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Kullanabilmek için, Silent Aimin açýk olmasý gerekir.");
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, " | Silent aimbot, spinbot v.b için ayarlar, | ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, " | Bu menüden kaldýrýlmýþtýr. | ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_aim_hileleri, menu_aim_hileleri, " | Ayarlara F2 menü üzerinden {00FF00}ulaþabilirsin. | ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);


	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "\t | Araç-Ýçi Fonksiyonlar |", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL, "Buradaki faktörlerin çoðunu kullanmak için araçta olmalýsýn.");
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "\tAraç jant ve renk ayarlarýný diðer menüde bulabilirsin!", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Renkleri #1", ID_CRAZY_CAR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Aracýn renklerini sürekli deðiþtirir.");
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Jantlarý #2", ID_CRAZY_CAR2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Aracýn jantlarýný sürekli deðiþtirir.");
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Renkleri #3", ID_CRAZY_CAR3, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Aracýn paintjoblarýný sürekli deðiþtirir.");
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Renkleri(Siyah-Beyaz) #4", ID_CRAZY_CAR4, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Sadece Siyah & Beyaz Renk");
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Sürükle", ID_PICK_CAR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Sað týk & Sol týk ile çalýþýr.");
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Ölüm Saldýrýsý", ID_EX_ATTACKER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Parça Flooderi", ID_VEHICLE_COMPONENT_FLOODER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Kullanmak için araç içinde olmalýsýn, diðer oyuncularýn FPS'ini düþürür.");
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "\t | Araç Fonksiyonlarý | ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), "Bu kategorideki çoðu hile, %100 Belirgindir. | BAN yiyebilirsin.");
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Yüksek FPS ile araç hileler kullanmak = BAN sebebi", NULL, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Bu kategorideki çoðu hile, %100 Bellidir | BAN yiyebilirsin.", NULL, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Hilelerini kullanýrken otomatik olarak araçlar patlasýn mý?", ID_MAKE_ZERO_HP_FOR_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Fýrlatýcý #1", ID_CAR_SHOOTER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Fýrlatýcý #2", ID_CAR_SHOOTER2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);//Çalýþmýyor.
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Fýrlatýcý #3", ID_CAR_SHOOTER3, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Takibi #1", ID_CAR_FOLLOWS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Takibi #2", ID_CAR_FOLLOWS2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Takibi #3", ID_CAR_FOLLOWS3, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Dairesi #1", ID_CAR_CIRCLE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Dairesi #2", ID_CAR_CIRCLE2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Yüzen Araçlar #1", ID_CAR_FLOATING, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Yüzen Araçlar #2", ID_CAR_FLOATING2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Yüzen Araçlar #3", ID_CAR_FLOATING3, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Silkeyici #1", ID_CAR_FUCKER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Silkeyici #2", ID_CAR_FUCKER2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Silkeyici #3", ID_CAR_FUCKER3, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);//Bi bak
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Kasýrgasý #1", ID_CAR_TORNADO, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Kasýrgasý #2", ID_CAR_TORNADO2, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araçlarý Hoplat", ID_HOP_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araçlarý Respawn Et", ID_REMOVE_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Düþen Araçlar", ID_CARS_FALLING, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Kulesi", ID_CARS_TOWER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Uçan Araçlar", ID_CARS_FLYING, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Çekici", ID_CARS_MAGNET, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Satýrý", ID_CAR_LINE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Titreyen Araçlar", ID_SHAKING_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Güneþi", ID_CAR_SUN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Pozisyon Lagger", ID_CAR_POSITION_LAGGER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Pozisyon deðerlerini diðer menüden ayarlayabilirsin.");
	//menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Dönen Araçlar", ID_CAR_SPINNING, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Pozisyon deðerlerini diðer menüden ayarlayabilirsin.");
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Dumanlý Araçlar", ID_CAR_SMOKING, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araçlarý Kaldýr", ID_REMOVE_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araçlarý Patlat", ID_EXPLODE_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araçlarý Sil", ID_DELETE_CARS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "\t Araç Renk/Jantlarý ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araçlarý Renklendir", ID_CAR_COLORIZE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);//Crash.
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Siyah & Beyaz Araçlar", ID_CAR_BLACK_WHITE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL); // ?
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Pembe Renk Araçlar", ID_CAR_PINK, D3DCOLOR_ARGB(255, 255, 0, 0), NULL); // ?
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "\t Araç Troll Fonksiyonlarý ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Trolleyici #1", ID_FOLLOW_TROLL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Trolleyici #2", ID_ZFOLLOW_TROLL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_arac_hileleri, menu_arac_hileleri, "Araç Trolleyici #3", ID_CAR_UNNAMED_TROLL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_flooderler, menu_flooderler, "\t Chat Faktörleri ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL, "Flooderlerin ayarlarýný diðer menüden yapabilirsin.");
	menu_item_add(menu_flooderler, menu_flooderler, "Flooder #1", ID_PROJECT_FLOODER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_flooderler, menu_flooderler, "PM Flooder", ID_PM_LAGGER_FLOODER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "PM Floodlayýcý, diðer menüde bulabilirsin ayarlarý.");
	menu_item_add(menu_flooderler, menu_flooderler, "Matrix Flooderi #1", ID_MATRIX_FLOODER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Pek kullanýþlý deðil.");

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "\t Görüþ Destekleri ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Siyah Chams Sadece Skinler", ID_BLACK_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Siyah Chams Skinler + WireFrame", ID_BLACK_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Siyah Chams Silahlar", ID_BLACK_CHAMS_WEAPONS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Siyah Chams Silahlar + WireFrame", ID_BLACK_CHAMS_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Kýrmýzý Chams Sadece Skinler", ID_RED_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Kýrmýzý Chams Skinler + WireFrame", ID_RED_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Kýrmýzý Chams Silahlar", ID_RED_CHAMS_WEAPONS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Kýrmýzý Chams Silahlar + WireFrame", ID_RED_CHAMS_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Yeþil Chams Sadece Skinler", ID_GREEN_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Yeþil Chams Skinler + WireFrame", ID_GREEN_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Yeþil Chams Silahlar", ID_GREEN_CHAMS_WEAPONS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Yeþil Chams Silahlar + WireFrame", ID_GREEN_CHAMS_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Mavi Chams Sadece Skinler", ID_BLUE_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Mavi Chams Skinler + WireFrame", ID_BLUE_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Mavi Chams Silahlar", ID_BLUE_CHAMS_WEAPONS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Mavi Chams Silahlar + WireFrame", ID_BLUE_CHAMS_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Altýn Chams Sadece Skinler", ID_GOLD_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Altýn Chams Skinler + WireFrame", ID_GOLD_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Altýn Chams Silahlar", ID_GOLD_CHAMS_WEAPONS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Altýn Chams Silahlar + WireFrame", ID_GOLD_CHAMS_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Orijinal Chams Sadece Skinler", ID_ORIGINAL_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Orijinal Chams Skinler + WireFrame", ID_ORIGINAL_CHAMS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Orijinal Chams Silahlar", ID_ORIGINAL_WEAPONS_CHAMS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Orijinal Chams Silahlar + WireFrame", ID_ORIGINAL_WEAPONS_WIREFRAME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

	menu_item_add(menu_wallhacklar, menu_wallhacklar, "\t Görüþ Destekleri #2 ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Adminlerin üzerini etiketle", ID_DRAW_ADMINS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Dostlarýn üzerini etiketle", ID_DRAW_FRIENDS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "Oyuncularýn HitBoXunu Gör[Lag-Shot Sunucularý]", ID_LAGSHOT_POINT, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Ýskelet Oyuncular", ID_BONE_ESP, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Çizgili Oyuncular", ID_TRACER_ESP, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Kutulu Oyuncular", ID_PLAYER_BOX_ESP, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "3D Bilgilendirici", ID_3D_INFORMER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Oyuncularýn Etiketlerinde Silah Bilgisi", ID_WEAPON_INFO, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_wallhacklar, menu_wallhacklar, "Oyuncularýn Etiketlerinde Durum Bilgisi", ID_STATUS_INFO, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "\t Görüþ Destekleri #3 ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Yeni Menüyü Çiz", ID_RENDER_NEW_HUD, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Adminler Listesini gör", ID_ADMINS_LIST, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_wallhacklar, menu_wallhacklar, "Arkadaþlar Listesini gör", ID_FRIENDS_LIST, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	
	menu_item_add(menu_korumalar, menu_korumalar, "\t Oyun Korumalarý ", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Bullet Crasher", ID_ANTI_BULLET_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Eski nesil bullet crasheri önler.");
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Invalid Bullets Crasher", ID_ANTI_INVALIDBULLETS_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Invalid Bullet Crasheri önler");
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Passenger Crasher", ID_ANTI_PASSENGER_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Passenger Crasheri önler.");
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Roll Crasher", ID_ANTI_ROLL_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Roll Crasheri önler.");
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Araç Trolleyiciler", ID_ANTI_CAR_TROLLER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Sana karþý iTroll veya herhangi bir araç trollü kullanan birini önler.");
	//menu_item_add(menu_korumalar, menu_korumalar, "Anti Warning Crasher", ID_ANTI_WARNINGS_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Sohbet ekranýndaki warningleri sýnýrsýzlaþtýrýr.");
	//menu_item_add(menu_korumalar, menu_korumalar, "Anti Loading", ID_ANTI_LOADING_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Beyaz & Sarý Ekran hatasýný önler.");
	menu_item_add(menu_korumalar, menu_korumalar, "Oyuncularýn içinden geçebilmek", ID_NO_COLLISION_ACTORS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Ýngilizce Adý: No Collision");
	menu_item_add(menu_korumalar, menu_korumalar, "Araçlarýn içinden geçebilmek", ID_NO_COLLISION_VEHICLES, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Ýngilizce Adý: No Collision");
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Geçersiz Aim Z Ekseni", ID_ANTI_INVALID_AIM_Z, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Invalid Aim Z'nin yarým beden oluþturmasýný önler.");
	menu_item_add(menu_korumalar, menu_korumalar, "Anti Shaking Camera[Titreþimli Ekran]", ID_ANTI_SHAKING_CAMERA, D3DCOLOR_ARGB(255, 255, 0, 0), NULL, "Ekran titreþimini önler.");
	menu_item_add(menu_korumalar, menu_korumalar, "", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "\t Trailer Crasher Korumalarý ", ID_NONE, D3DCOLOR_ARGB(255, 255, 255, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Trailer Crasher Korumasý #1", ID_ANTI_TRAILERSYNC_POS_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Trailer Crasher Korumasý #2", ID_ANTI_TRAILERSYNC_FSPIN_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_korumalar, menu_korumalar, "Trailer Crasher Korumasý #3", ID_ANTI_TRAILERSYNC_FSPEED_CRASHER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);

#endif

#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
	
	menu_item_add(menu_b0tz, menu_b0tz, " RapidFire'z Edit B0Tz ", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, " BoT Komutlarý ", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "/.botisim - Farklý isimde bot atmak için", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "/.botpmid - Bot PM Floodlayýcýnýn Hedefini seçmek için", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "/.botclassid - Bot Sýnýf ID'sini seçmek için. 0-300 Arasý", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "/.bot_fakekill - Botun Fake Kill yapacaðý oyuncu", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "/.botrnick - Sunucuya Random karakterlerle bot at", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "/.botrandnick - Yeni Random karakterlerle sunucuya bot at", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, " BoT Komutlarý ", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, " Bot Fonksiyonlarý ", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Bot at", ID_ADD_B0T, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "\aSayýlý bot at: //", ID_ADD_NUMBER_B0T, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "1 Bot Spawn et", ID_B0T_SPAWN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Bütün botlarý Spawn et", ID_B0T_SPAWN_ALL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "//--------Bot Baðlantý Fonksiyonlarý ---------//", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Botu sunucudan çýkart", ID_DELETE_B0T, D3DCOLOR_ARGB(191, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Bütün Botlarý Sunucudan Çýkart", ID_DELETE_ALL_B0TZ, D3DCOLOR_ARGB(255,255,0,0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Bütün Botlarý Sunucudan Çýkart[Zaman Aþýmý/Timeout]", ID_DELETE_ALL_B0TS_TIMEOUT, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "Bütün Botlarý Sunucudan Çýkart[Kick/Ban]", ID_DELETE_ALL_B0TS_KICKED, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "//--------Bot Baðlantý Fonksiyonlarý ---------//", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, " Bot OnFoot Fonksiyonlarý ", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Botlar seni takip etsin mi?", ID_B0T_FOLLOW_ME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Bot Dairesi", ID_B0T_CIRCLE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Bot Fýrlatýcý", ID_B0T_SH00TER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Bot Güneþi", ID_B0T_SUN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Saldýrgan Botlar", ID_B0T_ATTACKER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Trolleyen Botlar #1[ELEVATOR]", ID_B0T_ELEVATOR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Trolleyen Botlar #2[JETPACK-E]", ID_B0T_JETPACK_ELEVATOR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Trolleyen Botlar #3[SLAPPER]", ID_B0T_SLAPPER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "Troll Botlar #4", ID_B0T_FUCK, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "//-------- Bot Fonksiyon Ayarlarý ---------//", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "\aBotlar ile oyuncu arasýndaki mesafe: //", ID_B0T_DISTANCE_BETWEEN_PLAYER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "\aBotlarýn aralarýndaki mesafe: //", ID_B0T_DISTANCE_BETWEEN_B0TS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "\aSaldýrgan Botlar Silah ID: //", ID_B0T_ATTACKER_WEAPON, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "\aBot Baðlantý Gecikme süresi: //", ID_B0T_DELAY, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "\aBot Hedef ID: //", ID_B0T_SELECT_TARGET, MENU_COLOR_DEFAULT, NULL);
	menu_item_add(menu_b0tz, menu_b0tz, "\aBot Yakýndakileri Kullan", ID_B0T_USE_NEAREST_TARGET, MENU_COLOR_DEFAULT, NULL);


	//menu_item_add(menu_b0tz, menu_b0tz, "  RakNet Bots ", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, " Bot Funcs ", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "Add Bot", ID_ADD_B0T, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "\a Add Bot With Number: //", ID_ADD_NUMBER_B0T, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "Spawn Bot[Your Class[Team-Skin]]", ID_B0T_SPAWN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "Spawn all bots[Random Classes]", ID_B0T_SPAWN_ALL, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "//--------Bot Connection Settings---------//", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "Disconnect 1 Bot", ID_DELETE_B0T, D3DCOLOR_ARGB(191, 255, 0, 0), NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "Disconnect All Bots[By Leave]", ID_DELETE_ALL_B0TZ, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "Disconnect All Bots[By Timeout]", ID_DELETE_ALL_B0TS_TIMEOUT, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "//--------Bot Connection Settings---------//", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, " Bot OnFoot Funcs ", ID_NONE, MENU_COLOR_SEPARATOR, NULL); 
	//menu_item_add(menu_b0tz, menu_b0tz, "Bot Follow Me", ID_B0T_FOLLOW_ME, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);// V1.5
	////menu_item_add(menu_b0tz, menu_b0tz, "Bot Circle", ID_B0T_CIRCLE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL); // V1.5
	////menu_item_add(menu_b0tz, menu_b0tz, "Bot Shooter", ID_B0T_SH00TER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL); // V1.5
	////menu_item_add(menu_b0tz, menu_b0tz, "Bot Sun", ID_B0T_SUN, D3DCOLOR_ARGB(255, 255, 0, 0), NULL); // V1.5
	//////menu_item_add(menu_b0tz, menu_b0tz, "Attacker Bots[Not working well]", ID_B0T_ATTACKER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);// V1.5
	////menu_item_add(menu_b0tz, menu_b0tz, "Troller Bots #1[ELEVATOR]", ID_B0T_ELEVATOR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL); // which ver?// V1.5
	////menu_item_add(menu_b0tz, menu_b0tz, "Troller Bots #2[JETPACK-ELEVATOR]", ID_B0T_JETPACK_ELEVATOR, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);// V1.5
	////menu_item_add(menu_b0tz, menu_b0tz, "Troller Bots #3[SLAPPER]", ID_B0T_SLAPPER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);// V1.5
	////menu_item_add(menu_b0tz, menu_b0tz, "Bot Fuck #1", ID_B0T_FUCK, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);// V1.5
	//menu_item_add(menu_b0tz, menu_b0tz, "", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	//menu_item_add(menu_b0tz, menu_b0tz, "//-------- Bot Settings ---------//", ID_NONE, MENU_COLOR_SEPARATOR, NULL);// V1.5
	//menu_item_add(menu_b0tz, menu_b0tz, "\aBots Distance From Me: //", ID_B0T_DISTANCE_BETWEEN_PLAYER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);// V1.5
	//menu_item_add(menu_b0tz, menu_b0tz, "\aBots Distance From Bots: //", ID_B0T_DISTANCE_BETWEEN_B0TS, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);// V1.5
	////menu_item_add(menu_b0tz, menu_b0tz, "\aAttacker Bots Weapon ID: //", ID_B0T_ATTACKER_WEAPON, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);// V1.5
	//menu_item_add(menu_b0tz, menu_b0tz, "\aBot Connection Delay: //", ID_B0T_DELAY, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);// V1.5
	//menu_item_add(menu_b0tz, menu_b0tz, "\aBot Target ID: //", ID_B0T_SELECT_TARGET, MENU_COLOR_DEFAULT, NULL);// V1.5
	//menu_item_add(menu_b0tz, menu_b0tz, "\aBot Use Nearest Players as Target", ID_B0T_USE_NEAREST_TARGET, MENU_COLOR_DEFAULT, NULL);// V1.5
 //
#endif

	//menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, " RakNet Operations ", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	////menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, "Connect As NPC[Type /.recon after enable]", ID_CONNECT_AS_NPC, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, "Use Fake GPCI", ID_USE_FAKE_GPCI, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);// V1.5
	//menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, "Information About My Fake GPCI[Serial-Info]", ID_INFORMATION_ABOUT_MY_FAKE_GPCI, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);// V1.5
	//menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, "NPC Connection Checker[If a NPC ajoins, tell me]", ID_NPC_CHECKER, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	///*menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, "Disable Sending Bullet Data", ID_DISABLE_SENDING_BULLET_DATA, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, "Disable Sending Player Data", ID_DISABLE_SENDING_PLAYER_DATA, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);*/
	//menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, " Connection Functions ", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	//menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, "	Fake Leave -> /.fleave ", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, "	Fake Kick  -> /.kickme ", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, "	Fake Timeout -> /.ftimeout ", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	//menu_item_add(menu_raknet_hileleri, menu_raknet_hileleri, "	For Commands -> /mod_show_cmds ", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, M0D_VERSION, ID_NONE, MENU_COLOR_SEPARATOR, NULL);
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "Anlýk Sürüm: Project Attack V4 | Yarý-Özel Sürüm", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
#endif
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "Proje Geliþtiricileri | Yapýmcýlar:", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "RapidFire, Hellside ve TheLife", ID_NONE, MENU_COLOR_SEPARATOR, NULL); 
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "https://discord.gg/ZTn7DVN33W", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	/*menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "\t  Discord ID: from hellside#6976", ID_NONE, D3DCOLOR_ARGB(255, 255, 0, 0), NULL);
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "\t  Discord ID: Rothschild#3230 ", ID_NONE, D3DCOLOR_ARGB(255, 0, 255, 0), NULL);
	menu_item_add(menu_gecikme_sureleri, menu_gecikme_sureleri, "\t  Discord ID: theodore#1923 ", ID_NONE, D3DCOLOR_ARGB(255, 0, 0, 255), NULL);*/
	/* main menu -> cheats - menu items */
	//menu_item_add( menu_cheats, menu_cheats_mods, "Vehicle upgrades", ID_CHEAT_MODS, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_cheats, menu_cheats_handling, "Change vehicle handling", ID_CHEAT_HANDLING, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_cheats, menu_cheats_money, "Para | Fixli", ID_CHEAT_MONEY, MENU_COLOR_DEFAULT, NULL, "Çoðu sunucuda fixli.");
	menu_item_add( menu_cheats, NULL, "GTA Hileleri", ID_NONE, D3DCOLOR_ARGB(255,255,255,0), NULL);
	menu_item_add( menu_cheats, menu_cheats_inv, "God Mode", ID_CHEAT_INVULN, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Restore HP", ID_CHEAT_HP, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Restore AP", ID_CHEAT_ARMOR, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, menu_cheats_weather, "Freeze Weather", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, menu_cheats_time, "Freeze Time", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Gravity: 0.0080", ID_CHEAT_GRAVITY, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Game speed: 100%", ID_CHEAT_GAME_SPEED, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Map", ID_CHEAT_MAP, MENU_COLOR_DEFAULT, NULL );
	/*menu_item_add( menu_cheats, NULL, "Render teleport texts", ID_CHEAT_TELETEXTS, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Misc. protections", ID_CHEAT_PROT, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Go to nearest empty car", ID_CHEAT_WARP_NEAR, MENU_COLOR_DEFAULT, NULL );*/
	//menu_item_add( menu_cheats, NULL, "Give Jetpack", ID_CHEAT_JETPACK, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Unlock Vehicles", ID_CHEAT_UNLOCK, MENU_COLOR_DEFAULT, NULL );
	/*menu_item_add( menu_cheats, NULL, "Keep trailers attached", ID_CHEAT_KEEP_TRAILER, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Toggle vehicle collisions", ID_CHEAT_NOCOLS, MENU_COLOR_DEFAULT, NULL );*/
	//menu_item_add( menu_cheats, NULL, "Chams", ID_CHEAT_CHAMS, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Run Style: %i, ", set.custom_runanimation_id );
	menu_item_add( menu_cheats, NULL, name, ID_CHEAT_CUSTOM_RUNSTYLE, MENU_COLOR_DEFAULT, NULL, "NUM+ | NUM- ile ayarlayabilirsin.");
	snprintf( name, sizeof(name), "Fly Speed: %0.01f", set.fly_player_speed );
	menu_item_add( menu_cheats, NULL, name, ID_CHEAT_FLY_SPEED, MENU_COLOR_DEFAULT, NULL );
	//( menu_cheats, NULL, "Disable Water Waves", ID_CHEAT_DISABLE_WAVES, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Surf", ID_CHEAT_SURF, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_cheats, NULL, "Freeze vehicle spin", ID_CHEAT_FREEZEROT, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_cheats, NULL, "Draw map lines", ID_CHEAT_MAP_DRAW_LINES, MENU_COLOR_DEFAULT, NULL );

	/* main menu -> cheats -> invulnerable */
	//menu_item_add( menu_cheats_inv, NULL, "Oyuncu Ölümsüzlüðü", ID_CHEAT_INVULN_ACTOR, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_cheats_inv, NULL, "Araç Ölümsüzlüðü", ID_CHEAT_INVULN_VEHICLE, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_cheats_inv, NULL, "Araç Lastik Korumasý", ID_CHEAT_INVULN_TIRES, MENU_COLOR_DEFAULT, NULL );

	///*menu_item_add(menu_cheats_inv, NULL, "\t", ID_NONE, MENU_COLOR_SEPARATOR, NULL);*/
	//snprintf( name, sizeof(name), "Vehicle minimum HP: %d", (int)set.hp_minimum );
	//menu_item_add( menu_cheats_inv, NULL, name, ID_CHEAT_INVULN_MIN_HP, MENU_COLOR_DEFAULT, NULL );
	//snprintf( name, sizeof(name), "Vehicle HP regeneration: %dhp/sec", (int)set.hp_regen );
	//menu_item_add( menu_cheats_inv, NULL, name, ID_CHEAT_INVULN_REGEN, MENU_COLOR_DEFAULT, NULL );
	//snprintf( name, sizeof(name), "Onfoot HP regeneration: %dhp/sec", (int)set.hp_regen );
	//menu_item_add( menu_cheats_inv, NULL, name, ID_CHEAT_INVULN_REGEN_ONFOOT, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_cheats_inv, NULL, "Single Player Enemies vulnerable", 
	//	ID_CHEAT_INVULN_DISABLE_EXTRA_INV, MENU_COLOR_DEFAULT, NULL );
	// actor invulnerability additional values
	//menu_item_add(menu_cheats_inv, NULL, "Ayarlar:", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	//menu_item_add( menu_cheats_inv, NULL, "Patlamaya karþý koruma", ID_CHEAT_INVULN_ACT_EXPL_INV, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_cheats_inv, NULL, "Düþmeye karþý koruma", ID_CHEAT_INVULN_ACT_FALL_INV, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_cheats_inv, NULL, "Yanmaya karþý koruma", ID_CHEAT_INVULN_ACT_FIRE_INV, MENU_COLOR_DEFAULT, NULL );

	/* main menu -> cheats -> money */
	/*menu_item_add( menu_cheats_money, NULL, "Give $500", ID_CHEAT_MONEY_GIVE_500, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_money, NULL, "Give $1000", ID_CHEAT_MONEY_GIVE_1000, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_money, NULL, "Give $5000", ID_CHEAT_MONEY_GIVE_5000, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_money, NULL, "Give $10000", ID_CHEAT_MONEY_GIVE_10000, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_money, NULL, "Give $20000", ID_CHEAT_MONEY_GIVE_20000, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_money, NULL, "Give $99999999", ID_CHEAT_MONEY_GIVE_99999999, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Give custom .ini value ($%d)", (int)set.money_value );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_GIVE_CUSTOM, MENU_COLOR_DEFAULT, NULL );

	menu_item_add( menu_cheats_money, NULL, "\tSettings", ID_NONE, MENU_COLOR_SEPARATOR, NULL );
	snprintf( name, sizeof(name), "Max money: %d", (int)set.money_amount_max );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_MAX, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Random min: %d", (int)set.money_amount_rand_min );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_RAND_MIN, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Random max: %d", (int)set.money_amount_rand_max );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_RAND_MAX, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Interval min: %dsec", (int)set.money_interval_rand_min );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_IVAL_MIN, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Interval max: %dsec", (int)set.money_interval_rand_max );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_IVAL_MAX, MENU_COLOR_DEFAULT, NULL );*/

	/* main menu -> cheats -> weather */
	const struct
	{
		int		id;
		char	*name;
	}

	weather_map[] =
	{
		0,
		"Blue sky",
		8,
		"Stormy",
		9,
		"Cloudy and foggy",
		10,
		"Clear blue sky",
		11,
		"Scorching hot (heat waves)",
		12,
		"Very dull, colorless, hazy",
		16,
		"Dull, cloudy, rainy",
		17,
		"Scorching hot",
		19,
		"Sandstorm",
		20,
		"Greenish fog",
		21,
		"Very dark, gradiented skyline, purple",
		22,
		"Very dark, gradiented skyline, green",
		23,
		"Variations of pale orange",
		27,
		"Variations of fresh blue",
		30,
		"Variations of dark, cloudy, teal",
		33,
		"Dark, cloudy, brown",
		34,
		"Blue, purple, regular",
		35,
		"Dull brown",
		36,
		"Extremely bright",
		40,
		"Blue, purple, cloudy",
		43,
		"Dark toxic clouds",
		44,
		"Black, white sky",
		45,
		"Black, purple sky",
		-1,
		NULL
	};
	for ( i = 0;; i++ )
	{
		if ( weather_map[i].name == NULL )
			break;
		menu_item_add( menu_cheats_weather, NULL, weather_map[i].name, ID_CHEAT_WEATHER, MENU_COLOR_DEFAULT,
					   (void *)(UINT_PTR) weather_map[i].id );
	}

	/* main menu -> cheats -> time */
	for ( i = 0; i < 24; i++ )
	{
		snprintf( name, sizeof(name), "%02d:00", i );
		menu_item_add( menu_cheats_time, NULL, name, ID_CHEAT_TIME, MENU_COLOR_DEFAULT, (void *)(UINT_PTR) i );
	}

	/* main menu -> weapons */
	menu_item_add( menu_weapons, NULL, "Enable Weapon Cheat", ID_WEAPON_ENABLE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_weapons, NULL, "Random Ammo", ID_WEAPON_RANDOM, MENU_COLOR_DEFAULT, NULL );
	for ( slot = 0; slot < 13; slot++ )
	{
		const struct weapon_entry	*weapon = weapon_list;

		snprintf( name, sizeof(name), "\tSlot %d", slot );
		menu_item_add( menu_weapons, NULL, name, ID_NONE, MENU_COLOR_SEPARATOR, NULL );

		while ( weapon->name != NULL )
		{
			if ( weapon->slot == slot )
				menu_item_add( menu_weapons, NULL, weapon->name, ID_WEAPON_ITEM, MENU_COLOR_DEFAULT, (void *)weapon );
			weapon++;
		}
	}

	/* main menu -> vehicles */
	for ( i = 0; i < VEHICLE_CLASS_COUNT; i++ )
	{
		struct menu *menu = menu_new( menu_vehicles, ID_MENU_VEHICLES_SUB, menu_callback_vehicles_sub );

		snprintf( name, sizeof(name), "%s", gta_vehicle_class_name(i) );
		menu_item_add( menu_vehicles, menu, name, ID_NONE, MENU_COLOR_DEFAULT, (void *)(UINT_PTR) i );
	}

	menu_item_add( menu_vehicles, NULL, "Freeze nearby vehicles", ID_VEHICLES_FREEZE, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_vehicles, NULL, "Araçlarý kendine teleport et", ID_VEHICLES_IWARP, MENU_COLOR_DEFAULT, NULL );


	/* main menu -> patches */
	for ( i = 0; i < INI_PATCHES_MAX; i++ )
	{
		if ( set.patch[i].name == NULL )
			continue;

		menu_item_add( menu_patches, NULL, set.patch[i].name, i, MENU_COLOR_DEFAULT, NULL );
	}

	if ( g_dwSAMP_Addr != NULL )
	{
		/* main menu -> players */
		menu_item_add( menu_players, menu_players_warp, "Warp to Player", ID_MENU_PLAYERS_WARP, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_players, menu_players_vehwarp, "Warp instantly to player's vehicle", ID_MENU_PLAYERS_VEHWARP, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_players, menu_players_spec, "Spectate player", ID_MENU_PLAYERS_SPEC, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_players, menu_player_info, "Show infos on player", ID_MENU_PLAYERS_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_players, menu_players_mute, "Mute Players", ID_MENU_PLAYERS_MUTE, MENU_COLOR_DEFAULT, NULL);

		// net patches
		menu_item_add( menu_samppatches, menu_netpatches_inrpc, "Disable incoming RPC", ID_MENU_NETPATCHES_INRPC, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_samppatches, menu_netpatches_outrpc, "Disable outcoming RPC", ID_MENU_NETPATCHES_OUTRPC, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_samppatches, menu_netpatches_inpacket, "Disable incoming packet", ID_MENU_NETPATCHES_INPACKET, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_samppatches, menu_netpatches_outpacket, "Disable outcoming packet", ID_MENU_NETPATCHES_OUTPACKET, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_netpatches_inrpc, NULL, "Toggle all", ID_MENU_NETPATCHES_TOGGLE_ALL, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_netpatches_outrpc, NULL, "Toggle all", ID_MENU_NETPATCHES_TOGGLE_ALL, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_netpatches_inpacket, NULL, "Toggle all", ID_MENU_NETPATCHES_TOGGLE_ALL, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_netpatches_outpacket, NULL, "Toggle all", ID_MENU_NETPATCHES_TOGGLE_ALL, MENU_COLOR_DEFAULT, NULL );

		int netPatchNumber[4] = { 1, 1, 1, 1 };
		for (i = 0; i < iNetPatchesCount; ++i)
		{
			menu *pmenu = nullptr;
			stNetPatch &patch = set.netPatch[i];
			sprintf_s(name, "%d. %s", netPatchNumber[patch.type]++, patch.name);
			switch (patch.type)
			{
			case INCOMING_RPC: pmenu = menu_netpatches_inrpc; break;
			case OUTCOMING_RPC: pmenu = menu_netpatches_outrpc; break;
			case INCOMING_PACKET: pmenu = menu_netpatches_inpacket; break;
			case OUTCOMING_PACKET: pmenu = menu_netpatches_outpacket; break;
			}
			if (pmenu != nullptr)
				menu_item_add(pmenu, NULL, name, i, MENU_COLOR_DEFAULT, NULL);
		}

		// samp patches
		for ( i = 0; i < INI_SAMPPATCHES_MAX; i++ )
		{
			if ( set.sampPatch[i].name == NULL )
				continue;

			menu_item_add( menu_samppatches, NULL, set.sampPatch[i].name, i, MENU_COLOR_DEFAULT, NULL );
		}

		// server list
		menu_item_add( menu_servers, NULL, "Keep your current nickname", INI_SERVERS_MAX + 1, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_servers, NULL, "\tServers", ID_NONE, MENU_COLOR_SEPARATOR, NULL );
		for ( i = 0; i < INI_SERVERS_MAX; i++ )
		{
			if ( set.server[i].server_name == NULL )
				continue;

			menu_item_add( menu_servers, NULL, set.server[i].server_name, i, MENU_COLOR_DEFAULT, NULL );
		}
	}

	/* teleports */
	menu_item_add( menu_teleports, menu_interiors, "Teleport to interiors", STATIC_TELEPORT_MAX + 1, MENU_COLOR_DEFAULT,
				   NULL );
	for ( i = 0; i < 146; i++ )
	{
		menu_item_add( menu_interiors, NULL, interiors_list[i].interior_name, i, MENU_COLOR_DEFAULT, NULL );
	}

	for ( i = 0; i < STATIC_TELEPORT_MAX; i++ )
	{
		if ( strlen(set.static_teleport_name[i]) == 0 )
			continue;

		if ( vect3_near_zero(set.static_teleport[i].pos) )
			continue;

		menu_item_add( menu_teleports, NULL, set.static_teleport_name[i], i, MENU_COLOR_DEFAULT, NULL );
	}

	/* misc */
	menu_item_add( menu_misc, menu_debug, "Debug", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, NULL, "Write coordinates to log file", ID_MISC_COORDS, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_misc, NULL, "Reload settings", ID_MISC_RELOAD, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, NULL, "Enable HUD text", ID_MISC_HUDTEXT, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, NULL, "Disable bad weapons", ID_MISC_BAD_WEAPONS, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, NULL, "Trailer support", ID_MISC_TRAILERS, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, menu_hudindicators, "Toggle HUD indicators", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "FPS limit: %d", set.fps_limit );
	menu_item_add( menu_misc, NULL, name, ID_MISC_FPSLIMIT, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, NULL, "Toggle windowed mode", ID_MISC_TOGGLEWINDOWED, MENU_COLOR_DEFAULT, NULL );
#ifdef __CHEAT_VEHRECORDING_H__
	menu_item_add( menu_misc, menu_routes, "Routes", ID_NONE, MENU_COLOR_DEFAULT, NULL );
#endif

	/* misc -> debug */
	menu_item_add( menu_debug, NULL, "Enable", ID_DEBUG_ENABLE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_debug, NULL, "Self actor", ID_DEBUG_SELF_ACTOR, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_debug, NULL, "Self vehicle", ID_DEBUG_SELF_VEHICLE, MENU_COLOR_DEFAULT, NULL );

	if ( g_dwSAMP_Addr != NULL )
	{
		menu_item_add( menu_debug, NULL, "SA:MP DLL", ID_DEBUG_SAMP_DLL, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Info", ID_DEBUG_SAMP_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Player List", ID_DEBUG_SAMP_PLAYER_LIST, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Local info", ID_DEBUG_SAMP_LOCAL_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Vehicle List", ID_DEBUG_SAMP_VEHICLE_LIST, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Chat info", ID_DEBUG_SAMP_CHAT_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Input info", ID_DEBUG_SAMP_CHAT_IPT_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Kill info", ID_DEBUG_SAMP_KILL_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Local SAMP-PED", ID_DEBUG_SAMP_LOCAL_SAMPPED, MENU_COLOR_DEFAULT, NULL );
	}

#ifdef __CHEAT_VEHRECORDING_H__
	/* misc -> routes */
	menu_item_add( menu_routes, NULL, "Enable Routes function", ID_ROUTES_ACTIVATED, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_routes, menu_routes_load, "Load Route", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_routes, menu_routes_drop, "Delete Route", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_routes, NULL, "Save current Route", ID_ROUTES_WRITE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_routes, NULL, "Optimize Database (Rebuild)", ID_ROUTES_OPTIMIZE, MENU_COLOR_DEFAULT, NULL );
#endif

	// misc -> HUD indicators
	//menu_item_add( menu_hudindicators, NULL, "Draw bottom bar", ID_HUDIND_BAR, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "Render text shadows", ID_HUDIND_TSHADOWS, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "Inv", ID_HUDIND_INV, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "Weapon", ID_HUDIND_WEAPON, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "Money", ID_HUDIND_MONEY, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "Freeze", ID_HUDIND_FREEZE, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "In vehicle AirBrk", ID_HUDIND_INVEH_AIRBRK, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "In vehicle Stick", ID_HUDIND_INVEH_STICK, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "In vehicle BrkDance", ID_HUDIND_INVEH_BRKDANCE, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "In vehicle SpiderWheels", ID_HUDIND_INVEH_SPIDER, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "In vehicle Fly", ID_HUDIND_INVEH_FLY, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "On foot AirBrk", ID_HUDIND_ONFOOT_AIRBRK, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "On foot Stick", ID_HUDIND_ONFOOT_STICK, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "On foot Fly", ID_HUDIND_ONFOOT_FLY, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "Aim", ID_HUDIND_ONFOOT_AIM, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "Surf", ID_HUDIND_SURF, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "FreezeRot", ID_HUDIND_FREEZEROT, MENU_COLOR_DEFAULT, NULL );
	////menu_item_add( menu_hudindicators, NULL, "Ghost Mode", ID_HUDIND_GHOSTMODE, MENU_COLOR_DEFAULT, NULL);
	//menu_item_add( menu_hudindicators, NULL, "Position", ID_HUDIND_POS, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "FPS", ID_HUDIND_FPS, MENU_COLOR_DEFAULT, NULL );
	//menu_item_add( menu_hudindicators, NULL, "Toggle left bottom bars", ID_HUDIND_LB_BARS, MENU_COLOR_DEFAULT, NULL );

	if ( g_dwSAMP_Addr != NULL )
	{
		// main menu -> sampmisc
		//menu_item_add( menu_sampmisc, menu_vehicles_instant, "Warp instantly to vehicle", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, menu_fake_kill, "Fake kill", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, menu_spoof_weapon, "Spoof weapon", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, NULL, "Player info list", ID_MENU_SAMPMISC_SAMP_INFO_LIST, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, NULL, "Replace chat text rendering", ID_MENU_SAMPMISC_CHAT_TEXT, MENU_COLOR_DEFAULT, NULL );
		//snprintf( name, sizeof(name), "Display chat lines: %d", set.d3dtext_chat_lines );
		//menu_item_add( menu_sampmisc, NULL, name, ID_MENU_SAMPMISC_CHAT_TEXTLINES, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, menu_gamestate, "Change Game state", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, menu_specialaction, "Special action", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, NULL, "Drunk", ID_MENU_SAMPMISC_SAMP_DRUNK, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, menu_teleobject, "Teleport to object", ID_MENU_SAMPMISC_TELEOBJECT, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, NULL, "Render object texts", ID_MENU_SAMPMISC_RENDEROBJTXT, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, menu_telepickup, "Teleport to pickup", ID_MENU_SAMPMISC_TELEPICKUP, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, NULL, "Render pickup texts", ID_MENU_SAMPMISC_RENDERPCKTXT, MENU_COLOR_DEFAULT, NULL );
		//menu_item_add( menu_sampmisc, NULL, "Hile komutlarýný yükle", ID_MENU_SAMPMISC_M0DCOMMANDS, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, NULL, "Extra GodMode", ID_MENU_SAMPMISC_EXTRAGM, MENU_COLOR_DEFAULT, NULL );

		/* main menu -> sampmisc -> change game state */
		/*menu_item_add(menu_gamestate, NULL, "Baðlantý Ayarlarý", ID_NONE, MENU_COLOR_SEPARATOR, NULL, "Bu kategori kullanýþlý deðil.");
		menu_item_add( menu_gamestate, NULL, "Baðlanýlýyor...", GAMESTATE_CONNECTING, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_gamestate, NULL, "Baðlandý", GAMESTATE_CONNECTED, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_gamestate, NULL, "Baðlantý Bekleniyor...", GAMESTATE_AWAIT_JOIN, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_gamestate, NULL, "Restartlanýyor...", GAMESTATE_RESTARTING, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_gamestate, NULL, "Baðlanmayý Bekle.", GAMESTATE_WAIT_CONNECT, MENU_COLOR_DEFAULT, NULL );*/

		/* main menu -> sampmisc -> special action */
	/*	menu_item_add( menu_specialaction, NULL, "None", ID_MENU_SPECIAL_ACTION_NONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Smoke Blunt", ID_MENU_SPECIAL_ACTION_SMOKE_CIGGY, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Drink Beer", ID_MENU_SPECIAL_ACTION_DRINK_BEER, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Drink Wine", ID_MENU_SPECIAL_ACTION_DRINK_WINE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Drink Sprunk", ID_MENU_SPECIAL_ACTION_DRINK_SPRUNK, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Use Jetpack", ID_MENU_SPECIAL_ACTION_USEJETPACK, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Dance1", ID_MENU_SPECIAL_ACTION_DANCE1, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Dance2", ID_MENU_SPECIAL_ACTION_DANCE2, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Dance3", ID_MENU_SPECIAL_ACTION_DANCE3, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Dance4", ID_MENU_SPECIAL_ACTION_DANCE4, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Hands Up", ID_MENU_SPECIAL_ACTION_HANDSUP, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Use Cellphone", ID_MENU_SPECIAL_ACTION_USECELLPHONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Stop Use Cellphone", ID_MENU_SPECIAL_ACTION_STOPUSECELLPHONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Cuffed", ID_MENU_SPECIAL_ACTION_CUFFED, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Carry", ID_MENU_SPECIAL_ACTION_CARRY, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Urinate", ID_MENU_SPECIAL_ACTION_URINATE, MENU_COLOR_DEFAULT, NULL );*/

		/* main menu -> sampmisc -> fake weapon */
		for ( i = 0; weapon_list[i].name != NULL; i++ )
		{
			const struct weapon_entry	*weapon = &weapon_list[i];

			if ( strcmp(weapon->name, "Camera") == 0
			 ||	 strcmp(weapon->name, "NV Goggles") == 0
			 ||	 strcmp(weapon->name, "IR Goggles") == 0
			 ||	 strcmp(weapon->name, "Parachute") == 0
			 ||	 strcmp(weapon->name, "Detonator") == 0 ) continue;

			snprintf( name, sizeof(name), "Fake killed by %s", weapon->name );
			menu_item_add( menu_spoof_weapon, NULL, name, ID_MENU_SAMPMISC_SPOOF_WEAPON, MENU_COLOR_DEFAULT,
						   (void *)(UINT_PTR) weapon->id );
		}

		menu_item_add( menu_spoof_weapon, NULL, "Fake death by fall", ID_MENU_SAMPMISC_SPOOF_WEAPON, MENU_COLOR_DEFAULT,
					   (void *)(UINT_PTR) 20 );
		menu_item_add( menu_spoof_weapon, NULL, "Fake begin run over", ID_MENU_SAMPMISC_SPOOF_WEAPON, MENU_COLOR_DEFAULT,
					   (void *)(UINT_PTR) 21 );
	}

	menu_active = menu_main;
}

static void menu_free ( struct menu *menu )
{
	int i;

	for ( i = 0; i < menu->count; i++ )
	{
		if ( menu->item[i].submenu != NULL )
		{
			menu_free( menu->item[i].submenu );
			if ( menu->item[i].name != NULL )
				free( (void *)menu->item[i].name );
		}
	}

	/*if(menu->parent != NULL)
   {
      struct menu *parent = menu->parent;
      for(i=0; i<parent->count; i++)
      {
         if(menu->item[i].submenu == menu)
            menu->item[i].submenu = NULL;
      }
   }*/
	free( menu->item );
	free( menu );
}

void menu_items_free ( struct menu *menu )
{
	int i;

	if ( menu == NULL )
		return;

	for ( i = 0; i < menu->count; i++ )
	{
		if ( menu->item[i].submenu != NULL )
		{
			menu_free( menu->item[i].submenu );
			if ( menu->item[i].name != NULL )
				free( (void *)menu->item[i].name );
		}
	}

	free( menu->item );
	menu->item = NULL;
	menu->count = 0;
	menu->pos = 0;
	menu->top_pos = 0;
}

void menu_free_all ( void )
{
	struct menu *menu;

	if ( menu_active == NULL )
		return;

	/* find root menu */
	for ( menu = menu_active; menu->parent != NULL; menu = menu->parent );

	menu_free( menu );
	menu_active = NULL;
	menu_init = 0;
}
