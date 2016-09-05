#include "Cheat.hpp"

b32 FCheatBF4::Create() {
	static FWindow::FBind const binds[] = {
		{ VK_F10, MOD_ALT | MOD_CONTROL, this, KeyQuit },
		{ 'Q',   MOD_ALT | MOD_SHIFT, this, KeyQuit },
		{ 'R',   MOD_ALT | MOD_SHIFT, this, KeyReload },
		{ '1',   MOD_ALT, this, KeyToggle },
		{ '2',   MOD_ALT, this, KeyRecoilDown },
		{ '3',   MOD_ALT, this, KeyRecoilUp },
	};

	Window.RegisterKeys(binds, COUNT(binds));

	return true;
}

b32 FCheatBF4::Ready() {
	return true;
}

void FCheatBF4::Update() {
	// Update game state.
	Process.Open(false);
	UpdateView();
	UpdatePlayers();
	Process.Close();

	// Update render state.
	ScreenHalf = Render.GetViewport() * 0.5f;

	// Draw the radar box.
	RenderRadar();

	// Draw player state.
	for (u32 i = 0; i < NumPlayers; ++i) {
		RenderPlayer(Players + i);
	}

	// Draw recoil information.
	if (Timer.TotalUS - RecoilTime < 3000000) {
		Render.DrawText({ 7.0f, 9.0f }, Render.RGBA(255, 0, 255, 255), "%.3f", Recoil);
	}
}

void FCheatBF4::RenderRadar() {
	// Box dimensions are tuned for 1080p, so scale them to the current res.
	f32 yScale = ScreenHalf.y / 540.0f;

	// Draw radar box.
	#define DOT_S 5.0f
	#define DOT_S2 2.5f
	#define DOT_2S 10.0f

	#define RADAR_X 20.0f
	#define RADAR_Y 440.0f
	#define RADAR_S 200.0f
	#define RADAR_S2 100.0f
	
	// vec2 boxTL = 
	// vec2 boxTL = {  };
	vec2 boxSize = { 240.0f * yScale, 240.0f * yScale };
	vec2 boxTL = { 20.0f, 440.0f * yScale };
	vec2 boxBR = boxTL + boxSize;
	vec2 boxCenter = boxTL + boxSize * 0.5f;

	Render.DrawRectFill(boxTL, boxBR, Render.RGBA(0, 0, 0, 130));

	// Calculate yaw for player radar placements.
	f32 yaw = -Local.Yaw;
	f32 lcy = cosf(yaw);
	f32 lsy = sinf(yaw);

	// Draw dots.
	for (u32 i = 0; i < NumPlayers; ++i) {
		FPlayer* p = Players + i;

		// Ignore friendlies.
		if (p->Team == Local.Team) {
			continue;
		}

		// Calculate position on the radar.
		f32 dvx = Local.Pos.x - p->Pos.x;
		f32 dvz = Local.Pos.z - p->Pos.z;

		vec2 pos = vec2{ 
			(dvx * lcy - dvz * lsy) * 2.0f,
			(dvx * lsy + dvz * lcy) * 2.0f
		};

		pos += boxCenter;

		// Draw if the dot is fully enclosed in the radar box.
		vec2 dotSize = vec2{ 4.0f, 4.0f } * yScale;
		vec2 dotTL = pos - dotSize;
		vec2 dotBR = pos + dotSize;

		if (dotTL.x > boxTL.x && dotTL.y > boxTL.y && dotBR.x < boxBR.x && dotBR.y < boxBR.y) {
			Render.DrawRect(pos - 4.0f, pos + 4.0f, p->Color);
		}
	}

}

