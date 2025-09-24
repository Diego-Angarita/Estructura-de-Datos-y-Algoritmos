# Makefile para compilar Blas.cpp con OpenBLAS
# Autor: Sistema de desarrollo
# Fecha: $(date)

# Variables del compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -march=native
TARGET = blas_demo
SOURCE = Blas.cpp

# Variables de OpenBLAS - ajustar según tu instalación
# Para vcpkg (ajustar la ruta):
VCPKG_ROOT = C:/vcpkg
OPENBLAS_INCLUDE_VCPKG = $(VCPKG_ROOT)/installed/x64-windows/include
OPENBLAS_LIB_VCPKG = $(VCPKG_ROOT)/installed/x64-windows/lib

# Para instalación manual (ajustar la ruta):
OPENBLAS_ROOT = C:/OpenBLAS
OPENBLAS_INCLUDE_MANUAL = $(OPENBLAS_ROOT)/include
OPENBLAS_LIB_MANUAL = $(OPENBLAS_ROOT)/lib

# Para MSYS2/MinGW (rutas por defecto)
OPENBLAS_INCLUDE_MSYS2 = /mingw64/include
OPENBLAS_LIB_MSYS2 = /mingw64/lib

# Librería OpenBLAS
LIBS = -lopenblas

# Reglas de compilación
.PHONY: all clean help vcpkg manual msys2

all: help

# Compilar usando vcpkg
vcpkg:
\t@echo \"Compilando con vcpkg...\"
\t$(CXX) $(CXXFLAGS) $(SOURCE) -I\"$(OPENBLAS_INCLUDE_VCPKG)\" -L\"$(OPENBLAS_LIB_VCPKG)\" $(LIBS) -o $(TARGET).exe
\t@echo \"¡Compilación exitosa! Ejecuta: ./$(TARGET).exe\"

# Compilar usando instalación manual
manual:
\t@echo \"Compilando con instalación manual...\"
\t$(CXX) $(CXXFLAGS) $(SOURCE) -I\"$(OPENBLAS_INCLUDE_MANUAL)\" -L\"$(OPENBLAS_LIB_MANUAL)\" $(LIBS) -o $(TARGET).exe
\t@echo \"¡Compilación exitosa! Ejecuta: ./$(TARGET).exe\"

# Compilar usando MSYS2/MinGW
msys2:
\t@echo \"Compilando con MSYS2/MinGW...\"
\t$(CXX) $(CXXFLAGS) $(SOURCE) -I\"$(OPENBLAS_INCLUDE_MSYS2)\" -L\"$(OPENBLAS_LIB_MSYS2)\" $(LIBS) -o $(TARGET).exe
\t@echo \"¡Compilación exitosa! Ejecuta: ./$(TARGET).exe\"

# Compilar con rutas del sistema (si OpenBLAS está en PATH)
system:
\t@echo \"Compilando con rutas del sistema...\"
\t$(CXX) $(CXXFLAGS) $(SOURCE) $(LIBS) -o $(TARGET).exe
\t@echo \"¡Compilación exitosa! Ejecuta: ./$(TARGET).exe\"

# Ejecutar el programa
run: $(TARGET).exe
\t@echo \"Ejecutando $(TARGET).exe...\"
\t@echo \"=================================\"
\t./$(TARGET).exe

# Compilar en modo debug
debug:
\t@echo \"Compilando en modo debug...\"
\t$(CXX) -std=c++17 -Wall -Wextra -g -DDEBUG $(SOURCE) $(LIBS) -o $(TARGET)_debug.exe
\t@echo \"¡Compilación debug exitosa! Ejecuta: ./$(TARGET)_debug.exe\"

# Verificar si OpenBLAS está instalado
check:
\t@echo \"Verificando instalación de OpenBLAS...\"
\t@echo \"Buscando cblas.h...\"
\t@if exist \"$(OPENBLAS_INCLUDE_VCPKG)\\cblas.h\" echo \"✓ Encontrado en vcpkg: $(OPENBLAS_INCLUDE_VCPKG)\"\n\t@if exist \"$(OPENBLAS_INCLUDE_MANUAL)\\cblas.h\" echo \"✓ Encontrado en instalación manual: $(OPENBLAS_INCLUDE_MANUAL)\"\n\t@if exist \"$(OPENBLAS_INCLUDE_MSYS2)\\cblas.h\" echo \"✓ Encontrado en MSYS2: $(OPENBLAS_INCLUDE_MSYS2)\"\n\t@echo \"Buscando librerías...\"
\t@if exist \"$(OPENBLAS_LIB_VCPKG)\\openblas.lib\" echo \"✓ Librería encontrada en vcpkg\"\n\t@if exist \"$(OPENBLAS_LIB_MANUAL)\\libopenblas.a\" echo \"✓ Librería encontrada en instalación manual\"\n\t@if exist \"$(OPENBLAS_LIB_MSYS2)\\libopenblas.a\" echo \"✓ Librería encontrada en MSYS2\"

# Limpiar archivos generados
clean:
\t@echo \"Limpiando archivos generados...\"
\t@if exist \"$(TARGET).exe\" del \"$(TARGET).exe\"
\t@if exist \"$(TARGET)_debug.exe\" del \"$(TARGET)_debug.exe\"
\t@if exist \"*.o\" del \"*.o\"
\t@echo \"¡Limpieza completada!\"

# Mostrar ayuda
help:
\t@echo \"=== Makefile para OpenBLAS Demo ===\"
\t@echo \"\"
\t@echo \"Targets disponibles:\"
\t@echo \"  vcpkg    - Compilar usando vcpkg\"
\t@echo \"  manual   - Compilar usando instalación manual\"
\t@echo \"  msys2    - Compilar usando MSYS2/MinGW\"
\t@echo \"  system   - Compilar usando rutas del sistema\"
\t@echo \"  debug    - Compilar en modo debug\"
\t@echo \"  run      - Ejecutar el programa (requiere compilación previa)\"
\t@echo \"  check    - Verificar instalación de OpenBLAS\"
\t@echo \"  clean    - Limpiar archivos generados\"
\t@echo \"  help     - Mostrar esta ayuda\"
\t@echo \"\"
\t@echo \"Ejemplos de uso:\"
\t@echo \"  make vcpkg    # Si instalaste con vcpkg\"
\t@echo \"  make msys2    # Si instalaste con MSYS2\"
\t@echo \"  make run      # Ejecutar después de compilar\"
\t@echo \"\"
\t@echo \"Nota: Ajusta las rutas en el Makefile según tu instalación\"
