#include "Motor.h"
/* Motor */

Motor::Motor()
{
	m_MotorSettings = std::make_unique<MotorVariables::Settings>();
	m_StandaSettings = std::make_unique<StandaVariables::C_Settings>();
}

auto Motor::GetDeviceSerNum() const
{
	return m_SerNum;
}

auto Motor::GetDeviceRange() const
{
	return m_MotorSettings->stageRange;
}

auto Motor::GetDeviceActualStagePos() const
{
	return m_MotorSettings->stagePos;
}

auto Motor::SetDeviceName(const char* device_name)
{
	size_t char_count{};
	while (*device_name != '\0')
	{
		++char_count;
		++device_name;
	}
	device_name -= char_count;

	m_DeviceName = std::make_unique<char[]>(char_count + 1);
	//strncpy(m_DeviceName.get(), device_name, char_count);
	memcpy(m_DeviceName.get(), device_name, char_count);
	m_DeviceName[char_count] = '\0';
}

auto Motor::SetSerNum(unsigned int s_n)
{
	m_SerNum = s_n;
}

auto Motor::SetResult(result_t result)
{
	m_StandaSettings->result = result;
}

auto Motor::SetCalibration(calibration_t calibration)
{
	m_StandaSettings->calibration = calibration;
}

auto Motor::SetState(status_t state)
{
	m_StandaSettings->state = state;
}

auto Motor::SetCalbState(status_calb_t calb_state)
{
	m_StandaSettings->calb_state = calb_state;
}

auto Motor::SetRange(const float min_motor_deg, const float max_motor_deg)
{
	/* Min position */
	m_MotorSettings->minMotorPos = min_motor_deg;
	//m_MotorSettings->minStagePos = min_motor_deg / deg_per_mm;
	m_MotorSettings->minStagePos = min_motor_deg / m_MotorSettings->stepsPerMMRatio;

	/* Middle position */
	m_MotorSettings->middleMotorPos = (max_motor_deg - min_motor_deg) / 2.f;
	//m_MotorSettings->middleStagePos = m_MotorSettings->middleMotorPos / deg_per_mm;
	m_MotorSettings->middleStagePos = m_MotorSettings->middleMotorPos / m_MotorSettings->stepsPerMMRatio;

	/* Max position */
	m_MotorSettings->maxMotorPos = max_motor_deg;
	//m_MotorSettings->maxStagePos = max_motor_deg / deg_per_mm;
	m_MotorSettings->maxStagePos = max_motor_deg / m_MotorSettings->stepsPerMMRatio;

	/* Set Whole Motor Range */
	m_MotorSettings->motorRange = max_motor_deg - min_motor_deg;
	//m_MotorSettings->stageRange = (max_motor_deg - min_motor_deg) / deg_per_mm;
	m_MotorSettings->stageRange = (max_motor_deg - min_motor_deg) / m_MotorSettings->stepsPerMMRatio;
}

auto Motor::UpdateCurPosThroughStanda()
{
	m_MotorSettings->motorPos = m_StandaSettings->state.CurPosition;
	//m_MotorSettings->stagePos = m_StandaSettings->state.CurPosition / deg_per_mm;
	m_MotorSettings->stagePos = m_StandaSettings->state.CurPosition / m_MotorSettings->stepsPerMMRatio;
}

auto Motor::GoCenter()
{
	device_t device_c;
	device_c = open_device(m_DeviceName.get());

	{
		if ((m_StandaSettings->result = command_move_calb
		(
			device_c, 
			m_MotorSettings->middleMotorPos, 
			&m_StandaSettings->calibration
		)
			) != result_ok)
		{
			/* Error command_move_calb */
			return false;
		}
		/* Wait to Stop */
		if ((m_StandaSettings->result = command_wait_for_stop
		(
			device_c, 
			100
		)
			) != result_ok)
		{
			/* Error command_wait_for_stop */
			return false;
		}
		/* Wait for elimination of vibrations */
		std::this_thread::sleep_for(std::chrono::milliseconds(wait_delay_milliseconds));
		/* Get Status */
		if ((m_StandaSettings->result = get_status
		(
			device_c, 
			&m_StandaSettings->state 
		)
			) != result_ok)
		{
			/* Error getting status */
			return false;
		}
		/* Get Calibrated Status */
		if ((m_StandaSettings->result = get_status_calb
		(
			device_c, 
			&m_StandaSettings->calb_state, 
			&m_StandaSettings->calibration
		)
			) != result_ok)
		{
			/* Error getting status */
			return false;
		}
	}

	close_device(&device_c);

	UpdateCurPosThroughStanda();
}

