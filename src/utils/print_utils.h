#ifndef _INCLUDE_RTV_PRINT_UTILS_H_
#define _INCLUDE_RTV_PRINT_UTILS_H_

// Send a formatted chat message to a single player.
void RTV_PrintToChat(int slot, const char *fmt, ...);

// Broadcast a formatted chat message to all connected human players.
void RTV_ChatToAll(const char *fmt, ...);

// Send a console message to a single player's console.
void RTV_PrintToClient(int slot, const char *fmt, ...);

// Print to server console.
void RTV_ConPrint(const char *fmt, ...);

#endif // _INCLUDE_RTV_PRINT_UTILS_H_
