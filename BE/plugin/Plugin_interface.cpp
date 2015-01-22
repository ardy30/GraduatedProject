#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>
#include "Plugin.h"
#include "Plugin_interface.h"
#include "Xml_Wrapper.h"

#define PLUGIN_MAIN_NAME "WS"
#define CLOSE_TIME_SPAN 2

extern int g_startPort;
extern std::string g_dllConfig;
extern std::string g_dllPath;
extern std::string g_dllNotify;

void
Plugin_interface::start()
{
   
    pid_t pid = fork();
    /* child process */
    if (!pid)
    {
       
        char portStr[16];
        std::sprintf(portStr, "%d", g_startPort);
        std::string binPath = g_dllPath + "/" +PLUGIN_MAIN_NAME;
        if (execl(binPath.c_str(), PLUGIN_MAIN_NAME, g_dllConfig.c_str(), portStr, g_dllPath.c_str(), (char *)NULL) == -1)
        {
            exit(-1);
        }
    }
    /* parent process */
}

void
Plugin_interface::stop()
{

}

void
Plugin_interface::notify()
{
/*
    Xml_Wrapper notify_xml;
    Xml_Wrapper old_xml;
    if (notify_xml.load_from_buffer(g_dllNotify.c_str(), g_dllNotify.size()) == NULL)
    {
        throw std::runtime_error("load notify string error");
    }
    if (old_xml.load_from_buffer(g_dllConfig.c_str(), g_dllConfig.size()) == NULL)
    {
        throw std::runtime_error("load g_dllConfig string error");
    }
    std::vector<xmlNode *> v_children;
    std::vector<xmlNode *>::iterator iter;
    if (notify_xml.get_specific_children_nodes(notify_xml.get_specific_child_node(notify_xml.get_root_node(), "CHANGEITEM"), "PARE", v_children) < 0)
    {
        throw std::runtime_error("load pare error");
    }

    for (iter = v_children.begin(); iter != v_children.end(); ++iter)
    {
        std::string path;
        std::string value;
        if (notify_xml.get_node_value((notify_xml.get_specific_child_node(*iter, "PATH")), path) < 0)
        {
            throw std::runtime_error("get PATH error");
        }
        if (notify_xml.get_node_value((notify_xml.get_specific_child_node(*iter, "VALUE")), value) < 0)
        {
            throw std::runtime_error("get VALUE error");
        }
        old_xml.set_node_value(old_xml.get_first_node_by_xpath(path.c_str()), value.c_str());
    }
    if (old_xml.save_in_buffer(old_xml.get_root_node(), g_dllConfig) < 0)
    {
        throw std::runtime_error("save in old xml error");
    }
#if 0
    if (old_xml.save_in_buffer(old_xml.get_first_node_by_xpath("/CONFIG"), g_dllConfig) < 0)
    {
        throw std::runtime_error("old_xml save in g_dllConfig error");
    }
#endif
    std::cout << g_dllConfig << std::endl;
    this->stop();
    std::cout << "***********************************************ESP Receive Notify***********************************************" << std::endl;
    sleep(2);
    this->start();

*/
}







