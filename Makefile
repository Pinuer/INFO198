CXX = g++
CXXFLAGS = -Wall -std=c++17 -I./include

SRCS_PROG = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp INFO198_SO.cpp src/thread_operation.cpp src/env_setter.cpp 
SRCS_CONTAR = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp Procesos/contar_palabras.cpp
SRCS_PARALLEL = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp src/thread_operation.cpp src/env_setter.cpp Procesos/contar_paralelo.cpp
SRCS_INVERTIR = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp src/invertido.cpp src/env_setter.cpp Procesos/invertir_indice.cpp
SRCS_EJECUTADOR = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp src/thread_operation.cpp src/env_setter.cpp Procesos/ejecutador.cpp
SRCS_PLANIFICADOR = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp src/invertido.cpp src/env_setter.cpp src/func_planificador.cpp Procesos/planificador.cpp
SRCS_DISTRIBUIDOR = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp src/invertido.cpp src/env_setter.cpp src/func_distribuidor.cpp Procesos/distribuidor.cpp
SRCS_CORE = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp src/invertido.cpp src/env_setter.cpp src/func_core.cpp Procesos/core.cpp
SRCS_BUSCADOR = src/func_string.cpp src/file_operation.cpp Procesos/buscador.cpp 
SRCS_CACHE = src/func_string.cpp src/file_operation.cpp Procesos/cache.cpp
SRCS_MOTOR = src/func_string.cpp src/file_operation.cpp Procesos/motor_de_busqueda.cpp

OBJS_PROG = $(SRCS_PROG:src/%.cpp=obj/%.o)
OBJS_CONTAR = $(SRCS_CONTAR:src/%.cpp=obj/%.o)
OBJS_PARALLEL = $(SRCS_PARALLEL:src/%.cpp=obj/%.o)
OBJS_INVERTIR = $(SRCS_INVERTIR:src/%.cpp=obj/%.o)
OBJS_EJECUTOR = $(SRCS_EJECUTADOR:src/%.cpp=obj/%.o)
OBJS_PLANIFICADOR = $(SRCS_PLANIFICADOR:src/%.cpp=obj/%.o)
OBJS_DISTRIBUIDOR = $(SRCS_DISTRIBUIDOR:src/%.cpp=obj/%.o)
OBJS_CORE = $(SRCS_CORE:src/%.cpp=obj/%.o)
OBJS_BUSCADOR = $(SRCS_BUSCADOR:src/%.cpp=obj/%.o)
OBJS_CACHE = $(SRCS_CACHE:src/%.cpp=obj/%.o)
OBJS_MOTOR = $(SRCS_MOTOR:src/%.cpp=obj/%.o)

TARGET_PROG = prog
TARGET_CONTAR = contar_palabras
TARGET_PARALLELO = contar_paralelo
TARGET_INVERTIR = invertir_indice
TARGET_EJECUTADOR = ejecutador
TARGET_PLANIFICADOR = planificador
TARGET_DISTRIBUIDOR = distribuidor
TARGET_CORE = core
TARGET_BUSCADOR = buscador
TARGET_CACHE = cache
TARGET_MOTOR = motor

all: $(TARGET_PROG) $(TARGET_CONTAR) $(TARGET_PARALLELO) $(TARGET_INVERTIR) $(TARGET_EJECUTADOR) $(TARGET_PLANIFICADOR) $(TARGET_DISTRIBUIDOR) $(TARGET_CORE) $(TARGET_BUSCADOR) $(TARGET_CACHE) $(TARGET_MOTOR)

$(TARGET_PROG): $(OBJS_PROG)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_PROG)

$(TARGET_CONTAR): $(OBJS_CONTAR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_CONTAR)

$(TARGET_PARALLELO): $(OBJS_PARALLEL)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_PARALLEL)

$(TARGET_INVERTIR): $(OBJS_INVERTIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_INVERTIR)

$(TARGET_EJECUTADOR): $(OBJS_EJECUTOR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_EJECUTOR)

$(TARGET_PLANIFICADOR): $(OBJS_PLANIFICADOR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_PLANIFICADOR)

$(TARGET_DISTRIBUIDOR): $(OBJS_DISTRIBUIDOR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_DISTRIBUIDOR)

$(TARGET_CORE): $(OBJS_CORE)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_CORE)

$(TARGET_BUSCADOR): $(OBJS_BUSCADOR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_BUSCADOR)

$(TARGET_CACHE): $(OBJS_CACHE)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_CACHE)

$(TARGET_MOTOR): $(OBJS_MOTOR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_MOTOR)

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o $(TARGET_PROG) $(TARGET_CONTAR) $(TARGET_PARALLELO) $(TARGET_INVERTIR) $(TARGET_EJECUTADOR) $(TARGET_PLANIFICADOR) $(TARGET_DISTRIBUIDOR) $(TARGET_CORE) $(TARGET_BUSCADOR) $(TARGET_CACHE) $(TARGET_MOTOR)

.PHONY: all clean