auto Motor::GoHomeAndZero()
{
	device_t device_c;
	device_c = open_device(m_DeviceName.get());

	{
		if ((m_StandaSettings->result = command_homezero(device_c) != result_ok)) return false;
		/* Wait to Stop */
		if ((m_StandaSettings->result = command_wait_for_stop
		(
			device_c, 
			100
		)
			) != result_ok)
		{
			/* Error command_wait_for_stop */
			return false;
		}
		/* Wait for elimination of vibrations */
		std::this_thread::sleep_for(std::chrono::milliseconds(wait_delay_milliseconds));
		/* Get Status */
		if ((m_StandaSettings->result = get_status
		(
			device_c, 
			&m_StandaSettings->state 
		)
			) != result_ok)
		{
			/* Error getting status */
			return false;
		}
		/* Get Calibrated Status */
		if ((m_StandaSettings->result = get_status_calb
		(
			device_c, 
			&m_StandaSettings->calb_state, 
			&m_StandaSettings->calibration
		)
			) != result_ok)
		{
			/* Error getting status */
			return false;
		}
	}

	close_device(&device_c);

	UpdateCurPosThroughStanda();
}

auto Motor::GoToPos(const float stage_position)
{
	device_t device_c;
	device_c = open_device(&m_DeviceName[0]);

	/* Get Status */
	if ((m_StandaSettings->result = get_status_calb
	(
		device_c, 
		&m_StandaSettings->calb_state, 
		&m_StandaSettings->calibration
	)
		) != result_ok)
	{
		/* Error getting status */
		return false;
	}

	/* If stage_position is outside of motor's range -> return */
	if (stage_position < m_MotorSettings->minStagePos || 
		stage_position > m_MotorSettings->maxStagePos)
		return false;

	{
		//float motor_position = stage_position * deg_per_mm;
		float motor_position = stage_position * m_MotorSettings->stepsPerMMRatio;
		if ((m_StandaSettings->result = command_move_calb
		(
			device_c, 
			motor_position, 
			&m_StandaSettings->calibration
		) != result_ok)) 
			return false;
		/* Wait to Stop */
		if ((m_StandaSettings->result = command_wait_for_stop
		(
			device_c, 
			100
		)
			) != result_ok)
		{
			/* Error command_wait_for_stop */
			return false;
		}
		/* Wait for elimination of vibrations */
		std::this_thread::sleep_for(std::chrono::milliseconds(wait_delay_milliseconds));
		/* Get Status */
		if ((m_StandaSettings->result = get_status
		(
			device_c, 
			&m_StandaSettings->state 
		)
			) != result_ok)
		{
			/* Error getting status */
			return false;
		}
		/* Get Calibrated Status */
		if ((m_StandaSettings->result = get_status_calb
		(
			device_c, 
			&m_StandaSettings->calb_state, 
			&m_StandaSettings->calibration
		)
			) != result_ok)
		{
			/* Error getting status */
			return false;
		}
	}
	close_device(&device_c);

	UpdateCurPosThroughStanda();
}

/* MotorArray */
MotorArray::MotorArray()
{
	InitAllMotors();
}

auto MotorArray::FillNames()
{
	for (const auto& motor : m_MotorsArray)
	{
		m_NamesOfMotorsWithRanges.emplace(std::make_pair(motor.GetDeviceSerNum(), motor.GetDeviceRange()));
	}
}

std::map<unsigned int, float> MotorArray::GetNamesWithRanges() const
{
	return m_NamesOfMotorsWithRanges;
}

