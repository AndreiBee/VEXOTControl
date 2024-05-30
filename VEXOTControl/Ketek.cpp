#include "Ketek.h"

auto Ketek::InitializeDevice(const std::string deviceSN) -> bool
{
    if (IsDeviceInitialized()) DeinitializeDevice();
    /* Setup logging here */
    // Configuring the Handel log file
    xiaSetLogLevel(MD_DEBUG);
    xiaSetLogOutput((char*)"handel.log");

    // Loading the .ini file
    auto status = xiaInit((char*)m_InitializationFilePath.c_str());
    if (!CHECK_ERROR(status)) return false;

    xiaSetIOPriority(MD_IO_PRI_HIGH);

    status = xiaStartSystem();
    if (!CHECK_ERROR(status)) return false;

    // Serial Number
    {
        char serialNumber[17];
        status = xiaBoardOperation(0, (char*)"get_serial_number", &serialNumber);
        serialNumber[16] = '\0';
        m_DeviceSerialNumber = std::string(serialNumber);

        if (m_DeviceSerialNumber != deviceSN) return false;
    }

    /* Modify some acquisition values */
    status = xiaSetAcquisitionValues(0, (char*)"number_mca_channels", &m_nMCA);
    if (!CHECK_ERROR(status)) return false;

    status = xiaSetAcquisitionValues(0, (char*)"mca_bin_width", (void*)&m_BinWidth);
    if (!CHECK_ERROR(status)) return false;

    status = xiaSetAcquisitionValues(0, (char*)"trigger_threshold", &m_Thresh);
    if (!CHECK_ERROR(status)) return false;

    status = xiaSetAcquisitionValues(0, (char*)"polarity", &m_Polarity);
    if (!CHECK_ERROR(status)) return false;

    status = xiaSetAcquisitionValues(0, (char*)"gain", &m_Gain);
    if (!CHECK_ERROR(status)) return false;

    /* Apply changes to parameters */
    status = xiaBoardOperation(0, (char*)"apply", (void*)&m_Ignored);

    /* Save the settings to the current GENSET and PARSET */
    status = xiaGetAcquisitionValues(0, (char*)"genset", &m_CurrentGENSET);
    if (!CHECK_ERROR(status)) return false;

    status = xiaGetAcquisitionValues(0, (char*)"parset", &m_CurrentPARSET);
    if (!CHECK_ERROR(status)) return false;

    m_GENSET = (unsigned short)m_CurrentGENSET;
    m_PARSET = (unsigned short)m_CurrentPARSET;

    status = xiaBoardOperation(0, (char*)"save_genset", &m_GENSET);
    if (!CHECK_ERROR(status)) return false;

    status = xiaBoardOperation(0, (char*)"save_parset", &m_PARSET);
    if (!CHECK_ERROR(status)) return false;

    /* Read out number of peaking times to pre-allocate peaking time array */
    status = xiaBoardOperation(0, (char*)"get_number_pt_per_fippi", &m_NumberPeakingTimes);
    if (!CHECK_ERROR(status)) return false;

    m_PeakingTimes = std::make_unique<double[]>(m_NumberPeakingTimes);

    status = xiaBoardOperation(0, (char*)"get_current_peaking_times", m_PeakingTimes.get());
    if (!CHECK_ERROR(status)) return false;

    /* Read out number of fippis to pre-allocate peaking time array */
    status = xiaBoardOperation(0, (char*)"get_number_of_fippis", &m_NumberFippis);
    if (!CHECK_ERROR(status)) return false;

    m_PeakingTimes = std::make_unique<double[]>(m_NumberPeakingTimes * m_NumberFippis);

    status = xiaBoardOperation(0, (char*)"get_peaking_times", m_PeakingTimes.get());
    if (!CHECK_ERROR(status)) return false;

    return true;
}

auto Ketek::CaptureData(const int exposure, unsigned long* const mca, bool * const continueCapturing) -> bool
{
    if (!IsDeviceInitialized()) return false;
    if (!mca) return false;

    /* Start a run w/ the MCA cleared */
    auto status = xiaStartRun(0, 0);
    if (!CHECK_ERROR(status)) return false;

    auto exposureTime = abs(exposure);
    // Started run. Sleeping for exposure
    {
        auto startCheckingTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();

        double deltaTime{};
        /* 1. Wait till the Hardware Trigger signal or till the end of Waiting Time */
        do
        {
            currentTime = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>
                (currentTime - startCheckingTime).count() / 1'000.0;
            if (!*continueCapturing)
            {
                xiaStopRun(0);
                return false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (deltaTime < (double)exposureTime);
    }

    status = xiaStopRun(0);
    if (!CHECK_ERROR(status)) return false;

    /* Prepare to read out MCA spectrum */
    unsigned long mcaLen{};
    status = xiaGetRunData(0, (char*)"mca_length", &mcaLen);
    if (!CHECK_ERROR(status)) return false;

    if (mcaLen > m_MCALength) return false;

    /* If you don't want to dynamically allocate memory here,
     * then be sure to declare mca as an array of length 8192,
     * since that is the maximum length of the spectrum.
     */
    status = xiaGetRunData(0, (char*)"mca", (void*)mca);
    if (!CHECK_ERROR(status)) return false;

    /* Display the spectrum, write it to a file, etc... */

    return true;
}

auto Ketek::DeinitializeDevice() -> bool
{
    if (!IsDeviceInitialized()) return true;

	auto status = xiaExit();
    if (!CHECK_ERROR(status)) return false;
    xiaCloseLog();
    m_DeviceSerialNumber = "";

    return true;
}
