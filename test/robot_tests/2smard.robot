*** Settings ***
Documentation    Test suite description

Resource    keywords/2smard_keywords.robot

*** Test Cases ***
Pass the 2smard activation sequences via command line
    [Tags]    CLI
    [Teardown]    clean
    Given that the half_1 sequence is A1s\|I5s\|A3s
    And the half_2 sequence is A5s\|I2s\|A1s
    When 2smard is executed with half options
    Then the eps daemon should receive 2 activations and 2 deactivations signals for half 1
    And the eps daemon should receive 2 activations and 2 deactivations signals for half 2


Execute sequence from config file
    [Teardown]    clean
    Given a sample config file test_config.cfg
    When 2smard executed with config option
    Then the eps daemon should receive 3 activations and 3 deactivations signals for half 1
    And the eps daemon should receive 2 activations and 2 deactivations signals for half 2
