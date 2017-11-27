# Tools need and Members working on them

## Team Loop

Create harware in a loop framework. This will include the following:
- Write a command line tool to take argument for the pin and it's value to set
  - {0, D, 15, 1}    // first: delay value, second: pin type, third: pin number, fourth: pin value
  - {0, A, 1, 2}

The examples above show a packet system we will use for this tool. For digital
`D` will be sued and for analog `A` will be used. The tool will impose restrictions
on what the value of the pin can be. Based on Arduino Standars, ditital pins will be
in range: `0 >= i <= 1`, where i is the pin value. For analog pins the range is
`0 >= i <= 1024`, where i is the pin value.
- Write a GUI that will have each pin mapped on screen and we can toggle each value the
       the way we want it to be. Make sure restrictions are imposed on the GUI side as well.
       This GUI will use the command line tool behind the screen.
  - Features needed:
       1) All pins mapped (Arduino Mega)
       2) Browse button to get a file of inputs and process that
       3) Read a delay value from the packet to specify how much to wait before sending this packet
- Tools to use for this:

 We should consider using Qt. We will most likely make our front end in Qt so it will be a nice
experience working with that. Also this way we will stay on C++ side and avoid Java complexities

**Team members:** `Ayush, Mathieu and Ambareesh`

## Team function

Create functions for each sensor: This will include the following:
- Write a command line that will take an input and give you a value. This value will be the sensor function value:
  - {battery48TempSensor, 1, 55} // first: function name, second: num arguments, third: argument values
  - {battery48power, 2, 55, 20}

We will provide the doc that has all the values for each sensor we will use
- Write a GUI or an extention to this commndline tool where we feed it a file of inputs and it produces
PNG files for the graph for that function and highlits the point that has been provided. This can be
extended to include more graphs but let's start with simple graphs. Ask for output folder and input file
- Tools to use for this:
  - I think python is the best way to go here
  - Use various graph libraries (Matlab library) to plot graphs

**Team members:** `Bob, Ibrahim and Heather`