float MotorArray::GetActualStagePos(const std::string& motor_sn) const
{
	auto serial_num{ 0 };
	try { serial_num = std::stoi(motor_sn);}
	catch (std::invalid_argument const& ex) { return error_position; }

	for (auto motor{ 0 }; motor < m_MotorsArray.size(); ++motor)
	{
		if (m_MotorsArray[motor].GetDeviceSerNum() == serial_num)
			return m_MotorsArray[motor].GetDeviceActualStagePos();
	}
	return error_position;
}

auto MotorArray::MotorHasSerialNumber(const std::string& motor_sn) const -> bool
{
	auto serial_num{ 0 };
	try { serial_num = std::stoi(motor_sn);}
	catch (std::invalid_argument const& ex) { return false; }

	for (auto motor{ 0 }; motor < m_MotorsArray.size(); ++motor)
	{
		if (m_MotorsArray[motor].GetDeviceSerNum() == serial_num)
			return true;
	}
	return false;
}

float MotorArray::GoMotorHome(const std::string& motor_sn)
{	
	auto serial_num{ 0 };
	try { serial_num = std::stoi(motor_sn);}
	catch (std::invalid_argument const& ex) { return error_position; }

	for (auto motor{ 0 }; motor < m_MotorsArray.size(); ++motor)
	{
		if (m_MotorsArray[motor].GetDeviceSerNum() == serial_num)
		{
			m_MotorsArray[motor].GoHomeAndZero();
			return m_MotorsArray[motor].GetDeviceActualStagePos();
		}
	}
	return error_position;
}

float MotorArray::GoMotorCenter(const std::string& motor_sn)
{
	auto serial_num{ 0 };
	try { serial_num = std::stoi(motor_sn);}
	catch (std::invalid_argument const& ex) { return error_position; }

	for (auto motor{ 0 }; motor < m_MotorsArray.size(); ++motor)
	{
		if (m_MotorsArray[motor].GetDeviceSerNum() == serial_num)
		{
			m_MotorsArray[motor].GoCenter();
			return m_MotorsArray[motor].GetDeviceActualStagePos();
		}
	}
	return error_position;
}

float MotorArray::GoMotorToAbsPos(const std::string& motor_sn, float abs_pos)
{
	auto serial_num{ 0 };
	try { serial_num = std::stoi(motor_sn);}
	catch (std::invalid_argument const& ex) { return error_position; }

	for (auto motor{ 0 }; motor < m_MotorsArray.size(); ++motor)
	{
		if (m_MotorsArray[motor].GetDeviceSerNum() == serial_num)
		{
			m_MotorsArray[motor].GoToPos(abs_pos);
			return m_MotorsArray[motor].GetDeviceActualStagePos();
		}
	}
	return error_position;
}

float MotorArray::GoMotorOffset(const std::string& motor_sn, float offset)
{	
	auto serial_num{ 0 };
	try { serial_num = std::stoi(motor_sn);}
	catch (std::invalid_argument const& ex) { return error_position; }

	for (auto motor{ 0 }; motor < m_MotorsArray.size(); ++motor)
	{
		if (m_MotorsArray[motor].GetDeviceSerNum() == serial_num)
		{
			if (offset + m_MotorsArray[motor].GetDeviceActualStagePos() < 0.f || 
				offset + m_MotorsArray[motor].GetDeviceActualStagePos() > m_MotorsArray[motor].GetDeviceRange()) 
				return m_MotorsArray[motor].GetDeviceActualStagePos();

			m_MotorsArray[motor].GoToPos(m_MotorsArray[motor].GetDeviceActualStagePos() + offset);
			return m_MotorsArray[motor].GetDeviceActualStagePos();
		}
	}
	return error_position;
}

auto MotorArray::SetStepsPerMMForTheMotor(const std::string motor_sn, const int stepsPerMM) -> void
{
	auto serial_num{ 0 };
	try { serial_num = std::stoi(motor_sn);}
	catch (std::invalid_argument const& ex) { return ; }

	if (stepsPerMM <= 0) return;

	for (auto motor{ 0 }; motor < m_MotorsArray.size(); ++motor)
	{
		if (m_MotorsArray[motor].GetDeviceSerNum() == serial_num)
		{
			m_MotorsArray[motor].SetStepsPerMMRatio((float)stepsPerMM);
			break;
		}
	}

}

