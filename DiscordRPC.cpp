#include "DiscordRPC.h"
#include <chrono>

static int64_t timeuptd = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

void DiscordRPC::initialize()
{
    DiscordEventHandlers hndl;
    memset(&hndl, NULL, sizeof(hndl));
    Discord_Initialize("1050564320158810203", &hndl, 1, NULL); // client ID for discord applications
    // discord developer portal
}

void DiscordRPC::discordPresence() // all this is from discord developer portal
{
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = "int strings args main lil bro";
    discordPresence.details = "Keyauth Protected Loader";
    discordPresence.startTimestamp = timeuptd;
    discordPresence.endTimestamp = NULL;
    discordPresence.largeImageText = "Coder level 69";
    discordPresence.smallImageText = "Coder level 69";
    discordPresence.partyId = "ae488379-351d-4a4f-ad32-2b9b01c91657";
    discordPresence.largeImageKey = "cat"; // upload from rich-presence assets
    discordPresence.smallImageKey = "cat";
    discordPresence.partySize = 1;
    discordPresence.partyMax = 1;
    discordPresence.joinSecret = "MTI4NzM0OjFpMmhuZToxMjMxMjM= "; 


    Discord_UpdatePresence(&discordPresence);
}