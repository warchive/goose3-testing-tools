"""
 * @file sensor_functions.py
 * @brief sensor_functions provides the functions necessary for processing the data values of each sensor
 *
 * @author Bob Wei
 * @date December 19, 2017
 * @bug No known bugs
"""

# json library for parsing json file
import json


# SENSOR FUNCTIONS ===============================================================


# Type: temperature sensor
# Component: main battery
# Units: degrees celsius
def battery_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: temperature sensor
# Component: motor
# Units: degrees celsius
def motor_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: temperature sensor
# Component: friction drive
# Units: degrees celsius
def friction_drive_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: temperature sensor
# Component: EC-brake
# Units: degrees celsius
def ec_brake_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: temperature sensor
# Component: embedded system
# Units: degrees celsius
def embedded_system_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: temperature sensor
# Component: ESC
# Units: degrees celsius
def esc_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: temperature sensor
# Component: liquid cooling
# Units: degrees celsius
def liquid_cooling_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: temperature sensor
# Component: friction brakes
# Units: degrees celsius
def friction_brakes_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: temperature sensor
# Component: EC-solenoid
# Units: degrees celsius
def ec_solenoid_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: temperature sensor
# Component: friction piston solenoid
# Units: degrees celsius
def friction_piston_solenoid_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: current sensor
# Component: main battery
# Units: volts
def main_battery_current(value):
	if value > 55:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: tilt sensors
# Component: inclination
# Units:
def inclination(value):
	return 0  # No values at the moment


# Type: navigation sensor
# Component: IMU front
# Units: degrees celsius
def imu_front_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: navigation sensor
# Component: IMU back
# Units: degrees celsius
def imu_back_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# Type: navigation sensor
# Component: IMU front
# Units: gauss
def imu_front_magnetic(value):
	if value > 800:
		return 1
	elif value < 0:
		return -1
	else:
		return 0


# Type: navigation sensor
# Component: IMU back
# Units: gauss
def imu_back_magnetic(value):
	if value > 800:
		return 1
	elif value < 0:
		return -1
	else:
		return 0


# Type: navigation sensor (shaft encoder)
# Units: rpm
def shaft_encoder(value):
	if value > 9050:
		return 1
	else:
		return 0


# Type: navigation sensor
# Component: electronic speed controller
# Units: rpm
def electronic_speed_controller(value):
	if value > 9050:
		return 1
	else:
		return 0


# Type: lateral stability sensor (photoelectric distance sensor)
# Units: millimetres
def photoelectric_distance(value):
	if value > 80:
		return 1
	elif value < 20:
		return -1
	else:
		return 0


# Type: reed sensor
# Component: EC-Brake
# Units: binary (0/1)
def ec_brake_state(value):
	return value  # 0 or 1 state


# Type: pressure sensor
# Component: liquid cooling
# Units: psi
def liquid_cooling_pressure(value):
	if value > 100:
		return 1
	else:
		return 0


# END OF SENSOR FUNCTIONS ==============================================================


# Reads data from json file
def read_json_file(file):
	data = open(file)
	json_data = json.load(data)

	return json_data


# Saves data to file in the correct format for graphing
def save_to_file(filename, data):
	with open(filename, 'w') as file:
		file.write(data)


# Calls the corresponding sensor function based on data input
def sensor_handler(sensor, value):
	return {
		'batteryTemp': battery_temp(value),
		'motorTemp': motor_temp(value),
		'frictionDriveTemp': friction_drive_temp(value),
		'ECBrakeTemp': ec_brake_temp(value),
		'embeddedSystemTemp': embedded_system_temp(value),
		'ESCTemp': esc_temp(value),
		'liquidCoolingTemp': liquid_cooling_temp(value),
		'frictionBrakesTemp': friction_brakes_temp(value),
		'ECSolenoidTemp': ec_solenoid_temp(value),
		'frictionPistonSolenoidTemp': friction_piston_solenoid_temp(value),
		'mainBatteryCurrent': main_battery_current(value),
		'inclinationSensor': inclination(value),
		'IMUFrontTemp': imu_front_temp(value),
		'IMUFrontMagnetic': imu_front_magnetic(value),
		'IMUBackTemp': imu_back_temp(value),
		'IMUBackMagnetic': imu_back_magnetic(value),
		'shaftEncoder': shaft_encoder(value),
		'electronicSpeedController': electronic_speed_controller(value),
		'photoelectricDistance': photoelectric_distance(value),
		'ecBrakeState': ec_brake_state(value),
		'liquidCoolingPressure': liquid_cooling_pressure(value)
	}.get(sensor, 0)


def read_and_output(data):
	# primary output string
	output = ""

	for packet in data:
		sensor = packet['sensor']
		output += sensor + ", "

		# output including list of raw data values
		raw_data = ""
		# output including list of binary state values for each corresponding raw value
		binary_data = ""
		num_values = 0

		for value in packet['data']:
			num_values += 1
			raw_data += ", "
			raw_data += str(value)
			binary_data += ", "
			binary_data += str(sensor_handler(sensor, value))

		# output formatting
		output += str(num_values)
		output += raw_data
		output += binary_data
		output += "\n"

	return output


# Example Usage ==========================================================================

# Test using example input file
if __name__ == '__main__':

	# obtains json data from example file
	json_data = read_json_file("sensorInput.json")
	output_text = read_and_output(json_data)
	output_file = "sensorOutput.txt"

	# saves example data to text file (ready to graph)
	save_to_file(output_file, output_text)