void FCheatBF4::RenderPlayer(FPlayer const * p) {
	// Ignore friendly players.
	if (p->Team == Local.Team) {
		return;
	}

	// Cache player state.
	vec3 pos = p->Pos;

	// Calculate player head position based on stance (stand, crouch, prone).
	f32 const offsets[] = { 1.8f, 1.1f, 0.7f };
	vec3 head = pos;
	head.y += (p->Stance < 3) ? offsets[p->Stance] : offsets[0];

	// Calculate standing box position.
	vec3 playerTop = pos;
	playerTop.y += offsets[0];

	// Get screen coordinates for the base of the player and their head.
	vec2 boxTop, boxPos, boxHead;
	if (WorldToScreen(pos, &boxPos) == false || WorldToScreen(head, &boxHead) == false || WorldToScreen(playerTop, &boxTop) == false) {
		return;
	}

	// Ignore players that are under the map in the deploy screen).
	if (p->Distance > 2000000.0f) {
		return;
	}

	// Draw the bounding box around the player.
	f32 h = boxPos.y - boxHead.y;
	f32 w = (boxPos.y - boxTop.y) * 0.5f;
	f32 x = boxHead.x - w * 0.5f;

	// Ignore players that are too small to really see.
	if (w < 1.0f) {
		return;
	}

	Render.DrawRect({ x, boxHead.y }, { x + w, boxHead.y + h }, p->Color);

	// Draw the distance to the player.
	Render.DrawText({ x, boxHead.y + h + 1.0f }, p->Color, "%0.0fm", p->Distance);

	// Draw player health.
	if (p->HPValue > 0.0f) {
		f32 safeTotal = p->HPValue > p->HPTotal ? p->HPValue : p->HPTotal;
		f32 barWidth = ceilf(p->HPValue / safeTotal * w);
		f32 barY = boxHead.y - 8.0f;

		Render.DrawRect({ x, barY }, { x + w, barY + 5 }, p->Color);
		Render.DrawRectFill({ x + 1, barY + 1 }, { x + barWidth - 2.0f, barY + 3.0f }, Render.RGBA(0, 255, 0, 255));
	}
}

b32 FCheatBF4::WorldToScreen(vec3 world, vec2 * screen) {
	f32 w = View._14 * world.x + View._24 * world.y + View._34 * world.z + View._44;

	// Ignore world positions that don't fall within the screen.
	if (w < 0.000001f && w > -0.000001f) {
		return false;
	}

	f32 x = View._11 * world.x + View._21 * world.y + View._31 * world.z + View._41;
	f32 y = View._12 * world.x + View._22 * world.y + View._32 * world.z + View._42;

	screen->x = ScreenHalf.x + ScreenHalf.x * x / w;
	screen->y = ScreenHalf.y - ScreenHalf.y * y / w;

	return true;
}

void FCheatBF4::CheatRecoil(f32 value) {
	// We want the current recoil to be displayed for a few seconds after "changing".
	RecoilTime = Timer.TotalUS;

	if (IsPointer(Local.ClientPlayer) == false) {
		return;
	}

	if (Local.InVehicle) {
		return;
	}

	Process.Open(true);

	u64 wc = Process.Read<u64>(Local.ClientSoldier + 0x570); // ClientSoldierWeaponsComponent
	if (IsPointer(wc)) {
		i32 slot = Process.Read<i32>(wc + 0xA98); // WeaponSlot

		if (slot < 5) {
			u64 a0 = Process.Read<u64>(OFFSET_ANGLES); // ClientSoldierWeapon
			u64 a1 = Process.Read<u64>(a0 + 0x49c0); // WeaponFiring
			u64 a2 = Process.Read<u64>(a1 + 0x78); // WeaponSway
			u64 a3 = Process.Read<u64>(a2 + 0x8); // GunSwayData
			if (IsPointer(a3)) {
				f32 v;

				// VisualSpreadADS
				v = Process.Read<f32>(a3 + 0x430);
				Process.Write(a3 + 0x430, v * value);
				Recoil = v * value;

				// ProjectileSpreadADS
				v = Process.Read<f32>(a3 + 0x434);
				Process.Write(a3 + 0x434, v * value);

				// VisualSpread
				v = Process.Read<f32>(a3 + 0x438);
				Process.Write(a3 + 0x438, v * value);

				// ProjectileSpread
				v = Process.Read<f32>(a3 + 0x43C);
				Process.Write(a3 + 0x43C, v * value);
			}
		}
	}

	Process.Close();
}

