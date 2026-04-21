CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = main.cpp \
       Person.cpp \
       Patient.cpp \
       Doctor.cpp \
       Room.cpp \
       Appointment.cpp \
       Bill.cpp \
       Hospital_core.cpp \
       Hospital_patient.cpp \
       Hospital_doctor.cpp \
       Hospital_appointment.cpp \
       Hospital_room.cpp \
       Hospital_billing.cpp \
       Hospital_fileio.cpp \
       Hospital_run.cpp

OBJS   = $(SRCS:.cpp=.o)
TARGET = hospital

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
