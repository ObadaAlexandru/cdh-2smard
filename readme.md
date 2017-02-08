# 2-SMARD

2SMARD toolset comprises the following applications:
* **2SMARD activator**: Executes the activation sequence
* **2SMARD checker**: Reads the status of the 2SMARD halfs and displays it to the stdout _(Used for troubleshooting)_

#### 2SMARD activator
###### Configuration
The default configuration file location is ```./config.cfg```, it can be overridden with the ```--config=<config path>``` command line argument.

The configuration file must contain the following properties:
* **half_1** : The activation sequence of 2smard half 1
* **half_2** : The activation sequence of 2smard half 2

Sample configuration file:
```
half_1=A30s|I25s|A45s
half_2=A45s|I15s|A30s|I5m|A45s
```
___
##### Command Line arguments
```
--config=<config file path>
--half_1=<activation sequence>
--half_2=<activation sequence>
```
___
##### Activation sequence
The activation sequences have the following form:
```
<state><period><time_unit>|<state><period><time_unit>|...
```
The available state values are: ```{A, I}``` where ```A``` stands for **_Active_** and ```I``` for **_Inactive_**.
The period must be a positive integer number, it is the number of time units the eps power will be in the specified state.

Example: ```A30s|I1m|A15s``` Active for 30 seconds, inactive for 1 minute, active for 15 seconds.

The system always sends a deactivation signal at exit.
___

#### 2SMARD checker
#### Configuration
Differently from **2SMARD activator*** the activation sequences are not required. But, it requires the sensor activation and sensor read pins configuration.

The configuration file must contain the following properties:
* **pin_half_1**: sensor read pin half 1
* **pin_half_2**: sensor read pin half 2
* **activation_pin_half_1**: sensor half 1 activation pin
* **activation_pin_half_2**: sensor half 2 activation pin

Sample configuration file:
```
pin_half_1=P15
pin_half_2=P16
activation_pin_half_1=P17
activation_pin_half_2=P18
```

_**NB** The pin names must correspond to the mapping specified in [moveio](https://gitlab.lrz.de/move-ii/cdh_moveio#pinmapper-setup-file)_

The application will activate the sensors, read the values and display the status on the stdout.
