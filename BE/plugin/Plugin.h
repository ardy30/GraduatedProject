#ifndef _PLUGIN_H
#define _PLUGIN_H

extern "C"
{
	vector <pair<string,string> > plugin_start(int startPort, const char *pluginPath, int pathLen, const char *xmlPath, int xmlPathLen);
}


#endif
