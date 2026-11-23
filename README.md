# xv6-Watch

## Proyecto Final - Sistemas Operativos

**Universidad:** Universidad Nacional de San Cristóbal de Huamanga (UNSCH)  
**Escuela Profesional:** Ingeniería de Sistemas  
**Curso:** Sistemas Operativos (IS-380)  
**Periodo académico:** 2026-II

## 1. Descripción del proyecto

xv6-Watch es un proyecto académico basado en xv6-riscv, un sistema operativo educativo desarrollado por el MIT.

El objetivo del proyecto es ampliar las capacidades de observación del sistema operativo mediante nuevas llamadas al sistema y herramientas que permiten consultar información sobre procesos, memoria y ejecución de programas.

## 2. Integrantes y responsabilidades

| Nivel | Integrante | Responsabilidad |
|---|---|---|
| Nivel 1 | Jeancarlos | Configuración, getprocinfo y ps |
| Nivel 2 | Marco Antonio | trace y strace |
| Nivel 3 | Fernando | sysinfo y sysstat |
| Nivel 4 | Winner Alfonso | Pruebas con testwatch |
| Nivel 5 | Yojan Pool | README, monografía, PPT y LinkedIn |

## 3. Componentes principales

### ps
Muestra información sobre los procesos del sistema, incluyendo PID, PPID, estado, memoria, tiempo de CPU y llamadas al sistema.

### strace
Permite observar las llamadas al sistema realizadas por los programas mediante una máscara de seguimiento.

### sysstat
Muestra información sobre la memoria física disponible, páginas libres y procesos activos.

### testwatch
Programa de pruebas para verificar el funcionamiento de los componentes del proyecto.

## 4. Requisitos

Para compilar y ejecutar xv6-Watch se requiere:

- Ubuntu Linux o WSL2.
- Git.
- QEMU para RISC-V.
- Compilador GCC para RISC-V.
- Herramientas de compilación GNU.

## 5. Instalación y ejecución

Clonar el repositorio:

```bash
git clone https://github.com/jeancarloshuertas27-ai/xv6-watch-so-unsch.git
```

Entrar al proyecto:

```bash
cd xv6-watch-so-unsch
```

Compilar y ejecutar xv6:

```bash
make clean
make qemu
```

Dentro de xv6, ejecutar los comandos disponibles:

```text
ps
sysstat
strace 32 grep hello README
testwatch cpu
testwatch mem
testwatch fork
testwatch err
```

Nota: los comandos requieren que los módulos correspondientes estén integrados y compilados correctamente.

Para salir de QEMU, presionar Ctrl+A y luego X.

## 6. Casos de prueba

El manual del proyecto establece seis casos de prueba:

| Caso | Comando | Objetivo |
|---|---|---|
| CP-01 | ps | Verificar la información de procesos |
| CP-02 | testwatch cpu | Comprobar el incremento de tiempo de CPU |
| CP-03 | testwatch mem | Verificar el consumo de memoria |
| CP-04 | strace 32 grep hello README | Observar las llamadas read |
| CP-05 | strace 2 testwatch fork | Verificar trazabilidad y creación de procesos |
| CP-06 | testwatch err | Verificar el manejo seguro de punteros inválidos |

Los resultados de estas pruebas deberán confirmarse con las evidencias reales del equipo.

## 7. Organización del repositorio

- `kernel/`: código del núcleo de xv6.
- `user/`: programas de usuario.
- `docs/`: monografía e informe técnico.
- `evidencias/`: capturas de pruebas y resultados.
- `presentacion/`: diapositivas de sustentación.

## 8. Documentación y presentación

La monografía técnica se organizará en 11 secciones y la presentación de sustentación tendrá 10 diapositivas, de acuerdo con el manual operativo del proyecto.

## 9. Estado del proyecto

Proyecto académico en desarrollo. La integración de módulos, las pruebas y sus resultados se documentarán conforme sean verificados por el equipo.
