#pragma once
#ifndef MOTOR_H
#define MOTOR_H
#include <memory>
#include <algorithm>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <filesystem>
#include <ximc.h>



namespace MotorVariables
{
	struct Settings
	{
		float motorPos{};
		float minMotorPos{}, middleMotorPos{}, maxMotorPos{};
		float stagePos{};
		float minStagePos{}, middleStagePos{}, maxStagePos{};
		float motorRange{}, stageRange{};
		float stepsPerMMRatio{ 800.f }; 
	};
}

namespace StandaVariables
{
	struct C_Settings
	{
		result_t result{};
		calibration_t calibration{};
		status_t state{};
		status_calb_t calb_state{};
	};
}

class Motor final
{
public:
	Motor();
	/* Getters */
	auto GetDeviceSerNum() const;
	auto GetDeviceRange() const;
	auto GetDeviceActualStagePos() const;

	/* Setters */
	auto SetDeviceName(const char* device_name);
	auto SetSerNum(unsigned int s_n);
	auto SetResult(result_t result);
	auto SetCalibration(calibration_t calibration);
	auto SetState(status_t state);
	auto SetCalbState(status_calb_t calb_state);
	auto SetRange(const float min_motor_deg, const float max_motor_deg);

	auto SetStepsPerMMRatio(const int stepsPerMMRatio) -> void 
	{ 
		m_MotorSettings->stepsPerMMRatio = stepsPerMMRatio; 
		UpdateStageRange(); 
		UpdateCurrentPosition(); 
	};

	auto UpdateCurrentPosition() -> void
	{
		m_MotorSettings->motorPos = m_StandaSettings->state.CurPosition;
		m_MotorSettings->stagePos = m_MotorSettings->motorPos / m_MotorSettings->stepsPerMMRatio;
	}

	auto GoCenter();
	auto GoHomeAndZero();
	auto GoToPos(const float stage_position);

	/* Move constructor */
	Motor(Motor&& other) noexcept 
		: m_MotorSettings(std::move(other.m_MotorSettings)), 
		m_StandaSettings(std::move(other.m_StandaSettings)), 
		m_DeviceName(std::move(other.m_DeviceName)),
		m_SerNum(other.m_SerNum)
	{
		other.m_MotorSettings = nullptr;
		other.m_StandaSettings = nullptr;
		other.m_DeviceName = nullptr;
		other.m_SerNum = 0;
	};

	/* Move assignment */
	auto& operator=(Motor&& other) noexcept
	{
		m_MotorSettings.reset(other.m_MotorSettings.release());
		m_StandaSettings.reset(other.m_StandaSettings.release());
		m_DeviceName.reset(other.m_DeviceName.release());
		m_SerNum = other.m_SerNum;
		return *this;
	};

private:
	auto UpdateStageRange() -> void 
	{
		/* Min position */
		m_MotorSettings->minStagePos = m_MotorSettings->minMotorPos / m_MotorSettings->stepsPerMMRatio;

		/* Middle position */
		m_MotorSettings->middleStagePos = m_MotorSettings->middleMotorPos / m_MotorSettings->stepsPerMMRatio;

		/* Max position */
		m_MotorSettings->maxStagePos = m_MotorSettings->maxMotorPos / m_MotorSettings->stepsPerMMRatio;

		/* Set Whole Motor Range */
		m_MotorSettings->stageRange = m_MotorSettings->motorRange / m_MotorSettings->stepsPerMMRatio;
	};


private:
	std::unique_ptr<MotorVariables::Settings> m_MotorSettings{};
	std::unique_ptr<StandaVariables::C_Settings> m_StandaSettings{};
	//int m_StepsPerMM{ 800 }; 
	std::unique_ptr<char[]> m_DeviceName{};
	unsigned int m_SerNum{};
	const long long wait_delay_milliseconds{ 500 };
};

class MotorArray final
{
public:
	MotorArray(const std::string ipAddress);
	bool InitAllMotors(const char* ip_address);
	auto FillNames();

	/* Getter */
	std::map<unsigned int, float> GetNamesWithRanges() const;
	float GetActualStagePos(const std::string& motor_sn) const;
	auto MotorHasSerialNumber(const std::string& motor_sn) const -> bool;

	/* Setter */
	float GoMotorHome(const std::string& motor_sn);
	float GoMotorCenter(const std::string& motor_sn);
	float GoMotorToAbsPos(const std::string& motor_sn, float abs_pos);
	float GoMotorOffset(const std::string& motor_sn, float offset);

	auto AreAllMotorsInitialized() const -> bool { return !m_UninitializedMotors.size(); };
	auto GetUninitializedMotors() const -> std::vector<unsigned int> { return m_UninitializedMotors; };

	auto SetStepsPerMMForTheMotor(const std::string motor_sn, const int stepsPerMM) -> void;

private:
	std::vector<Motor> m_MotorsArray{};
	std::map<unsigned int, float> m_NamesOfMotorsWithRanges{};
	const float error_position = 0.0f;

	std::vector<unsigned int> m_UninitializedMotors{};
};

#endif
