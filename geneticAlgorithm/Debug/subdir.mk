################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AbstractEcosystem.cpp \
../AbstractEnvironment.cpp \
../AbstractSpecimen.cpp \
../Genome.cpp \
../TestGeneticAlg.cpp \
../Unisolver.cpp \
../UniwalkerEcosystem.cpp \
../UniwalkerEnvironment.cpp \
../UniwalkerSpecimen.cpp 

C_UPPER_SRCS += \
../Random.C \
../main.C 

OBJS += \
./AbstractEcosystem.o \
./AbstractEnvironment.o \
./AbstractSpecimen.o \
./Genome.o \
./Random.o \
./TestGeneticAlg.o \
./Unisolver.o \
./UniwalkerEcosystem.o \
./UniwalkerEnvironment.o \
./UniwalkerSpecimen.o \
./main.o 

CPP_DEPS += \
./AbstractEcosystem.d \
./AbstractEnvironment.d \
./AbstractSpecimen.d \
./Genome.d \
./TestGeneticAlg.d \
./Unisolver.d \
./UniwalkerEcosystem.d \
./UniwalkerEnvironment.d \
./UniwalkerSpecimen.d 

C_UPPER_DEPS += \
./Random.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/Users/dstuck/projects/geneticAlgorithm/headers" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.C
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/Users/dstuck/projects/geneticAlgorithm/headers" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


