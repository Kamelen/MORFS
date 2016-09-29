cmake_minimum_required(VERSION 3.6)
project(RFPredictor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    RFPredictor/arff_attr.cpp
    RFPredictor/arff_attr.h
    RFPredictor/arff_data.cpp
    RFPredictor/arff_data.h
    RFPredictor/arff_instance.cpp
    RFPredictor/arff_instance.h
    RFPredictor/arff_lexer.cpp
    RFPredictor/arff_lexer.h
    RFPredictor/arff_parser.cpp
    RFPredictor/arff_parser.h
    RFPredictor/arff_scanner.cpp
    RFPredictor/arff_scanner.h
    RFPredictor/arff_token.cpp
    RFPredictor/arff_token.h
    RFPredictor/arff_utils.cpp
    RFPredictor/arff_utils.h
    RFPredictor/arff_value.cpp
    RFPredictor/arff_value.h
    RFPredictor/DataLoader.cpp
    RFPredictor/DataLoader.h
    RFPredictor/Explorer.cpp
    RFPredictor/Explorer.h
    RFPredictor/IPredictor.h
    RFPredictor/ISplitter.h
    RFPredictor/ITreeClassifier.h
    RFPredictor/main.cpp
    RFPredictor/MORandomForests.cpp
    RFPredictor/MORandomForests.h
    RFPredictor/Node.cpp
    RFPredictor/Node.h
    RFPredictor/RandomMultiCVCL.cpp
    RFPredictor/RandomMultiCVCL.h
    RFPredictor/RandomMultiMSE.cpp
    RFPredictor/RandomMultiMSE.h
    RFPredictor/RandomSingleMSE.cpp
    RFPredictor/RandomSingleMSE.h
    RFPredictor/SORandomForests.cpp
    RFPredictor/SORandomForests.h
    RFPredictor/Tree.cpp
    RFPredictor/Tree.h
    RFPredictor/Utils.cpp
    RFPredictor/Utils.h)

add_executable(RFPredictor ${SOURCE_FILES})