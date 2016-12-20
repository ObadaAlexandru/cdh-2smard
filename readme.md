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
##### Activation sequence
The activation sequences have the following form:
```
<state><period><time_unit>|<state><period><time_unit>|...
```
The available state values are: ```{A, I}``` where ```A``` stands for **_Activa_** and ```I``` for **_Inactive_**.
The period must be a positive integer number.
