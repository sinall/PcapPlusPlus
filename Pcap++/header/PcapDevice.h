#ifndef PCAPPP_DEVICE
#define PCAPPP_DEVICE

#include <RawPacket.h>
#include <PcapFilter.h>
#include <PointerVector.h>
#include <pcap.h>

/// @file

/** A vector of pointers to RawPacket */
typedef PointerVector<RawPacket> RawPacketVector;

/**
 * An abstract class representing all possible packet capturing devices: files, libPcap, WinPcap, RemoteCapture, PF_RING, etc.
 * This class cannot obviously be instantiated
 */
class IPcapDevice
{
protected:
	pcap_t* m_PcapDescriptor;
	bool m_DeviceOpened;

	// c'tor should not be public
	IPcapDevice() { m_DeviceOpened = false; m_PcapDescriptor = NULL; }

public:
	virtual ~IPcapDevice();

	/**
	 * Open the device
	 * @return True if device was opened successfully, false otherwise
	 */
	virtual bool open() = 0;

	/**
	 * Close the device
	 */
	virtual void close() = 0;

	/**
	 * Get statistics from device:
	 * - pcap_stat#ps_recv: number of packets received
	 * - pcap_stat#ps_drop: number of packets dropped
	 * - pcap_stat#ps_ifdorp: number of packets dropped by interface
	 * @param[out] stats The stats struct where stats are returned
	 */
	virtual void getStatistics(pcap_stat& stats) = 0;

	/**
	 * Set a filter for the device. When implemented by the device, only packets that match the filter will be received
	 * @param[in] filter The filter to be set in PcapPlusPlus' GeneralFilter format
	 * @return True if filter set successfully, false otherwise
	 */
	bool setFilter(GeneralFilter& filter);

	/**
	 * Set a filter for the device. When implemented by the device, only packets that match the filter will be received
	 * @param[in] filterAsString The filter to be set in Berkeley %Packet Filter (BPF) syntax (http://biot.com/capstats/bpf.html)
	 * @return True if filter set successfully, false otherwise
	 */
	bool setFilter(string filterAsString);
};

#endif
