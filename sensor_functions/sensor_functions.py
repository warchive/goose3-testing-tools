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


def battery48(value):
	# temporary values
	if value > 0:
		return 1
	else:
		return -1


def ESC_temp(value):
	if -40 <= value < 120:
		return 1
	else:
		return -1


def motor_temp(value):
	# temporary value
	if value > 0:
		return 1
	else:
		return -1


def cooling_pump_flow_rate(value):
	# temporary value
	if value > 0:
		return 1
	else:
		return -1


def pressure_sensor(value):
	if value > 250:
		return -1
	else:
		return 1


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
		'battery48': battery48(value),
		'ESCTemp': ESC_temp(value),
		'motorTemp': motor_temp(value),
		'coolingPumpFlowRate': cooling_pump_flow_rate(value),
		'pressureSensor': pressure_sensor(value)
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
