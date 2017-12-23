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

# degrees celsius
def battery_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# degrees celsius
def friction_drive_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# degrees celsius
def ec_brake_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# degrees celsius
def embedded_system_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# degrees celsius
def esc_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# degrees celsius
def liquid_cooling_temp(value):
	if value > 125:
		return 1
	elif value < -40:
		return -1
	else:
		return 0


# volts
def main_battery_current(value):
	if value > 55:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


def inclination(value):
	return 0  # No values at the moment


# degrees celsius
def imu_front_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# degrees celsius
def imu_back_temp(value):
	if value > 60:
		return 1
	elif value < 5:
		return -1
	else:
		return 0


# gauss
def imu_front_magnetic(value):
	if value > 800:
		return 1
	elif value < 0:
		return -1
	else:
		return 0


# gauss
def imu_back_magnetic(value):
	if value > 800:
		return 1
	elif value < 0:
		return -1
	else:
		return 0


# millimetres
def photoelectric_distance(value):
	return 0  # no values at the moment


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
		'frictionDriveTemp': friction_drive_temp(value),
		'ECBrakeTemp': ec_brake_temp(value),
		'embeddedSystemTemp': embedded_system_temp(value),
		'ESCTemp': esc_temp(value),
		'liquidCoolingTemp': liquid_cooling_temp(value),
		'mainBatteryCurrent': main_battery_current(value),
		'inclinationSensor': inclination(value),
		'IMUFrontTemp': imu_front_temp(value),
		'IMUFrontMagnetic': imu_front_magnetic(value),
		'IMUBackTemp': imu_back_temp(value),
		'IMUBackMagnetic': imu_back_magnetic(value),
		'photoelectricDistance': photoelectric_distance(value)
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


# Test using example input file
if __name__ == '__main__':

	# obtains json data from example file
	json_data = read_json_file("sensorInput.json")
	output_text = read_and_output(json_data)
	output_file = "sensorOutput.txt"

	# saves example data to text file (ready to graph)
	save_to_file(output_file, output_text)
