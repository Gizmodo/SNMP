//
// Created by user on 02.02.2021.
//

#ifndef SNMPMANAGER_MANAGER_H
#define SNMPMANAGER_MANAGER_H

#include <vector>
#include "Host.h"
#include <functional>

class Manager {
public:
    Manager();

    ~Manager();

    void set_func(std::function<bool(Host, snmp_pdu *)> f);

    void run();

    void stop();

    void add_host(Host *h);

    void handle_data(Host *h, snmp_pdu *p);

    void set_interval(uint32_t i);

    //bool add_host_info(std::vector<char*> hosts, std::vector<char*> oids);

private:
    void init_sessions();

    void asyn_send();

    void wait_request();

private:
    std::vector<Host *> m_hosts;
    std::function<bool(Host, snmp_pdu *)> m_handleFunc;
    bool m_running;
    uint32_t m_sendCount;
    uint32_t m_loopInterval;
};


#endif //SNMPMANAGER_MANAGER_H
