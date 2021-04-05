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

void sampMainCheat(void);
void sampAntiHijack(void);
void spectateHandle(void);
void spectatePlayer(int iPlayerID);
void HandleRPCPacketFunc(unsigned char id, struct RPCParameters *rpcParams, void(*callback) (struct RPCParameters *));
void initChatCmds(void);
bool OnSendRPC(int uniqueID, RakNet::BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp);
bool OnSendPacket(RakNet::BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel);
bool OnReceivePacket(Packet *p);
void CALLBACK StatusProc(const void *buffer, DWORD length, void *user);
extern int										g_iSpectateEnabled;
extern int										g_iCursorEnabled;
extern int										g_iJoiningServer;
extern int										g_iNumPlayersMuted;
extern bool										g_bPlayerMuted[SAMP_MAX_PLAYERS];