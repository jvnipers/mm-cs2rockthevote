#include <stdio.h>
#include "cs2rockthevote.h"

CS2RTVPlugin g_ThisPlugin;
PLUGIN_EXPOSE(CS2RTVPlugin, g_ThisPlugin);
bool CS2RTVPlugin::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();

	return true;
}

bool CS2RTVPlugin::Unload(char *error, size_t maxlen)
{
	return true;
}

void CS2RTVPlugin::AllPluginsLoaded()
{
}