b32 FCheatBF4::ReadPlayer(FPlayer* p, u64 cp) {
	*p = {};
	p->ClientPlayer = cp;

	u64 attached = Process.Read<u64>(cp + 0x14C0); // m_pAttachedControllable (ClientVehicleEntity)

	if (IsPointer(attached)) {
		u64 cc = Process.Read<u64>(cp + 0x14B0); // m_character (ClientSoldierEntity)
		p->ClientSoldier = Process.Read<u64>(cc) - 8;
		p->InVehicle = true;
	} else {
		p->ClientSoldier = Process.Read<u64>(cp + 0x14D0); // m_pControlledControllable (ClientSoldierEntity)
	}

	u64 cs = p->ClientSoldier;
	if (IsPointer(cs) == false) {
		return false;
	}

	p->Team = Process.Read<b32>(cp + 0x13CC);

	u64 hp = Process.Read<u64>(cs + 0x140);

	if (p->InVehicle) {
		p->HPValue = Process.Read<f32>(hp + 0x38); // m_vehicleHealth
		u64 data = Process.Read<u64>(cs + 0x30); // m_data (VehicleEntityData)
		if (IsPointer(data)) {
			p->HPTotal = Process.Read<f32>(data + 0x148); // m_FrontMaxHealth
		}

		p->IsDriver = (Process.Read<u64>(cp + 0x14C8) == 0); // m_attachedEntryId

		if (p->IsDriver) {
			u64 entity = Process.Read<u64>(attached + 0x238); // m_pPhysicsEntity (DynamicPhysicsEntity)
			u64 trans = Process.Read<u64>(entity + 0xA0); // m_EntityTransform (PhysicsEntityTransform)
			mat4 m = Process.Read<mat4>(trans); // m_Transform

			p->Pos.x = m._41;
			p->Pos.y = m._42;
			p->Pos.z = m._43;
		} else {
			u64 predicted = Process.Read<u64>(cs + 0x490); // m_pPredictedController (ClientSoldierPrediction)
			p->Pos = Process.Read<vec3>(predicted + 0x30); // m_Position
		}
	} else {
		p->HPValue = Process.Read<f32>(hp + 0x20); // m_Health
		p->HPTotal = Process.Read<f32>(hp + 0x24); // m_MaxHealth

		u64 predicted = Process.Read<u64>(cs + 0x490); // m_pPredictedController (ClientSoldierPrediction)
		p->Pos = Process.Read<vec3>(predicted + 0x30); // m_Position
	}

	p->Yaw = Process.Read<f32>(cs + 0x4D8); // m_authorativeYaw
	p->IsVisible = !Process.Read<u8>(cs + 0x5B1); // m_occluded
	p->Stance = Process.Read<i32>(cs + 0x4F0); // m_poseType
	p->IsSpectator = Process.Read<u8>(cp + 0x13C9); // m_isSpectator

	// Update the distance to the player.
	p->Distance = Vec3::Length(Local.Pos - p->Pos);

	// Determine the color for drawing based on player occlusion, and team.
	if (p->InVehicle == false) {
		p->Color = (p->IsVisible) ? Render.RGBA(255, 0, 0, 255) : Render.RGBA(255, 175, 0, 255);
	} else {
		p->Color = Render.RGBA(255, 0, 255, 255);
	}

	return true;
}

void FCheatBF4::UpdatePlayers() {
	NumPlayers = 0;

	u64 ctx = Process.Read<u64>(OFFSET_GAMECONTEXT); // GameContext
	u64 playerManager = Process.Read<u64>(ctx + 0x60); // m_pPlayerManager (ClientPlayerManager)
	u64 localPlayer = Process.Read<u64>(playerManager + 0x540); // m_pLocalPlayer (ClientPlayer)
	u64 playerList = Process.Read<u64>(playerManager + 0x548); // m_ppPlayer (ClientPlayer)

	ReadPlayer(&Local, localPlayer);

	for (u32 i = 0; i < MAX_PLAYERS; ++i) {
		u64 client = Process.Read<u64>(playerList + i * 8);
		if (client == localPlayer || client == 0) {
			continue;
		}

		if (ReadPlayer(&Players[NumPlayers], client)) {
			++NumPlayers;
		}
	}
}

void FCheatBF4::UpdateView() {
	u64 gameRender = Process.Read<u64>(OFFSET_GAMERENDERER); // GameRenderer
	u64 gameContext = Process.Read<u64>(gameRender + 0x60); // m_pRenderView (RenderView)
	View = Process.Read<mat4>(gameContext + 0x420); // m_ViewProj
}

b32 FCheatBF4::IsPointer(u64 address) {
	return (address > 0xFFFFFFF) && (address < 0x000F000000000000);
}

void FCheatBF4::KeyQuit(void * p) {
	auto cheat = (FCheatBF4*)p;
	cheat->Window.Quit();
}

void FCheatBF4::KeyReload(void * p) {
	auto cheat = (FCheatBF4*)p;
	cheat->Window.Retrack();
}

void FCheatBF4::KeyToggle(void * p) {
	auto cheat = (FCheatBF4*)p;
	cheat->IsVisible = !cheat->IsVisible;
}

void FCheatBF4::KeyRecoilUp(void * p) {
	auto cheat = (FCheatBF4*)p;
	cheat->CheatRecoil(1.25f);
}

void FCheatBF4::KeyRecoilDown(void * p) {
	auto cheat = (FCheatBF4*)p;
	cheat->CheatRecoil(0.80f);
}
