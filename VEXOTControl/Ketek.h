#pragma once
#ifndef KETEK_H
#define KETEK_H

#include "handel.h"
#include "handel_errors.h"
#include "md_generic.h"

#include <string>
#include <memory>
#include <chrono>
#include <thread>

class Ketek
{
public:
	Ketek(const std::string deviceSN) { InitializeDevice(deviceSN); };
	auto InitializeDevice(const std::string deviceSN) -> bool;
	auto IsDeviceInitialized() const -> bool { return !m_DeviceSerialNumber.empty(); };
	auto CaptureData(const int exposure, unsigned long* const mca, bool* const continueCapturing) -> bool;
	auto GetDataSize() const -> unsigned long { return m_MCALength; };
	auto DeinitializeDevice() -> bool;
	~Ketek() { DeinitializeDevice(); };

private:
	static bool CHECK_ERROR(int status) { return status == XIA_SUCCESS ? true : false;  }
private:
	std::string m_InitializationFilePath{".\\KETEK.ini"};
	std::string m_DeviceSerialNumber{};

	double m_nMCA = 8192.0; // BinSize
	const unsigned long m_MCALength = 8192;
	double m_Thresh = 48.0;
	double m_Polarity = 1.0;
	double m_Gain = 5.884;
	unsigned short m_Ignored = 0;

	double m_CurrentGENSET;
	double m_CurrentPARSET;

	unsigned short m_GENSET;
	unsigned short m_PARSET;

	unsigned short m_NumberPeakingTimes = 0;
	std::unique_ptr<double[]> m_PeakingTimes{};

	unsigned short m_NumberFippis = 0;
};

#endif // !KETEK_H
