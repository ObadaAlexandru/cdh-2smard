Error Codes
===========

|   Code   |  Description  | Next steps |
|----------|---------------|------------|
| 2SMARD-001 | Invalid command line arguments| Make sure the provided command line arguments are correct |
| 2SMARD-002 | Invalid config file properties | Make sure that the config file is valid |
| 2SMARD-003 | Dbus failure | Check if the EPS daemon is running |
| 2SMARD-004 | Invalid execution sequence | Make sure a valid execution sequence is provided |
| 2SMARD-005 | Unexpected error | - |

Configuration File
==================

The configuration file contains key value pairs separated by the equals symbol `=`, lines starting with `#` are interpreted as comments. It is required by 2smard_activator as well as 2smard_checker. 2smard_activator expects two activation sequences, one per half. 2smard_checker expects sensor read pins and sensor activation pins.

Settings
--------

| Name                       | Default                        | Description                         |
|----------------------------|--------------------------------|-------------------------------------|
| half\_1                    | A5s\|I4000s\|A4040s\|I300s     | Half one activation sequence        |
| half\_2                    | A5s\|I4000s\|A4040s\|I300s     | Half two activation sequence        |
| pin\_half\_1               | --                             | Sensor read pin half one            |
| pin\_half\_2               | --                             | Sensor read pin half two            |
| activation\_pin\_half\_1   | --                             | Sensor half one activation pin      |
| activation\_pin\_half\_2   | --                             | Sensor half two activation pin      |
