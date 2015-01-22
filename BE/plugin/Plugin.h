#ifndef _PLUGIN_H
#define _PLUGIN_H

extern "C"
{
	int plugin_start(int startPort, const char *pluginPath, int pathLen, const char *xmlPath, int xmlPathLen);
	void plugin_notify(const char *notify, int notifyLen);
	int plugin_stop();
}


#endif
