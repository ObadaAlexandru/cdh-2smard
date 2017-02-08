*** Settings ***
Documentation    Suite descriptions
Library    OperatingSystem
Library    Process
Library    String
Library    result_checker.py

*** Variables ***

*** Keywords ***
that the half_1 sequence is ${sequence}
    Set Test Variable    ${half_1}    ${sequence}

And the half_2 sequence is ${sequence}
    Set Test Variable    ${half_2}    ${sequence}

2smard is executed with half options
    ${handle}=    Start Process    python    dbus/service.py
    Sleep    1s
    ${result}=    Run Process     2smard_activator    --half_1\=${half_1}    --half_2\=${half_2}
    Log    ${result.stdout}
    Terminate Process    ${handle}
    Should Be Equal As Integers    ${result.rc}    0

the eps daemon should receive ${activations} activations and ${deactivations} deactivations signals for half ${half}
    ${act}    ${deact}=    Get Results For    ${half}    result.txt
    Should Be Equal As Integers    ${act}    ${activations}
    Should Be Equal As Integers   ${deact}    ${deactivations}

a sample config file ${config_file}
    Set Test Variable    ${config}    ${config_file}

2smard executed with config option
    ${handle}=    Start Process    python    dbus/service.py
    Sleep    1s
    ${result}=    Run Process     2smard_activator    --config\=${config}
    Log    ${result.stdout}
    Terminate Process    ${handle}
    Should Be Equal As Integers    ${result.rc}    0

clean
    Remove File    result.txt