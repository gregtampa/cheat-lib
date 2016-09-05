#pragma once
#include "core/Cheat.hpp"

class FCheatBF4 : public FCheat {
public:
	b32 Create();
	b32 Ready();
	void Update();

private:
	//=========================================================================
	// Constants.
	//=========================================================================

	// Base offsets.
	static constexpr u64 const OFFSET_GAMECONTEXT	= 0x1424abd20;
	static constexpr u64 const OFFSET_DXRENDERER	= 0x142572FA0;
	static constexpr u64 const OFFSET_GAMERENDERER	= 0x1424AD330;
	static constexpr u64 const OFFSET_ANGLES		= 0x1421caee0;

	// Maximum number of players.
	static constexpr u32 const MAX_PLAYERS = 70;

	//=========================================================================
	// Types.
	//=========================================================================

	// A player.
	struct FPlayer {
		u64 ClientPlayer;
		u64 ClientSoldier;
		vec3 Pos;
		f32 Yaw;
		f32 Distance;
		f32 HPTotal;
		f32 HPValue;
		i32 Team;
		u32 Stance;
		b32 InVehicle;
		b32 IsDriver;
		b32 IsVisible;
		b32 IsSpectator;
		u32 Color;
	};

	//=========================================================================
	// Game render functions.
	//=========================================================================

	// Renders the radar.
	void RenderRadar();

	// Renders a player.
	void RenderPlayer(FPlayer const* p);

	// Calculates the screen position for a world vector.
	b32 WorldToScreen(vec3 world, vec2* screen);

	//=========================================================================
	// Game update functions.
	//=========================================================================

	// Modifies the recoil value for the current weapon by the given amount.
	void CheatRecoil(f32 value);

	// Reads player data for a client.
	b32 ReadPlayer(FPlayer* p, u64 cp);

	// Updates the list of players.
	void UpdatePlayers();

	// Updates the world view.
	void UpdateView();

	//=========================================================================
	// Static helpers.
	//=========================================================================

	// Returns true if the given address is potentially a valid pointer.
	static b32 IsPointer(u64 address);

	//=========================================================================
	// Key callbacks.
	//=========================================================================

	static void KeyQuit(void* p);
	static void KeyReload(void* p);
	static void KeyToggle(void* p);
	static void KeyRecoilUp(void* p);
	static void KeyRecoilDown(void* p);

	//=========================================================================
	// Cheat state.
	//=========================================================================

	// Render state.
	vec2 ScreenHalf; // Half the current "screen" size.
	b32 IsVisible; // True if the overlay is visible.

	// Game state.
	mat4 View; // Player view matrix.
	u32 NumPlayers; // Current number of players.
	u32 NumSpectators; // Current number of spectators.
	FPlayer Local; // The local player.
	FPlayer Players[MAX_PLAYERS]; // Non-local players.

	// Recoil state.
	f32 Recoil; // Current recoil value.
	i64 RecoilTime; // Time the recoil was last changed.
};
