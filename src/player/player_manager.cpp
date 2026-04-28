#include "player_manager.h"
#include "src/config/config.h"

RTVPlayerManager g_RTVPlayerManager;

void RTVPlayerManager::OnClientConnected(int slot, const char *name, uint64_t xuid, const char *address, bool fakePlayer)
{
	if (slot < 0 || slot > MAXPLAYERS)
	{
		return;
	}

	PlayerInfo &p = m_players[slot];
	p.Reset();
	p.connected = true;
	p.steamid64 = xuid;
	p.name = name ? name : "";
	p.fakePlayer = fakePlayer;
}

void RTVPlayerManager::OnClientDisconnect(int slot)
{
	if (slot < 0 || slot > MAXPLAYERS)
	{
		return;
	}

	m_players[slot].Reset();
}

PlayerInfo *RTVPlayerManager::GetPlayer(int slot)
{
	if (slot < 0 || slot > MAXPLAYERS)
	{
		return nullptr;
	}
	return &m_players[slot];
}

int RTVPlayerManager::GetHumanPlayerCount() const
{
	int count = 0;
	for (int i = 0; i <= MAXPLAYERS; i++)
	{
		const PlayerInfo &p = m_players[i];
		if (p.connected && !p.fakePlayer)
		{
			count++;
		}
	}
	return count;
}

int RTVPlayerManager::GetEligiblePlayerCount() const
{
	int count = 0;
	for (int i = 0; i <= MAXPLAYERS; i++)
	{
		const PlayerInfo &p = m_players[i];
		if (!p.connected || p.fakePlayer)
		{
			continue;
		}
		if (!g_RTVConfig.general.includeSpectator && p.teamNum == 1)
		{
			continue;
		}
		count++;
	}
	return count;
}
