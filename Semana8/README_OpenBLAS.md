# Instrucciones para usar OpenBLAS con Blas.cpp

## ¿Qué es OpenBLAS?

OpenBLAS es una implementación optimizada de la librería BLAS (Basic Linear Algebra Subprograms) que proporciona operaciones eficientes de álgebra lineal como:
- Multiplicación de matrices
- Producto punto de vectores
- Normas de vectores
- Operaciones nivel 1, 2 y 3 de BLAS

## Instalación de OpenBLAS en Windows

### Opción 1: Usar vcpkg (Recomendado)
```powershell
# Instalar vcpkg si no lo tienes
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Instalar OpenBLAS
.\vcpkg install openblas:x64-windows
```

### Opción 2: Descargar binarios precompilados
1. Ir a: https://github.com/xianyi/OpenBLAS/releases
2. Descargar la versión para Windows
3. Extraer en una carpeta (ej: C:\OpenBLAS)

### Opción 3: Usar MSYS2/MinGW
```bash
pacman -S mingw-w64-x86_64-openblas
```

## Compilación

### Con vcpkg:
```powershell
# Si usaste vcpkg
g++ -std=c++17 Blas.cpp -lopenblas -I"[vcpkg_root]\installed\x64-windows\include" -L"[vcpkg_root]\installed\x64-windows\lib" -o blas_demo.exe
```

### Con Visual Studio:
```powershell
# Compilar con MSVC
cl /EHsc /std:c++17 Blas.cpp /I"C:\OpenBLAS\include" /link /LIBPATH:"C:\OpenBLAS\lib" openblas.lib -o blas_demo.exe
```

### Con MinGW/GCC:
```powershell
# Si instalaste OpenBLAS manualmente
g++ -std=c++17 Blas.cpp -I"C:\OpenBLAS\include" -L"C:\OpenBLAS\lib" -lopenblas -o blas_demo.exe

# Si usaste MSYS2
g++ -std=c++17 Blas.cpp -lopenblas -o blas_demo.exe
```

## Ejecución

```powershell
.\blas_demo.exe
```

## Lo que hace el programa

El programa `Blas.cpp` demuestra las siguientes operaciones de OpenBLAS:

1. **DDOT**: Producto punto de dos vectores (x^T * y)
2. **DNRM2**: Cálculo de la norma euclidiana de un vector (||x||₂)
3. **DGEMV**: Multiplicación matriz-vector (y = α*A*x + β*y)
4. **DGEMM**: Multiplicación matriz-matriz (C = α*A*B + β*C)

### Características del código:
- Utiliza matrices y vectores grandes para demostrar el rendimiento
- Mide tiempos de ejecución de cada operación
- Muestra información del sistema OpenBLAS
- Genera datos aleatorios para las pruebas
- Imprime resultados parciales para verificación

## Ventajas de OpenBLAS

- **Optimizado**: Aprovecha instrucciones SIMD y paralelización
- **Multi-threading**: Utiliza múltiples núcleos automáticamente
- **Portable**: Funciona en diferentes arquitecturas
- **Estándar**: Compatible con la interfaz BLAS estándar

## Notas importantes

- Asegúrate de tener las DLLs de OpenBLAS en tu PATH o en el mismo directorio
- El número de threads se puede controlar con variables de entorno:
  ```powershell
  $env:OPENBLAS_NUM_THREADS = "4"
  ```
- Para matrices muy grandes, considera el uso de memoria disponible

## Solución de problemas

### Error: "cblas.h not found"
- Verifica que la ruta de include esté correcta
- Instala OpenBLAS development headers

### Error: "openblas.dll not found"
- Copia la DLL al directorio del ejecutable
- O añade la ruta de OpenBLAS al PATH del sistema

### Error de linking
- Verifica que las librerías estén en la ruta correcta
- Usa el nombre correcto de la librería (openblas, blas, etc.)
