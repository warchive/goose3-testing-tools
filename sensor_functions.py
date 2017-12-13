import json


def battery48(value):
	# temporary value
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


def read_json_file(file):
	data = open(file)
	json_data = json.load(data)

	return json_data


def save_to_file(filename, data):
	with open(filename, 'w') as file:
		file.write(data)


def sensor_handler(sensor, value):
	return {

		'battery48': battery48(value),
		'ESCTemp': ESC_temp(value),
		'motorTemp': motor_temp(value),
		'coolingPumpFlowRate': cooling_pump_flow_rate(value),
		'pressureSensor': pressure_sensor(value)

	}.get(sensor, 0)


def sensor_functions(data):
	output = ""

	for packet in data:
		sensor = packet['sensor']
		output += sensor + ", "
		output_data = ""
		num_values = 0

		for value in packet['data']:
			num_values += 1
			output_data += ", "
			output_data += str(sensor_handler(sensor, value))

		# output formatting
		output += str(num_values)
		output += output_data
		output += "\n"

	return output


if __name__ == '__main__':

	DATA = "[{\"sensor\": \"battery48\", \"data\": [-50, 30]}, {\"sensor\": \"ESCTemp\", \"data\": [2, 20, 40]}, {\"sensor\": \"pressureSensor\", \"data\": [200, 500, 40]}]"
	json_data = json.loads(DATA)
	output_text = sensor_functions(json_data)
	output_file = "sensorOutput.txt"

	save_to_file(output_file, output_text)
	print(output_text)
