#include "Plugin.h"
#include "Plugin_interface.h"
#include "Tcp_socket.h"
#include "Xml_Wrapper.h"
#include <iostream>
#include <exception>
#include <string>
#include <vector>

int g_startPort;
std::string g_dllConfig;
std::string g_dllPath;
std::string g_dllNotify;

Plugin_interface g_plugin_interface;

int plugin_start(int startPort, const char *pluginPath, int pathLen, const char *xmlString, int stringLen)
{
    g_startPort = startPort;
    g_dllPath.assign(pluginPath, pathLen);
    g_dllConfig.assign(xmlString, stringLen);
    std::cout << g_dllConfig << std::endl;
    try 
    {
        g_plugin_interface.start();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;  
}

int plugin_stop()
{
    try
    {
        g_plugin_interface.stop();
    }
    catch (...)
    {
        std::cerr << "plugin stop error" << std::endl;
        return -1;
    }
    return 0;
}

void plugin_notify(const char *notifyString, int notifyLen)
{
    g_dllNotify.assign(notifyString, notifyLen);
    try
    {
        g_plugin_interface.notify();
    }
    catch (...)
    {
        std::cerr << "plugin notify error" << std::endl;
    }
}



