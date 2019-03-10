#ifndef ADDON_ERRORS_H
#define ADDON_ERRORS_H

#include<iostream>


// common errors
const std::string DEFAULT_ERR_MSG = "Something unexpected happened";
const std::string IN_DEVELOPMENT = "In development";


// wrong arguments errors
const std::string WRONG_ARGUMENT_NUMBER = "Invalid number of arguments";
const std::string WRONG_ARGUMENT_TYPE = "Invalid argument type";

const std::string MUST_BE_A_STRING = "Parameter should be a string";
const std::string MUST_BE_AN_INSTANCE_OF_WORD = "Argument must be an instance of Word";
const std::string MUST_BE_AN_ARRAY_OF_WORDS = "Argument must be an array of Words";
const std::string MUST_BE_A_STRING_OR_A_WORD = "Argument must be either a string or an instance of Word";
const std::string MUST_BE_AN_ARRAY_OF_SENTENCES = "Argument must be an array of Sentences";

const std::string NO_EMPTY_ARGUMENTS = "None of parameters can be empty";
const std::string INVALID_ADRUMENT = "Invalid argument";

const std::string WRONG_SIZE_OF_ARGUMENT_ARR = "Argument array is wrong size";
const std::string WRONG_PROPERTIES_FOR_ACTIVE_OPTS = "Object properties don't contain required options";


// wrong path errors
const std::string WRONG_CONFIG_PATH = "Config file doesn't exist";
const std::string NO_RESOURCES_FOR_SELECTED_LANG = "No resources for selected language";

#endif // ADDON_ERRORS_H