bool MotorArray::InitAllMotors()
{
	auto appendUnitializedMotor = [&](const unsigned int motorSN, const int motorNum) 
		{
			m_UninitializedMotors.push_back(motorSN);
			m_MotorsArray[motorNum].SetSerNum(0);
		};

	m_UninitializedMotors.clear();

	const char* correction_table = "table.txt";
	// Checking whether table.txt is inside the working directory
	{
		auto currPath = std::filesystem::current_path();
		if (!std::filesystem::exists(currPath / correction_table)) return false;
	}

	result_t result_c;
	result_c = set_bindy_key("keyfile.sqlite");
	if (result_c != result_ok) return false;

	device_enumeration_t devenum_c;
	const int probe_flags = ENUMERATE_PROBE | ENUMERATE_NETWORK;
	const char* enumerate_hints = "addr=";
	devenum_c = enumerate_devices(probe_flags, enumerate_hints);
	if (!devenum_c) return false;

	int names_count = get_device_count(devenum_c);
	/* Here we need to clear motor list */
	m_MotorsArray.clear();
	m_MotorsArray.reserve(names_count);

	char device_name[256];
	device_t device_c;
	status_t state_c;
	status_calb_t state_calb_c;
	emf_settings_t emfSettings{};
	calibration_t calibration_c;
	stage_settings_t stage_settings_c;
	edges_settings_calb_t edges_settings_calb_c;
	stage_information_t stage_information_c;
	unsigned int device_sn{};
	for (int i = 0; i < names_count; ++i)
	{
		m_MotorsArray.emplace_back(Motor());
		m_MotorsArray[i].SetResult(result_c);

		strcpy(device_name, get_device_name(devenum_c, i));
		m_MotorsArray[i].SetDeviceName(device_name);
		device_c = open_device(device_name);
		get_serial_number(device_c, &device_sn);
		m_MotorsArray[i].SetSerNum(device_sn);

		if ((result_c = get_status(device_c, &state_c)) != result_ok)
		{
			appendUnitializedMotor(device_sn, i);
			continue;
		}

		if (result_c = get_stage_settings(device_c, &stage_settings_c) != result_ok)
		{
			appendUnitializedMotor(device_sn, i);
			continue;
		}

		if (get_stage_information(device_c, &stage_information_c) != result_ok)
		{
			appendUnitializedMotor(device_sn, i);
			continue;
		}

		if (result_c = get_emf_settings(device_c, &emfSettings) != result_ok)
		{
			appendUnitializedMotor(device_sn, i);
			continue;
		}
		if (emfSettings.Km == 0.0f)
		{
			appendUnitializedMotor(device_sn, i);
			continue;
		}
		//m_MotorsArray[i].SetGearRatio(emfSettings.Km);

		// The device_t device parameter in this function is a C pointer, unlike most library functions that use this parameter
		if ((result_c = set_correction_table(device_c, correction_table)) != result_ok)
		{
			appendUnitializedMotor(device_sn, i);
			continue;
		}

		calibration_c.A = 1;
		calibration_c.MicrostepMode = MICROSTEP_MODE_FULL;
		m_MotorsArray[i].SetCalibration(calibration_c);

		/* Get Status */
		if ((result_c = get_status_calb(device_c, &state_calb_c, &calibration_c)) != result_ok)
		{
			appendUnitializedMotor(device_sn, i);
			continue;
		}
		m_MotorsArray[i].SetState(state_c);

		get_edges_settings_calb(device_c, &edges_settings_calb_c, &calibration_c);
		m_MotorsArray[i].SetRange(edges_settings_calb_c.LeftBorder, edges_settings_calb_c.RightBorder);

		m_MotorsArray[i].UpdateCurPosThroughStanda();

		close_device(&device_c);
	}
	
	std::sort(m_MotorsArray.begin(), m_MotorsArray.end(), [](Motor& left, Motor& right)
		{
			return (left.GetDeviceSerNum() < right.GetDeviceSerNum());
		});

	free_enumerate_devices(devenum_c);
	FillNames();

}
